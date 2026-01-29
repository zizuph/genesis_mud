/*
 * Guild item for the Halflings of Faerun
 * Finwe, September 2015
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/cmd/std/command_driver";
inherit "/lib/help";

#include "/d/Faerun/defs.h"
#include "halflings.h"
#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#define MEDALLION_NAME  "_halfling_guild_item"

string
query_auto_load()
{
  return MASTER;
}

void
create_object()
{
    set_help_dir(GUILD_HELP);
    set_help_category(({"halfling", "half", "halflings"}));
    set_help_default("all");

    set_name("pendant");
    set_adj(({"plain", "round"}));
    add_name(MEDALLION_NAME);
    set_short("plain round pendant");
    set_long("This is a " + query_short() + " showing you are a Halfling " +
        "of Faerun. It is in the shape of a shield with a cornucopia set in " +
        "the center. The shield is colored green. Around the edge of the " +
        "shield are raised bumps for rivets. The cornucopia is in the shape " +
        "of a ram's horn and overflowing with fruit and corn. Type " +
        "<help halfling> to learn more about the guild.\n");
    add_prop(OBJ_I_NO_DROP,"This is too valuable of an object to lose.\n");
}

public string 
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == on)
        return  "You are wearing the " + query_short() + ", identifing you " +
        "as a Halfling of Faerun.\n";
    else
        return (capitalize(on->query_pronoun()) + " is wearing a " + 
        query_short() + " around their neck, identifying them as Halfling.\n");
}


public void
enter_env(object dest,object old)
{
    remove_name(MEDALLION_NAME);
    if(present(MEDALLION_NAME,E(TO)))
    {
        tell_room(E(TO),"You throw the duplicate pendant away.\n");
        remove_object();
        return;
    }

    add_name(MEDALLION_NAME);

    if(living(E(TO)))
    {
        dest->add_subloc(MEDALLION_NAME, this_object());
    }
}

public void
leave_env(object from, object to)
{
    this_player()->remove_subloc(MEDALLION_NAME);
}

void
init()
{
    ::init();
}

