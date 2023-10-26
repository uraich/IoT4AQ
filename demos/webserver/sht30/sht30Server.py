import picoweb
import time
from machine import Pin
# import the SHT3X class
from sht3x import SHT3X,SHT3XError
# import the plantower class
from pms5003 import PlanTower
import wifi_connect

print ("Connecting to the network")
wifi_connect.connect()
ipaddr=wifi_connect.getIPAddress()

app = picoweb.WebApp(None)

monthTable ={ 1: 'January',
              2: 'February',
              3: 'March',
              4: 'April',
              5: 'May',
              6: 'June',
              7: 'July',
              8: 'August',
              9: 'September',
              10: 'October',
              11: 'November',
              12: 'December'}

# create a SHT3X object
try:
    sht30 = SHT3X()
except SHT3XError as exception:
    if exception.error_code == SHT3XError.BUS_ERROR:
        print("SHT30 module not found on the I2C bus, please connect it")
        sys.exit(-1)
    else:
         raise exception
# start the plantower driver     
AVERAGE = 5

@app.route("/")
@app.route("/temp")
def html(req, resp):
    plantower = PlanTower()
    plantower.start()
    for i in range(AVERAGE):
         plantower.read_raw()
         # skip badly read lines from PlanTower sensor
         if plantower.decode():
             # plantower.print_results()
             plantower.sum()
         else:
             i:-1
    pm1_0 = plantower.avr_results()["pm1_0_std_avr"]
    pm2_5 = plantower.avr_results()["pm2_5_std_avr"]
    pm10  = plantower.avr_results()["pm10_std_avr"]
    plantower.clear_sums()
    plantower.deinit()
    t,h = sht30.getTempAndHumi(clockStretching=SHT3X.CLOCK_STRETCH,repeatability=SHT3X.REP_S_HIGH)
    print("Temperature: ",t,"°C, Humidity: ",h,"%")
    print("Dust measurement: pm 1.0: {:5.2f}, pm 2.5: {:5.2f}, pm 10: {:5.2f}".format(pm1_0,pm2_5,pm10))
    tm = time.localtime(time.time())
    timeStamp = '{0:02d} {1} {2:04d} {3:02d}:{4:02d}:{5:02d}'.format(tm[2],monthTable[tm[1]],tm[0],tm[3],tm[4],tm[5])
    # sensor={"tmpr":t,"hmdty":h,"timeStamp":timeStamp}
    # msg = (b'{0:3.1f} {1:3.1f}'.format(t,h))
    
    sensor={"tmpr":t,"hmdty":h,
            "pm_1_0":pm1_0,
            "pm_2_5":pm2_5,
            "pm_10" :pm10,
            "timeStamp":timeStamp}
    msg = (b'{0:3.1f} {1:3.1f} {2:4.2f}, {3:4.2f}, {4:4.2f}'.format(t,h,pm1_0,pm2_5,pm10))
    
    print(msg)
    yield from picoweb.start_response(resp, content_type = "text/html; charset=utf-8")
    yield from app.render_template(resp, "sensor.tpl", (sensor,))
    
app.run(debug=True, host =ipaddr,port=80)
