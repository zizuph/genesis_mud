/*
 *   /d/Gondor/ithilien/poros/npcs/prisoner.c
 *
 *   This the standard prisoner for the cells where the corsairs hold
 *   there captives in the manor base. prisoner.c is a slightly 
 *   modified version of /d/Gondor/morgul/npc/prisoner.c
 *
 *   Talisan,  February 1996
 */

#pragma strict_types

inherit "/std/monster";

#include <ss_types.h>

#include "/d/Gondor/defs.h"

string *
random_color()
{
    switch(random(8))
    {
    case 0:
        return ({ "merchant", "gondorian" });
        break;
    case 1:
        return ({ "ranger", "dunadan" });
        break;
    case 2:
        return ({ "merchant", "rohirrim" });
        break;
    case 3:
        return ({ "soldier", "gondorian" });
        break;
    case 4:
        return ({ "sailor", "gondorian" });
        break;
    case 5:
        return ({ "merchant", "haradan" });
        break;
    case 6:
        return ({ "merchant", "umbarian" });
        break;
    case 7:
        return ({ "sailor", "haradan" });
        break;
    }
}

void
create_monster()
{
    string *color;

    color = random_color();
    
    set_name(color + ({ "prisoner"}));
    add_name(({"prisoner", "man"}));
    set_race_name("human");
    add_adj("chained");
    add_adj(color[1]);
    set_long(BSN("This "+color[1]+" "+color[0]+" is one of the poor "
      + "souls who have had the misfortune of being captured by the "
      + "corsair raiders. Looking tortured and weak, the prisoner "
      + "seems destined for the slave pits of Umbar, or worse... "));

    default_config_npc(40);
    set_width_desc("very skinny");
    set_alignment(100);

    set_base_stat(SS_STR, 30);
    set_base_stat(SS_CON, 20);

}

int
query_knight_prestige() {return -1000;}
