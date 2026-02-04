/*
 *
 *
 */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/seqaction";

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#define ARM_DIR  CALATHIN_DIR + "armour/"
#define WEP_DIR  CALATHIN_DIR + "weapon/"
#define KILL_LOG CALATHIN_DIR + "log/joe_hand"

string adj();
string adj2();
string races();
string breeches();
void dress_me();
int weps;

public void
create_monster()
{

    set_name("joe_hand");
    set_gender(0);
    set_race_name(races());
    set_adj(adj());
    set_adj(adj2());
    set_stats(({ 120 + random(10),
                 140 + random(10),
                 130 + random(10),
                 120 + random(10),
                 120 + random(10),
                 130 + random(10)}));

    set_alignment((random(300) + 200) * -1);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_WEP_KNIFE, 90);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 80);
    set_skill(SS_UNARM_COMBAT, 0);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_2H_COMBAT, 80);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(OBJ_M_HAS_MONEY, random(3100));
    set_restrain_path(CALATHIN_DIR);
    set_random_move(10);
    set_aggressive("@@attack_big");
    weps = 0;
    dress_me();

}

void
dress_me()
{
    FIX_EUID;
    clone_object(ARM_DIR + "jh_boots")->move(TO);
    clone_object(ARM_DIR + "jh_shirt")->move(TO);
    clone_object(ARM_DIR + "hat")->move(TO);
    clone_object(ARM_DIR + breeches())->move(TO);
    command("wear all");

}

string breeches()
{
    string *breeches_list;
    breeches_list = ({"bl_breeches","g_breeches","gr_breeches","t_breeches"});
    return breeches_list[random(sizeof(breeches_list))];
}

string races()
{
    string *races;
    races = ({"elf","half-elf","human"});
    return races[random(sizeof(races))];
}

string adj()
{
    string *adj;
    adj = ({"black-haired","blond-haired","muscular", "swarthy",
               "thick-armed","long-haired","short-haired", "silver-haired",
               "red-haired", "brown-haired", "grey-haired"});
    return adj[random(sizeof(adj))];
}

string adj2()
{
    string *adj2;
    adj2 = ({"blue-eyed", "hazel-eyed", "black-eyed", "brown-eyed",
            "green-eyed","olive-skinned","brown-skinned",
            "tanned","dark-skinned","light-skinned","grey-eyed"});
    return adj2[random(sizeof(adj2))];
}


mixed
attack_big()
{
    if(TP->query_prop(HAND_MARK) == 0)
     return 0;
    return 1;
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
    if (!(killer->query_prop(HAND_MARK)))
      killer->add_prop(HAND_MARK,1);
    ::do_die(killer);
}

int
special_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object me, wuss;
    int intox,hurt, i, Hand;
    Hand = 0;

    intox = enemy->query_intoxicated();
    if(enemy->query_prop(HAND_MARK))
    {
        Hand = 25 * enemy->query_prop(HAND_MARK);
    }

    me = TO;

    if(!(weps))
    {
       clone_object(WEP_DIR + "jh_sword")->move(TO);
       clone_object(WEP_DIR + "dagger")->move(TO);
       command("wield all");
       weps = 1;
    }
       
    if(random(11) > 8)
    {
        hurt = F_PENMOD(35  + Hand + (intox / 3), 35 + Hand + (intox / 3));

        hitresult = enemy->hit_me(hurt, W_SLASH, me, -1);

        how = "unharmed";
        if (hitresult[0] > 0)
            how = "slightly hurt";
        if (hitresult[0] > 20)
            how = "rather hurt";
        if (hitresult[0] > 50)
            how = "crushed";
        if (hitresult[0] > 100)
            how = "devastated";

        tell_watcher(QCTNAME(me) + " slashes at " + QCTNAME(enemy) + ".\n",
                             enemy);
        enemy->catch_tell(query_The_name(enemy) + " slashes at you!\n" +
            "You feel " + how + ".\n");

        if (enemy->query_hp() <= 0)
        {
            if (enemy->query_prop(HAND_MARK))
            {
                command("say to " +enemy->query_real_name() +
                    "Thus is the vengeance of the Hand!");
                command("say Which of you other fools is next?");
            }
            command("cackle maniacally");
            enemy->do_die(me);

        }

        wuss = query_smallest_enemy();
        if (wuss != query_attack())
          command("kill " + wuss->query_real_name());
        return 1;
    }


    return 0;
}


