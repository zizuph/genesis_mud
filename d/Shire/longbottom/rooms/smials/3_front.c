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
   roomtype     = 1; /*Type of room in the smial   */
   areatype     = "hamlet"; /*Type of village*/
   smialsize    = "large"; /*Size of the house*/

    extraline = "Some hooks line the wall. A large bedroom is to the " +
        "north, and a kitchen is to the west.";

    add_exit(LB_RM_DIR + "lb03", "out");
    add_exit("3_master", "north");
    add_exit("3_kitchen", "west");

    set_add_front_hall(); 

    set_add_door("green");
    set_add_walls();
    set_add_ceiling();
    set_add_floor_plain();
    set_wood_panel();

   reset_shire_room();
}

void
reset_shire_room()
{
    if (!hob)
    {
   	    hob = clone_object(HOBBITMAKER);
   	    hob->set_type(CITIZEN);
	    hob->set_power(140);
   	    hob->move(TO);
    }
}
