/* created by Aridor 12/21/93 */

#pragma no_clone
#pragma save_binary

#include "../local.h"

inherit "/std/object";

#include TIME_FLOW
#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#define NUM_DIFF_TROOP_PATHS        5
                                   /* the number of different troop
        			      paths ( files troop* ) */
#define MAX_TROOPS                  14
                                   /* the maximum number of troops that
				      should be created */

mapping troops = ([]);
string color = "blue";
mapping troop_command = ([]);
mapping troop_paths = ([]);
int troop_count = 0;
int this_attack_team_strength = 6;
object my_dragon;

void
create_object()
{
    set_name("kitiara's troop master");
    set_long("This is Kitiara's master to control the blue dragon army.\n");
}

static nomask void
set_color(string new_color)
{
    color = new_color;
}


static nomask void
make_a_team()
{
    int i;
    object comm;
    object dummy;
    object leader;
    int num,val;
    if (!my_dragon)
      return;
    leader = clone_object(LIV + "aurak");
    if (leader->query_prop(OBJ_I_COLORABLE))
      leader->set_color(color);
    leader->move(E(my_dragon));
    num = random(8) + 4;
    for(i = 0; i < num; i++)
      {
	  val = 10 + this_attack_team_strength + random(15) - random(15);
	  if (val < 6)
	    dummy = clone_object(LIV + "baaz");
	  else if (val < 12)
	    dummy = clone_object(LIV + "kapak");
	  else if (val < 16)
	    dummy = clone_object(LIV + "bozak");
	  else
	    dummy = clone_object(LIV + "sivak");
	  /*clone_object(LIV + "team_attack_shadow")->shadow_me(dummy);*/
	  if (dummy->query_prop(OBJ_I_COLORABLE))
	    dummy->set_color(color);
          dummy->set_stats(({170 + val, 170 + val, 170 + val, 
              170 + val, 170 + val, 170 + val}));
	  dummy->move(E(my_dragon));
	  dummy->set_leader(leader);
	  leader->team_join(dummy);
      }
    comm = clone_object(OBJ + "troop_command");
    comm->set_the_troop(leader);
    comm->set_commander(TO);
    num = ((m_sizeof(troop_command)) % NUM_DIFF_TROOP_PATHS) + 1;
    troops += ([ (m_sizeof(troop_command)):comm ]);
    troop_paths += ([ (m_sizeof(troop_command)):num ]);
    troop_command += ([ (m_sizeof(troop_command)):1 ]);
    
}

/* returns: 0 couldn't give out the command
 *          1 gave out the command to the troop
 */
static nomask int
do_a_command(int troop_no, string *comm)
{
    int ret;
    if (troop_no >= m_sizeof(troop_command))
      return 0;
    ret = (troops[troop_no]->receive_command(comm));
    if (ret == -1)
      troops = m_delete(troops,troop_no);
    return ret;
}


static nomask int
get_whose_command()
{
    int i;
    for(i = 0;i<m_sizeof(troop_command); i++)
      {
	  troop_count++;
	  if (troop_count >= m_sizeof(troop_command))
	    troop_count = 0;
	  if (m_sizeof(troop_command))
	    return troop_count;
      }
    set_alarm(6000.0,0.0,"prepare_flee_troops_gone");
}

static nomask string
get_the_command(int who)
{
    return read_file(LIV + "troop" + (troop_paths[who]),
		     troop_command[who], 1);
}


static nomask void
start_the_strategy()
{
    /* check if the last command was successfully performed
     * and no fights are pending
     *only then issue the next command
     *-get the next command from the list and issue it*/

    int who;
    mixed what;
    int ret;
    
    who = get_whose_command();
    what = get_the_command(who);
    if (troop_command[who] == 0)
      {
	  
	  set_alarm(100.0,0.0,"start_the_strategy");
	  return;
      }
    else
      troop_command[who]++;
    /*dump_mapping(troop_command);
      dump_mapping(troops);
      write("A: " + who + "," + what + "\n");*/
    if (what == "CREATE_TROOP\n")
      {
	  if (m_sizeof(troop_paths) < MAX_TROOPS + 1)
	    {
		make_a_team();
		set_alarm(itof(40+random(20)),0.0,"start_the_strategy");
	    }
      }
    else if (what == "MAKE_AGGRESSIVE\n")
      troops[who]->make_troop_aggressive();
    else if (what == "CAPTURE_GUNTHAR\n")
      troops[who]->capture_prisoner("gunthar");
    else if (what == "RELEASE_GUNTHAR\n")
      {
	  troops[who]->release_prisoner();
	  troops[who]->command("dismount");
	  INTERRUPT_PERIOD("kitiara","return home victoriously");
      }
    else if (atoi(what) != 0)
      troop_command[who] += (atoi(what) - 1);
    else 
      {
	  ret = do_a_command(who, what);
	  if (ret == -1)
	    troop_command[who] = 0;
	  if (ret == 0)
	    troop_command[who]--;
      }
    if (ret >= 0)
      {
	  if (troop_paths[who] == 1) /* means it's an intruder team */
	    set_alarm(40.0,0.0,"start_the_strategy");
	  else
	    set_alarm(100.0,0.0,"start_the_strategy");
      }
    else
      set_alarm(6000.0,0.0,"prepare_flee_troops_gone");
}

/* return 0 if the attack wasn't started, 1 if it was */
/* Called from common/flow/kitiara */
nomask void
my_strategy(object dragon, int strength)
{
    my_dragon = dragon;
    this_attack_team_strength = strength;

    set_alarm(1.0,0.0,"make_a_team");
    set_alarm(2.0,0.0,"start_the_strategy");
}

static nomask void
prepare_flee_troops_gone()
{
    INTERRUPT_PERIOD("kitiara","flee home");
}

