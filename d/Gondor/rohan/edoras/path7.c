inherit "/d/Gondor/common/lib/town";

create_room() {
    hillside="east";
    height=4;
    road=1;
    density=2;
    extraline ="Kingsroad is almost at its end here, almost at the top of the hill. All of the east side of Edoras can be seen below you. The great lawns, that surrounds Meduselds great walls can be see upwards to the west, but they can't be accessed from here. There is a wooden hall to the east. Kingsroad continues towards a little square to the northwest and downwards to the southwest. ";
   make_the_room();
  add_exit("/d/Gondor/rohan/edoras/hall","east",0);
  add_exit("/d/Gondor/rohan/edoras/square2","northwest",0);
  add_exit("/d/Gondor/rohan/edoras/path6","southwest",0);
}

