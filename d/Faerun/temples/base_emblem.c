/*
 * Emblem of a Deity in Faerun
 * -- Finwe, July 2006
 */

#pragma save_binary

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/cmd/std/command_driver";
inherit "/d/Faerun/temples/default_info.c";


// variables for the emblem and temple


int badge(string s);

void create_badge()
{
}

query_auto_load()
{
  return MASTER;
}

void create_object()
{
    set_name(emblem_name);
    add_name("token");
    add_name("emblem");
//    add_name(god_token);
    add_name(TOKEN_NAME);
    set_adj(adj1);
    set_adj(adj2);
    set_short(adj1 + " " + adj2 + " " + emblem_name);
    set_long("This is a " + short() + " made of " + material + ". " +
        "It identifies you as a follower of " + deity_name + ". On the " +
        "front is the likeness of " + symbol + ". On the back are the " +
        "words 'type <clinfo> for more info'.\n");

    add_prop(OBJ_I_NO_DROP,"This is too valuable of an object to lose.\n");
    create_badge();

}



init()
{
    ::init();
    add_action("badge", "crush");
    add_action("help", "clinfo");
}

int
badge(string s)
{
    NF("Crush what? The " + query_short() + "?\n");
    if(!strlen(s) || !parse_command(s,TO,"[away] [the] ["+ adj1 + "] ["+ adj2 + "] '"+ emblem_name + "'"))
        return 0;
    else
    {
        TP->catch_msg("You crush the " +query_short()+ ". It is reduced to " +
            "powder and blows away.\n");
        say(QCTNAME(TP)+ " crushes a " +query_short()+ ". It is reduced to " +
            "powder and blows away.\n");
//        set_alarm(4.5, 0.0, &badge());
        remove_object();
        return 1;
    }
}



/*******************************************************************************
 * Emotes
 ******************************************************************************/

int
help()
{
    write("This " + short() + " designates you as a follower of the " +
        cult_type + " of " + deity_name + ". You can only be a follower " +
        "of one deity. If your alignment changes from that of " +
        deity_name + ", you will be removed as a follower. If at anytime " +
        "you decide to no longer follow this deity, you may <crush " +
        emblem_name + ">'.\n");
    return 1;
}
