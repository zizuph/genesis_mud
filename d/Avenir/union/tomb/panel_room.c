/*
 * Panel room
 *
 * This is the second puzzle in the area:
 *   The player must push the panels in the correct order
 *   to open the passage to the east. The order in which the
 *   panels need to be pressed is random, and can be discerned
 *   by the pattern of dots on the floor. In order to see the
 *   pattern of dots, the player must have a lit torch in the brazier
 *   to give enough light. There is also a resolve_task() needed
 *   in order to make out the pattern of dots. A torch can be
 *   found in the area, at ~Avenir/union/tomb/entry_passage2
 *
 *       Cirion, May 28 1996
 */
#pragma strict_types
#include "defs.h"

inherit "/std/room";
inherit "/d/Avenir/inherit/quest";

#include <tasks.h>
#include <macros.h>
#include <ss_types.h>

#define SAW_PATTERN	"_Avenir_quest_saw_ppattern"

public string *num;
public object brazier;
public int alarm, tried, door, *solution = ({ 0, 0, 0, 0, 0, 0, 0, 0 });


public void
close_door(void)
{
    tell_room(TO, "The door slowly closes.\n");
    tell_room(PASSAGE, "You hear a deep rumble, and the stone slab to "+
	"the west slowly closes with a loud crash.\n");
    tell_room(HOLE, "You hear a low rumble from the east.\n");

    door = 0;
    remove_exit("east");
    PASSAGE->remove_exit("west");
}

public void
open_door(void)
{
    tell_room(TO, "You hear a deep rumble far below you, and "+
	"a large slab of stone in the east wall raises to "+
	"reveal an opening into the darkness.\n");
    tell_room(PASSAGE, "With a low rumble, the large stone slab "+
	"to the west rises, opening into a large, circular room.\n");

    door = 1;
    add_exit(PASSAGE, "east");
    PASSAGE->add_exit(PANEL, "west");
}

public void
reset_room(void)
{
    /* Don't reset while there are players here */
    if (sizeof(filter(all_inventory(), query_interactive)))
	return;

    /* All this hackneyed bit does is pick a random symbol for a certain number,
     * so that, say, 5 can be either ::. or ..... or :.:, etc. */
    num  = ({ ".",
	one_of_list(({"..",":"})),
	one_of_list(({"...",":.",".:"})),
	one_of_list(({"....","::",":..",".:.","..:"})),
	one_of_list(({"::.",":.:",".::","...:",".:.."})),
	one_of_list(({":::","......","...:.",":..:","::..",":.:."})),
	one_of_list(({":.:..",":::.",":.::",".......",":...:"})),
	one_of_list(({"::::",":....:","..::..",":.:.:","::....","........"})),
	one_of_list(({"::::.",".::::",":......:","::..:.","...:.:."})),
	one_of_list(({":::::",":.:.:..",".:.:.:.","::......","...::..."})) });

    solution = ({ random(10), random(10), random(10), random(10),
	random(10), random(10), random(10), random(10) });

    tell_room(TO, "The floor swirls with a rush of colour for a moment, "+
	"and something seems different.\n");

    alarm = 0;
    tried = 0;

    if (door)
        close_door();
}

public void
leave_inv(object to, object from)
{
    ::leave_inv(to, from);
    if (!alarm)
	alarm = set_alarm(10.0, 0.0, reset_room);
}

public string
query_solution(void)
{
    string str = "";
    int i = -1, size = sizeof(solution);

    while(++i < size)
	str += num[solution[i]] + "  ";
    return str;
}

public int
solution_sum(void)
{
    int sum, i = -1, size = sizeof(solution);

    while(++i < size)
	sum += solution[i] + 1;
    return sum;
}

public void
create_room(void)
{
    set_short("circular room");
    set_long("This is a wide, perfectly circular room. Sitting "+
	"in the center of the room is a tall sconce, and inlaid "+
	"into the floor around the sconce are strange patterns of "+
	"dots.@@brazier_inv@@ The wall is tall and smooth, and "+
	"evenly spaced all along it are ten square tiles made "+
	"from some shiny black stone, in stark contrast to the "+
	"smooth limestone of the wall. The tiles are spread evenly "+
	"around the wall, except for a space in the west side, "+
	"where there is a square hole leading into a small, dim "+
	"tunnel.@@see_door@@\n");

    add_item(({"floor","ground"}), "The floor is of smooth marble, "+
	"unadorned except for the area around the sconce, which "+
	"seems to be decorated with patterns of tiny dots.\n");
    add_item(({"dots","pattern","patterns","dot"}), "@@see_dots@@");
    add_item(({"panel","panels","tile","tiles"}),
	"There are ten perfectly square black tiles spread along the "+
	"wall at even intervals, all appearing to be identical.\n");
    add_item(({"first panel","second panel","third panel",
	    "fourth panel","fifth panel","sixth panel","eighth panel",
	    "ninth panel","tenth panel"}),
	"It looks just like all the rest, shiny black stone. It appears "+
	"to be somewhat loose.\n");
    add_item(({"tunnel","hole"}), "The hole in the west wall is "+
	"perfectly square, made from smooth blocks of grey stone. "+
	"The hole leads into a small tunnel, just large enough for "+
	"one person to fit into.\n");

    add_cmd_item(({"panel","tile","first panel","second panel",
	    "third panel","fourth panel","fifth panel","sixth panel",
	    "seventh panel","eighth panel","ninth panel","tenth panel"}),
	({"rattle","shake","pull","lift","wiggle","jiggle"}),
	"It moves slightly. You might be able to push it into the wall.\n");

    set_noshow_obvious(1);
    add_exit(HOLE, "west", "@@go_west@@");

    brazier = clone_object(TOBJ + "brazier");
    brazier->move(TO);

    reset_room();
}

public string
see_door(void)
{
    if (!door) return "";
    return " A large stone slab has opened up in the east side "+
	"of the chamber, leading into a gloomy passage.";
}

/* If there is a torch in the sconce, show it in the room desc */
public string
brazier_inv(void)
{
    object *inv = filter(all_inventory(brazier),
	&->query_prop(OBJ_I_HAS_FIRE));

    if (!sizeof(inv)) return "";
    return " Sitting in the brazier is a flickering "+
	inv[0]->query_name() + ".";
}

public string
see_dots(void)
{
    say(QCTNAME(TP) +" stares hard at the pattern on the floor.\n");

    if (!strlen(brazier_inv()))
    {
	return "There seems to be some sort of pattern etched "+
	    "into the floor around the sconce, but the light "+
	    "there is too dim to make them out.\n";
    }

    if (TP->query_mana() < 40)
    {
	return "You stare at the pattern on the floor, but your "+
	    "mind is so tired you cannot make any sense out of it.\n";
    }

    if (TP->resolve_task(TASK_ROUTINE,
	    ({ SKILL_AVG, SS_AWARENESS, TS_INT, SKILL_END })) <= 0 &&
	TP->query_prop(SAW_PATTERN) != solution_sum())
    {
	TP->add_mana(-40);
	return "You stare hard at the pattern on the floor, "+
	    "but the flickering shadows hurt your eyes and "+
	    "you cannot make out the pattern.\n";
    }

    TP->add_prop(SAW_PATTERN, solution_sum());

    return "The pattern around the base of the sconce is etched into "+
	"the stone surface of the floor, illuminated gently by the "+
	"flickering light from the sconce:\n"+
	break_string(query_solution(), 30, 15) +"\n";
}

public int
go_west(void)
{
    object hole = find_object(HOLE);

    if (hole && sizeof(filter(all_inventory(hole), query_interactive)))
    {
	write("There is someone already in the tunnel, and "+
	    "you cannot both fit in there together.\n");
        tell_room(HOLE, "Someone seems to be trying to enter "+
	    "the hole from the east, but there is not enough room "+
	    "for two people in the tunnel.\n");
	return 1;
    }

    write("You climb into the hole.\n");
    say(QCTNAME(TP) +" climbs into the hole.\n");
    return 0;
}

public int
push(string str)
{
    int num;
    string wnum, verb = query_verb();

    NF(CAP(verb) +" what?\n");
    if (!strlen(str))
        return 0;

    NF(CAP(verb) +" which panel?\n");
    if (parse_command(str, ({}), "[the] 'panel' / 'panels'"))
        return 0;

    /* Allow for 'push the second panel' or 'push panel 2' */
    if (!parse_command(str, ({}),
	    "[the] 'panel' / 'tile' [number] %d", num) &&
	!parse_command(str, ({}), "[the] %w 'panel' / 'tile'", wnum))
	return 0;

    if (strlen(wnum))
        num = LANG_ORDW(wnum);  // translate 'third' -> 3

    if (num > 10)
    {
	write("There are only ten panels.\n");
        return 1;
    }

    if (num < 1)
    {
	write("You do not see that panel.\n");
        return 1;
    }

    if (door)
    {
	write("It does not budge.\n");
	return 1;
    }

    write("You "+ verb +" the "+ LANG_WORD(num) +" panel inwards slightly.\n");
    say(QCTNAME(TP) +" pushes the "+ LANG_WORD(num) +" panel inwards.\n");

    /* Pushed the wrong panel in the sequence. Start over. */
    if (--num != solution[tried++])
    {
	DEBUG("Wrong panel: pushed " + (num+1) + ", should have been " +
	    solution[tried-1]);
        /* If the (wrong) panel we pushed happens the be the first panel
         * in the correct sequence, allow that to happen */
        if (num == solution[0])
            tried = 1;
        else
            tried = 0;
    }

    if (tried >= sizeof(solution) &&
	TP->query_prop(SAW_PATTERN) == solution_sum())
    {
	open_door();
	tried = 0;
    }

    return 1;
}

public void
init(void)
{
    ::init();

    add_action(push, "push");
    add_action(push, "press");
    add_action(push, "move");
}
