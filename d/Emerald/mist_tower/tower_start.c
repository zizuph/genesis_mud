#include "defs.h"

inherit MIST_TOWER_BASE;

#include "/d/Emerald/common/guild/vamp/guild.h"

#include <macros.h>

#define VOID (MIST_TOWER_DIR + "void")

void
create_tower_room()
{
    string runes;
    set_em_long("Huge pieces of unnaturally smooth black rock lie clumped"
      + " in ruined heaps all around this area. Clearly, this was once the"
      + " base of some massive structure which has, through some force of"
      + " very great violence, been completely destroyed. A huge slab"
      + " of black stone lies amidst the ruin, a runed circle carved"
      + " in its fathomless black surface.\n");

    add_item( ({ "rock", "black rock", "smooth rock", "smooth black rock",
                 "unnaturally smooth rock", "unnaturally smooth black rock",
                 "pieces", "huge pieces", "pieces of rock", "rubble",
                 "ruin", "ruins" }),
        "The pieces of rock are smoother than any hand or natural process"
      + " could form, and look magically constructed. They have, however,"
      + " been blown to pieces. Every so often, a tiny arc of purple"
      + " energy licks along the surface of the rubble.\n");
    add_item( ({ "energy", "purple energy", "arc", "tiny arc",
                 "arc of purple energy", "tiny arc of purple energy" }),
        "Perhaps this is some remaining clue as to the power that caused"
      + " all the destruction. It is vivid purple - like miniature"
      + " lightning.\n");
    add_item( ({ "lightning", "miniature lightning", "purple lightning" }),
        "You feel you have seen such energy before ... but where?\n");
    add_item( ({ "structure", "massive structure" }),
        "There is little left of the structure but the ruined base.\n");
    add_item( ({ "base", "base of some massive structure",
                 "ruined base", "ruined base of the structure" }),
        "This whole area looks to have once been the base of a large"
      + " tower or some other structure. It is merely a blasted remains"
      + " now.\n");
    add_item( ({ "remains", "blasted remains" }),
        "Who or what could have caused such destruction?\n");
    add_item( ({ "tower" }),
        "There is little of the tower left. It has been blown to pieces"
      + " by some terrible power.\n");
    add_item( ({ "slab", "huge slab", "slab of stone", "stone slab",
                 "slab of black stone", "huge slab of black stone" }),
        "Strangely, the stone slab seems to have been spared the violence"
      + " that has destroyed most everything else. A runed circle is"
      + " carved in its otherwise perfect surface.\n");
    add_item( ({ "surface", "perfect surface", "black surface",
                 "fathomless surface", "fathomless black surface" }),
        "The surfaces of the broken rocks here look utterly perfect, and"
      + " formed by powerful magic.\n");

    add_item(({ "circle", "runed circle", "carved circle", "runed circle",
        "tendrils", "twisting tendrils" }),
        "A circle, about a meter in diameter, is carved into the slab.  " +
        "Carved among the runes along the inside of the circle are a set of " +
	"twisting tendrils, winding about the runes, but each finally " +
        "pointing toward the center of the circle. Somehow, this feature " +
        "seems to have completely escaped the destruction that surrounds " +
        "it\n");

    add_item(({ "center", "center of circle" }), "There is nothing at the " +
        "center of the circle.\n");

    add_item(({ "wall", "walls", "dark wall", "dark walls", "tower wall",
                "tower walls", "featureless wall", "featureless walls", 
                "inside wall", "inside walls", "stone wall", "stone walls" }),
        "They have been, for the most part, destroyed.\n");

    add_item(({ "ceiling", "dark ceiling", "tower ceiling",
                "featureless ceiling", "stone ceiling"}),
        "There is no ceiling left. All has collapsed to ruin.\n");

    add_item(({ "floor", "dark floor", "tower floor", "featureless floor",
                "stone floor", "ground", }),
        "The floor, where unbroken, is littered with ruin and rubble from"
      + " the destroyed tower.\n");

    runes = "The runes are completely foreign to you.\n";
    add_item(({ "rune", "runes" }), runes);
    add_cmd_item("runes", "read", runes);

    add_exit("prominence01", "south");
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
