/*
 * Emblem of a Deity in Faerun
 * -- Finwe, July 2006
 */

#pragma save_binary
// domain defs file. Always include this with every file.
#include "/d/Faerun/defs.h"


// standard definitions for the file
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>

// this inherits code for objects
inherit "/std/object";
// this makes the object wearable over armours
inherit "/lib/wearable_item";
// sets up routines for the object
inherit "/cmd/std/command_driver";
// this file contains information about the object, ie adjective descrptions.
inherit "/d/Faerun/temples/myrkul/info.c";

// variables for the emblem and temple
#define TOKEN_NAME  "_temple_token"
int badge(string s);

// makes the object reload when the player logs back in
query_auto_load()
{
  return MASTER;
}

// creates the object
void create_object()
{
// sets the names, adjectives, and descriptions of the object. they are
// defined in /d/Faerun/temples/myrkul/info.c
    set_name(emblem_name);
    add_name("token");
    add_name(TOKEN_NAME);
    set_adj(adj1);
    set_adj(adj2);
    set_short(adj1 + " " + adj2 + " " + emblem_name);
    set_long("This is a " + short() + " made of " + material + ". It " +
        "identifies you as a member of the " + cult_type + " of " + 
        deity_name + ". On the front is the likeness of " + symbol + 
        ". On the back are the words 'type <clinfo> for more info'.\n");
// this prop prevents the object from being dropped
    add_prop(OBJ_I_NO_DROP,"This is too valuable of an object to lose.\n");

}

// this routine sets up what the mortals see when the wearer is examined.
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

  data+="a follower of the " + cult_type + " of " + deity_name + ".\n";

  return data;
}

// what happens when a mortal buys or gets more than one emblem, or 
// enters their inventory.
enter_env(object dest,object old)
{
  remove_name(TOKEN_NAME);
// if you have one already, do this
  if(present(TOKEN_NAME,E(TO)))
    {
        write("You can only worship one deity.\n");
        tell_room(E(TO),"The duplicate " + short() + " explodes before you.\n");
        remove_object();
        return;
    }
// log the action
    LOG_FILE("temples", "joined " + deity_name);

    add_name(TOKEN_NAME);
    if(living(E(TO)))
        dest->add_subloc(TOKEN_NAME, this_object());
}

// when they get rid of the object, remove it from the inventory.
public void
leave_env(object from, object to)
{
  this_player()->remove_subloc(TOKEN_NAME);
}

// commands that can be done with the object
init()
{
    ::init();
    add_action("badge", "crush");
    add_action("help", "clinfo");
}

// routine to leave the club
int
badge(string s)
{
    NF("Crush what? The " + short() + "?\n");
    if(!strlen(s) || !parse_command(s,TO,"[away] [the] ["+ adj1 + "] ["+ adj2 + "] '"+ emblem_name + "'"))
        return 0;
    else
    {
        TP->catch_msg("You crush the " +short()+ ". It is reduced to " +
            "powder, which blows away.\n");
        say(QCTNAME(TP)+ " crushes the " +short()+ ". It is reduced to " +
            "powder, which blows away.\n");
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
    write("This " + short() + " designates you as a follower of the " +
        cult_type + " of " + deity_name + ". You can only be a follower " +
        "of one deity. If at anytime you decide to no longer follow " + 
        deity_name + ", you may 'crush " + emblem_name + ".\n");
    return 1;
}
