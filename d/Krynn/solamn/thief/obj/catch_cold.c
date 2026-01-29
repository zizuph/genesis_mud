/* This is a catching cough!
 * Anyone how is infected will cough once in a while
 * There is a chance anyone else in the room is
 * infected...
 * Effect: lowers all stats a little. 2-8 points.
 */

inherit "/std/object";

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

int alrm;
int *stat_mod;

void
create_object()
{
    seteuid(getuid(TO));
    set_no_show();
    set_name("cold");
    add_name("cough");
    stat_mod = ({-random(7)-2,-random(7)-2,-random(7)-2,
		 -random(7)-2,-random(7)-2,-random(7)-2});
    add_prop(OBJ_M_NO_DROP,1);
}

void
enter_env(object dest, object old)
{
    int i;
    if (interactive(dest) || dest->query_npc())
      {
	  dest->command("cough .");
	  dest->catch_msg("It seems you have caught a cold.\n");
	  if (dest->query_wiz_level())
	    dest->catch_msg("Since you are a wizard you're immune to it. :)\n");
	  tell_room(E(dest),QCTNAME(dest) + " seems to have caught a cold.\n",dest);

	  /* newbie check */
	  if (dest->query_avg_stat() < 30)
	    stat_mod = ({0,0,0,0,0,0});

	  /* lower all stats a little while sick */
	  for(i=0;i<5;i++)
	    dest->set_stat_extra(i, stat_mod[i]);

	  set_alarm(itof(random(40) + 1),0.0,"do_cough");
	  alrm = set_alarm(2000.0,0.0,"remove_object");
      }
    ::enter_inv(dest, old);
}

void
leave_env(object from, object to)
{
    set_alarm(1.0,0.0,"remove_object");
    ::leave_env(from, to);
}

void
do_cough()
{
    object who = E(TO);
    object *whos;
    int i;
    if (!interactive(who) && !who->query_npc())
      {
	  leave_env(who, who);
	  return;
      }
    for(i=-1;i<random(3);i++)
      who->command(({"cough vigorously","sneeze",
		       "cough pitifully","sneeze",
		       "cough noisily"})[random(5)]);
    if (who && !who->query_wiz_level())
      {
	  whos = FILTER_LIVE(all_inventory(E(who)));
	  for(i=0;i<sizeof(whos);i++)
	    if ((interactive(whos[i]) || whos[i]->query_npc()) &&
		!present("cough",whos[i]) && /* !random(10) && not any more, instead:*/
		(whos[i]->query_max_hp() / whos[i]->query_hp()) > random(10))
	      clone_object(MASTER)->move(whos[i],1);
      }
    if (random(3))
      i = random(40);
    else
      i = random(250);
    set_alarm(itof(i + 1),0.0,"do_cough");
}

void
remove_object()
{
    mixed the_alarm = get_alarm(alrm);
    int i;
    object who = E(TO);
    if (!the_alarm && (interactive(who) || who->query_npc()))
      {
	  for(i=0;i<5;i++)
	    who->set_stat_extra(i, -stat_mod[i]);
	  tell_room(E(who),QCTNAME(who) + " seems to feel better now.\n",who);
	  who->catch_msg("You feel much better.\n");
      }
    ::remove_object();
}

string
query_auto_load()
{
    mixed *the_alarm = get_alarm(alrm);
    return MASTER + ":" + ftoi(the_alarm[2]);
}

void
init_arg(string str)
{
    set_alarm(5.0,0.0,"set_remove_time",atoi(str));
}

void
set_remove_time(int i)
{
    alrm = set_alarm(itof(i),0.0,"remove_object");
}

