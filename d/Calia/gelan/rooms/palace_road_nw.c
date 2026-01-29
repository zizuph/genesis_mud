/* 	this is a room of the town Gelan

    coder(s):   Merlin, Deinonychus & Maniac

    history:
                24/8/95     description modified            Maniac
                17.07.94    descriptions                    Deinonychus
                18. 2.93    path system                     Merlin
                17. 1.93    new guard system                Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 2. 1.92    slight modifications            Merlin
                28.12.92    slight mod                      Merlin
                22.12.92    installed clean_up              Merlin
                21.12.92    descs                           Merlin
                21.12.92    installed door                  Merlin
                 3.11.92    created                         Merlin
                 6.11.92    installed help system           Merlin

    purpose:    road into town
    exits:      n-nw-ne to square, west to stables, e-se-s to palace road

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


#pragma save_binary

#include "defs.h"
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
#include GUARD_INCLUDE

inherit GELAN_BASE_ROOM;

object door;                                    /* door in room */

public void
create_gelan_room()
{
    /* doors */

    door = clone_object(GELAN_DOORS + "palace_road_nw");
    door->move(this_object());

    /* descriptions */

    set_short("Palace road north west");
    set_long("You're standing on northwestern end of the palace road, "
          + "and can see the town square open out to your north. " 
          + "To your west you see the bottom of a row of "
          + "huge columns that flank the road, creating a "
          + "corridor effect. They look so high that you can't "
          + "even see their tops! Behind the columns is one of the "
          + "stables of Gelan. "
          + "The palace road continues southwards, where it leads "
          + "to the drawbridge. The road is also wide, extending eastwards "
          + "up to the columns that flank the other side of the gate. " 
          + "You see a map on the wall here.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "square_southend_center_w","north",0);
    add_exit(GELAN_ROOMS + "palace_road_sw","south",0);
    add_exit(GELAN_ROOMS + "palace_road_ne","east",0);
    add_exit(GELAN_ROOMS + "square_southend_w","northwest",0);
    add_exit(GELAN_ROOMS + "square_southend_center_e","northeast",0);
    add_exit(GELAN_ROOMS + "palace_road_se","southeast",0);

    /* items in the room */

    add_item(({"road","floor","ground"}), DESC("floor"));
    add_item(({"town","gelan","Gelan"}), DESC("gelan"));
    add_item(({"armoury", "armouries","house","building"}),
      DESC("armoury_house"));
    add_item("entrance", DESC("armoury_entrance"));
    add_item("sign", DESC("armoury_sign"));
    add_item(({"column","columns"}), DESC("gate_columns"));
    add_item("gate", DESC("gate"));
    add_item("square", DESC("square_far"));
    add_item("statue", DESC("fountain_statue_far"));
    add_item("marble", DESC("marble"));
    add_item(({"map","plan"}),
    "This is a map of Gelan:     Legend:\n\n" +
    "         |-|  |---|\n" +
    "   \\     |#|  |  %|   / /   Roads:                 Official Buildings:\n" +
    "  \\ \\    |-|  |-| |  / /     1) Palace Road         @) Stable of Gelan\n" +
    "   \\ \\/\\ |c|  |C|-/\\/ /      2) Calia Street        #) Guards Armoury\n" +
    "    \\ \\D\\|-| 5|-|/!/ /       3) Maple Street        %) Guards Headquarters\n" +
    "    /\\6\\/        \\/4/\\       4) Parliament Street   !) Jail\n" +
    "    \\d\\            / /       5) Castle Road\n" +
    "     \\/     $$     \\/        6) High Street\n" +
    "   ---              ---      7) Surgery Street\n" +
    "   |e|              |B|\n" +
    "------              -----   Commerce:              Special Points:\n" +
    "    7               3        a) McCroissant bakery  $) Pillory of Gelan\n" +
    "------              -----    b) Angora Hairdresser  +) Fountain of Gelan\n" +
    "   |E|      ++      |b|      c) Brandybug Inn       &) Gate of Gelan\n" +
    "   ---     ++++     ---      d) Goldiloon Alchemy\n" +
    "     /\\     ++     /\\        e) Miser Shop          *) your position\n" +
    "    /f/            \\A\\       f) Hammerhead Smithy\n" +
    "    \\/ /\\        /\\2\\/       g) Tomati Empire\n" +
    "    / /g/|-|*1|-|\\a\\ \\ \n" +
    "   / /\\/ |@|  |@| \\/\\ \\     Public Buildings:\n" +
    "  / /    |-|  |-|    \\ \\     A) public lavatory\n" +
    " / /     |#|  |#|     \\ \\    B) Public School of Gelan\n" +
    "  /      |-|  |-|      \\     C) Tourist Office\n" +
    "           |  |              D) Post Office of Gelan\n" +
    "           |&|-              E) Bank of Calia, Gelan branch \n" +
    "           | |\n\n");


} /* create_room */

/*
 * Function name: clean_up
 * Description:   called for clean up
 * Arguments:     none
 * Returns:       none
 */

void
clean_up()
{

    door->remove_door_info(this_object());
    door->destruct();

    ::clean_up();

}

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
