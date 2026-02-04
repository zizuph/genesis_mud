/* File         : /d/Terel/silver_new/weapon/cutlass.c
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
#define PEN 36

create_weapon()
{
  set_name("cutlass");
  add_name("sword");
  set_short("short broad cutlass");   
  set_long("A short but broad cutlass usually with a curved blade and one " +
	 "cutting edge. It is suited for close, cramped conditions like in a forest.\n");
  set_default_weapon(HIT + random(3), PEN + random(3), W_SWORD,W_IMPALE | W_SLASH, W_ANYH);
  
  add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_WEAPON(HIT, PEN)) * VALUE_MOD));
  add_prop(OBJ_I_WEIGHT, ftoi(itof(F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD)) *
WEIGHT_MOD));
  add_prop(OBJ_I_VOLUME, ftoi(itof(query_prop(OBJ_I_WEIGHT)) / (5.0 *
WEIGHT_MOD)));
}
