/*
 *  Benton's meathook /d/Terel/unique/bmeathook.c
 *   
 *  This is a gaffing hook used by people in abbatoires/
 *  charnel houses to grab hold of carcasses and move them 
 *  around. This one has a special attack that causes 
 *  opponents to receive a 10 second add_attack_delay
 *  (2 swings) on average once every 3 minutes 
 *  (1 in 35 chance).
 *
 *  Created: Lilith Apr/May 2022
 *  Approved: 
 *
 *  Update: Zizuph Aug 2022
 *  Switched hands - not enough left handed polearms.
 *
 */

inherit "/std/weapon";

#include <wa_types.h>   
#include <macros.h>     
#include <filter_funs.h>
#include <formulas.h>   
#include <stdproperties.h>

#define HOOK_LOG   "/d/Terel/unique/log/hook_log"
#define MY_HIT 45
#define MY_PEN 49
#define DELAY  10

void
create_weapon()
{
    set_name("meathook");
    add_name(({"polearm", "gaffing hook", "gaff hook", "hook",
      "gaffhook", "gaff", "_bentons_meathook_"}));
    set_short("abbatoir gaff");
    set_adj("benton's");
    add_adj(({"gaffing", "meat", "abbatoire", "abbatoir", "benton" }));
    set_long("This abbatoir gaff is comprised of a wickedly sharp "+ 
      "meathook attached to the end of a meter-long shaft. "+ 
      "The shaft itself looks like it is made of sections of bone "+ 
      "that have been threaded onto a metal pole. A bit of sinew "+
      "has been wound around the end to provide a textured grip. "+ 
      "This weapon is terrifying in its efficiency at hooking into "+
      "flesh, causing stunning pain.\n");   

    add_item(({"alloy", "mysterious alloy", "meathook", "hook", 
      "metal"}),  
      "It resembles a very large fish hook made of a mysterious "+
      "ice-blue alloy.\n");

    add_item(({"handle", "bone handle", "grip", "long bone", "sinew",
      "shaft", "bone", "sections of bone", "pole"}),
      "The grip of the gaff hook looks like it was made from "+ 
      "long bones. It is wrapped in sinew to provide a good grip "+
      "for a gory hand.\n");

    // Benton is an unpleasant bugger. He should have superb weapons.
    set_default_weapon(MY_HIT, MY_PEN, W_POLEARM, 
      W_SLASH | W_IMPALE, W_LEFT, this_object());

    set_wf(this_object());
    set_likely_dull(-10);
    set_likely_corr(-10);
    set_likely_break(-10);
    set_keep(1);

    add_prop(OBJ_I_WEIGHT,  2000);  
    add_prop(OBJ_I_VOLUME,  3000); 

    // Magical items cannot be bought at a store.
    add_prop(OBJ_M_NO_BUY, 1); 	
    // Magical, so at least twice as valuable.
    add_prop(OBJ_I_VALUE, (F_VALUE_WEAPON(40, 40) * 2));
    add_prop(OBJ_S_WIZINFO, 
      "This is Benton's meathook polearm, cloned by "+
      "/d/Terel/common/moor/monster/benton at "+
      "/d/Terel/common/moor/tomb/gore_chamber. "+
      "It has hit "+ MY_HIT +" and pen "+ MY_PEN +
      "and has a 1 in 35 (avg once every 3 mins) chance "+
      "of causing a "+ DELAY +" second add_attack_delay.\n");		

    // Setting the required magical props.
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({50,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, 
      ({" This abbatoir gaff that you hold in your hand\n", 20,
        " Belongs to Benton the warlock who once was a man,\n", 30,
        " But now is infected with evil so deep\n", 35, 
        " His soul is corrupted and he no longer sleeps.\n", 40,
        " He will sink this meathook in your flesh\n", 45,
        " And through it you'll know misery afresh\n", 50,
        " As you stumble and miss him again and again.\n", 55,
      }));

}


varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit,
  int dam)
{
    int result, special;

    result = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if (phurt == -1) 
    {
	query_wielded()->catch_msg("You just miss snagging "+ QTNAME(enemy) +  
	  " with your "+short()+".\n");
    }
    else if (phurt == 0) 
    {
	query_wielded()->catch_msg("As your "+ short() +" connects with "+
	  QTNAME(enemy) + " and bounces off with little damage.\n");
    }
    else 
    {
	// 1 swing every 5 seconds is 12 swings a minute.
	// 1 in 35 chance is once every 3 mins make enemy stumble.
	if (random(35) == 0) 
	{
	    query_wielded()->catch_msg("You feel a menacing energy flow "+
	      "between you and the "+ short() +" as it hooks deeply " +
	      "into "+ QTPNAME(enemy) + " flesh and yanks "+
	      enemy->query_objective() +" toward you, making "+
	      enemy->query_objective() +" stumble!\n");
	    enemy->catch_msg("You feel excruciating pain as the "+ short() +
	      "in "+QTPNAME(query_wielded()) +" hand hooks into your "+
	      "flesh and yanks you off your feet, causing you to miss "+
	      "your attack!\n");

	    // Delay does not stack.
	    enemy->add_attack_delay(DELAY, 1);

	    write_file(HOOK_LOG, wielder->query_name() +" caused "+
	      QNAME(enemy) +" to stumble (" + ctime(time()) + ")\n");	
	}
	return result;
    }
}

