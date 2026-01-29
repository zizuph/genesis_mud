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

//inherit P_UPPERDARK_STD + "wep";
//inherit "/d/Faerun/underdark/std/wep";
inherit UNDER_STD_DIR + "wep";


/*
 * Function name: create_menzo_weapon
 * Description  : Construct a weapon for Menzoberranzan
 */
void create_menzo_weapon()
{
}

/*
 * Function name: create_underdark_weapon
 * Description  : Construct a weapon for the underdark
 */
nomask void create_upperdark_weapon()
{
	// Set defaults
	set_faerun_area("menzoberranzan");

	// Call the constructor
	create_menzo_weapon();
}
