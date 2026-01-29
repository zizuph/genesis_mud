/*
 *  faerun/underdark/upper/menzo/std/menzo_weapon.c
 *
 *  Standard weapon for Menzoberranzan and surroundings
 *
 *  Created by Wully, 12-2-2004
 *
 */
#include "/d/Faerun/defs.h"
#include "defs.h"

inherit FAERUN_WEP_BASE;

/*
 * Function name: create_menzo_weapon
 * Description  : Construct a weapon for Menzoberranzan
 */

/*
 * Function name: create_underdark_weapon
 * Description  : Construct a weapon for the underdark
 */
nomask void create_faerun_weapon()
{
	// Set defaults
	set_faerun_area("menzoberranzan");

}
