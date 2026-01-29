inherit "/d/Gondor/rohan/plains/plain";

create_plain()
{
   set_geo("rocky");
   set_wet("high");
   set_grass("high and thick dark green");
   set_land("the Westfold");
   set_where("southern");
   set_special(5);
   add_exit("k04","north",0,5);
   add_exit("j05","east",0,5);
   add_exit("/d/Gondor/rohan/road/wr4","south",0,2);
   add_exit("/d/Gondor/rohan/road/wr5","west",0,2);

}
