/*
 *  faerun/underdark/upper/menzo/std/menzo_armour.c
 *
 *  Standard armour for Menzoberranzan and surroundings
 *
 *  Created by Wully, 12-2-2004
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit (UNDER_STD_DIR + "arm");

/*
 * Function name: create_menzo_armour
 * Description  : Construct a armour for Menzoberranzan
 */
void create_menzo_armour()
{
}

/*
 * Function name: create_underdark_armour
 * Description  : Construct a armour for the underdark
 */
nomask void create_upperdark_armour()
{
	// Set defaults
	set_faerun_area("menzoberranzan");

	// Call the constructor
	create_menzo_armour();
}
