/*
 * Info: This weapon is based on a mace made by Glain.
 * Creator: Elmore.
 * 
 * This polearm was once created by the High Priests
 * of Istar to aid them and their guards in battle.
 * However this one has been blessed by the evil god
 * Sargonnas, thus no goodalignmed persons can wield
 * this weapon. The blade is serrated and this makes it
 * very hard to dull. 
 * Suranir, the priest of the village of Nethosak, has 
 * furthermore enchated the halberd giving it an
 * improved combat speed
 *
 * 16.08.2001 Torqual: 
 * - Added randomness to hit/pen
 * - Added new wield/unwield descriptions
 * - Changed damage formula to reduce 3rd max_hp and 200 random hp
 *   so smaller players will have chance of surviving the first try
 *   if player is less then 50 con - half of hp will be reduced
 * - Added check if player got enough damage to be killed
 *
 * June 2006: Navarre:
 * Changed:  #define HIT 	46 + random(3)
 *           #define PEN 	42 + random(2)
 * To     :  #define HIT 	46 + random(4)
 *           #define PEN 	42 + random(3)
 * To match documentation of wanting hit 46-49
 * and pen 42-44, since random(3) is 0-2.
 * Cotillion 2015-02-14:    LIVE_I_QUICKNESS 100 -> 50
 * 
 * June 2017: Carnak
 * Changed to allow for hoopak conversion.
 *
 * Jan 2020: Arman
 * Added code to ensure it breaks when item_expiration.c is called.
 *
 * 2021-03-10 Carnak:
 * - Increasing the hit and pen of this weapon as a part of a change
 *   of several two handed weapons in the game.
 */

#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <options.h>
#include <filter_funs.h>

/* Kender prop, allow alter ability to change the descriptions of the weapon */
#define OBJ_I_CONVERT_HOOPAK "_obj_i_convert_hoopak"

#define WOUNDS 	4
#define SPEED   50	
#define HIT 	55
#define PEN 	53 + random(3)

/* prototypes */
void kill_infidel(object whom);


void
create_weapon()
{
   set_name("halberd");
   set_adj("serrated");
   add_adj("obsidian");
   set_long("The halberd is made out of a smooth wooden staff "+
         "and has a large blade connected to one end. The blade "+ 
         "have been forged out of the precious obsidian and it is "+
         "extremely sharp. There's a small crystal on the "+
         "other end of the staff, which might act like a "+
         "counterweight on combat. The entire halberd is very "+
         "light even though the blade seems quite large. You "+
         "notice some silvery runes which has been engraved "+
         "into the staff. As you look at them they seem to shimmer "+
         "slightly. Some of the runes are overlapped with each "+
         "other almost like they are trying to enchant this "+
         "halberd beyond its capability.\n");

   set_short("serrated obsidian halberd");
    		// to_hit 46-49, pen 42-44
   set_default_weapon(HIT,PEN, W_POLEARM, W_SLASH | W_IMPALE, W_BOTH);

/* Kender prop, allow alter ability to change the descriptions of the weapon */
    add_prop(OBJ_I_CONVERT_HOOPAK, 1);
    
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
   add_prop(MAGIC_AM_ID_INFO, ({"These polearms were created "+
      "by the High Priests of Istar before the Cataclysm.  "+
      "Forged from a long forgotten mixture of metals that give it "+
      "its durability and light weight, it was then enchanted to "+
      "leave ghastly wounds that could not be healed through normal means. "+
      "Many of the High Priests enemies slowly bled to death "+
      "attempting to flee from the cruel oppressors.\n",10,
      "This one seems to be defiled by becoming blessed by the evil "+
      "god Sargonnas, which gives it some extra speed.\n", 35}));

   add_item(("blade"),"The blades are both identical and made out of "+
                     "obsidian, they are extremely sharp and the way they "+
                     "are constructed would make it quite easy to impale "+
                     "someone.\n");

   add_item(("staff"),"This staff is made from some unknown type of "+
                       "wood. It seems very dark and hard, you notice some "+
                       "strange runes on the staff.\n");

   add_item(({"runes", "silvery"}),
        "These runes may be of elven origin but neither "+
        "the writing nor the way that this weapon has been "+
        "forged indicate who could have done this. You start "+
        "to stare intensely on the runes, but are unable "+
        "to decipher what they mean.\n");

   add_item(({"crystal"}),"This is a transparent crystal "+
        "that has been put here to make the weapon more steady in "+
        "combat.\n");

   set_wf(this_object()); 
   seteuid(getuid(TO));
   add_prop(OBJ_I_VOLUME, 3000);
   add_prop(OBJ_I_WEIGHT, 4470);
   set_likely_dull(1);
   set_likely_corr(1);
   set_likely_break(1);

}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
        int phit, int dam)
{ 
    if (phurt <= 0)
    {
       return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }

    if (!random(10))
    {
    switch (!random(WOUNDS))
      {
      default:
         wielder->catch_msg("You feel a tug on the " + short() +
            " as you rip flesh out of the " + hdesc + " of " +
            QTNAME(enemy) + " with the serrated edge " +
            "of the " + short() + ", leaving behind a nasty " +
            "bleeding wound.\n");
         enemy->catch_msg("Pain shoots through your " + hdesc +
            " as your flesh is torn off from the serrated edge on " +
            "of the " + short() + ", leaving behind a " +
            "nasty bleeding wound.\n");
         wielder->tell_watcher(QCTNAME(wielder) + " rips the flesh " +
            "out of the " + hdesc + " of " + QTNAME(enemy) + " with " +
            "the serrated edge of the " + short() +
            ", leaving behind a nasty bleeding wound.\n", enemy);
         break;
      }
      seteuid(getuid(TO));
      clone_object("/d/Ansalon/goodlund/nethosak/city/std/bleed_obj")->move(enemy, 1);
   }
    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

mixed
wield(object what)
{
    string fail_wield_message,
	   death_message;

    if (this_player()->query_alignment() <= 0)
    {
        wielder->catch_msg("As you close your hands around the shaft " +
		"of the halberd, you feel the runes growing warm. "+
                "For a short moment your vision blurs and in " +
		"red, swirling mist you see silhouette of a man. " +
		"It changes into the vulture and soon after your vision "+
		"returns.\n");
        wielder->tell_watcher("As " + QTNAME(wielder)+ " grips the shaft of the "+
                query_short()+ " " + HIS(wielder) + " eyes dim and then " +
		"flash red for a short moment.\n");
        wielder->change_prop(LIVE_I_QUICKNESS,
		 wielder->query_prop(LIVE_I_QUICKNESS) + SPEED);
        return 1;
    }

    fail_wield_message = "As you close your hands around the shaft "+
	   "of the halberd, your vision blurs and in red, swirling " +
	   "mist you see silhouette of a man. He speaks to you in " +
	   "distant voice : \" Wretch, how dare you?! I may be banished but " +
	   "in the end I will have my vengence! You will be first to feel " +
	   "my wrath!\" When shape fades into the mist, the runes on the " +
	   "halberd grow hotter and hotter. In an instant, flames surround " +
	   "your forearms! ";
    if (wielder->query_base_stat(2) > 50 )
    {
	// 30% of max_hp and random 200 hp penalty - should spare small players
        wielder->heal_hp(-(wielder->query_max_hp()/3) - random(200));
    }
    else
    {
	wielder->heal_hp(-(wielder->query_max_hp()/2));
    }

    if (wielder->query_hp() <=0)
    {
        wielder->tell_watcher(QCTNAME(wielder)+ " grips the shaft of the " + 
		query_short() + ". " + C(HIS(wielder)) + " eyes " +
		"flash red for a short moment and " +
		"face twists in pain as flames leap from the " + query_short() +
 		" onto " + HIS(wielder) + " arms! In a short time " + 
		HIS(wielder) + " body is consumed by white-hot flames.\n"); 

	death_message = "Despite your best efforts you cannot release " +
		"the halberd. Your hands, your shoulders and then " +
		"your whole body is engulfed in white-hot flames. " +
		"Just as you take your teminal breath you hear " +
		"demonic laughter comming from far away.";

	set_alarm(0.0, 0.0, "kill_infidel", wielder ); // lets kill him finaly

	return fail_wield_message + death_message + "\n"; 
    }
    else
    {
        wielder->tell_watcher(QCTNAME(wielder)+ " grips the shaft of the " + 
		query_short() + ". " + C(HIS(wielder)) + " eyes " +
		"flash red for a short moment and " +
		"face twists in pain as flames leap from the " + query_short() +
 		" onto " + HIS(wielder) + " arms! With great effor " +
		HE(wielder) + " releases it from " + HIS(wielder) + 
		" hands.\n");
 
	return fail_wield_message + "You struggle to release the halberd "+
		"and with great effor you succed.\n";
    }
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


/*
 * Function name: set_dull
 * Description:   Use this to increases the dull status on weapons.
 * Arguments:     cond - The new condition we want (can only be raised)
 * Returns:       1 if new condition accepted
 */
int
set_dull(int du)
{
    return 0;
}


mixed
unwield(object what)
{
    wielder->catch_msg("You release your grip around the halberd.\n");
    wielder->tell_watcher(QCTNAME(wielder)+ " releases " +HIS(wielder)+
                          " grip around the " +short()+ ".\n");
    wielder->change_prop(LIVE_I_QUICKNESS,
	     wielder->query_prop(LIVE_I_QUICKNESS) - SPEED);
    return 1;
}

void
kill_infidel(object whom)
{
	whom->do_die(TO);
}
