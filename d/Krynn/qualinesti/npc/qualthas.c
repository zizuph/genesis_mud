/* File : qualthas.c
 *
 * The leader of elven scouts.
 *
 * Blizzard, 02/2003
 * Last update: 11.05.2003
 *
 * Navarre April 2008: Added name _qualinesti_elf_ to qualthas, like all the other elves.
 * Cotillion Dec 2008: Added sword skill.
 * Petros May 2010: Added query_not_attack_me check for specials
 * Cotillion - 2020-10-04
 * - Fixed type confusion
 */

#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <money.h>
#include "../local.h"

#define I_HAVE_MONEY      "_i_have_money"
#define LOST_SCOUTS       "_lost_scouts"
#define WARN_QUALTHAS     "_warn_qualthas"
#define QUALTHAS_KILLED   "_qualthas_killed"
#define FOUND_DEORL       "_found_deorl"
#define ELF_SAFE          "_elf_safe"
#define ELF_CAMP_QUEST    "_elf_camp_quest"
#define CAMP_VISITED      "_camp_visited"

inherit "/lib/unique";
inherit AUTO_TEAM
inherit M_FILE

public string ask_help();
public string ask_deorl();
public string ask_sarist();
public string ask_location();
public string ask_reward();
public void   do_answer(string what, object who);
int           report_me(string str);
void          arm_me();
// void          check_for_arrows;

//int gSeq_started = 0;
object        quiver;
int           shouted;

int
check_aggressive()
{
    if ( TP->query_dragonarmy_occ_member() )
        return 1;
    else
        return TP->query_prop(I_KILLED_ELF);

}

void
create_krynn_monster()
{

    set_name("qualthas");
    add_name("_qualinesti_elf_");
    set_living_name("qualthas");
    set_race_name("elf");
    set_adj("noble");
    add_adj("sharp-eyed");
    set_title("Darriel, Leader of the Elven Scouts");
    set_long("This tall, well-built elf has a commanding air about him. " +
        "He firmly wields his weapon and you have no doubts he knows how " +
        "to use it. Althought he appears stern, a hint of warmth and " +
        "compassion can be seen in his eyes.\n");
    set_gender(0);
    set_alignment(800);
    set_knight_prestige(-300);

    set_stats(({ 180, 230, 210, 180, 180, 185 }));

    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_WEP_MISSILE, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_SWORD, 100);

    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_BLIND_COMBAT, 100);

    set_exp_factor(160);

    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_HEIGHT, 185);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_ATTACK_THIEF, 0);
    add_prop(LIVE_I_SEE_DARK, 20);
    add_prop(LIVE_I_QUICKNESS, 130);
    add_prop(LIVE_S_EXTRA_SHORT, " discussing something with his companions");
    set_aggressive(VBFC("check_aggressive"));
    set_introduce(1);
    set_pick_up_team(({"_qualinesti_elf_"}));

    set_hp(query_max_hp());

    set_act_time(10 + random(2));
    add_act("emote paces nervously.");
//    add_act("@@check_for_arrows");
    add_act("emote speaks with his companions silently.");
    add_act("say Those two should be here already.");
    add_act("emote stares worriedly into the forest.");
    add_act("say Where is Sarist? Still no reports from him.");
    add_act("emote gives some orders to the elf, who leaves into the " +
        "forest quickly.");
    add_act("say Dragonarmies keep sending more and more draconians to Pax " +
        "Tharkas! We have to keep patroling the forest.");
    add_act("say We must weaken the dragonarmy forces before they launch " +
        "the attack on Qualinost!");
    add_act("say The scouts have seen a red dragon flying over Pax Tharkas. " +
        "It seems Verminaard indeed got a new pet.");
    add_act("say Some of those draconians are quite skilled, but they " +
        "are no match for us!");
    add_act("say You there! Keep watching the forest!");

    add_cact("emote scowls at you.");
    add_cact("say You really think you can stand against me?!");
    add_cact("say Defend yourself!");
    add_cact("take arrows");

    set_default_answer(VBFC_ME("def_answer"));
    add_ask(({ "draconians", "draconian" }),
        "say Yes, I realize their presence. We are here to stop them " +
        "from entering our forest. Otherwise Qualinost may be in danger.", 1);
    add_ask(({ "pax", "pax tharkas", "Pax Tharkas", "Pax tharkas" }),
        "say Hmm. It is bad that Dragonarmies control that city. But we " +
        "cannot afford attacking them.", 1);
    add_ask(({ "speaker of the suns", "Speaker of the Suns" }),
        "say He is a wise person and he will not risk the life of even a " +
        "single elf until it is necessary. " +
        "We are here to keep an eye on those draconians, and to estimate " +
        "the real danger.", 1);
    add_ask(({ "Verminaard", "verminaard" }),
        "say I wish he never arrived to these lands! He lives for the " +
        "destruction of all that is good!", 1);
    add_ask(({ "dragons", "evil dragon", "evil dragons", "dragon" }),
        "say My people saw a red dragon flying over the forest, as he was " +
        "looking for something. It seems it was Verminaard's pet.", 1);
    add_ask(({ "dragonarmy", "Dragonarmy", "dragonarmies", "Dragonarmies" }),
        "say There are more and more forces coming to Pax Tharkas. We have " +
        "to stop them or soon they will be ready to launch the attack on " +
        "Qualinost!", 1);
    add_ask(({ "Qualinost", "qualinost" }),
        "say This is our home, but now the Speaker of the Suns is " +
        "considering leaving the city. I hope this will never happen, but " +
        "we may have no choice.", 1);
    add_ask(({ "Qualinesti", "qualinesti", "forest" }),
        "say This forest is the last thing that stops Dragonarmies from " +
        "attacking Qualinost. If they cross its borders, they will " +
        "regret that.", 1);
    add_ask(({ "sarist", "Sarist", "about sarist", "about Sarist" }),
        VBFC_ME("ask_sarist"), 1);
    add_ask(({ "deorl", "Deorl", "about deorl", "about Deorl" }),
        VBFC_ME("ask_deorl"), 1);
    add_ask(({ "help", "task", "quest" }), VBFC_ME("ask_help"), 1);
    add_ask(({ "reward", "about reward" }), VBFC_ME("ask_reward"), 1);
    add_ask(({ "location", "where", "place" }), VBFC_ME("ask_location"), 1);

    seteuid(getuid(TO));
    arm_me();
}

string
def_answer()
{
    command("emote goes hmmm.");
    command("say What? Speak up!");

    return "";
}

void
check_for_arrows()
{
    object weapon, *wp;
    object *items;
    int    i, arrow, size;

    wp = query_weapon(-1);

    if ( sizeof(wp) )
        weapon = wp[0];

    if ( weapon->query_wt == W_MISSILE )
    {
        items = deep_inventory(TO);
        size = sizeof(items);

        for ( i = 0; i < size; i++ )
        {
            if ( (items[i])->id("arrow") )
                arrow++;
        }

        if ( arrow <= 10 )
        {
            command("emote puts some more arrows into his quiver.");
            clone_object(WEP + "elven_arrow")->move(quiver, 1);
            arrow += 12;
        }
        else
        {
            command("emote inpsects his quiver for arrows.");
            command("take arrows");
            command("put arrows in quiver");
        }
    }
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
    object weapon, dagger;

   /* Clone coins */

    if (!TO->query_prop(I_HAVE_MONEY))
    {
        TO->add_prop(I_HAVE_MONEY, 1);
        MONEY_MAKE_GC(10 + random(10))->move(TO);
        MONEY_MAKE_SC(5 + random(10))->move(TO);
    }

   /* Clone weapons */
    switch (random(3))
    {
        case 0:
            dagger = clone_unique(WEP + "eagle_dagger", 5,
                WEP+ "dagger");
            dagger->move(TO);
            weapon = clone_object(WEP + "qual_sword");
            weapon->move(TO);
        break;
        case 1:
            weapon = clone_unique(WEP + "singing_bow", 5,
                WEP + "silver_bow");
            weapon->move(TO);
            quiver = clone_object(OBJ + "quiver");
            quiver->move(TO);
            clone_object(WEP + "leaf_arrow")->move(quiver);
            clone_object(WEP + "elven_arrow")->move(quiver);
            clone_object(WEP + "leaf_arrow")->move(quiver);
            clone_object(WEP + "piercing_arrow")->move(quiver);
            clone_object(WEP + "piercing_arrow")->move(quiver);
        break;
        case 2:
            weapon = clone_object(WEP + "warspear");
            weapon->move(TO);
        break;
    }

    clone_object(ARM + "elven_boots")->move(TO);
    clone_object(ARM + "elven_sleeves")->move(TO);

    clone_unique(ARM + "ashchain", 5,
        ARM + "chain")->move(TO);

    clone_unique(ARM + "firebane_cloak", 5,
        ARM + "cloak")->move(TO);

    command("wield all");
    command("wear all");

}

/* Function name: notify_death
 * Description  : Notify onlookers of my death
 * Arguments    : object killer - the object that killed me
 */
void
notify_death(object killer)
{
    ::notify_death(killer);

    if ( killer->query_prop(ELF_CAMP_QUEST) )
    {
        if ( !(killer->query_prop(CAMP_VISITED)) )
             killer->add_prop(CAMP_VISITED, 1);

        if ( !(killer->query_prop(QUALTHAS_KILLED)) )
            killer->add_prop(QUALTHAS_KILLED, 1);

        killer->catch_msg("Now, when Qualthas is dead you may " +
            "report back to the aurak.\n");

    }

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
        remove_prop(LIVE_S_EXTRA_SHORT);

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
        remove_prop(LIVE_S_EXTRA_SHORT);

        if ( shouted == 1 )
            return;

        switch(3)
        {
        case 0:
            command("say It was your last mistake!");
        break;
        case 1:
            command("emote scowls at you.");
        break;
        case 2:
            command("emote draws his weapon and moves to defend his " +
                "companion.");
        break;
        }

        command("assist " + OB_NAME(friend));

        shouted = 1;
        set_alarm(8.0, 0.0, &calm_me());
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
        switch (random(4))
        {
        case 0:
            command("shout To arms! Enemies in the camp!");
        break;
        case 1:
            command("say You will regret that!");
        break;
        case 2:
            command("shout Do not expect I will let you win easily!");
        break;
        case 3:
            command("say Let's test your skills!");
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

    remove_prop(LIVE_S_EXTRA_SHORT);

    ::attacked_by(attacker);
    set_alarm(1.0, 0.0, &react_attack(attacker));
}

string
query_damage_desc(int hit)
{
    string *dam;
    object weapon, *wp;

    wp = query_weapon(-1);

    if ( sizeof(wp) )
        weapon = wp[0];

    switch (weapon->query_wt())
    {
    case W_SWORD:
    case W_KNIFE:
        dam = ({ "In the last moment you jump aside and his attack misses",
            "The flurry of attacks slightly wounds you",
            "You feel mildly wounded by the flurry of attacks",
            "The elf's attacks cause serious wounds as he slices you in " +
            "many places",
            "His attacks reach you, opening deep bleeding wounds in your body",
            "You try to make a dodge but your moves are too slow. As the " +
            "elf gains momentum you feel sharp blades cutting deeply into " +
            "your body, time after time" });
    break;
    case W_POLEARM:
        dam = ({ "but misses badly", "just grazing it",
            "opening a minor wound", "dealing a serious wound",
            "opening a bleeding wound", "almost puncturing it" });
    break;
    case W_MISSILE:
        dam = ({ "You duck, avoiding the frozen missile",
            "You are slightly chilled", "The skin around the wound chills " +
            "for a moment", "Your blood chills for a moment",
            "A cold sensation spreads through your body",
            "Your body almost freezes for a while" });
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

/* Function    : special_attack
 * Description : Qualthas' special attacks.
 * Arguments   : enemy
 * Returns     : 0 - if we want the round to continue
 *               1 - if we are done with this round
 */
int
special_attack(object enemy)
{
    mixed  hitresult;
    object me = TO;
    object weapon, *wp;
    string dam_desc;
    int    pen, dt;
    int    stun_duration = 3 + random(3);

    wp = query_weapon(-1);

    if ( sizeof(wp) )
        weapon = wp[0];
    else
        return 0;

    dt = weapon->query_dt();

    if ( !random(3) && (TO->query_hp() < 2900) && (TO->query_mana() > 149) )
    {
        command("emote silently chants some words and he appears healthier!");
        TO->heal_hp(1300);      // He heals a bit :)
        TO->add_fatigue(200);  // And becomes less tired.
        TO->add_mana(-150);    // But at the cost of mana of course.
    }

    if ( !enemy )
        return 0;

  // Execute the special atack 1 in 4 rounds in average
    if (random(4))
        return 0;

    // Make sure that we can actually attack the target
    if (enemy->query_not_attack_me(me, -1))
    {
        return 1; // round is ended so return 1.
    }

    if ((weapon->query_wielded() == TO) && ((weapon->query_wt() == W_SWORD) ||
        (weapon->query_wt() == W_KNIFE)) )
    {
        pen = TO->query_stat(SS_DEX) + 450;
        hitresult = enemy->hit_me(pen, dt, me, -1);
        dam_desc = query_damage_desc(hitresult[0]);

        enemy->catch_msg(QCTNAME(TO) + " speeds up and his moves begin to " +
            "blur before your eyes. Then he reverses the grip on " +
            "his " + weapon->short() + " and starts to spin towards you. " +
            dam_desc + ".\n");
        tell_watcher(QCTNAME(TO) + " speeds up and his moves begin to " +
            "blur before yoru eyes. Then he reverses the grip on " +
            "his " + weapon->short() + " and starts to spin towards " +
            QTNAME(enemy) + ((hitresult[0] == 0) ? " but misses badly" :
            " hitting " + OBJECTIVE(enemy) + " with a flurry of attacks" ) +
            ".\n", enemy);

   /* If the player has hp < 1/2 his max hp there will be 50% chance that
      he will be unable to attack for a few seconds */

        if ((hitresult[0] > 0) && (enemy->query_hp() > 0) &&
            (enemy->query_hp() < (enemy->query_max_hp() / 2)) && random(2))
        {
            enemy->catch_msg("Your wounds are very serious and you pause for " +
                "a moment trying to catch a breath.\n");
            tell_watcher(QCTNAME(enemy) + " has been seriously wounded and " +
                 PRONOUN(enemy) + " pauses for a moment trying to catch a " +
                 "breath.\n", enemy);
            enemy->add_attack_delay(stun_duration, 1);
        }

        if (enemy->query_hp() <= 0)
            enemy->do_die(me);

        return 0;
    }

    if ((weapon->query_wielded() == TO) && (weapon->query_wt() == W_POLEARM))
    {
        pen = TO->query_stat(SS_DEX) + query_skill(weapon->query_wt()) +
            400;

        string where  = ({ "left leg", "right leg", "left arm", "right arm",
            "head", "stomach", "body" })[random(7)];

        hitresult = enemy->hit_me(pen, dt, me, -1);
        dam_desc = query_damage_desc(hitresult[0]);

        enemy->catch_msg(QCTNAME(TO) + " parries a wild blow from you, " +
            "then twirling around " + PRONOUN(TO) + " counters with a " +
            "vicious stab of " + POSSESSIVE(TO) + " " + weapon->short() +
            " at your " + where + ", " + dam_desc + ".\n" );
        tell_watcher(QCTNAME(TO) + " parries a wild blow from " +
            QTNAME(enemy) + ", then twirling around " + PRONOUN(TO) +
            " counters with a vicious stab of " + POSSESSIVE(TO) + " " +
            weapon->short() + " at " + QTNAME(enemy) + ".\n", enemy);

        if (enemy->query_hp() <= 0)
            enemy->do_die(me);

        return 0;

    }

    if ((weapon->query_wielded() == TO) && (weapon->query_wt() == W_MISSILE))
    {
        pen = TO->query_stat(SS_DEX) + query_skill(weapon->query_wt()) +
            400;

        string where  = ({ "left leg", "right leg", "left arm", "right arm",
            "head", "stomach", "body" })[random(7)];

        hitresult = enemy->hit_me(pen, dt, me, -1);
        dam_desc = query_damage_desc(hitresult[0]);

        enemy->catch_msg(QCTNAME(TO) + " swiftly pulls an arrow out of his " +
            "quiver and almost without aiming shoots at you. " +
            QCTNAME(TO) + " chants a single word and, as the arrow flies " +
            "towards you, its tip covers with frost. " +
            ((hitresult[0] > 0) ? "Just after that you feel piercing, cold " +
            "pain in your " + where + ". " + dam_desc + ".\n" : dam_desc +
            ".\n") );
        tell_watcher(QCTNAME(TO) + " swiftly pulls an arrow out of his " +
            "quiver and almost without aiming shoots at " + QTNAME(enemy) +
            ". " + QCTNAME(TO) + " chants a single word and, as the arrow " +
            "flies towards the target, its tip covers with frost. " +
            ((hitresult[0] > 0) ? QCTNAME(enemy) + " grimaces painfully " +
            "when the frozen missile hits " + POSSESSIVE(enemy) + " " + where +
            ".\n" : QCTNAME(enemy) + " ducks, avoiding the frozen missile.\n"),
            enemy);

        if ( (hitresult[0] > 0) && !random(3) )
            enemy->add_attack_delay(stun_duration, 1);

        if (enemy->query_hp() <= 0)
            enemy->do_die(me);

        return 0;

    }

    return 0;
}

public void
init_living()
{
    init_team_pickup();
    ADD(report_me, "report");
    ADD(report_me, "inform");
    ::init_living();
}

int
report_me(string str)
{
    object who = TP;

    if ( !stringp(str) )
    {
        notify_fail("Report to who?\n");
        return 0;
    }

    if ( str == "qualthas" || str == "Qualthas" || str == "to qualthas" ||
        "to Qualthas" )
    {
        who->catch_msg("You speak with " + QTNAME(TO) + " for a moment.\n");
        tell_room(E(TO), QCTNAME(who) + " speaks with " + QTNAME(TO) +
            " for a moment.\n", ({ who, TO }) );

     // Player rescued Sarist
        if ( who->query_prop(ELF_SAFE) )
        {
            set_alarm(1.0, 0.0, &do_answer("sarist", who));
            return 1;
        }
     // Player found Deorl
        if ( who->query_prop(LOST_SCOUTS) && who->query_prop(FOUND_DEORL) )
        {
            command("say So you say they attacked those draconians? They " +
                "were only to watch them! But I trust Sarist knew what he " +
                "was doing.");
            command("say It is sad to hear about Deorl...");
            command("sigh");
            set_alarm(3.0, 0.0, &do_answer("help__0", who));
            return 1;
        }
     // Player has not found Deorl
        if ( who->query_prop(LOST_SCOUTS) && !(who->query_prop(FOUND_DEORL)))
        {
            command("say Hmm, you haven't found anything? One of " +
                "my scouts saw Sarist though. He was led by draconians " +
                "probably to Pax tharkas.");
            command("emote curses.");
            set_alarm(3.0, 0.0, &do_answer("help__1", who));
            return 1;
        }
     // We havent asked the player for anything
        command("say What? Speak up!");
        return 1;
    }

    write("Report to who?");
    return 0;
}

/* Function name   : ask_help
 * Description     : answer to question about help
 */
public string
ask_help()
{
    set_alarm(1.0, 0.0, &do_answer("help", TP));
    return "";
}

/* Function name   : ask_reward
 * Description     : answer to question about reward
 */
public string
ask_reward()
{
    set_alarm(1.0, 0.0, &do_answer("reward", TP));
    return "";
}

/* Function name   : ask_location
 * Description     : answer to question about location
 */
public string
ask_location()
{
    set_alarm(1.0, 0.0, &do_answer("location", TP));
    return "";
}

/* Function name   : ask_sarist
 * Description     : answer to question about Sarist
 */
public string
ask_sarist()
{
    set_alarm(1.0, 0.0, &do_answer("sarist", TP));
    return "";
}

/* Function name   : ask_deorl
 * Description     : answer to question about Deorl
 */
public string
ask_deorl()
{
    set_alarm(1.0, 0.0, &do_answer("deorl", TP));
    return "";
}

/* Function name   : do_answer
 * Description     : answers to the questions
 * Arguments       : string what  - topic
 *                   object who   - the player who asked
 */
public void
do_answer(string what, object who)
{
    object out_room = E(TO);

    if ( !objectp(who) || E(who) != E(TO))
    {
        return;   /* We wont speak if the player is gone */
    }

  // We will not answer if player has attacked the camp before
    if ( who->query_prop(I_KILLED_ELF) )
    {
        command("say What? Begone!");
        return;
    }

    switch (what)
    {
    case "help":
        who->catch_msg(QCTNAME(TO) + " peers at you.\n");
        say(QCTNAME(TO) + " peers at " + QTNAME(who) + ".\n", who);
 // Add answer for players who did the quest.
   // Player looks reliable and is not doing a quest
        if ( who->query_alignment() > 150 && !(who->query_prop(LOST_SCOUTS)) )
        {
            who->catch_msg(QCTNAME(TO) + " says to you: You look reliable. " +
                "Maybe you can help me, indeed.\n");
            who->catch_msg(QCTNAME(TO) + " says to you: Three days ago " +
                "I sent two scouts to the eastern " +
                "border of the forest. Their task was to keep track on " +
                "the small group of draconians, who were seen roaming " +
                "surprisingly close to Qualinesti.\n");
            say(QCTNAME(TO) + " speaks with " + QTNAME(who) + " for a " +
                "moment.\n", who);
            set_alarm(3.0, 0.0, &do_answer("help1", who));
        }
  // Player doesnt look trustworthy enough
        else if ( who->query_alignment() <= 150 )
        {
            who->catch_msg(QCTNAME(TO) + " says to you: You do not look " +
                "like a person I could trust to. Begone!\n");
            say(QCTNAME(TO) + " says to " + QTNAME(who) + ": You do not " +
                "look like a person I could trust to. Begone!\n");
        }
  // Player has already got a quest but has not found Deorl yet
        else if ( who->query_prop(LOST_SCOUTS) &&
            !(who->query_prop(FOUND_DEORL)) )
        {
            command("say Have you found anything?");
        }
  // Player has already got a quest and found Deorl
        else if ( who->query_prop(LOST_SCOUTS) &&
            who->query_prop(FOUND_DEORL) )
        {
            command("say Hmm, so you found the place? Curse those dracs!");
            set_alarm(1.0, 0.0, &do_answer("help__0", who));
        }
    break;
    case "help1":
        who->catch_msg(QCTNAME(TO) + " says to you: Sarist and Deorl were " +
            "to inform me about every move of that group. They also should " +
            "let me know after reaching the last location, where those " +
            "dracs were seen.\n");
        who->catch_msg(QCTNAME(TO) + " pauses for a moment.\n");
        set_alarm(4.0, 0.0, &do_answer("help2", who));
    break;
    case "help2":
        who->catch_msg(QCTNAME(TO) + " says: But I haven't heard from them " +
            "for almost two days. I do not know what to think about that " +
            "since Sarist is one of my best warriors and he would keep " +
            "me informed.\n");
        set_alarm(3.0, 0.0, &do_answer("help3", who));
    break;
    case "help3":
        command("say Something must have happened there. If you could " +
            "find it out I would decide what to do.");
        who->catch_msg(QCTNAME(TO) + " says to you: I will await your " +
            "return.\n");
        say(QCTNAME(TO) + " says to " + QTNAME(who) + ": I will await " +
            "your return.\n", who);
        who->add_prop(LOST_SCOUTS, 1);
    break;
    case "deorl":
  // Player found Deorl
        if ( who->query_prop(FOUND_DEORL) )
        {
            command("say So you found him? He was a good warrior.");
            command("emote sighs.");
        }
  // Player has not found Deorl
        else if ( !who->query_prop(FOUND_DEORL) )
        {
            command("say I sent him together with Sarist to the eastern " +
                "borders of the forest. I don't know why but I have no " +
                "informations from them.");
        }
    break;
    case "sarist":
  // Player know Deorl's story and tells it to Qualthas but hasnt
  // released Sarist yet
        if ( who->query_prop(FOUND_DEORL) && !(who->query_prop(ELF_SAFE)) )
        {
            command("say Yes, we know about him too.");
            set_alarm(2.0, 0.0, &do_answer("help__0", who));
        }
  // Player has already warned Qualthas (after founding Deorl) but he has not
  // released Sarist yet.
        else if ( who->query_prop(WARN_QUALTHAS) &&
            !(who->query_prop(ELF_SAFE)) )
        {
            command("say Did you succeed to get into Pax Tharkas? He must be " +
                "held there.");
        }
  // Player released Sarist, final sequence.
        else if ( who->query_prop(ELF_SAFE) )
        {
            out_room->final_sequence("seq1", who);
//            gSeq_started = 1;
        }
  // Other cases
        else
            command("say Sarist is one of my best scouts. I sent him to " +
                "the eastern borders of the forest to keep track on the " +
                "group of draconians. I have received no messages from him " +
                "since then.");
    break;
    case "reward":
        if ( who->query_prop(ELF_SAFE) )
            set_alarm(1.0, 0.0, &do_answer("sarist", who));
        else if ( who->query_prop(LOST_SCOUTS) &&
            !(who->query_prop(ELF_SAFE)) )
            command("say Find Sarist first!");
        else
            command("say What?");
    break;
    case "help__0":
        command("say One of scouts saw Sarist. He was led by draconians, " +
            "probably to Pax Tharkas. Damn! I need him!");
        command("emote goes hmm.");
        set_alarm(2.0, 0.0, &do_answer("help__1", TP));
    break;
    case "help__1":
        who->catch_msg(QCTNAME(TO) + " asks you: Maybe you could get " +
            "into Pax Tharkas and look for Sarist? " +
            "I know it is not easy task but I can not send my " +
            "warriors there. And you look like a person that could do it.\n");
        who->catch_msg(QCTNAME(TO) + " says to you: If you can find and " +
            "help him I will reward you greatly.\n");
        if ( !(who->query_prop(WARN_QUALTHAS)) )
            who->add_prop(WARN_QUALTHAS, 1);
        say(QCTNAME(TO) + " asks " + QTNAME(who) + " about something.\n", who);
    break;
    case "location":
 // Player is not doing a quest
        if ( !(who->query_prop(LOST_SCOUTS)) )
        {
            command("say What are you talking about?");
            command("emote goes hmm.");
        }
 // Player is doing a quest
        else
        {
            command("say I sent them to the eastern part of the forest. They " +
                "are to watch that group of draconians so you should find " +
                "them somewhere close to the Newports road.");
            command("say But I think you will be found by them first.");
            command("emote grins.");
        }
    break;
    default:
        command("say I do not quite understand...");
    break;

    }

}

public int
second_life(object killer)
{
    K_KILL_LOG("kills", "Qualthas", killer);
    return 0;
}

