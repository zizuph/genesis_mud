inherit "/d/Gondor/rohan/plains/plain";

create_plain() 
{
   set_geo("open");
   set_wet("damp");
   set_grass("long, dark green and spicy");
   set_land("the Eastfold");
   set_where("eastern");
   set_special(2);
   add_exit("e14","north",0,5);
   add_exit("d15","east",0,5);
   add_exit("c14","south",0,5);
   add_exit("d13","west",0,5);
}

