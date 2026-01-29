/**********************************************************************
 * - charge.c                                                       - *
 * - Special attack for gladiators.                                 - *
 * - Removed this out of the soul for easier debugging purposes.    - *
 * - Created by Damaris@Genesis 10/2004                             - *
 **********************************************************************/
#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver"; 
inherit "/d/Cirath/lib/commands";
inherit "/d/Genesis/lib/multi_alarm";

#include "defs.h"
#include <cmdparse.h>
#include <wa_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include "/std/combat/combat.h"
#include <macros.h>
#include <time.h>

void
allow_charge(object ob)
{
    ob->catch_tell("\nYou feel ready to crush your foe again.\n\n");
    ob->remove_prop(GLAD_I_IS_CHARGE);
}
string
c_can_attack(object attacker, object target)
{
    if (!target || !living(target) || !present(target, ENV(attacker)))
    return "Charge whom?\n";

    if (attacker->query_prop(LIVE_I_ATTACK_DELAY))
    return "You are too stunned to execute the charge.\n";

    if (target->query_prop(OBJ_M_NO_ATTACK))
    {
    if (stringp(target->query_prop(OBJ_M_NO_ATTACK)))
    {
        return (target->query_prop(OBJ_M_NO_ATTACK));
    }
    return "You detect a presence protecting the intended victim.\n";
    }

    if (environment(target) &&
      environment(target)->query_prop(ROOM_M_NO_ATTACK))
    {
    if (stringp(E(target)->query_prop(ROOM_M_NO_ATTACK)))
    {
        return ((E(target)->query_prop(ROOM_M_NO_ATTACK))+".\n");
    }
    return "You detect a magical peace spell on the room.\n";
    }

    if ((!attacker->query_npc()) && (attacker->query_met(target)) &&
      (!(attacker==(target->query_attack()))) &&
      (attacker->query_prop(LIVE_O_LAST_KILL) != target))
    {
    attacker->catch_msg("Attack " + QTNAME(target) +
      "?!? Please confirm by trying again.\n");
    attacker->add_prop(LIVE_O_LAST_KILL, target);
    return "";
    }

    if (!F_DARE_ATTACK(attacker, target) &&
        member_array(target, attacker->query_enemy(-1)) == -1)
            return "You don't dare attack.\n";

    if (CHECK_PUNISHMENT(attacker, PUN_EXPEL))
    {
    return "By Kalak's decree a gladiator expelled by the "
    +"Overseers may not charge.\n";
    }
}
int
maxout(int stat)
{
    if (stat>150) return 150;
    return stat;
}

void
do_charge(object target, object attacker)
{
    int hitsuc, hurt, prop, wtohit;
    string how, chargestr;

    if (!objectp(attacker))
    return;

    set_alarm(attacker->query_speed(15+random(6)),
	      0.0, &allow_charge(attacker));

    chargestr = MANAGER->query_charge_desc(attacker);

    /* Has there been a seperation before the charge occured? */
    if ((attacker->query_prop(GLAD_I_IS_CHARGE))==2) return;

    if (present(target, environment(attacker)) &&
      target != attacker->query_attack())
    {
    target = attacker->query_attack();
    }

    /* Has target become invalid somehow? */
    if (stringp(c_can_attack(attacker, target)))
    {
    attacker->catch_tell("You decide to abandon your "+chargestr+".\n");
    return;
    }

    /* Perform the actual collision! */
    wtohit = (attacker->query_skill(SS_CHARGE) / 2) + random(maxout(DEX(attacker))/2);
    attacker->add_prop(GLAD_I_IS_CHARGE, 2);
    if ((hitsuc = QEXC(attacker)->cb_tohit(-1, wtohit, target)) > 0)
    {
    hurt = target->hit_me(2 * (F_PENMOD(maxout(STR(attacker)) / 5 +
          maxout(CON(attacker)) / 5, attacker->query_skill(SS_CHARGE)) +
        16), W_BLUDGEON, attacker, -1)[0];
    }
    else
    {
    hurt = target->hit_me(hitsuc, 0, attacker, -1)[0];
    }
    
//  /* I want to do a bit of a log on this for a while. I based the Ogre
//   * guild special on this formula, and so I want to compare damage and
//   * see how things shake out. (Gorboth - January 2008)
//   */
//  if (hurt > 999)
//  {
//      write_file("/d/Cirath/athas/gladiator/charge_log",
//      TIME2FORMAT(time(), "mm/dd") + " ("
//        + ctime(time())[11..18] + ") "
//        + "Damage = " + hurt + " - "
//        + capitalize(attacker->query_name()) + " vs. "
//        + capitalize(target->query_name()) + "\n");
//  }
//  else
//  {
//      write_file("/d/Cirath/athas/gladiator/charge_log", "Lesser hit -- " +
//      TIME2FORMAT(time(), "mm/dd") + " ("
//        + ctime(time())[11..18] + ") "
//        + "Damage = " + hurt + " - "
//        + capitalize(attacker->query_name()) + " vs. "
//        + capitalize(target->query_name()) + "\n");
//  }

   /* For debugging */
   /* tell_object(attacker,"hc: "+wtohit+", hitsuc: "+hitsuc+"\n"); */

    if (attacker->query_fatigue() > 2)
    {
    attacker->add_fatigue(-3);
    }
    else
    {
    attacker->set_fatigue(0);
    attacker->reduce_hit_points(10);
    attacker->catch_tell("The strain of the attack drains you.\n");
    }

    if (hurt >= 0)
    {
    attacker->add_panic(- hurt / 5);
    if (target->query_hp() > 0)
    {
        if (hurt > 75)
        how = "on the verge of collapse";
        else if (hurt > 50)
        how = "severely hurt";
        else if (hurt > 30)
        how = "hurt";
        else if (hurt > 15)
        how = "injured";
        else if (hurt > 0)
        how = "dazed";
        else how = "amazed by such a feeble attack";

        attacker->catch_msg("You strike "+QTNAME(target)+" with "+
          "your "+chargestr+".\n");
        attacker->catch_msg(QCTNAME(target)+" looks "+ how +".\n");

        target->catch_msg(QCTNAME(attacker) + " strikes you with "+
          HIS_HER(attacker) + " "+chargestr+".\n");
        target->catch_tell("You feel " + how + ".\n");

        attacker->tell_watcher(QCTNAME(attacker)+" strikes " +
          QTNAME(target) + " with " + HIS_HER(attacker) + " " +
          chargestr+".\n", target);

        return;
    }

    attacker->catch_msg("Bones break and blood splatters as you "+
      "devastate " + QTNAME(target) + " with your "+chargestr+
      ", throwing "+HIM_HER(target)+" to the ground in a "+
      "bloody, lifeless heap.\n");

    attacker->tell_watcher(QCTNAME(target) + " lets out a final shriek in "+
      "horrible agony and falls lifelessly to the "+
      "ground at the feet of " + QTNAME(attacker) + ".\n", target);

    target->do_die(attacker);
    return;
    }

    attacker->add_panic(2);
    attacker->add_attack_delay(2, 0);

    attacker->catch_msg("You miss " + QTNAME(target) + " completely "+
      "with your "+chargestr+".\n");

    target->catch_msg(QCTNAME(attacker) + " flails wildly past you, "+
      "missing miserably with "+HIS_HER(attacker)+" "+chargestr+".\n");

    attacker->tell_watcher(QCTNAME(attacker) + " runs past " + QTNAME(target) +
      " in a botched attempt to hit "+HIM_HER(target) + ".\n", target);
}



int
charge(string str)
{
    string how;
    object ob, *obj, charger = TP;

    /* Does attacker have the skill? */
    if (!(charger->query_skill(SS_CHARGE)))
    {
    NF("First you should learn how.\n");
    return 0;
    }

    if (CHECK_PUNISHMENT(charger, PUN_SPEC))
    {
    write("Kalak has cursed you with the inability to charge!\n"+
      "You shall need to find another way to defeat your enemies.\n");
    return 1;
    }

    /* Is the attacker already busy? */
    if ((charger->query_prop(GLAD_I_IS_CHARGE)))
    {
    if ((charger->query_prop(GLAD_I_IS_CHARGE))==1)
        NF("You are already preparing such an attack.\n");
    else
        NF("It seems you can't summon the energy to do that now.\n");
    return 0;
    }

    /* What are we attacking anyway? */
    if (strlen(str))
    {
    if (!sizeof(obj = parse_this(str, "[at] / [into] [the] %l")))
    {
        NF("Choose a more appropriate target.\n");
        return 0;
    }
    ob = obj [0];
    }
    else if (!(ob = charger->query_attack()))
    {
    NF("But you aren't in battle with anyone!\n");
    return 0;
    }

    /* Are we even allowed to attack it? */
    if (stringp(how = c_can_attack(charger, ob)))
    {
    NF(how);
    return 0;
    }

    /* Hurray! Lets set up the alarms to begin and end charge. */
    charger->catch_tell("You prepare to execute the lethal attack.\n");
    set_alarm(charger->query_speed(1 + random(5)),
	      0.0, &do_charge(ob, charger));

    charger->add_prop(GLAD_I_IS_CHARGE, 1);
    
    /* Initiate battle with the target */
    if (!(ob==(charger->query_attack())))
	ob->attacked_by(charger);

    charger->attack_object(ob);
    return 1;
}


