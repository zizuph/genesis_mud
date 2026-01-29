/* zgbuild1: Western section of Tyr's Brickyards, 01/11/96. */
 
#pragma strict_types
 
inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"
 
void
reset_room()
{
    bring_room_mob("slave", ATH_PERSON+"slav_hmn.c", 6, 1);
}
 
void
create_room()
{
    ::create_room();
    set_short("western brickyards");
    set_long("The air is filled with the sound of shattering stone, "
            +"punctuated by the occasional strike of a whip and some "
            +"soft moans. It is here that the bricks of the city are "
            +"carved or molded by the teaming slave population, most "
            +"to end up in the Kalak's ziggurat which looms to the "
            +"south.\n");
 
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
 
    add_exit(TZ_SLAVE+"rd_tr_02.c", "northwest", 0, 1);
    add_exit(TZ_SLAVE+"zgbuild2.c", "east", 0, 1);
 
    reset_room();
}
