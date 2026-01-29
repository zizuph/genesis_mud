/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/caves/tower_start.c
 *
 *  This room was used by the Torque Wearers as a temporary residence
 *  and makeshift library. In addition to setting up very basic
 *  living quarters, they compiled texts in this place of the lore
 *  of the torque, and their progress with its implementation
 *
 *  Copyright (c) September 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/common/guild/vamp/guild.h"

/* prototypes */
public void        create_del_rimmon();
public string      exa_parchment();
public int         start(string str);
public int         stand(string str);
public void        init();


/* definitions */
#define VOID ("/d/Emerald/blackwall/delrimmon/lakeside/caves/void")


/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room
 */
public void
create_del_rimmon()
{
    string runes;

    set_short("a small, dark chamber");
    set_long("The walls of this chamber draw in extremely close on"
      + " all sides. Darkness hangs heavily in this room, struggling"
      + " to overpower the light which issues from a parchment which"
      + " has been placed on a podium before the north wall. You see"
      + " no obvious exits here.\n");

    add_item( ({ "here", "room", "chamber", "small chamber",
                 "small room", "dark chamber", "dark room",
                 "small dark room", "small dark chamber", "area" }),
        "This room serves no obvious purpose other than to house the"
      + " podium which stands against the north wall.\n");
    add_item( ({ "darkness", "dark", "light" }),
        "There is only a very small amount of light which is able to"
      + " penetrate the darkness which hangs heavily in this room."
      + " The light seems to be coming from the parchment which rests"
      + " on the podium.\n");
    add_item( ({ "podium", "black podium", "black material" }),
        "The podium is black, and composed of a material you do not"
      + " recognize. Sitting atop it is a piece of parchment which"
      + " emits the only light which shines in this room.\n");
    add_item( ({ "parchment", "piece of parchment", "paper",
                 "piece of paper" }), exa_parchment);
    add_item( ({ "wall", "walls" }),
        "The walls of this chamber are pitch black, and featureless.\n");
    add_item( ({ "north wall", "north", "northern wall",
                 "wall to the north" }),
        "A podium stands before the wall to the north.\n");
    add_item( ({ "south", "south wall", "southern wall",
                 "wall to the south" }),
        "Only blackness lies in that direction.\n");
    add_item( ({ "ceiling", "roof", "up" }),
        "The blackness above gives no indication that there is"
      + " a ceiling, or how low it might be.\n");
    add_item( ({ "sky" }),
        "There is no sky to view here.\n");

    add_cmd_item( ({ "parchment", "paper", "piece of parchment",
                     "piece of paper" }),
                  ({ "read" }), exa_parchment);
    add_cmd_item( ({ "parchment", "paper", "piece of parchment",
                     "piece of paper" }),
                  ({ "get", "take", "lift", "steal", "remove" }),
        "A strong enchantment stops your hand inches from the"
      + " parchment.\n");


    add_item(({ "circle", "runed circle", "carved circle",
        "runed circle", "tendrils", "twisting tendrils", "down",
        "floor", "ground" }),
        "A circle, about a meter in diameter, is carved into the"
      + " floor. Carved among the runes along the inside of the"
      + " circle are a set of twisting tendrils, winding about the"
      + " runes, but each finally pointing toward the center of the"
      + " circle.\n");

    add_item(({ "center", "center of circle" }), "There is nothing"
      + " at the center of the circle.\n");

    runes = "The runes are completely foreign to you.\n";
    add_item(({ "rune", "runes" }), runes);
    add_cmd_item("runes", "read", runes);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO,
        "A strange force prevents your travel.\n");
    add_prop(ROOM_S_EXIT_FROM_DESC,
        "from out of nowhere.");

    add_exit("/d/Emerald/blackwall/delrimmon/lakeside/caves/tower_entry",
             "south", 0, 1, 1);
    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
                        "southwest", "west", "northwest" }),
        "The chamber walls block your path.\n");
} /* create_del_rimmon */


/*
 * Function name:        start
 * Description  :        allow vampires to set this as their
 *                       start location
 * Arguments    :        string str - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
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

    write("As you step into the circle at the center of the room"
      + " and focus on binding your soul to the spot, its carved"
      + " lines begin to shift and move, extending up and wrapping"
      + " around you in dark, immaterial tendrils, as if to study"
      + " your form.  In only a moment, they retreat and fall back"
      + " into their pattern on the floor.\n");
    msg = " steps into the circle at the center of the room, its"
      + " carved lines begin to shift and move, extending up and"
      + " wrapping around " + this_player()->query_objective()
      + " briefly in dark, immaterial tendrils.  They quickly"
      + " retreat and fall back into their pattern on the floor.\n";
    say(({ METNAME + msg, NONMETNAME + msg, "" }));

    this_player()->set_default_start_location(
        "/d/Emerald/blackwall/delrimmon/lakeside/caves/pre_start");
    return 1;
} /* start */


/*
 * Function name:        stand
 * Description  :        allows vampires to enter the void ?
 * Arguments    :        string str - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
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

    if (!(v = find_object(VOID)) || 
        !sizeof(vs = filter(object_clones(v),
        &operator(==)(this_player()->query_real_name()) @ 
        &->query_owner())))
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
        write("Some force prevents you from entering the"
         + " circle.\n");
        return 1;
    }

    this_player()->reset_darkvision();
    
    write("As you pass into the circle, an impenetrable darkness"
      + " suddenly overcomes you.  In this pitch black, not even"
      + " your supernatural senses give you sight.\n");
    msg = " steps into the circle and is instantly swallowed up"
      + " in a flash of darkness.\n";
    tell_room(this_object(),
             ({ METNAME + msg, NONMETNAME + msg, "" }));

    return 1;
} /* stand */
 

/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();
    add_action(start, "start");
    add_action(stand, "stand");
    add_action(stand, "step");
    add_action(stand, "enter");
} /* init */


/*
 * Function name:        exa_parchment
 * Description  :        print the text of the parchment
 * Returns      :        string - the text
 */
public string
exa_parchment()
{
    string  txt = "The parchment reads as follows:\n\n";

    txt += read_file("/d/Emerald/blackwall/delrimmon/text/"
      + "tower_text.txt", 0);

    this_player()->more(txt);
    return "";

/*
    string ptxt = "The parchment reads as follows:\n\n";

    ptxt += read_file("/d/Emerald/blackwall/delrimmon/text/"
                    + "tower_text.txt", 0);

    return ptxt;
*/
} /* exa_parchment */
