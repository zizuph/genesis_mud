/* scout_base.c
 *
 * Elven scout base file for Krynn.
 *
 * Blizzard, 01/2003
 * Petros May 2010: Added query_not_attack_me check for specials
 * Cotillion - 2020-09-29
 * - Fixed type confusion
 */

#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include <options.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <money.h>
#include "../local.h"

inherit M_FILE

inherit "/std/act/domove";
inherit "/std/act/action";

#define I_HAVE_MONEY "_i_have_money"
#define EHEIGHT ({ 180 + random(15), 170 + random(15) })

void    setup_elf();
void    arm_me();

string *adj_list = ({ "tall", "young", "proud", "alert",
    "long-legged", "watchful", "lean", "solemn", "slim", "noble" });
string *adj_list2 = ({ "blond-haired", "silver-haired", "blue-eyed",
    "bright-eyed", "brown-eyed", "brown-haired", "dark-haired",
    "long-haired" });

string adj1, adj2, gType;
int    type , shouted;

/*  Function name : query_elf_type
 *  Returns       : string type - type of an elf
 */
string
query_elf_type()
{
    return gType;
}

/*  Function name : set_elf_type
 *  Description   : sets type of elf and gives him some skills
 *  Arguments     : int i - three values:
 *                      0 - warrior
 *                      1 - archer
 *                      2 - scout
 *                  Default set to warrior.
 */
void
set_elf_type(int type)
{
    switch(type)
    {
    case 0:
        gType = "warrior";
    break;
    case 1:
        gType = "archer";
    break;
    case 2:
        gType = "scout";
    break;
    default:
        gType = "warrior";
    break;
    }

    setup_elf();
}

/*
 * Function    : add_descr
 * Arguments   : description - The string to be shown after short.
 * Description : Add a string after the normal short().
 */
public void
add_descr(string description)
{
    add_prop(LIVE_S_EXTRA_SHORT, description);
}

/*
 * Function    : remove_descr
 * Description : Remove the extra description
 */
public void
remove_descr()
{
    remove_prop(LIVE_S_EXTRA_SHORT);
}

int
check_aggressive()
{
    if ( CAN_SEE(TO, TP) && CAN_SEE_IN_ROOM(TP) )
    {
        if ( TP->query_dragonarmy_occ_member() ||
            TP->query_guild_member("Priests of Takhisis") )
            return 1;
        else
            return TP->query_prop(I_KILLED_ELF);
    }
    else
        return 0;

}

void
create_elf_npc()
{
    if (!gType)
        set_elf_type(2);
}

void
setup_elf()
{

    set_base_stat(0, 125 + random(15));
    set_base_stat(1, 165 + random(35));
    set_base_stat(2, 150 + random(35));
    set_base_stat(3, 130 + random(15));
    set_base_stat(4, 135 + random(15));
    set_base_stat(5, 135 + random(15));

    set_skill(SS_WEP_KNIFE, 150);
    set_skill(SS_DEFENCE, 130);
    set_skill(SS_PARRY, 130);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_2H_COMBAT, 100);

    set_skill(SS_SNEAK, 80);
    set_skill(SS_HIDE, 80);
    set_skill(SS_WEP_SWORD, 150);
    set_skill(SS_WEP_POLEARM, 150);
    set_skill(SS_WEP_MISSILE, 150);
    set_random_move(5, 0); /* Don't use cpu when players are not here */
    set_restrain_path(FDIR);

    set_exp_factor(115);
}

void
create_krynn_monster()
{
    int gen;

    set_name("elf");
    add_name("scout");
    add_name("_qualinesti_elf_");
    set_race_name("elf");
    set_alignment(600+random(300));
    set_knight_prestige(-200);

    if (!random(10))
        gen = 1;
    else
        gen = 0;

    set_gender(gen);
    adj1 = adj_list[random(sizeof(adj_list))];
    adj2 = adj_list2[random(sizeof(adj_list2))];
    set_adj(({ adj1, adj2 }));
    set_long("@@long_desc");

    set_act_time(20);
    add_act("emote stares into the forest.");
    add_act("emote watches the forest.");
    add_act("emote kneels to check some tracks.");

    add_cact("emote moves with an amazing speed. You realize " +
        PRONOUN(TO) + " is a way quicker than you.");
    add_cact("say You are no match for me.");

    add_prop(CONT_I_HEIGHT, EHEIGHT[gen] + random(10));
    add_prop(CONT_I_WEIGHT, 36000 + random(9000) );
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(LIVE_I_QUICKNESS, 50);
    add_prop(LIVE_I_ATTACK_THIEF, 0);
    set_aggressive(VBFC_ME("check_aggressive"));
    create_elf_npc();

    if ( !random(500) )
        add_leftover(OBJ + "skull", "skull", 1, "", 0, 1);

    set_hp(query_max_hp());

    seteuid(getuid(TO));
    arm_me();
}

int
query_option(int opt)
{
    if ( opt == OPT_UNARMED_OFF )
       return 1;
}

void
calm_me()
{
    shouted = 0;
}

void
arm_me()
{
    object weapon, arrows, quiver;

   /* Clone coins */

    if (!TO->query_prop(I_HAVE_MONEY))
    {
        TO->add_prop(I_HAVE_MONEY, 1);
        MONEY_MAKE_GC(10 + random(10))->move(TO);
        MONEY_MAKE_SC(5 + random(10))->move(TO);
    }

   /* Clone weapon */

    if (!random(3))
        weapon = clone_object(WEP + "warspear");
    else
    {
        weapon = clone_object(WEP + "ash_bow");
        quiver = clone_object(OBJ + "quiver");
        quiver->move(TO);
        clone_object(WEP + "elven_arrow")->move(quiver);
        clone_object(WEP + "elven_arrow")->move(quiver);
        clone_object(WEP + "piercing_arrow")->move(quiver);
        clone_object(WEP + "leaf_arrow")->move(quiver);

        switch(random(2))
        {
        case 0:
            arrows = clone_object(WEP + "piercing_arrow");
        break;
        case 1:
            arrows = clone_object(WEP + "leaf_arrow");
        break;
        }
    }

    weapon->move(TO);
    arrows->move(quiver);

  /* Clone armours */

    clone_object(ARM + "elven_boots")->move(TO);

    if ( !random(3) )
        clone_object(ARM + "elven_sleeves")->move(TO);

    clone_object(ARM + "cloak")->move(TO);

    if ( !random(2) )
        clone_object(ARM + "stud_arm")->move(TO);
    else
        clone_object(ARM + "chain")->move(TO);

    command("wield all");
    command("wear all");
}

/*
string
short_desc()
{
    return adj1 + " "+ adj2 + (query_gender() == 1 ? " female" : " male") +
        " elf";
}
*/

string
long_desc()
{
    return "This " + short() + " is quite a bit taller than the average " +
        "human. " + (query_gender() == 1 ? "She looks rather young but " +
        "you cannot be sure her age since elves are known of their long " +
        "lives. She" : "Like the others here, he looks rather young but " +
        "since elves are known of their long lives you are not able to " +
        "estimate his real age. He") + " is a member of the group, that " +
        "has been sent here to patrol the area of Pax Tharkas and keep " +
        "an eye on the movements of the dragonarmy forces.\n";

}

/* Function    : oke_to_move
 * Description : This function makes an elf scout sneak when moving randomly
 */
mixed
oke_to_move(string exit)
{
    if (this_object()->query_attack())
        return 0;

    return "sneak " + exit;
}

/*
 * Function     : aggressive_attack
 * Description  : If we are aggressive, let us attack but also remove
 *                our nice extra description :/
 * Arguments    : ob - the object to attack
 */

public void
aggressive_attack(object ob)
{
    if (TO->query_prop(LIVE_S_EXTRA_SHORT))
        remove_descr();

    ::aggressive_attack(ob);
}

/*
 * Function:      notify_attacked
 * Description:   Called from an associated npc when it is attacked,
 *                for example one in the same team. This npc will
 *                assist if not already fighting.
 * Arguments:     object friend -   the friend who was attacked
 *                object attacker - the attacker
 */
void
notify_attacked(object friend, object attacker)
{
          // If not fighting anyone, assist.
    if (!objectp(query_attack()))
    {
        remove_descr();
        command("assist " + OB_NAME(friend));
    }
}

/*
 * Function:    react_attack
 * Description: React to an attack. This called by alarm from
 *              the function "attacked_by" below.
 * Arguments:   object attacker  -  the attacker.
 */
void
react_attack(object attacker)
{
    query_team_others()->notify_attacked(this_object(), attacker);

    if ( shouted == 1 )
        return;

    if (!CAN_SEE_IN_ROOM(this_object()))
    {
        command("say You bring much darkness to our homeland! But it will " +
            "not help you!");
    }
    else if (!CAN_SEE(this_object(), attacker))
    {
        command("say Show yourself, coward!");
    }
    else
    {
        switch (random(3))
        {
        case 0:
            command("say That was your last mistake.");
            command("emote moves to face you.");
        break;
        case 1:
            command("say You will regret that!");
        break;
        case 2:
            command("say Let's see if you manage to leave this " +
                "forest alive.");
        break;
        }
    }

    shouted = 1;
    set_alarm(8.0, 0.0, &calm_me());
}

/*
 *   Function:     attacked_by
 *   Description:  Called by the combat system when a living is
 *                 attacked. See "sman attacked_by" for documentation.
 *   Arguments:    object attacker  -  the attacking living.
 */
public void
attacked_by(object attacker)
{
    if (!attacker->query_prop(I_KILLED_ELF))
        attacker->add_prop(I_KILLED_ELF, 1);

    remove_descr();
    ::attacked_by(attacker);
    set_alarm(1.0, 0.0, &react_attack(attacker));
}


string
query_damage_desc(int hit)
{
    string *dam;
    object weapon = query_weapon(-1)[0];

    switch (weapon->query_wt())
    {
    case W_SWORD:
    case W_KNIFE:
        dam = ({ "almost", "lightly", "mildly", "seriously", "badly",
            "horribly" });
    break;
    case W_POLEARM:
        dam = ({ "but misses badly", "just grazing it",
            "opening a minor wound", "dealing a serious wound",
            "opening a bleeding wound", "almost puncturing it" });
    break;

    case W_MISSILE:
        dam = ({ "Luckily for you, both missiles miss you with a sharp " +
            "whistling sound.", "Luckily, you manage to avoid the first " +
            "missile but the second one hits you, causing a little damage.",
            "The first missile hits your body hard, but the second one " +
            "misses you by a few inches.", "You duck in attempt to avoid " +
            "these missiles but your moves are too slow. The first arrow " +
            "scratches you slightly but the second one causes a more " +
            "serious wound.", "Being still in a shock, amazed by the elf's " +
            "speed, you pause for a moment. When you shake off you " +
            "realize you have two arrows sticking from a deep bleeding " +
            "wounds in your body.", "Being slowed by your wounds you are " +
            "unable to avoid getting hit. You feel a piercing pain as " +
            "the first arrow hits your body and the moment later the " +
            "second missile almost punctures your throat." });
    break;
    }

    switch (hit)
    {
    case 0:
        return dam[0];
    break;
    case 1..5:
        return dam[1];
    break;
    case 6..10:
        return dam[2];
    break;
    case 11..25:
        return dam[3];
    break;
    case 26..40:
        return dam[4];
    break;
    default:
        return dam[5];
    break;
    }
}

/*
 * Function    : special_attack
 * Description :
 * Arguments   : enemy - the one we are fighting now
 * Returns     : 0 - if we want the round to continue
 *               1 - if we are done with this round
 */
int
special_attack(object enemy)
{
    mixed  hitresult;
    object me = TO;
    object wp, *wps;
    string dam_desc, where;
    int    stun_duration = 5 + random(5);
    int    pen, dt;

    wps = query_weapon(-1);

    if ( sizeof(wps) )
        wp = wps[0];
    else
        return 0;

    if ( !objectp(wp) )
        return 0;

    if ( !enemy )
        return 0;

      // Execute the special attack 1 in 4 rounds on average
    if (random(4))
        return 0;

    dt = wp->query_dt();

    // Make sure that we can actually attack the target
    if (enemy->query_not_attack_me(me, -1))
    {
        return 1; // round is ended so return 1.
    }

    if ((wp->query_wielded() == TO) && ((wp->query_wt() == W_SWORD) ||
        (wp->query_wt() == W_KNIFE)) )
    {
        pen = TO->query_stat(SS_DEX) + query_skill(wp->query_wt()) +
            350;

        hitresult = enemy->hit_me(pen, dt, me, -1);

        dam_desc = query_damage_desc(hitresult[0]);

        enemy->catch_msg(TO->query_The_name(enemy) + "'s moves begin to " +
            "blur before your eyes as he speeds up. The elf reverses the " +
            "grip on " + POSSESSIVE(TO) + " " + wp->short() + " and " +
            "moving with an amazing speed, " + PRONOUN(TO) + " disappears " +
            "from your sight ... Suddenly, you feel a stab in your ribs.\n" +
            "In shock, you realize you have been " + dam_desc + " wounded " +
            "and didn't notice how it happened.\n");
        tell_watcher(QCTNAME(TO) + "'s moves begin to blur before your " +
            "eyes as he speeds up. The elf reverses the grip on " +
            POSSESSIVE(TO) + " " + wp->short() + " and moving with an " +
            "amazing speed, " + PRONOUN(TO) + " disappears from your sight " +
            "... Suddenly, " + PRONOUN(TO) + " reappears at " +
            QCTNAME(enemy) + "'s side, stabbing " + OBJECTIVE(enemy) +
            " in the ribs.\n", enemy);

     // if hitresult[0] > 13 there is 80% chance for stunning opponent for
     // a moment
        if ( hitresult[0] > 13 && random(5) )
        {
            enemy->catch_msg("You feel a blade hindering your movement, " +
                "sticking from between your ribs and stopping your arm.\n");
            enemy->add_attack_delay(stun_duration, 1);
        }

        if (enemy->query_hp() <= 0)
            enemy->do_die(me);

        return 0;
    }

    if ((wp->query_wielded() == TO) && (wp->query_wt() == W_MISSILE))
    {
        pen = TO->query_stat(SS_DEX) + query_skill(wp->query_wt()) +
            350;

        hitresult = enemy->hit_me(pen, dt, me, -1);
        dam_desc = query_damage_desc(hitresult[0]);

        enemy->catch_msg(TO->query_The_name(enemy) + " loads " +
            POSSESSIVE(TO) + " " + wp->short() + " and quickly aims at " +
            "you. Then " + PRONOUN(TO) + " releases a string, sending an " +
            "arrow in your direction and before you are able to react " +
            PRONOUN(TO) + " shoots again.\n" + dam_desc + "\n" );
        tell_watcher(QCTNAME(TO) + " loads " + POSSESSIVE(TO) + " " +
            wp->short() + " and quickly aims at " + QCTNAME(enemy) +
            ". Then " + PRONOUN(TO) + " releases a string, sending an " +
            "arrow in " + QCTNAME(enemy) + "'s direction and before " +
            PRONOUN(enemy) + " is able to react the elf shoots again.\n",
            enemy);

        if (enemy->query_hp() <= 0)
        {
            enemy->catch_msg("You produce a gurgling sound and grasp " +
                "your throat when one of elven arrows punctures it. " +
                "You fall to your knees trying to pull this sharp stick " +
                "from your neck.\n");
            tell_watcher(QCTNAME(enemy) + " produces a gurgling sound " +
                "and grasp " + POSSESSIVE(enemy) + " throat when one of " +
                "elven arrows punctures it. Desperately trying to pull " +
                "the sharp stick from " + POSSESSIVE(enemy) + " neck, " +
                QCTNAME(enemy) + " falls to " + POSSESSIVE(enemy) +
                " knees.\n", enemy);

            enemy->do_die(me);
        }

        return 0;

    }

    if ((wp->query_wielded() == TO) && (wp->query_wt() == W_POLEARM))
    {
        pen = TO->query_stat(SS_DEX) + query_skill(wp->query_wt()) +
            350;

        where  = ({ "left leg", "right leg", "left arm", "right arm",
            "head", "stomach", "body", "stomach" })[random(7)];

        hitresult = enemy->hit_me(pen, dt, me, -1);
        dam_desc = query_damage_desc(hitresult[0]);

        enemy->catch_msg(QCTNAME(TO) + " parries a wild blow from you, " +
            "then twirling around " + PRONOUN(TO) + " counters with a " +
            "vicious stab of " + POSSESSIVE(TO) + " " + wp->short() +
            " at your " + where + ", " + dam_desc + ".\n" );
        tell_watcher(QCTNAME(TO) + " parries a wild blow from " +
            QTNAME(enemy) + ", then twirling around " + PRONOUN(TO) +
            " counters with a vicious stab of " + POSSESSIVE(TO) + " " +
            wp->short() + " at " + QTNAME(enemy) + ".\n", enemy);

        if (enemy->query_hp() <= 0)
            enemy->do_die(me);

        return 0;

    }

    return 0;

}



