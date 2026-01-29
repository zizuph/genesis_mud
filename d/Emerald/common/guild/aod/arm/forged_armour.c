/*
 *  /d/Emerald/common/guild/aod/wep/forged_armour.c
 *
 *  This is the base file to be inherited by armours which have
 *  been forged by the Army of Darkness Smith.
 *
 *  Copyright (c) July 2006, by Cooper Sherry (Gorboth)
 *
 *  2019-01-15: Carnak
 *      These items will now recover, this was changed due to the implementation
 *      of item expiration
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

/* Definitions */
#define        ARM_CLASS  ( ({ 28, 28, 28, \
                               38, 38, 38, \
                               48, 51, 54, \
                               58, 58, 58  \
                          }) )
#define        ARM_SHORTS ( ({ "crude slab of scrap metal",           \
                               "huge iron can",                       \
                               "pair of dented iron tubs",            \
                               "enormous curtain of ringmail",        \
                               "monstrous iron skullcap",             \
                               "pair of gigantic chain leggings",     \
                               "darksteel ogre breastplate",          \
                               "pair of darksteel troll bracers",     \
                               "darksteel goliath helm",              \
                               "pair of titan's darksilver greaves", \
                               "deathplate of the behemoth",         \
                               "pair of vast darksilver arm-bands",     \
                            }) )

/* Global Variables */
public int         Arm_Level = 0;

/* Prototypes */
public void        create_forged_armour();
public void        create_armour();
public void        configure_it();
public mixed       wear(object obj);
public mixed       remove(object obj);

public void        set_arm_level(int i) { Arm_Level = i; }
public int         query_arm_level() { return Arm_Level; }


/*
 * Function name:        create_forged_armour
 * Description  :        a dummy function to be used by inheriting files
 */
public void
create_forged_armour()
{
} /* create_forged_armour */


/*
 * Function name:        create_armour
 * Description  :        set up the armour
 */
public void
create_armour()
{
    set_name("armor");
    add_name( ({ "armour", AOD_FORGED_ITEM }) );
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

    create_forged_armour();
    configure_it();
} /* create_armour */


/*
 * Function name:        configure_it
 * Description  :        set up all the properties of the weapon.
 */
public void
configure_it()
{
    int     arm_weight;
    int     oac = ARM_CLASS[Arm_Level] + random(3);
    string  short_desc = ARM_SHORTS[Arm_Level];

    set_short(short_desc);

    switch(short_desc)
    {
        case "crude slab of scrap metal":
            add_name( ({ "metal", "scrap", "slab" }) );
            add_adj( ({ "crude", "scrap", "of", "slab" }) );
            set_long("For a serious attempt at creating armour,"
              + " this example is comical at best. Someone has taken"
              + " a thick slab of metal, roughly four by four feet"
              + " in size, and fastened a huge rope to each of the"
              + " top two corners, apparently to allow one to"
              + " hang this around their neck. For anyone other"
              + " than a giant, though, this would be nothing more"
              + " than an torturous burden!\n");
            arm_weight = 24000;
            set_at(TS_CHEST);
            break;
        case "huge iron can":
            add_name( ({ "can", "helm", "helmet" }) );
            add_adj( ({ "huge", "iron", "garbage" }) );
            set_long("Anyone of even medium intelligence would instantly"
              + " recognize this ridiculous excuse for a helmet as"
              + " nothing more than a thick metal garbage can that"
              + " has been turned upside down and cut open on one side"
              + " for the face. Of course, you'd have to be"
              + " some sort of giant for this to fit your head, in which"
              + " case it would probably protect your skull.\n");
            arm_weight = 2100;
            set_at(TS_HEAD);
            break;
        case "pair of dented iron tubs":
            add_name( ({ "tub", "greaves", "leggings", "pair" }) );
            add_adj( ({ "dented", "iron" }) );
            set_pshort("pairs of dented iron tubs");
            set_long("Is this really armour? Someone has apparently"
              + " taken some huge iron wash tubs, cut them down a"
              + " bit, and then connected them with strips of"
              + " leather to form unbelievably crude leggings. They"
              + " look like they were made for someone who is about"
              + " fifteen feet tall!\n");
            arm_weight = 7200;
            set_at(TS_LEGS);
            break;
        case "enormous curtain of ringmail":
            add_name( ({ "mail", "ringmail", "curtain", "coat" }) );
            add_adj( ({ "enormous", "curtain", "of", "ring" }) );
            set_long("This coat of mail is staggeringly huge! Tens of"
              + " thousands of linked rings have been set together to"
              + " make a fabric of metal so large, that an average"
              + "-sized human could pitch a tent beneath this thing."
              + " I suppose if you were some sort of giant, it could"
              + " come in quite handy.\n");
            arm_weight = 6000;
            set_at(TS_CHEST);
            break;
        case "monstrous iron skullcap":
            add_name( ({ "helm", "helmet", "skullcap", "cap" }) );
            add_adj( ({ "monstrous", "iron" }) );
            set_long("Massively thick iron has been forged into a"
              + " skullcap of frightening proportions. Though clearly"
              + " intended for use protecting the head, anyone other"
              + " than a giant ogre would have more luck using this"
              + " as an end table.\n");
            arm_weight = 2400;
            set_at(TS_HEAD);
            break;
        case "pair of gigantic chain leggings":
            add_name( ({ "leggings", "greaves", "pair" }) );
            add_adj( ({ "gigantic", "chain" }) );
            set_pshort("pairs of gigantic chain leggings");
            set_long("Enormous sheets of linked iron rings have been"
              + " fit together to form leggings - for some kind of"
              + " giant, at least! These leggings look like they"
              + " could fit on an elephant!\n");
            set_at(TS_LEGS);
            arm_weight = 5700;
            break;
        case "darksteel ogre breastplate":
            add_name( ({ "plate", "breastplate", "mail" }) );
            add_adj( ({ "plate", "dark", "steel", "darksteel", "breast",
                        "ogre" }) );
            set_long("The massive bulk of this huge metal breastplate"
              + " crackles and gleams with dark energy. It looks to have"
              + " been built for some kind of titan, for no normal race"
              + " is born of this size.\n");
            add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }) );
            add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
            set_at(TS_CHEST);
            arm_weight = 24000;
            break;
        case "pair of darksteel troll bracers":
            add_name( ({ "bracers" }) );
            add_adj( ({ "pair", "of", "dark", "steel", "darksteel",
                        "troll" }) );
            set_pshort("pairs of darksteel troll bracers");
            set_long("These things are massive! The"
              + " metal from which this armour has been forged is not"
              + " only frighteningly thick, but crackling with some"
              + " fearful dark energy. While clearly designed to be"
              + " strapped to gigantic arms, they would probably"
              + " be more appropriately used by any normal-sized"
              + " humanoid as a table-top!\n");
            add_prop(MAGIC_AM_MAGIC, ({ 60, "enchantment" }) );
            add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
            set_at(TS_LARM|TS_RARM);
            arm_weight = 4800;
            break;
        case "darksteel goliath helm":
            add_name( ({ "helm", "helmet", }) );
            add_adj( ({ "dark", "steel", "darksteel", "goliath" }) );
            set_long("Even without the twisted spikes of gleaming"
              + " dark metal which pulsate with malevolent energy"
              + " protruding from every inch of its massive bulk,"
              + " the sheer size of this hideous helmet would strike"
              + " fear and awe into the heart of most observers."
              + " Anyone huge enough to wear this monstrosity would"
              + " end up looking like a living wrecking ball!\n");
            add_prop(MAGIC_AM_MAGIC, ({ 80, "enchantment" }) );
            add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
            set_at(TS_HEAD);
            arm_weight = 3500;
            break;
        default:
//      case "fullplate of the behemoth":
//          add_name( ({ "plate", "fullplate", "behemoth" }) );
//          add_adj( ({  "dark", "steel", "darksteel", "full",
//                       "fullplate", "plate", "of", "the",
//                       "behemoth" }) );
//          set_long("Even without a wearer, this armour is the stuff"
//            + " of nightmares! More than 13 feet from the base of"
//            + " its leggings to the collar of its breastplate, it"
//            + " looks like it could provide spectacular protection"
//            + " to a true Goliath. For anyone else, it looks meant"
//            + " only to inspire fear and trembling. Its entire"
//            + " surface is composed of vibrantly dark steel which"
//            + " positively hums with arcane energy.\n");
//          add_prop(MAGIC_AM_MAGIC, ({ 100, "enchantment" }) );
//          add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
//          set_at(A_TORSO|A_L_ARM|A_R_ARM|A_LEGS);
//          arm_weight = 36000;
//          break;
        case "pair of titan's darksilver greaves":
            add_name( ({ "leggings", "greaves", "pair" }) );
            add_adj( ({ "titans", "titan's", "silver",
                        "darksilver", "dark", "chain" }) );
            set_pshort("pairs of gigantic chain greaves");
            set_long("Huge rings of pure darksilver have been"
              + " fit together to form armour - for some kind of"
              + " giant, at least! These greaves look like they"
              + " could fit around a medium sized tree trunk!\n");
            add_prop(MAGIC_AM_MAGIC, ({ 100, "enchantment" }) );
            add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
            set_at(TS_LEGS);
            arm_weight = 6000;
            break;
        case "deathplate of the behemoth":
            add_name( ({ "plate", "deathplate", "behemoth" }) );
            add_adj( ({  "dark", "steel", "darksilver", "full",
                         "breastplate", "plate", "of", "the",
                         "behemoth" }) );
            set_long("The massive bulk of this huge darksilver deathplate"
              + " crackles and gleams with mystic power. It looks to have"
              + " been built for some kind of titan, for no normal race"
              + " is born of this size.\n");
            add_prop(MAGIC_AM_MAGIC, ({ 100, "enchantment" }) );
            add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
            set_at(TS_CHEST);
            arm_weight = 25000;
            break;
        case "pair of vast darksilver arm-bands":
            add_name( ({ "bands", "arm-bands" }) );
            add_adj( ({ "pair", "of", "dark", "silver", "darksilver",
                        "vast", "arm" }) );
            set_pshort("pairs of vast darksilver arm-bands");
            set_long("Fearsome spear-length spikes protrude from the"
              + " surface of these truly enormous arm-bands. The"
              + " metal from which this armour has been forged is not"
              + " only frighteningly thick, but crackling with some"
              + " fearful dark energy. While clearly designed to be"
              + " strapped to gigantic arms, they would probably"
              + " be more appropriately used by any normal-sized"
              + " humanoid as a kite shield!\n");
            add_prop(MAGIC_AM_MAGIC, ({ 100, "enchantment" }) );
            add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
            set_at(TS_LARM|TS_RARM);
            arm_weight = 5000;
            break;
    }

    if (query_prop(MAGIC_AM_MAGIC))
    {
       add_prop(MAGIC_AM_ID_INFO, ({ 
            "The steel of this armour has been magically enchanted"
          + " with the powers of darkness. It provides excellent"
          + " added protection. Moreover, this material,"
          + " known as Darksteel, is twice as dense as normal"
          + " steel, but only slightly heavier.\n", 30 }) );
       add_prop(OBJ_S_WIZINFO, 
            "Members of the Army of Darkness, being Ogres, are"
          + " unable to wear normal Genesis armour. These armours"
          + " which are crafted for them in the forge of the Army"
          + " of Darkness can be imbued with magic powers to"
          + " achieve high AC levels similar to items found by"
          + " other players throughout the normal game. However,"
          + " to prevent Army members from easily obtaining high"
          + " AC armours and wearing them at all times, purchasing"
          + " them from the forge comes at a very high platinum"
          + " and forge credit cost. Ask Gorboth for more information"
          + " if you require further explanation.\n");

        /* These armours cost a hefty amount both in terms of
         * magic credits (requiring the player to bring magic items
         * back to the guild to melt down to provide the metal
         * for their creation) and platinum coins. Moreover, they
         * never glow, and are thus unkeepable after an armageddon.
         * For this reason, lets assume that Darksteel is
         * extremely durable, and resistant to breakage.
         */
        set_likely_break(0);
        set_likely_cond(0);
    }

    set_ac(ARM_CLASS[Arm_Level] + random(3));
    set_am( ({ -2, -1, 3 }) );
    set_wf(this_object());

    /* Now give the armour some value, weight and volume          */
    /* use standard functions, randomize to hide actual AC values */
    /* These armours are VERY heavy, but ogres can handle that.   */
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(oac) + random(20) -10);
    add_prop(OBJ_I_WEIGHT, (arm_weight * 2) + (random(1000) - 1500));

    /* No one would buy such huge things. */
    add_prop(OBJ_M_NO_SELL, "No merchant would want such huge"
      + " items!\n");

    /* This armour is wearable by ogres, and only ogres. It is    */
    /* also the _only_ type of armour ogres may wear.             */
    add_prop(AOD_WEAR_PROP, 1);

    /* calculate volume from weight */
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
} /* configure_it */



/*
 * Function name:        wear
 * Description  :        only allow ogres to wear this massive armour
 * Arguments    :        object obj - this_object
 * Returns      :        0 -- allow to wear
 *                       1 -- not an ogre, fail
 */
public mixed
wear(object obj)
{
    object  tp = environment(this_object());

    if (!living(tp))
    {
        return 0;
    }

    if (tp->query_guild_name_occ() == GUILD_NAME)
    {
        return 0;
    }

    return "Wear this massive thing? You could more likely"
      + " take a nap under it! Whatever creature was intended to wear"
      + " this piece of equipment is more than twice your height.\n";

    return 1;
} /* wear */


/*
 * Function name:        remove
 * Description  :        called when the player removes
 *                       the armour
 * Arguments    :        object obj - this_object()
 * Returns      :        0
 */
public mixed
remove(object obj)
{
    object  tp = this_object()->query_worn();

    if (!living(tp))
    {
        return 0;
    }

    return 0;
} /* remove */
