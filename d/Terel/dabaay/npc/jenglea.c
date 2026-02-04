/*
 *
 * Jenglea the Master Thief of the Hand
 *
 * Goldberry - January, 2000
 *
 *
 * Jan 2021 - Lucius - Commented out set_living_name
 */


#include "/d/Terel/include/Terel.h"
inherit "/lib/unique";
inherit STDMONSTER;

#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

#define KILL_LOG "/d/Terel/dabaay/log/jenglea_kills"

void dress_me();
int react_enter(string who);
int initial_attack(object enemy);
int SATTACK = 6;

public mixed
oke_to_move(string exit)
{
    mixed ret = ::oke_to_move(exit);
    if (stringp(ret))
      ret = "sneak " + ret;
    return ret;
}

public void
create_monster()
{
    set_name("jenglea");
//    set_living_name("jenglea");
    set_adj("sinewy");
    set_adj("black-eyed");
    set_race_name("elf");
    set_height_desc("tall");
    set_width_desc("of normal width");
    set_scar(random(512));
    set_alignment((random(200) + 400) * -1);
//    set_title("the Master Avenger of the Hand");
    set_gender(0);
    set_short("sinewy black-eyed male elf");
    set_stats(({120+random(20), 
                165+random(20), 
                145+random(20), 
                130+random(20), 
                130+random(20), 
                130+random(20)}));
    set_exp_factor(130);

    set_skill(SS_WEP_KNIFE, 95);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 85);
    set_skill(SS_2H_COMBAT, 90);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_SNEAK, 100);
    set_skill(SS_HIDE, 100);
    set_skill(SS_BACKSTAB, 100);
    set_skill(SS_PICK_POCKET, 85);
    set_skill(SS_BLIND_COMBAT, 70);

    add_prop(LIVE_I_QUICKNESS, random(60) + 75);
    add_prop(OBJ_I_HIDE, 105);
    add_prop(OBJ_M_HAS_MONEY, random(400) + 1200);
    set_aggressive("@@attack_big");
    set_act_time(2);
    add_act("hide", 0);
//    trig_new("%w 'arrives' %s", "react_enter");
    set_restrain_path(DABAAY_DIR);
    set_random_move(random(10) + 5);
    set_cchat_time(2);
    add_cchat("You will soon realize the magnitude of your folly.");
    add_cchat("You are more foolish than you appear.");
    add_cchat("Death awaits you fool.");
    add_cchat("There is no escape from the vengeance."); 
    dress_me();
//    enable_intro();
}


void
dress_me()
{
    FIX_EUID;
    clone_object(DABAAY_DIR + "weapon/sdagger")->move(TO);
    clone_unique(DABAAY_DIR + "weapon/ssickle",7,DABAAY_DIR + "weapon/sdagger")->move(TO);
/*
    clone_unique(DABAAY_DIR + "weapon/ssickle",5,DABAAY_DIR + "weapon/sdagger")->move(TO);
    clone_unique(DABAAY_DIR + "weapon/ssickle",5,DABAAY_DIR + "weapon/sdagger")->move(TO);
*/
    clone_object(DABAAY_DIR + "armour/l_boots")->move(TO);
    clone_object(DABAAY_DIR + "armour/jtunic")->move(TO);
    clone_object(DABAAY_DIR + "armour/jcloak")->move(TO);
    command("wield all");
    command("wear all");
}

/* mask the kind of initial attack he makes so he can backstab */
/*
void
aggressive_attack(object ob)
{
    TO->command("backstab "+lower_case(ob->query_name())+
         " with dagger");
    return;
}
*/

void
aggressive_attack(object ob)
{
    if(!(TO->query_enemy()))
    {
       TO->command("emote hisses angrily.");
       if (initial_attack(ob));
          command("kill " + ob->query_real_name());
    }
    return;
}

mixed
attack_big()
{
    if (!TO->can_see_in_room())
     return 0;
    react_enter(TP->query_name());
    if(TP->query_prop(HAND_MARK) == 0)
     return 0;
    return 1;
}
    
int
react_enter(string who)
{
   if(!(TO->query_enemy()))
     add_prop(OBJ_I_HIDE, 105);
   if (random(10) > 8)
   {
       command("steal item from "+ lower_case(who));
   }
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
    clone_object(DABAAY_DIR + "obj/jkey")->move(TO);    
    if (killer->query_prop(HAND_MARK) < 2)
      killer->add_prop(HAND_MARK,2);
    killer->catch_tell(
      TO->query_The_name(killer)+ " gasps to you: Death hunts you!\n");
/*
    TO->command("say to "+killer->query_name()+" Death hunts you!");
*/
    TO->command("emote seems to gag on something as he falls.");
    ::do_die(killer);
}

int 
initial_attack(object enemy)
{
    mixed *hitresult;
    string how;
    object me;
    int intox, hurt, Hand;
    Hand = 0;

    intox = enemy->query_intoxicated();
    if(enemy->query_prop(HAND_MARK))
    {
        Hand = 50 * enemy->query_prop(HAND_MARK);
    }

    me = TO;

    if (present(enemy, ENV(me)))
    {
        hurt = F_PENMOD(35 + Hand + (intox/3), 35 + Hand + (intox/3));
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

        tell_watcher(QCTNAME(me)+ " slashes at " +QCTNAME(enemy)+ 
            " from behind!\n",
                             enemy);
        enemy->catch_tell(query_The_name(enemy) + " slashes at you "+
            "from behind!\n" +
            "You feel " + how + ".\n");
        return 1;
    }
    return 0;
}
 

int
special_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object me, wuss;
    int intox,hurt, i, Hand, blind, fnum;
    Hand = 70;

    intox = enemy->query_intoxicated();
    if(enemy->query_prop(HAND_MARK))
    {
        Hand = 35 * enemy->query_prop(HAND_MARK);
    }
    me = TO;
    blind = TO->query_skill(SS_BLIND_COMBAT);

    if(random(SATTACK) > 8) 
    {
        SATTACK = 6;
        fnum = 35 + Hand + (intox/3);

        if (!TO->can_see_in_room() || enemy->query_invis())
          fnum = fnum * blind / 100;
 
        hurt = F_PENMOD(fnum, fnum);

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

    SATTACK++;
    return 0;
}

