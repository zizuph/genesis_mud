inherit "/d/Gondor/rohan/plains/plain";

create_plain()
{
   set_geo("flat");
   set_wet("high");
   set_grass("thick spicy dark green");
   set_land("the West Emnet");
   set_where("south");
   set_special(1);
   add_exit("l08","north",0,5);
   add_exit("k09","east",0,5);
   add_exit("j08","south",0,5);
   add_exit("k07","west",0,5);

}
