/*
 * lochaber.c
 *
 * Coded by Khail, Nov 25/96
 *
 * This lochaber axe is _very_ different. It's a magic 
 * axe, of sorts, and a one-of-a-kind, completely unique.
 * It's got a fair hit and a good pen, but very dangerous
 * to wield, for a number of reasons:
 *
 * 1: Players with align > 900 can wield the axe, but get
 *    poisoned (see POISON define for current path) in the
 *    process. It's more of a nausea than a poison though.
 * 2: Players with > 900 align cannot unwield the axe, and
 *    attempts to do so will result in more of the same
 *    poison.
 * 3: Players with < -900 align have no problems wielding,
 *    in fact they get a kick out of it. However, when it
 *    comes time to let go, the axe forces them to kill 
 *    anything and everything that's alive in the room 
 *    before they can unwield.
 * 4: The axe gets very jealous, this has a couple ill 
 *    effects. For one, if someone wielding the axe happens
 *    to pick up another magic weapon, the axe grows thorns
 *    through the player's hands, making it completely
 *    unwieldable, and forces the player to attack the largest
 *    living in the room, so long as it's bigger than the
 *    player. This remains in effect indefinately.
 * 5: The axe also gets jealous of magic weapons being wielded
 *    by other players, and will randomly attempt to destroy
 *    them from time to time.
 * 6: If the axe is ever broken, it has one final fit in which
 *    it attempts to take out as many living beings as 
 *    possible by exploding into a ball of magical energy, 
 *    which inflicts _serious_ damage.
 *
 * Note that the axe also uses a shadow for some purposes, see
 * the SHADOW define for the current path. This is to allow it
 * to see more 'intelligent' to the player by letting it see
 * what the player's doing, when it comes to moving around, 
 * taking damage, etc.
 *
 * I M P O R T A N T!!!!!
 * This axe is not open code as of Feb 16/97 and in all
 * liklihood never will be. It remains only in the event
 * that I change my mind in the future.
 * - Khail
 */
#pragma strict_types

#include "defs.h"
#include <filter_funs.h>

#define HIT 35
#define PEN 55

#define JEALOUS_REVENGE  "_i_jealous_revenge"
#define SHADOW           SPECIAL + "lochaber_shadow"
#define POISON           SPECIAL + "lochaber_poison"

inherit "/std/weapon";

object shadow;
public void attack_weapon(object ob);


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
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(HIT, W_AXE));
    add_prop(OBJ_I_VOLUME, 7500 / 5);
    add_prop(OBJ_S_WIZINFO, "IMPORTANT: At the moment this " +
        "axe is _NOT_ open code. If found on a mortal, " +
        "it's probably time to start looking for a wiz " +
        "with bad habits.\n");
    setuid(); seteuid(getuid());
}

/*
 * Function name: wield
 * Description  : What to do when someone tries to wield
 *                this weapon. There's a variety of
 *                possible outcomes.
 * Arguments    : object ob - Object pointer to the object
 *                            this_player() was trying to 
 *                            wield.
 * Returns      :
 */
public mixed
wield(object ob)
{
    object *temp,
           poison;
  
  /* Don't do anything if this object wasn't the one */
  /* this_player() was trying to wield, for some */
  /* reason. */
    if (ob != TO)
        return 0;

  /* This thing's made of iron. Only relatively large */
  /* players can wield it. */
    if (TP->query_stat(SS_STR) < 60)
        return "You don't have the strength to even " +
            "hope to use this weapon.\n";

  /* Do-gooders just can't handle the truth. The */
  /* touch of this weapon makes 'em sick. */
    if (TP->query_alignment() > 900)
    {
        write("As you wield the lochaber in both " +
            "a wave of hatred and corruption passes " +
            "over you, so intense you feel nauseous " +
            "but are unable to release your grip " +
            "on the weapon!\n");
        say(QCTNAME(TP) + " attempts to wield " +
            "a brutal iron lochaber axe, but " +
            "doesn't appear right, " +
            TP->query_pronoun() + " suddenly seems " +
            "very sick.\n");
 
      /* A nice little poison to start the day */
      /* off right. */
        poison = clone_object(POISON);
        poison->move(TP, 1);
        poison->start_poison();
 
      /* Since the player wielded the axe, give them */
      /* the shadow that controls a lot of its finer */
      /* finer talents. */
        if (!shadow)
        {
            shadow = clone_object(SHADOW);
            shadow->shadow_me(TP);
            shadow->set_caller(TO);
        }
        return 1;        
    }

  /* Bad guys, however, get a rush out of this */
  /* thing. */
    else if (TP->query_alignment() < -900)
    {
        write("As you grasp the lochaber axe, you " +
            "suddenly feel as if you have become, " +
            "finally, a whole being. You can't help " +
            "but to exhalt in the passionate waves " +
            "of hatred that emanate from the weapon!\n");
        say(QCTNAME(TP) + " gets a strange look on " +
            TP->query_possessive() + " face as " +
            TP->query_pronoun() + " wields a brutal " +
            "iron lochaber axe.\n");
        TP->command("$cackle demonically");

      /* The player wielded, so let's give him a */
      /* shadow. */
        if (!shadow)
        {
            shadow = clone_object(SHADOW);
            shadow->shadow_me(TP);
            shadow->set_caller(TO);
        }
        return 1;
    }

    write("As you wrap your hands around the handle " +
        "of the brutal iron lochaber axe, thoughts " +
        "of pure rage and horrific violence leap " +
        "unbidden to your mind.\n");

  /* Again, they wielded, so shadow them. */
    if (!shadow)
    {
        shadow = clone_object(SHADOW);
        shadow->shadow_me(TP);
        shadow->set_caller(TO);
    }
    return 0;
}

/*
 * Function name: unwield
 * Description  : Things to do when the player tries to
 *                unwield a specified weapon, again, a
 *                variety of results depending on the
 *                player.
 * Arguments    : object ob - Object pointer to the weapon
 *                            the player is trying to wield.
 * Returns      :
 */
public mixed
unwield(object ob)
{
    object poison;
    object *temp;

  /* Make sure 'ob' is this object. */
    if (ob != TO)
        return 0;

  /* Ah-ah-ah, naughty player picked up another magic */
  /* weapon while wielding the axe, now he or she's */
  /* stuck with it. */
    if (query_prop(JEALOUS_REVENGE))
    {
        return "Countless thorns have locked your " +
            "hands upon the handle of the lochaber " +
            "axe, it's impossible to unwield!\n";
    }

  /* Silly boy! If it made you sick wielding it, */
  /* it's really gonna have fun with you if you */
  /* think it's gonna let you throw it in a */
  /* corner. If align > 900, don't let them */
  /* unwield, but poison for the attempt. */
    if (TP->query_alignment() > 900)
    {
        write("You attempt to release the weapon, " +
            "but it seems to realize your intents " +
            "and the waves of nausea only become " +
            "worse!\n");
        say(QCTNAME(TP) + " struggles for a moment, " +
            "seemingly trying to release " + 
            TP->query_possessive() + " grip on the " +
            "brutal iron lochaber axe, but " +
            TP->query_pronoun() + " only seems " +
            "to become sickened by it.\n");
        poison = clone_object(POISON);
        poison->move(TP, 1);
        poison->start_poison();        
        return "";        
    }

  /* If the player's too evil, he enjoyed using the */
  /* axe just a bit too much. We'll let him unwield, */
  /* but not until he's been forced to kill anything */
  /* and everything that's in the room. */
    if (TP->query_alignment() < -900)
    {
        write("As you grasp the lochaber axe, you " +
            "suddenly feel as if you have parted " +
            "with a piece of yourself. You find " +
            "yourself thinking 'not without one " +
            "last kill'...\n");
        say(QCTNAME(TP) + " gets a strange look on " +
            TP->query_possessive() + " face as " +
            TP->query_pronoun() + " attempts to " +
            "unwield a brutal " +
            "iron lochaber axe.\n");
        TP->command("$cackle demonically");
        if (sizeof(temp = FILTER_OTHER_LIVE(all_inventory(environment(TP)))))
        {
            TP->command("$kill " +
                OB_NAME(temp[random(sizeof(temp))]));
            return "";
        }
        else
        {
          /* Bah, nothing left to kill. Guess we'll let */
          /* the player unwield and remove the axe shadow. */
            write("But, finding nobody present to " +
                "kill, the urge passes.\n");
            if (shadow)
            {
                shadow->remove_shadow();
            }
            return 0;
        }
    }

    write("As you release your grip on the lochaber " +
        "axe, your mind reels with the memory of " +
        "the horrific thoughts which filled it.\n");
  
  /* Same thing as above. The player managed to unwield */
  /* the axe, so remove the shadow. */
    if (shadow)
        shadow->remove_shadow();
    return 0;
}

public int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
    int phit, int dam)
{
    string mess1,   /* Wielder message  */
           mess2,   /* Target message   */
           mess3;   /* Watcher messages */

    if (!dt || dt == W_SLASH)
    {
      /* Double-damage for a slash to the head. */
        if (hdesc == "head" && dam)
        {
            enemy->heal_hp(-dam);
            phurt = ftoi(enemy->query_max_hp() / (dam * 2) * 100);
        } 
        switch(phurt)
        {
            case -1:
                mess1 = "You swing the lochaber axe heavily, but " +
                    "slice through nothing but the air above " +
                    QTNAME(enemy) + "'s head.\n";
                mess2 = QCTNAME(wielder) + " swings " +
                    wielder->query_possessive() + " lochaber axe heavily " +
                    "towards you, but slices nothing but the air " +
                    "over your head.\n";
                mess3 = QCTNAME(wielder) + " swings " +
                    wielder->query_possessive() + " lochaber axe heavily " +
                    "towards " + QTNAME(enemy) + ", but slices through " +
                    "nothing except the air above " + 
                    enemy->query_possessive() + " head.\n";
                break;
            case 0:
                mess1 = "You swing the lochaber axe deftly at " +
                    QTNAME(enemy) + "'s " + hdesc + ", but miss your " +
                    "mark, doing nothing but a painless scratch of " +
                    "damage.\n";
                mess2 = QCTNAME(wielder) + " swings " + 
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
                mess2 = QCTNAME(wielder) + "'s lochaber axe slices a " +
                    "thin wound across your " + hdesc + ".\n";
                mess3 = QCTNAME(wielder) + "'s lochaber axe slices a " +
                    "thin wound across " + QTNAME(enemy) + "'s " +
                    hdesc + ".\n";
                break;
            case 11..30:
                mess1 = "You slash a bloody wound across " +
                    QTNAME(enemy) + "'s " + hdesc + " with your " +
                    "lochaber axe.\n";
                mess2 = QCTNAME(wielder) + " slashes a bloody wound " +
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
                mess2 = QCTNAME(wielder) + "'s lochaber axe " +
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
                mess2 = QCTNAME(wielder) + "'s lochaber axe bites " +
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
                mess2 = QCTNAME(wielder) + " drives a massive " +
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
  /* Impale messages. Triple damage to head, double to body. */
    else
    {
        if (hdesc == "head" && dam)
        {
            enemy->heal_hp(-(dam * 2));
            phurt = ftoi(enemy->query_max_hp() / (dam * 3) * 100);
        } 

        else
        if (hdesc == "body" && dam)
        {
            enemy->heal_hp(-dam);
            phurt = ftoi(enemy->query_max_hp() / (dam * 2) * 100);
        } 

        switch (phurt)
        {
            case -1:
                mess1 = "You drive the lochaber axe heavily, but " +
                    "punch through nothing but the air above " +
                    QTNAME(enemy) + "'s head.\n";
                mess2 = QCTNAME(wielder) + " drives " +
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
                mess2 = QCTNAME(wielder) + " stabs " + 
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
                mess2 = QCTNAME(wielder) + "'s lochaber axe punches a " +
                    "small bruise on your " + hdesc + ".\n";
                mess3 = QCTNAME(wielder) + "'s lochaber axe punches a " +
                    "small bruise on " + QTNAME(enemy) + "'s " +
                    hdesc + ".\n";
                break;
            case 11..30:
                mess1 = "You punch a bloody wound in " +
                    QTNAME(enemy) + "'s " + hdesc + " with your " +
                    "lochaber axe's beak.\n";
                mess2 = QCTNAME(wielder) + " punches a bloody wound " +
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
                mess2 = QCTNAME(wielder) + "'s lochaber axe's beak " +
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
                mess2 = QCTNAME(wielder) + "'s lochaber axe's beak " +
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
                mess2 = QCTNAME(wielder) + " drives a massive " +
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
    
    return 1;
}

/*
 * Function name: check_other_weapons
 * Description  : It seems out little axe has a jealous
 *                streak a mile wide. If it finds other
 *                magical weapons in it's wielder's 
 *                inventory, it decides to teach him
 *                a lesson down the road.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
check_other_weapons()
{
    object *others;
    
  /* Don't check for other magic weapons if this weapon */
  /* isn't wielded. */
    if (!query_wielded())
        return;

  /* Find any magic weapons in the wielder's inventory. */
    others = filter(all_inventory(wielder) - ({TO}), 
        &->query_prop(OBJ_I_IS_MAGIC_WEAPON));

  /* Wielder was a good boy, no other magic weapons. */
    if (!sizeof(others))
        return;

  /* Oops, the wielder picked up another magic weapon. */
  /* This one's a little jealous, and will give the */
  /* wielder a shadow that will teach him/her a lesson. */
    if (!shadow)
    {
        shadow = clone_object(SHADOW);
        shadow->shadow_me(TP);
        shadow->set_caller(TO);
    }
    shadow->set_jealousy(wielder);
}
          
/*
 * Function name: jealous_revenge
 * Description  : The axe is fairly jealous of its
 *                abilities. If the wielder picks up
 *                another magic weapon (in the function
 *                check_other_weapons()), the axe decides
 *                it's time to teach someone a lesson. It
 *                waits until the right moment, then 
 *                takes revenge here.
 * Arguments    : object who - Object pointer to player to
 *                             take revenge on. Since the 
 *                             axe waits for it's revenge, we
 *                             have to be sure the player who
 *                             pissed it off is the current
 *                             wielder.
 * Returns      : n/a
 */
public void
jealous_revenge(object who)
{
  /* Fail if the person to take revenge on isn't */
  /* the current wielder. */
    if (!query_wielded() ||
        !who ||
        wielder != who)
    {
      /* Remove the 'jealousy' from the shadow. */
        if (shadow)
            shadow->remove_jealousy();
        return;
    }

  /* Payback's a bitch. */
    tell_object(wielder, "Suddenly, you hear a strange, " +
        "hissing voice inside your head: Desire other " +
        "weapons of power, do you? Perhaps this will " +
        "remind you what loyalty means!\n");
    tell_object(wielder, "Steely thorns suddenly " +
        "spring from the handle of the brutal iron " +
        "lochaber axe, piercing your hands! They curl " +
        "back in upon themselves, locking your hands " +
        "into place on the handle. The only way to " +
        "unwield this thing now would be to cut off " +
        "your hands!\n");
    wielder->heal_hp(-200);
    wielder->command("$scream");
    tell_room(environment(wielder), "As you look in " +
        "shock, you realize " + QTNAME(wielder) + "'s " +
        "hands are now covered in " + TP->query_possessive() +
        " own blood, and the handle of his lochaber axe is " +
        "now covered in barbed and hooked thorns, several " +
        "of which have erupted through " + 
        QTNAME(wielder) + "'s hands, locking them " +
        "into place on the handle of the axe!\n");

  /* Once this prop is added, the axe is unwieldable, */
  /* except by destruction, and the shadow will start */
  /* forcing the player to attack the biggest livings */
  /* he or she comes across. */
    add_prop(JEALOUS_REVENGE, 1);
}

/*
 * Function name: check_other_magic
 * Description  : Decides if there are any magic items
 *                being carried by anyone in the wielder's
 *                environment.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
check_other_magic()
{
    object *weaps;
    int i;

    if (!query_wielded())
        return;

    weaps = filter(deep_inventory(environment(wielder))
        - all_inventory(wielder), 
        &->query_prop(OBJ_I_IS_MAGIC_WEAPON));

    if (!sizeof(weaps))
        return;

    for (i = 0; i < sizeof(weaps); i++)
    {
        if (weaps[i]->query_wielded())
        {
            attack_weapon(weaps[i]);
            break;
        }
    }
}

/*
 * Function name: attack_weapon
 * Description  : Allows the axe to try and break a
 *                magic weapon it finds being wielded
 *                by someone else in its wielder's
 *                environment, even someone on the
 *                wielder's team.
 * Arguments    : object ob - pointer to the object
 *                            to try and break.
 * Returns      : n/a
 */
public void
attack_weapon(object ob)
{
  /* Fail if 'ob' isn't a magic weapon. */
    if (!ob->query_prop(OBJ_I_IS_MAGIC_WEAPON))
        return;

  /* Fail if the axe isn't wielded. */
    if (!query_wielded())
        return;

  /* Fail if 'ob' isn't wielded. */
    if (!ob->query_wielded())
        return;

  /* Fail if 'ob's wielder is in a different */
  /* room than the axe's wielder. */
    if (environment(ob->query_wielded()) !=
        environment(wielder))
        return;

  /* Ok, the axe has found another magic weapon being */
  /* wielded by someone in the axe's wielder's */
  /* environment, now to destroy it. */
    tell_object(wielder, "Suddenly, the lochaber " +
        "seems to spring to life on it's own " +
        "and slashes out at " + 
        QTNAME(ob->query_wielded()) + "'s " +
        ob->short() + "! You could swear you can " +
        "hear an insane howl of fury from within.\n");
    tell_object(ob->query_wielded(), "Suddenly, " +
        QTNAME(wielder) + " brings " +
        wielder->query_possessive() + " lochaber axe " +
        "down across your " + ob->short() + "!\n");
    tell_room(environment(wielder), "Suddenly, " +
        QCTNAME(wielder) + " brings " +
        TP->query_possessive() + " down heavily " +
        "across " + QTNAME(ob->query_wielded()) + 
        "'s " + ob->short() + "!\n",
        ({wielder, ob->query_wielded}));

  /* We hit it, let's try to break it. */
    ob->set_dull(10);

  /* Axe gets smug if 'ob' was broken. */
    if (ob->query_prop(OBJ_I_BROKEN))
        write("The lochaber axe settles down, seeming " +
            "to pulse slightly with a smug contentment.\n");
}

public string
query_recover()
{
    return "";
}

/*
 * Function name: remove_broken (MASKED)
 * Description  : Handles what to do when the object breaks.
 *                This particular mask allows normal handling,
 *                but has some additional effects. The axe,
 *                while intelligent, isn't particularly mature.
 *                Therefore, once it realizes it is basically
 *                about to die, it tries to take everyone it
 *                can with it.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
remove_broken()
{
    object *present;
  
  /* Call back to the masked remove_broken(). */ 
    ::remove_broken();
      
  /* Now we'll see who's standing around where */
  /* the axe is, first seeing if it's in a room, */
  /* in a player's inventory, or in a container */
  /* in a player's inventory. */
    if (environment()->query_prop(ROOM_I_IS))
        present = FILTER_LIVE(all_inventory(environment()));
    else if (living(environment()))
        present = FILTER_LIVE(
            all_inventory(environment(environment())));
    else
        present = FILTER_LIVE(
            all_inventory(environment(environment(environment()))));

  /* See if we found anyone to take out with us. */
    if (!sizeof(present))
        return;

  /* "It's better to burn out, than to fade away!" */
    present->catch_msg("You suddenly hear a strange, " +
        "hissing voice scream: Noooooooooo!\n");
    present->catch_msg("The brutal iron lochaber axe " +
        "suddenly erupts in an explosion of raw energy " +
        "as it breaks, catching you with its power, " +
        "in one final act of wrath!\n");
    
  /* That'll teach 'em to take good care of their */
  /* weapons. This object produces a magic special */
  /* attack that tries to do an effective 5000 wcpen */
  /* on everyone it can reach. */
    present->hit_me(5000, MAGIC_DT, TO, -1);
}

/*
 * Function name: init
 * Description  : Called when another object enters this
 *                object's environment or inventory.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init()
{
    ::init();
    check_other_weapons();
}
