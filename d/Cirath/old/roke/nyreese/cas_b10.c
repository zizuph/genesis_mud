/*
 * cas_b10.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Gres  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>

object knight, spirit;
int key_is_here;

void reset_room();

void
create_room()
{

    set_short("Office of the Lords");
    set_long("You are standing in what used to be the office of the " +
             "Warlords of Nyreese. As you study the charts and " +
             "documents in the room you feel very happy that the " +
             "warlords were eaten by one of the dragons. " +
             "In the middle of the room is a rather large oak desk, which " +
             "looks a little interesting.\n");

    add_exit("cas_b6", "north");

    add_item(({"map", "chart", "maps", "charts"}),
             "The charts are scattered all over the room. They were " +
             "used to prepare for battles and wars.\n");

    add_item("desk",
             "The desk is very old, and is made of oak. It has several drawers.\n");
    add_item(({"drawer", "drawers"}), 
             "The drawers are full of papers and various items.\n");

    add_prop(OBJ_S_SEARCH_FUN, "desk_search");

    reset_room();
}

string
desk_search(object who, string s)
{
    string gunk;

    if (parse_command(s, TO, "'drawer' / 'drawers' / 'desk' %s", gunk))
    {
        if (key_is_here)
        {
            clone_object(ROKEDIR + "obj/key")->move(who);
            say(QCTNAME(who) + " found something in the desk.\n");
            key_is_here = 0;
            return "You found a key in the desk!\n";

        }
        else
            return "You find nothing in the desk.\n";
    }
    else
        return "";
}

void
reset_room()
{
    key_is_here = 1;

    if (knight)
        return;

    knight = clone_object(ROKEDIR + "npc/knights");
    knight->equip_me();
    knight->move(TO);
}
