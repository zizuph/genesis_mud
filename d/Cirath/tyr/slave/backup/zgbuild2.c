/* zgbuild2: Eastern section of Tyr's Brickyards, 01/11/96. */
 
#pragma strict_types
 
inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"
 
void
reset_room()
{
    bring_room_mob("guard", TYR_NPC+"hgiant.c", 1, 1);
    bring_room_mob("slave", TYR_NPC+"slav_hmn.c", 6, 1);
}
 
void
create_room()
{
    ::create_room();
    set_short("eastern brickyards");
    set_long("Just a few yards west of Stadium Way, this section of "
            +"the brickyards is particularly depressing. At least "
            +"elsewhere the slaves assigned to carving and molding "
            +"bricks in the scorching sun don't have to watch the "
            +"free people parading down a major road all day.\n");
 
    add_item(({"people", "free people"}),
             "They try to avoid looking into the brickyards.\n");
    add_item(({"brick", "bricks"}), "They are mostly squarish, some "
            +"carved of stone and some of mud formed in large molds.\n");
    add_item(({"mold", "molds"}), "Simple stone molds with fires "
            +"blazing beneath to bake mud solid.\n");
    add_item(({"stone", "stone bricks", "stone brick"}), "Largely "
            +"unremarkable, save for how many are being made.\n");
    add_item(({"mud", "mud bricks", "mud brick"}), "You note with some "
            +"distaste that the mud is formed from dirt moistened by "
            +"waste products.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM
 
    add_exit(TYR_SLAVE+"zgbuild1.c", "west", 0, 1);
    add_exit(TYR_SLAVE+"rd_sw_04.c", "east", "@@check_guard", 1);
 
    reset_room();
}
 
public int
check_guard()
{
    object guard = present("guard", TO);
    if(objectp(guard))
        TP->catch_msg(QCTNAME(guard) + ", seeing you are not a slave, "
                    +"ignores your passing.\n");
    return 0;
}
