#include "defs.h";

inherit "/d/Emerald/std/room";

#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include <subloc.h>
#include <ss_types.h>

#define WATER_SUBL "_water_subloc"

object carriage;

void
create_emerald_room()
{
    string str;
    object obelisk;

    set_short("Ceral Island Ferry Dock");
    set_em_long("A dock extends out from the shore into Lake Telberin. " +
        "Ferries dock here regularly to transport passengers to and " +
        "from Ceral Island, where passage can be booked to other " +
        "lands.\n@@subl_desc@@");

    add_item(({ "lake", "lake telberin" }),
        "From here at its western edge, scenic Lake Telberin opens up " +
        "before you.  Just to the north lies Telberin Island and its great " +
        "city.\n");

    add_item(({ "telberin", "city", "island", "telberin island",
	        "telberin city" }),
        "The capital city of Emerald, Telberin, lies just to your " +
        "north.  Even from here, the tall spires of the royal palace " +
        "dominates the view among the myriad buildings which cover " +
        "seemingly every inch of the island.\n");

    add_item(({ "buildings" }),
        "From here you can make out a number of homes that follow the " +
        "edge of the island around.  Beyond, you can make out quite a " +
        "number of different structures, including the magnificent " +
        "royal palace.\n");

    add_item(({ "palace", "royal palace" }),
        "The royal palace of Telberin is a magnificent sight, even from " +
        "a distance.  Its tall spires reach toward the clouds, and its " +
        "walls, brilliant white, seem to give off a glistening light of " +
        "their own.\n");

    add_item(({ "water", "clear water", "lake water" }),
        "The water is extremely clear, allowing you to see the rocky bottom " +
        "of the lake, even a great distance out.\n");

    add_item(({ "dock", "docks", "ship dock", "ferry dock", "boat dock",
        "wooden dock" }),
        "A wooden dock extends out from the shore into the lake.  The ferry " +
        "from Ceral Island stops there.\n");

    str = "By order of the King, travel through the lands of Emerald " +
          "is not permitted.  Those seeking to visit the wedding " +
          "chapel may take the carriage which stops here.\n";

    add_item(({ "sign", "prominent sign" }), str);
    add_cmd_item(({ "sign", "prominent sign" }), "read", str);

    add_subloc(WATER_SUBL, this_object());

    obelisk = clone_object("/d/Emerald/telberin/mainland/obj/obelisk");
    obelisk->set_no_show_composite(1);
    obelisk->move(this_object(), WATER_SUBL);

    reset_room(); 
}

public string
subl_desc()
{
    if (!this_player()->query_subloc())
    {
	return "A prominent sign is posted here.\n";
    }

    return "From your position here in the lake, you notice a dark, " +
        "pointed stone jutting up from the surface of the water.\n";
}

void
reset_room()
{
    if (!objectp(carriage))
    {
        reset_euid();
        carriage = clone_object(TELBERIN_DIR + "mainland/chapel_carriage/carriage");
        carriage->start_carriage();
    }
}

public int
query_carriage_stop(object carriage)
{
    return 1;
}

public mixed
subloc_access(string subloc, object ob, string access, object for_obj)
{
    if (access == SUBLOC_ACCESS_MANIP)
    {
        return "It is too far away.\n";
    }

    return 1;
}

public string
show_subloc(string subloc, object ob, object for_obj)
{
    object *livings = FILTER_LIVE(subinventory(subloc));
    int i;
    string *names;

    if (sizeof(livings))
    {
        if ((i = member_array(for_obj, livings)) >= 0)
        {
            names = ({ "You" });
            livings = exclude_array(livings, i, i);
        }
        else
        {
            names = ({});
        }

        livings = FILTER_CAN_SEE(livings, for_obj);
        names += map(livings, &->query_the_name(for_obj));
        return capitalize(COMPOSITE_WORDS(names)) +
            (((sizeof(names) == 1) && (names[0] != "You")) ? 
            " is " : " are ") + "wading in the lake.\n";
    }

    return "";
}

public int
into_water()
{
    string msg;

    if (this_player()->query_subloc() == WATER_SUBL)
    {
	write("You are already wading in the water.\n");
	return 1;
    }

    this_player()->move(this_object(), WATER_SUBL);
    write("You wade out into the cold water.\n");
    msg = " wades out into the lake.\n";
    say(({ METNAME + msg, NONMETNAME + msg, "" }));
    return 1;
}

public int
out_of_water()
{
    string msg;

    if (this_player()->query_subloc() != WATER_SUBL)
    {
	write("You aren't in the water, though.\n");
	return 1;
    }

    this_player()->move(this_object());
    write("You wade back to the shore.\n");
    msg = " wades onto the shore.\n";
    say(({ METNAME + msg, NONMETNAME + msg, "" }));
    return 1;
}

public varargs int
wade(string str)
{
    if (!strlen(str))
    {
	notify_fail(capitalize(query_verb()) + " where?\n");
	return 0;
    }

    if (parse_command(str, ({}), "[out] [into] / [to] / [in] [the] " +
        "'water' / 'lake'"))
    {
        return into_water();
    }

    if (parse_command(str, ({}), "[out] [of] [from] [the] 'water' / 'lake'") ||
	parse_command(str, ({}), "[back] [to] / [onto] [the] 'shore' / 'land'"))
    {
	return out_of_water();
    }

    notify_fail(capitalize(query_verb()) + " where?\n");
    return 0;
}

public int
enter(string str)
{
    if (strlen(str) &&
        parse_command(str, ({}), "[the] 'water' / 'lake'"))
    {
	return into_water();
    }

    notify_fail(capitalize(query_verb()) + " what?\n");
    return 0;
}

public int
leave(string str)
{
    if (strlen(str) &&
        parse_command(str, ({}), "[the] 'water' / 'lake'"))
    {
	return out_of_water();
    }

    notify_fail(capitalize(query_verb()) + " what?\n");
    return 0;
}

public int
swim(string str)
{
    return 0;
}

public void
init()
{
    ::init();

    add_action(wade, "wade");
    add_action(wade, "walk");
    add_action(wade, "go");
    add_action(enter, "enter");
    add_action(leave, "leave");
    add_action(leave, "exit");
    add_action(swim, "swim");
}
