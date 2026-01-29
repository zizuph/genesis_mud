/* ironsqr3: Northeast section of Iron Square. */

inherit "/std/room";
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "defs.h"


void
create_room()
{
    ::create_room();
    set_short("northeast of iron square");
    set_long("As Iron Square turns from west to south, the usual "+
             "oppulence turns dark and foreboding. Pandora's End, site "+
             "of King Kalak's greatest betrayal and his fiercest revenge "+
             "leads north to the jail, while Templar Road leads east to "+
             "the slave pits and the main site of of the Ziggurat's "+
             "slave-based construction. The emblem of House Stel, the "+
             "most brutal of all the merchant houses in Tyr, defaces the "+
             "entrance to a building southwest.\n");

    add_item (({"emblem", "building"}), "Two curved obsidian blades "+
             "collide atop a bone-white field.\n");

    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM

    add_exit(TYR_SLAVE+"rd_pe_01.c", "north", 0, 1);
    add_exit(TYR_SLAVE+"rd_tr_01.c", "east", 0, 1);
    add_exit(TYR_MERCHANT+"ironsqr5.c", "south", 0, 1);
/*
    add_exit(TYR_MERCHANT+"housstel.c", "southwest", "@@house_block", 1);
*/
    add_exit(TYR_MERCHANT+"tyroffc.c", "southwest", "@@house_block", 1);
    add_exit(TYR_MERCHANT+"ironsqr2.c", "west", 0, 1);
}
