#pragma strict_types
/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/nw_cliff1.c
 *
 *  The hillside at the base of the western cliffs of the Blackwall Mountains
 *  joggs northeast here as one travels north. A small waterfall
 *  tumbles down from the cliffs here, feeding a pool that empties
 *  down the slope in a stream running towards the lake. This area
 *  has been heavily defiled by the orcs, but can be cleaned by
 *  the conscientious adventurer.
 *
 *  Copyright (c) April 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/cliff_room.c";
inherit "/d/Emerald/blackwall/delrimmon/stream.c";
inherit "/d/Emerald/blackwall/delrimmon/lib/water_effects.c";

#include <macros.h>      /* for QCTNAME */
#include <ss_types.h>    /* for SS_CLIMB */
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* definitions */
#define    WATERFALL    (DELRIMMON_DIR + "lakeside/cliffs/ledge8")

/*
 * Prototypes
 */
public int     smell_here(string str);
string         describe_stream_hook();
public string  chimney_desc();
public string  filth_desc();
public string  floating_filth_desc();
public string  orc_filth();
public string  pool_desc();
public string  room_describe();
public string  search_pool_desc();
public string  smell_desc();
public string  waterfall_desc();
public int     clean_pool(string arg);
public int     enter_pool(string arg);
public void    init();

/*
 * Function name: create_cliff_room
 * Description  : allows us to create the room with presets for the
 *                stream descriptions
 */
public void
create_cliff_room()
{
    Next_Stream = DELRIMMON_DIR + "lakeside/w_wood5b";

    set_loc(3);
    set_side("northwest");
    add_name("chimney_room");
    add_name("chimney_bottom");
    set_uproom(DELRIMMON_DIR + "lakeside/cliffs/ledge8");

    set_extraline(room_describe);

    add_item( ({"bend"}), BSN(
        "Southwest of here the cliffs jog to the south, running in"
      + " tandom with the countour of the lake."));
    add_item( ({"side", "side of the cliff", "side of the cliffs"}),
    BSN("The cliffs bend a ways to the southwest running south in"
      + " tandom with the contour of the lake. Closeby, a chimney"
      + " has been worn into the rock where water flows down the"
      + " side of the cliff."));
    add_item( ({"contour", "contour of the lake"}), BSN(
        "The lake of Del Rimmon curves in a long oval here along"
      + " the west side from its center."));
    add_item( ({"center", "center of the lake"}), BSN(
        "The center of the lake is not clearly visible from"
      + " here, though glimpses can be had through the tree"
      + " tops."));
    add_item( ({"glimpses", "glimpse"}), BSN(
        "A hint of greyish blue water is visible through the"
      + " tops of the trees."));
    add_item( ({"erosion", "water erosion"}), BSN(
        "The chimney looks to have been carved out over many years"
      + " by the flow of water down the cliff side."));
    add_item( ({"vent", "inner vent"}), BSN(
        "The inner surface of the chimney which extends up the rock"
      + " face is quite smooth, having been worn continuously by"
      + " falling water."));
    add_item( ({"jagged edge", "edge of the chimney"}), BSN(
        "The edge of the chimney is jagged, due to its nature as"
      + " a literal cross section of the texture along the"
      + " cliffs which has been created by the cutting of the"
      + " waterfall."));
    add_item( ({"texture", "cross section"}), BSN(
        "Where a chimney has been cut out of the cliffs, the"
      + " texture of the rock is jagged, creating what would"
      + " surely be perfect hand holds for a climber."));
    add_item( ({"chimney"}), chimney_desc );
    add_item( ({"smell", "odour", "stench",
                "unbearable stench"}), 
                smell_desc );
    add_item( ({"defecation", "unspeakable refuse"}), orc_filth );
    add_item( ({"water of the pool", "waters of the pool",
                "surface", "surface of the pool", "filthy water",
                "floating filth", "floating refuse"}),
                floating_filth_desc );
    add_item( ({"filth", "edge", "edge of the pool", "refuse"}),
                filth_desc );
    add_item( ({"waterfall", "splashing waterfall",
                 "trickle", "tiny trickle",
                 "trickle of water"}), waterfall_desc );
    add_item( ({"pool", "fetid pool"}), pool_desc );
    add_item( ({ "stream", "overflow", "flow" }),
        "It seems that the water from above is enough to have pushed"
      + " some of the water out of the pool into a narrow channel which"
      + " winds away south.\n");
    add_item( ({ "narrow channel", "channel" }),
        "The channel looks as if it has been dug out by running water"
      + " over a rather long period of time.\n");

    add_cmd_item( ({"pool", "fetid pool"}),
                  ({"search"}), search_pool_desc );
    add_cmd_item( ({"chimney"}),
                  ({"search"}), BSN(
        "Examining the chimney more closely, you notice that the"
      + " texture of its sides is such that it would probably be"
      + " quite easy to climb up."));
    add_cmd_item( ({"pool", "fetid pool", "surface",
                    "water from pool", "from pool"}),
                  ({"drink"}), BSN(
        "The filth strewn along the edge of the pool makes it"
      + " quite clear that this water is not fit for consumption."));

    add_prop(OBJ_I_CONTAIN_WATER, -1);

    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff2","northeast");
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood1b","east",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood5","southeast",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood5b","south",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_cliff5","southwest");

    set_no_exit_msg( ({ "west", "northwest", "north" }),
        "The walls of the cliffs prevent you from travelling in"
      + " that direction.\n");
} /* create_cliff_room */

/*
 * Function name: room_describe
 * Description  : allows us to modify the room description based on
 *                whether or not the water is clean.
 * Arguments    : none
 * Returns      : the text for the room description (string)
 */
public string
room_describe()
{
    string  rdesc;

    rdesc = "The sheer rock faces round a bend a ways to the southwest,"
          + " gradually tracing the contour of the lake. ";

    if (Pure_Water)
     {
        rdesc += "A small waterfall splashes down the side of the"
              + " cliffs here, feeding into a pool which overflows"
              + " down the hill in the form of a stream.";
    }

    else
    {
        rdesc += "A tiny trickle of water drips down the side of"
               + " the cliffs here, draining into a fetid pool"
               + " which is overflowing down the"
               + " hillside in the form of a stream. The smell"
               + " here is almost too much to bear.";
    }

    return rdesc;
} /* room_describe */

/*
 * Function name:        clean_pool
 * Description  :        allow the player to try to clean the place
 *                       up.
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
clean_pool(string arg)
{
    if (!strlen(arg))
    {
        NFN0("Clean what?");
    }

    if (!parse_command(arg, ({}),
        "[up] [the] 'mess' / 'filth' / 'refuse' / 'water' /"
      + " 'pool'"))
    {
        return 0; /* Wrong syntax, or we didn't anticipate it */
    }

    if (Pure_Water)
    {
        write("It already seems that the flowing water from the falls"
            + " has done the work for you. Though the sides of the"
            + " pool are still strewn with filth, the water itself"
            + " looks clear and fresh.\n");

        return 1;
    }
    write("Taking a moment to appraise the situation, you quickly"
        + " decide that there is no way that you could manually clean"
        + " up this pool. Natural forces might help, but the meager"
        + " trickle of the waterfall is not doing any good.\n");

    return 1;
} /* clean_pool */


/*
 * Function name: search_pool_desc
 * Description  : what do the players see when they search the pool?
 * Returns      : description of the pool (string)
 */
public string
search_pool_desc()
{
    if (query_pure_water())
    {
        return BSN("Searching through the waters of the pool, you"
                 + " find that most of the filth is gone from the"
                 + " waters, and only that which remains on shore"
                 + " is yet any defilement to the area.");
    }

    return BSN("Searching through the waters of the pool, you are"
             + " hit with a nearly overwhelming stench which rises"
             + " from the filth choked surface. Cleaning this up"
             + " would probably clear the stream of its foul"
             + " debris as well.");
} /* search_pool_desc */

/*
 * Function name: chimney_desc
 * Description  : describes the chimney, and tells us if the waterfall
 *                is in action.
 * Returns      : description of the chimney (string)
 */
public string
chimney_desc()
{
    string  chdesc = "A chimney perhaps three feet in width has"
                   + " been bored out of the cliffside here.";

    if (query_pure_water())
    {
        chdesc += " A small waterfall courses down through the passage"
                + " in the rock to spill into a pool at the base of"
                + " the cliff.";
    }

    else
    {
        chdesc += " A tiny trickle of water winds and drips down the"
                + " length of the chimney, falling into a pool at the"
                + " base of the cliff.";
    }

    return BSN(chdesc + " The erosion from the water has left the"
                      + " inner vent of the chimney smooth, but"
                      + " created a jagged edge along both sides.");
} /* chimney_desc */

/*
 * Function name: smell_desc
 * Description  : we give the player info on how the room smells.
 * Returns      : description of the smell (string)
 */
public string
smell_desc()
{
    if (query_pure_water())
    {
        return BSN("A slight odour arises from the filth littered along"
                 + " the edge of the pool.");
    }

    return BSN("The filth along the edge of the pool combined with the"
             + " rank contents of its water produce a nearly"
             + " unbearable stench in this place.");
} /* smell_desc */

/*
 * Function name: orc_filth
 * Description  : goblins obviously would not be offended by orcish
 *                behavior, so they get a different description.
 * Returns      : description of the orc filth (string)
 */
public string
orc_filth()
{
    if (TP->query_race() == "goblin")
    {
        return BSN("You recognize this as just the sort of thing one"
                 + " of your kind might do.");
    }

    return BSN("Only orcs would perform such hideous acts as this.");
} /* orc_filth */

/*
 * Function name: floating_filth_desc
 * Description  : describe the awful stuff floating in the pool
 * Returns      : description of the gross stuff (string)
 */
public string
floating_filth_desc()
{
    if (query_pure_water())
    {
        return BSN("Though an occasional bit of the filth along the"
                 + " edge of the pool will slip into the water, it"
                 + " is soon washed downstream by the flow generated"
                 + " by the falls.");
    }

    return BSN("The waters of the pool are absolutely filled with"
             + " unspeakable refuse. It seems quite evident that"
             + " some beastly creature has taken it upon itself to"
             + " use this water for defecation.");
} /* floating_filth_desc */

/*
 * Function name: filth_desc
 * Description  : describe the filth based on query_pure_water
 * Returns      : description of the filth (string)
 */
public string
filth_desc()
{
    string  fdesc = "The filth which is strewn along the edge of the"
                  + " pool is ghastly in the extreme. It would seem"
                  + " as if some wretched creature has been using"
                  + " the pool for defecation.";

    if (query_pure_water())
    {
        fdesc += " Fortunately, it appears that most of the refuse"
               + " has been washed downstream by the flow of the"
               + " waterfall.";
    }

    else
    {
        fdesc += " The surface of the pool is crowded with floating"
               + " refuse, and a hideous smell arises from its fetid"
               + " waters.";
    }

    return BSN(fdesc);
} /* filth_desc */

/*
 * Function name: pool_desc
 * Description  : provides a description of the pool depending on
 *                whether query_pure_water is true
 * Returns      : description of the pool (string)
 */
public string
pool_desc()
{
    string pdesc = "A pool spreads itself along the base of the"
                 + " cliffs here, perhaps running twenty feet"
                 + " in diameter. The waters of the pool overflow"
                 + " into a stream which runs south, and disappears"
                 + " between the trees of the forest.";

    if (query_pure_water())
    {
        pdesc += " Filth is strewn along the edge of the pool, yet"
               + " seems to have been washed free of the waters.";
    }

    else
    {
        pdesc += " The waters of the pool have been completely defiled"
               + " by someone or something. Filth is strewn along the"
               + " edge of the pool, and the surface of the pool is"
               + " cluttered with floating refuse.";
    }

    return BSN(pdesc);
} /* pool_desc */

/*
 * Function name: waterfall_desc
 * Description  : provides a description of the waterfall depending on
 *                whether query_pure_water is true.
 * Returns      : description of the waterfall (string)
 */
public string
waterfall_desc()
{
    if (query_pure_water())
    {
        return BSN("Spilling from high above in the cliffs, this"
             + " waterfall pours into a pool which rests at the base of"
             + " the rock face. Years of water erosion have carved a"
             + " chimney in the rock where it pours down.");
    }

    return BSN("Dripping weakly from high above in the cliffs, this"
         + " trickle drops into a pool which rests at the base of"
         + " the rock face. Years of water erosion have carved a"
         + " chimney in the rock where it runs down.");
} /* waterfall_desc */

/*
 * Function name: describe_stream_hook
 * Description  : here we redefine the master file's function to give
 *                this room a unique description of the stream
 * Returns      : description of the stream (string)
 */
string
describe_stream_hook()
{
    return "The stream seems to issue from its source here, where"
         + " a pool overflows into a narrow gulley. Winding down"
         + " the slope, the water dissapears through the trees"
         + " to the south.";
} /* describe_stream_hook */

/*
 * Function name: notify_purification_hook
 * Description  : by redefining this, we give the room a unique message
 *              : when change_stream is called
 * Returns      : the unique text message (string)
 */
string
notify_purification_hook()
{
    if (!Pure_Water)
    {
        return "The waterfall dwindles to a mere trickle, and the"
             + " flow of the water down the stream is stifled as"
             + " well. As the pool stagnates, an unpleasant colour"
             + " appears in the stream, and a foul odour arises from"
             + " the water.";
    }

    return "The trickle of water which runs down the cliff face"
         + " splashes suddenly, becoming a rushing torrent"
         + " of water from above. As the flow of the waterfall"
         + " stabilizes, the fetid waters of the pool"
         + " are washed downstream and replaced by the clean water"
         + " of the falls.";
} /* notify_purification_hook */

/*
 * Function name: smell_here
 * Description  : adds support for the verb "smell"
 * Returns      : int 1 - success, 0 - fail
 */
public int
smell_here(string str)
{
    if (!strlen(str))
    {
        write(smell_desc());
        return 1;
    }

    if (str != "pool" && str != "fetid pool" &&
        str != "filth" && str != "floating filth" &&
        str != "refuse" && str != "floating refuse" &&
        str != "stream" && str != "here" &&
        str != "water" && str != "surface" &&
        str != "surface of the pool")
    {
        NFN0("What do you wish to smell?");
    }

    write(smell_desc());
    return 1;
} /* smell_here */


/*
 * Function name:        enter_pool
 * Description  :        if the pool is clean, allow the player to
 *                       try to swim around in its waters
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
enter_pool(string arg)
{
    if (!strlen(arg))
    {
        NFN0(CAP(QVB) + " where?");
    }

    if (!parse_command(arg, ({}),
        "[in] [into] [the] 'water' / 'pool' / 'waters'"
      + " [of] [the] [pool]"))
    {
        return 0; /* player typed unusable syntax */
    }

    if (query_pure_water())
    {
        if (this_player()->query_skill(SS_SWIM) < 10)
        {
            write("You look doubtfully at the water, and think better"
                + " of it. You simply don't know how to swim well"
                + " enough to dare.\n");

            return 1;
        }

        write("You dive into the pool.\n");

        tell_room(this_object(), QCTNAME(this_player())
          + " dives into the pool and disappears beneath its"
          + " surface.\n", this_player());
 
        douse_flames(this_player());

        this_player()->move_living("M", 
            DELRIMMON_DIR + "lakeside/pool_bottom", 1, 0);
        tell_room(environment(this_player()), QCTNAME(this_player())
          + " arrives, plunging into the water amid a flurry of"
          + " bubbles.\n", this_player());

        return 1;
    }

    write("Dive into a pool of such filth? You'd better find a way to"
        + " clean it first. This sort of thing could prove quite"
        + " poisonous if swallowed.\n");
    return 1;
} /* enter_pool */


/*
 * Function name: init
 * Description  : add actions for the player
 */
void
init()
{
    ::init();

    add_action(climb_chimney, "climb");
    add_action(smell_here, "smell");
    add_action(enter_pool, "swim");
    add_action(enter_pool, "dive");
    add_action(enter_pool, "enter");
    add_action(clean_pool, "clean");
    add_action(do_drink, "drink");
} /* init */
