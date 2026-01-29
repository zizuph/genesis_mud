/* File name: porthios.c
 *
 * Porthios, Heir to the Speaker of the Suns, Leader of the Elven Archers.
 *
 * Blizzard, 05.11.2003
 */

#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <money.h>
#include "/d/Krynn/qualinesti/local.h"

inherit  "/lib/unique";
inherit  AUTO_TEAM
inherit  M_FILE
inherit  "/d/Krynn/std/equip";

object                quiver;
int                   shouted;

#define ARMOUR1       (ARM + "ashchain")
#define ARMOUR2       (ARM + "chain")
#define ARMOUR3       (ARM + "firebane_cloak")
#define ARMOUR4       (ARM + "elven_sleeves")
#define ARMOUR5       (ARM + "cloak")
#define ARMOUR6       (ARM + "elven_boots")

#define WEAPON1       (WEP + "qual_sword")
#define WEAPON2       (WEP + "warspear")
#define WEAPON3       (WEP + "silver_bow")

#define QUIVER        (OBJ + "quiver")
#define ARROWS        (WEP + "piercing_arrow")


int
check_aggressive()
{
    return TP->query_prop(I_KILLED_ELF);
}

void
create_krynn_monster()
{
    
    set_name("porthios");
    set_living_name("porthios");
    set_race_name("elf");
    set_adj("noble");
    add_adj("sharp-eyed");
    set_title("Kanan, the Prince of Qualinesti, Leader of the " +
        "Elven Resistance");
    set_long("This tall, well-built elf has a commanding air about him. " +
        "He firmly wields his weapon and you have no doubts he knows how " +
        "to use it. Althought he appears stern, a hint of warmth and " +
        "compassion can be seen in his eyes.\n");
    set_gender(0);
    set_alignment(1200);
    set_knight_prestige(-600);
    
    set_stats(({ 200, 240, 220, 180, 180, 185 }));

    set_skill(SS_WEP_KNIFE, 150);
    set_skill(SS_WEP_MISSILE, 150);
    set_skill(SS_WEP_POLEARM, 150);
    set_skill(SS_2H_COMBAT, 150);
    set_skill(SS_PARRY, 150);
    set_skill(SS_DEFENCE, 150);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    
    set_exp_factor(160); 
   
    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_HEIGHT, 185);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_ATTACK_THIEF, 0);
    add_prop(LIVE_I_SEE_DARK, 2);
    add_prop(LIVE_I_QUICKNESS, 130);    
    set_aggressive(VBFC("check_aggressive"));
    set_introduce(1);
    set_pick_up_team(({"_qualinesti_elf_"}));

    set_hp(query_max_hp());

    set_act_time(10 + random(2));
    add_act("emote paces nervously.");
    add_act("say Dragonarmies keep sending more and more draconians to Pax " +
        "Tharkas! We have to keep patroling the forest.");
    add_act("say We must weaken the dragonarmy forces before they launch " +
        "the attack on Qualinost!");
    add_act("say The scouts have seen a red dragon flying over Pax Tharkas. " +
        "It seems Verminaard indeed got a new pet.");
    add_act("say Some of those draconians are quite skilled, but they " +
        "are no match for us!");
        
    add_cact("emote scowls at you.");
    add_cact("say You really think you can stand against me?!");
    add_cact("say Defend yourself!");
    add_cact("take arrows");
    
    set_default_answer(VBFC_ME("def_answer"));
    add_ask(({ "draconians", "draconian" }),
        "say Yes, I realize their presence. We are here to stop them " +
        "from entering our forest. Otherwise Qualinost may be in danger.", 1);
    add_ask(({ "pax", "pax tharkas", "Pax Tharkas", "Pax tharkas" }),
        "say It is bad that Dragonarmies control that city. But we " +
        "cannot afford attacking them. All we can do is to destroy their " +
        "troops before they reach the fortress.", 1);
    add_ask(({ "speaker of the suns", "Speaker of the Suns" }),
        "say Why are you asking? He is a wise person and will not risk the " +
        "life even a single subject until he is convinced that such risk " +
        "is necessary, but we can't just sit here and watch draconians " +
        "destroying our homeland. That is why I am here, even if I should " +
        "be with him now...", 1);
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
        "we may have no choice. However, together with my people we will " +
        "do all to defend our land.", 1);
    add_ask(({ "Qualinesti", "qualinesti", "forest" }),
        "say This forest is the last thing that stops Dragonarmies from " +
        "attacking Qualinost. If they cross its borders, they will " +
        "regret that.", 1);
    
    seteuid(getuid(TO));
    
    equip(({
        (random(2) ? clone_unique(WEAPON1, 10, WEAPON2) :
            clone_unique(WEAPON3, 10, WEAPON2)),
            clone_unique(ARMOUR1, 10, ARMOUR2),
            clone_unique(ARMOUR3, 8,  ARMOUR5),
            ARMOUR4, ARMOUR6 }));
    
    quiver = clone_object(QUIVER);
    quiver->move(TO, 1);
    
    clone_object(ARROWS)->move(quiver, 1);
    clone_object(ARROWS)->move(quiver, 1);
    clone_object(ARROWS)->move(quiver, 1);
    clone_object(ARROWS)->move(quiver, 1);
    clone_object(ARROWS)->move(quiver, 1);

}

string
def_answer()
{
    command("emote goes hmmm.");
    command("say What? Speak up!");
    
    return "";
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

public void
hook_attacked(object attacker)
{     
    if (!attacker->query_prop(I_KILLED_ELF))
        attacker->add_prop(I_KILLED_ELF, 1);

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
    string dam_desc, *where;
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
        TO->heal_hp(1500);      // He heals a bit :)
        TO->add_fatigue(200);  // And becomes less tired.
        TO->add_mana(-100);    // But at the cost of mana of course.
    }
        
    if ( !enemy )
        return 0;
        
  // Execute the special atack 1 in 4 rounds in average
    if (random(4))
        return 0;
    
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
        
        where  = ({ "left leg", "right leg", "left arm", "right arm",
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
        
        where  = ({ "left leg", "right leg", "left arm", "right arm",
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

/*
public void
init_living()
{
    init_team_pickup();
    ADD(suggest_member, "suggest");
    ::init_living();
}

int
suggest_member(string str)
{
    
}
*/
