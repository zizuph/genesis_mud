inherit "/std/monster";

#include "/sys/stdproperties.h"
#include "default.h"
#include <poison_types.h>

void damage_armour(object enemy);
void do_die(object enemy);

void
create_monster()
{
        set_name( ({ "daemonlord", "daemon" }) );
        set_living_name("_mylos_daemonlord_");
        set_race_name("daemon");
        set_short("daemonlord");
        set_long(break_string("This human-appearing creature is massive! "+
           "It is armoured to the teeth and you think twice about hitting "+
           "him.\n", 76));

    set_base_stat(SS_STR, 210);      /* Mortals were complaining that */
    set_base_stat(SS_DEX, 192);      /* he was too easy to kill for them */
    set_base_stat(SS_CON, 191);      /* so i've updated it slightly. */
    set_base_stat(SS_INT, 100);
    set_base_stat(SS_WIS, 100);
    set_base_stat(SS_DIS, 100);

    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);

    set_hp(TO->query_max_hp());

    set_all_hitloc_unarmed(80); /* Inherent AC of 80 */

    add_prop(OBJ_I_WEIGHT, 19000);

    add_prop(CONT_I_MAX_WEIGHT, 180000);
    add_prop(OBJ_I_VOLUME, 89000);
    add_prop(LIVE_O_ENEMY_CLING, 1);
    add_prop(CONT_I_MAX_VOLUME, 100000);


    set_chat_time(20);                       /* Set speaking interval */
    add_chat("Do not mess with me mortal!");

    
    set_cchat_time(4);                      /* Set combat speaking interval */
    add_cchat("I am invincible, mortal!");
    add_cchat("This is not a game now, you have pushed me too far.");


    set_act_time(10);                    /* Set action interval           */
    add_act("grin");
    add_act("growl");

    trig_new("%w 'smiles' %s", "react_smile");
    trig_new("%w 'introduces' %s", "react_introduce");
    trig_new("%w 'shakes' %w 'head' %s", "react_shake");
    trig_new("%w 'bows' %s", "react_bow");

    call_out("arm_me", 1);
}

int
react_bow(string who, string dummy) {
    if(who) {
        who = lower_case(who);
        call_out("return_bow", 3, who);
        return 1;
    }
}

void
return_bow(string who) {
   object obj;
   int ran;

   if(obj = present(who, environment())) {
        ran = random(3);
        if(ran == 0)
           command("say Who the hell do you think you are?");
        if(ran == 1)
           command("snarl at " + who);
        if(ran == 2)
           command("say Bow down again and I'll chop your head off, "+
                obj->query_nonmet_name() +".");
   }
}

int
react_smile(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      call_out("return_smile", 3, who);
      return 1;
   }
}

void
return_smile(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Who are you smiling at, " + obj->query_nonmet_name()
               + "?");
      if (ran == 1)
         command("sneer at " + who);
      if (ran == 2)
         command("say A smile like that deserves a good kicking, " +
         obj->query_nonmet_name() + ".");
   }
}

int
react_introduce(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      return 1;
   }
}

void
return_introduce(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
      {
         command("say I'll rip your head off, " + obj->query_name() + ".");
         command("bow to " + who);
      }
      if (ran == 1)
      {
         command("snarl " + who);
      }
      if (ran == 2)
      {
         command("say What is this? A picnic, " + obj->query_race() + "?");
         command("kick " + who);
      }
   }
}

int
react_shake(string who, string dummy1, string dummy2) {
   if (who) {
      who = lower_case(who);
      call_out("return_shake", 3, who);
      return 1;
   }
}

void
return_shake(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say I've seen better dishcloths than you, " + 
	   obj->query_race() + "?");
      if (ran == 1)
         command("say What a pathetic creature you are, "
               + ((obj->query_gender() == G_MALE) ? "master" : "lady") + ".");
      if (ran == 2)
         command("say Why do " + LANG_PWORD(obj->query_race())
               + " always disagree?");
   }
}

void
arm_me()
{
    object eq;

    if(random(10) == 1)
      eq = clone_object("/d/Emerald/mylos/obj/damn_d_sword");
    else
    eq = clone_object("/d/Emerald/mylos/obj/d_sword");
    if (eq)
        eq->move(this_object());

    eq = clone_object("/d/Emerald/mylos/obj/d_dag");
    if(eq)
        eq->move(this_object());
    eq = clone_object("/d/Emerald/mylos/obj/emerald2");
    if(eq)
        eq->move(this_object());
    eq = clone_object("/d/Emerald/mylos/obj/emerald");
    if(eq)
        eq->move(this_object());
    eq = clone_object("/d/Emerald/mylos/obj/d_gre");
    if (eq)
        eq->move(this_object());
    eq = clone_object("/d/Emerald/mylos/obj/d_pl");
    if (eq)
        eq->move(this_object());
    eq = clone_object("/d/Emerald/mylos/obj/d_hel");
    if (eq)
        eq->move(this_object());
    eq = clone_object("/d/Emerald/mylos/obj/d_bra");
    if(eq)
        eq->move(this_object());
    command("wield all");

    command("wear all");

}

/* Filter the people without see_blood , so they dont see the special hits 
*/
static void
tell_watcher(string str, object enemy)
{
    object me, *ob;
    int i;

    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}

int
filter_worn_armours(object obj)
{
    if ((function_exists("create_object",obj) == "/std/armour")
            && obj->query_worn())
        return 1;
    return 0;
}

/* select random armour for damage */
object
select_armour(object enemy)
{
    object *arm_arr;

    arm_arr = filter(all_inventory(enemy),"filter_worn_armours",this_object());

    if (!sizeof(arm_arr))
        return 0;    /* if no armour worn */

    return arm_arr[random(sizeof(arm_arr))];
}

void
damage_armour(object enemy)
{
   int power, old_ac, new_ac;
    string tmp;
    object arm_affected;

    arm_affected = select_armour(enemy);
    if (arm_affected == 0)
        return;

        /* check for resistance */
    if (arm_affected->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
        return;

    enemy->catch_msg(break_string("The daemonlord bashes your " +
                     arm_affected->short() + " and cracks it.\n", 75));

    tell_watcher(QTNAME(enemy)+"'s " + arm_affected->short() + " is "+
        "smashed by the daemonlord.\n",enemy);


    power = random(15) + 3; /* ac lost due to daemonlord */
    old_ac = arm_affected->query_ac();
    new_ac = old_ac - power;
    if (new_ac < 0)
        new_ac = 0;
    arm_affected->set_ac(new_ac);
    arm_affected->add_prop(OBJ_I_BROKEN);
    arm_affected->add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(new_ac));

    if (sscanf(arm_affected->short(), "%s (cracked)",tmp) == 0)
        arm_affected->set_short(arm_affected->short() + " (cracked)");
}

/* display the special attack results */
void
disp_att_results(string how, object me, object enemy)
{
    me->catch_msg("You bash the enemy with your arm" + how + ".\n");
    enemy->catch_msg(QCTNAME(me)+" bashes you with his arm"+how+".\n");
    tell_watcher(QCTNAME(me)+" bashes "+QTNAME(enemy)+"'s armour"+how+".\n",enemy);
}



/* Define the special attack here */
int
special_attack(object enemy)
{
    object me, poison;
    mixed* hitresult;
    string how;
    int old_prop, new_prop, ran;

    ran = random(10);

    me = this_object();

    if(ran == 1)
    {
        hitresult = enemy->hit_me(100, W_NO_DT, me, -1);

        if (hitresult[0] <= 0)
        {
           how = " without effect";
           disp_att_results(how, me, enemy);
           return 1;
        }

        how = "";
           disp_att_results(how, me, enemy);
        if (random(50) >= 25);
           damage_armour(enemy);

        if (enemy->query_hp() <= 0)
           enemy->do_die(me);

        return 1;
    }
    else if(ran == 2)
    {
        enemy->catch_msg("The daemonlord breathes gas at you!\n");
        tell_watcher(QCTNAME(me)+" breathes gas at "+QTNAME(enemy)+".\n", enemy);
        poison = clone_object("/std/poison_effect");
        if(poison) {
           poison->move(enemy);
           poison->set_time(1000);
           poison->set_interval(50);
           poison->set_strength(150);
           poison->set_damage(({POISON_FATIGUE, 100, POISON_STAT, SS_CON }));
           poison->start_poison();
        }
    }
    else if(ran == 3)
    {
        enemy->catch_msg("The daemonlord mutters under his breath and the "+
           "light fades from the room!\n");
        tell_watcher(QCTNAME(me)+" mutters under his breath and the light "+
           "fades from the room!\n", enemy);
        old_prop = ENV(TO)->query_prop(ROOM_I_LIGHT);
        ENV(TO)->set_prop(ROOM_I_LIGHT, (old_prop - 1));
        return 1;
    }
    else if(ran == 4)
    {
 	enemy->catch_msg("The Daemonlord punches you in the face and you "+
	   "feel dizzy.\n");
 enemy->add_attack_delay(5);
	tell_watcher("The Daemonlord punches "+QTNAME(enemy)+" hard in the "+
	   "face. "+QCTNAME(enemy)+" looks stunned.\n", enemy);
	return 1;
    }
    return 0;
}

void
do_die(object enemy)
{
   object death;

   if(query_hp() > 0) { return; }
   /* and not if(query_hp()) for query_hp() might be negative */
      
   if(!enemy) { enemy = previous_object(); }
   
   if(find_player("mylos"))
      find_player("mylos")->catch_msg(QCTNAME(enemy)+" has "+
        "just killed the Daemonlord.\n");
   death = clone_object("/d/Emerald/mylos/open/d_death");
   death->move(enemy, 1);

   ::do_die(enemy);
   return;
}
