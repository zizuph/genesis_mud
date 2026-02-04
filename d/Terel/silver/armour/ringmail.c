/* File         : /d/Terel/silver_new/armour/ringmail.c
 * Creator      : Udana
 * Date         :        
 * Purpose      : Rommenus Ringmail
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

#define ARMOUR_CLASS 40

void
create_armour()
{
    	set_name("armour");
    	add_name("ringmail");

    	add_adj(({"long", "steel"}));

    	set_short("long steel ringmail");
    	set_long( "This armour is made of small steel rings plated together. It has no sleeves, "+
   			"but it's long enough to cover your legs down to tighs.\n");
    	set_ac(ARMOUR_CLASS + random(5));
    	set_at(A_BODY);
    	
    	add_prop(OBJ_I_WEIGHT, 7000);
    	add_prop(OBJ_I_VOLUME, 5500);
    	add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}
