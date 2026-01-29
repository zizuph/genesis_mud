/* gdareobj.c: For gladiator gdare command: Serpine, 5/1/95.
 *     Based on Dunstable's riddle object for the Tricksters.
 */
inherit "/std/object";
#include "defs.h"

object gdrawer;
int alarm_id;
object *crossers;

void
set_gdrawer(object ob)
{
    gdrawer = ob;
    return;
}

int
blow_away()
{
    tell_room(ENV(TO), "A passing gust of wind blows away the line "+
      "that had been drawn in the dust.\n");
    remove_alarm(alarm_id);
    remove_object();
    return 1;
}

int
do_cross(string str)
{
    if(TP == gdrawer)
    {
	write("Cross your own line? Why?\n");
	return 1;
    }

    if(member_array(TP, crossers) > -1)
    {
	write("But you already have crossed that line!\n");
	return 1;
    }

    if(!present(gdrawer, E(TO)))
    {
	write("It feels somewhat silly to step over the undefended line.\n");
	say(QCTNAME(TP) + " steps over the line for no apparent reason.\n");
	return 1;
    }

    TP->catch_msg("You bravely step over the line drawn by " +
      QCTNAME(gdrawer) + ", confident in your ability to deal with "+
      "anything "+ PRONOUN(gdrawer) + " might be willing to try.\n");
    say(QCTNAME(TP) + " bravely steps over the line, confidently facing " +
      QCTNAME(gdrawer) + ", the one who drew it.\n", ({gdrawer, TP}));
    gdrawer->catch_msg(QCTNAME(TP) + " foolishly steps across your line!\n"+
      "How could " + PRONOUN(TP) + " dare?!\n" +
      "Are you going to stand for this insult?\n");
    crossers = (crossers + ({ TP }));
    return 1;
}

void
create_object()
{
    set_short("line in the dust");
    set_name("line");
    add_name("dust");
    add_name("_glad_dare_obj_");
    set_long("A line slices through the dust, daring anyone to cross it.\n");

    add_prop(OBJ_M_NO_GET, 1);

    alarm_id = set_alarm(60.0, 0.0, "blow_away");

    crossers = ({});
}

void
init()
{
    ::init();
    add_action("do_cross", "cross");
    add_action("do_cross", "step");
}
