inherit "/d/Gondor/rohan/plains/plain";

create_plain()
{
   set_geo("open");
   set_wet("high");
   set_grass("spicy dark green");
   set_land("the Westfold");
   set_where("north");
   set_special(2);
   add_exit("k09","north",0,5);
   add_exit("j10","east",0,5);
   add_exit("i09","south",0,5);
   add_exit("j08","west",0,5);

}
