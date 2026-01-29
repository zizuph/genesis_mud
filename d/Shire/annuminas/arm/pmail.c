/*
 * 2003/12/02 Last update
 * 2011/07/25 Lavellan - Added adjectives
 */


inherit "/std/armour";
inherit "/lib/keep";

#include "/sys/wa_types.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"

create_armour()
{
    set_name("platemail");
    set_adj( ({"heavy", "steel"}));
    set_short("heavy steel platemail");
    set_long("This is a suit of heavy steel platemail. It seems rather "
	    +"nice for a goblin to have, he must have stolen it from "
    	+"someone.\n");
    set_default_armour(28);
    add_prop(OBJ_I_WEIGHT,5500);
    add_prop(OBJ_I_VOLUME,2000);
    set_keep();
}
