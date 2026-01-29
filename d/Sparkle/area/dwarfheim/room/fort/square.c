/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <macros.h>

#include "defs.h"

void reset_room();

object beggar;

string
sign()
{
    return "The Royal Palace in Dwarfheim.\n";
}

void
create_room()
{
    set_short("Town square");
    set_long("This is the town square of Dwarfheim. Around you are a lot of\n"+
             "the locals, some of them just walking around for lack of better\n"+
             "things to do, others are shopping or selling various items in\n"+
             "the small sheds that dominate the area. To the east you see\n"+
             "the entrance to an impressive-looking building, with its front\n"+
             "covered by gold and valuable gems. A beautiful silver sign is\n"+
             "placed just above the doors that lead into the building.\n"+
             "North of you is another building, which is obviously the black-\n"+
             "smith's shop.\n");

    add_item("locals", "They seem quite busy.\n");
    add_item("sheds", "They are sealed tight.\n");
    add_item("gold", "It looks real!\n");
    add_item("gems", "They look to be real!\n");
    add_item("building", "It is crafted from the stone within the cave.\n");
    add_prop(ROOM_I_INSIDE,1);
    add_item("doors","These doors are merely a decoration, since the guards\n"+
             "that mostly stand here usually protects the palace, and of\n"+
             "course it never rains inside the mountain.\n");
    add_item("sign","The sign says: The Royal Palace of Dwarfheim.\n");
    add_cmd_item("sign", "read", "@@sign");

    add_exit ("corr5","west");
    add_exit ("palace1","east");
    add_exit ("smith","north","@@block");

    reset_room();
}

int
block()
{
  write("The blacksmith is on vacation. You try to break through the\n"+
        "door with your head, but unfortunately you fail.\n");
  say(QCTNAME(TP)+" bonks "+TP->query_possessive()+" head in the door.\n");
  return 1;
}

void
reset_room()
{
    if(beggar)
        return;

    setuid (); seteuid (getuid ());
    beggar = clone_object(S_LOCAL_NPC_DIR + "beggar");
    beggar->move_living("sdd",TO);
}

