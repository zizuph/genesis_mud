inherit "/d/Gondor/common/lib/town";

create_room() {
   hillside="north";
   height=4;
   road=4;
   density=3;
   extraline ="Here Kingroad and the staircase meet on a little square. The little stream is floating under a bridge on the west side of the square. Kingsroad continues downwards to the southeast. The staircase continues upwards towards Meduseld to the south and downwards to the north. To the southwest is another part of the Kingsroad, and a large stone building.";
   make_the_room();
  add_exit("/d/Gondor/rohan/edoras/path7","southeast",0);
  add_exit("/d/Gondor/rohan/edoras/stairs3","south",0);
  add_exit("/d/Gondor/rohan/edoras/stairs2","north",0);
  add_exit("/d/Gondor/rohan/edoras/path8","southwest",0,0);
}

