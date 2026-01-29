/* CALIA : ROOM - Valkira's Room (/d/Calia/valkira/rooms/valsroom.c)
Date      Coder      Action 	  Note/Purpose
-------- ----------- -----------  --------------------
9/09/99   Valkira    Modified     Arch exit 
9/05/99   Valkira    Modified	  Added @@pulltape (action to green box)
8/17/99   Valkira    Created	  Pratice coding, To create a room of my own */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";                   /* standard room                    */
inherit "/d/Calia/std/room_tell_room"; /* Used for room tell routines      */

#include "/d/Calia/domain.h"           /* Default include file for  
                                          Calia Domain                      */
#include <stdproperties.h>             /* ( /sys/stdproperties.h ) This file
                                          holds definition of all the standard
                                          properties that an object can have.
                                          The documentation for the properties
                                          can all be found in the directory
                                           /doc/man/properties              */
#include <macros.h>                    /* ( /sys/macros.h) This file contains
                                          various useful macros.            */
#include <ss_types.h>                  /* ( /sys/ss_types.h) This file 
                                          defines the available stats and 
                                          skills. Use this file in conjunction
                                          with query_stat() and query_skill()
                                          calls.                            */

#define ROOMS              "/d/Calia/valkira/rooms/"
#define TP this_player()
#define TO this_object()

void
create_room()
{
    object box;
    object door;

    /* DESCRIPTION */

    set_short("Valkira's Workroom");

    set_long("This is Valkira's 'Room of Her Own'. There is a front" +
        " door, which opens into a garden. Next to the door is a" +
        " window, from where a cooling breeze drifts through the room." +
        " Through an archway you see a small room. Looking around," +
        " you find yourself in the midst of a great number of" +
        " unopened boxes.  What a mess!\n");


    /* ITEMS */

    add_item(({"box","boxes"}),
        " The boxes are all shapes and sizes. The green one looks" +
        " particularly interesting.\n");

    add_item(("green box"), "It's a green box with tape wrapped around." +
             " The tape looks as if it could be pulled loose. \n");

    add_item("tape",
       "You wonder what would happen if you pull the tape.\n");

    add_cmd_item("tape","pull", "@@pull_tape");

    add_item(({"garden","garden door"}),
        " The door is open.  In fact, it appears the door was" +
        " taken off it's hinges. Perhaps in order to get the boxes" +
        " into the room? The garden looks inviting.\n");

    add_item(("archway"), "This door leads to a small room.\n");

    add_item(("window"),"The window is framed by bright yellow curtains." +
        " It gives a splendid view of the garden.\n");

    add_item(("view"), "This garden is quiet and peaceful.  A gardenia" +
        " bush in full bloom sits beneath the open window.\n");
    
    set_tell_time(100);
                
    add_tell("A slight breeze touches your cheek.\n");
    add_tell("The smell of gardenia drifts from the window.\n");
    add_tell("The curtains flutter in the breeze.\n");

    door=clone_object(ROOMS+"gdoorout.c"); /* door to garden */
    door->move(this_object());

    add_exit("/d/Calia/valkira/rooms/valsgarden", "garden");
    add_exit("/d/Calia/valkira/workroom", "arch");

    
//    reset_room();
}
int pull_tape() {
   write("You pull the tape, and it lifts easily from the box.\n");
   tell_room(TO,QCTNAME(TP)+" pulls the tape.  It lifts easily from" +
       " the box.\n",TP);
   tell_room(TO,"A loud voice, sounding somewhat like your mother, reminds" +
       " everyone that 'If it is not yours, leave it alone!'\n");
   return 1;
}


 
