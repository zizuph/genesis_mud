inherit "/d/Gondor/rohan/plains/plain";

create_plain()
{
   set_geo("open");
   set_wet("high");
   set_grass("long green");
   set_land("the Westfold");
   set_where("central");
   set_special(2);
   add_exit("j08","north",0,5);
   add_exit("i09","east",0,5);
   add_exit("h08","south",0,5);
   add_exit("i07","west",0,5);

}
