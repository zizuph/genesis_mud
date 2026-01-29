/*
 * Who          : Kadez de-Toron, a dangerous brutal male minotaur
 * Located      : The Toron minotaur village near Crystalmir Lake outside
 *                Solace.
 *                /d/Krynn/solace/lake/npc
 * Description  : The chiftain for the tribe. I very touch opponent with a
 *                special attack hitting everyone in the room, also a special
 *                hit against bouncers.
 * Base file    : Made to inherit "minotaur_base".
 * Made by      : Cherek, Feb 2007
 */

#include "../local.h"
#include <wa_types.h>
#include <ss_types.h>
#include <filter_funs.h>

inherit MINOTAUR;

inherit "/lib/unique";

#define G_AXE OBJ + "gigantic_axe.c"
#define CHAMPRON OBJ + "champron.c"
#define CHAINMAIL OBJ + "chainmail.c"

/* Gives a unique prop for everyone who attacked him, makes him 
   recognize them if they return. */

int unique_id = random(1000000);
string _i_attacked_kadez = "_i_attacked_kadez"+unique_id;

void arm_me(object me);

void
create_minotaur()
{
    set_type("CHIEFTAIN");
    
    set_adj("brutal");
    set_adj("dangerous");

    set_name("kadez");
    set_living_name("_kadez");	    
    set_title("de-Toron, Mighty Chieftain of the Toron tribe of Kothas");
    set_gender(G_MALE);           
    set_long("Before you stands a large creature. He is half human and " +
             "half bull leading you to believe this must be a minotaur. " +
             "His skin is thick and covered with a deep brown fur but his " +
             "most noticable feature are the two long and very sharp horns " +
             "growing on his head. This is the leader of the Toron tribe " +
             "minotaurs.\nHe looks extremely intimidating.\nHe is very " +
             "tall and muscular for a minotaur.\n");

    set_gender(G_MALE);

    set_stats(({ 200+random(40), 250+random(40), 200+random(40), 
                 100+random(20), 100+random(20), 180+random(40) }));

    set_skill(SS_PARRY, 80);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_WEP_SWORD, 65);
    set_skill(SS_WEP_AXE, 90);
    set_skill(SS_UNARM_COMBAT,90); 
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 100);

    add_prop("_ranger_m_not_disarm", 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    remove_prop(LIVE_I_NEVERKNOWN);

    set_act_time(40);
    add_act("emote thrashes his head back and forth.");
    add_act("emote laughs silently at you.");
    add_act("emote grumbles unhappily");
    add_act("say I shall lead us to vengeance. ");
    add_act("say If you are from the Orilg tribe you will not get out of " +
            "here alive. Come to think of it, you probably will " +
            "not anyway!");
    add_act("emote cackles with glee");
    add_act("say You have no business here. " +
            "Get out while you can still walk.");

    set_cact_time(10);
    add_cact("say You will regret this.");

    set_default_answer("say I have no time for you. You shall be quiet.",1); 
     
    add_ask(({"quest", "help", "task"}), 
              "emote mutters: Go talk to Takchuk, if anything it will " +
              "at least get you out of my face.", 1); 
        
    add_ask("takchuk", "emote shouts: Are you deaf? Go talk " +
            "to him and stop bothering me!", 1); 
            
    set_alarm(0.1, 0.0, &arm_me(TO));

    setuid();
    seteuid(getuid());

}

int query_max_hp() 
{     
    return 10000;  /* A lot of extra HP */ 
}

void arm_me(object me) /* NOTE: Function called using an alarm. */ 
{

    object headpiece;

    if (random(2))
    {    
        headpiece = clone_unique(CHAMPRON, 5);
        headpiece->move(me, 1);
    }

    clone_object(G_AXE)->move(me, 1);
    clone_object(CHAINMAIL)->move(me, 1);
    me->command("wield all"); 
    me->command("wear all");
}

void
return_intro(object me) /* NOTE: Function called using an alarm. */ 
{
    me->command("introduce myself");
}

void
add_introduced(string str)
{
    object ob = find_player(lower_case(str));
    if(ob && !ob->query_met(TO))
    {
        set_alarm(1.0, 0.0, &return_intro(TO));
    }
}

/*
 * Function name: bouncer
 * Description  : This function is called when a player who already has
 *                attacked Kadez enters the room. Deal alot of damage.
 *                Made to avoid "bouncing". Also makes it a little 
 *                tricky to fight him in a team since you can't wimp and
 *                re-enter without getting hurt badly.
 */
 
void bouncer(object ob, object kadez)
{
    string *proplist;
              
    if(ob->query_prop("_i_attacked_kadez"))
    {
        tell_room(environment(kadez), "\n" + QCTNAME(kadez) + 
                  " notices " + QTNAME(ob) + " entering and makes " +
                  "a gigantic leap across the room. " + QCTNAME(ob) + 
                  " is badly impaled by the sharp horns. \n\n", ob);

        ob->catch_msg("\n" + QCTNAME(kadez) + " notices you entering " +
                      "and makes a gigantic leap across the room. " +
                      "Before you are able to react you are badly " +
                      "impaled by his sharp horns, \n\n");

        ob->hit_me(800+random(800), W_IMPALE, TO, 1);

        kadez->attack_object(ob);
        
    }
}

void
attacked_by(object ob)
{
    ob->add_prop("_i_attacked_kadez", 1);

    command("emote snarls: The proud Toron tribe has suffered enough! " +
            "Prepare to die " + ob->query_nonmet_name() + ".");
                        
}

public void
notify_you_killed_me(object player)
{

    if (player->query_npc()) 
    {
        return;
    }

    setuid();
    seteuid(getuid());
    write_file(LOGS + "kadez_kill_log.txt", ctime(time()) + " | " + 
               player->query_real_name() + " was killed by Kadez. \n");
}


/*
 * Function name: special_attack
 * Description  : Adds a special attack that hits everyone in the 
 *                room that is fighting him. The attack always 
 *                aims at the head of the enemy.
 */

int
special_attack(object enemy)
{
    mixed hitresult;
    string how1, how2, weapon;
    object* enemies;
    object current_enemy;
    object enemylist;
    string* how_descriptions = ({});

    weapon = query_weapon(W_BOTH)->short();

    /* No attack if he doesnt have his axe. */

    if(weapon != "gigantic two-handed battleaxe")
    {
        return 0;
    }
    
    if(random(4))
    {
        return 0;
    }
    
    enemies = query_enemy(-1);
    
    tell_room(environment(TO), "\n" + QCTNAME(TO) + 
              " makes an enormous swing with his " + weapon + 
              ", trying to chop the head off all his enemies with " +
              "one single blow! \n\n");

    for(int i = 0; i < sizeof(enemies); i++)
    {
        current_enemy = enemies[i];

        if(environment(current_enemy) == environment(TO))
        {
             hitresult = current_enemy->hit_me(400+random(600), 
                                        W_IMPALE, TO, -1, A_HEAD);

             if(hitresult[0] < 0)
             {
                 hitresult[0] = 0;
             }
 
             switch(hitresult[0])
             {
                 case 0:
                     how1 = "You manage to duck just in time. Phew.";
                     how2 = "manages to duck just in time.";
                     break;
                 
                 case 1..10:
                     how1 = "You are grazed but did not lose your head. " +
                            "Literally.";
                     how2 = "looks grazed.";
                     break; 
                 
                 case 11..15: 
                     how1 = "BOING! Your head is spinning and you see " +
                            "stars. You thank higher powers that you " +
                            "were hit with the flat side of the axe. " +
                            "Therefore you still have a head!";
                     how2 = "looks hurt.";
                     break;
                 
                 case 26..40:
                     how1 = "You are hit with tremendous force. Blood " +
                            "begins to flow from your head and your " +
                            "vision is blurred, For an instant you " +
                            "wonder how much damage a head can take " +
                            "before it falls off.";
                     how2 = "looks very hurt. ";
                     break;

                 default:
                     how1 = "Bloods spurts everywhere and you feel large " +
                            "chunks of flesh part with your neck. You " +
                            "are amazed to find your head still attached " +
                            "to the rest of your body.";
                     how2 = "looks badly wounded. ";
            }

            how_descriptions += ({how2});

            current_enemy->catch_tell(how1 + "\n\n");

            /* An extra message of the attack was fatal. */ 
            
            if (current_enemy->query_hp() <= 0)
            {
                tell_watcher(QCTNAME(TO) + " bellows victoriously " +
                             "while the lifeless body of " + 
                             QTNAME(current_enemy) + " falls to the " +
                             "ground. " + HIS(current_enemy) + " head " +
                             "only attached by thrashed strings of bloody " +
                             "skin.\n");

                current_enemy->catch_msg(QCTNAME(TO) + " quickly makes " +
                                         "a second swing with his " + weapon + 
                                         "\n\n You feel death's grasp as " +
                                         "the cold metal buries itself into " +
                                         "your neck.\n\n");

                current_enemy->do_die(TO);
            }
        }
    }

    for(int i = 0; i < sizeof(how_descriptions); i++)
    {
        current_enemy = enemies[i];
	if(current_enemy && TO)
	{
	    tell_room(environment(TO), 
                  QTNAME(current_enemy) + " " + how_descriptions[i] + 
                  "\n", current_enemy);
	}
    }

    return 1;

}
