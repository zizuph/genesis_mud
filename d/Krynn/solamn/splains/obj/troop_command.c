/* created by Aridor 12/21/93 */

/* Navarre Feb 3rd 2007, added checks for who and leader to avoid runtime error */

inherit "/std/object";

#include "../local.h"
#include <ss_types.h>
#include <wa_types.h>
#include "/sys/stdproperties.h"
#include <macros.h>

object *members = ({ });
object commander;
object leader;
object prisoner;

void
create_object()
{
    set_name("troop_command_object");
    set_long("This is the communication object of the troops.\n");
}

/* void set_the_troop (object lead)
 *
 * Make my platoon from the team of
 * the leader object.*/
void
set_the_troop(object lead)
{
  if (lead)
    {
      members = lead->query_team_others();
      leader = lead;
    }
}

/* void set_commander(object lead)
 * make the leader object commander in the platoon
 */
void
set_commander(object lead)
{
  if (lead)
    commander = lead;
}

/* void find_a_new_leader()
 *
 * if there is not leader in the platoon
 * find the highest one from the members
 * and make him leader */
void
find_a_new_leader()
{
  int i;
  object new;
  members -= ({ 0 });
  if (leader || (sizeof(members) == 0))
    return;
  new = members[0];
  for (i = 1; i<sizeof(members); i++)
    if (members[i]->query_base_stat(SS_DIS) > new->query_base_stat(SS_DIS))
      new = members[i];
  leader = new;
  members -= ({ new });
  for (i = 0; i<sizeof(members); i++)
    {
      members[i]->set_leader(leader);
      leader->team_join(members[i]);
    }
}

/* int receive_command(string *comm)
 * let the leader do the command comm
 * or a set of commands
 * if one member of the troop is fighting
 * don't perform the command.
 * returns: 0 if failed to do the command
 *          1 if command was successful
 *         -1 if the troop don't exist anymore
 */
int
receive_command(mixed comm)
{
  int i;
  string my_com;
  if (!leader)
    find_a_new_leader();
  if (leader)
    {
      if (leader->query_enemy())
	if (P(leader->query_enemy(), E(leader)))
	  return 0;
      for (i = 0; i<sizeof(members); i++)
	if (members[i]->query_enemy())
	  if (P(members[i]->query_enemy(), E(members[i])))
	    return 0;
      my_com = (explode(comm,"\n"))[0];
      leader->command(my_com);
      if (comm[0..3] == "kill")
	leader->command(my_com);
      if (prisoner && (comm[0..3] != "kill"))
	prisoner->command(my_com);
      if (comm[0..3] == "kill" || comm[0..4] == "enter")
	for(i = 0; i<sizeof(members); i++)
	  {
	    members[i]->command(my_com);
	    if (comm[0..3] == "kill")
	      members[i]->command(my_com);
	  }
      return 1;
    }
  return -1;
}


make_troop_aggressive()
{
  int i;
  leader->set_aggressive(1);
  for(i = 0; i<sizeof(members); i++)
    members[i]->set_aggressive(1);
}


capture_prisoner(string who)
{
  if(!who || !leader)
  {
      return;
  }
  prisoner = present(who,E(leader));
  if (!prisoner)
    return;
  tell_room(E(leader),QCTNAME(prisoner) + " is overwhelmed by the draconians, gagged and bound.\n");
  prisoner->capture_me();
}


release_prisoner()
{
  if (!prisoner)
    return;
  tell_room(E(leader),QCTNAME(prisoner) + " is turned over to the highlord.\n");
  prisoner = 0;
}
