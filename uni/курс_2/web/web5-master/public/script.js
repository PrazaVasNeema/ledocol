  function clickPrice() {
  let f1 = document.getElementsByName("colour");
  let f2 = document.getElementsByName("quantity");
  let f3 = document.getElementsByName("type");
  let r = document.getElementById("price");
  let multi;
  if (/[0-9a-z]/.test(f2[0].value)===false)
  { 
      alert("Plese input a value");
     return false; 
  }  
  if (/[a-z]/.test(f2[0].value)===true)
  { 
      alert("Plese input a correct value");
     return false; 
  }  
  if (f3[0].value==="dual-bladed"){
      alert("Sorry! Dual-bladed lightsabers are out of stock!");
      return false;
  }
  multi=parseInt(f1[0].value)*parseInt(f2[0].value);
  r.innerHTML = multi + "£";
  let img = document.getElementById("content-preview-lightsaber-image");
  switch (parseInt(f1[0].value)){
      case 1000:
        img.src = "lightsabers%20previews/red.png";
        break;
      case 1100:
          img.src = "lightsabers%20previews/blue.png";
        break;
      case 1800:
          img.src = "lightsabers%20previews/yellow.png";
        break;
      case 1900:
          img.src = "lightsabers%20previews/gold.png";
        break;
      case 2200:
          img.src = "lightsabers%20previews/silver.png";
        break;
      case 3700:
          img.src = "lightsabers%20previews/green.png";
        break;
      case 8000:
          img.src = "lightsabers%20previews/purple.png";
          break;
      case 9900:
          img.src = "lightsabers%20previews/turquoise.png";
          break;
      case 16500:
          img.src = "lightsabers%20previews/viridian.png";
          break;
      case 19000:
          img.src = "lightsabers%20previews/sunshine.png";
  }
  document.getElementsByClassName("content-preview-lightsaber")[0].getElementsByTagName("p")[0].style.display="block";
  document.getElementsByClassName("content-preview-lightsaber")[0].getElementsByTagName("p")[1].style.display="block";
  document.getElementById("content-preview-lightsaber-image").style.display="block";
  return false;
}
function nameChanger(){
  let name=prompt("Please enter your name");
  if (name !== null) {
    document.getElementsByClassName("content-preview-lightsaber")[0].getElementsByTagName("span")[0].innerHTML=name;
    document.getElementsByClassName("nameChanger")[0].getElementsByTagName("span")[0].innerHTML=name;
  }
    return false;
}
document.addEventListener("DOMContentLoaded", function(event) {
  console.log("DOM fully loaded and parsed");
  let a = document.getElementById("click0");
  let b = document.getElementById("click1");
  a.addEventListener("click", clickPrice);
  b.addEventListener("click", nameChanger);
});
