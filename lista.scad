




difference(){
  translate ([ -53,-22,0])  cube([106,44,8]);
  
  {  

     cylinder(h=10, r=6/2, center=false, $fn=360);
//     cylinder(h=4, r=17/2,  center=false, $fn=360);
     translate ([ 15,0,0]) cylinder(h=10, r=7/2, center=false, $fn=360);
     translate ([ 15,0,0]) cylinder(h=5, r=14/2,  center=false, $fn=360);
     translate ([-15,0,0]) cylinder(h=10, r=7/2, center=false, $fn=360);
     translate ([-15,0,0]) cylinder(h=5, r=14/2,  center=false, $fn=360);
     translate ([-25,0,0]) cylinder(h=10, r=5.2/2, center=false, $fn=360);
     translate ([25,0,0]) cylinder(h=10, r=5.2/2, center=false, $fn=360);
  }      
}   




