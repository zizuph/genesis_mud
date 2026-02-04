inherit "/std/room.c";

/*  A game room.  Some simople games may be added soon
 *
 *  Coded by Vader on 10/26/92
 *
 */
#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"

create_room()
{
   object door;
   set_short("game room");
   set_long(break_string(
    "The Avenchirs used to spend loads of time using this room.  Games " +
    "are very important to help keep sanity in these trying times.  " +
    "Spread out in this large room are a pool table, a large, jade chess " +
    "board, a backgammon set, and a shuffleboard table.  There is also a " +
    "large collection of papers here, probably telling the rules of some " +
    "game created by one of the Avenchirs.\n", 70));

   add_item(({"games", "pool", "pool table", "chess", "chess board", 
              "backgammon", "backgammon set", "shuffleboard", 
              "shuffleboard table"}), break_string(
              "Despite the run down condition of this room, these games " +
              "seem remarkably well cared for, while still relatively used" +
              ".\n", 70));

   add_exit(MANSION + "wing_s2", "south", 0);
   add_prop(ROOM_I_INSIDE, 1);

    add_item(({"rules", "papers", "paper", "instructions"}),
              break_string("The instructions for the games " +
              "have become all mixed up over the years. You " +
              "can not understand how to play any of " +
              "the games in this room!\n", 70));
    add_cmd_item(({"rules", "papers", "paper", "instructions"}),
         "sort", break_string("As start to sort the papers and " +
         "intructions.  You quickly realise this is fruitless " +
        "due to the large number of intructions mixed up here.\n", 70));
   door = clone_object(MANSION + "crt/gard_door1");
   door->move(this_object());
}
