inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("The entrance of the House of Aemilius");
    INSIDE;
    set_long("You have now stepped into the grand house of "+
        "the Lord Aemilius. The floor here is made of marble, "+
        "and you can see your reflection off the black surface. "+
        "Along the walls, you see many ornate candle holders holding "+
        "burning, scented candles, filling the room with exotic smells. "+
        "The walls are made of polished oak, with paintings and tapestries "+
        "hang on them. An open archway leads west, while another one leads "+
        "south and north. There two sets of spiraling staircases going up, "+
        "one to your north, and one to your south. The stairs disappear into the "+
        "ceiling above.\n");
    add_item("candles","They burn softly, giving light and smell.\n");
    add_item("walls","They are very polished, and gleam with an "+
        "inner beauty.\n");
    add_item("paintings","They depict scenes of battles.\n");
    add_item("tapestries","They are woven with intricate symbols "+
        "and designs.\n");
    add_item("staircases","They are made of black, wooden platforms "+
        "that spiral up and up.\n");
    add_exit(NOBLE(aemilius/m12),"stair1",0,-1,-1);
    add_exit(NOBLE(aemilius/m14),"stair2",0,-1,-1);
    add_exit(NOBLE(aemilius/m7),"west",0,-1,-1);
    add_exit(NOBLE(aemilius/m3),"north",0,-1,-1);
    add_exit(NOBLE(aemilius/m2),"south",0,-1,-1);
    add_exit(NOBLE(aemilius/g3),"east",0,-1,-1);
}

