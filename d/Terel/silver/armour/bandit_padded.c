/* File         : /d/Terel/silver_new/weapon/bandit_padded.c
 * Creator      : Pasqua
 * Date         : March 2006         
 * Purpose      : Bandit Crew
 * Related Files: 
 * Comments     : Used Mentor Udana's thought of how to calculate EQ
 * Modifications: 
 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"
/* used to calculate weight and volume, 1.0 is for steel.*/
#define WEIGHT_MOD 0.2
/* used to calculate value */
#define VALUE_MOD 0.5
#define AC 32 
#define AT (A_CHEST | A_SHOULDERS | A_ARMS)

create_armour()
{
  set_name("armour");
  set_short("black padded cloth armour");   
  set_long("This black padded armour consist of two layers of spun cloth stuffed " +
	"with thick battering and quilted together. The camouflaging colors make it  " +
	"extremely difficult to spot the wearer of this armour piece under both normal " +
	"light conditions and night operations. The light but durable material doesn't " +
	"seem to provide much armour support and this type of outfit is mostly used by " +
	"bandit packs.\n");
  /* (impale, slash, bludgeon) */
  set_default_armour(AC + random(2), AT, ({-2, -2, 2}));
  add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_ARMOUR(AC)) * VALUE_MOD));
  add_prop(OBJ_I_WEIGHT, ftoi(itof(F_WEIGHT_DEFAULT_ARMOUR(AC, AT)) *
WEIGHT_MOD));
  add_prop(OBJ_I_VOLUME, ftoi(itof(query_prop(OBJ_I_WEIGHT)) / (5.0 *
WEIGHT_MOD)));
}

