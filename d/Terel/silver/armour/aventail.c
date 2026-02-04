/* File         : /d/Terel/silver_new/weapon/aventail.c
 * Creator      : Pasqua
 * Date         : May 2006         
 * Purpose      : Mauwia's Eq
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
#define WEIGHT_MOD 0.5
/* used to calculate value */
#define VALUE_MOD 1.0
#define AC 39 
#define AT (A_HEAD | A_SHOULDERS | A_NECK)

create_armour()
{
  set_name("burgonet-aventail");
  set_short("ivory-white painted burgonet-aventail");   
  set_long("This ivory-white burgonet-aventail consist of a light weight helmet " +
	       "that got an aventail attached to it. The aventail is a chain mail that " +
	       "covers the neck and shoulders. A regular aventail could also be worn as " +
	       "a shawl-like garment, very similar in function to a coif. It is attached " +
	       "directly to the helmet. Staples hold the garment in place to the open-faced " +
	       "burgonet helmet and this type of helmet was used chiefly by cavalry soldiers " +
	       "as a substitute to heavier close-helms and armets. The smith that have forged " +
	       "these two armour pieces and linked them together to one piece of masterpiece. " +
	       "This light weight burgonet-aventail have been painted with an ivory-white color.\n");
  /* (impale, slash, bludgeon) */
  set_default_armour(AC + random(2), AT, ({-1, -1, 1}));
  add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_ARMOUR(AC)) * VALUE_MOD));
  add_prop(OBJ_I_WEIGHT, ftoi(itof(F_WEIGHT_DEFAULT_ARMOUR(AC, AT)) *
WEIGHT_MOD));
  add_prop(OBJ_I_VOLUME, ftoi(itof(query_prop(OBJ_I_WEIGHT)) / (5.0 *
WEIGHT_MOD)));
}

int
special_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object me;
    int hurt;
    int fire_resist;

    me = TO;
    
    if(random(10) < 4) {

        hurt = F_PENMOD(50, 50 + random(20));
        
        hitresult = enemy->hit_me(hurt, MAGIC_DT, me, -1);

        how = "unharmed";
        if (hitresult[0] > 0)
            how = "hurt";
        if (hitresult[0] > 50)
            how = "injured";
        if (hitresult[0] > 100)
            how = "crushed";
        if (hitresult[0] > 200)
            how = "pulverized";
            
        write(QCTNAME(me) + " starts to beats himself in the chest and scream loudly " +
			 "and charges at " + QTNAME(enemy) + ".\n"); 
        enemy->catch_msg(QCTNAME(me) + " starts to beat himself in the chest and scream and charges at you!\n");
        enemy->catch_msg("You feel " + how + " by the charge.\n");
      
        return 1;
    }

    return 0;
}

