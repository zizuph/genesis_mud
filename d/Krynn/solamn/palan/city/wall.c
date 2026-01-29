/* created by Aridor 12/14/93 */

#include "../local.h"

inherit ROOM_BASE

#include <macros.h>
#ifdef CITYCLOSED
#define OUT_WALL      ROOM + "closedcity"
#else
#define OUT_WALL      ROOM + "street18"
#endif

#define LIMIT         30 /*time length where you can push button*/

void
create_palan_room()
{
    set_short("Inside the city wall");
    set_long("@@my_long");

    add_exit(ROOM + "pipe1","down",0,0);

    add_item(({"wall","city wall"}),
         "The city wall surrounds the entire city, except at the " +
         "harbour to the north. It is made of big and small stone " +
         "blocks.\n");
    add_item(({"stone blocks","blocks","stones","stone","block"}),
         "They look like ordinary stone blocks, some of them are big, " +
         "others are small.\n");
    add_item(({"big stone blocks","big stone block","big stone",
         "big block","big blocks","big stones"}),
         "Some of the blocks are really big and heavy. On the east wall " +
         "you notice a small button set into one of the big stones.\n");
    add_item(({"small stone blocks","small stone block","small stone",
         "small block","small blocks","small stones"}),
         "These small stones are used to fill the spaces between the " +
         "big blocks. You notice that one of the small stones in the " +
         "west wall seems loose.\n");
    add_item(({"shaft"}),
         "It's a shaft leading down, there is a ladder there so you " +
         "won't fall.\n");
    add_item(({"hole"}), "@@examine_the_hole@@");
    add_item(({"small button","button"}),
         "It's just a normal button set into the stone.\n");

    add_cmd_item(({"small stone"}),({"pry","get","push","press"}),
         "@@open@@");
    add_cmd_item(({"hole"}),({"enter"}),
         "@@go_out_of_the_wall@@");
    add_cmd_item(({"button","small button"}),({"press","push"}),
         "@@fall_out_east_wall@@");

    DARK;
}

string
my_long()
{
#ifdef CITYCLOSED
    return "This is inside the city wall of Palanthas, you somehow "
      +"feel extreemly close to intense magic!!!\n";
#endif
    return ("This is the inside of the city wall of Palanthas. " +
        (((OUT_WALL)->query_door_open()) ?
         "There is a hole in the wall to your west." : "") +
        " A dim shimmering light comes up from the shaft that " +
        "ends in the middle of the room.\n");
}

string
open()
{
#ifndef CITYCLOSED
    (OUT_WALL)->secret_door_opens();
#endif
    if (member_array("west",query_exit_cmds()) == -1)
      add_exit(OUT_WALL,"west");
    return "";
}

string
go_out_of_the_wall()
{
#ifndef CITYCLOSED
    if (!(OUT_WALL)->query_door_open())
      {
      write("What?\n");
      return "";
      }
#endif
    write("You enter the hole and find yourself on the streets of " +
      "Palanthas.\n");
    TP->move_living("into the hole",(OUT_WALL), 1, 0);
    return "";
}


string
examine_the_hole()
{
#ifdef CITYCLOSED
    return "You stare into the art of creation, beware!\n";
#else
    if ((OUT_WALL)->query_door_open())

    return ("It's a hole out of the room. It is very bright outside. " +
        "You think it's large enough that you can fit through.\n");
    else
      return "You find no hole.\n";
#endif
}

string
fall_out_east_wall()
{
    int i = TP->query_prop("_player_i_has_touched_gems");
    TP->remove_prop("_player_i_has_touched_gems");
    if (i + LIMIT < time())
      return "You " + query_verb() + " the button. Something is missing, though. You feel you forgot to do something beforehand. Something about gems?????\n";
    write("You push the button, and pressing against the wall you suddenly " +
      "fall forward into some brambles.\n");
    TP->move_living("through the east wall",(THIEF_ENTRANCE), 1, 0);
    return "";
}
