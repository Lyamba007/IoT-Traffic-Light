const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .ds-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
    button {
      display: inline-block;
      margin: 0 10px 0 0;
      padding: 15px 45px;
      font-size: 48px;
      font-family: "Bitter",serif;
      line-height: 1.8;
      appearance: none;
      box-shadow: none;
      border-radius: 0;
    }
    button:focus {
     outline: none
    }
    .flat-button {
      color: #fff;
      background-color: #6496c8;
      text-shadow: -1px 1px #417cb8;
      border: none;
    }
    .flat-button:hover,
    .flat-button.hover {
      background-color: #346392;
      text-shadow: -1px 1px #27496d;
    }
    section.flat button:active,
    section.flat button.active{
      background-color: #27496d;
      text-shadow: -1px 1px #193047;
    } 
  </style>
</head>

<body>
  <h2>ESP Traffic Light Server</h2>
  <p>
    <i class="fas fa-traffic-light-go"></i>
    <span id="quantity" class="ds-labels">Click button to activate Green Wave</span> 
  </p>
  <button id="toggle" onClick="toggleButton(this.id)" class="flat-button" style="background-color:#08a045;">Activate</button>
</body>

<script>

  function toggleButton(button_id) 
  {                 
    document.getElementById(button_id).style.backgroundColor = "#ba262b";
    document.getElementById(button_id).innerText = "Wait";
    document.getElementById(button_id).disabled = true;
   
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "/greenwave/?value=1", true);
    xhttp.send();
    xhttp.onload = function() 
    {
      if (this.readyState == 4 && this.status == 200)
      {
        document.getElementById("quantity").innerHTML = "Wait 20s till Green Wave end";
      }
    };

    setTimeout(function() 
    {
      document.getElementById(button_id).style.backgroundColor = "#08a045";
      document.getElementById(button_id).innerText = "Activate";
      document.getElementById(button_id).disabled = false;

      document.getElementById("quantity").innerHTML = "Click button to activate Green Wave";
    }, 21000); // all delays
  };

</script>
</html>)rawliteral";
