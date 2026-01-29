/*
 *  /d/Sparkle/guilds/new_merc/rooms/mill_roof.c
 *
 *  This is the roof of the mill in the Mercenary Camp. Players have to be
 *  fairly clever to find their way up here.
 *
 *  Created May 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;

#include <filter_funs.h>   /* for FILTER_LIVE         */
#include <macros.h>        /* for QCTNAME             */
#include <time.h>          /* for TIME2FORMAT         */


/* Prototypes */
public void        create_merc_room();
public void        init();
public int         try_climb(string arg);
public void        land_player(object player, string edge);
public int         do_jump(string arg);


/* 
 * Function name:        create_merc_room
 * Descrption   :        set up the room with area presets
 */
public void
create_merc_room()
{
    set_short("atop the roof of a sawmill in the Mercenary Camp");
    set_long("You've found a way to get yourself up onto the roof of"
      + " the mill. From here you have an excellent view of nearly all"
      + " parts of the camp. The waterwheel of the mill blocks your"
      + " view to the north, however.\n");

    try_item( ({ "areas", "various areas", "parts", "part",
                 "part of the camp", "parts of the camp" }),
        "You'll have to be more specific.\n");
    try_item( ({ "view", "excellent view" }),
        "You can see the entire camp from up here!\n");
    try_item( ({ "roof", "roof of the mill", "here", "area" }),
        "The roof of the mill provides fairly secure footing thanks to"
      + " the thousands of cedar shingles which cover its surface. The"
      + " edges of the roof look onto various areas of the Mercenary"
      + " camp.\n");
    try_item( ({ "surface", "surface of the roof" }),
        "Shingles, shingles everywhere ...\n");
    try_item( ({ "shingle", "shingles", "cedar shingle",
                 "cedar shingles" }),
        "They crunch softly as you tread on them, but seem to flex"
      + " rather than to break. A few are quite thickly covered in moss.\n");
    try_item( ({ "moss" }),
        "The moss is both thick and springy, coating many of the"
      + " shingles up here.\n");
    try_item( ({ "thick moss" }),
        "And springy!\n");
    try_item( ({ "springy moss" }),
        "And thick!\n");
    try_item( ({ "cedar" }),
        "It is a very common wood in these parts.\n");
    try_item( ({ "parts", "these parts" }),
       "You know ... here ... in the lands of Sparkle.\n");
    try_item( ({ "mill", "old mill", "sawmill", "saw mill",
                 "old saw mill", "old sawmill" }),
        "You can't see much of the mill other than its roof from"
      + " up here.\n");
    try_item( ({ "wheel", "waterwheel", "water wheel", "turning wheel",
                 "turning water wheel", "turning waterwheel" }),
        "Only the top of the waterwheel is visible from here. It extends"
      + " above the north edge of the roof.\n");
    try_item( ({ "top" }),
        "The top? The top of what?\n");
    try_item( ({ "top of the wheel", "top of the water wheel",
                 "top of the waterwheel" }),
        "It turns endlessly just north of the roof, its troughs spilling"
      + " water as they reach the apex and begin their downward"
      + " journey.\n");
    try_item( ({ "apex" }),
        "You know, the point at which the top of the waterwheel has been"
      + " reached.\n");
    try_item( ({ "trough", "troughs", "trough of the waterwheel",
                 "trough of the water wheel" }),
        "The troughs are what catch the water at the bottom of the"
      + " wheel, which in turn forces the wheel to rotate and power"
      + " the mill.\n");
    try_item( ({ "bottom of the wheel", "bottom of the water wheel",
                 "bottom of the waterwheel" }),
        "It isn't visible from up here.\n");
    try_item( ({ "edge" }),
        "Edge? Edge of what?\n");
    try_item( ({ "edge of the roof", "roof edge", "edges",
                 "edges of the roof", "edge of roof",
                 "edges of roof" }),
        "Which edge do you want to look at - north, south, east, or"
      + " west?\n");
    try_item( ({ "north edge", "northern edge", "north edge of the roof",
                 "northern edge of the roof" }),
        "The northern edge of the roof faces on to the turning"
      + " waterwheel, whose massive frame blocks visibility in that"
      + " direction.\n");
    try_item( ({ "frame", "massive frame" }),
        "The waterwheel is big. Darn big.\n");
    try_item( ({ "east edge", "eastern edge", "east edge of the roof",
                 "eastern edge of the roof" }),
        "The eastern edge of the roof overlooks the river which flows"
      + " diagonally toward the bridge.\n");
    try_item( ({ "south edge", "southern edge", "south edge of the roof",
                "southern edge of the roof" }),
        "The southern edge of the roof overlooks the point at which"
      + " the path from the lodge divides to either enter the mill or"
      + " travel west through the guarded gate into the training"
      + " yard.\n");
    try_item( ({ "west edge", "western edge", "west edge of the roof",
                 "western edge of the roof" }),
        "The western edge of the roof overlooks the perimeter of the"
      + " training yard.\n");
    try_item( ({ "perimeter", "perimeter of the training yard",
                 "perimeter of the yard" }),
        "The training yard is quite huge and extends out away from the"
      + " mill to the west. Just beneath the roof of the mill, a large"
      + " pile of lumber has been stacked against the wall.\n");
    try_item( ({ "wall", "walls", "wall of the mill",
                 "walls of the mill" }),
        "They aren't really something you can see from up here too"
      + " well.\n");
    try_item( ({ "lumber", "pile", "lumber pile", "pile of lumber",
                 "large pile of lumber", "large pile" }),
        "The lumber pile is quite big, closing the distance between"
      + " the roof and the ground quite conveniently ... hmmm ...\n");
    try_item( ({ "ground", "below", "ground below" }),
        "It's a loooooong way down. Eeeks.\n");
    try_item( ({ "gate", "guarded gate" }),
        "The gate to the training yard is guarded quite heavily. You"
      + " see mercenaries coming and going occasionally, being admitted"
      + " by the guards.\n");
    try_item( ({ "yard", "training yard", "mercenary training yard" }),
        "The training yard is just to the west of the mill you are"
      + " standing on.\n");

    add_cmd_item( ({ "waterwheel", "wheel", "water wheel", "trough",
                     "troughs" }),
                  ({ "grab", "hold", "ride" }),
        "The waterwheel is not within reach. It doesn't look like"
      + " you could jump onto it without killing yourself.\n");

    add_delay_cmd_item(
        ({ "roof", "mill roof", "roof of the mill" }),
        "search",
        "searching around the roof",
        10,
        "You begin searching around the roof, looking for anything"
      + " that might be worth finding.\n",
        "Hmmm ... there really isn't much up here. You do notice that"
      + " the edges of the roof overhang different parts of the camp."
      + " The south edge overhangs the path back to the lodge, and"
      + " the west part overhangs the training yard, which is off-"
      + "limits to non-mercenaries.\n");
     
    add_river_view();
    add_bridge_view();
    add_outdoor_view();
    add_lodge_view();

    set_no_exit_msg( ({ "north", "northeast", "east", "southeast", "south",
                        "southwest", "west", "northwest" }),
        "You pause at the edge of the roof, and decide to think it"
      + " over a bit.\n");
    set_no_exit_msg( ({ "down" }),
        "Got any ideas how?\n");

    setuid();
    seteuid(getuid());
} /* create_merc_room */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_jump, "jump");
    add_action(do_jump, "drop");
    add_action(try_climb, "climb");
} /* init */


/*
 * Function name:        try_climb
 * Description  :        let players try to climb stuff
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
try_climb(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if (arg == "up" || arg == "down")
    {
        notify_fail("Climb " + arg + " what?\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[down] [on] [to] [onto] [the] [huge] [lumber] 'pile' /"
      + " 'lumber' [pile]"))
    {
        notify_fail("The lumber pile isn't within reach from up here."
          + " There is no way to climb to it that you can see. You"
          + " might be able to drop down onto it though, if you were"
          + " feeling lucky.\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[down] [over] [the] [saw] [mill] [sawmill] 'wall' / 'walls'"
      + " [of] [the] [saw] [mill] [sawmill]"))
    {
        notify_fail("The edges of the roof overhang the walls of the"
          + " mill. You don't have any way to climb down them.\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[down] [to] [the] [training] 'ground' / 'camp' / 'yard'"))
    {
        notify_fail("A nice idea, but how? It's not like there is"
          + " a ladder propped against the edge of the roof for your"
          + " climbing pleasure.\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[up] [down] [the] [water] 'wheel' / 'waterwheel'"))
    {
        notify_fail("It is a few feet from the north edge of the roof."
          + " Trying to jump and catch hold of it would be to risk"
          + " life and limb. Not an option.\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[up] [down] [from] [the] [old] 'mill' / 'roof'"))
    {
        notify_fail("There just doesn't seem to be any way to climb down"
          + " from the roof. It might be possible to jump off of one of"
          + " the sides.\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[up] [the] 'trough' / 'troughs' [of] [the] [waterwheel]"))
    {
        notify_fail("The troughs are not within reach, and jumping to"
          + " grab hold of one would almost certainly result in a"
          + " broken neck.\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[down] [to] [the] 'ground'"))
    {
        notify_fail("How would you do that? There aren't any ladders"
          + " conveniently propped against the side of the roof.\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[down] [over] [the] [north] [northern] [south] [southern]"
      + " [east] [eastern] [west] [western] 'edge' [of] [the] [roof]"))
    {
        notify_fail("There really aren't any good handholds on the"
          + " edge of the roof. You'd probably have to simply jump"
          + " if you wanted to get down from here.\n");
        return 0;
    }

    notify_fail("You don't seem to be able to climb that.\n");
    return 0;
} /* try_climb */


/*
 * Function name:        land_player
 * Description  :        have the player land in the right place after
 *                       letting go of the wheel.
 * Arguments    :        object player - the player in question,
 *                       string edge - which edge did they jump from?
 */
public void
land_player(object player, string edge)
{
    switch (edge)
    {
        case "west":
        {
            tell_room(ROOM_DIR + "behind_mill", QCTNAME(player)
              + " falls from above and lands with a bit of difficulty"
              + " on the woodpile.\n");

            player->move_living("M", ROOM_DIR + "lumber_pile", 1, 1);
            set_alarm(1.0, 0.0, &player->catch_tell(
                "\nYou land on the woodpile and struggle to keep your"
              + " footing! Phew ... that was almost a bit of a"
              + " tumble.\n"));

            write_file(LOG_DIR + "mill_roof",
                TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
              + ctime(time())[11..18] + ") "
              + capitalize(this_player()->query_real_name()) 
              + " jumps to the woodpile.\n");

            break;
        default:
            tell_room(ROOM_DIR + "behind_mill", QCTNAME(player) + " falls"
              + " from above and lands in the water with a heavy"
              + " splash!\n");

            player->move_living("M", ROOM_DIR + "behind_mill", 1, 1);
            set_alarm(1.0, 0.0, &player->catch_tell("\nYou land with a"
              + " splash! OOOOOF!\n"));

            write_file(LOG_DIR + "mill_roof",
                TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
              + ctime(time())[11..18] + ") "
              + capitalize(this_player()->query_real_name()) 
              + " jumps into the water.\n");

            break;
        }
    }
} /* land_player */


/*
 * Function name:        add_outdoor_tells
 * Description  :        mask the inherited one to provide unique
 *                       tells for this room
 */
public void
add_outdoor_tells()
{
    add_tell("The top of the waterwheel turns endlessly on to the"
      + " north.\n");
    add_tell("A bird lands on the edge of the roof, and then quickly"
      + " flies off again.\n");
    add_tell("A few mercenaries appear from within the mill and walk"
      + " south along the path toward the lodge.\n");
    add_tell("A mercenary approaches the gate below, nods at the guards,"
      + " and is admitted into the training grounds.\n");
    add_tell("A few fast-moving birds arc down toward the river, skim"
      + " along the water, and then disappear over the bridge.\n");
    add_tell("A cloud passes lazily overhead, dimming the sun for a"
      + " brief moment.\n");
} /* add_outdoor_tells */


/*
 * Function name:        do_jump
 * Description  :        allow players to jump off the roof
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_jump(string arg)
{
    /* which direction did they jump? */
    mixed  *edge = ({ "north", "northern", "n",
                      "east", "eastern", "e",
                      "south", "southern", "s",
                      "west", "western", "w",
                      "northeast", "northeastern", "ne",
                      "southeast", "southeastern", "se",
                      "southwest", "southwestern", "sw",
                      "northwest", "northwestern", "nw" }); 
    notify_fail(capitalize(query_verb()) + " where?\n");

    if (!strlen(arg))
    {
        return 0; /* It's an emote, so fail message is covered */
    }

    if (parse_command(arg, ({}),
        "[down] [off] [from] [of] [to] [the] 'roof' / 'ground' /"
      + " 'mill'"))
    {
        write(capitalize(query_verb()) + " off the roof? Err ..."
          + " hmm ... well, from which edge of the roof are you"
          + " thinking to accomplish such a stunt?\n");
        return 1;
    }

    if (parse_command(arg, ({}),
        "[down] [off] [the] 'edge' / 'side' [of] [the] [roof] [mill]"))
    {
        write("Which edge? Standard roofs have four, and this one looks"
          + " pretty standard.\n");
        return 1;
    }

    if (parse_command(arg, ({}),
        "[off] [the] [roof] [down] [on] [to] [onto] [the] [large]"
      + " 'lumber' / 'pile' [of] [lumber] [pile]"))
    {
        write("You carefully drop down onto the pile of lumber.\n");
        tell_room(this_object(), QCTNAME(this_player()) + " drops"
          + " down off the west side of the house and disappears.\n",
            this_player());
        land_player(this_player(), "west");
        return 1;
    }

    if (!parse_command(arg, ({}),
        "[down] [off] [from] [of] [to] [the] %p [side] [of] [the]"
      + " [roof] [ground] [edge]", edge))
    {
        return 0;
    }

    switch (edge[0])
    {
        default:
            return 0;
            break;
        case "north":
        case "northern":
        case "n":
            write("Trying to jump onto the waterwheel is simply a"
              + " lead-up to disaster. You think better of it.\n");
            return 1;
            break;
        case "east":
        case "eastern":
        case "e":
            write("You leap off the roof, soaring down over the"
              + " river!\n");
            tell_room(this_object(), QCTNAME(this_player()) + " jumps"
              + " off the east edge of the roof, and falls down to"
              + " the river landing with a painful looking splash!\n",
                this_player());
            land_player(this_player(), "east");
            return 1;
            break;
        case "south":
        case "southern":
        case "s":
        case "west":
        case "western":
        case "w":
            write("You pause at the edge. It must be a twenty foot"
              + " drop. Broken legs aren't your thing.\n");
            return 1;
            break;
        case "northeast":
        case "northeastern":
        case "ne":
        case "southeast":
        case "southeastern":
        case "se":
        case "southwest":
        case "southwestern":
        case "sw":
        case "northwest":
        case "northwestern":
        case "nw":
            write("Choose a side. Jumping off the corners isn't a good"
              + " idea. The balance is too iffy.\n");
            return 1;
            break;
    }

    return 0; /* shouldn't ever get here, but just in case. */
} /* do_jump */

