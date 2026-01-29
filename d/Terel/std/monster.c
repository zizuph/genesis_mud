/* -*- C++ -*- */

/*
 * Terel standard monster
 *
 * All the monsters in the domain should inherit this one.
 * Code to handle intros based on Mercade's tutorial.
 * Autoassist code by Udana
 * Anty-Bounce code by Udana
 * Skill add code by Lilith
 * Changed bouncing code to not hit extra when hunting by Petros
 * 
 * Cotillion - 2017-04-20
 * - Fixed runtime in remove_me_from_list 
 */

#include "/d/Terel/include/Terel.h"
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <options.h>
#include <ss_types.h>

#define MONSTER_BEEN_ATTACKED_BY "_monster_been_attack_by"
/* Weapon pen multiplier for special re_enter hit. */
#define RE_ENTER_MOD 10 + random(10)
#define SEND(x) find_player("udana")->catch_msg(x + "\n")

inherit "/std/monster";
inherit "/d/Terel/std/living_extra";
inherit "/d/Terel/include/log_asks";

/*
 * Prototypes
 */

void remove_me_from_list(string whos_name);
void introduce_me(object who);
public void set_assist(string f_name, int a_flag = 1);
/*
 * Global Variables
 */

public string   friend_name;
public int      always_assist = 1;
public int      rAlarm = 0;
public int      is_moving = 0;

/*
 * Function name: create_terel_monster
 * Description:   Configure this monster
 */
public void
create_terel_monster()
{
  
}


/*
 * Function name: add_basic_skills
 * Description:   add basic and general skills to npcs at lvl 40
 *                randomly add magic and thief skills at lvl 40
 */
public void
add_basic_skills()
{
    /* general skills always added */
    set_skill(SS_LANGUAGE,40);
    set_skill(SS_HERBALISM,40);
    set_skill(SS_APPR_MON,40);
    set_skill(SS_APPR_OBJ,40);
    set_skill(SS_APPR_VAL,40);
    set_skill(SS_SWIM,40);
    set_skill(SS_CLIMB,40);
    set_skill(SS_ANI_HANDL,40);
    set_skill(SS_LOC_SENSE,40);
    set_skill(SS_TRACKING,40);
    set_skill(SS_HUNTING,40);
    set_skill(SS_AWARENESS,40);
    set_skill(SS_TRADING,40);
    set_skill(SS_RIDING,40);

    /* basic combat skills always added */
    set_skill(SS_2H_COMBAT, 40);
    set_skill(SS_DEFENCE,40);
    set_skill(SS_PARRY,40);
    set_skill(SS_UNARM_COMBAT,40);
    set_skill(SS_BLIND_COMBAT,40);
    set_skill(SS_AWARENESS,40);
    set_skill(SS_WEP_SWORD,40);
    set_skill(SS_WEP_POLEARM,40);
    set_skill(SS_WEP_AXE,40);
    set_skill(SS_WEP_KNIFE,40);
    set_skill(SS_WEP_CLUB,40);
    set_skill(SS_WEP_MISSILE,40);


    /* magic skills randomly set */
    if (random(7))
    {
        set_skill(SS_SPELLCRAFT,40);
        set_skill(SS_ALCHEMY,40);
        set_skill(SS_FORM_TRANSMUTATION,40);
        set_skill(SS_FORM_ILLUSION,40);
        set_skill(SS_FORM_DIVINATION,40);
        set_skill(SS_FORM_ENCHANTMENT,40);
        set_skill(SS_FORM_CONJURATION,40);
        set_skill(SS_FORM_ABJURATION,40);
        set_skill(SS_ELEMENT_FIRE,40);
        set_skill(SS_ELEMENT_AIR,40);
        set_skill(SS_ELEMENT_EARTH,40);
        set_skill(SS_ELEMENT_WATER,40);
        set_skill(SS_ELEMENT_LIFE,40);
        set_skill(SS_ELEMENT_DEATH,40);
    }

    /* thief skills randomly set */    
    if (random(4))
    {
        set_skill(SS_OPEN_LOCK,40);
        set_skill(SS_PICK_POCKET,40);
        set_skill(SS_ACROBAT,40);
        set_skill(SS_FR_TRAP,40);
        set_skill(SS_SNEAK,40);
        set_skill(SS_HIDE,40);
        set_skill(SS_BACKSTAB,40);
    }
}


/*
 * Function name: create_monster
 * Description:   This should really be nomask, but Terel monsters which
 *                inherit this file already mask it. Future code should *not*
 *                use this, but create_terel_monster()
 */
public void
create_monster()
{
    add_prop(MONSTER_BEEN_ATTACKED_BY, ({}));
    add_prop(MONSTER_I_NOT_BOUNCED, 1);
    add_basic_skills();
    create_terel_monster();
    equip_me();
    equip_actions();
  
}

void list_remove(string str)
{
	if(!pointerp(query_prop(MONSTER_BEEN_ATTACKED_BY)))
		add_prop(MONSTER_BEEN_ATTACKED_BY, ({}));
  string *list = query_prop(MONSTER_BEEN_ATTACKED_BY);
  if(member_array(str, list) != -1)
    add_prop(MONSTER_BEEN_ATTACKED_BY, list - ({str}));
}

void list_add(string str)
{
	if(!pointerp(query_prop(MONSTER_BEEN_ATTACKED_BY)))
		add_prop(MONSTER_BEEN_ATTACKED_BY, ({}));
  string *list = query_prop(MONSTER_BEEN_ATTACKED_BY);
  if(member_array(str, list) == -1)
    add_prop(MONSTER_BEEN_ATTACKED_BY, list + ({str}));
}

/*
 * Function name: remove_me_from_list
 * Description:   Removes give player from list of
 *              fought enemies.
 */
void remove_me_from_list(string whos_name)
{
    if (!stringp(whos_name))
        return;

    /* will be removed later */
    if (pointerp(get_alarm(rAlarm)))
    {
        mixed *calls = get_alarm(rAlarm);
        mixed *args = calls[4];
        if(args[0] == whos_name)
            return;
    }

    object who = find_player(whos_name);
    /* player logged off, lets remove him */
    if(!objectp(who))
    {
        list_remove(whos_name);
        return;
    }

    /* they are fighting each other right now, check again later. */
    if(query_attack() == who || who->query_attack() == TO)
    {
        rAlarm = set_alarm(30.0, 0.0, &remove_me_from_list(whos_name));
        return;
    }

    /* all is fine, lets remove him */
    list_remove(whos_name);
}

/*
 * Function name: do_die(object ob)
 * Description:   Called when we die.
 */
public void do_die(object ob)
{
  /* he's dead, he's got no emies. */
  add_prop(MONSTER_BEEN_ATTACKED_BY, ({}));
  ::do_die(ob);
}


/*
 * Function name: re_enter_hit
 * Description:   Hit given living with additional damage.
 */
void re_enter_hit(object enemy)
{
  string desc = "";
  object my_weapon;
  int wpen, wdt = W_BLUDGEON;
  string a_desc, v_desc, w_desc;
  object *watchers = FILTER_LIVE(all_inventory(environment(this_object()))) - ({enemy, this_object()}); 

  /* he's set to be bouncable */
  if(!query_prop(MONSTER_I_NOT_BOUNCED))
	return;
  
  /* he's not a player */
  if(!interactive(enemy))
	return;
  
  /* he left */
  if(environment(TO) != environment(enemy))
	return;
  
  /* it can't see the enemy */
  if(!CAN_SEE(TO, enemy))
    return;

  /* fist fighting */
  if(!sizeof(query_weapon(-1)))
  {
    desc = "batters";
    w_desc = "fist";
  }
  else
  {
    my_weapon = query_weapon(-1)[0];
    w_desc = my_weapon->query_short();
	int w_dt = my_weapon->query_dt();
	
    if(!strlen(desc) && (w_dt &  W_IMPALE) > 0)
    {
      desc = "jabs";
      wdt = W_IMPALE;
    }
    if(!strlen(desc) && (w_dt &  W_SLASH) > 0)
    {
      desc = "slashes";
      wdt = W_SLASH;
    }
    if(!strlen(desc))
      desc = "slams";
  }
  wpen = objectp(my_weapon) ? my_weapon->query_pen() * RE_ENTER_MOD : 20 * RE_ENTER_MOD;
  /* actual hit */
  enemy->hit_me(wpen, wdt, TO, -1, A_HEAD);
  
  a_desc = CAN_SEE(enemy, this_object()) ? QNAME(this_object()) : "someone";
  enemy->catch_msg("Being prepared for you to come back, " + a_desc + " " + desc + " your head with "+
    "his " + w_desc + ".\n");
  for(int i = 0; i < sizeof(watchers); ++i)
  {
    a_desc = CAN_SEE(watchers[i], this_object()) ? QCNAME(this_object()) : "Someone";
    v_desc = CAN_SEE(watchers[i], enemy) ? QTNAME(enemy) : "someone";
    if(a_desc != "someone" || v_desc != "someone")
      if(!watchers[i]->query_option(OPT_NO_FIGHTS))
        watchers[i]->catch_msg(CAP(a_desc) + " " +  desc + " " + v_desc + " on the head with his " + w_desc + ".\n");
  }
}

/*
 * Function name:   adjust_combat_on_move
 * Description:     Called to let movement affect the ongoing fight. This
 *                  is used to print hunting messages.
 * Arguments:       True if leaving else arriving
 */
public void 
adjust_combat_on_move(int leave)
{
    if (leave)
    {
        // Leaving, so we know we're moving.
        is_moving = 1;
    }
    else
    {
        // Arriving, so ending movement
        is_moving = 0;
    }
}

/*
 * Function name: init_living
 * Description  : overload standard init living function, if player is re-entering
 *                combat with this monster he gets an additional hit.
 */
public void init_living()
{

  if (!is_moving 
      && IN_ARRAY(TP->query_real_name(), query_prop(MONSTER_BEEN_ATTACKED_BY)))
  {
   /* hit the bouncer! */
    set_alarm(1.0, 0.0, &re_enter_hit(TP));
  }
   ::init_living();
}


/*
 * Function name: set_assist
 * Description: Monsters with given name will assist this monster every
 *              time it's attacked. The second argument is a flag -
 *              if positive the monsters will attack even if he can't see in
 *              that room. It's true by default.
 */
public void set_assist(string f_name, int a_flag = 1)
{
  friend_name = f_name;
  always_assist = a_flag;
}

/*
 * Function name: help_terel_friend
 * Description: Makes us assist given monster against given attacker
 * Note: Function name is so weird becouse help_friend name is a typical name
 *       people have been using in Terel.
 */
public void help_terel_friend(object victim, object enemy)
{
  string a_display, m_display;
  object *watchers = FILTER_LIVE(all_inventory(environment(this_object()))) - ({enemy, this_object()});
  if(victim == this_object())
    return;
  if(!always_assist && !CAN_SEE(this_object(), enemy))
    return;
  if(!present(enemy, environment(this_object())))
    return;
  /* he's already fighting */
  if(objectp(query_attack()))
	return;
  attack_object(enemy);
  m_display = CAN_SEE(enemy, this_object()) ? QCTNAME(this_object()) : "Someone";
  enemy->catch_msg(m_display + " attacks you!\n");
  for(int i = 0; i < sizeof(watchers); ++i)
  {
    m_display = CAN_SEE(watchers[i], this_object()) ? QCTNAME(this_object()) : "Someone";
    a_display = CAN_SEE(watchers[i], enemy) ? QTNAME(enemy) : "someone";
    if(a_display != "someone" || m_display != "Someone")
      watchers[i]->catch_msg(m_display + " attacks " + a_display + ".\n");
  }
}

/*
 * Function name: request_terel_help
 * Description: Makes us call others for help.
 * Note: Function name is so weird becouse request_help name is a typical name
 *       people have been using in Terel.
 */

void request_terel_help(object enemy)
{
  object *friends = filter(all_inventory(environment(this_object())), &->id(friend_name));
  for(int i = 0; i < sizeof(friends); ++i)
    friends[i]->help_terel_friend(TO, enemy);
}

/*
 * Function name: attack_object
 * Description: Called when we attack.
 */
public void attack_object(object ob)
{
  ::attack_object(ob);
  set_alarm(1.0, 0.0, &list_add(ob->query_real_name()));
  rAlarm = set_alarm(30.0, 0.0, &remove_me_from_list(ob->query_real_name()));
}

/*
 * Function name: attacked_by
 * Description: Called when we're attacked.
 */
public void attacked_by(object attacker)
{
  ::attacked_by(attacker);
  set_alarm(1.0, 0.0, &list_add(attacker->query_real_name()));
   rAlarm = set_alarm(30.0, 0.0, &remove_me_from_list(attacker->query_real_name()));
  set_alarm(1.0, 0.0, &request_terel_help(attacker));  
}

/*
 * Function name: enable_intro
 * Description  : set a property that will enable this monster to
 *                react to introductions.
 */
public void
enable_intro()
{
    add_prop(LIVE_I_INTRO_ENABLED, 1);
}

/*
 * Function name: disable_intro
 * Description  : set a property that will disable this monster to
 *                react to introductions.
 */
public void
disable_intro()
{
    remove_prop(LIVE_I_INTRO_ENABLED);
}

int last_introduction = 0;

/*
 * Function name: add_introduced
 * Description  : Whenever someone is introduced to me (CC), this function
 *                is called in me to tell me that 'name' (BB) is being
 *                introduced to me. The living that does the introduction
 *                (AA) is available though this_player().
 * Arguments    : string name - the [lower case] name of the living that
 *                              is being introduced to me. (BB)
 */
public void
add_introduced(string name)
{
    /* In players, this function makes sure that 'name' appears on your
     * 'introduced' list and then you may later 'remember' him/her. In
     * NPC's you may for instance use it to return the honour by
     * introducing yourself. Note that we don't necessarily have to use
     * an alarm since this function is called _after_ all messages from
     * the original introduction have been printed.
     */

    object who;

    if (!(TO->query_prop(LIVE_I_INTRO_ENABLED))) {
	return;
    }
    
    if ((who = present(name, ETO)) == 0) {
	return;
    }

    if (!who || (ETO != ENV(who))) {
	return;
    }

    if (!(who->query_met(TO))) {
	introduce_me(who);
    }
}

/*
 * Function name: introduce_me
 * Description  : called when an introduction is to be performed.
 * Arguments    : string name - the [lower case] name of the living that
 *                              is being introduced to me. (BB)
 */
public void
introduce_me(object who)
{
    command("introduce me to " + OB_NAME(who));
}

/*
 * Handle intros
 *
 *  trig_new("%s 'introduces' %s", "react_introduce");
 *
 */

return_introduce(string who)
{
    object *obs;
    string name, dummy;
    if ((last_introduction + 10) > time())
	return;

    last_introduction = time();

    TO->command("introduce myself to " + who);
}

