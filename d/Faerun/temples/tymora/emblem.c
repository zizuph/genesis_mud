/*
 * Emblem of a Deity in Faerun
 * -- Finwe, July 2006
 */

#pragma save_binary

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <alignment.h>

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/cmd/std/command_driver";
inherit TYMORA_DIR + "info";

// variables for the emblem and temple
int badge(string s);


string
query_auto_load() { return MASTER + ":"; }

void create_object()
{
    set_name(emblem_name);
    add_name("token");
    add_name(TOKEN_NAME);
    set_adj(adj1);
    set_adj(adj2);
    set_short(adj1 + " " + adj2 + " " + emblem_name);

    set_long("This is a " + short() + " made of " + material + ". " +
        "It identifies you as a follower of " + deity_name + ". On the " +
        "front is the likeness of " + symbol + ". On the back are the " +
        "words 'type <clinfo> for more info'.\n");

    add_prop(OBJ_I_NO_DROP,"This is too valuable of an object to lose.\n");

}

public string
show_subloc(string subloc, object on, object for_obj)
{
  string data;

  if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
  {
    return "";
  }

  if (for_obj == on)
    data = "You are ";
  else
    data = capitalize(environment(this_object())->query_pronoun()) + " is ";

  data+="a follower of " + deity_name + ".\n";

  return data;
}

void
enter_env(object dest,object old)
{
    ::enter_env(dest,old);

    seteuid(getuid());

// check player's alignment. Some clubs have restrictions
// Is deity neutral? It doesn't care about alignment
// deity is good, is the player still?
    if(min_guild >= ALIGN_AGREEABLE)
    {
        if(dest->query_alignment() < min_guild)
        {
            write("\nYour actions have saddened " + deity_name + ". Your " +
                query_short() + " shatters before your eyes as a sign of " +
                "their displeasure towards you.\n\n");
            remove_object();
            return;
        }
    }
// deity is evil, is the player still?
    else if(min_guild <= ALIGN_DISAGREEABLE)
    {
        if(dest->query_alignment() > min_guild)
        {
            write("\nYour actions have angered " + deity_name + ". Your " +
                query_short() + " melts before your eyes as a sign of " +
                "their disdain towards you.\n\n");
            remove_object();
            return;
        }
    }

    add_name(TOKEN_NAME);
    if(living(E(TO)))
        dest->add_subloc(TOKEN_NAME, this_object());
}

public void
leave_env(object from, object to)
{
    this_player()->remove_subloc(TOKEN_NAME);
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
    NF("Crush what? The " + short() + "?\n");
    if(!strlen(s) || !parse_command(s,TO,"[away] [the] ["+ adj1 + "] ["+ adj2 + "] '"+ emblem_name + "'"))
        return 0;
    else
    {
        TP->catch_msg("You crush the " +short()+ ". It is reduced to " +
            "powder and blows away.\n");
        say(QCTNAME(TP)+ " crushes the " +short()+ ". It is reduced to " +
            "powder and blows away.\n");
//        set_alarm(4.5, 0.0, &badge());
        LOG_FILE("temples", "left " + deity_name);
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
    write("This " + short() + " designates you as a follower of " +
        deity_name + ". You can only be a follower " +
        "of one deity. If at anytime you decide to no longer follow " +
        deity_name + ", you may 'crush " + emblem_name + ".\n");
    return 1;
}
