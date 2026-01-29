inherit "/d/Gondor/rohan/plains/plain";

create_plain()
{
   set_geo("flat");
   set_wet("dry");
   set_grass("long green");
   set_land("the West Emnet");
   set_where("south");
   set_special(1);
   add_exit("l07","north",0,5);
   add_exit("k08","east",0,5);
   add_exit("j07","south",0,5);
   add_exit("k06","west",0,5);

}
