#pragma strict_types

inherit "/std/object";
inherit "/lib/commands";

#include "guild.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include "/d/Ansalon/goodlund/bloodsea/local.h"

#define MAX_GUILD_LEVEL 12

#define MARINER_TITLES    ({ "a Fresh Deckhand of the High Seas", \
                             "a Midshipman of the High Seas", \
                             "a Skilled Midshipman of the High Seas", \
                             "a Firstclass Midshipman of the High Seas", \
                             "an Able-Bodied Seafarer of Genesis", \
                             "an Experienced Seafarer of Genesis", \
                             "an Experienced Seafarer of Genesis", \
                             "a Mariner of Genesis", \
                             "a Mariner of Genesis", \
                             "a Seasoned Mariner of Genesis", \
                             "a Master Mariner of Genesis", \
                             "a Sea Captain of Genesis", \
                             "a Renowned Sea Captain of Genesis"})

static string *titles = MARINER_TITLES;


void
create_object()
{

   set_name("spyglass");
   add_name(GUILD_EMBLEM_ID);
   add_adj(({"gnomish"}));
   set_short("gnomish spyglass");

   set_long("A remarkable invention, this is a small tube with carefully crafted " +
     "glass lenses at either end that allow you to view distant objects as if you " +
     "were right next to them!  This one looks a bit battered and worn over time, " +
     "and it looks like it once had a number of bells and whistles attached to it " +
     "that have since been ripped off.\nYou may find out information " +
     "about the mariners through <help mariner menu>.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GET,  0);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME,  2000);
    add_prop(OBJ_I_VALUE, 2000);

    seteuid(getuid(TO));
    TP->add_subloc("mariner_craft_guild", TO);

}

/* Function name: query_guild_level_craft
 * Description:   What is the member's level within the guild?
 * Returns:	  int - the level
 */
int
query_guild_level_craft()
{

    return MIN(MAX_GUILD_LEVEL, E(TO)->query_stat(SS_CRAFT) /12);


}

string
show_subloc(string subloc, object me, object for_obj)
{

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
        return "You are " +titles[query_guild_level_craft()]+ ".\n";
    else
        return C(PRONOUN(me)) + " is " +titles[query_guild_level_craft()]+ ".\n";
}

int
investigate(string str)
{
   notify_fail("The gnomish gadget doesn't seem to work here!\n");
   return 0;
}


void
init()
{
    ::init();
    add_action(investigate, "investigate");

}

