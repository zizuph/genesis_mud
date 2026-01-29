inherit "/d/Gondor/rohan/plains/plain";

create_plain()
{
   set_geo("open");
   set_wet("dry");
   set_grass("short green");
   set_land("the West Emnet");
   set_where("southern");
   set_special(1);
   add_exit("l06","north",0,5);
   add_exit("k07","east",0,5);
   add_exit("j06","south",0,5);
   add_exit("k05","west",0,5);

}
