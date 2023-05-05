const char htmlindex[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>

<head lang="es">
    <meta charset="UTF-8">
    <title>3D</title>
    <style>
        html * {
            font-family: 'Tohomo Font TH', 'Noto Sans Light', 'Arial Nue', Helvetica;
            margin: 0;
            padding: 0;
        }

        body {
            height: 100vh;
            background-image: linear-gradient(180deg, #202124 0%, #010101 100%);
        }

        button p {
            background-image: linear-gradient(35deg, #44baff 0%, #00ffd5 100%);
            font-size: 2em;
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
        }

        button {
            position: absolute;
            border: none;
            background-image: linear-gradient(35deg, #000000 0%, #242527 100%);
            outline: none;
            cursor: pointer;
            top: 5vh;
        }

        button:hover {
            background-image: linear-gradient(35deg, #000000 0%, #000000 100%);
        }

        button:active {
            background-image: linear-gradient(35deg, #447fff 0%, #00ff9d 100%);
        }

        @media (hover: none) and (pointer: coarse) {
            main {
                height: 40vh;
                max-height: 20vw;
                border-radius: 3vw;
                width: 80vw;
                left: 10vw;
                top: 30vh;
            }

            button {
                font-size: 1.4rem;
                padding: 2vh 8vw;
                border-radius: 1vw;
            }

            #containers {
                font-size: 3rem;
                width: 85%;
            }
        }

        @media (hover: hover) and (pointer: fine) {
            main {
                height: 40vh;
                max-height: 20vw;
                border-radius: 3vw;
                width: 30vw;
                left: 35vw;
                top: 30vh;
            }

            button {
                padding: 2vh 2vw;
                border-radius: 1vw;
            }

            #containers {
                font-size: 1.3rem;
                width: 60%;
            }
        }

        main {
            position: absolute;
            background-color: white;
        }

        #containers {
            display: flex;
            flex-direction: row;
            justify-content: space-between;
        }

        body, 
        main,
        button,
        #containers div {
            display: flex;
            flex-direction: column;
            justify-content: space-evenly;
            align-items: center;
        }
    </style>
    <script language="JavaScript">
        var json = undefined
        function run() {
            setInterval(function () {
                var containers = document.getElementById("containers")
                var xobj = new XMLHttpRequest()
                xobj.overrideMimeType("text/json")
                xobj.open("get", "/get-update", false)
                xobj.send(null)
                json = JSON.parse(xobj.responseText)

                containers.innerHTML = ""
                for (var i = 0; i < 3; i++) {
                    var div = document.createElement("div")
                    div.setAttribute("id", i + "-axis")
                    var span = document.createElement("span")
                    span.setAttribute("id", i + "-axis")
                    span.innerHTML = "Eje " + i + ":"
                    var div2 = document.createElement("div")
                    div2.setAttribute("id", "value-" + i)
                    var div3 = document.createElement("div")
                    var p = document.createElement("p")
                    p.innerHTML = Math.round(json["value-" + i] * 1000) / 1000
                    div3.appendChild(p)
                    div2.appendChild(div3)
                    div.appendChild(span)
                    div.appendChild(div2)
                    containers.appendChild(div)
                }
            }, 100)
        }
        function lock() {
            var xobj = new XMLHttpRequest()
            xobj.overrideMimeType("text/json")
            xobj.open("get", "/lock", false)
            xobj.send(null)
            console.log(xobj.responseText)
        }
    </script>
</head>

<body onload="run()">
    <button onclick="lock()">
        <p>
            >>>
        </p>
    </button>
    <main>
        <h1>Giroscopio</h1>
        <div id="containers">
            <div id="0-axis">
                <span>
                    Eje X:
                </span>
                <div id="value-0">
                    <div>
                        <p>
                            0
                        </p>
                    </div>
                </div>
            </div>
            <div id="1-axis">
                <span>
                    Eje Y:
                </span>
                <div id="value-1">
                    <div>
                        <p>
                            0
                        </p>
                    </div>
                </div>
            </div>
            <div id="2-axis">
                <span>
                    Eje Z:
                </span>
                <div id="value-2">
                    <div>
                        <p>
                            0
                        </p>
                    </div>
                </div>
            </div>
        </div>
    </main>
</body>

</html>
)rawliteral";