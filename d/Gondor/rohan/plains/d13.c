inherit "/d/Gondor/rohan/plains/plain";

create_plain() 
{
   set_geo("open");
   set_wet("damp");
   set_grass("long, dark green and spicy");
   set_land("the Eastfold");
   set_where("central");
   set_special(2);
   add_exit("e13","north",0,5);
   add_exit("d14","east",0,5);
   add_exit("c13","south",0,5);
   add_exit("d12","west",0,5);
}

