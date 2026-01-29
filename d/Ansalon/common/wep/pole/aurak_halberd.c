/*
 * Name: ancient dragon-coiled halberd.
 * Hit/Pen: Depends on who's using it. 40/40 - 40/42
 * Special: +4 Hit against a mounted enemy.
 * Description: A halberd for auraks.
 *
 * By: Elmore.
 *
 * Latest change: Removed the mana drain when using the commandword.
 *                Added a alarm that removes 20 points of fatigue
 *                every five minutes.
 * 
 * Navarre: July 3rd 2006, fixed typos.
 * Petros: November 2009, weapon allowed unlimited haste because it was checking
 *                        wielder instead of query_wielded.
 */

// this is good habit to put everywhere - enforces better coding Milan
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

// Used for when a RDA or draconian wields the weapon.
#define HITRDA 40
#define PENRDA 42

// Used for when a RDA vs. a mounted person wields that weapon.
#define HITMRDA 44
#define PENMRDA 42

// Used when a normal player vs. a mounted person wields the weapon.
#define HITMN 44
#define PENMN 40

// Used when a normal player wields the weapon.
#define HITN 40
#define PENN 40

#define HASTE_MOD       50

int enemy_mounted = 0;
int alarm_id;
int has_speed = 0;

void
create_weapon()
{
    set_name("halberd");
    add_adj(({"ancient","dragon-coiled"}));
    set_short("ancient dragon-coiled halberd");
    set_long("This long halberd looks very old and well "+
      "used. The handle is made out of oak wood and "+
      "carved with such precision that the blade almost "+
      "seems to merge together with the wood. From the "+
      "bottom of the handle a beautiful silver serpent "+
      "twists and curls itself all the way to the "+
      "beginning of the blade. The blade is made "+
      "out of tempered steel and the edge of it "+
      "has been coated with some strange red alloy. The "+
      "halberd has been bent in an odd angle, making it "+
      "very effective against mounted foe.\n");

    add_item(("serpent"),
      "The details of this serpent is amazing. It has "+
      "been made with such care that every scale of the "+
      "serpent is visible. The head of the serpent "+
      "resembles the head of an ancient horned red "+
      "dragon, both quite fascinating and terrifying. "+
      "The serpent has an open mouth, and it looks "+
      "like it's almost breathing out the blade. "+
      "The silver serpent is wrapped around the handle "+
      "in some rather unfortunate places, and it makes "+
      "it very hard to get a decent grip around this "+
      "weapon without the proper training.\n");

    add_item(("blade"),"The blade is extremely sharp "+
      "and it's made out of tempered steel that has been "+
      "blackened by the fire. The edge of the " +
      "blade has been coated with some strange red alloy.\n");

    add_item(("grip"),
      "You realise that this weapon is one of the few "+
      "halberds that was forged by the Dark Queens "+
      "smiths and imbued with her power. They were "+
      "created for the officers of the Red Dragonarmy "+
      "and made especially for their fighting style.\n");

    add_prop(OBJ_S_WIZINFO, "This is one of the many halberds "+
      "that was forged in the Abyss, by the smiths of "+
      "the Dark Queen. "+
      "The halberds are a gift to the officers of the "+
      "Red Dragonarmy and are thus customized to their "+
      "fighting style. When wielded by a draconian or "+
      "dragonarmy member, the halberd will grant the "+
      "wielder +2 pen, and if it is used against a "+
      "mounted foe the halberd will add +5 to hit. "+
      "The halberd also has a commandword, that will "+
      "grant some speed to the wielder. This halberd "+
      "can be found in Ansalon and Krynn, and it's "+
      "wielded by Auraks.\n");

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 10, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,
      ({"The weapon is enchanted.\n", 5,
	"The smiths of Takhisis "+
	"made this weapon and it was crafted for " +
	"each of the officers in the Red Dragonarmy, " +
	"as a gift from their General. The halberd is " +
	"effective against mounted enemies. \n", 25,
	"If the wielder " +
	"is a member of the Red Dragonarmy he will be able to " +
	"wield it more effectively in battle.\n", 50}));

/* Kender prop, allow alter ability to change the descriptions of the weapon */
    add_prop(OBJ_I_CONVERT_HOOPAK, 1);
 
    
    set_default_weapon(HITN, PENN, W_POLEARM, W_IMPALE, W_BOTH);
    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 7600);
    add_prop(OBJ_I_WEIGHT, 7500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HITN, PENN));
}

/*
 * Function name: rda_wield
 * Description  : Called when a member of the Dragonarmy or a Draconian
 *                wields the weapon.
 * Arguments    : None.
 * Returns      : void.
 */
private void
rda_wield()
{
    wielder->catch_msg("As you wield the " +short()+
      ", you close your eyes briefly. Suddenly visions "+
      "of victorious battles in the name of the Dark Queen begin "+
      "to form in your mind.\n"+
      "The vision fades, leaving you with a taste for battle, and a "+
      "lust for blood.\n");

    set_hit(HITRDA);
    set_pen(PENRDA);
    wielder->update_weapon(TO);
}

/*
 * Function name: default_wield
 * Description  : Called when a !member of the Dragonarmy or a !Draconian
 *                wields the weapon.
 * Arguments    : None.
 * Returns      : void.
 */
private void
default_wield()
{
    wielder->catch_msg("As you wield the " +short()+
      ", you feel a strange sense of malevolence radiate briefly from the " +
      "weapon, making you feel somewhat uncomfortable.\n");

    set_hit(HITN);
    set_pen(PENN);
    wielder->update_weapon(TO);
}

/*
 * Function name: wield
 * Description  : Called when somone tries to wield the weapon.
		  Checks to see if it's a draconian or RDA
		  where it calls rda_wield(). If not it's
		  going to call default_wield.
 * Arguments    : The object that is being wielded
 * Returns      : void.  - nor really, see sman. Milan
 */
mixed
wield(object what)
{

    if(TP->query_guild_name_occ() == "Dragonarmy" || TP->query_race_name() == "draconian")
    {
	rda_wield();
    }
    else
	default_wield();
    has_speed = 0;
    say(QCTNAME(TP) + " wields " + HIS(TP) + " " + QSHORT(TO) + ".\n");
    return 1;
}

/*
 * Function name: state_change
 * Description  : Called when a the weapons changes it
 *                hit and pen.
 * Arguments    : hit and pen
 * Returns      : void.
 */
void
state_change(int hit, int pen)
{
    set_hit(hit);
    set_pen(pen);

    if (wielded && wielder)
	wielder->update_weapon(this_object());
}

/*
 * Function name: try_hit
 * Description  : Checks to see if the enemy is mounted.
 * Arguments    : object target
 * Returns      : int
 */
public int
try_hit(object enemy)
{
    if (objectp(enemy->query_prop(LIVE_O_STEED)))
    {
	/* Switch to high power */
	if (!enemy_mounted)
	{
	    if(TP->query_guild_name_occ() == "Dragonarmy" ||
	      TP->query_race_name() == "draconian")
	    {
		state_change(HITMRDA, PENMRDA);
	    }
	    else
		state_change(HITMN, PENMN);
	    enemy_mounted = 1;
	}
    }
    else
    {
	/* Switch to low power */
	if (enemy_mounted)
	{
	    if(TP->query_guild_name_occ() == "Dragonarmy" ||
	      TP->query_race_name() == "draconian")
	    {
		state_change(HITRDA, PENRDA);
	    }
	    else
		state_change(HITN, PENN);
	    enemy_mounted = 0;
	}
    }

    return ::try_hit(enemy); // we have to return nonzero in order to be able hit. Milan
}

/*
 * Function name: unwield
 * Description  : Checks it see if the wielder has
		  the speed bonus, if true, then it'll
		  remove it.
 * Arguments    : object
 * Returns      : mixed
 */
mixed
unwield(object what)
{
    state_change(HITN, PENN); // just reset the state. Milan
    if (has_speed)
    {
        has_speed = 0;
	    TP->change_prop(LIVE_I_QUICKNESS, 
	        TP->query_prop(LIVE_I_QUICKNESS) - HASTE_MOD);
        wielder->catch_msg("The world around you seems to slow down.\n");
        if (wielder->query_race_name() != "draconian")
        {
            remove_alarm(alarm_id);
        }        
    }
    return 0;
}

private void
do_fatigue()
{
    wielder->add_fatigue(20);
    return;
}

/*
 * Function name: get_speed
 * Description  : If a draconian or Dragonarmy member wields this
		  weapon, it'll be possible to use a command word
		  (Takhisis). If this happens, the polearm will
		  add 50 to the speed of the wielder. This can
		  only be done if the wielder has max mana. And
		  if it succeeds it'll drain the wielder of
		  1000 mana.
 * Arguments    : None.
 * Returns      : void.
 */
// added private cast so this function can be called only from this object Milan
private void
get_speed()
{
    object player = query_wielded();
    if (!objectp(player)
        || has_speed)
    {
        // Weapon must be wielded, and speed must not have already been
        // applied.
        return;
    }
    
    if (player->query_guild_name_occ() == "Dragonarmy" 
        || player->query_race_name() == "draconian")
    {
        has_speed = 1;
    	wielder->change_prop(LIVE_I_QUICKNESS, 
    	    wielder->query_prop(LIVE_I_QUICKNESS) + HASTE_MOD);
    	wielder->catch_msg("The " +short()+ " seems to become become alive!\n" +
    	  "You feel hasted!\n");
        if (wielder->query_race_name() != "draconian")
        {
            alarm_id = set_alarm(0.5,300.0,&do_fatigue());
        }
    }
    return;
}

/*
 * Function name: my_say
 * Description  : Checks to see if the wielder
		  said or shouted the command word.
 * Arguments    : string
 * Returns      : int
 */
int
my_say(string what)
{
    if (what != "takhisis" && what != "Takhisis")
    {
	    return 0;
	}

    get_speed();
    set_alarm(0.0, 0.0, get_speed);
    return 0;
}

/*
 * Function name: init
 * Description  : Called when the weapon is cloned
 * Arguments    : None.
 * Returns      : void.
 */
void
init()
{
    ::init();
    add_action(my_say, "say"); 
    add_action(my_say, "shout");
}
