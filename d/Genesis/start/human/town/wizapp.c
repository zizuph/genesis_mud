
/* 

   /d/Genesis/start/human/town/wizapp

   Place where mortals post a note to apply for wizhood. 

   Coded by ? 

   Modified, Maniac, 5/4/97

*/ 

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#define WIZAPP_BOARD "/w/postmaster/private/arch_boards/wizapp"

#include "../defs.h"

void
create_room() 
{
    set_short("In the wizard application room");
    set_long("\nThis is the wizardhood application room. There is a board " +
      "here that you can use for writing your application. It can only be " +
      "read by the Administration, Lieges and Stewards of Genesis, not by " +
      "other wizards or mortal players.\n\n" +
      "This note is your big chance for wizardhood, so you must consider " +
      "your words carefully and pay extra attention to the writing. " +
      "Specify who you are and _why_ you want to become a wizard. " + 
      "You should list the domain(s) you are interested in, the liege " +
      "who backs you (if any, this can come later), and _all_ of your " +
      "seconds. Any " +
      "previous coding merits are not of great importance here, what " +
      "is desired is ingenuity and imagination rather than coding " +
      "proficiency. We can teach you to code, we cannot teach you to " +
      "think. Please ensure you have read <help wizapp> and <help " +
      "wizhood>.\n\n");

    add_exit(TOWN_DIR + "tower", "west");

    add_prop(ROOM_S_MAP_FILE, "tower_map.txt");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK, "This is a room for writing, " +
      "not fighting.\n");
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    clone_object(WIZAPP_BOARD)->move(TO);
}


