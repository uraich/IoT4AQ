{% args sensor %}
<html>
<head>
  <title>Temperature, humidity and dust density</title>
  <style>
  table, th, td {
  	 border: 1px solid black;
  	 padding: 5px;
	 }
  table {
  	border-spacing: 15px;
  }
  </style>
</head>
<body>
<h1> Temperature, humidity and dust concentration </h1>
<table>
  <tr>
    <th align="left">measurement</th>
    <th align="left">value</th>
    <th align="left">timestamp</th>
  </tr> 
  <tr>
    <td>temperature:</td>
    <td>{{sensor['tmpr']}}</td>
    <td>taken at: {{sensor['timeStamp']}}</td>
  </tr>
  <tr>
    <td>humidity:</td>
    <td>{{sensor['hmdty']}}</td>
  </tr>
  <tr>
    <td>pm 1.0:</td>
    <td>{{sensor['pm_1_0']}}</td>
  </tr>
  <tr>
    <td>pm 2.5:</td>
    <td>{{sensor['pm_2_5']}}</td>
  </tr>
  <tr>
    <td>pm 10:</td>
    <td>{{sensor['pm_10']}}</td>
  </tr>
</table>

</body>

</html>
