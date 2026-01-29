/* This is the object that blocks the exit for the enemy of a knight */

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

mapping person_exit = ([ ]);
/* ([ knight1:"west", knight2:"east", ... ]) */

/*prototype*/
int attack_and_environment_check();
object query_blocking_person(string the_exit);

public void
create_object()
{
    set_name("blblblblbl");
    add_name("knight_block_object");
    add_prop(OBJ_M_NO_DROP, 1);
    set_no_show();
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VALUE, 0);
    seteuid(getuid(TO));
}

public void
init()
{
    add_action("do_check","",1);
    ::init();
}

/* add some exit to be blocked by a knight.
 * return 0 if not successful, 1 if successful.
 */
int
add_blocked_exit(object who, string exit_name)
{
    object owner = E(TO);
    if (!owner || !owner->query_prop(LIVE_I_IS))
      return 0;
    /* inside max 1 knight can block an exit. */
    if (E(owner)->query_prop(ROOM_I_INSIDE))
      {
	  if (member_array(exit_name, m_values(person_exit)) > -1)
	    {
		who->catch_msg(QCTNAME(query_blocking_person(exit_name)) +
			       " is already blocking the " + exit_name + " exit.\n");
		return 0;
	    }
      }    
    if (member_array(who, m_values(person_exit)) >= 0)
      person_exit = m_delete(person_exit, who);
    person_exit += ([ who:exit_name ]);
    add_name(who->query_real_name() + "_block_object");
    return 1;
}

int
remove_blocked_exit(object who, string how)
{
    int i = member_array(who, m_indexes(person_exit)) + 1;
    if (!i)
      return 0;
    who->catch_msg(how);
    person_exit = m_delete(person_exit, who);
    remove_name(who->query_real_name() + "_block_object");
    if (m_sizeof(person_exit) == 0)
      set_alarm(0.1,0.0,"remove_object_now");
    return 1;
}

string
query_blocked_exit(object person)
{
    return person_exit[person];
}

string *
query_blocked_exits()
{
    return m_values(person_exit);
}

object *
query_blocking_persons()
{
    return m_indexes(person_exit);
}

object
query_blocking_person(string the_exit)
{
    return mkmapping(m_values(person_exit),
		     m_indexes(person_exit))[the_exit];
}

int
do_block(string str)
{
    object owner = E(TO);
    object *persons = ({ });
    object person;
    mixed *tmp = m_indexes(person_exit);
    int i, success, bsk, accumulate = 0;
    if (!attack_and_environment_check())
      return 0;
    
    for(i=0;i<sizeof(tmp);i++)
      if (person_exit[tmp[i]] == query_verb())
	persons += ({ tmp[i] });
    
    for(i=0;i<sizeof(persons);i++)
      {
	  person = persons[i];
	  success = (person->query_stat(SS_DEX) * person->query_stat(SS_WIS)- 
		     owner->query_stat(SS_STR) * owner->query_stat(SS_INT));
	  success = success / 20 + 300;
	  bsk = person->query_skill(SS_BLOCK);
	  success += (bsk * (200 - bsk) / 20);
	  if (!CAN_SEE(person, owner))
	    success -= (success * (100 - person->query_skill(SS_BLIND_COMBAT))
			/ 200);
	  if (!CAN_SEE(owner,person))
	    success += (success * (100 - owner->query_skill(SS_BLIND_COMBAT))
			/ 100);
	  if (!E(owner)->query_prop(ROOM_I_INSIDE))
	    success = success * 4 / 5;
	  success += accumulate;
	  if (success > 990)
	    success = 990;
	  /* max 99% chance */
	  if (success < 10)
	    success = 10;
	  /* at least 1% chance */
	  if (success < random(1001))
	    {
		owner->catch_msg(person->query_The_name(owner) + " tries " +
				 "to prevent you from going that way, but " +
				 "you manage to break through!\n");
		person->catch_msg("You try to prevent " +
				  owner->query_the_name(person) + " from " +
				  "going " + person_exit[person] + ", but " +
				  "fail!\n");
		tell_room(E(owner),QCTNAME(person) + " tries to prevent " +
			  QTNAME(owner) + " from going " +
			  person_exit[person] + ", but fails.\n",
			  ({owner,person}));
		accumulate = success / 3;
	    }
	  else
	    {
		owner->catch_msg(person->query_The_name(owner) +
				 " prevents you from going that way!\n");
		person->catch_msg("You successfully prevent " +
				  owner->query_the_name(person) + " from " +
				  "going " + person_exit[person] + "!\n");
		tell_room(E(owner),QCTNAME(person) + " prevents " +
			  QTNAME(owner) + " from going " +
			  person_exit[person] + ".\n", ({owner,person}));
		return 1;
	    }
      }
    set_alarm(1.0,0.0,"remove_the_object","");
    return 0;
}

int
do_check(string str)
{
    if (member_array(query_verb(),m_values(person_exit)) > -1)
      return do_block(str);
    set_alarm(0.2,0.0,"attack_and_environment_check");
    set_alarm(1.5,0.0,"attack_and_environment_check");
    return 0;
}

int
attack_and_environment_check()
{
    object owner = E(TO);
    object *persons = m_indexes(person_exit);
    int i,j = sizeof(persons);
    if (!owner)
      {
	  for(i=0;i<j;i++)
	    remove_blocked_exit(persons[i], "You stop blocking the " + 
				person_exit[persons[i]] + " exit.\n");

	    /*set_alarm(0.1,0.0,"remove_blocked_exit",persons[i],
		      "You stop blocking the " + person_exit[persons[i]] + 
		      " exit.\n");*/
	  return 0;
      }
    for(i=0;i<j;i++)
      {
	  if (persons[i]->query_attack() != owner ||
	      E(persons[i]) != E(owner))
	    remove_blocked_exit(persons[i], "You stop blocking the " + 
				person_exit[persons[i]] + " exit.\n");

	    /*set_alarm(0.1,0.0,"remove_blocked_exit",persons[i],
		      "You stop blocking the " + person_exit[persons[i]] +
		      " exit.\n");*/
      }
    if (!m_sizeof(person_exit))
      return 0;
    return 1;
}

void
remove_object_now()
{
    if (m_sizeof(person_exit) == 0)
      remove_object();
}
