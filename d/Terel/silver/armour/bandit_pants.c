/* File         : /d/Terel/silver_new/weapon/bandit_pants.c
 * Creator      : Pasqua
 * Date         : March 2006         
 * Purpose      : Bandit Crew
 * Related Files: 
 * Comments     : Used Mentor Udana's thought of how to calculate EQ
 * Modifications: Udana - added cold weather protection.
 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"
/* used to calculate weight and volume, 1.0 is for steel.*/
#define WEIGHT_MOD 0.3
/* used to calculate value */
#define VALUE_MOD 0.6
#define AC 22
#define AT A_LEGS

#ifndef OBJ_COLD_WEATHER_PROTECT
#define OBJ_COLD_WEATHER_PROTECT "_obj_cold_weather_protect"
#endif


create_armour()
{
  set_name("pants");
  add_name("armour");
  set_short("green leather pants");   
  set_long("These green pants seems to strong and stiff, the leather have been " +
	  "hardened in boiling oil and then stretched over a wooden or stone model " +
	  "of a regular legparts of a human body. In severe combat situations, these " +
	  "leather pants may need to be replaced often. However, they are easily cleaned " +
	  "reasonably unaffected by the weather and resists all but the severest of abrasions.\n");
  /* (impale, slash, bludgeon) */
  set_default_armour(AC + random(3), AT, ({-1, -1, 1}));
  add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_ARMOUR(AC)) * VALUE_MOD));
  add_prop(OBJ_I_WEIGHT, ftoi(itof(F_WEIGHT_DEFAULT_ARMOUR(AC, AT)) *
WEIGHT_MOD));
  add_prop(OBJ_I_VOLUME, ftoi(itof(query_prop(OBJ_I_WEIGHT)) / (5.0 *
WEIGHT_MOD)));
  
  add_prop(OBJ_COLD_WEATHER_PROTECT, 1);
}

