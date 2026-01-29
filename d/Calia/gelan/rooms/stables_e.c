
/* 	
    This is a room of the town Gelan

    coder(s):   Merlin

    history:     22/4/96    took out call_out               Maniac 
                  7.9.94    provisional description added   Maniac
                21. 2.93    path system                     Merlin
                17. 1.93    new guard system                Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 3.11.92    created                         Merlin
                 6.11.92    installed help system           Merlin
                21.12.92    installed door                  Merlin
                22.12.92    installed clean_up              Merlin

    purpose:    keep horses and this stuff here
    exits:      east to palace road

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


#pragma save_binary

inherit "/std/room";
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
#include GUARD_INCLUDE

object door;                       /* pointer to door in room */

create_room()
{

    /* doors */

    door = clone_object(GELAN_DOORS + "stables_e");
    door->move(this_object());

    /* descriptions */

    set_short("Stables east");
    set_long("You are inside the east stables of Gelan. There are a " +
             "number of stalls here, where the horses are usually " +
             "kept. The floor is swept clean indicating that the " +
             "place is well maintained. Only the faintest smell of " +
             "hay and horse dung is in the air. Bales of hay are " +
             "stacked in one corner of the stable.\n"); 

    /* properties */

    add_prop(ROOM_I_INSIDE, 1);		/* this room is inside */
    add_prop(ROOM_S_MAP_FILE, "gelan_map.txt");

    /* items in the room */
    add_item("floor", "The floor is swept very clean, as stables go " +
                      "at least.\n");

    add_item(({ "stall", "stalls" }), "There are a number of stalls " +
               "here to keep the horses in. Their walls are high and " +
               "painted green.\n");

    add_item(({ "bales", "hay" }), "Bales of hay are stacked in one " +
              "corner of the stable, food for the horses no doubt.\n");

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
