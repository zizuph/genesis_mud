/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/caves/tower_shore.c
 *
 *  Here, along the western shore of the lake beneath Del Rimmon, the
 *  Crystal Tower stands.
 *
 *  Copyright (c) June 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/lakeside/caves/under_lake";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"


/* prototypes */
public void        create_del_rimmon();
public int         do_swim(string arg);
public int         enter_tower(string arg);
public void        init();


/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room
 */
public void
create_del_rimmon()
{
    set_short("on a subterranean lakeshore beside a glowing crystal"
            + " tower");
    set_long("A rocky shore climbs unevenly from the quiet waters of"
      + " a dark lake which extends a great distance"
      + " to the east, filling the basin of this vast subterranean"
      + " cavern. A tall tower rises here to nearly touch the domed"
      + " cavern roof which spreads over the area. A brilliant"
      + " illumination seems to be coming from the walls of the tower,"
      + " filling the area with light.\n");

    add_item( ({ "shore", "rocky shore", "lakeshore", "rocky lakeshore",
                 "lake shore", "rocky lake shore", "shore of the lake",
                 "uneven shore" }),
        "The rocky shore of the lake climbs unevenly from the dark"
      + " water to the east, rising to meet the walls of the cavern"
      + " which slope upward to the west.\n");
    add_item( ({ "wall", "walls", "rock wall", "rock walls",
                 "cavern wall", "cavern walls", "wall of the cavern",
                 "walls of the cavern" }),
        "Great rock walls surround the lake, sloping upward to"
      + " eventually arc over to form the domed roof of this"
      + " huge subterranean cavern.\n");
    add_item( ({ "tower", "tall tower", "glowing tower",
                 "crystal tower", "six-sided tower",
                 "tall six-sided tower" }),
        "A tall six-sided tower rises from the shores of the lake here."
      + " Though it is difficult to be sure, the entire surface of the"
      + " structure appears to be made of crystal, which is glowing"
      + " so brightly that it is difficult to stare very long at its"
      + " brilliance. A doorless opening is visible in the base of"
      + " the tower directly to the west.\n");
    add_item( ({ "light", "bright light", "illumination",
                 "brilliance", "brilliant illumination" }),
        "The tower which stands upon this shore is somehow emitting"
      + " terrific amounts of brilliant illumination which spreads"
      + " out to fill much of the cavern.\n");
    add_item( ({ "crystal", "crystals", "glowing crystals",
                 "glowing crystal", "surface of the tower",
                 "walls of the tower", "wall of the tower",
                 "tower wall", "tower walls", 
                 "surface of the structure" }),
        "The walls of the tower are completely covered with"
      + " brightly glowing crystals. The crystals are of all"
      + " shapes and sizes, and upon closer inspection have a"
      + " rather organic look to their arrangement, much like"
      + " moss on a rock, or barnacles on a shell. There are"
      + " small patches which are bare, though they are few and"
      + " far between.\n");
    add_item( ({ "patch", "patches", "bare patch", "bare patches",
                 "small patch", "small patches", "dark patch",
                 "dark patches", "patches which are bare",
                 "small patches which are bare" }),
        "In places, the surface of the tower is bare of any crystal"
      + " formations, though these are very small and few. The actual"
      + " material which lies beneath the brightly glowing outer"
      + " cover is black beyond black, almost appearing to emit"
      + " darkness rather than light. However, in direct competition"
      + " with the overwhelming number of crystals, the original"
      + " material seems almost invisible aside from very close"
      + " inspection.\n");
    add_item( ({ "opening", "doorless opening", "arch", "archway",
                 "round arch", "arched entryway", "base", "tower base",
                 "base of the tower", "west", "entryway", "entry" }),
        "Just to the west, an arched entryway leads into the base"
      + " of the tower. No door or hinges are visible, simply an"
      + " opening in the tower walls.\n");
    add_item( ({ "door", "doorway", "hinge", "hinges" }),
        "The opening in the base of the tower does not have any"
      + " door or hinges at all.\n");
    add_item( ({ "ground", "floor", "roof", "terrain" }),
        "The ground at your feet is rough and uneven stone.\n");
    add_item( ({ "stone", "rough stone", "uneven stone",
                 "rough and uneven stone" }),
        "Beneath your feet, the stone is rough and uneven, forming"
      + " a rocky shore which rises from the quiet waters to the"
      + " east.\n");

    add_cmd_item( ({ "tower", "tall tower", "glowing tower",
                     "crystal tower" }),
                  ({ "climb" }),
        "You grasp onto the crystals which cling to the sides of"
      + " the tower, and begin to make your way up its sheer sides."
      + " Getting almost to the top this way, you discover that it"
      + " does not contain any windows, and that its top is"
      + " inaccessible.\n");
    add_cmd_item( ({ "crystal", "crystals", "glowing crystals",
                     "glowing crystal" }),
                  ({ "get", "take", "remove", "steal", "pry",
                     "break", "pull" }),
        "You grasp one of the crystals which clings to the side"
      + " of the tower and attempt to pull it off. After a very"
      + " short time, you decide that there is no point to this. It"
      + " would be impossible to remove any of these crystals without"
      + " shattering them, and they seem quite too hard for even"
      + " that.\n");
    add_cmd_item( ({ "crystal", "crystals", "glowing crystals",
                     "glowing crystal" }),
                  ({ "hit", "break", "smash", "shatter",
                     "destroy" }),
        "You strike at the crystals with all of your might, and"
      + " decide that the act is futile. These crystals are harder"
      + " than any ordinary stone, and will not yield.\n");
    add_item( ({ "dark material", "black material", "actual material",
                 "original material" }),
        "The material which lies beneath the crystals is a mystery."
      + " It seems, strangely enough, to be competing with the crystals"
      + " (albeit hopelessly) in their glow. It is perfectly smooth"
      + " to the touch, and darkens your hand a bit as you touch"
      + " it, even in the presence of the bright illumination of"
      + " the crystals.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(DELRIMMON_DIR + "lakeside/caves/tower_entry", "west",
             0, 1, 1);

    set_no_exit_msg( ({ "northwest", "north", "northeast",
                        "southeast", "south", "southwest" }),
        "The walls of the cavern rise to block your movement in that"
      + " direction.\n");
    set_no_exit_msg( ({ "east" }),
        "The waters of the lake block your movement in that direction."
      + " You could certainly swim there, if you wished.\n");

    add_cavern_items();

    add_prop(ROOM_I_LIGHT, 100); /* the tower is remarkably brilliant */
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO,
        "A strange force prevents your travel.\n");

    setuid();
    seteuid(getuid());
    clone_object(DELRIMMON_DIR + "obj/obelisk")->move(this_object(), 1);
} /* create_del_rimmon */


/*
 * Function name:        do_swim
 * Description  :        allow the player to swim to the east
 * Arguemnts    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_swim(string arg)
{
    if (!strlen(arg))
    {
        NFN0("Where do you wish to swim?");
    }

    if (!parse_command(arg, ({}),
        "[in] [into] [to] [the] 'e' / 'east' / 'lake' / 'water'"))
    {
        return 0;
    }

    write("You dive into the lake, and swim to the east.\n");
    this_player()->move_living("M",
        DELRIMMON_DIR + "lakeside/caves/under_lake", 1, 0);
    tell_room(this_object(), QCTNAME(this_player())
      + " dives into the lake.\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " arrives swimming from the east.\n", this_player());

    return 1;
} /* do_swim */


/*
 * Function name:        enter_tower
 * Description  :        allow the player to enter the tower
 * Arguemnts    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
enter_tower(string arg)
{
    if (!strlen(arg))
    {
        NFN0("Enter what?");
    }

    if (!parse_command(arg, ({}),
        "[in] [into] [to] [the] [tall] [crystal] [doorless]"
      + "[round] [glowing] 'tower' / 'opening' / 'arch'"
      + " / 'archway' / 'entry' / 'entryway'"))
    {
        return 0;
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player 'west' here, using"
            + " command(). Since you are a wizard, that won't work on"
            + " you. Simply type 'w'.\n");
        return 1;
    }

    write("You walk through the opening into the tower.\n");
    this_player()->command("$west");

    return 1;
} /* enter_tower */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_swim, "swim");
    add_action(do_swim, "dive");
    add_action(enter_tower, "enter");
} /* init */
