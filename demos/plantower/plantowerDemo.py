#
# read out the plantower pms5003 dust sensor
# average over x measurements
# U. Raich, March 2021
#
# it is connected to
# Rx: D2 GPIO 17
# Tx: D1 GPIO 16

from pms5003 import PlanTower        
print("Starting PlanTower readout...")
plantower = PlanTower()
plantower.start()
while True:
    if plantower.count == 0:
        print("Measuring for 10 s...")
    plantower.read_raw()
    plantower.decode()
    # plantower.print_results()
    plantower.sum()
    if plantower.count >9:
        plantower.print_avr_results()

        print("pm1.0: {:6.3f} pm2.5: {:6.2f}, pm10: {:6.2f}".format(
            plantower.avr_results()["pm1_0_std_avr"],
            plantower.avr_results()["pm2_5_std_avr"],
            plantower.avr_results()["pm10_std_avr"]))
        plantower.clear_sums()
