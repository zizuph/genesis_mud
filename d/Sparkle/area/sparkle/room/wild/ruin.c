/* 	ruin.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <language.h>
#include <stdproperties.h>

#include "defs.h"

object ogre, compartment;
int open;

void reset_room();

void
create_room()
{
    set_short("Old ruin");
    set_long("\n"+
             "You are standing in the middle of a ruin.\n"+
             "This might once have been a cottage of some kind but all that is left\n"+
             "is the foundation and some of the outer walls. This place shows signs\n"+
             "of recent use. Maybe by some animal.\n");

    add_exit ("field10","north");
    add_exit ("pond",   "west");
    add_exit ("field6", "south");
    add_exit ("field7", "east");

    add_item(({"ruin","cottage" }),
             "There is not much left and not much to see.\n"+
             "");
    add_item(({"wall","walls","foundation","foundations" }),
             "The best kept wall is the west one containing a fireplace\n"+
             "and the chimney.\n"+
             "");
    add_item(({"fireplace","chimney" }),
             "@@fireplace");
    add_item(({"hatch" }),
             "@@hatch");
    add_item(({"ground" }),
             "You find some ogre footprints.\n"+
             "");
    add_item(({"footprint","footprints" }),
             "They seem to be rather fresh.\n"+
             "");

    add_cmd_item( ({ "metal hatch", "hatch" }),
                  "open", "@@open_hatch" );
    add_cmd_item( ({ "metal hatch", "hatch" }),
                  "close", "@@close_hatch" );


    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    compartment = clone_object(S_LOCAL_OBJ_DIR + "compartment");
    compartment->set_no_show();
    compartment->move(TO);

    reset_room();
}

string
fireplace()
{
    TP->add_prop("_obj_i_hatch_found", 1);
    if (open)
        return "An open hatch in the back of the fireplace seems to\n"+
               "reveal a hidden compartment.\n";
    return "There is a small hatch in the back of the fireplace.\n";
}

string
hatch()
{
    TP->add_prop("_obj_i_hatch_found", 1);
    if (open)
        return "It is a small open metal hatch, revealing some kind of\n"+
               "hidden compartment in the back of the fireplace.\n";
    return "It is a small metal hatch. It is closed.\n";
}

int
open_hatch(string str)
{
    if (TP->query_prop("_obj_i_hatch_found") != 1)
    {
        NF("What hatch?\n");
        return 0;
    }
    if (open)
    {
        write("It is already open.\n");
        return 1;
    }
    write("You open the hatch.\n");
    say(QCTNAME(TP) + " does something to the fireplace.\n");
    open = 1;
    compartment->unset_no_show();
    return 1;
}

int
close_hatch(string str)
{
    if (TP->query_prop("_obj_i_hatch_found") != 1)
    {
        NF("What hatch?\n");
        return 0;
    }
    if (!open)
    {
        write("It is already closed.\n");
        return 1;
    }
    write("You close the hatch.\n");
    say(QCTNAME(TP) + " does something to the fireplace.\n");
    open = 0;
    compartment->set_no_show();
    return 1;
}

void
get_gem()
{
    object gem;

    if(!compartment)
        return;

    if(present("gemstone", compartment))
        return;

    gem = clone_object("/std/object");

    gem->set_name("gemstone");
    gem->add_name("gem");
    gem->add_name("jewel");
    gem->set_adj("shining");
    gem->set_long("This little jewel sparkles and shines as you look at it.\n"+
                  "It should bring you a nice price...\n");
    gem->add_prop(OBJ_I_VALUE,	96 + 12 * random(9));
    gem->add_prop(OBJ_I_WEIGHT,	3);
    gem->add_prop(OBJ_I_VOLUME,	1);

    gem->move(compartment);
}

void
reset_room()
{
    int n;

    get_gem();

    if (ogre)
        return;

    ogre = clone_object(S_LOCAL_NPC_DIR + "ogre_mage");
    ogre->arm_me();
    ogre->move_living("apa", TO);
}

