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
   roomtype     = 5; /*Type of room in the smial   */
   areatype     = "hamlet"; /*Type of village*/
   smialsize    = "large"; /*Size of the house*/

    extraline = "";

    add_exit("3_front", "south");

    set_add_master();

    set_add_walls();
    set_add_ceiling();
    set_add_floor_rug();
    set_wood_panel();
    set_add_master();

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
