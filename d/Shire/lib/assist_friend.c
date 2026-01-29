/*
 * This file contains all the routines necessary to force npcs to
 * assist each other when attacked. Simply include it in each 
 * npc file, and that's all there is to it!
 * 
 * The routines for this file come from several Shire npcs and 
 * then was implemented in the Esgaroth npcs, hence the esgaroth 
 * influence. 
 *
 * start_follow routine borrowed from Gondor.

 * -- Finwe, February 2002
 */

#include <stdproperties.h>
#include <formulas.h>
#include "/d/Shire/sys/defs.h"

inherit SHIRE_MONSTER;
inherit "/std/act/attack";

//#include "../local.h"


int attack_alarm;
// shire_npc_name = 'name' of area npcs
string shire_npc_name = "_shire_npc_";
string attack_message = "";

void test_can_see(object victim);
void help_friend(object ob, object friend);

static  object  Victim;

/****************************************************************
 * sets up the hunting routine in players who attack npcs
 ****************************************************************/

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
/*****************************************************************/


/****************************************************************
 * routines for npcs to assist each other when attacked
 ****************************************************************/

int
shire_monster_filter(object monster)
{
   if (monster->id(shire_npc_name))
       return 1;
   return 0;
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

//   start_follow(ob);

   while (!room->query_prop(ROOM_I_IS))
      room = ENV(room);
   arr = filter(all_inventory(room), shire_monster_filter);
   arr->notify_ob_attacked_me(TO, ob);

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
   
   set_alarm(2.0, 0.0, &help_friend(attacker, TO));
}

void
do_attack(object victim)
{
/*
   if (objectp(query_attack()))
       return;
*/
   if (victim->query_npc())
       return;
   if (!present(victim, ENV(TO)))
       return;
   if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, victim))
   {
      if (!sizeof(get_alarm(attack_alarm)))
          attack_alarm = set_alarm(5.0, 10.0, &test_can_see(victim));
      command("shout Where is the enemy? I can't see him!");
      return;
   }
   command("kill "+victim->query_real_name());
}

/*
* Function name: help_friend
* Description:   Help my friends by attacking their attacker
* Arguments:     attacker - The person who attacked my friend
*/
void
help_friend(object ob, object friend)
{
   if (objectp(ob) && !objectp(query_attack()) &&
       present(ob, ENV(TO)) && //F_DARE_ATTACK(TO, ob) &&
       CAN_SEE_IN_ROOM(TO) && CAN_SEE(TO, ob))
   {
       do_attack(ob);
//       start_follow(ob);

   }
}  

void
test_can_see(object victim)
{
    if (!present(victim,ENV(TO)))
    {
        remove_alarm(attack_alarm);
        attack_alarm = 0;
        return;
    }
    if (CAN_SEE_IN_ROOM(TO) && CAN_SEE(TO,victim))
    {
        remove_alarm(attack_alarm);
        attack_alarm = 0;
        do_attack(victim);
    }
}

/*****************************************************************/