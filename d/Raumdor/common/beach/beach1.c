/* beach room, sarr */

/* 2018-03-08 Malus: This room known to be a teleport location via:
 *      /d/Faerun/guilds/nov/temple/nport.c
 */
#include "defs.h"
inherit BEACH_ROOM;

object board, wall;
void reset_room();

void
create_room()
{
    ::create_room();
    set_short("On the beach off the coast");
    set_long(
      "You are on a beach off the coast. To the west are some docks. To the " +
      "east is stone wall with an archway, leading to a shadowy forest. The " +
      "forest looks very gloomy, like the kind of place in tales of " +
      "terrible monsters.\n");
    add_item(
      ({"docks"}), "Docks lie to the west. They look dreary, but intact.\n");
    add_item(({"forest"}),
      "The forest is dark and foreboding. You sense evil from it.\n");
    add_item("wall", "The wall runs along the beach, north to south, with an " +
      "arch here to the east. It is made of well-aligned stone blocks. " +
      "Looking closely, you can see subtle carvings all over the surface.\n");
    add_item(({"arch","archway"}), "The archway forms a passage through the " +
      "wall, east into the forest. You notice that, like the rest of the " +
      "wall, it is covered in carvings. However, the distribution of the " +
      "carvings is most dense on the archway itself.\n");
    add_item(({"beach"}), "It streaches north and south.\n");
    add_cmd_item(({"wall", "stone wall"}), "climb", "Aside from being too " +
      "tall and smooth to climb, you could just walk through the archway.\n");
    add_exit(BEACH_DIR + "dock2", "west");
    add_exit(BEACH_DIR + "beach2", "north");
    add_exit(BEACH_DIR + "beach3", "south");
    add_exit(FOREST_DIR + "wforest31", "east", "@@brave");
    reset_room();
}

void
reset_room()
{
    if (!board)
    {
        board = clone_object(COMMON_OBJ_DIR + "raumdor_board");
        board->move(this_object(), 1);
    }
}

string
climb_wall()
{
}

int
brave()
{
    if (TP->query_prop(LIVE_I_UNDEAD))
    {
        write("You step under the archway and into the dark forest and feel " +
          "at home. The shadows comfort you, and you feel the presence of " +
          "your kindred.\n");
        return 0;
    }
    else
    {
        write("You step under the archway into the shadowy forest and a " +
          "chill goes up your spine.\n");
        return 0;
    }
}

mixed
query_waypoint_direction(string waypoint)
{
    if (waypoint == "beach")
        return 1;
    if (waypoint == "forest")
        return "east";
    return 0;
}
