/* File         : /d/Terel/silver_new/weapon/bandit_bandana.c
 * Creator      : Pasqua
 * Date         : March 2006         
 * Purpose      : Bandit Crew
 * Related Files: 
 * Comments     : Used Mentor Udana's idea of how to calculate EQ
 * Modifications: 
 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"
/* used to calculate weight and volume, 1.0 is for steel.*/
#define WEIGHT_MOD 0.1
/* used to calculate value */
#define VALUE_MOD 0.2
#define AC 9
#define AT A_HEAD
create_armour()
{
  set_name("bandana");
  set_short("black bandana");   
  set_long("This is a regular black bandana, made out of cloth. The purpose of this " +
	"bandana is simply to cover half of the face, with this worn only the eyes and " +
	"forehead can be seen.\n");
  /* (impale, slash, bludgeon) */
  set_default_armour(AC + random(2), AT, ({-2, -2, 2}));
  add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_ARMOUR(AC)) * VALUE_MOD));
  add_prop(OBJ_I_WEIGHT, ftoi(itof(F_WEIGHT_DEFAULT_ARMOUR(AC, AT)) *
WEIGHT_MOD));
  add_prop(OBJ_I_VOLUME, ftoi(itof(query_prop(OBJ_I_WEIGHT)) / (5.0 *
WEIGHT_MOD)));
}

