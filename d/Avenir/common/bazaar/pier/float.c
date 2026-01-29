/*
 * Filename: /d/Avenir/common/bazaar/pier/float.c
 * Original creator: Ilyian on May 1995
 * Purpose: where the outpost boat will land
 * Last update(s):
 *    Manat on Jul 2000   - changed coding style and stuff
 *                          moved #include below inherit
 *    Achdram 25/01/2005 Added props TERRAIN_ONWATER and
 *                       OBJ_I_CONTAIN_WATER to room.
 * Known bug(s):
 * To-do:
 */
#pragma save_binary
#pragma strict_types
/* added strict_types check because you always want it! Manat on Jul 2000 */

inherit "/std/room";
inherit "/d/Avenir/common/ships/bazaar/pipe.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Avenir/common/bazaar/bazaar.h"
#include <terrain.h>

#define OUTPOST_BOAT_ROOM  "/d/Avenir/common/ships/bazaar/boat_path2.c"

/*
 * Function name: init
 * Description  : Add the commands to the player
 */
public void
init()
{
    ::init();
    /* different verbs to hit metal pipe & summon the boat */
    init_boat_room();
}

/*
 * Function name: create_room
 * Description  : creator function for this room
 */
public void
create_room()
{
    set_short("On the float");
    set_long("You are standing on a very unstable float that sways " +
             "with the currents of the black water. The only thing " +
             "keeping the float in place is a rickety walkway that " +
             "leads up to a pier above. The pier seems to lead east " +
             "to the rest of the island, from where you can hear the " +
             "murmuring of a crowd. A metal pipe pokes up from the water.\n");

    AI( ({ "pier", "dock" }),
       "It is made from strong wood, and is raised up " +
       "from the black water by long poles. This pier seems much too " +
       "high to dock a ship at. To the west, a walkway leads down " +
       "to a large float.\n");
    AI( ({ "float" }),
       "The float seems to be of sturdy construction, it " +
       "is just rather unsteady.\n");
    AI( ({ "water", "sea", "ocean" }),
       "The black sea surrounds you to the west " +
       "for as far as you can see. In the distance to the west, you can " +
       "barely make out the great walls of the cavern that rise up to " +
       "staggering heights, and along the wall is a narrow, winding ledge.\n");
    AI( ({ "walkway "}), "The walkway leads up to the pier.\n");

    AI( ({ "pipe", "metal pipe" }),
          "The hard metal pipe sticks out about two feet from the sea " +
          "surface. It leans over the beach slightly, and you can " +
          "see it disappear underwater at the same angle. Despite the " +
          "hard quality of the metal, the pipe has scratches.\n");
    AI( ({ "scratches", "pipe scratches" }),
       "The scratches are scattered along the length of the pipe.\n");

    AE(BAZAAR + "pier/pier", "up", "@@go_up");

    set_terrain(TERRAIN_ONWATER);

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(OBJ_I_CONTAIN_WATER, 1);
    IN

/*
  set_tell_time (110);
  add_tell ("The float bobs up and down gently.\n");
  add_tell ("The sea around you swirls and churns in strange eddies.\n");
  add_tell ("From the east, you hear the distant call of "
          +"hawkers selling their wares.\n");
  add_tell ("The float tilts dangerously as a small wave washes over it.\n");
*/

  /* link this room to the boats starting room. */
  set_boat_start_room( OUTPOST_BOAT_ROOM );
}

/*
 * Function name: go_up
 * Description  : This function is called when someones goes up.
 * Returns      : 0 - always a success
 */
public int
go_up()
{
    write("You make your way up the rickety walkway.\n" +
          "It sways dangerously.\n");
    return 0;
}

/*
 * Function name: query_docking_msg
 * Description  : message to append onto the end of the boat's short when
 *                boat docks in this room.
 * Returns      : string - the message
 */
public string
query_docking_msg()
{
    return( " drifts into view and bumps against the float.\n" );
}
