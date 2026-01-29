/*
 *  IGARD_ARM + "i_besthalberd.c"
 *  Larger Isengard Axe
 *    Last modified by Alto, 12 October 2001
 * 
 * Modification log:
 * Rohim 2002-11-09      Modified did_hit to handle parries as dodges.
 * 
 *
 */

#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";


#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#include <options.h>
#include "../igard_defs.h"

#define HIT 40
#define PEN 40

int     more_parry;

public void
create_weapon()
{
    set_name(({"halberd", "polearm"}));
    set_pname("halberds");
    add_pname("polearms");
    set_short("ivory rough-edged halberd");
    set_pshort("ivory rough-edged halberds");
    set_long("The handle of this halberd is made from ivory and fashioned into "
        + "the likeness of two great white hands. A sturdy wooden pole projects "
        + "from the handle, where a mighty rough-edged blade is lashed. One "
        + "side of the blade has a roughened edge for cutting as well as tearing, "
        + "while the other side is narrow for gouging. It is almost "
        + "perfectly balanced, and would be lethal in the hands of one skilled "
        + "with polearms.\n");
    add_item(({"handle", "hands", "ivory", "white hands"}), "The handle of the "
        + "ivory rough-edged halberd is made from ivory and resembles two large "
        + "white hands, held protectively over the hands of the wielder.\n");

    set_adj("ivory");
    add_adj("rough-edged");

	   set_hit(HIT);
   	set_pen(PEN);
   	set_wt(W_POLEARM);
   	set_dt(W_IMPALE|W_SLASH);
   	set_hands(W_BOTH);
   	set_wf(TO);

    add_prop(OBJ_I_WEIGHT,
	       (F_WEIGHT_DEFAULT_WEAPON(40, W_POLEARM) + random(500) + 1000));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(40,40)+random(400)-100);

   	add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   	add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }));
   	add_prop(MAGIC_AM_ID_INFO, ({ "This halberd resonates a sense of "
        + "protection.\n", 20, "When wielded, this halberd can increase "
        + "the ability of the wielder to parry blows.\n", 40 }));
	   add_prop(OBJ_S_WIZINFO, "This halberd is wielded by a limited number "
        + "of NPCs in Isengard, in the Gondor domain. It adds a value of "
        + "15 to the parry skill of the wielder when wielded, and removes "
        + "that value when unwielded.\n");
}


/*
 * Function     : wield
 * Description  : Wield a weapon
 * Arguments    : Object what - The weapon to wield
 * Returns      : string - error message (weapon not wielded)
 *                1 - success (weapon wielded)
 */
public mixed
wield(object what)
{
    int level;

    /* Wield description. */
    wielded = 1;

    say(QCTNAME(TP) + " inserts " + POSSESSIVE(TP)
        + " hands into the handle of the " + short() + ". " + CAP(PRONOUN(TP))
        + " suddenly seems rather uncomfortable.\n");
    write("As you insert your hands into the handle of the "
        + short() + ", you feel the ivory hands close about your own. This "
        + "may reduce the risk of it slipping from your hands in combat, but "
        + "the grip of the ivory hands makes you uncomfortable nonetheless.\n");

    if (TP->query_npc())
    {
    TP->add_prop("_ranger_i_not_disarm", 1);
    }

    more_parry = 15;
    if ((TP->query_skill(23) + more_parry) > 100)
    {
        more_parry = (100-(TP->query_skill(23)));
    }
    TP->set_skill_extra(23, (TP->query_skill_extra(23) + more_parry));

    return 1;
}

/* 
 * Function    : unwield
 * Description : Unwield a weapon
 * Arguments   : object what - the weapon to unwield
 */
public mixed
unwield(object what)
{
    set_this_player(wielder);

    /* Unwield description. */
    if (wielder)
    {
        say(QCTNAME(this_player()) + " unwields the " + short() + " and " +
            "relaxes visibly.\n", ({wielder}));
        write("You withdraw your hands from the " + short() + " and relax "
            + "now that the "
            + "ivory hands on the handle are no longer clutching yours.\n");
    }

    if (TP->query_npc())
    {
    TP->remove_prop("_ranger_i_not_disarm");
    }

    wielder->set_skill_extra(23,(wielder->query_skill_extra(23) - more_parry));

    return 1;
}


public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    object wielder = query_wielded();
    string wmess = "", emess = "", omess = "", pole = short();
    string foe = enemy->query_the_name(wielder);
    string Hero = wielder->query_The_name(enemy);
    string hero = wielder->query_the_name(enemy);
    string his = wielder->query_possessive();
    string he = wielder->query_pronoun();
    string her = enemy->query_possessive();
    string she = enemy->query_pronoun();

    switch(phurt)
    {
    case -1:
    case -2:
        if (!wielder->query_npc() &&
          !wielder->query_option(OPT_GAG_MISSES))
        {
            wmess = ("You swing the " + pole + " high over your head and "
                + "hack downward at " + foe + ". You miss by a mile and the "
                + pole + " rings against the ground.\n");
        }

        if (interactive(enemy) && 
          !enemy->query_option(OPT_GAG_MISSES))
        {

            emess = (Hero + " swings " + his + " " + pole + " high over "
                + his + " head and hacks downward at you. " + CAP(he) 
                + " misses by a mile and the " + pole + " rings against "
                + "the ground.\n");
        }

        wielder->tell_watcher_miss(QCTNAME(wielder) + " swings the " + pole 
            + " high over " + his + " head and hacks downward at "
            + foe + ". " + CAP(he) + " misses by a mile and the " + pole
            + " rings against the ground.\n", enemy, enemy);
            break;

    case 0:
        if (!wielder->query_npc() &&
          !wielder->query_option(OPT_GAG_MISSES))
        {
            wmess = ("You swipe your " + pole + " through the air and "
            + "almost hit " + foe + " on " + her + " " + hdesc + ".\n");
        }

        if (interactive(enemy) && 
          !enemy->query_option(OPT_GAG_MISSES))
        {
            emess = (Hero + " swipes " + his + " " + pole + " through "
            + "the air and almost hits you on the " + hdesc + ".\n");
        }

        wielder->tell_watcher_miss(QCTNAME(wielder) + " swipes " + his + " " 
            + pole + " through the air and almost hits " + foe + " on " + her 
            + " " + hdesc + ".\n", enemy, enemy);
            break;

    case 1..5:
        wmess = ("You jab the " + pole + " at " + foe + ", searching for "
            + "weaknesses, and score a small nick on " + her + " " + hdesc + ".\n");
        emess = (Hero + " jabs " + his + " " + pole + " at you, searching for "
            + "weaknesses, and scores a small nick on your " + hdesc + ".\n");
        omess = (QCTNAME(wielder) + " jabs " + his + " " + pole + " at " 
            + foe + ", searching for weaknesses, and scores a small nick on " 
            + her + " " + hdesc + ".\n");
        break;

    case 6..10:
        wmess = ("Your " + pole + " makes a small cut into the " + hdesc
            + " of " + enemy->query_the_name(wielder) + ".\n");
        emess = (wielder->query_The_possessive_name(enemy) + " " 
            + pole + " makes a small cut into your " + hdesc + ".\n");
        omess = (QCTPNAME(wielder) + " " + pole 
            + " makes a small cut into the " + hdesc + " of " 
            + QTNAME(enemy) + ".\n");
        break;

    case 11..20:
        wmess = ("You sweep the " + pole + " over your right shoulder and "
            + "swing it at " + foe + " with all your might, opening a wound "
            + "in " + her + " " + hdesc + ".\n");
        emess = (Hero + " sweeps the " + pole + " over " + his + " right "
            + "shoulder and swings it at you with all " + his + " might, "
            + "opening a wound in your " + hdesc + ".\n");
        omess = (QCTNAME(wielder) + " sweeps the " + pole + " over " + his 
            + " right " + "shoulder and swings it at " + foe + " with all " + his
            + " might, opening a wound in " + her + " " + hdesc + ".\n");
        break;

    case 21..40:
        wmess = ("Blood fountains everywhere as you watch your " 
            + pole + " slice deeply through the " + hdesc + " of "
            + enemy->query_the_name(wielder) + ".\n");
        emess = (wielder->query_The_possessive_name(enemy) + " " 
            + pole + " slices deeply through your " + hdesc + ". Blood "
            + "fountains everywhere.\n");
        omess = (QCTPNAME(wielder) + " " + pole 
            + " slices deeply through the " + hdesc + " of " 
            + QTNAME(enemy) + ". Blood fountains everywhere.\n");
        break;

    case 41..60:
        wmess = ("You swing the " + pole + " high over your head and hack "
            + "downward at " + foe + ", where it bites deeply into " + her
            + " " + hdesc + ".\n");
        emess = (Hero + " swings " + his + " " + pole + " high over " + his
            + " head and hacks downward at you, where it bites deeply "
            + "into your " + hdesc + ".\n");
        omess = (QCTNAME(wielder) + " swings " + his + " " + pole + " high over " 
            + his + " head and hacks downward at " + foe + ", where it bites "
            + "deeply into " + her + " " + hdesc + ".\n");
        break;

    case 61..90:
        wmess = ("Bringing the " + pole + " up from the ground, you impale "
            + foe + ", ripping away at " + her + " intestines as you withdraw the "
            + "halberd.\n");
        emess = (Hero + " brings the " + pole + " up from the ground and "
            + "impales you, ripping away at your intestines as " + he 
            + " withdraws the halberd.\n");
        omess = (QCTNAME(wielder) + " brings the " + pole 
            + " up from the ground and "
            + "impales " + foe + ", ripping away at " + her + " intestines as " 
            + he + " withdraws the halberd.\n");
        break;

    default:
        wmess = ("You swivel the " + pole + " in your hands, aiming it "
            + "directly at " + foe + ". With a quick jab, you drive it "
            + "completely through " + her + " body.\n");
        emess = (Hero + " swivels the " + pole + " in " + his + " hands, "
            + "aiming it directly at you. With a quick jab, " + he
            + " drives it completely through your body.\n");
        omess = (QCTNAME(wielder) + " swivels the " + pole + " in " + his 
            + " hands, "
            + "aiming it directly at " + foe + ". With a quick jab, "
            + he + " drives it completely through " + her + " body.\n");
        break;

    }

    wielder->catch_tell(wmess);
    enemy->catch_tell(emess);
    wielder->tell_watcher(omess, enemy, enemy);

    hits++;

    if (F_WEAPON_CONDITION_DULL(hits, wep_pen, likely_dull))
    {
        hits = 0;
        set_dull(query_dull() + 1);
    }

    return 1;
}

