const char *HTML_CONTENT_HOME = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.6.0/css/all.min.css">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Inter:wght@100..900&family=Roboto+Slab:wght@100..900&family=Roboto:ital,wght@0,100;0,300;0,400;0,500;0,700;0,900;1,100;1,300;1,400;1,500;1,700;1,900&display=swap" rel="stylesheet">
    <!-- <link rel="stylesheet" href="./main.css"> -->
     <style>
        body {
            background-color: rgb(165, 208, 163);
            font-family: "Roboto", sans-serif;
        }
        
        .sensor-panel {
            display: flex;
            flex-direction: column;
            width: 250px;
            margin: auto;
        }
        .sensor {
            padding: 20px;
            color: white;
            margin-bottom: 15px;
            text-align: right;
            border-radius: 10px;
            display: flex;
            flex: 1;
            justify-content: space-between; 
            font-size: 20px;
        }
        
        .led { 
            background-color: #8e8e93; 
            display: flex;
            align-items: center;
            height: 80px;
            margin-bottom: 10px;
            justify-content: center;
            border-radius: 10px;
            color: wheat;
            font-weight: bold;
        }
        .temp { background: linear-gradient(180deg, #FF919D 0%, #FC929D 100%); }
        .humi { background: linear-gradient(180deg, #bb67ff 0%, #c484f3 100%); }
        .light { background: linear-gradient(rgb(248, 212, 154) -146.42%, rgb(255 202 113) -46.42%); 
               
            
        }
        
        .sensor_block {
            margin-right: 10px;
            margin-top: auto;
            margin-bottom: auto;   
            font-weight: bold; 
        }
        
        .value {
            margin-top: 5px;
            font-weight: bold;
            font-size: 25px;
        }
        
        button {
            padding: 10px;
            margin-top: 5px;
            cursor: pointer;
        }

        a {
          color: white;
          text-decoration: none;
          font-weight: bold;
        }
        
        .on-button { 
            background-color: green; 
            border: none;
            margin-left: 10px;
            margin-right: 10px;
        }
        
        .on-button:hover {
            background-color: #4cd964;
        }
        
        .off-button { 
            background-color: red; 
            border: none;
        }
        
        .off-button:hover {
            background-color: #ff2d55;
        }
        
        div[role="progressbar_light"] {
            --size: 80px;
            --fg: white;
            --bg: rgb(154, 153, 153) 80%;
            --pgPercentage: calc(var(--value)/40);
            animation: growProgressBar 3s 1 forwards;
            width: var(--size);
            height: var(--size);
            border-radius: 50%;
            display: grid;
            place-items: center;
            background: 
              radial-gradient(closest-side, rgb(154, 153, 153) 80%, transparent 0 99.9%, white 0),
              conic-gradient(var(--fg) calc(var(--pgPercentage) * 1%), var(--bg) 0)
              ;
            font-family: Helvetica, Arial, sans-serif;
            font-size: calc(var(--size) / 4);
            color: var(--fg);
            filter: drop-shadow(2px 4px 6px white);
            font-weight: bold;
          }
          
          div[role="progressbar_light"]::before {
            counter-reset: percentage var(--value);
            content: counter(percentage);
          }
        
          div[role="progressbar_temp"] {
            --size: 80px;
            --fg: white;
            --bg: rgb(154, 153, 153) 80%;
            --pgPercentage: calc(var(--value)*10/4);
            animation: growProgressBar 3s 1 forwards;
            width: var(--size);
            height: var(--size);
            border-radius: 50%;
            display: grid;
            place-items: center;
            background: 
              radial-gradient(closest-side, rgb(154, 153, 153) 80%, transparent 0 99.9%, white 0),
              conic-gradient(var(--fg) calc(var(--pgPercentage) * 1%), var(--bg) 0)
              ;
            font-family: Helvetica, Arial, sans-serif;
            font-size: calc(var(--size) / 4);
            color: var(--fg);
            filter: drop-shadow(2px 4px 6px white);
            font-weight: bold;
          }
          
          div[role="progressbar_temp"]::before {
            counter-reset: percentage var(--value);
            content: counter(percentage) '°C';
          }
        
          div[role="progressbar_humi"] {
            --size: 80px;
            --fg: white;
            --bg: rgb(154, 153, 153) 80%;
            --pgPercentage: calc(var(--value));
            animation: growProgressBar 3s 1 forwards;
            width: var(--size);
            height: var(--size);
            border-radius: 50%;
            display: grid;
            place-items: center;
            background: 
              radial-gradient(closest-side, rgb(154, 153, 153) 80%, transparent 0 99.9%, white 0),
              conic-gradient(var(--fg) calc(var(--pgPercentage) * 1%), var(--bg) 0)
              ;
            font-family: Helvetica, Arial, sans-serif;
            font-size: calc(var(--size) / 4);
            color: var(--fg);
            filter: drop-shadow(2px 4px 6px white);
            font-weight: bold;
          }
          
          div[role="progressbar_humi"]::before {
            counter-reset: percentage var(--value);
            content: counter(percentage) '%';
          }
          
          /* demo */
          .bar{
            margin-left:10px;
          }
        
          .icon {
            color: rgb(253, 250, 250);
            margin-bottom: 5px;
          }
     </style>
</head>
<body>
    <div class="sensor-panel">
        <div class="led">
            LED
            <button class="on-button">
              <a href='/?state=on'>ON</a>
            </button>
            <button class="off-button">
              <a href='/?state=off'>OFF</a>
            </button>
        </div>
       
        <div class="sensor temp">
            <div id="bar_temp" class="bar" role="progressbar_temp" aria-valuenow="65" aria-valuemin="0" aria-valuemax="100" style=%temp_style%></div>
            <div class="sensor_block">

                <div class="icon">
                    <i class="fa-solid fa-temperature-three-quarters"></i>
                </div>
                Temp
                <div class="value" id="temperature">%temp%°C</div>
            </div>
        </div>
       
        <div class="sensor humi">
            <div id="bar_humi" class="bar" role="progressbar_humi" aria-valuenow="65" aria-valuemin="0" aria-valuemax="100" style=%humi_style%></div>
            <div class="sensor_block">
                <div class="icon">
                    <i class="fa-solid fa-droplet"></i>
                </div>
                Humi
                <div class="value" id="humidity">%humi%%</div>
            </div>
        </div>
       
        <div class="sensor light">
            <div id="bar_light" class="bar" role="progressbar_light" aria-valuenow="65" aria-valuemin="0" aria-valuemax="100" style=%light_style%></div>
            <div class="sensor_block">
                <div class="icon">
                    <i class="fa-solid fa-sun"></i>
                </div>
                Light
                <div class="value" id="light_item">%light%</div>
            </div>
        </div>
       
    </div>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("bar_temp").style.cssText = "--value:" + this.responseText;
      document.getElementById("temperature").innerHTML = this.responseText + "°C";
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("bar_humi").style.cssText = "--value:" + this.responseText;
      document.getElementById("humidity").innerHTML = this.responseText + "%";
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("bar_light").style.cssText = "--value:" + this.responseText;
      document.getElementById("light_item").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/light", true);
  xhttp.send();
}, 10000 ) ;

</script>
</html>
)=====";
