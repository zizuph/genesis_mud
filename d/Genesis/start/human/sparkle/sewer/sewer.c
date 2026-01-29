inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <sewer.h>

public int dip(string what);
public void init_reaction(object who);


/*
 ************************************************************
 * Remember to check:
 *
 * 1) The sequence of events: leave_inv -> enter_inv
 *    ie: what happens to messages printed to the 'to' room when called
 *    from leave_inv _AFTER_ calling the masked fun?
 *    Do they appear before the player is shown to arrive? Should do but
 *    varify.
 *
 * 2) What happens to livings when they LD and return from LD
 *    and ensure call to masked enter_xxx and leave_xxx are
 *    called at the appropriate times.
 */

public void
create_room()
{
	::create_room();
	set_short("Base sewer room");
	set_long("A sewer");

	add_prop(ROOM_I_SEWER, 1);
	remove_prop(ROOM_I_LIGHT);
}

public void
init()
{
	::init();

//  add_action("smell","smell");
	add_action("dip", "dip");
//	add_action("wade", "wade");
//	add_action("jump", "jump");
//	add_action("enter", "enter");
//	add_action("exit", "exit");
}

public void
enter_inv(object ob, object from)
{
    int alrm;

//  filter out non-living and players returning from LD
//	if(!ob->query_living() || !interactive(ob))
//		return;

	::enter_inv(ob, from);
//	object livings[] = FILTER_PLAYERS(all_inventory(this_object()));

	if(!from->query_prop(ROOM_I_SEWER))
	{
		// Give player time stamp for entry into sewer
		ob->add_prop(LIVE_I_SEWER_TIME_STAMP, time());
	}

	alrm = set_alarm(2.0, 0.0, &init_reaction(ob));
}

public void
leave_inv(object ob, object to)
{
	// filter out non-living and players LDing
//	if(!ob->query_living() || !interactive(ob))
//		return;

	::leave_inv(ob, to);

	if(!to->query_prop(ROOM_I_SEWER))
	{
		ob->remove_prop(LIVE_I_SEWER_TIME_STAMP);
		ob->catch_msg("Mmmmmmm... Fresh air!\n");
	}
	say(QCTNAME(ob) + " takes a deep savouring breath " +
		"of air.\n");
}

public void
init_reaction(object who)
{
    int con, reac;

	con = who->query_stat(SS_CON);
	reac = (time() - who->query_prop(LIVE_I_SEWER_TIME_STAMP)) / 10800;
	if (reac > 4)
		reac = 4;
//  who->command("$emote " + SEWER_ENTER_EMOTE[reac]);

    who->catch_msg("Auuuughhh! The stench in here is...\n");
	who->command("$"+SEWER_ENTER_COMMAND[reac]);
    return;
}

public int
dip(string what)
{
	int c;
	mixed dipped;
    object *wep, soiled;

	if(!what) return 0;

	c = sscanf(what, "%s in sewer", dipped);
	if (c != 1)
		return notify_fail("Dip what?\n");

	/*
	 * Add possibility to dip wielded weapons in too...
	 */
   	notify_fail("Dip what in sewer?\n");
	if ((what != "finger in sewer") && (what != "hand in sewer") &&
		(what != "finger in sewage") && (what != "hand in sweage") &&
		(what != "finger in canal") && (what != "hand in canal"))
    {
        if (sizeof(wep = this_player()->query_weapon(-1)) < 1)
            return 0;

        if (member_array(dipped, wep[0]->parse_command_id_list()) < 0)
        {
            if (sizeof(wep) == 2)
                if (member_array(dipped, wep[1]->parse_command_id_list()) < 0);
            return 0;
        }
    }    

	if ((dipped == "hand" || dipped == "finger") && this_player()->query_race() !=
		"goblin")
	{
		write("You turn your head and grimace as you dip your " + dipped +
			" into the scumy sewage.\n");
	    say(QCTNAME(this_player()) + " grimaces as " +
			this_player()->query_pronoun() + " dips " + 
			this_player()->query_possessive() + " " + dipped + 
    		" into the scumy sewer.\n");
	}
	else
	{
		write("You dip your " + dipped + " into the scumy sewage.\n");
	    say(QCTNAME(this_player()) + " dips " + 
			this_player()->query_possessive() + " " + dipped + 
    		" into the scumy sewer.\n");
	}
	write("You feel your " + dipped + " dragged " +
		query_prop(ROOM_S_SEWER_DIRECTION) + " by the flow.\n");

	if (dipped == "hand" || dipped == "finger")
	{
		if (member_array(SUBLOC_SOILED, this_player()->query_sublocs()) < 0)
		{
			seteuid(getuid(this_object()));
			soiled = clone_object(SEWER_OBJ + "soiled.c");
			soiled->set_body_part((dipped == "hand" ? 1 : 2));
			soiled->move(this_player());
		}
		else
		{
			soiled = this_player()->query_subloc_obj(SUBLOC_SOILED);
			if (dipped == "hand" && soiled->get_body_part() == "finger")
				soiled->set_body_part(1);
		}
    }
	return 1;
}

