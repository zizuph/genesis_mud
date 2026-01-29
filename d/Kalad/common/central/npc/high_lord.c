/*
 * High Lord of Kabal.
 * MADE BY: Korat
 * DATE: Feb 14 1995
 *
 * 2005-08-29 - Cotillion
 * - Stuns were cloned into the void, fixed
 *
 * 2011/08/04 Lavellan - Fixed Gunthar location.
 * Reworked by Zignur 2017-11-09
 * Added some tells regarding return of Thanar - Mirandus 2018-01-19
 * 
 * 2020/06/15 Cotillion - Added skill for backup weapon
 * 2021/05/03 Cotillion - Nerfed coins a bit
 */

inherit "/d/Kalad/std/monster";
/* Zignur: We use this to make him team properly */
inherit "/d/Kalad/std/group_cluster";
/* Zignur: Use clone unique for his whip and breastplate */
inherit "/lib/unique";
/* Zignur: Add a kill logger */
inherit "/d/Kalad/common/kill_logger";

#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"
#include <stdproperties.h>


/* Prototypes */
public void         create_monster();
public void         arm_me();
public void         help_friend(object ob);
public int          react_attack(string who, string dummy);
public void         return_attack(string who);
public int          special_attack(object enemy);
public int          attack_object(object ob);

/*
 * Function name:        create_monster
 * Description  :        Creates the npc
 */
public void
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
   
    set_stats(({250,250,250,250,250,250}));
    refresh_living();
    set_alignment(0);
    set_skill(SS_WEP_SWORD, 100);
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
    add_act("say Damn those Thanarians. Forcing my hand. I had no choice "
    +"but to allow their return. We must watch them and ensure they do not "
    +"grow too powerful\n");
    add_act("say With the return of their Avatar, the Thanarians have "
    +"grown powerful enough that they have bought favour with the "
    +"council. I have been forced to allow them to reopen their "
    +"church.\n");
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
    add_prop(NPC_M_NO_ACCEPT_GIVE,1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_SEE_DARK,20);
    add_prop(LIVE_I_ATTACK_THIEF, 1);
    trig_new("%w 'attacks' %s","react_attack");
    
    /* Zignur Add him to the team */
    set_prospective_cluster(({"_urian_npc"}));
    
    /* Zignur XP Adjustment */
    set_exp_factor(150);  
}

/*
 * Function name:        arm_me
 * Description  :        Handles all the items on the npc
 */
public void
arm_me()
{
    object weapon, armour;
    seteuid(getuid(TO));
    
    /* Zignur use equip and clone_unique */
    weapon = clone_unique("/d/Kalad/common/central/wep/lord_whip", 10,
                          "/d/Kalad/common/central/wep/lord_sword");
    weapon -> move(TO);

    armour = clone_unique("/d/Kalad/common/central/arm/lord_breastplate", 10,
                          "/d/Kalad/common/central/arm/lord_breastplate_poor");
    armour -> move(TO);   
    
    equip(({
        weapon,
        armour,
        "/d/Kalad/common/central/arm/lord_ring",
        "/d/Kalad/common/central/arm/lord_boots",
        "/d/Kalad/common/central/arm/lord_gauntlets",
        "/d/Kalad/common/central/arm/lord_greaves",
        "/d/Kalad/common/central/arm/lord_helm",
        }));
   
    command("remove helm");
    MONEY_MAKE_GC(random(300)+100)->move(TO,1);
    MONEY_MAKE_PC(random(30)+10)->move(TO,1);
}

/*
 * Function name:        help_friend
 * Description  :        This is the assist routine for the npc
 * Arguments    :        object ob - the attacker
 */
public void
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

/*
 * Function name:        react_attack
 * Description  :        This function will be called if someone
 *                       is attacked.
 * Arguments    :        string who, string dummy
 * Returns      :        1
 */
public int
react_attack(string who, string dummy)
{
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

/*
 * Function name:        return_attack
 * Description  :        This function is called from the 
 *                       react_attack function.
 * Arguments    :        string who
 */
public void
return_attack(string who)
{
    object obj;
    int ran;
    if(obj = present(who, environment())){
        command("wear all");
        command("lower visor");
        command("say Fools! You will all die.");
        command("whipslash "+lower_case(obj->query_real_name()));
    }
}

/*
 * Function name:        special_attack
 * Description  :        Handles the special attack for the npc
 * Arguments    :        object enemy
 * Returns      :        1 - success, 0 - failure
 */
public int 
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
   
    /* This decides if we shall do anything more... */
    if (random(2))
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

/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 * Arguments:       The object to attack
 */
public int
attack_object(object ob)
{
    ::attack_object(ob);
    map(query_team_others(), &->notify_attack_on_team(this_object(), ob));
} /* attack_object */

