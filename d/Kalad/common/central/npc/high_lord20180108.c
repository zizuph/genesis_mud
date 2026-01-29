/*
 * High Lord of Kabal.
 * MADE BY: Korat
 * DATE: Feb 14 1995
 *
 * 2005-08-29 - Cotillion
 * - Stuns were cloned into the void, fixed
 *
 * 2011/08/04 Lavellan - Fixed Gunthar location.
 */

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"
#include <stdproperties.h>

//#define GUNTHAR "/d/Krynn/solamn/vkeep/mnstrs/gunthar"
#define GUNTHAR "/d/Krynn/guilds/knights/guildhall/npcs/gunthar"

void
create_monster()
{
    ::create_monster();
    set_name("urian");
    add_name("high lord");
    add_name("lord");
    set_living_name("urian");
    set_race_name("human");
    set_adj("noble");
    add_adj("terrifying");
    set_long("This man seems to wear the symbol of his position as "+
        "the High Lord, a large golden ring, with pleasure. Dressed "+
        "in his battle equipment, this man can frighten any man just by "+
        "the look. You wonder if he wears it for that purpose, but then "+
        "you see his face. Those sharp and piercing eyes seems to dig "+
        "through all your layers of protection, making you think "+
        "he soon will know all your thoughts and feelings! You tear your "+
        "eyes away. A dangerous man indeed, being an excellent warrior "+
        "combined with having a sharp brain.\n");
   
    set_stats(({165,204,197,113,103,175}));
    set_alignment(200);
    set_skill(SS_WEP_CLUB,100);
    set_skill(SS_WEP_KNIFE,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_AWARENESS,100);
    set_skill(SS_SPELLCRAFT,40);
   
    set_act_time(5);
    add_act(({"say Well...well...and who are you, may I ask!","fume ."}));
    add_act("emote twists his ring around slowly.");
    add_act("say You may talk to my cleric. I have little time to use "+
        "on your kind.");
    add_act("emote studies some of the papers on his desk.");
    set_cact_time(1);
    add_cact("say So you have a deathwish!");
    add_cact("I would hate to be forced to kill again. I have others to "+
        "do that for me.");
    add_cact("grin all");
    add_cact("whipsnap");
    add_cact("whiprattle");
    set_title("the High Lord of Kabal");
    add_speak("Talk to my cleric. I do not have the time for this.\n");
    set_default_answer("The High Lord says: Quit wasting my time!\n");
    add_ask(({"job","quest","help","task"}),"The High Lord says: "+
        "Talk to my cleric. Maybe he can help you out.\n");
    set_knight_prestige(-10);
    add_prop(NPC_M_NO_ACCEPT_GIVE,1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_SEE_DARK,20);
    trig_new("%w 'attacks' %s","react_attack");
    trig_new("%w 'rescues' 'you' %s","react_resque");
}
void
arm_me()
{
    object wep, arm;
    seteuid(getuid(TO));
    arm = clone_object("/d/Kalad/common/central/arm/lord_ring");
    arm -> move(TO);
    arm = clone_object("/d/Kalad/common/central/arm/lord_breastplate");
    arm -> move(TO);
    arm = clone_object("/d/Kalad/common/central/arm/lord_boots");
    arm -> move(TO);
    arm = clone_object("/d/Kalad/common/central/arm/lord_gauntlets");
    arm -> move(TO);
    arm = clone_object("/d/Kalad/common/central/arm/lord_greaves");
    arm -> move(TO);
    arm = clone_object("/d/Kalad/common/central/arm/lord_helm");
    arm -> move(TO);
    command("wear all");
    command("remove helm");
    wep = clone_object("/d/Kalad/common/central/wep/lord_whip");
    wep -> move(TO);
    command("wield all");
    MONEY_MAKE_PC(random(5)+4)->move(TO,1);
}

/* this is the assist routine. */

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        command("wear helm");
        command("lower visor");
        command("kill " + lower_case(ob->query_real_name()));
        command("say How dare you!!");
        command("shout Guuuaarrrdddssss!!!");
        command("whipslash "+(lower_case(ob->query_real_name())));
    }
}   

/* this is the attack routine, that will be started if */
/* someone attacks someone else. */
   
int
react_attack(string who, string dummy){
    string *str_check;
    if(who){
        who = lower_case(who);
        str_check = explode(dummy, " ");
        if (sscanf(str_check[0],"you%s",dummy))
        {
            set_alarm(0.0,0.0,"return_attack",who);
            return 1;
        }
        TO->command("emote snarls: Stop this at once!");
        return 1;
    }
}

void
return_attack(string who){
    object obj;
    int ran;
    if(obj = present(who, environment())){
        command("wear all");
        command("lower visor");
        command("say Fools! You will all die.");
        command("whipslash "+lower_case(obj->query_real_name()));
        if (obj->query_guild_member("Solamnian Knights"))
            set_alarm(2.0,0.0,"send_gunthar",obj);
    }
}

/* this function sends a message to Gunthar (in vkeep)
 *  if a knight attacks him.
 */

send_gunthar(object knight)
{
    command("gasp");
    command("emote announces: I will make sure you are punished for "+
        "this treaserous attack, knight! No more will I trust you and "+
        "the rest of the filth from Vingaard. My power can reach far...");
    GUNTHAR->add_bad_guy(capitalize(knight->query_real_name()),"the High Lord of Kabal",
        "started a revolt there","punished");
    command("emote shouts aloud: Scribe! Send word to Lord Gunthar about "+
        "this. And hurry!");
}

/* This function sends a message to Gunthar if a knight
 * resques him.
 */

react_resque(string who,string dummy)
{
    if (who)
    {
        who=lower_case(who);
        command("say You did the right action, Knight of Solamnia.");
        set_alarm(2.0,0.0,"do_reward",who);
        return 1;
    }
    return 1;
}

do_reward(string who)
{
    object knight;
    if (knight = present(who, environment()))
    {
        command("say I will make sure you get a fitting reward for your services, "+
            capitalize(knight->query_real_name())+".");
        GUNTHAR->add_good_guy(capitalize(knight->query_real_name()),"the High Lord of Kabal",
            "helped to prevent a revolt there","rewarded");
    }
}



int
special_attack(object enemy)
{
    object shamein;
    object stun;
    object *ob;
    object *shamein_attackers;
    object *enemies;
    object kill_enemy;
    int i;
    int did_push;
    object me;
    mixed* hitresult;
    string how;
    me = this_object();
   
    /* this part will make the attackers of the npc */
    /* shamein, turn to attack the high lord. */
   
    if(random(2))
    {
        if (shamein=present("shamein",environment(me)))
        {
            shamein_attackers=shamein->query_enemy(-1);
            did_push = 0;
            if (sizeof(shamein_attackers)>0)
            {
                for (i=0;i<sizeof(shamein_attackers);i++)
                {
                    if(shamein_attackers[i]->query_attack()==shamein)
                    {
                        shamein_attackers[i]->catch_msg(QCTNAME(me)+
                            " pushes "+
                            QTNAME(shamein)+
                            " behind him, forcing you to attack himself.\n");
                        shamein_attackers[i]->attack_object(me);
                        did_push = 1;
                    }
                }
                if (did_push)
                {
                    me->catch_msg("You pushed "+QTNAME(shamein)+" behind you, "+
                        "and his enemies turn to attack you.\n");
                    shamein->catch_msg(QCTNAME(me)+" pushed you behind himself, letting "+
                        "your enemies attack himself.\n");
                }
            }
        }
    }
   
    /* This decides if we shall do anything more... */
    if (random(3))
        return 0;
   
   
    /* This part will make the high lord and his councellor */
    /* attack the weakest player of their enemies. */
   
    kill_enemy= me->query_attack();
    enemies = me->query_enemy(-1);
    for (i=0;i<sizeof(enemies);i++)
    {
        if (enemies[i]->query_stat(SS_CON) < kill_enemy->query_stat(SS_CON))
            kill_enemy = enemies[i];
    }
    if(kill_enemy != me->query_attack())
    {
        command("kill "+kill_enemy->query_real_name());
        if (shamein=present("shamein",environment(me)))
            shamein->command("kill "+kill_enemy->query_real_name());
    }
   
    /* a normal special attack - a kick. */
   
    hitresult = enemy->hit_me(400+random(600), W_BLUDGEON, me, -1);
    how  = "without effect";
    if (hitresult[0] > 0)
        how == "";
    if (hitresult[0] > 10)
        how = "softly";
    if (hitresult[0] > 20)
        how = "hard";
    if (hitresult[0] > 30)
        how = "very hard";
    if (hitresult[0] > 40)
        how = "smashingly";
   
    me -> catch_msg("You kick your opponent in the stomach, "+how+"!\n");
    enemy->catch_msg(QCTNAME(me)+" kicks you "+how+" in your stomach!\n");
    tell_watcher(QCTNAME(me)+" kicks "+QTNAME(enemy)+" "+how+
        " in the stomach!\n",enemy);
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(me);
        return 1;
    }

    /* add a stun if damage above 10 */
    if (hitresult[0] < 9) return 1;
    if (random(2) == 0) return 1;
    ob = all_inventory(enemy);
    for(i=0;i<sizeof(ob);i++)
    {
        if(ob[i]->query_name()=="stun")
        {
            return 1;
        }
    }
    seteuid(getuid(TO));
    stun = clone_object("/d/Kalad/common/central/obj/lord_stun");
    stun -> move(enemy, 1);
    enemy->catch_msg("The kick makes you loose your breath!\n");
    return 1;
}
