inherit "/d/Gondor/common/lib/town";

create_room() {
    hillside="north";
    height=4;
    road=2;
    density=3;
    extraline="On the west side of the staircase, a little stream is rushing downhill in a nice little canal made of stone. The stairs lead up to a big lawn before the Golden Hall to the south and downwards towards a square to the north.";
  add_exit("/d/Gondor/rohan/edoras/lawn","south",0);
  add_exit("/d/Gondor/rohan/edoras/square2","north",0);
   make_the_room();
  add_item(({"canal","little canal","stream","little stream","river"}),
  break_string("The little stream splashes and bubbles on its way to the "+
   "Snowstream, which runs along just outside town. The water is cold and "+
   "clear, you notice when you taste it.\n",70));
}
