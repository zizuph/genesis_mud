/*
 * Smial in Longbottom
 * Finwe, January 2020
 */

#include "/d/Shire/sys/defs.h"
#include "../../defs.h"
#include "/d/Shire/hobbitmaker/hobbitmaker.h"

inherit BASE_SMIAL;

static object hob;
object door;

void
create_smial()
{
    object door, key;

    areaname     = "Longbottom"; /*Name of village*/
    land         = "Southfarthing"; /*Name of land   */
    roomtype     = 4; /*Type of room in the smial   */
    areatype     = "hamlet"; /*Type of village*/
    smialsize    = "large"; /*Size of the house*/

    extraline = "";

    add_exit("5_corridor", "north");


room_add_object(LB_OBJ_DIR + "5_door_kitchen");
//    door = clone_object(LB_OBJ_DIR + "5_door_kitchen");
//    door->move(this_object());
/*
    key = clone_object(LB_OBJ_DIR + "5_door_kitchen");
    key->set_key(5_KEY); // Setting the id number of the key.
    door->set_key(5_KEY); // Tells the door which key fits. 
    key->move(this_object());
*/
       /* This is what is needed for the north door. */


    set_add_walls();
    set_add_ceiling();
    set_add_floor_plain();
    set_wood_panel();
    set_add_kitchen();

    reset_shire_room();
}

void
reset_shire_room()
{
    object other;
/*
    if (!hob)
    {
   	    hob = clone_object(HOBBITMAKER);
   	    hob->set_type(MAIDEN);
	    hob->set_power(140);
   	    hob->move(TO);
    }
*/

    if (door->query_open())
    {
        door->do_close_door("A hobbit comes in and closes the door."); /* If you want a message written put it */
        other->do_close_door("A hobbit comes in and closes the door."); /* between the "" */
    }
    if (!door->query_locked())
    {
        door->do_lock_door("A hobbit locks the door."); /* If you want a message written put it */
        other->do_lock_door("A hobbit locks the door."); /* between the "" */
    }
}
