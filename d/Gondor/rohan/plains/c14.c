inherit "/d/Gondor/rohan/plains/plain";

create_plain() 
{
   set_geo("open");
   set_wet("damp");
   set_grass("long, dark green and spicy");
   set_land("the Eastfold");
   set_where("south");
   set_special(2);
   add_exit("d14","north",0,5);
   add_exit("c15","east",0,5);
   add_exit("b14","south",0,5);
   add_exit("c13","west",0,5);
}

