/* rd_ds_01: Diamond Street section 1: Serpine, 04-23-95 */

inherit "/std/room";
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "defs.h"


void
create_room()
{
    ::create_room();
    set_short("diamond street west");
    set_long("Though technically outside the gate that seperates the "+
             "Nobles' Quarter west of here from the rest of the city, this "+
             "end of Diamond Street is the site of the Senators' Hall. "+
             "Squatting to the south, the structure has served as both "+
             "meeting place and tavern for the nobles of Tyr since before "+
             "the gate existed, and its owners have seen no need to move. "+
             "Diamond Street continues east towards what is sometimes "+
             "called the 'Slaves District.'\n");

    add_item(({"structure", "hall", "senators' hall"}), "A large building, "+
             "built from heavy stones and engraved with images.\n");

    add_item(({"image", "images", "stone", "stones", "heavy stones"}), "The "+
             "images are of nobles in their favorite pursuit: Pleasure.\n");

    add_item("gate", "Its relatively large but wide open.\n");

    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TYR_NOBLE+"rd_hr_04.c", "west", "@@gate_message", 1);
    add_exit(TYR_HALL+"sh_lobby.c", "south", 0, 1);
    add_exit(TYR_SLAVE+"rd_ds_02.c", "east", 0, 1);
}

public int
gate_message()
{
    TP->catch_msg("You feel you are being watched as you pass "+
                  "under the large gate.\n");
    return 0;
}
