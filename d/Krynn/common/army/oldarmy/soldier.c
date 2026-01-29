/* Inherit this file into any npc in addition to the normal npc stuff to
 * allow it to be controlled by the platoon.c object.
 */

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>

int do_block = 0;
int do_call_for_help = 0;
mapping block = ([]);
object platoon;

/* called from the platoon object */
public void
setup_soldier_for_platoon(object plat)
{
    platoon = plat;
}

/* call this from init_living()! */
public void
init_block()
{
    add_action("check_all_cmds","",1);
}

static void
start_guard()
{
    do_block = 1;
    do_call_for_help = 1;
    block = mkmapping(E(TO)->query_exit_rooms(),
		      E(TO)->query_exit_cmds());
    
}

static void
end_guard()
{
    do_block = 0;
    do_call_for_help = 0;
}

/* called from the platoon object */
public void
receive_command(string cmd, string what)
{
    switch(cmd)
      {
	case "do_pack": 
	  TO->command("out");
	  TO->command("pack tent");
	  break;
	case "do_unpack":
	  TO->command("set up tent");
	  TO->command("enter tent");
	  break;
	case "do_guard":
	  TO->command("out");
	  start_guard();
	  break;
	case "do_march":
	  TO->command("out");
	  end_guard();
	  TO->command(what);
	  break;
	default:
	  TO->command(cmd);
      }
}

static int
check_all_cmds(string str)
{
    mixed comes_from = TP->query_prop(LIVE_O_LAST_ROOM);

    if (!do_block) /* no block? don't prevent anything then. */
      return 0;

    if (!comes_from || !objectp(comes_from))
      return 0;

    comes_from = file_name(comes_from);
    if (query_verb() == block[comes_from])
      return 0;
    if (member_array(query_verb(), m_values(block)) < 0)
      return 0;

    if (TP->query_average_stat() < 20) /* newbies can always pass */
      return 0;

    /* try to block the player from going anywhere except back */
    if (random(TP->query_stat(SS_STR)) > random(TO->query_stat(SS_STR)) + 20)
      {
	  TO->command("emote tries in vain to prevent you from going into " +
		      "that direction.");
	  return 0; /* fail */
      }
    TO->command("emote prevents you from going into that direction!");
    return 1;
}

static void
call_others_to_help(object against_who)
{
    platoon->get_others_to_help(TO,against_who);
}
