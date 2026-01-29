/*
 * Smial in Longbottom
 * Finwe, January 2020
 */

#include "/d/Shire/sys/defs.h"
#include "../../defs.h"
#include "/d/Shire/hobbitmaker/hobbitmaker.h"

inherit BASE_SMIAL;
inherit BASE_COMMON;

static object hob;
object door;

void
create_smial()
{
    object door, key;

   areaname     = "Longbottom"; /*Name of village*/
   land         = "Southfarthing"; /*Name of land   */
   roomtype     = 9; /*Type of room in the smial   */
   areatype     = "hamlet"; /*Type of village*/
   smialsize    = "large"; /*Size of the house*/

    extraline = "";

//    door = clone_object(LB_OBJ_DIR + "5_door_cellar");
//    door->move(this_object());

    room_add_object(LB_OBJ_DIR + "5_door_cellar");

    set_add_walls();
    set_add_ceiling();
    set_add_floor_plain();
    set_wood_panel();

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
}
