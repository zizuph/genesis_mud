/*
 * other/houses/k-04.c
 *
 * By Skippern 20(c)01
 *
 * The barracks. A place where the guards can rest.
 */
#include "../../defs.h"

//inherit "/d/Gondor/std/delay_room";
inherit DOL_STD + "inside.c";

#include <macros.h>

static int     Made;
static string  Making;

void
last_msg()
{
    write("Before completing, you test the beds by leting a coin " +
	  "bounce on the beds.\n");
    say(QCTNAME(this_player()) + " drops a coin on the beds and " +
	"watches it bounce back up to " + this_player()->query_possessive() +
	" hand.\n");
}

void
make_msg()
{
    write("You stretch the sheets as best you can.\n");
    say(QCTNAME(this_player()) + " stretches the sheets as best " +
	this_player()->query_pronoun() + " can.\n");
    set_alarm(20.0, 0.0, last_msg());
}

public mixed
begin_make()
{
    if (!Made)
    {
	if (!strlen(Making))
	{
	    Making = this_player()->query_name();

//	    set_alarm(5.0, 0.0, make_msg() );

	    say(QCTNAME(this_player()) + " starts making the beds.\n");
	    return "You start making the beds.\n";
	}
	notify_fail(Making + " is allready making the beds.\n");
    }
    else
    {
	notify_fail("The beds are allready made.\n");
    }
    return 0;
}

public string
stop_make()
{
    object token = present("I_do_quest_token.c", this_player());

    Made = 1;
    Making = "";

    if (objectp(token)) token->set_part(2);

    say(QCTNAME(this_player()) + " is finnished making the beds.\n");
    return "You have finished making the beds, what a job.\n";
}

string
bed_desc()
{
    string r = "Bed descriptions. ";

    if (Made == 0)
	r += "Beds are messy.";
    else r += "Beds are tidy.";

    r += "\n";

    return r;
}

/*
 * Function name:    create_inside()
 * Description  :    Creates the inside room.
 */
public void
create_inside()
{
    set_short("inside the barracks");
    set_long("This is the main hall of the marine barracks. The room " +
	     "is devided by four raws of beds, all with a small chest " +
	     "by the foot end. This serves as the home for the soldiers " +
	     "when they'r not on mission. The barracks seems empty, " +
	     "are not even traces of intendants or officers.\n");

    add_item("beds", &bed_desc() );
    add_delay_cmd_item("beds", "make", "making the beds", 15, begin_make,
		       stop_make);

    add_exit(DOL_OTHER + "pier/k-03", "north", 0, 1);
    add_exit(DOL_COMMON + "streets/k-05", "south", 0, 1);

    reset_room();
}

void
reset_room()
{
    Made = 0;
}

/*
 * Function name:       leave_inv
 * Description  :       catch any polishers leaving ... they can't
 *                      do it on their own, but they might be trans'd
 * Arguments    :       object ob -- the departing object
 *                      object dest -- its destination
 */
public void
leave_inv(object ob, object dest)
{
    if (Making == ob->query_name())
    {
        Making = "";
    }
    ::leave_inv(ob, dest);
} /* leave_inv */

/*
 * Function name:       stop_delay_cmd
 * Description  :       mask parent so that if player does "stop",
 *                      we clear Polishing
 * Arguments    :       mixed arg -- if string, player did "stop"
 *                                -- if object, time ran out or
 *                                    called from leave_inv().
 * Returns      :       0 -- stop is always allowed
 */
public int
stop_delay_cmd(mixed arg)
{
    object      tp;

    if (!objectp(arg))
    {
        /* called from paralyze object when player did "stop" */
        tp = ENV(previous_object());
        if (tp->query_name() == Making)
        {
            Making = "";
        }
    }
    return ::stop_delay_cmd(arg);
} /* stop_delay_cmd */
