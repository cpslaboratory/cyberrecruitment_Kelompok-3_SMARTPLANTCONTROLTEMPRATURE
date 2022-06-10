function darkmode() {
  dark_Mode = localStorage.getItem("dark-mode");
  const element = document.querySelector(".darklight");
  const sec = document.querySelector(".sec");
  const toggle = document.querySelector(".toggle");
  sec.classList.toggle("dark");
  if (element.innerHTML === "Dark") {
    element.innerHTML = "Light";
  } else {
    element.innerHTML = "Dark";
  }
  if (dark_Mode !== "enable") {
    enableDarkMode();
  } else {
    disableDarkMode();
  }
}

let dark_Mode = localStorage.getItem("dark-mode");

const enableDarkMode = () => {
  document.body.classList.add("dark-mode");
  localStorage.setItem("dark-mode", "enable");
};

const disableDarkMode = () => {
  document.body.classList.remove("dark-mode");
  localStorage.setItem("dark-mode", null);
};

if (dark_Mode === "enable") {
  document.querySelector(".sec").classList.toggle("dark");
}

var lampu = 0;
var kipas = 0;
var data = {}

setInterval(function () {
  fetch("https://smart-temp.herokuapp.com/api")
    .then((hasil) => hasil.json())
    .then((res) => {
      console.log(res.now);
      data = res.now;
      document.getElementById("suhu").innerHTML = res.temperature.toString() + "°C";
      document.getElementById("kelembaban").innerHTML = res.humidity.toString() + "%";
      if (res.lampu == 1) {
        lampu = 1;
        document.getElementById("lampu").innerHTML = value = "ON";
        document.getElementById("switchlampu").checked = true;
      } else {
        lampu = 0;
        document.getElementById("lampu").innerHTML = value = "OFF";
        document.getElementById("switchlampu").checked = false;
      }
      if (res.kipas == 1) {
        kipas = 1;
        document.getElementById("kipas").innerHTML = value = "ON";
        document.getElementById("switchkipas").checked = true;
      } else {
        kipas = 0;
        document.getElementById("kipas").innerHTML = value = "OFF";
        document.getElementById("switchkipas").checked = false;
      }
    });
}, 1000);

function nilailampu(value) {
  if (value == true) {
    value = "ON";
    lampu == 1;
  } else {
    value = "OFF";
    lampu = 0;
  }
  document.getElementById("lampu").innerHTML = value;
}

function nilaikipas(value) {
  if (value == true) value = "ON";
  else value = "OFF";
  document.getElementById("kipas").innerHTML = value;
}
