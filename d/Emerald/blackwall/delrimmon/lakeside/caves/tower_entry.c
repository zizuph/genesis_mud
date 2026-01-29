/*
 *  /d/Emerald/blackwall/del_rimmon/lakeside/caves/tower_entry.c
 *
 *  This is a room at the base of the Crystal Tower. Poor Raeldu
 *  made his final pilgrimage here after the debacle with the
 *  Darkling Forces, and died, final sentinel of the Torque-Wearers
 *  keeping silent vigil forever.
 *
 *  Copyright (c) August 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";

#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void        create_del_rimmon();
public int         check_exit();
public int         get_torque(string arg);
public int         do_climb(string arg);
public int         tell_climb();
public void        init();
public void        reset_room();
public void        notice_surroundings(object ob);
public void        enter_inv(object ob, object from);

/* definitions */
#define        ALREADY_NOTICED     "_vamp_noticed_dr_tower"




/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room
 */
public void
create_del_rimmon()
{
    set_short("within the confines of a dark stone tower");
    set_long("You stand within the confines of a dark stone tower."
      + " Smooth black walls run upwards from this, the base of the"
      + " building, to a high ceiling which is dimly visible above."
      + " A break in the wall to the left reveals a tightly spiraling"
      + " staircase leading upwards. To the east, an archway opens"
      + " onto a cramped hallway which leads out of the tower.\n");

    add_item( ({ "sky" }),
        "The sky is not visible here.\n");
    add_item( ({ "tower", "stone tower", "dark tower",
                 "dark stone tower", "crystal tower", "building" }),
        "This would seem to be the base of the tower, whose bulk"
      + " rises around you in all directions.\n");
    add_item( ({ "base", "tower base", "base of the tower" }),
        "There do not appear to be any levels lower than this in"
      + " the tower, and it is clear that the archway to the east"
      + " leads out of the building. This is indeed the base of"
      + " the tower.\n");
    add_item( ({ "wall", "walls", "smooth wall", "black wall",
                 "smooth walls", "black walls", "smooth black wall",
                 "smooth black walls", "tower wall", "tower walls",
                 "walls of the tower", "wall of the tower",
                 "inside wall", "inside walls", "inside tower wall",
                 "inside tower walls", "stone wall", "stone walls" }),
        "The inside tower wall forms a plain, smooth circle around"
      + " the room. Its dark, perfect surface nearly gives the"
      + " appearance of empty space. At certain intervals, brightly"
      + " glowing crystals interrupt the otherwise flawless surface"
      + " of the stone.\n");
    add_item( ({ "surface", "dark surface", "perfect surface",
                 "flawless surface", "stone", "interval", "intervals",
                 "certain intervals" }),
        "The surface of the walls is as perfect as polished glass,"
      + " and it is almost unimaginable that they could have been"
      + " created by anything other than magic. Spaced unevenly,"
      + " and disturbing the otherwise flawless surface, are brightly"
      + " glowing crystals which are somehow affixed to the stone."
      + " You notice an absence of crystals on the wall to the north.\n");
    add_item( ({ "north", "wall to the north", "walls to the north",
                 "north wall", "absence", "absence of crystals" }),
        "Upon closer inspection, you notice that there is in fact a"
      + " narrow passageway travelling north into the wall of the"
      + " tower.\n");
    add_item( ({ "crystal", "crystals", "glowing crystal",
                 "glowing crystals", "brightly glowing crystal",
                 "brightly glowing crystals" }),
        "The crystals emit a fierce glow which seems to be competing"
      + " with a darkness which wishes to hang heavily in this"
      + " tower. The crystals themselves look alien in this place,"
      + " and clearly seem to have been added by some force other than"
      + " that which formed the walls. They look exactly like the"
      + " crystals which cover the outer surface of the tower, yet"
      + " it appears that here, inside, they have been unable to"
      + " cluster as thickly.\n");
    add_item( ({ "light", "glow", "illumination" }),
        "The light in this tower is dim, and appears to be coming from"
      + " the crystals which cling to the walls. Though one is able to"
      + " see in this room, it is clear that the presence of darkness"
      + " is very great as well, and were it not for the crystals, that"
      + " the darkness would be complete.\n");
    add_item( ({ "ceiling", "up", "above", "high ceiling",
                 "stone ceiling", "roof" }),
        "Like the surrounding wall, the dark, stone ceiling appears"
      + " to be completely flat and unblemished, giving it an almost"
      + " unreal aspect, as if one could reach through it into dark,"
      + " empty space. Unlike the walls, no crystals are attached"
      + " to the ceiling.\n");
    add_item( ({ "stair", "stairs", "staircase", "spiraling staircase",
                 "tightly spiraling staircase", "spiral stairs",
                 "spiral staircase", "steps", "stairway",
                 "spiral stairway", "break", "break in the wall",
                 "break in the wall to the left",
                 "left wall", "wall to the left" }),
        "At one end of this chamber, a tightly spiraling staircase"
      + " winds its way up into the recesses of the stone ceiling.\n");
    add_item( ({ "hallway", "east", "cramped hallway", "arch",
                 "archway", "opening", "archway to the east",
                 "eastern archway" }),
        "An archway opens onto a cramped hallway which leads out"
      + " of the tower to the east. The height of the hallway"
      + " suggests that it was not built for men or elves, but"
      + " rather for a slighter race of beings.\n");
    add_item( ({ "passage", "passageway", "north", "north passageway",
                 "passageway to the north", "narrow passageway",
                 "northern passageway" }),
        "You are not able to clearly see much of the passageway which"
      + " leads out of this chamber to the north. It is marked most"
      + " clearly by the absence of glowing crystals which forms its"
      + " rough dimensions. There is a forboding darkness in that"
      + " direction, as if some strange force is present there.\n");
    add_item( ({ "outside", "cave", "out" }),
        "The outside of the tower is not visible from here.\n");
    add_item( ({ "down", "floor", "ground" }),
        "Like the surrounding wall, the dark, stone floor appears to"
      + " be perfectly smooth and unblemished, giving the strange"
      + " impression of endless, void depth.\n");

    add_cmd_item( ({ "crystal", "crystals", "glowing crystal", 
                     "glowing crystals", "brightly glowing crystal",
                     "brightly glowing crystals" }),
                  ({ "take", "pull", "move", "get", "remove" }),
        "You pull on one of the nearby crystals briefly. It is quite"
      + " clear that there is no way for you to remove it.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO,
        "A strange force somehow prevents your travel.\n");

    add_exit(DELRIMMON_DIR + "lakeside/caves/tower_start", "north",
             check_exit, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/caves/torque_room", "up",
             tell_climb, 5, 1);
    add_exit(DELRIMMON_DIR + "lakeside/caves/tower_shore", "east");

    set_no_exit_msg( ({ "northwest", "west", "southwest", "south",
                        "southeast", "northeast" }),
        "The walls of the tower rise to block your movement.\n");

    setuid();
    seteuid(getuid());

    reset_room();
} /* create_del_rimmon */


/*
 * Function name:        check_exit
 * Description  :        only players who posess a torque may pass
 *                       this way
 * Returns      :        1 - cannot pass, 0 - allowed to pass
 */
public int
check_exit()
{
    if (present("ctower_torque", this_player()))
    {
        return 0;
    }

    write("A strange magical force prevents you from passing that"
        + " way.\n");
    return 1;
} /* check_exit */


/*
 * Function name:        get_torque
 * Description  :        provide the player with feedback if they
 *                       try to get the torque from Raeldu's corpse
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
get_torque(string arg)
{
    if (!strlen(arg))
    {
        return 0; /* the mudlib can handle this one */
    }

    if (!parse_command(arg, ({}),
        "[the] [luminous] [fair-stone] [crystal] 'torque'"
      + " [from] [corpse] [skeleton]"))
    {
        return 0; /* mudlib takes it */
    }

    write("The torque is somehow fused to the surface of the skull,"
        + " and cannot be removed from the skeleton.\n");
    return 1;
} /* get_torque */


/*
 * Function name:        do_climb
 * Description:          allow players to climb the steps
 * Arguments:            string arg - what the player typed
 * Returns:              1 - success, 0 - failure
 */
public int
do_climb(string arg)
{
    if (!strlen(arg))
    {
        NFN0("What do you wish to " + QVB + "?\n");
    }

    if (!parse_command(arg, ({}),
        "[up] [the] [tightly] [spiral] [spiraling]"
      + " 'stair' / 'stairs' / 'staircase' / 'step' / 'steps'"
      + " / 'stairway'"))
    {
        return 0; /* player used bad syntax */
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player 'up' here using"
          + " command. Since you are a wizard, that will not work."
          + " Simply type 'up' yourself.\n");
        return 1;
    }

    this_player()->command("$up");
    return 1;
} /* do_climb */


/*
 * Function name:        tell_climb
 * Description  :        provide the player with a description
 *                       of his climbing up the stairs
 * Returns      :        int 0
 */
public int
tell_climb()
{
    write("You ascend the stairway to reach a higher level of the"
        + " tower.\n");
    return 0;
} /* tell_climb */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(get_torque, "get");
    add_action(get_torque, "remove");
    add_action(get_torque, "pry");
    add_action(do_climb, "climb");
    add_action(do_climb, "ascend");
} /* init */



/*
 * Function name:        reset_room
 * Description  :        clone the corpse of Borgil into this room
 */
public void
reset_room()
{
    object corpse,
           torque;

    if (!present("corpse_of_raeldu"))
    {
        corpse = clone_object(DELRIMMON_DIR
          + "obj/raeldu")->move(this_object());
    }

    if (!present("_raeldu_torque"))
    {
        torque = clone_object(
            "/d/Emerald/torque/unique_torques/raeldu_torque");
        torque->set_no_show(1);
        torque->move(this_object());
    }
} /* reset_room */


/*
 * Function name:        notice_surroundings
 * Description  :        tell vampire players that this place
 *                       reminds them of their home tower
 * Arguments    :        ob: The player object
 */
public void
notice_surroundings(object ob)
{
    ob->catch_msg("You notice distinct similarities between this"
                + " place and your Coven home. There is an eerie"
                + " sense of connection here to things buried deep"
                + " within you ... memories that you do not have"
                + " the ability to recall.\n");

    return;
} /* notice_surroundings */


/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 *                Specifically, we want to tell vampires that this place
 *                is very much like their home.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (ob->query_prop(ALREADY_NOTICED))
    {
        return;
    }

    if (ob->query_vampire())
    {
        set_alarm(2.0, 0.0, &notice_surroundings(ob));
        ob->add_prop(ALREADY_NOTICED, 1);
    }

    return;
} /* enter_inv */
