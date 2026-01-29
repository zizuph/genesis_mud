/*
 * doggystick.c
 *
 * Used in npc/boy.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "defs.h"
#include <cmdparse.h>
#include <macros.h>
#include <composite.h>

object *victims;

void
create_object()
{
    set_short("wooden stick");
    set_name("stick");
    set_adj("wooden");
    add_name("doggystick");

    set_long("This is a wooden stick. When you examine it closer, you " +
             "notice some bite-marks in it.\n");

    add_prop(OBJ_S_WIZINFO, "This is a doggy stick. Spit on it, show it " +
             "to someone, throw it to the next room and say 'apport'. " +
             "Very funny indeed!.\n");
 
    victims=({});
}

int
throw(string s)
{
    string dir;
    string *exits;
    int index;
    object apport;

    NF("Throw what where?\n");
    if (!s || s == "")
        return 0;
    if(!parse_command(s, TP, "'stick' %w", dir))
        return 0;

    exits = ENV(TP)->query_exit();
    index = member_array(dir, exits);
  
    NF("You can't throw anything in that direction.\n");
    if(index < 1)
        return 0;

    if(exits[index+1] != 0)
        return 0;

    move(exits[index-1]);
    tell_room(exits[index-1], "Someone throws a stick into the room.\n");
    TP->catch_msg("You throw the stick " + dir + ".\n");
    say(QTNAME(TP) + " throws a stick " + dir + ".\n");

    seteuid(getuid(TO));
    apport = clone_object(ROKEDIR + "obj/apport");
    apport->move(TP);
    apport->set_owner(TP);
    apport->set_victims(victims);
    apport->set_dir(dir);
    victims=({});
    dir="";
  
    return 1;
}

mixed
show(string s)
{ 
    NF("Show what to whom?\n");
    if (!s || s == "")
        return 0;

    if (s == "stick" || s == "stick to everyone")
        s = "stick to all";

    if (!parse_command(s, ENV(TP), "'stick' 'to' %l", victims))
        return 0;

    victims -= ({TP});
    victims = exclude_array(victims, 0, 0);

    TP->catch_msg("You show the stick to " + COMPOSITE_LIVE(victims) + ".\n");
    victims->catch_msg(QCTNAME(TP) + " holds a stick under your nose.\n");
  
    return 1;
}
  
void
init()
{
    add_action(throw, "throw");
    add_action(show, "show");
}
