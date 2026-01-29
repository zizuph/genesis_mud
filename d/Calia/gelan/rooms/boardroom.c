
/* 
 * A room in the town of Gelan where the board is kept.
 * No npcs may enter so it doesn't have to be in the town room mappings.
 *
 * Maniac 7/9/94
 *
 * Revised, Maniac, 28/11/98
 */

#pragma save_binary

#include "defs.h"
#include <stdproperties.h>
#include "room.h"

inherit GELAN_BASE_ROOM;

/*
 * Prototypes
 */
void    load_board();
void    load_poster();

public void
create_gelan_room()
{
    set_short("In the Gelan board room");
    set_long(
        "You are standing in the room where the public board of Gelan is. "
      + "Here travellers visiting Gelan may post notes to discuss matters "
      + "relating to the town. There is a prominent sign hanging on the " 
      + "wall. Around the room are desks with quills and ink perched on " 
      + "them. To the east you see the inside of the great gate of " 
      + "Gelan.\n");
 
    add_exit(GELAN_ROOMS + "gate", "east", 0);

    add_prop(ROOM_I_INSIDE, 1);
  
    add_item(({ "desk", "desks" }), "There are many writing desks " +
             "here, neatly spaced, and on each of them is placed " +
             "a quill, ink, and note writing paper.\n");

    add_item(({ "wall", "walls" }), "There is a sign on one wall.\n");

    add_item("sign", "The sign hanging on the wall reads in gold " 
                   + "letters: 'QUIET PLEASE!'\n");
    add_cmd_item("sign", "read", "The sign hanging on the wall reads " 
                   + "in gold letters: 'QUIET PLEASE!'\n");
    load_board();
    load_poster();
}


/* function to load the board to the room */
void
load_board()
{
    object bb;

    seteuid(getuid(this_object()));

    bb = clone_object(GELAN_OBJECTS + "board");
    bb->move(this_object());
}


/* function to load the board to the room */
void
load_poster()
{
    object bp;

    seteuid(getuid(this_object()));

    bp = clone_object(GELAN_OBJECTS + "bright_poster");
    bp->move(this_object());
}

