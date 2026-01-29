/*
 *  faerun/underdark/upper/menzo/std/menzo_drow.c
 *
 *  Standard drow for Menzoberranzan and surroundings
 *
 *  Created by Wully, 12-2-2004
 */

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit (UNDER_STD_DIR + "drow");

/*
 * Function name: create_menzo_drow
 * Description  : Construct a drow for Menzoberranzan
 */
void create_menzo_drow()
{
}

/*
 * Function name: create_underdark_drow
 * Description  : Construct a drow for the underdark
 */
nomask void create_upperdark_drow()
{
	// Set defaults
	set_faerun_area("menzoberranzan");

	// Call the constructor
	create_menzo_drow();
}
