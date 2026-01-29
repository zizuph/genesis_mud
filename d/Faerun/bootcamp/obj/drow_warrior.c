/*
 * Drow Warrior NPC/Entrance camp Underdark city
 * by Clyptas, July, 2017
 */
inherit "/std/monster";

#include <macros.h>
#include "/d/Faerun/defs.h"

create_monster()
{
    set_name("warrior");

    set_race_name("drow");

    set_adj( ({"cautious"}) );

    set_stats( ({59, 79, 68, 78, 78, 50}) ;

    set_alignment(0);

    set_gender(G_MALE);
}