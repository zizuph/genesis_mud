/*
 *  faerun/std/faerun_armour.c
 *
 *  Standard armour for the entire Faerun region.
 *
 *  Created by Wully, 12-2-2004
 */

#include "/d/Faerun/defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>


inherit "/lib/keep";
inherit "/std/armour";
inherit FAERUN_ITEM_BASE;

/*
 * Function name: create_faerun_armour
 * Description  : Constructor, redefine this to configure your armour
 */
void create_faerun_armour()
{
	// Redefine this
}

/* 
 * Function name: create_armour
 * Description  : Constructor, redefined so we can set some default properties
 */
nomask void create_armour()
{
	// Call the faerun_armour constructor so that people can configure the armour
	// since this function cannot be masked.
	create_faerun_armour();
    set_keep(0);

//     set_default_armour(query_ac(), query_at(), 0, 0);

}

