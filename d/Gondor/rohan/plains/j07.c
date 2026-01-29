inherit "/d/Gondor/rohan/plains/plain";

create_plain()
{
   set_geo("open");
   set_wet("dry");
   set_grass("high green");
   set_land("the Westfold");
   set_where("northern");
   set_special(2);
   add_exit("k07","north",0,5);
   add_exit("j08","east",0,5);
   add_exit("i07","south",0,5);
   add_exit("j06","west",0,5);

}
