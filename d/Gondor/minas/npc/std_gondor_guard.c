/* 
 * /d/Gondor/minas/npc/std_gondor_guard.c
 *
 * some routines follow /doc/examples/mobiles/troll.c
 *
 * Borrowed from /d/Gondor/morgul/npc/ithil_monster,
 * By Olorin 14-july-93
 * This file stolen by Dunstable, Mar 94
 *
 *	Modification log:
 *	 1-Feb-1997,  Olorin:	Changed make_money to inherit.
 *       12-Sep-2002, Rohim:    Changed move(TO) to move(TO, 1)
 */

#pragma strict_types

inherit "/d/Gondor/minas/npc/mtirith_monster.c";
inherit "/d/Gondor/common/lib/make_money.c";

#include <composite.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define WEP_ARRAY1 ({WEP_DIR + "hhalberd",WEP_DIR + "gspear", WEP_DIR + "dlongsword"})
#define WEP_ARRAY2 ({ })
#define ARM_ARRAY1 ({ARM_DIR + "schainmail", ARM_DIR + "gchainmail"}) 
#define ARM_ARRAY2 ({ARM_DIR + "ghelmet"})
#define ARM_ARRAY3 ({ })
#define DID_ATTACK_MT_GATES    "_attacked_mt_gate"

object lamp;
string *wep1, *wep2, *arm1, *arm2, *arm3;
int  da_aid;
string alignlook();
void do_attack(object victim);
void help_friend(object *arr);
public varargs int	move_living(string how, mixed to_dest,
				    int dont_follow, int no_glance);
public void		destroy_eyes();

void 
create_monster()
{
   int rnd;
   seteuid(getuid(TO));

   set_name("guard");
   add_name("_gondor_guard");
   set_race_name("human");
   set_adj("tall");
   add_adj(alignlook());
   rnd = random(10);
   set_skill(SS_AWARENESS,     55+rnd);
   set_skill(SS_CLIMB,        45+rnd);
   set_skill(SS_BLIND_COMBAT, 50+rnd);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop("_live_m_attack_thief", 1);
   set_alignment(300 + random(100));

   set_alarm(1.0, 0.0, get_money);
    set_alarm(2.0, 0.0, refresh_mobile);
   add_act("@@adjust_lamplight");
   add_cact("@@adjust_lamplight");
}

void
set_arm_arrays()
{
   wep1 = WEP_ARRAY1;
   wep2 = WEP_ARRAY2;
   arm1 = ARM_ARRAY1;
   arm2 = ARM_ARRAY2;
   arm3 = ARM_ARRAY3;
}

void
arm_me()
{
    int iw, is;
   
    set_arm_arrays();
    
    seteuid(getuid(TO));
    
    if (random(3))
    {
	lamp = clone_object("/d/Gondor/minas/obj/g_oil_lamp");
	lamp->set_time_left(10000);
	lamp->move(TO, 1);
    }
    
    if (is = sizeof(wep1))
    {
	iw = random(is);
	clone_object(wep1[iw])->move(TO, 1);
    }
    
    command("wield weapon");
    
    if (wep1[iw]->query_hands() != W_BOTH)
    {
	
	if(is = sizeof(wep2))
	{
	    iw = random(is);
	    clone_object(wep2[iw])->move(TO, 1);
	}
    }
    
    if (is = sizeof(arm1))
    {
	iw = random(is);
	clone_object(arm1[iw])->move(TO, 1);
    }
    
    if (is = sizeof(arm2))
    {
	iw = random(is);
	clone_object(arm2[iw])->move(TO, 1);
    }
    
    if (is = sizeof(arm3))
    {
	iw = random(is);
	clone_object(arm3[iw])->move(TO, 1);
    }
    
    command("wield all");
    command("wear all");
    set_hp(query_max_hp());
}

int 
gondor_guard_filter(object guard)
{
   if(guard->id("_gondor_guard")) return 1;
   return 0;
}

void
adjust_lamplight()
{
  int envl;
  if (!lamp) return;
  envl = ENV(TO)->query_prop(OBJ_I_LIGHT);
  if (envl < 1) {
    command("say It's too dark here, we need more light!");
    if (!lamp->light_me())
    {
        command("say Oh no, I'm out of oil!");
        lamp->set_time_left(2000);
    }
  else {
    tell_room(ENV(TO),QCTNAME(TO)+" lights his oil-lamp.\n");
    command("say That's better!");
    }
    }
  else if (envl > 1) {
    if (lamp->extinguish_me()) {
    if (!random(4))
    {
    command("say I don't need to spend oil on this lamp right now.");
    tell_room(ENV(TO),QCTNAME(TO)+" extinguishes his oil-lamp.\n");
    }
    lamp->set_time_left(10000);
    }
    }
  return;
}


void call_for_friends(object ob)
{
  int i;
  object room, *arr;
  room = ENV(TO);
  while (!room->query_prop(ROOM_I_IS)) room = ENV(room);
  arr = all_inventory(room);
  arr = filter(arr,"gondor_guard_filter",TO);
  for (i = 0; i < sizeof(arr); i++)
  arr[i]->notify_ob_attacked_me(TO,ob);
}

void
find_weapon()
{
  if (present("weapon",TO)) {
    command("wield "+present("weapon",TO)->query_name());
    return;
    }
  command("get weapon");
  command("wield weapon");
}

void
attacked_by(object ob)
{
   ::attacked_by(ob);
  call_for_friends(ob);
}

int query_not_attack_me(object att, int att_id)
{
  if (att->query_prop(DID_ATTACK_MT_GATES)!=1)
    att->add_prop(DID_ATTACK_MT_GATES,1);
  if (!random(10))
    call_for_friends(att);
  if (!random(5))
    adjust_lamplight();
  if (!random(5))
    find_weapon();
  if (!random(5) && (TO->id("officer")) &&
    (strlen(ENV(TO)->query_dir_to_gate())))
  {
    command("shout To me! Retreat towards the gate!");
    command(ENV(TO)->query_dir_to_gate());
  }
  if (att->query_average_stat() > 70 && !random(10)) {
    command("shout Men of Gondor! Help!");
    ENV(TO)->start_archers();
    }
  return 0;
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
   if (query_attack()) return;
   
   if (random(10))
      set_alarm(rnd()*5.0, 0.0, &help_friend(({ attacker, TO })));
}

/*
* Function name: help_friend
* Description:   Help my friends by attacking their attacker
* Arguments:     attacker - The person who attacked my friend
*/
void
help_friend(object *arr)
{
   object ob, friend;
   ob     = arr[0];
   friend = arr[1];
   if (!random(5))
     adjust_lamplight();
   if(ob && !query_attack() && present(ob, ENV(TO)) && CAN_SEE(TO,ob))
      {
      if (!random(4))
        command("shout In the name of Gondor, begone, foul " + ob->query_race_name()
         + "!");
      if (!da_aid)
        da_aid = set_alarm(4.0, 0.0, &do_attack(ob));
   }
}

void
do_attack(object victim)
{
  if (query_attack()) return;
  if (victim->query_npc()) return;
  if (victim->query_wiz_level()) return;
  if (!present(victim,ENV(TO)) || !CAN_SEE(TO,victim)) {
    command("say Who? Where?");
    return;
    }
  command("kill "+victim->query_real_name());
  if (!random(4))
    command("shout I will kill you, "+victim->query_race_name()+", enemy of Gondor!");
}

string
alignlook() 
{
   string *alignlooks;
   alignlooks = ({"noble", "stern", "dark-haired", "scarred","battle-tested",
         "strong", "lean", "stout", "friendly", "aged", 
         "tough"});
   return alignlooks[random(sizeof(alignlooks))];
}

void
check_attack(object pl)
{
  if (query_friend_or_foe(pl) < 0  ||
    pl->query_prop(DID_ATTACK_MT_GATES))
    da_aid = set_alarm(rnd()*3.0 + 1.0, 0.0, &do_attack(pl));
}

public void
init_attack()
{
   if(query_attack())
      return;
   
    set_alarm(0.3, 0.0, &check_attack(TP));
}


void
order_attack_enemy(object commander, object victim)
{
   if(query_attack()) return;
   if (!da_aid)
      da_aid = set_alarm(2.0, 0.0, &do_attack(victim));
}

int
query_knight_prestige() { return -5; }



/*
 * Function name:	move_living
 * Description	:	mask parent so we can check new env for spying eyes
 * Arguments	:	string how -- direction of travel, etc
 *			mixed to_dest -- destination
 *			int dont_follow -- flag re group movement
 *			int no_glance -- flag re looking in new room
 * Returns	:	int -- 0 on success, non-0 on failure
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int rval;
    rval = ::move_living(how, to_dest, dont_follow, no_glance);

    if (objectp(present("eye", ENV(TO))))
    {
	set_alarm(2.0, 0.0, destroy_eyes);
    }
    return rval;
} /* move_living */

/*
 * Function name:	destroy_eyes
 * Description	:	smash any spying eyes in env
 */
public void
destroy_eyes()
{
    object	*eyes;
    int		s;

    s = sizeof(eyes = filter(all_inventory(ENV(TO)), &->id("eye")));
    if (s > 0)
    {
	command("emote smashes the glass eye" +
	    (s > 1 ? "s." : "."));
	eyes->remove_object();
    }
} /* destroy_eyes */
