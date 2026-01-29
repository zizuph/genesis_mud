/* rd_cw_01: Caravan Way section 1 (nearest gate). */

inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";

void create_room()
{
    ::create_room();
    set_short("caravan crossing");
    set_long("Standing just east of Caravan Gate, this crossroads is a "+
             "center of action. New entrants to the city flood to the east "+
             "down Caravan Way, north to the Noble quarter, and even south "+
             "into the warrens (these probably headed for Shadow Square). "+
     "It is difficult to breathe, and hard to see anything "+
     "through all the dust being "+
             "kicked up except for the enormous gate.\n");
    add_item("entrants", "With the gate scant feet away, it is no wonder "+
             "that members of every race and profession in Athas can be "+
             "found within this dusty haze.\n");
    add_item("gate", "The gate consists of two huge doors made of thick "+
             "agafari wood, armored with hide and steel. Dark shapes move "+
             "about in the tunnel just beyond them, and beyond that the "+
             "yellow expanse of desert that is Athas.\n");
 
    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TYR_NOBLE+"rd_hr_01.c", "north", 0, 1);
    add_exit(TYR_CARAVAN+"rd_cw_02.c", "east", 0, 1);
    add_exit(TYR_WARREN+"rd_vr_04.c", "south", 0, 1);
    add_exit(TYR_GATES+"crvngate.c", "west", "@@gatepass", 1);
}

gatepass()
{
    write("You pass through the doors on this side of the gate, amazed "+
          "at just how huge they are. What sort of threat are they "+
          "supposed to keep out?  ... Or in ...\n");
    return 0;
}
