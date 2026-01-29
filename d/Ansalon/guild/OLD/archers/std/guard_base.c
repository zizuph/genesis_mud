/* File name: guard_base.c
 * (Based on /d/Krynn/qualinesti/std/elf_base.c)
 *
 * Elven archer, one of warriors that guards their guild..
 *
 * Blizzard, 05.11.2003
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
#include "/d/Krynn/qualinesti/local.h"
#include "../guild.h"

inherit AUTO_TEAM
inherit M_FILE

inherit "/std/act/domove";
inherit "/std/act/action";

public void attack_ranged(object *enemies, object room, string location);
public void attack_ranged_enemies(object *enemies, object room,
                                  string location);
public void attack_him(object *enemy, string room);
void        arm_me();


#define I_HAVE_MONEY     "_i_have_money"

#define EHEIGHT          ({ 180 + random(15), 170 + random(15) })

#define TREE_ROOM        GUILD_ROOM + "guard_tree1"

void    setup_elf();

string *warrior_descr = ({ " polishing " + POSSESSIVE(TO) + " weapon",
    " standing silently", " watching the area",
    " pacing nervously around, watching the forest",
    " staring into the forest", " watching the trees", "" });
string *archer_descr = ({ " checking " + POSSESSIVE(TO) + " arrows",
    " pacing nervously around, watching the forest",
    " balancing " + POSSESSIVE(TO) + " arrows", " testing " + POSSESSIVE(TO) +
    " bow", " carefully studying the forest", " watching the trees", "" });

string *adj_list = ({ "tall", "young", "proud", "alert", "long-legged",
    "watchful", "lean", "solemn", "slim", "noble" });
string *adj_list2 = ({ "blond-haired", "silver-haired", "blue-eyed",
    "bright-eyed", "brown-eyed", "brown-haired", "dark-haired",
    "long-haired" });

string adj1, adj2, gType;

int    type, shouted;

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
    if ( CAN_SEE(TO, TP) && CAN_SEE_IN_ROOM(TO) )
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
        set_elf_type(random(2));
}

void
setup_elf()
{

    set_base_stat(0, 125 + random(35));
    set_base_stat(1, 165 + random(35));
    set_base_stat(2, 150 + random(35));
    set_base_stat(3, 135 + random(15));
    set_base_stat(4, 135 + random(15));
    set_base_stat(5, 135 + random(15));

    set_skill(SS_WEP_KNIFE, 150);
    set_skill(SS_DEFENCE, 130);
    set_skill(SS_PARRY, 130);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_UNARM_COMBAT, 70);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_2H_COMBAT, 100);

    if ( gType == "warrior" )
    {
        add_name("warrior");
        set_skill(SS_WEP_SWORD, 150);
        set_skill(SS_WEP_POLEARM, 150);
        add_descr(ONE_OF(warrior_descr));
        set_exp_factor(145);
    }
    else
    if ( gType == "archer" )
    {
        add_name("archer");
        set_skill(SS_WEP_MISSILE, 150);
        set_skill(SS_WEP_SWORD, 150);
        add_descr(ONE_OF(archer_descr));
        set_exp_factor(135);
        add_act("take arrows");
    }
    else
    if ( gType == "scout" )
    {
        add_name("scout");
        set_skill(SS_SNEAK, 70);
        set_skill(SS_HIDE, 70);
        set_skill(SS_WEP_SWORD, 140);
        set_skill(SS_WEP_MISSILE, 140);
        set_random_move(20);
        set_restrain_path(FDIR);
        set_exp_factor(115);

    }
}

void
create_krynn_monster()
{
    int gen;

    set_name("elf");
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

    set_act_time(65 + random(50));
    add_act("pace");
    add_act("emote stares into the forest.");
    add_act("say The forest is so silent. That's not normal.");
    add_act("say We should be prepared. Verminaard's forces are too close.");
    add_act("say Where are all those dracs are coming from?!");
    add_act("say A strange lone human with a green gem placed in his " +
        "chest was seen in the forest. Scouts tried to capture him but he " +
        "lost them somehow.");
    add_act("say More and more dracs are seen in Solace area. They seem to " +
        "be looking for something.");
    add_act("say Those draconians are cowards, they will not dare to " +
        "invade our home.");
    add_act("say It seems the red dragonarmy is preparing the attack on " +
        "Qualinost. The Speaker of the Suns is considering leaving the " +
        "city.");
    add_act("emote stares into the sky.");
    add_act("say The war verges upon Qualinesti. It's a bad time for us.");
    add_act("emote sighs.");
    add_act("say Why only evil dragons are flying above our heads?");
    add_act("say Pax Tharkas used to be a monument of peace... now it's " +
        "a nest of evil!");

    add_cact("emote is moving with an amazing speed.\nYou realize " +
        PRONOUN(TO) + " is a way quicker than you.");
    add_cact("say You are no match for me.");
    add_cact("emote scowls at you.");

   
    set_default_answer("Your question has been ignored.\n");

    add_ask(({ "archers", "elven archers", "guild", "training", 
        "join", "joining", "camp", "base" }), 
        "say You should speak with the Senator or with the Prince if you " +
        "want to know that.", 1);
    add_ask(({ "draconians", "dracs", "draconian", "dragonarmies",
        "dragonarmy", "red dragonarmy" }),
        "say For now they stay away from the forest but some day " +
        "they will dare to enter it, that's sure. But it will their " +
        "last mistake.", 1);
    add_ask(({ "forest", "Qualinesti", "qualinesti", "city" }),
        "say Our task is to protect this forest. If dragonarmies dare " +
        "to enter it, nothing will stand on their way to Qualinost.", 1);
    add_ask(({ "Qualinost", "qualinost" }),
        "say The city is well protected, but if evil dragons come " +
        "we will not be able to defend it. The Speaker of the Suns seems " +
        "to realize that too.", 1);
    add_ask(({ "Speaker of the Suns", "speaker of the suns" }),
        "say He is wise and I trust him. If he decides to leave the " +
        "city I will follow him. But I hope this will never happen.", 1);
    add_ask(({ "dragon", "dragons", "evil dragons", "evil dragon" }),
        "say I saw the red dragon flying over the forest. It left " +
        "towards Pax Tharkas.", 1);
    add_ask(({ "pax", "Pax Tharkas", "pax tharkas" }),
        "say Yes, Pax Tharkas is a great fortress. But as long as " +
        "the dragonarmy controls it I would not wish anyone to " +
        "enter the city.", 1);
    add_ask(({ "dwarves", "daergar", "Daergar" }),
        "say I saw a lone dwarf who was traveling towards Pax Tharkas. " +
        "If it appears Daergar are trading with dragonarmies, they will " +
        "regret it!", 1);
    add_ask(({ "Verminaard", "verminaard" }),
        "say I have never seen him, but I have heard he not only a " +
        "skilled fighter but also a powerful priest.", 1);
      
    add_prop(CONT_I_HEIGHT, EHEIGHT[gen] + random(10));
    add_prop(CONT_I_WEIGHT, 36000 + random(9000) );
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_SEE_DARK, 2);
    add_prop(LIVE_I_QUICKNESS, 50);
    add_prop(LIVE_I_ATTACK_THIEF, 0);

    if ( !random(500) )
        add_leftover(OBJ + "skull", "skull", 1, "", 0, 1);
        
    set_aggressive(VBFC_ME("check_aggressive"));
    create_elf_npc();

    set_hp(query_max_hp());

    seteuid(getuid(TO));
    arm_me();
    set_pick_up_team(({"_qualinesti_elf_"}));
}

int
query_option(int opt)
{
    if ( opt == OPT_UNARMED_OFF )
       return 1;
}

void
arm_me()
{
    object weapon, quiver, arrows, dagger;

   /* Clone coins */

    if (!TO->query_prop(I_HAVE_MONEY))
    {
        TO->add_prop(I_HAVE_MONEY, 1);
        MONEY_MAKE_GC(10 + random(10))->move(TO);
        MONEY_MAKE_SC(5 + random(10))->move(TO);
    }

   /* Clone weapon */

    switch(gType)
    {
    case "warrior":
        switch( random(7) )
        {
            case 0..1:
                weapon = clone_object(WEP + "shortsword");
                weapon->move(TO);
                dagger = clone_object(WEP + "edagger");
                dagger->move(TO);
            break;
            case 2..4:
                weapon = clone_object(WEP + "elongsword");
                weapon->move(TO);
                if (!random(3))
                {
                    dagger = clone_object(WEP + "edagger");
                    dagger->move(TO);
                }
            break;
            case 5..6:
                weapon = clone_object(WEP + "warspear");
                weapon->move(TO);
            break;
        }
    break;
    case "scout":
        switch(random(3))
        {
        case 0:
            weapon = clone_object(WEP + "elongsword");
        break;
        case 1:
            weapon = clone_object(WEP + "ash_bow");
        break;
        case 2:
            weapon = clone_object(WEP + "warspear");
        break;
        }
        weapon->move(TO);
    break;
    case "archer":
        weapon = clone_object(WEP + "ash_bow");
        weapon->move(TO);
        quiver = clone_object(OBJ + "quiver");
        quiver->move(TO, 1);

        switch(random(2))
        {
        case 0:
            arrows = clone_object(WEP + "piercing_arrow");
        break;
        case 1:
            arrows = clone_object(WEP + "leaf_arrow");
        break;
        }
        arrows->move(quiver, 1);
        clone_object(WEP + "elven_arrow")->move(quiver, 1);
        clone_object(WEP + "leaf_arrow")->move(quiver, 1);
        clone_object(WEP + "elven_arrow")->move(quiver, 1);

    break;
    }

  /* Clone armours */

    clone_object(ARM + "elven_boots")->move(TO, 1);
    
    if ( !random(2) )
        clone_object(ARM + "elven_sleeves")->move(TO, 1);
    
    clone_object(ARM + "cloak")->move(TO, 1);

    switch(random(3))
    {
        case 0:
            clone_object(ARM + "lchain")->move(TO);
        break;
        case 1 :
            clone_object(ARM + "chain")->move(TO);
        break;
        case 2:
            clone_object(ARM + "stud_arm")->move(TO);
        break;
    }

    command("wield all");
    command("wear all");
}

string
long_desc()
{
    return "This " + short() + " is quite a bit taller than the average " +
        "human. " + (query_gender() == 1 ? "She looks rather young but " +
        "you cannot be sure her age since elves are known of their long " +
        "lives. She" : "Like the others here, he looks rather young but " +
        "since elves are known of their long lives you are not able to " +
        "estimate his real age. He") + " is one of the elite elven " +
        "warriors, that have set their training base here.\n";

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
        remove_descr();

  // remove the permission for entering the camp.
    if ( ob->query_prop(ELVEN_TOKEN) )
        ob->remove_prop(ELVEN_TOKEN);

    ::aggressive_attack(ob);

    if ( shouted == 1 )
        return;
        
    switch(random(3))
    {
    case 0:
        command("say You will never leave this place alive!");
        break;
    case 1:
        command("emote scowls madly at you");
        break;
    case 2:
        command("say A dragonarmy spy! Kill him!");
        break;
    }

    shouted = 1;
    set_alarm(8.0, 0.0, &calm_me());

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

        if ( shouted == 1)
            return;
            
        switch(random(3))
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
            command("shout We are being attacked!");
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
    object *enemy;
    enemy = TO->query_enemy(-1);
    
    if ( (E(TO))->query_sniper_room() )
        attack_him(enemy, (E(TO))->query_sniper_room());

    if (!attacker->query_prop(I_KILLED_ELF))
        attacker->add_prop(I_KILLED_ELF, 1);

    if ( attacker->query_prop(ELVEN_TOKEN) )
        attacker->remove_prop(ELVEN_TOKEN);

    remove_descr();
    ::attacked_by(attacker);
    set_alarm(1.0, 0.0, &react_attack(attacker));
}

public void
hook_attack(object enemy)
{
    if ( (E(TO))->query_sniper_room() )
        attack_him( ({ enemy }), (environment(enemy))->query_sniper_room() );

}

string
query_damage_desc(int hit)
{
    string *dam;
    object wp = query_weapon(-1)[0];

    switch ( wp->query_wt() )
    {
    case W_SWORD:
    case W_KNIFE:
        dam = ({ "but misses badly", "cutting a shallow wound in your body",
            "dealing a minor wound to your body", "tearing a serious wound " +
            "in your body", "horribly wounding you",
            "tearing a gash wound in your body" });
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
    object me = TO;
    object wp, *wps;
    int    dt, pen;
    mixed  hitresult;
    string dam_desc, *where;
    
    wps = query_weapon(-1);

    if ( sizeof(wps) )  // Check if the elf has any weapons
        wp = wps[0];
    else
        return 0;       // if not we continue the round without special
    
    if ( !enemy )
        return 0;
    
      // Execute the special attack 1 in 5 rounds on average
    if (random(5))
        return 0;

    if ( !objectp(wp) )
        return 0;
    
    dt = wp->query_dt();
          
    if ((wp->query_wielded() == TO) && ((wp->query_wt() == W_SWORD) ||
        (wp->query_wt() == W_KNIFE)) )
    {
        pen = TO->query_stat(SS_DEX) + query_skill(wp->query_wt()) +
            300;

        hitresult = enemy->hit_me(pen, dt, me, -1);
        dam_desc = query_damage_desc(hitresult[0]);

        enemy->catch_msg(QCTNAME(TO) + " dodges aside as " +
            "you try to hit " + OBJECTIVE(TO) + ", and then rushes with a " +
            "counterattack. Moving with unbelievable quickness " +
            PRONOUN(TO) + " slashes at you with " + POSSESSIVE(TO) +
            " " + wp->short() + ", " + dam_desc + ".\n");
        tell_watcher(QCTNAME(TO) + " dodges aside as " + QTNAME(enemy) +
            " tries to hit " + OBJECTIVE(TO) + ", and then rushes with a " +
            "counterattack. Moving with unbelievable quickness the elf " +
            "slashes at " + QTNAME(enemy) + " with his " + wp->short() +
            ".\n", enemy);

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

public void
init_living()
{
    init_team_pickup();
    ::init_living();
}

public void
attack_ranged_enemies(object *enemies, object room, string location)
{

    if (!query_attack())
    {
        command("emote stretches and picks up his bow.");
        attack_ranged(enemies, room, location);
    }
}

public void
attack_ranged(object *enemies, object room, string location)
{
    int size;
    object target;
    string description;

    enemies = filter(enemies, &operator(==)(room) @ &environment());
    size = sizeof(enemies);

    if (size)
    {
    target = enemies[random(size)];
    description = implode(target->query_adjs(), " ") + " " +
                  target->query_race_name();
    command("shoot " + description + " " + location);

    set_alarm(2.0, 0.0,
          &attack_ranged(enemies, room, location));
    }
}

public void
attack_him(object *enemy, string room)
{
    object archer;

    if ( room )
    {
        seteuid(getuid(TO));
        (room)->load_me();
    }
    
    archer = present("_guard_", find_object(room));

 //   DEBUG("Archer is: " + MASTER_OB(archer));
 //   DEBUG("We ask him to shoot at: " + MASTER_OB(environment(TO)));

    archer->attack_ranged_enemies(enemy, environment(TO), "ground");
}
