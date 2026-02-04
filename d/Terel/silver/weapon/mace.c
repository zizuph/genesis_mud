/* File         : /d/Terel/silver_new/weapon/mace.c
 * Creator      : Pasqua
 * Date         : March 2006         
 * Purpose      : Bandit Crew
 * Related Files: 
 * Comments     : Used Mentor Udana's thought of how to make EQ
 * Modifications: 
 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"
/* used to calculate weight and volume*/
#define WEIGHT_MOD 2.1
/* used to calculate value */
#define VALUE_MOD 1.5
#define HIT 32
#define PEN 37

create_weapon()
{
  set_name("mace");
  add_name("club");
  set_short("heavy flanged mace");   
  set_long("The 8 flanged head top of this mace seems quite fearsome and it seems like its " +
	 "capable of fending off the deadliest foes.\n");
  set_default_weapon(HIT + random(2), PEN + random(2), W_CLUB, W_BLUDGEON, W_ANYH);
  
  add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_WEAPON(HIT, PEN)) * VALUE_MOD));
  add_prop(OBJ_I_WEIGHT, ftoi(itof(F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD)) *
WEIGHT_MOD));
  add_prop(OBJ_I_VOLUME, ftoi(itof(query_prop(OBJ_I_WEIGHT)) / (5.0 *
WEIGHT_MOD)));
}
