/*
 * blade.c
 *
 * An ancient blade, enchanted to be exceedingly light
 * and strong.
 */
#pragma strict_types

#define ID_SKILL  50
#define BASE_HIT  20
#define BASE_PEN  35

#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <macros.h>
#include <tasks.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/skills.h"

inherit "/std/weapon";

string *known_by;
static int is_magic;

public int
setup_magic()
{
    is_magic = 1;
    set_hit(BASE_HIT + 5);  /* How well sword hits. */
    set_pen(BASE_PEN + 10); /* How much damage does the */
                            /* sword do. */
    set_likely_corr(0);     /* It's magic gives 0% chance */
                            /* of corrosion. */
    set_likely_dull(0);     /* It's magic gives 0% chance */
                            /* of dulling. */
    set_likely_break(0);    /* It's magic gives 0% chance */
                            /* of breaking. */
    add_prop(OBJ_M_NO_BUY, 1);     /* Magic weapons cannot be */
                                   /* bought. */
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);  /* Identify this weapon */
                                         /* as magic. */
    add_prop(MAGIC_AM_MAGIC, ({40, "enchantment"}));
                                   /* Says the magic in this */
                                   /* weapon is a fairly strong */
                                   /* enchantment. */
    add_prop(OBJ_S_WIZINFO, "This is the Sword of Donham, a " +
        "magic sword with enhanced strength and reduced weight. " +
        "It can also be wielded either one or two handed, " +
        "though will be less effective wielded two-handed " +
        "by those without great dexterity and skill. This is " +
        "determined randomly, however, so a player will never " +
        "know if he's getting the one-handed penalty without " +
        "trial and error.\n");
    add_prop(MAGIC_AM_ID_INFO,
        ({"This weapon is very, very old, as is the enchantment " +
        "which fills it.\n", 25,
        "The enchantment which binds this weapon renders it " +
        "much stronger and lighter than any like it.\n", 50}));

  /* Update the player's combat object with new hit & pen */
  /* values if it's being wielded. */
    if (wielder)
        wielder->update_weapon(TO);

    return 1;
}

public int
setup_normal()
{
    is_magic = 0;
    set_hit(BASE_HIT);
    set_pen(BASE_PEN);

  /* Increase some liklihoods to default values in case the */
  /* sword was magic but reverted to normal. */
    set_likely_corr(10);     /* 10% chance of corrosion. */
    set_likely_dull(10);     /* 10% chance of dulling. */
    set_likely_break(10);    /* 10% chance of breaking. */

  /* Remove all magic props in case the sword was somehow */
  /* reverted to normal after being magic. */
    remove_prop(OBJ_M_NO_BUY);
    remove_prop(OBJ_I_IS_MAGIC_WEAPON);
    remove_prop(MAGIC_AM_MAGIC);  
    remove_prop(OBJ_S_WIZINFO);
    remove_prop(MAGIC_AM_ID_INFO);

  /* Update the player's combat object with new hit & pen */
  /* values if it's being wielded. */
    if (wielder)
        wielder->update_weapon(TO);

    return 1;
}

public int
knows_sword(mixed who)
{
    if (objectp(who))
        who = who->query_real_name();

    if (member_array(who, known_by) > -1)
        return 1;

    return 0;
}

public string
check_identity_short()
{
    if (knows_sword(TP) && is_magic)
        return "Sword of Donham";
    return "ancient steel longsword";
}

public string
check_identity_long()
{
    if (knows_sword(TP) && is_magic)
        return "This ancient weapon is the Sword of Donham, " +
            "first King of Calladon! ";
    return "";
}

public string
check_recognize()
{
    int skill = (TP->query_skill(SS_KHALAKHOR_LORE));

    if (!is_magic)
        return "";

  /* No check if this_player() has already recognized this */
  /* sword. */
    if (member_array(TP->query_real_name(), known_by) > -1)
        return "";

  /* See if the player recognizes this weapon. */
    if (skill >= ID_SKILL)
    {
        known_by += ({(TP->query_real_name())});
        return "Drawing on all of your knowledge of Khalakhor " +
            "lore and history, you recognize this weapon as " +
            "the Sword of Donham, the first king of Calladon!";
    }

    if (skill >= (ID_SKILL / 2))
    {
        return "You vaguely recall hearing something in Khalakhor " +
            "lore about a sword similar to this one, but the " +
            "exact legend escapes you for the moment.";
    }

    return "";
}

/*
 * Function name: check_magic_weight
 * Description  : Returns the weight of the sword. The magic
 *                version has a weight 1/3 the normal.
 * Arguments    : n/a 
 * Returns      : Weight as an integer.
 */
public int
check_magic_weight()
{
    if (is_magic)
        return 2000;
    return 6000;
}

/*
 * Function name: create_weapon
 * Description  : Turns this object into a weapon.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_weapon()
{
  /* First we'll set some stuff that's common to most */
  /* any object, a name. */
    set_name("longsword");
    add_name("sword");
    add_name("weapon");
    set_adj(({"ancient","steel"}));
    set_short("@@check_identity_short@@");
    set_long("@@check_identity_long@@" +
        "This magnificent-looking weapon appears " +
        "to be forged of some kind of steel, now darkened " +
        "and tarnished so that the long double-edged " +
        "blade appears almost black. The hilt is made of " +
        "the same material. The pommel is sculpted into " +
        "the shape of a lion's head, and the wide crosspiece " +
        "is engraved with an intricate pattern of weaving " +
        "lines. The long handle provides two-handed " +
        "wielding, though the weapon is light enough it " +
        "could be wielded with only one by a skilled " +
        "swordsman. @@check_recognize@@\n");

  /* Weapon is by default magic. */
    setup_magic();

  /* Next set some of the weapon variables to determine */
  /* what kind of weapon we're making. */
    set_pm(({-5,5,0}));     /* This sword slashes better */
                            /* it than impales */
    set_wt(W_SWORD);        /* This weapon is a sword. */
    set_dt(W_IMPALE | W_SLASH); /* This sword can do slash */
                                /* and impale damage. */
    set_hands(W_ANYH);      /* Can be wielded in any hand(s). */
    set_wf(TO);             /* Check this object for special */
                            /* code when it's wielded and */
                            /* unwielded. */

  /* Next we add a variety of properties. */
    add_prop(OBJ_I_WEIGHT, "@@check_magic_weight");
    add_prop(OBJ_I_VOLUME, 5000);  /* 5 litres of material */
                                   /* in this sword (a guess). */
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(BASE_HIT, BASE_PEN));

    known_by = ({});  /* Initiate the known_by array. */
}

public string
query_recover()
{
    return MASTER + ":DON" + implode(known_by,"$$") +
        "##" + is_magic + "HAM" +
        query_wep_recover();
}

public void
init_recover(string arg)
{
    string arg1,
           arg2;

    sscanf(arg, "DON%s%HAM%s", arg1, arg2);
    sscanf(arg1, "%s##%d", arg1, is_magic);
    known_by = explode(arg1, "$$");
    init_wep_recover(arg2);
}

/*
 * Function name: set_corroded (MASK)
 * Description  : Called to set a new corroded status
 *                in the weapon. Masked to make double-sure
 *                this weapon is never corroded.
 * Arguments    : corr - Integer, the new corrosion status.
 * Returns      : 0 always, to indicate no corrosion took
 *                place.
 */
public nomask int
set_corroded(int corr)
{
    if (is_magic)
        return 0;
    return ::set_corroded(corr);
}

/*
 * Function name: set_dull (MASK)
 * Description  : Called to set a new dull status
 *                in the weapon. Masked to make double-sure
 *                this weapon is never dulled.
 * Arguments    : corr - Integer, the new dull status.
 * Returns      : 0 always, to indicate no dulling took
 *                place.
 */
public nomask int
set_dull(int du)
{
    if (is_magic)
        return 0;
    return ::set_dull(du);
}

/*
 * Function name: remove_broken (MASK)
 * Description  : Called when this weapon is to be broken.
 *                Masked here to ensure this never happens.
 * Arguments    : silent - True if no messages to be printed
 *                         while breaking.
 * Returns      : n/a
 */
varargs nomask void
remove_broken(int silent = 0)
{
    if (is_magic)
        return;
    return ::remove_broken(silent);
}
