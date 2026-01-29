inherit "/d/Gondor/common/lib/town";

create_room() {
   hillside="south";
   height=2;
   road=1;
   density=1;
   extraline ="North of here there is a large important looking building. Kingsroad continues upwards to the northeast and downwards towards the stables to the northwest. ";
  make_the_room();
  add_exit("/d/Gondor/rohan/edoras/temple","north",0);
  add_exit("/d/Gondor/rohan/edoras/path4","northeast",0);
  add_exit("/d/Gondor/rohan/edoras/path2","northwest",0);
}
