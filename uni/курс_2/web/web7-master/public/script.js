document.addEventListener("DOMContentLoaded", function(event) {
    console.log("DOM fully loaded and parsed");
    $('.gallery').slick({
    slidesToShow: 4,
    slidesToScroll: 4,
    dots: true,
    responsive: [
{
  breakpoint: 1024,
  settings: {
    slidesToShow: 2,
    slidesToScroll: 2
  }
},
]
    });
});
