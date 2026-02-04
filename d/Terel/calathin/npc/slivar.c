/*
 *  Slivar the Bad, /d/Terel/calathin/npc/slivar.c 
 *
 *  Goldberry, May 2002.
 *  Based on Sliver by Shinto
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/lib/unique";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>

#define TOX_BONUS 80
#define KILL_LOG "/d/Terel/log/slivar_kills"
#define GEM_DIR "/d/Genesis/gems/obj/"

void dress_me();

public void
create_monster()
{
    set_name("slivar");
    set_living_name("slivar");
    set_adj("thin");
    set_adj("brown-eyed");
    set_race_name("halfling");
    set_title("the Bad");
    set_gender(0);
    set_long("A thin almost frail looking halfing. He has "+
             "dark brown eyes, and short brown hair. His face "+
             "is sunken and pale. He stares at you intently "+
             "through those malevolent eyes.\n");
    set_stats(({130, 190, 156, 130, 130, 130}));
    set_exp_factor(120);

    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 90);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_2H_COMBAT, 90);
    set_skill(SS_SNEAK, 100);
    set_skill(SS_HIDE, 100);
    set_skill(SS_BACKSTAB, 100);
    set_cchat_time(3);
    add_cchat("You'll not live to see the glory of Maskyr Keep's victory.");
    add_cchat("I bet that blade in your back hurt!");
    add_cchat("The Hand will find you.");

    set_act_time(3);
    add_act("hide");

    add_prop(OBJ_I_HIDE, 100);
    add_prop(LIVE_I_QUICKNESS,100);
    add_prop(OBJ_M_HAS_MONEY, random(500) + 900);

    set_aggressive(1);
    dress_me();

}


/* mask the kind of initial attack he makes so he can backstab */
void
aggressive_attack(object ob)
{
    TO->command("backstab "+ob->query_race_name()+" with dagger");
    return;
}


/* Get some equipment */
void
dress_me()
{
    FIX_EUID;
    clone_object(CALATHIN_DIR + "armour/sm_bracers")->move(TO);
    clone_object(CALATHIN_DIR + "armour/stud_armourh")->move(TO);
    clone_object(CALATHIN_DIR + "armour/sm_boots")->move(TO);
    clone_object(CALATHIN_DIR + "weapon/dagger")->move(TO);
    clone_object(CALATHIN_DIR + "weapon/dagger")->move(TO);

    clone_object(GEM_DIR + "ruby")->move(TO);
    clone_object(GEM_DIR + "jade")->move(TO);
    clone_object(GEM_DIR + "agate")->move(TO);

    command("wield all");
    command("wear all");
}

/* perform a special attack */
int
special_attack(object enemy)
{
    mixed* hitresult;
    string how, spattack, hdesc;
    object me, *enemies;
    int intox, hurt, hitloc, gobmod, ranseed;

    me = TO;
    gobmod = 1;
    ranseed = 8;
    if (enemy->query_race_name() == "goblin")
    {
      gobmod = 2;
      ranseed = 5;
    }
    /* Choose a hit location */
    if(random(ranseed) < 1)
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
        intox = enemy->query_intoxicated() / enemy->intoxicated_max() * 100;

        hurt = F_PENMOD((45+(TOX_BONUS * intox / 100)) * gobmod, 60);

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

        if (hitresult[0] > 20)
           enemy->add_attack_delay((hitresult[0] / 2), 1);

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

void
do_die(object killer)
{
    int i;
    string str;
    object *enemies;
    
    if (query_hp() > 0) return;
    enemies = query_my_enemies();
    str = killer->query_name() + "[" + killer->query_average_stat() + "]";
    for (i=0; i<sizeof(enemies); i++) {
       if (enemies[i] != killer)
           str += ", " + enemies[i]->query_name() +
           "[" + enemies[i]->query_average_stat() + "]";
      }
    write_file(KILL_LOG, str + " (" + ctime(time()) + ")\n");
    
    ::do_die(killer);
}


