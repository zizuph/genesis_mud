/*
 *  This is the Harondor Haradrim master file.
 *  Serif, September 2001. 
 *
 *  Modified from portions of /d/Gondor/morgul/npc/ithil_olog.c
 */

#pragma strict_types

inherit "/std/monster";
inherit "/d/Gondor/common/lib/make_money.c";

#include <stdproperties.h>
#include <composite.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

#define ATTACKED_HARADRIM  "_attacked_haradrim"

static  int     Attack_Alarm,
                Wimpy_Run;
int attack_alarm;
public int	query_knight_prestige();
public string	*random_haradrim();
static  object  Victim;

void    help_friend(object ob, object friend);
void    test_can_see(object victim);

string random_haradrim();

string    /* List of adjectives for the haradrim. */
random_haradrim()
{
    string *har = ({"stealthy", "sinewy", "lean", "watchful",
        "weathered", "furtive"});

    return ONE_OF_LIST(har);
}

public void
create_monster()
{
   string har = random_haradrim(),
       har2 = har;

   set_adj(har);
   add_adj("dark-skinned");
   add_adj("male");
   set_short(har2 + " dark-skinned male human");
   set_name("haradrim");
   add_name(({"scout", "southron", "haradrim", "man"}));
   add_name("_harondor_haradrim"); 
   add_pname(({"southrons", "scouts", "haradrim", "men"}));
   set_race_name("human");
   set_long("This is one of the warriors of Harad. He is a typical "
        + "southron, tall of stature and with dark skin. He seems "
        + "somewhat cautious, and moves with quiet deliberation, "
        + "as if trying to avoid notice.\n");

   set_base_stat(SS_STR, 75 + random(15));
   set_base_stat(SS_DEX, 85 + random(15));
   set_base_stat(SS_CON, 75 + random(15));
   set_base_stat(SS_INT, 75 + random(15));
   set_base_stat(SS_WIS, 75 + random(15));
   set_base_stat(SS_DIS, 100 + random(15));
   set_skill(SS_WEP_SWORD, 95 + random(5));
   set_skill(SS_PARRY, 95 + random(5));
   set_skill(SS_DEFENCE, 95 + random(5));
   set_skill(SS_AWARENESS, 70 + random(10));
   set_skill(SS_UNARM_COMBAT, 65 + random(10));
   set_skill(SS_2H_COMBAT, 85 + random(10)); 
   set_skill(SS_WEP_KNIFE, 95 + random(5));
   set_skill(SS_BLIND_COMBAT, 65 + random(10));
   set_skill(SS_SNEAK, 80 + random(20));
   set_skill(SS_HIDE, 75 + random(25));

   set_alignment(-250 + random(200));

   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(CONT_I_HEIGHT, 180 + random(20));
   add_prop(CONT_I_WEIGHT, 68000 + random(6000));
   add_prop(CONT_I_VOLUME, 68000 + random(6000));

   set_random_move(11 + random(3));
   set_restrain_path("/d/Gondor/ithilien/forest/");
   set_whimpy(30);

   set_tell_active(1);
   set_cchat_time(4 + random(2));
   add_cchat("Die, you filthy wretch!");
   add_cchat("I will flood the ground with your blood!");
   add_cchat("After I defeat you, I shall toss your body into the Poros!");
   add_cchat("For Harad!");
   add_cchat("Curse you, you fool!");

   set_act_time(15);
   add_act("assist haradrim");

   get_money();

   clone_object(HAR_WEP_DIR + "h_scimitar")->move(this_object());
   command("wield all");

   clone_object(HAR_ARM_DIR + "leather_vest")->move(this_object());
   clone_object(HAR_ARM_DIR + "leather_cap")->move(this_object());
   clone_object(HAR_ARM_DIR + "hide_shield")->move(this_object());
   command("wear all");

   set_alarm(0.0, 0.0, &command("hide"));

}

/*
 * Function name:   start_follow
 * Description:     Start following the enemy.
 * Arguments:       The object to follow.
 */
public void
start_follow(object ob)
{
    object *follower,
            shadow;

    if (!objectp(ob) || !objectp(present(ob, ENV(TO))) || 
	(ob != query_attack()) || (Victim == ob))
	return;

    if (pointerp(follower = ob->query_follower()))
    {
	if (member_array(TO, follower) < 0)
	    ob->add_follower(TO);
    }
    else
    {
	shadow = clone_object(GONDOR_FOLLOW_SHADOW);
	shadow->follow(ob, TO);
    }
    Victim = ob;
}

public varargs void
remove_victim(object victim)
{
    if (objectp(victim) && (Victim != victim))
	return;
    Victim = 0;
}

/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 * Arguments:       The object to attack
 */
public void
attack_object(object ob)
{
    ::attack_object(ob);
    start_follow(ob);
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    object  room = ENV(TO),
          *arr;
    
    ::attacked_by(ob);

    start_follow(ob);

    while (!room->query_prop(ROOM_I_IS))
	room = ENV(room);
    arr = filter(all_inventory(room), &->id("haradrim"));
    arr->notify_ob_attacked_me(TO, ob);
    ob->add_prop(ATTACKED_HARADRIM, 1);
}

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *                attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
   if (objectp(query_attack()))
      return;
   
   if (random(10))
      set_alarm(5.0, 0.0, &help_friend(attacker, TO));
}

void
do_attack(object victim)
{
   object *arr;
   if (objectp(query_attack()) || !objectp(present(victim, ENV(TO))))
       return;

   if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, victim))
   {
      if (!Attack_Alarm || !sizeof(get_alarm(Attack_Alarm)))
          Attack_Alarm = set_alarm(5.0, 10.0, &test_can_see(victim));
        command("hmm");
        command("peer");
        return;
   }

   command("kill "+victim->query_real_name());
   command("reveal me");

   if (objectp(query_attack()))
   {
	arr = filter(all_inventory(ENV(TO)), &->id("haradrim")) - ({ TO });
	arr->order_attack_enemy(TO, victim);
   }
}

/*
 * Function Name:    help_friend
 * Description:      Help my friends by attacking thier attacker.
 * Arguments:        attacker- The person who attacked my friend.
 */
void
help_friend(object ob, object friend)
{
    if (objectp(ob) && !objectp(query_attack()) &&
        present(ob, ENV(TO)) && CAN_SEE(TO, ob) && F_DARE_ATTACK(TO, ob))
    {
        command("say You will die for this, "+ob->query_race_name()+"!");
        do_attack(ob);
        command("reveal me");
    }
}

void
react_attacker(object player)
{
    if (IS_RANGER(player))
    {
        if (!random(4))
            command("say It is one of the accursed Rangers!");
    }
    else if (!random(4))
    {
        command("say Death take you!");
    }
    set_alarm(1.0, 0.0, &do_attack(player));
}

int
check_attack(object player)
{
    if (query_attack())
        return 0;
    if (CAN_SEE(TO, player) && CAN_SEE_IN_ROOM(TO) &&
        (player->query_prop(ATTACKED_HARADRIM) ||
        (IS_RANGER(player) && random(player->query_stat(SS_OCCUP)) > 40)))
    {
        set_alarm(2.0, 0.0, &react_attacker(player));
        return 1;
    }
}

public void
init_attack()
{
    if (query_attack())
	return;
    if (!interactive(TP))
	return;
    check_attack(TP);
}

void
loot_corpse()
{
    command("get all from corpse");
}

void
test_can_see(object victim)
{
    if (!present(victim, ENV(TO)))
    {
	remove_alarm(attack_alarm);
	attack_alarm = 0;
	return;
    }
    if (CAN_SEE_IN_ROOM(TO) && CAN_SEE(TO, victim))
    {
        remove_alarm(attack_alarm);
        attack_alarm = 0;
        do_attack(victim);
        command("reveal me");
    }
}

void
remove_surplus(object ob)
{
    command("wear all");
    if (!sizeof(query_weapon(-1)))
    command("wield weapon");
    if (!objectp(ob->query_worn()) && !objectp(ob->query_wielded()))
      ob->remove_object();
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!objectp(ob) || !objectp(from))
      return;
    if (!query_prop(NPC_M_NO_ACCEPT_GIVE))
      return;
    if (query_encumberance_weight() > 50 ||
        query_encumberance_volume() > 80)
      set_alarm(1.0, 0.0, &remove_surplus(ob));
}

public int	query_knight_prestige()	{ return 90; }

/*
 * This function makes the ranger sneak when moving randomly
 */
mixed
oke_to_move(string exit)
{
    if (this_object()->query_attack())
	return 0;

    return "sneak "+exit;
}

varargs void
sneak_away(string dir)
{
    string *dirs;

    if (strlen(dir))
    {
        command("sneak "+dir);
        return;
    }

    dirs = ENV(TO)->query_exit_cmds();

    dir = ONE_OF_LIST(dirs);

    command("sneak "+dir);
    sneak_away(dir);
}
