/* File         : /d/Terel/silver_new/weapon/rapier.c
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
#define WEIGHT_MOD 1.1
/* used to calculate value */
#define VALUE_MOD 1.2
#define HIT 35
#define PEN 33

create_weapon()
{
  set_name("rapier");
  add_name("sword");
  set_short("slender sharp rapier");   
  set_long("A relatively slender rapier with a blade that is only about one inch in width. " +
	 "This sharply pointed rapier got an elaborate hilt and hand-guard. Its possible to both " +
	 "cutting and thrusting the enemy with the attacks of this sword.\n");
  set_default_weapon(HIT + random(4), PEN + random(4), W_SWORD,W_IMPALE | W_SLASH, W_ANYH);
  
  add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_WEAPON(HIT, PEN)) * VALUE_MOD));
  add_prop(OBJ_I_WEIGHT, ftoi(itof(F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD)) *
WEIGHT_MOD));
  add_prop(OBJ_I_VOLUME, ftoi(itof(query_prop(OBJ_I_WEIGHT)) / (5.0 *
WEIGHT_MOD)));
}
