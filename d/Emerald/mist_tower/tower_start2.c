#include "defs.h"

inherit MIST_TOWER_BASE;

#include "/d/Emerald/common/guild/vamp/guild.h"

#include <macros.h>

#define VOID (MIST_TOWER_DIR + "void")

int blah = 0;

void
create_tower_room()
{
    string runes;
    set_em_long("The dark, unadorned, nearly featureless walls and ceiling " +
        "give a slightly disorienting sense of boundless, empty space within " +
        "this small area.  Only the runed circle carved deep into the floor " +
        "at the center of the room and the narrow exit to the stairway give " +
        "the room any true sense of form and dimension.\n");

    add_item(({ "circle", "runed circle", "carved circle", "runed circle",
        "tendrils", "twisting tendrils" }),
        "A circle, about a meter in diameter, is carved into the floor.  " +
        "Carved among the runes along the inside of the circle are a set of " +
	"twisting tendrils, winding about the runes, but each finally " +
        "pointing toward the center of the circle.\n");

    add_item(({ "center", "center of circle" }), "There is nothing at the " +
        "center of the circle.\n");

    runes = "The runes are completely foreign to you.\n";
    add_item(({ "rune", "runes" }), runes);
    add_cmd_item("runes", "read", runes);

    add_exit("tower_library", "down");
}

public int
start(string str)
{
    string msg;

    if (str != "here")
    {
        return 0;
    }

    if (!IS_MEMBER(this_player()) && !this_player()->query_wiz_level())
    {
        return 0;
    }

    write("As you step into the circle at the center of the room and focus " +
        "on binding your soul to the spot, its carved lines begin to " +
	"shift and move, extending up and wrapping around you in dark, " +
        "immaterial tendrils, as if to study your form.  In only a moment, " +
        "they retreat and fall back into their pattern on the floor.\n");
    msg = " steps into the circle at the center of the room, its carved " +
        "lines begin to shift and move, extending up and wrapping around " +
        this_player()->query_objective() + " briefly in dark, immaterial " +
        "tendrils.  They quickly retreat and fall back into their pattern on " +
        "the floor.\n";
    say(({ METNAME + msg, NONMETNAME + msg, "" }));

    /* Players don't actually start here.  There is a staging area, of sorts */
    this_player()->set_default_start_location(MIST_TOWER_DIR + "pre_start");
    return 1;
}

public void open()
{
  blah = 1;
}

public int
stand(string str)
{
    object v, *vs;
    string msg;

    if (!strlen(str) || !parse_command(str, ({}),
        "[in] / [into] / [on] / [onto] [the] 'circle'"))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
	return 0;
    }

    if (!IS_MEMBER(this_player()))
    {
        write("You step into the circle for a moment.\n");
        msg = " steps into the circle for a moment.\n";
        say(({ METNAME + msg, NONMETNAME + msg, "" }));
	return 1;
    }

    if (blah)
    {
        write("Some force prevents you from entering the circle.\n");
        return 1;        
    }

    if (!(v = find_object(VOID)) || !sizeof(vs = filter(object_clones(v),
        &operator(==)(this_player()->query_real_name()) @ &->query_owner())))
    {
        setuid();
        seteuid(getuid());
	v = clone_object(VOID);
    }
    else
    {
        v = vs[0];
    }

    if (this_player()->move_living("M", v, 1, 1))
    {
        write("Some force prevents you from entering the circle.\n");
	return 1;
    }

    this_player()->reset_darkvision();
    
    write("As you pass into the circle, an impenetrable darkness suddenly " +
        "overcomes you.  In this pitch black, not even your supernatural " +
        "senses give you sight.\n");
    msg = " steps into the circle and is instantly swallowed up in a " +
        "flash of darkness.\n";
    tell_room(this_object(), ({ METNAME + msg, NONMETNAME + msg, "" }));

    return 1;
}

public void
init()
{
    ::init();
    add_action(start, "start");
    add_action(stand, "stand");
    add_action(stand, "step");
    add_action(stand, "enter");
}
