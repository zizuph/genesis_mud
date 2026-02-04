/*
 *
 * Dunker, ogre
 *
 * Goldberry - April, 2000
 *
 * Modifications
 *  - Converted to use Genesis Stat-based special, Petros, March 2010
 *
 * Jan 2021 - Lucius - Commented out set_living_name
 */


#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
inherit "/lib/unique";
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/d/Genesis/specials/npc/stat_based_specials";

#define KILL_LOG "/d/Terel/dabaay/log/dunker_kills"
#define STUN_OBJ "/d/Terel/dabaay/obj/stun_obj"
#define DUR_SEED 20;

void dress_me();
int react_enter(object who);
int initial_attack(object enemy);

int SATTACK = 6;

public void
create_monster()
{
    set_name("dunker");
//    set_living_name("dunker");
    set_adj("massive");
    set_adj("rat-faced");
    set_race_name("ogre");
    set_alignment((random(300) + 600) * -1);
    set_gender(0);
    set_short("massive rat-faced male ogre");

    set_long(
        "A huge ogre with impressive muscles and sharp teeth.\n");
    set_stats(({185+random(25), 
                165+random(20), 
                185+random(25), 
                150+random(20), 
                150+random(20), 
                170+random(20)}));

    set_skill(SS_WEP_CLUB, 95);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 80);
    set_skill(SS_2H_COMBAT, 80);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_BLIND_COMBAT, 90);
    set_exp_factor(140);

    set_all_hitloc_unarmed( ({ 30, 30, 30 }) );

    add_prop(OBJ_I_INVIS, 1);
    add_prop(OBJ_M_HAS_MONEY, random(700) + 1800);
    set_aggressive("@@attack_big");
    dress_me();
}


void
dress_me()
{
    FIX_EUID;
    clone_unique(DABAAY_DIR + "weapon/dmace", 7, DABAAY_DIR + "weapon/short")->move(TO);
    clone_object(DABAAY_DIR + "weapon/short")->move(TO);
    clone_object(DABAAY_DIR + "armour/ogre_boots")->move(TO);
    clone_object(DABAAY_DIR + "armour/ogre_chain")->move(TO);
    clone_object(DABAAY_DIR + "armour/ogre_helm")->move(TO);
    command("wield all");
    command("wear all");
}

/* mask the kind of initial attack he makes */
void
aggressive_attack(object ob)
{
    if(!(TO->query_enemy()))
    {
    if (initial_attack(ob));
        command("kill " + ob->query_real_name());
    }
    return;
}

mixed
attack_big()
{
    if(!TO->can_see_in_room())
     return 0;
    react_enter(TP);
    if((TP->query_prop(HAND_MARK) < 3) || (TP->query_prop(HAND_PATCH))) 
     return 0;
    return 1;
}
    
int
react_enter(object who)
{
   if(!(TO->query_enemy()))
     add_prop(OBJ_I_INVIS, 1);
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
    if (killer->query_prop(HAND_MARK) < 3)
      killer->add_prop(HAND_MARK,3);
    TO->command("say They will bring me back to finish you!");
    TO->command("emote grunts out a last breath.");
    ::do_die(killer);
}

int
initial_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object me, stunner; 
    int intox,hurt, i, Hand;
    Hand = 80;

    intox = enemy->query_intoxicated();
    if(enemy->query_prop(HAND_MARK))
    {
        Hand = 35 * enemy->query_prop(HAND_MARK);
    }

    me = TO;
    command("shout Gonna bash you one good!");
    if (present(enemy, ENV(TO)))
    {
        me->remove_prop(OBJ_I_INVIS);
    
        hurt = F_PENMOD(45  + Hand + (intox / 3), 45 + Hand + (intox /
3));

        hitresult = enemy->hit_me(hurt, W_BLUDGEON, me, -1);

        how = "unharmed";
        if (hitresult[0] > 0)
            how = "slightly hurt";
        if (hitresult[0] > 20)
            how = "rather hurt";
        if (hitresult[0] > 50)
            how = "crushed";
        if (hitresult[0] > 100)
            how = "devastated";
            
        tell_watcher(QCTNAME(me) + " strikes at " + QCTNAME(enemy) + ".\n",
                             enemy);
        enemy->catch_tell(query_The_name(enemy) + " strikes at you!\n" +
            "You feel " + how + ".\n");
        
        if (hitresult[0] > 5)
        {
           stunner = clone_object(STUN_OBJ);
           stunner->move(enemy);
           stunner->set_from("ogre's strike");
           stunner->set_duration(random(20) + 20);
           command("shout Haw! Knockered ya stupid!");
        }


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
    Hand = 80;

    intox = enemy->query_intoxicated();
    if(enemy->query_prop(HAND_MARK))
    {
        Hand = 35 * enemy->query_prop(HAND_MARK);
    }

    me = TO;
    blind = TO->query_skill(SS_BLIND_COMBAT);
    if (me->query_prop(OBJ_I_INVIS))
      remove_prop(OBJ_I_INVIS);

    if(random(SATTACK) > 8) 
    {
        // We use the Genesis NPC stat-based special
        SATTACK = 6;
        fnum = query_pen_by_stat(query_average_stat()) + Hand + (intox / 3);

        if (!TO->can_see_in_room() || enemy->query_invis())
          fnum = fnum * blind / 100;

        if (!(hitresult = do_stat_based_attack(this_object(), enemy, W_BLUDGEON)))
        {
            // Could not attack the target, or they evaded.
            return 1;
        }

        if (!strlen(hitresult[1]))
        {
            // Handle misses.
            tell_watcher(QCTNAME(me) + " tries to swing at " + QTNAME(enemy) 
                + " but misses completely.\n", enemy);
            enemy->catch_msg(QCTNAME(me) + " tries to swing at you but misses "
                + "completely!\n");
            return 1;
        }

        how = "unharmed";
        if (hitresult[0] > 0)
            how = "slightly hurt";
        if (hitresult[0] > 20)
            how = "rather hurt";
        if (hitresult[0] > 50)
            how = "crushed";
        if (hitresult[0] > 100)
            how = "devastated";

        tell_watcher(QCTNAME(me) + " swings at " + QCTNAME(enemy) + ".\n",
                             enemy);
        enemy->catch_tell(query_The_name(enemy) + " swings at you!\n" +
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


