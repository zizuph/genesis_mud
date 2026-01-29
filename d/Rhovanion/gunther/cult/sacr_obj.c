/* the sacrifice object */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"
#define NEW_MAY_COME 0
#define STARTED		1

object *organs;	/* all the organs to be sacrificed */
object *riters;	/* players performing the rite. riters[0] is the leader */
int sacrifice_sum;	/* sum of favor points accumulated so far */
int sacrifice_state;
status leader_has_knife;
status leader_has_thongs;


is_organ(object ob)
{
	string *nam;
	nam = ob->query_names();
	if(nam[sizeof(nam) - 1] == "organ")
		return 1;
	return 0;
}

create_object()
{
	set_short("@@short_desc");
	set_name("_cult_sacrifice_object"); /* not possible to exa it, hopefully */
	set_long("You aren't supposed to see this text, please mail the wizard"
		+" Gunther about it :)\n");
		
	add_prop(OBJ_I_NO_PICKUP,1);
	add_prop(OBJ_I_WEIGHT, 0);
	add_prop(OBJ_I_VOLUME, 0);
	
	add_prop(OBJ_S_WIZINFO, "This object handles the rite of sacrifice for"
		+" the Cult of Melkor.\n");
	sacrifice_state = NEW_MAY_COME;
	sacrifice_sum = 0;
	leader_has_knife = 0;
	leader_has_thongs = 0;
	organs = ({ });
	riters = ({ });
}

tell_what_is_going_on(string *strs)
{
	int n;
	write(str[0]);
	tell_room(ENV(TO), str[1], riters);
	riters->catch_msg(str[2]);
}

public void
add_sacrifice(object me, object *org_arg)
{
	set_this_player(me);
	if(sacrifice_state != NEW_MAY_COME)
		write("The rite of sacrifice has progressed too far for you to"
			+" join in.\n");
	if(!sizeof(riters))
	{
		write("You initiate the rite of sacrifice.\n");
		say(QCTNAME(TP) + " brings out " + HIS(TP) + " brazier and starts to "
			+"chant eerily.\n");
		if(present("_cult_knife", all_inventory(TP))) leader_has_knife = 1;
		if(present("_cult_thongs", all_inventory(TP))) leader_has_thongs = 1;
	}
	else
		tell_what_is_going_on(({
			"You join in the rite of sacrifice.\n",
			QCTNAME(TP) + " joins in the chant.\n",
			QCTNAME(TP) + " joins in the sacrifice.\n"}));
	me->add_prop(LIVE_S_SOULEXTRA, "chanting eerily");
	
	/* paralyze me here ! */
	
	organs += org_arg;
	riters += ({ me });
}

goto_next_stage(object me)
{
	int n;
	set_this_player(me);
	/* check that TP was leading the sacrifice */
	if(me != riters[0]))
	{
		write("You are not leading the sacrifice.\n");
		return;
	}
	if(!sizeof(organs))
	{
		tell_what_is_going_on(({
			"There is nothing to sacrifice! You abort the ritual.\n",
			"The chanting suddenly stops.\n",
			QCTNAME(TP) + " aborts the ritual as there is nothing to sacrifice.\n" }));
		end_of_sacrifice();
		return;
	}
	
	sacrifice_state = STARTED;
   
   tell_what_is_going_on(({"You continue with the rite of sacrifice.\n",
   	QCTNAME(TP) + " changes " + HIS(TP) + " tone of voice"
		+" slightly" + ((sizeof(riters) > 1)?" and the others quickly follow suit":"")
		+".\n",
		QCTNAME(TP) + " continues with the sacrifice.\n"}));

	TP->change_prop(LIVE_S_SOULEXTRA, "chanting hollowly");
	riters->change_prop(LIVE_S_SOULEXTRA, "chanting hollowly");
	set_alarm(2.0, 2.0, sacrifice_real);
}

sacrifice_real()
{
	int n;
	set_this_player(riters[0]);
	if(!sizeof(organs))
	{  
		tell_what_is_going_on(({
			"There is nothing more to sacrifice, so you conclude the rite.\n",
			"The chanting stops.\n",
			QCTNAME(TP) + " concludes the rite.\n"}));
		remove_alarm(sacrifice_real); /* this the way to do it ? */
		end_of_sacrifice();
		return;
	}
	/* ok, now we sacrifice *hehe* */
	tell_what_is_going_on(({
		