inherit "/d/Gondor/rohan/plains/plain";

create_plain()
{
   set_geo("flat");
   set_wet("high");
   set_grass("long and spicy dark green");
   set_land("the West Emnet");
   set_where("south");
   set_special(1);
   add_exit("l09","north",0,5);
   add_exit("k10","east",0,5);
   add_exit("j09","south",0,5);
   add_exit("k08","west",0,5);

}
