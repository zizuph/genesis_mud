/* rd_pe_03: Northern section of Pandora's End. */
 
inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";

void
create_room()
{
        ::create_room();
    set_short("pandora's End north");
    set_long("An aura of menace fills the north section of Pandora's "
            +"End. Just east through a blighted thorn patch the towering "
             +"jail of Tyr gazes out across the city. Once bright and "
             +"rich, as befitted the home of the High Templar who's ebony "
            +"statue rests here, the pigments have fallen away revealing "
            +"cold grey stone and weathered wood. The screams of tortured "
            +"prisoners occasionally echo from within, filling you with a "
            +"strong desire to flee south down the road or, better still, "
            +"north towards Diamond Street.\n");
 
    add_item("jail", "Blotting out the bloated sun, this dark tower is "
            +"the final stop for many of Tyr's criminals and dissidents. "
            +"The lucky die before they ever near this place.\n");
    add_item(({"patch", "thorn patch", "blighted thorn patch"}), 
             "The thorns have been shaped to resemble a set of gigantic "
            +"nightmare beasts and cilopsi.\n");
    add_item(({"statue", "ebony statue"}), "The statue depicts the last "
            +"stand of the traitor High Templar Pandora. You have never "
            +"seen human entrails and blood so skillfully depicted in "
            +"stone. Another statue is off to the south.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM
 
    add_exit(TYR_SLAVE+"rd_ds_02.c", "north", 0, 1);
    add_exit(TYR_SLAVE+"rd_pe_02.c", "south", 0, 1);
 /*
    add_exit(TYR_JAIL+"c38.c","east","@@goeast",1);
  */
}

int
goeast()
{
  TP->catch_msg(
    "Passing by the thorn patch you feel a sudden chill, despite "+
    "the heat of the crimson sun.\n");
  return 0;
}
