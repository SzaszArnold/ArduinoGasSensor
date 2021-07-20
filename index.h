//Store data in flash (program) memory instead of SRAM
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style>
    .card {
        position: fixed;
        top: 50%;
        left: 50%;
        /* bring your own prefixes */
        transform: translate(-50%, -50%);
        align-items: center;
        font-size: 20px;
        max-width: 1000px;
        align-content: center;
        size: 50px;
        min-height: 500px;
        background: #02b875;
        padding: 30px;
        box-sizing: border-box;
        color: #FFF;
        box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.75);
        font-family: Helvetica;
        display: inline-block;
        vertical-align: middle;
        text-align: center;
    }

    .button {
        background-color: #F92E03;
        border: none;
        color: white;
        padding: 16px 40px;
        text-decoration: none;
        font-size: 30px;
        margin: 2px;
        cursor: pointer;
    }

    .button2 {
        background-color: #555555;
    }
</style>

<body>

    <div class="card">
        <h1 class="button" >ESP32 Project with MQ-2 gas sensor.</h1><br>
        <h4>If the gas value is greater than 3000ppm, the system automatically interrupts.</h4><br>
        <h1>Sensor Value:<span id="GasValue">0</span> ppm</h1><br>
        <img src="https://cdn.displays2go.com/images/zoom/fd2418fg.rw_zoom.jpg" id="warning" alt="Flowers" style="width:100px; visibility:hidden;" ><br>
        <h4>Manual Interrupt: <span id="spanManual">OFF</span></h4><br>
        <input id="btnManual" type="button" class="button" name="Interrupt" value="Manual Intterupt">
        
    </div>

    <script>
        var xhttp = new XMLHttpRequest();
        var audio = new Audio( 
        'https://media.geeksforgeeks.org/wp-content/uploads/20190531135120/beep.mp3'); 
        document.getElementById("btnManual").addEventListener("click", () => {
            var state = document.getElementById("spanManual").innerHTML;
            if (state == "ON") {
                document.getElementById("spanManual").innerHTML = "OFF";
            }
            else {
                document.getElementById("spanManual").innerHTML = "ON";
            }
            xhttp.open("GET", "manualInterrupt", true);
            xhttp.send();
        })
        setInterval(function () {
            getData();
        }, 1000); //1000mSeconds update rate

        function getData() {
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                  if(this.responseText>=3000){
                   audio.play(); 
                   document.getElementById("warning").style.visibility="visible";
                    }
                    else{
                      document.getElementById("warning").style.visibility="hidden";
                      }
                    document.getElementById("GasValue").innerHTML =
                        this.responseText;
                }
            };
            xhttp.open("GET", "readGas", true);
            xhttp.send();
        }


    </script>
</body>

</html>
)=====";
