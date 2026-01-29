/* A rapier for the Elf generated Elves */
 
inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
 
#define WEP_TYPE W_SWORD
#define HIT            20
#define PEN            21
#define HANDS          W_ANYH
#define DAMAGE         W_SLASH | W_IMPALE
 
void
create_weapon()
{
   set_name("sword");
   add_name(({"rapier"}));
   add_adj(({"elven"}));
   set_short("elven rapier");
   set_pshort("elven rapiers");
   set_long("The rapier has runes etched on the side of the blade. "+
        "You cannot make out what they say. But it does make the "+
		  "rapier look a little more deadlier than you know it to be.\n");
	add_item(({"blade","runes"}),
		  "The blade of this rapier is made of steel. "+
		  "Etched into the blade you see 'A Elbereth Githoniel'. "+
		  "You wonder what it means.\n");
   set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);
   add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(HIT,PEN));
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
   add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);
 
}
 
