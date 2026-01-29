/*
 * Smial in Longbottom
 * Finwe, January 2020
 */

#include "/d/Shire/sys/defs.h"
#include "../../defs.h"
#include "/d/Shire/hobbitmaker/hobbitmaker.h"

inherit BASE_SMIAL;

static object hob;

void
create_smial()
{
    areaname     = "Longbottom"; /*Name of village*/
    land         = "Southfarthing"; /*Name of land   */
    roomtype     = 2; /*Type of room in the smial   */
    areatype     = "hamlet"; /*Type of village*/
    smialsize    = "large"; /*Size of the house*/

    extraline = "";

    add_exit("1_kitchen", "north");
    add_exit("1_front", "east");
    add_exit("1_dining", "west");


    set_add_walls();
    set_add_ceiling();
    set_add_floor_rug();
    set_wood_panel();
    set_add_parlor();

    reset_shire_room();
}

void
reset_shire_room()
{
//    object other;

    if (!hob)
    {
   	    hob = clone_object(HOBBITMAKER);
   	    hob->set_type(MAIDEN);
	    hob->set_power(140);
   	    hob->move(TO);
    }

/*
    if (door->query_open())
    {
        door->do_close_door("A hobbit comes in and closes the door."); 
        other->do_close_door("A hobbit comes in and closes the door."); 
    }
    if (!door->query_locked())
    {
        door->do_lock_door("A hobbit locks the door."); 
        other->do_lock_door("A hobbit locks the door."); 
    }
*/
}
