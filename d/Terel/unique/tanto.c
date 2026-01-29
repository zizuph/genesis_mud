/*
 * Sorgum's tanto for Benton the Cannibal Corpse.
 */
// file name:    ~Terel/unique/tanto.c
// creator(s):   Sorgum 1994-ish
// purpose:      A magical knife for Benton the Cannibal Corpse
// note:         Has a special with MAGIC_DT that goes off 1 in 4 did_hits
//               against good align opponents.
//               Must be evil align to wield. 
//               Making it a spell_enhancer too.
// updates: Lilith + Zizuph, Jan 2022 for re-launch
//          Lilith, Mar 2022: fixed typo in special; made kept.
//          Lilith, May 2022: Since Tanto is unbreakable, reducing the 
//                  hit/pen from 40/40 to 36/36. Tuned off logging 
//                  of special as it is working as intended.

inherit "/std/weapon";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";
inherit "/d/Genesis/specials/resist";
#include <stdproperties.h>
#include <language.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>

#define TP this_player()
#define TO this_object()
#define ETO environment(this_object())
#define ETP environment(this_player())
#define ENV(xx) environment(xx)
#define CAP(xx) capitalize(xx)
#define TANTO_LOG "/d/Terel/unique/log/tanto_log"

#define ALIGN   -650
#define SP      40
#define HIT     36
#define PEN     36

public mixed
wield(object wep)
{
    // need to be evil
    if (this_player()->query_alignment() > (ALIGN))
    {
	return "The tanto resists the clasp of your hand! You are much "+
	"too good to be be worthy of wielding it.\n";
    }

    this_player()->catch_msg("You feel a dark chill settle upon you like an "+
      "invisible shroud.\n");

    return 1;
}

void
create_weapon()
{
    set_name("tanto");
    add_name(({"_benton_knife_", "knife", "dagger", "blade"}));
    set_adj(({"steel", "cold"}));
    set_short("tanto");
    set_long("This is a cold steel blade of superb craftsmanship.  "+
      "It is almost too long to be considered a knife but a bit "+
      "too short to fit into the 'short sword' class of weapons. "+
      "The metal appears to have stripes where the steel has been "+
      "repeatedly folded during the forging process. The hilt is "+
      "crafted from fossilized bone and wrapped in shark skin. "+
      "The kashira at the end of the handle is made of the same "+
      "steel as the blade.\n");

    add_item(({"steel", "metal", "stripes"}),  "");
    add_item(({"hilt", "fossilized bone", "bone", "handle"}),  "");
    add_item(({"shark skin"}),  "");
    add_item(({"kashira", "cap"}),  "The cap is oblong in shape, and "+
      "made of steel. The shark skin that wraps the hilt is threaded "+
      "through a metal loop on each side. A seal has been affixed atop "+
      "the kashira.\n");
    add_item(({"seal", "decoration", "moons", "crescent moons"}),
      "The seal atop the oblong kashira is that of a dragon-like serpent "+
      "in a figure-eight, with seven crescent moons one side "+
      "and seven stars on the other.\n"); 
    add_item(({"dragon", "dragon-like serpent", "scale"}),
      "The dragon is made of platinum. It has been etched with fine "+
      "details -- you can see the outline of every scale.\n");

    set_magic_spellpower(SP);   
    set_default_weapon(HIT, PEN, W_KNIFE, W_SLASH | W_IMPALE, W_LEFT, TO);
    set_wf(TO);
    set_keep(1);

    add_prop(OBJ_I_WEIGHT,  1000); 
    add_prop(OBJ_I_VOLUME,  1000); 
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + random(500));
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_S_WIZINFO, "This is Benton's weapon. It is cloned by "+
      "/d/Terel/common/moor/monster/benton at "+
      "/d/Terel/common/moor/tomb/gore_chamber. It can only be "+
      "wielded by those with evil align ("+ALIGN+") and will do "+
      "a MAGIC_DT hit_me of 1/4 of the alignment of the 'good' enemies. "+
      "Chance of the special is 1 in 4 did_hits. It does not dull. "+
      "It is also a lvl "+ SP +" spell enhancer (for now).\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({50,"death"}));
    add_prop(MAGIC_AM_ID_INFO,
      ({ "An aura of evil enshrouds this weapon\n", 10,
	"Evil from hands that kill without reckon\n", 15,
	"From Benton it comes and his it shall remain\n", 20,
	"Yet one of an evil leaning may it obtain\n", 30,
	"To inflict havoc and pain on those who think they are good\n", 35,
	"This is the requirement Benton wants understood.\n", 40, 
	"To you this is his unbreakable vow,\n", 45, 
	"'My magical tanto is unbreakable now.'\n", 50 }) );

}

/*
 * Function name: set_dull
 * Description:   Use this to increases the dull status on weapons.
 * Arguments:     cond - The new condition we want (can only be raised)
 * Returns:       1 if new condition accepted
 *  IF THIS IS CHANGED, THE MAGIC ID INFO AND WIZ INFO NEED TO BE CHANGED.
 */
int
set_dull(int du)
{
    return 0;
}

/*
 * Function name: remove_broken
 * Description  : The weapon got broken so the player has to stop
 *                wielding it.
 * Arguments    : int silent - true if no message is to be genereated
 *                             about the fact that the weapon broke.
 */
varargs void
remove_broken(int silent = 0)
{
    if (calling_function() == "item_expiration_break") 
	::remove_broken(silent);

    return;
}

varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit,
  int dam)
{
    int result, mag_res, special;

    result = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if (enemy->query_alignment() < 0)
	return 0;

    if (phurt == -1) 
    {
	query_wielded()->catch_msg("The tanto just misses " +
	  QTNAME(enemy) + " by a hair.\n");
	enemy->catch_msg("The tanto comes dangerously close to cutting "+
	  " you.\n");

    }
    else if (phurt == 0) 
    {
	query_wielded()->catch_msg("The tanto cuts into the flesh of " +
	  QTNAME(enemy) + " but does little damage.\n");
	enemy->catch_msg("The tanto cuts cleanly into your flesh with "+
	  "little damage.\n");
    }
    else 
    {
	if (random(4) == 3) 
	{
	    mag_res = combine_resistances(enemy, ({ MAGIC_I_RES_COLD }) );	 
	    if (mag_res >= 100)	
	    {				
		query_wielded()->catch_msg(QCTNAME(enemy) +" appears to "+
		  "be immune to the dark magic of your tanto!\n");
		enemy->catch_msg("You are immune to the dark magic of "+
		  QTPNAME(query_wielded ())+" tanto.\n");
		return result;
	    }

	    query_wielded()->catch_msg("You feel dark energy coursing "+
	      "between your hand and the tanto as it shreds through " +
	      QTPNAME(enemy) + " flesh.\n");
	    enemy->catch_msg("You feel excruciating pain as the evil "+
	      "blade of the tanto shreds your flesh away from the bone.\n");

	    // F_PENMOD(40,100) is 280, so this will be slightly higher than
	    // a normal hit at maximum 1200 alignment. This does bypass
	    // armour as it is a magic energy attack, but it checks for
	    // magical resistance to cold and reduces damage accordingly.
	    dam = (F_ATTACK_PEN_MOD(enemy->query_alignment()/4));
	    special = dam - (dam * mag_res / 100);
	    enemy->hit_me(special, MAGIC_DT, query_wielded(), -1);
// Turned off logging. The special is working as intended - Lil
//	    seteuid(getuid());
//	    write_file(TANTO_LOG, wielder->query_name() +" "+ special +
//	      " wcpen to "+ enemy->query_name() +" with align "+
//	      enemy->query_alignment() +" and cold res "+ mag_res +
//	      " (" + ctime(time()) + ")\n");	

	    if (enemy->query_hp() <= 0)
	    {
		enemy->do_die(query_wielded());
	    }
	}
	return result;
    }
}

void appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}


