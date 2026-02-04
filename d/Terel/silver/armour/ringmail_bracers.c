/* File         : /d/Terel/silver_new/armour/ringmail_bracers.c
 * Creator      : Udana
 * Date         : March 2006         
 * Purpose      : Rommenus Ringmail Bracers
 * Related Files: 
 * Comments     : 
 * Modifications: Modified by Pasqua
 */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"

#define ARMOUR_CLASS 30

void
create_armour()
{
    	set_name("armour");
    	add_name("bracers", "sleeves");

    	add_adj(({"steel", "ringmail"}));

    	set_short("pair of ringmail bracers");
    	set_long("Sleeves made of small steel rings plated together. They are not heavy "+
		"and looks like could stop an arrow, or even a weak blow.\n");
    	set_ac(ARMOUR_CLASS + random(5));
    	set_at(A_ARMS);

    	add_prop(OBJ_I_WEIGHT, 1000);
    	add_prop(OBJ_I_VOLUME, 1200);
    	add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}
