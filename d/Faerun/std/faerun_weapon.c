/*
 *  faerun/std/faerun_weapon.c
 *
 *  Standard weapon for the entire Faerun region.
 *
 *  Created by Wully, 12-2-2004
 */

// #include "defs.h"
#include "/d/Faerun/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

inherit "/lib/keep";
inherit "/std/weapon";
inherit FAERUN_ITEM_BASE;

/*
 * Function name: create_faerun_weapon
 * Description  : Constructor, redefine this to configure your weapon
 */
void create_faerun_weapon()
{
	// Redefine this
}

/* 
 * Function name: create_weapon
 * Description  : Constructor, redefined so we can set some default properties
 */
nomask void create_weapon()
{
	// Call the faerun_weapon constructor so that people can configure 
    // the weapon since this function cannot be masked.
	create_faerun_weapon();
    set_keep(0);
}

