/* -*- C -*- */

#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;
inherit "/lib/unique";

#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <formulas.h>
#define KILLED_TREVIN "_i_killed_trevin"

void dress_me();

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */

public void
create_terel_monster()
{
    set_name ("trevin");
    set_living_name("trevin");
    add_name ("assassin");
    set_title("Blackheart, Master Assassin of the Hand");
    set_living_name ("trevin");
    set_long ("A sinister look crosses his face as you both exchange " +
					      "glances at each other. He moves gracefully around the " +
					      "room, taking your measure.\n");
    set_adj (({"tall","wiry"}));
    set_race_name ("human");
    set_gender (0);

    set_stats (({130, 170, 130, 100, 100, 150}));
    SET_MAX_HP;
    SET_MAX_MANA;
    set_alignment (-800);
    set_skill (SS_DEFENCE, 100);
    set_skill (SS_AWARENESS,    100);
    set_skill(SS_HIDE, 100);
    set_skill(SS_SNEAK, 100);
    set_skill (SS_WEP_KNIFE, 100);
    set_skill (SS_WEP_SWORD,100);
    set_skill (SS_2H_COMBAT,100);
    set_skill (SS_UNARM_COMBAT,0);
    set_skill (SS_PARRY, 100);
    set_skill (SS_BACKSTAB, 100);
    add_prop(LIVE_I_QUICKNESS,30);
    add_prop(OBJ_I_HIDE, 90);
    AGGRESSIVE;
    set_act_time (10);
    add_act (({"hide", "grin", "snicker"}));

    
    set_chat_time (10);
    add_cchat ("You should not have come here, fool.");    
    add_cchat ("Another kill to improve my reputation.");
    add_cchat ("I've met filthy Angmarians who fight better then you do.");

    enable_intro();
    dress_me();
}

/* Get some equipment */
void
dress_me()
{
    FIX_EUID;
    switch(random(2)) 
   {
        case 0 :  clone_unique(LAST_DIR+"armour/trev_boots",7,
                     LAST_DIR+"armour/boots",1,60)->move(TO);
                     command("wear boots");  
                  break;
        case 1 :  clone_unique(LAST_DIR+"armour/trev_bracers",7,
                     LAST_DIR+"armour/boots",1,60)->move(TO);
                     command("wear bracers"); 
                  break;
    }
    clone_object(LAST_DIR + "armour/tunic")->move(TO);
    clone_object(LAST_DIR + "armour/tcloak")->move(TO);
    clone_object(LAST_DIR + "weapon/dagger")->move(TO);
    clone_object(LAST_DIR + "weapon/black_sword")->move(TO);
    command("wield all");
    command("wear all");
}

public void add_introduced(string s_who)
{
    object o_who = find_player(s_who);


    if(o_who &&
       !o_who->query_met(this_object()))
        set_alarm(itof(random(5) + 1), 0.0, "command",
                  "introduce myself to "+ s_who);

}

void
do_die(object killer)
{
    killer->add_prop(KILLED_TREVIN, 1);
    if (interactive(killer)) {
	  write_file("/d/Terel/last/log/trevin_kills",
		     killer->query_name()+ " " + ctime(time()) + "\n");
       }

    ::do_die(killer);
}

/* mask the kind of initial attack he makes so he can backstab */
void
aggressive_attack(object ob)
{
    TO->command("backstab "+ob->query_race_name()+" with dagger");
    return;
}


/* perform a special attack */
int
special_attack(object enemy)
{
    mixed* hitresult;
    string how, spattack, hdesc;
    object me, *enemies;
    int intox, hurt, hitloc;

    me = TO;
    /* Choose a hit location */
    if(random(8) < 1)
    {
        switch(random(4))
        {
            case 0:    hitloc = A_BODY;
                       hdesc = "body";
                       break;

            case 1:    hitloc = A_HEAD;
                       hdesc = "head";
                       break;

            case 2:    hitloc = A_LEGS;
                       hdesc = "legs";
                       break;

            case 3:    hitloc = A_R_ARM;
                       hdesc = "right arm";
                       break;

            case 1:    hitloc = A_L_ARM;
                       hdesc = "left arm";
                       break;
        }




        /* Figure a pen value, take drunken bastards into account */

        hurt = F_PENMOD(45 + (intox/3), 45 + (intox/3));

        /* Switch between three types of attack, stab, slash, and punch. */

        switch(random(2)) 
        {
            case 0:  
                    if(sizeof(me->query_weapon(-1)))
                    {
                        hitresult = enemy->hit_me(hurt, W_IMPALE, me, hitloc);
                        spattack = "stabs";
                    }
                    else
                    {
                        hitresult = enemy->hit_me(hurt, W_BLUDGEON, me, hitloc);
                        spattack = "punches";
                    }
                    break;

            case 1:  
                    if(sizeof(me->query_weapon(-1)))
                    {
                        hitresult = enemy->hit_me(hurt, W_SLASH, me, hitloc);
                        spattack = "slashes";
                    }
                    else
                    {
                        hitresult = enemy->hit_me(hurt, W_BLUDGEON, me, hitloc);
                        spattack = "punches";
                    }
                    break;

        }

        /* Determine how good a hit and describe it. */
        if (hitresult[0] >= 0)
            how = "slightly hurt";
        if (hitresult[0] > 20)
            how = "rather hurt";
        if (hitresult[0] > 50)
            how = "crushed";
        if (hitresult[0] > 100)
            how = "devastated";

        /* Describe the attack. */
        tell_watcher(QCTNAME(me)+ " " +spattack+ " " +QCTNAME(enemy)+
                     " in "+POSSESSIVE(enemy)+" "+hdesc+"!\n",enemy);
        enemy->catch_tell(query_The_name(enemy) + " " + spattack + " you "+
            "in the "+hdesc+"!\n" +
            "You feel " + how + ".\n");

        /* Kill the bastard if he's got no hit points. */
        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(me);
        }
        return 1;
    }
    return 0;
}
