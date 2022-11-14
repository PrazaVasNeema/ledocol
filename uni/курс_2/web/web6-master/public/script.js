function updatePrice() {
  let quantity=document.getElementsByName("quantity")[0].value;
  
  // Находим select по имени в DOM.
  let select = document.getElementsByName("stuff_type")[0];
  let price = 0;
  let prices = getPrices();
  price = prices.stuffTypes[select.value];
  let img = document.getElementById("content-preview-stuff-image");

  if(select.value==="2")
    img.src = "stuff_preview/KotORII_Item_Jedi_Robe.png";
  //Работаю с радиокнопками (варианты лайтсэбер)
  document.getElementById("lightsaber_type").style.display = (select.value=="0"?"block":"none");
  if(select.value==="0"){
    let radios = document.getElementsByName("lightsaber_type");
     radios.forEach(function(radio) {
    if (radio.checked) {
      let lightsaber_type_Price = prices.lightsaberTypes[radio.value];
      if (lightsaber_type_Price !== undefined) {
        price += lightsaber_type_Price;
      }
    }
  });
  img.src = "stuff_preview/Short_Lightsaber.png";
  }
  //Работаю с чекбоксами (обвесы бластера)
  document.getElementById("blaster_features").style.display = (select.value == "1" ? "block" : "none");
  if(select.value==="1"){
     let checkboxes = document.querySelectorAll("#blaster_features input");
     checkboxes.forEach(function(checkbox) {
       if (checkbox.checked) {
         let blaster_prop_Price = prices.blasterFeatures[checkbox.name];
         if (blaster_prop_Price !== undefined) {
           price += blaster_prop_Price;
         }
       }
     });
     img.src = "stuff_preview/KotORII_Item_Blaster_Pistol.png";
}
if(!(/[0-9]/.test(quantity)===true && /[a-z]/.test(quantity)===false && parseInt(quantity)>0))
{ 
  document.getElementsByClassName("content-preview-stuff")[0].getElementsByTagName("div")[0].style.display="none";
  document.getElementsByClassName("content-preview-stuff")[0].getElementsByTagName("div")[1].style.display="block";
  return false; 
}
else{
  document.getElementsByClassName("content-preview-stuff")[0].getElementsByTagName("div")[0].style.display="block";
  document.getElementsByClassName("content-preview-stuff")[0].getElementsByTagName("div")[1].style.display="none";
}
  //Вывод цены
  document.getElementById("price").innerHTML = price * parseInt(document.getElementsByName("quantity")[0].value) + "£";

  
  return false;
}

function getPrices() {
  return {
    stuffTypes: [10000, 2000, 1000],
    lightsaberTypes: {
      lightsaber: 0,
      double_bladed: 2500,
      short: -2500,
    },
    blasterFeatures: {
      prop1: 100,
      prop2: 500,
      prop3: 1000,
    }
  };
}

function nameChanger(){
  let name=prompt("Please enter your name");
  if (name !== null) {
    document.getElementsByClassName("content-preview-stuff")[0].getElementsByTagName("span")[0].innerHTML=name;
    document.getElementsByClassName("content-preview-stuff")[0].getElementsByTagName("span")[2].innerHTML=name;
    document.getElementsByClassName("nameChanger")[0].getElementsByTagName("span")[0].innerHTML=name;
  }
    return false;
}


document.addEventListener("DOMContentLoaded", function(event) {
  console.log("DOM fully loaded and parsed");
  // Скрываю чекбоксы
  let checkboxDiv = document.getElementById("blaster_features");
  checkboxDiv.style.display = "none";
  // Находим select по имени в DOM.
  let select = document.getElementsByName("stuff_type")[0];
  // Назначаем обработчик на изменение select.
  select.addEventListener("change", function(event) {
    let target = event.target;
    console.log(target.value);
    updatePrice();
  });
  
  // Назначаем обработчик радиокнопок.  
  let radios = document.getElementsByName("lightsaber_type");
  radios.forEach(function(radio) {
    radio.addEventListener("change", function(event) {
      let r = event.target;
      console.log(r.value);
      updatePrice();
    });
  });

    // Назначаем обработчик радиокнопок.  
  let checkboxes = document.querySelectorAll("#blaster_features input");
  checkboxes.forEach(function(checkbox) {
    checkbox.addEventListener("change", function(event) {
      let c = event.target;
      console.log(c.name);
      console.log(c.value);
      updatePrice();
    });
  });

  let quantity=document.getElementsByName("quantity");
  quantity[0].addEventListener("change", function(event){
    console.log(quantity[0].value);
    updatePrice();
  })

  updatePrice();

  let b = document.getElementById("click1");
  
  b.addEventListener("click", nameChanger);
  
});
