inherit "/std/monster";
#include "/d/Shire/common/defs.h"

// Protoypes
void do_attack(object victim);

// Global Variables
int attack_alarm;

void call_for_friends(object ob)
{
  int i;
  object room, *arr;
  room = ENV(TO);
  while (!room->query_prop(ROOM_I_IS)) room = ENV(room);
  arr = all_inventory(room);
  arr = filter(arr,"shire_orc_filter",TO);
  for (i = 0; i < sizeof(arr); i++)
  arr[i]->notify_ob_attacked_friend(TO,ob);
}


/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    object *arr;
    int i;

    ::attacked_by(ob);

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(this_object(), ob);
    call_for_friends(ob);
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
    if (query_attack())
        return;

    if (random(10))
        set_alarm(itof(random(3)), 0.0, "help_friend", attacker);
}

/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
void
help_friend(object ob)
{
  if (ob && !query_attack() && present(ob, environment()))
  {
//  command("kill " + lower_case(ob->query_real_name()));
    switch(random(5))
    {
      case 0:
        command("say You'll pay for that!");
        break;
      case 1:
        command("growl all");
        break;
      case 2:
        command("snarl all");
        break;
      case 3:
        command("shout Die like the pig you are!");
        break;
      case 4:
        command("say I will kill you!");
        break;
    }
    command("assist");
  }
}


int 
shire_orc_filter(object orc)
{
   if(orc->id("_orcmaker_orc")) return 1;
   return 0;
}


int query_not_attack_me(object att, int att_id)
{
  if (!random(10))
    call_for_friends(att);
  return 0;
}

/*
* Function name: notify_ob_attacked_friend
   * Description:   This is called when someone attacks a team member of mine
* Arguments:     friend - My team mate
*                attacker - The attacker
*/
void
notify_ob_attacked_friend(object friend, object attacker)
   {
   if (query_attack()) return;
   
   if (random(10))
      set_alarm(6.0,0.0,"help_orc", ({attacker,TO}));
}

/*
* Function name: help_orc
* Description:   Help my friends by attacking their attacker
* Arguments:     attacker - The person who attacked my friend
*/
void
help_orc(object *arr)
{
   object ob, friend;
   ob     = arr[0];
   friend = arr[1];
   if(ob && !query_attack() && present(ob, ENV(TO)) && CAN_SEE(TO,ob))
   {
     command("shout You better run, stupid "+ob->query_race_name()+"!");
      attack_alarm = set_alarm(2.0, 0.0, &do_attack(ob));
   }
}

void
do_attack(object victim)
{
  remove_alarm(attack_alarm);
  if (query_attack()) return;
  if (victim->query_npc()) return;
  if (!present(victim,ENV(TO)) || !CAN_SEE(TO,victim)) {
    command("say I don't see anyone here, you brainless dung-eater!");
    return;
    }
  command("kill "+victim->query_real_name());
  command("shout I will smash this "+victim->query_race_name()+"!");
}


public void
init_attack()
{
   if(query_attack())
      return;
   
   set_alarm(0.0, 0.0, &check_attack(this_player()));
}


void
order_attack_enemy(object commander, object victim)
{
   if(query_attack()) return;
   if (!attack_alarm)
      attack_alarm = set_alarm(2.0, 0.0, &do_attack(victim));
}
