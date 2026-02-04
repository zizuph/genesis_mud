// Maivia, dark elf warrior
// Shinto 3-10-01
//
#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/lib/unique";
inherit DARK_DIR + "mon/team";
#include "/sys/ss_types.h"
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

#define KILL_LOG "/d/Terel/log/maivia_kills"

void dress_me();

public void
create_monster()
{
    set_race_name("dark elf");
    set_name("maivia");
    set_living_name("maivia");
    add_name(({"warrior", "master","elf"}));
    set_adj("dark");
    set_short("dark elf warrior");
    set_pshort("dark elf warriors");
    set_long("These evil creatures are the opposers of all light " +
      "and truth. They seek utter darkness for the world. They are pale "+
      "beings with dark hair, their beauty being that of the "+
      "shadows. They are wicked things.\n");


    set_stats(({ 160, 200, 200, 160, 160, 160}));
    set_alignment(-1000);

    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_SPELLCRAFT, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_SNEAK, 100);
    set_skill(SS_HIDE, 100);
    set_skill(SS_BACKSTAB, 100);
    set_skill(SS_PICK_POCKET, 85);
    set_skill(SS_BLIND_COMBAT, 85);
    set_hp(9000);
    set_mana(9000);
    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(LIVE_I_QUICKNESS, 200);
    add_prop(OBJ_M_HAS_MONEY, ({ 0, 25, 10 }) );

    set_chat_time(5);
    dress_me();


}


void
dress_me()
{
    FIX_EUID;
    clone_object(DARK_DIR + "obj/chainmail")->move(TO);
    clone_object(DARK_DIR + "obj/war_helm")->move(TO);

    switch(random(2))
    {
        case 0: clone_unique(DARK_DIR + "obj/evil_spear",7,DARK_DIR + "obj/halberd")->move(TO);
            command("wield all");
            break;

        case 1: clone_unique(DARK_DIR + "obj/silver_spear",7,DARK_DIR + "obj/halberd")->move(TO);
            command("wield all");
            break;
    }
    clone_object(DARK_DIR + "obj/boots")->move(TO);
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
    int intox, hurt, hitloc, ranseed;

    me = TO;
    ranseed = 8;

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

        hurt = F_PENMOD((45 + (intox/2)), (45 + (intox/2)));

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
                        hitresult = enemy->hit_me(hurt, W_IMPALE, me, hitloc);
                        spattack = "stabs";
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
