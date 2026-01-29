/*
 * party_tool.c
 *
 * With this you can start up a party, or be teleported to or from
 * the party. The real stuff is handled by /d/Shire/open/party/party_room.c,
 * this is just something to carry around.
 */
inherit "/std/object";

#include <ss_types.h>
#include <stdproperties.h>
#include "party.h"

#define START    1
#define MOVE     2
#define RETURN   3

static string return_to_room;
static int condition;
static int last_party_held;
static int alarm_id = 0;

void test_carried();

void
create_object()
{
    seteuid(getuid());
    set_name(({ "partytool", "tool", PARTY_TOOL_ID }));
    set_short("@@my_short_desc");
    set_pshort("@@my_pshort_desc");
    set_long("@@my_long_desc");
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_M_NO_DROP, "@@drop_call");
    condition = START;
}

string
my_short_desc()
{
    if (condition == START || condition == MOVE)
	return "partytool (tm)";
    return 0;
}

string
my_pshort_desc()
{
    if (condition == START || condition == MOVE)
	return "partytools (tm)";
    return 0;
}

string
my_long_desc()
{
    switch (condition)
    {
    case START:
	return break_string("It's the PartyTool (tm). With this you "
                +"can create a party... Just type 'start party'.\n", 70);
    case MOVE:
	return break_string("Type 'party' to join the party. You "
                +"still have " + get_alarm(alarm_id)[2] + " seconds "
                +"left before the PartyTool (tm) self-destructs.\n", 70);
    case RETURN:
	return 0;
    }
} 

void
init()
{
    ::init();
    switch (condition)
    {
    case START:
	add_action("do_start", "start");
	break;
    case MOVE:
	add_action("do_party", "party");
	break;
    }
}

int
drop_call()
{
    set_alarm(2.0, 0.0, &test_carried());
    return 1;
}

void
test_carried()
{
    if (!interactive(environment()))
    {
        tell_room(environment(), "The " + my_short_desc()
		+ " crumbles to dust.\n");
	remove_object();
    }
}

int
do_start(string str)
{
    int next_party;

    seteuid(getuid());

    if (!((this_player()->query_wiz_level() ||
        (this_player()->test_bit("Shire", 0, 0) == 1 &&
         this_player()->query_base_stat(SS_LAYMAN) > 70))))
    {
	notify_fail("Only highlevel Hin Warriors or wizards can start a "
		  + "party!\n");
	return 0;
    }

    if (str != "party")
    {
	notify_fail("Please use 'start party' to avoid any confusion.\n");
	return 0;
    }

    /*
     * The PARTY_LOG_PATH file is updated when a new party is thrown,
     * so its filetime indicates when the last party was held.
     */
    next_party = file_time(PARTY_LOG_PATH) + HOURS_BETWEEN_PARTIES * 3600;

    /* Wizards may throw parties anytime */
    if (this_player()->query_wiz_level() || time() >= next_party)
    {
	PARTY_ROOM->start_the_party();
    }
    else
    {
	write("Sorry, a party has been held not too long ago.\n"
	    + "A new party can be thrown in about "
            + (((next_party - time()) / 3600) + 1) + " hours.\n");
    }
    return 1;
}

int
do_party(string str)
{
    if (str)
    {
	notify_fail("Please use 'party' without any arguments to avoid any "
		   +"confusion.\n");
	return 0;
    }
    write("You said it: Partytime!\n");
    remove_alarm(alarm_id);
    this_player()->move_living("off to party", PARTY_ROOM);
    return 1;
}

/*
 * set_selfdestruct_timer(), set_return_to_room() and query_return_to_room()
 * are called by the partyroom.
 */

void
set_selfdestruct_timer(int mins)
{
    if (alarm_id)
	return;

    condition = MOVE;
    set_alarm(itof(mins * 60), 0.0, &remove_object());
}

void
set_return_to_room(string str)
{
    return_to_room = str;
    condition = RETURN;
    remove_name("partytool");
    remove_name("tool");
}

string
query_return_to_room()
{
    return return_to_room;
}
