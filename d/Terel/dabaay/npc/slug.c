/*
 *
 * Slug the Master Mugger of the Hand
 *
 * Goldberry - May, 2002
 *
 *
 * Jan 2021 - Lucius - Commented out set_living_name
 */


#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/lib/unique";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

#define KILL_LOG "/d/Terel/dabaay/log/slug_kills"

void dress_me();

public void
create_monster()
{
    set_name("slug");
//    set_living_name("slug");
    set_adj("thin");
    set_adj("olive-skinned");
    set_race_name("human");
    set_alignment((random(200) + 200) * -1);
    set_gender(0);
    set_short("thin olive-skinned male human");
    set_scar(random(512));
    set_height_desc("tall");
    set_width_desc("lean");
    set_stats(({120 + random(30), 
                165 + random(30), 
                155 + random(30), 
                130 + random(30), 
                100 + random(30), 
                130 + random(30)}));
    set_exp_factor(130);

    set_skill(SS_WEP_KNIFE, 85);
    set_skill(SS_WEP_SWORD, 95);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 80);
    set_skill(SS_2H_COMBAT, 90);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_SNEAK, 90);
    set_skill(SS_HIDE, 90);
    set_skill(SS_BACKSTAB, 95);
    set_skill(SS_BLIND_COMBAT, 50);
    add_prop(OBJ_M_HAS_MONEY, random(800) + 1700);

    add_prop(LIVE_I_QUICKNESS, random(30) + 75);
    add_prop(OBJ_I_HIDE, 90);
    set_aggressive("@@attack_big");
    dress_me();
    set_act_time(2);
    add_act("hide", 0);

}


void
dress_me()
{
    FIX_EUID;
    clone_object(DABAAY_DIR + "weapon/short")->move(TO);
    clone_object(DABAAY_DIR + "weapon/sdagger")->move(TO);
    clone_object(DABAAY_DIR + "armour/l_boots")->move(TO);
    clone_object(DABAAY_DIR + "armour/tunic")->move(TO);
    clone_object(DABAAY_DIR + "armour/tcloak")->move(TO);
    command("wield all");
    command("wear all");
}

/* mask the kind of initial attack he makes so he can backstab */
void
aggressive_attack(object ob)
{
    TO->command("backstab "+ob->query_race_name()+" with dagger");
    return;
}


mixed
attack_big()
{
    if(TP->query_average_stat() < 75)
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
    killer->catch_tell(
      TO->query_The_name(killer)+ " gasps to you: You are marked to die.\n");
    TO->command("emote chokes and gasps out his last breath.");
    ::do_die(killer);
}
