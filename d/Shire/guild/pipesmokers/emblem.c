#pragma strict_types

inherit "/std/object";
inherit "/lib/commands";

#include "guild.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>
#include "/d/Shire/sys/defs.h"
#include <wa_types.h>

#define E(ob)        environment(ob)
#define HIS(x)        ((x)->query_possessive())
#define HIM(x)        ((x)->query_objective())
#define HE(x)         ((x)->query_pronoun())
#define C(xxx)       capitalize(xxx)

// If you want titles in the subloc use the following in the guild object
#define MAX_GUILD_LEVEL 12
#define PIPESMOKER_TITLES    ({ "Gagging Newbie Smokesniffer", \
                             "Novice Pipesmoker", \
                             "Green Pipesmoker", \
                             "Pipesmoker", \
                             "Capable Pipesmoker", \
                             "Experienced Pipesmoker", \
                             "Robust Pipesmoker", \
                             "etc", \
                             "etc", \
                             "etc", \
                             "etc", \
                             "etc", \
                             "Pipesmoker, Ringblower Extraordinaire"})

static string *titles = PIPESMOKER_TITLES;

void
create_object()
{

   set_name("pipe");
   add_name(GUILD_EMBLEM_ID);
   add_adj(({"long"}));
   set_short("long pipe");

   set_long("Guild object for pipesmokers.\nYou may find out information " +
     "about the pipesmokers through <help pipesmokers menu>.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GET,  0);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME,  2000);
    add_prop(OBJ_I_VALUE, 2000);

    seteuid(getuid(TO));
    TP->add_subloc("pipesmoker_craft_guild", TO);

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
        return "You are a " +titles[query_guild_level_craft()]+ ".\n";
    else
        return C(PRONOUN(me)) + " is a " +titles[query_guild_level_craft()]+ ".\n";
}

// If you want your guild object to have their own commands outside of what
// is in the cmdsoul, you can put the following sort of stuff.

int
smokepipe(string str)
{
   if(str == "pipe")
   {
      write("You puff contently on your pipe.\n");
      say(QCTNAME(this_player())+ " puffs contently on " +HIS(this_player())+
          " pipe.\n");
      return 1;
   }

   notify_fail("Smoke what?!\n");
   return 0;
}

void
init()
{
    ::init();
    add_action(smokepipe, "smoke");

}
