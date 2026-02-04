/* File         : /d/Terel/silver_new/armour/worn_cloak.c
 * Creator      : Udana	
 * Date         : March 2006         
 * Purpose      : Rommenus Cloak
 * Related Files: 
 * Comments     : 
 * Modifications: Modified by Pasqua
 */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 18

#ifndef OBJ_COLD_WEATHER_PROTECT
#define OBJ_COLD_WEATHER_PROTECT "_obj_cold_weather_protect"
#endif



void
create_armour()
{
    set_name("armour");
    add_name("cloak");

    set_adj("green");
    add_adj("worn");

    set_short("green cloak");
    set_long("A worn cloak of green linen patched with leather or cloth in many "+
    	     "places - it looks like its been serving its "+
             "owner for many years now. \n");
    set_ac(ARMOUR_CLASS);
    set_at(A_ROBE);

	add_prop(OBJ_COLD_WEATHER_PROTECT, 1);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}

