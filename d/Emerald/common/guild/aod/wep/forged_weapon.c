/*
 *  /d/Emerald/common/guild/aod/wep/forged_weapon.c
 *
 *  This is the base file to be inherited by weapons which have
 *  been forged by the Army of Darkness Smith.
 *
 *  Copyright (c) June 2006, by Cooper Sherry (Gorboth)
 *
 *  2019-01-15: Carnak
 *      These items will now recover, this was changed due to the implementation
 *      of item expiration
 *
 *  2020-08-19: Arman
 *      Hit and pen reduced when wielded by non-ogres
 */
#pragma strict_types
#include "/d/Emerald/common/guild/aod/defs.h"

inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

/* Definitions */
#define        WEP_POWER  ( ({ 28, 31, 34, \
                               38, 41, 44, \
                               48, 51, 54, \
                               58, 25, 25 }) )
#define        WEP_SHORTS ( ({ "twisted sheet of scrap iron", \
                               "crude iron post", \
                               "heavy iron bar", \
                               "huge iron rod", \
                               "great iron hammer", \
                               "colossal spiked morningstar", \
                               "darksteel face mallet", \
                               "darksteel head spiker", \
                               "darksteel death stick", \
                               "sledgehammer of the colossus", \
                               "enormous dented bucket", \
                               "giant filthy shovel", \
                            }) )

/* Global Variables */
public int         Wep_Level = 0;

/* Prototypes */
public void        create_forged_weapon();
public void        create_weapon();
public void        configure_it();

public void        set_wep_level(int i) { Wep_Level = i; }
public int         query_wep_level() { return Wep_Level; }

int weapon_hit, weapon_pen;

/*
 * Function name:        create_forged_weapon
 * Description  :        a dummy function to be used by inheriting files
 */
public void
create_forged_weapon()
{
} /* create_forged_weapon */


/*
 * Function name:        create_weapon
 * Description  :        set up the weapon
 */
public void
create_weapon()
{
    add_name(AOD_FORGED_ITEM);
    set_name("club");
    add_adj( ({ "large", "big", }) );

    add_prop(OBJ_M_NO_SELL,
        "This would only be worth something to an Ogre. You can't sell"
      + " it here!\n");

    /* This is now necessary to prevent recovery by the recovery handler */
    add_prop("_obj_i_ignore_recovery", 1);

    /* Because these are available at the Forge, we do not want them
     * to recover. Ogres need to work to get these.
     * 
     * 2019-01-15: Carnak
     *      This has been removed due to the implementation of item expiration
     */
    //set_may_not_recover();

    create_forged_weapon();
    configure_it();

} /* create_weapon */


/*
 * Function name:        configure_it
 * Description  :        set up all the properties of the weapon.
 */
public void
configure_it()
{
    int     hit = WEP_POWER[Wep_Level] + random(3);
    int     pen = WEP_POWER[Wep_Level] + random(3);
    string  short_desc = WEP_SHORTS[Wep_Level];

    set_default_weapon(hit, pen, W_CLUB, W_BLUDGEON, W_BOTH, 0);

    set_short(short_desc);

    switch(short_desc)
    {
        case "twisted sheet of scrap iron":
            add_name( ({ "iron", "scrap", "sheet" }) );
            add_adj( ({ "twisted", "scrap", "of", "sheet" }) );
            set_long("What a preposterous weapon! Someone (incredibly"
              + " strong) seems to have taken something like a"
              + " two by four foot sheet of scrap metal and twisted"
              + " it up like a napkin into the shape of a very"
              + " large and heavy cigar. I suppose if you really"
              + " feel the need you could wield this mess. It"
              + " would certainly hurt to be hit by it!\n");
            break;
        case "crude iron post":
            add_name( ({ "post", "pole" }) );
            add_adj( ({ "crude", "iron" }) );
            set_long("Is this actually a weapon? If so, it looks as"
              + " if someone made it by simply pulling a fence post"
              + " out of the ground. It is little more than a large"
              + " pole which has been twisted a bit at the bottom to"
              + " form a handle of sorts. I suppose in the right"
              + " hands anything makes a dangerous weapon!\n");
            break;
        case "heavy iron bar":
            add_name( ({ "bar" }) );
            add_adj( ({ "heavy", "iron" }) );
            set_long("This heavy piece of iron looks as if is meant"
              + " to have been used in construction. However, someone"
              + " has decided that it can also be used as a weapon, and"
              + " has wrapped some leather around its base for grip."
              + " Only a very large person would think of this as"
              + " a proper weapon.\n");
            break;
        case "huge iron rod":
            add_name( ({ "rod" }) );
            add_adj( ({ "huge", "iron" }) );
            set_long("This weapon is remarkably crude. A huge iron rod,"
              + " at least six inches in diameter and five feet long,"
              + " has been wrapped with leather at one end to assist"
              + " with grip. It almost looks as if it were designed to"
              + " be wielded in one hand.\n");
            break;
        case "great iron hammer":
            add_name( ({ "hammer" }) );
            add_adj( ({ "great", "iron" }) );
            set_long("This hammer is positively huge! From a thick"
              + " iron shaft that is at least four feet in length,"
              + " a massive blunt hammer head has been fixed to the"
              + " end. This looks more like a tent-stake pounder"
              + " than a weapon.\n");
            break;
        case "colossal spiked morningstar":
            add_name( ({ "morningstar", "star" }) );
            add_adj( ({ "colossal", "spiked", "morning", "iron" }) );
            set_long("This enormous weapon is fearful indeed! A huge"
              + " ball of iron fixed with dozens of three-inch long"
              + " spikes rests atop the oversized pommel, which itself"
              + " is nearly four feet long.\n");
            break;
        case "darksteel face mallet":
            add_name( ({ "mallet" }) );
            add_adj( ({ "dark", "steel", "face", "darksteel" }) );
            set_long("Massive and dark, the steel which has formed"
              + " this huge weapon of war positively crackles with"
              + " dark energy. The head of the hammer is shaped"
              + " as a perfect black square which rests atop a long"
              + " steel shaft.\n");
            add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }) );
            add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
            break;
        case "darksteel head spiker":
            add_name( ({ "spiker", }) );
            add_adj( ({ "dark", "steel", "darksteel", "head" }) );
            set_long("Though the size and shape of this powerful"
              + " weapon alone would be enough to strike fear and"
              + " awe into most opponents, it is the strange power"
              + " which radiates from the malevolent dark steel which"
              + " makes up the enormous spikes that cover the"
              + " weapon that is truly fearsome.\n");
            add_prop(MAGIC_AM_MAGIC, ({ 60, "enchantment" }) );
            add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
            break;
        case "darksteel death stick":
            add_name( ({ "stick" }) );
            add_adj( ({ "dark", "steel", "darksteel", "death" }) );
            set_long("Whoever designed this weapon had one thing in"
              + " mind - absolute carnage. Every surface of the"
              + " weapon besides the gigantic leatherbound handle"
              + " is layered with long, dark, cruel iron barbs"
              + " and razors which resonate with dark energy."
              + " Simply wielding this thing would be"
              + " enough to make most people nervous, but to see it"
              + " swinging toward your face - disaster!\n");
            add_prop(MAGIC_AM_MAGIC, ({ 80, "enchantment" }) );
            add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
            break;
        case "sledgehammer of the colossus":
            add_name( ({ "hammer", "sledgehammer", "colossus" }) );
            add_adj( ({  "dark", "steel", "darksteel", "sledge",
                         "sledgehammer", "hammer", "of", "the",
                         "colossus" }) );
            set_long("This weapon can be described in one word -"
              + " terrifying! Its mighty shaft alone must weigh more"
              + " than the average human being. Mounted at its"
              + " top is an absolutely enormous driving head, barrel-"
              + "like in shape and size, with sheer edges and"
              + " hideous sharp ridges along each of the smashing"
              + " ends. You are basically staring at a gigantic"
              + " meat tenderizer!\n");
            add_prop(MAGIC_AM_MAGIC, ({ 100, "enchantment" }) );
            add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
            break;

        case "enormous dented bucket":
            add_name( ({ "bucket" }) );
            add_adj( ({ "enormous", "dented" }) );
            set_long("This bucket is about the size of a bathtub! Its"
              + " curved iron sides are dented and beaten from"
              + " heavy use as a bludgeoning device. Truly, this is"
              + " a proud weapon - as long as you are the worlds"
              + " dumbest ogre.\n");
            break;
        case "giant filthy shovel":
        default:
            add_name( ({ "shovel" }) );
            add_adj( ({ "giant", "filthy" }) );
            set_long("This looks like the worlds largest snow shovel!"
              + " Clearly, it has not been used for that purpose,"
              + " however. Its nearly four foot wide iron scoop is"
              + " coated with carbon and ash, as if it had been used"
              + " for shoveling coal. I suppose in the right hands,"
              + " it would also be a fairly nasty weapon.\n");
            break;

    }

    if (query_prop(MAGIC_AM_MAGIC))
    {
        add_prop(MAGIC_AM_ID_INFO, ({ 
            "The steel of this weapon has been magically enchanted"
          + " with the powers of darkness. When it strikes an"
          + " an enemy, it unleashes some these powers into their"
          + " flesh, causing extra harm. Moreover, this material,"
          + " known as Darksteel, is twice as dense as normal"
          + " steel, but only slightly heavier.\n", 30 }) );
       add_prop(OBJ_S_WIZINFO, 
            "The Army of Darkness is allowed to pay hefty fees"
          + " to achieve these magical weapons. Members are prevented"
          + " from wielding anything but two-handed clubs."
          + " Because of the extremely limited numbers of such"
          + " weapons in the game, these weapons are provided at"
          + " heavy platinum costs, as well as requiring the player"
          + " to collect and turn in to the forge magical weapons"
          + " that they collect but cannot use. Ask Gorboth for"
          + " more details if you need them.\n");

        /* These weapons cost a hefty amount both in terms of
         * magic credits (requiring the player to bring magic weapons
         * back to the guild to melt down to provide the metal
         * for their creation) and platinum coins. Moreover, they
         * never glow, and are thus unkeepable after an armageddon.
         * For this reason, lets assume that Darksteel is
         * extremely durable, and resistant to corrosion, breakage,
         * or dulling.
         */
        set_likely_dull(0);
        set_likely_corr(0);
        set_likely_break(0);
    }

    /* Now give the weapon some value, weight and volume          */
    /* use standard functions, randomize to hide actual WC values */
    /* These weapons are VERY heavy, but ogres can handle that.   */
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit, pen) + random(20) -10);
    add_prop(OBJ_I_WEIGHT, 10000 + ((Wep_Level * 1000) / 2)
      + (random(1000) - 1500));

    /* No one would buy such huge things. */
    add_prop(OBJ_M_NO_SELL, "No merchant would want such huge"
      + " items!\n");

    /* calculate volume from weight */
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);

    /* Designate wield and unwield effects. */
    set_wf(this_object());

} /* configure_it */


void
state_change(int hit, int pen)
{
    set_hit(hit);
    set_pen(pen);
 
    if (wielder)
        wielder->update_weapon(this_object());
}

/*
* Function:    wield_mes()
* Description: The message and any extra functions/mechanics to
*              the weapon when it's wielded.
*/
void
wield_mes()
{
    if (environment(this_object()) != wielder)
        return;
    
    wielder->catch_msg("This huge ogre weapon feels very unbalanced "
        + "in your hands.\n");
}

/*
* Function name:        wield
* Description  :        we only allow players with sufficient
*                       sword skill to wield this weapon
* Arguments    :        object wep - this object
* Returns      :        -1 : cannot wield
*                        0 : okay to wield
*/ 
mixed
wield(object what)
{
    int alt_hit, alt_pen;
    wielder = this_player();
    
    weapon_hit = this_object()->query_hit();
    weapon_pen = this_object()->query_pen();
	
    if (this_player()->query_race_name() == "ogre")
    {
        return 0;
    }
    else
    {	
        // Non-ogres cannot wield this ogre weapon effectively, and
        // the hitand pen of the weapon are modified accordingly.
        set_alarm(0.1, 0.0, "wield_mes");
        alt_hit = weapon_hit - 25;
        alt_pen = weapon_pen - 10;

        state_change(alt_hit, alt_pen);
    }
        
    return 0;
}

/*
* Function name: unwield
* Description  : This function might be called when someone tries to unwield
*                this weapon. To have this function called, use the function
*                set_wf().
* Arguments    : object obj - the weapon to stop wielding.
* Returns      : int  0 - the weapon can be unwielded normally.
*                     1 - unwield the weapon, but print no messages.
*                    -1 - do not unwield the weapon, print default messages.
*                string - do not unwield the weapon, use this fail message.
*/
mixed
unwield(object what)
{    
    if(weapon_hit && weapon_pen)     
        state_change(weapon_hit, weapon_pen);
    
    return 0;
}
