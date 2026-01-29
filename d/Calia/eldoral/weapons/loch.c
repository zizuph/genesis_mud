/*
 * lochaber1.c
 *
 * A moderately straight-forward weapon. Non-magical, but does
 * extra damage for blows to the head and/or body, based on current
 * damage type. The breakdown is as follows, where 'dam' is the amount
 * of damaged done to the target, as passed to the did_hit() function.
 *
 * Case 1: Slash to the head. Extra damage = random(dam);
 * Case 2: Impale to the body. Extra damage = random(dam);
 * Case 3: Impale to the head. Extra damage = random(dam) + random(dam);
 *
 * The weapon also has different messages for hits/misses, depending
 * on the current damage type (can be impale or slash).
 *
 * Khail - Feb 19/97
 */
#pragma strict_types

#include "defs.h"
#include <filter_funs.h>

#define HIT 25
#define PEN 30

#define DO_DEBUG

#ifdef DO_DEBUG
#define DEBUG(s) log_file("eldoral/debug_lochaber",s,10000)
#endif

inherit "/std/weapon";

/*
 * Function name: create_weapon
 * Description  : Creates the weapon, obviously.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_weapon()
{
    set_name("axe");
    add_name("lochaber");
    add_name("axe");
    add_name("wrath");
    set_adj("brutal");
    add_adj("iron");
    add_adj("lochaber");
    set_short("brutal iron lochaber axe"); 
    set_pshort("brutal iron lochaber axes"); 
    set_long("The iron lochaber axe is a vicious-" +
        "looking weapon. Almost more like a halberd " +
        "than an axe, the head is mounted atop a " +
        "long handle made from wire-wrapped wood. " +
        "The head itself is comprised of a sharply " +
        "curved axe blade, the end of which curls " +
        "to a sharp point. It almost looks like an " +
        "ox-horn that has been forged from iron and " +
        "hammered flat. On the back of the head, " +
        "a brutally sharp hook gleams dully, like " +
        "the beak of some predatory bird. The fact " +
        "that the head seems to be made of raw iron " +
        "also seems a bit strange, making the weapon " +
        "very difficult to wield, but the damage from " +
        "the impact would be staggering. But " +
        "even beyond its appearance, there's " +
        "something very odd about this weapon that " +
        "you can't quite put into words.\n");
    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_AXE);
    set_hands(W_BOTH);
    set_dt(W_SLASH | W_IMPALE);
    set_wf(TO);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_WEIGHT, 2*F_WEIGHT_DEFAULT_WEAPON(HIT, W_AXE));
    add_prop(OBJ_I_VOLUME, 7500 / 5);
    setuid(); seteuid(getuid());
}

/*
 * Function name: did_hit (MASK)
 * Description  : Here, we mask this function to do extra damage
 *                for certain hits, as well as customize hit/miss
 *                messages. See 'sman did_hit' for additional info.
 * Arguments    : See 'sman did_hit'
 * Returns      : See 'sman did_hit'
 */
public int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
    int phit, int dam)
{
    int temp,
        left_hp,
        init_hp;
    string mess1,   /* Wielder message  */
           mess2,   /* Target message   */
           mess3;   /* Watcher messages */
    
   /* First off, call back to ::did_hit, otherwise, this */
   /* weapon will never dull. */
    ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);

    left_hp = enemy->query_hp();
    if (!dt || dt == W_SLASH)
    {
      /* Extra damage for a slash to the head. */
        if (hdesc == "head" && dam)
        {
          /* Get additional damage */
            temp = random(dam);
          /* Inflict additional damage */
            enemy->heal_hp(-temp);
          /* Determine pre-attack hp of enemy */
            init_hp = 100 * dam / phurt;
          /* Get a new phurt based on additional damage */
            phurt = 100 * (dam + temp) / init_hp;
        }

      /* Now, generate a message for slash attacks based on the */
      /* 'phurt' percentage of damage done. */
        switch(phurt)
        {
          /* Hard miss. */
            case -1:
                mess1 = "You swing the lochaber axe heavily, but " +
                    "slice through nothing but the air above " +
                    QTNAME(enemy) + "'s head.\n";
                mess2 = wielder->query_The_name(enemy) + " swings " +
                    wielder->query_possessive() + " lochaber axe heavily " +
                    "towards you, but slices nothing but the air " +
                    "over your head.\n";
                mess3 = QCTNAME(wielder) + " swings " +
                    wielder->query_possessive() + " lochaber axe heavily " +
                    "towards " + QTNAME(enemy) + ", but slices through " +
                    "nothing except the air above " + 
                    enemy->query_possessive() + " head.\n";
                break;

          /* Only a couple hp damage, if that. */
            case 0:
                mess1 = "You swing the lochaber axe deftly at " +
                    QTNAME(enemy) + "'s " + hdesc + ", but miss your " +
                    "mark, doing nothing but a painless scratch of " +
                    "damage.\n";
                mess2 = wielder->query_The_name(enemy) + " swings " + 
                    wielder->query_possessive() + " lochaber axe " +
                    "deftly at your " + hdesc + ", but misses " +
                    wielder->query_possessive() + " " +
                    "mark, doing nothing but a painless scratch of " +
                    "damage.\n";
                mess3 = QCTNAME(wielder) + " swings " +
                    wielder->query_possessive() + " lochaber axe " +
                    "deftly at " + QTNAME(enemy) + "'s " + hdesc + ", " +
                    "but misses " + wielder->query_possessive() + " mark, " +
                    "inflicting nothing but a painless scratch of " +
                    "damage.\n";
                break;

            case 1..10:
                mess1 = "Your lochaber axe slices a thin wound across " +
                    QTNAME(enemy) + "'s " + hdesc + ".\n";
                mess2 = wielder->query_The_name(enemy) + 
                    "'s lochaber axe slices a " +
                    "thin wound across your " + hdesc + ".\n";
                mess3 = QCTNAME(wielder) + "'s lochaber axe slices a " +
                    "thin wound across " + QTNAME(enemy) + "'s " +
                    hdesc + ".\n";
                break;

            case 11..30:
                mess1 = "You slash a bloody wound across " +
                    QTNAME(enemy) + "'s " + hdesc + " with your " +
                    "lochaber axe.\n";
                mess2 = wielder->query_The_name(enemy) + 
                    " slashes a bloody wound " +
                    "across your " + hdesc + " with " +
                    wielder->query_possessive() + " lochaber axe.\n";
                mess3 = QCTNAME(wielder) + " slashes a bloody wound " +
                    "across " + QTNAME(enemy) + "'s " + hdesc + " " +
                    "with " + wielder->query_possessive() + " " +
                    "lochaber axe.\n";
                break;

            case 31..60:
                mess1 = "Your lochaber axe slashes a deep, jagged " +
                    "wound across " + QTNAME(enemy) + "'s " +
                    hdesc + ".\n";
                mess2 = wielder->query_The_name(enemy) + 
                    "'s lochaber axe " +
                    "slashes a deep, jagged wound across your " +
                    hdesc + ".\n";
                mess3 = QCTNAME(wielder) + "'s lochaber axe " +
                    "slashes a deep, jagged wound across " +
                    QTNAME(enemy) + "'s " + hdesc + ".\n";
                break;

            case 61..90:
                mess1 = "Your lochaber axe bites deeply into " +
                    QTNAME(enemy) + "'s " + hdesc + ", right " +
                    "down to the bone.\n";
                mess2 = wielder->query_The_name(enemy) + 
                    "'s lochaber axe bites " +
                    "deeply into your " + hdesc + ", right down " +
                    "to the bone.\n";
                mess3 = QCTNAME(wielder) + "'s lochaber axe bites " +
                    "deeply down into " + QTNAME(enemy) + "'s " +
                    hdesc + ", right down to the bone.\n";
                break;

            case 91..99:
                mess1 = "You drive a massive blow home with your " +
                    "lochaber axe, inflicting a shocking slash " +
                    "through muscle and nerves to " + QTNAME(enemy) +
                    "'s " + hdesc + ".\n";
                mess2 = wielder->query_The_name(enemy) + 
                    " drives a massive " +
                    "blow home with " + wielder->query_possessive() +
                    " lochaber axe, inflicting a shocking slash " +
                    "through muscle and nerves to your " + hdesc +
                    ".\n";
                mess3 = QCTNAME(wielder) + " drives a massive " +
                    "blow home with " + wielder->query_possessive() +
                    " lochaber axe, inflicting a shocking slash " +
                    "through muscle and nerves to your " + hdesc +
                    ".\n";
                break;

          /* Damage done >= 100%, fatal blow. */
            default:
                mess1 = "Your lochaber axe screams through the " +
                    "air and chops completely through " +
                    QTNAME(enemy) + "'s " + hdesc + ", killing " +
                    enemy->query_objective() + " instantly!\n";
                mess2 = "You see a lochaber axe coming for your " +
                    hdesc + ", then blackness...\n";
                mess3 = QCTNAME(wielder) + "'s lochaber axe " +
                    "screams through the air and chops " +
                    "completely through " + QTNAME(enemy) +
                    "'s " + hdesc + ", killing " +
                    enemy->query_objective() + " instantly!\n";
        }
    }

  /* Impale messages. Extra damage to head and body. */
    else
    {
      /* Extra damage if target's head was impaled. */
        if (hdesc == "head" && dam)
        {
            temp = random(dam) + random(dam);
            enemy->heal_hp(-temp);
          /* Determine pre-attack hp of enemy */
            init_hp = 100 * dam / phurt;
          /* Get a new phurt based on additional damage */
            phurt = 100 * (dam + temp) / init_hp;
        } 
     
      /* Extra damage if target's body was impaled. */
        else
        if (hdesc == "body" && dam)
        {
            temp = random(dam);
            enemy->heal_hp(-temp);
          /* Determine pre-attack hp of enemy */
            init_hp = 100 * dam / phurt;
          /* Get a new phurt based on additional damage */
            phurt = 100 * (dam + temp) / init_hp;
        } 

      /* Generate a proper hit/miss message for an impaling attack */
      /* based on the 'phurt' percentage of damage done. */
        switch (phurt)
        {
            case -1:
                mess1 = "You drive the lochaber axe heavily, but " +
                    "punch through nothing but the air above " +
                    QTNAME(enemy) + "'s head.\n";
                mess2 = wielder->query_The_name(enemy) + " drives " +
                    wielder->query_possessive() + " lochaber axe heavily " +
                    "towards you, but punches nothing but the air " +
                    "over your head.\n";
                mess3 = QCTNAME(wielder) + " drives " +
                    wielder->query_possessive() + " lochaber axe heavily " +
                    "towards " + QTNAME(enemy) + ", but punches through " +
                    "nothing except the air above " + 
                    enemy->query_possessive() + " head.\n";
                break;
            case 0:
                mess1 = "You stab the lochaber axe deftly at " +
                    QTNAME(enemy) + "'s " + hdesc + ", but miss your " +
                    "mark, doing nothing but a painless nudge of " +
                    "damage.\n";
                mess2 = wielder->query_The_name(enemy) + " stabs " + 
                    wielder->query_possessive() + " lochaber axe " +
                    "deftly at your " + hdesc + ", but misses " +
                    wielder->query_possessive() + " " +
                    "mark, doing nothing but a painless nudge of " +
                    "damage.\n";
                mess3 = QCTNAME(wielder) + " stabs " +
                    wielder->query_possessive() + " lochaber axe " +
                    "deftly at " + QTNAME(enemy) + "'s " + hdesc + ", " +
                    "but misses " + wielder->query_possessive() + " mark, " +
                    "inflicting nothing but a painless nudge of " +
                    "damage.\n";
                break;
            case 1..10:
                mess1 = "Your lochaber axe punches a small bruise on " +
                    QTNAME(enemy) + "'s " + hdesc + ".\n";
                mess2 = wielder->query_The_name(enemy) + 
                    "'s lochaber axe punches a " +
                    "small bruise on your " + hdesc + ".\n";
                mess3 = QCTNAME(wielder) + "'s lochaber axe punches a " +
                    "small bruise on " + QTNAME(enemy) + "'s " +
                    hdesc + ".\n";
                break;
            case 11..30:
                mess1 = "You punch a bloody wound in " +
                    QTNAME(enemy) + "'s " + hdesc + " with your " +
                    "lochaber axe's beak.\n";
                mess2 = wielder->query_The_name(enemy) + 
                    " punches a bloody wound " +
                    "in your " + hdesc + " with " +
                    wielder->query_possessive() + " lochaber axe's " +
                    "beak.\n";
                mess3 = QCTNAME(wielder) + " punches a bloody wound " +
                    "in " + QTNAME(enemy) + "'s " + hdesc + " " +
                    "with " + wielder->query_possessive() + " " +
                    "lochaber axe's beak.\n";
                break;
            case 31..60:
                mess1 = "Your lochaber axe's beak stabs a deep, " +
                    "jagged puncture into " + QTNAME(enemy) + "'s " +
                    hdesc + ".\n";
                mess2 = wielder->query_The_name(enemy) + 
                    "'s lochaber axe's beak " +
                    "stabs a deep, jagged puncture into your " +
                    hdesc + ".\n";
                mess3 = QCTNAME(wielder) + "'s lochaber axe's beak " +
                    "stabs a deep, jagged puncture into " +
                    QTNAME(enemy) + "'s " + hdesc + ".\n";
                break;
            case 61..90:
                mess1 = "Your lochaber axe's beak impales deeply " +
                    "into " + QTNAME(enemy) + "'s " + hdesc + ", right " +
                    "down to the bone.\n";
                mess2 = wielder->query_The_name(enemy) + 
                    "'s lochaber axe's beak " +
                    "impales deeply into your " + hdesc + ", right " +
                    "down to the bone.\n";
                mess3 = QCTNAME(wielder) + "'s lochaber axe's beak " +
                    "impales deeply down into " + QTNAME(enemy) + 
                    "'s " + hdesc + ", right down to the bone.\n";
                break;
            case 91..99:
                mess1 = "You drive a massive blow home with your " +
                    "lochaber axe's beak, inflicting a shocking " +
                    "puncture wound through muscle and nerves to " +
                    QTNAME(enemy) + "'s " + hdesc + ".\n";
                mess2 = wielder->query_The_name(enemy) + 
                    " drives a massive " +
                    "blow home with " + wielder->query_possessive() +
                    " lochaber axe's beak, inflicting a shocking " +
                    "puncture wound through muscle and nerves to " +
                    "your " + hdesc + ".\n";
                mess3 = QCTNAME(wielder) + " drives a massive " +
                    "blow home with " + wielder->query_possessive() +
                    " lochaber axe's beak, inflicting a shocking " +
                    "puncture wound through muscle and nerves to " +
                    "your " + hdesc + ".\n";
                break;
            default:
                mess1 = "Your lochaber axe screams through the " +
                    "air and pierces straight through " +
                    QTNAME(enemy) + "'s " + hdesc + ", killing " +
                    enemy->query_objective() + " instantly!\n";
                mess2 = "You see a lochaber axe coming for your " +
                    hdesc + ", then blackness...\n";
                mess3 = QCTNAME(wielder) + "'s lochaber axe " +
                    "screams through the air and pierces " +
                    "completely through " + QTNAME(enemy) +
                    "'s " + hdesc + ", killing " +
                    enemy->query_objective() + " instantly!\n";
        }
    }
    wielder->catch_msg(mess1);
    tell_object(enemy, mess2);
    wielder->tell_watcher(mess3, enemy, ({wielder, enemy}));
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(wielder);
    }
    reset_euid();
#ifdef DO_DEBUG
    DEBUG(ctime(time()) + 
        ": Damage - " + dam + ": Extra Damage - " + temp + 
        ": Phurt - " + phurt + ":\n\tHitloc - " + hdesc + 
        ": Damage Type " +
        ({"impale","slash","none","bludgeon"})[dt-1] + "\n\t" +
        ":Max HP - " + enemy->query_max_hp() + ": Remaining HP - " +
        left_hp + ".\n");
#endif
    return 1;
}
