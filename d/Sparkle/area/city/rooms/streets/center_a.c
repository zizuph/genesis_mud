/*
 *  /d/Sparkle/area/city/rooms/streets/center_a.c
 *
 *  Here, the Old Sparkle Road ends beside the Post office and AoP
 *  Office. There is a fountain here that has some fun things for
 *  players to discover, as well.
 *
 *  Created June 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../../defs.h"
inherit ROOMS_DIR + "outdoor_room";

#include <composite.h>
#include <macros.h>

/* Prototpyes */
public void        create_sparkle();
public string      exa_sign(string arg);
public string      exa_manhole();
public string      exa_stuff(string arg);
public int         get_stuff(string arg);
public void        init();


/* Globabl Variables */
public int         Manhole_Closed = 1;
public object      Pool;


/*
 * Function name:        create_sparkle
 * Description  :        set up the room with area presets
 */
public void
create_sparkle()
{
    object    pool;

    set_quadrant("center");
    set_street(STREET_CENTER);

    set_short_extra("The post office is to the south. East is a large"
      + " building");

    set_long_extra("The road ends in a cul-de-sac here at the center of"
      + " which a beautiful fountain sends water splashing above the"
      + " heads of those who pass. Just to the east, a large and formal"
      + " looking building rises above the street, casting shade into"
      + " the front of an inn to the north. A cheerful sign hangs beside"
      + " a stone path leading south toward a busy office, and an"
      + " elegant sign hangs above the inn.");

    try_item( ({ "inn", "silver swan", "silver swan inn",
                 "the silver swan", "the silver swan inn" }),
        "To the north, the Silver Swan Inn rests comfortably in the"
      + " shade. It is a notably refined building, with elegance of"
      + " architecture and stylings evident in its every corner.\n");
    try_item( ({ "large building", "formal building",
                 "formal looking building",
                 "large and formal looking building",
                 "aop office", "tall building", "building to the east",
                 "east building", "eastern building",
                 "large formal building" }),
        "This is the AoP Office, which allows players to communicate"
      + " with the wizard responsible for player concerns. Travelling"
      + " east will take you inside.\n");
    try_item( ({ "building" }),
        "There are a number of buildings here. Which did you wish"
      + " to examine?\n");
    try_item( ({ "base", "base of the fountain", "fountain base" }),
        "The base of the fountain is comprised of a basin filled with"
      + " a large pool of water.\n");
    try_item( ({ "stone" }),
        "There is a lot of stone in a city such as this. Can you be"
      + " more specific?\n");
    try_item( ({ "stone path", "path" }),
        "The path is comprised of flat white stones that have been"
      + " placed close together leading south toward the Post Office.\n");
    try_item( ({ "stones", "white stones", "flat stones",
                 "white stone", "flat stone", "flat white stone",
                 "flat white stones", "white flat stone",
                 "white flat stones" }),
        "They are very attractive examples of what is available in"
      + " some of the local quarries.\n");
    try_item( ({ "office", "busy office", "post office" }),
        "The Post Office is just to the south. A stone path leads"
      + " from the road up to its door.\n");
    try_item( ({ "door", "post office door", "door of the post office",
                 "green door" }),
        "The door of the post office is green. It looks inviting.\n");
    try_item( ({ "shade" }),
        "The inn is pleasantly shaded by the tall"
      + " building just to the east.\n");
    try_item( ({ "cul-de-sac", "circle", "cul de sac",
                 "culdesac" }),
        "The road circles here around a central fountain, its only"
      + " exit the one to the west.\n");
    try_item( ({ "exit", "west" }),
        "West, the road travels away from the cul-de-sac, eventually"
      + " rounding a bend to travel southward.\n");
    try_item( ({ "bend", "bend in the road" }),
        "You can't see much from here.\n");
    try_item( ({ "fountain", "beautiful fountain", "central fountain" }),
        "@@exa_stuff|fountain@@");
    try_item( ({ "figure", "man", "fat man", "very fat man" }),
        "Though the man looks like a bit of a comic figure, a sense"
      + " of tragedy tugs at your awareness as you gaze upon him.\n");
    try_item( ({ "fatty" }),
        "Indeed, this figure can be none other than Fatty, the poor"
      + " soul whose greed brought about the creation of the Donut"
      + " itself. You can learn more with <help history>.\n");
    try_item( ({ "tray", "tray of donuts" }),
        "There are a dozen or so donuts on the tray.\n");
    try_item( ({ "dozen", "dozen donuts" }),
        "Well ... I suppose its a baker's dozen.\n");
    try_item( ({ "water" }),
        "Streams of water shoot from the fountain, landing in a pool"
      + " within a basin that surrounds the central figure which is the"
      + " fountain's focal point.\n");
    try_item( ({ "focal point" }),
        "Hard to miss him. He's a very fat man.\n");
    try_item( ({ "bakers dozen", "baker's dozen" }),
        "Mmmmmm ... donuts ...\n");
    try_item( ({ "donut", "donuts" }),
        "From the hole in each donut, a stream of water sprays powerfully"
      + " into the air, creating the beautiful aquatic display.\n");
    try_item( ({ "display", "aquatic display" }),
        "Mesmerizing. One can stare at falling water for hours.\n");
    add_cmd_item( ({ "falling water", "at falling water",
                     "at the falling water" }),
                  ({ "exa", "look", "stare" }),
        "As you stare, time ticks by ... \n");
    try_item( ({ "donut hole", "hole", "holes", "donut holes",
                 "hole in each donut", "holes in each donut" }),
        "There must be powerful pipes of some sort that power the"
      + " streams of water.\n");
    try_item( ({ "pipe", "pipes", "powerful pipe", "powerful pipes" }),
        "The fountain is cleverly crafted so that they are not"
      + " visible.\n");
    try_item( ({ "stream", "streams", "water stream", "water streams",
                 "stream of water", "streams of water" }),
        "They arc high above, putting on a display that is truly"
      + " mesmerizing. Falling water has that effect, I suppose.\n");
    try_item( ({ "basin", "water basin", "basin of the fountain",
                 "large basin", "large water basin" }),
        "The basin rises a few feet off the narrow walkway that"
      + " surrounds the fountain. In it, the falling water from the"
      + " fountain forms a large pool.\n");
    try_item( ({ "walkway", "narrow walkway" }),
        "The walkway surrounds the fountain, allowing people to stand"
      + " and toss coins in the pool or enjoy the spray from the falling"
      + " water on their faces. A manhole cover is embedded in the"
      + " walkway.\n");
    try_item( ({ "spray", "spray from the fountain",
                 "spray from the falling water" }),
        "As the water falls into the pool, spray is kicked up, sometimes"
      + " splashing a bit on anyone standing close enough.\n");
    add_cmd_item( ({ "close", "close enough", "close to the fountain",
                     "fountain", "close enough to the fountain",
                     "closer" }),
                  ({ "stand" }),
        "You stand right up against the basin, allowing some of the"
      + " spray from the falling water to splash onto your face. Ahh ..."
      + " that is refreshing!\n");
    try_item( ({ "sparkling water", "sparkling water of the fountain" }),
        "The sun catches it at times, creating bright flashes of"
      + " light.\n");
    try_item( ({ "flash", "flashes", "flash of light", "flashes of light",
                 "bright flash", "bright flashes",
                 "bright flash of light", "bright flashes of light" }),
        "Dazzling!\n");
    try_item( ({ "splashing water", "splashing water of the fountain" }),
        "The pool catches the water as it falls, frothing with many"
      + " and constant splashes.\n");
    try_item( ({ "splash", "splashes", "splashing" }),
        "Splish, splosh ...\n");
    try_item( ({ "ladder", }), &exa_stuff("ladder"));
    try_item( ({ "lid", "tight-fitting lid", "iron lid",
                 "tight-fitting iron lid", "manhole lid" }),
                 &exa_stuff("lid"));
    try_item( ({ "opening", }), &exa_stuff("opening"));
    try_item( ({ "darkness", "dark" }), &exa_stuff("darkness"));
    try_item( ({ "hinge", "sturdy hinge", "manhole hinge", "cover hinge",
                 "lid hinge" }),
        "The hinge connects the manhole cover to the walkway. It looks"
      + " extremely sturdy.\n");
    try_item( ({ "cover", "manhole", "manhole cover" }), exa_manhole);

    try_item( ({ "sign", "signs" }),
        "Examine which sign? The cheerful sign and the"
      + " elegant sign are both nearby.\n");
    add_cmd_item( ({ "sign", "the sign", "the signs", "signs" }),
                  ({ "read" }),
        "Read which sign? The small cheerful sign and the"
      + " elegant sign are both nearby.\n");

    add_item( ({ "cheerful sign", "post office sign",
                 "south sign" }),
        "@@exa_sign|sign_post_office@@");
    add_item( ({ "elegant sign", "inn sign", "silver swan sign",
                 "silver swan inn sign", "north sign" }),
        "@@exa_sign|sign_inn@@");

    add_cmd_item( ({ "cheerful sign",
                     "the cheerful sign", "post office sign",
                     "the post office sign", "south sign" }),
                  ({ "read" }), "@@exa_sign|sign_post_office@@");
    add_cmd_item( ({ "elegant sign", "the elegant sign",
                     "inn sign", "the inn sign",
                     "silver swan sign", "the silver swan sign",
                     "silver swan inn sign", "the silver swan inn sign",
                     "north sign", "the north sign" }),
                  ({ "read" }), "@@exa_sign|sign_inn@@");
    add_cmd_item( ({ "manhole", "cover", "manhole cover",
                     "lid", "manhole lid" }),
                  ({ "pull", "open", "lift", "flip" }),
        "You tug at one corner of the manhole lid, and manage to lift"
      + " it about an inch before it firmly catches in place and will"
      + " not budge any further. It appears to be locked from"
      + " beneath.\n");
    add_cmd_item( ({ "manhole", "cover", "manhole cover",
                     "lid", "manhole lid", "lock" }),
                  ({ "unlock", "pick" }),
        "The lock is beneath the manhole cover. You have no access.\n");

    add_center_items();

    add_delay_cmd_item( ({ "cover", "manhole", "manhole cover" }),
                        "search",
                        "searching the manhole",
                        10,
                        "You begin searching the manhole, looking for"
                      + " anything that looks interesting.\n",
                        "After careful inspection of the manhole"
                      + " you guess that it is meant to be pulled"
                      + " open, flipping it on its hinges.\n");

    /* Let players fill buckets, etc here. */
    add_prop(OBJ_I_CONTAIN_WATER, -1);

    /* Lets add some room tells for the fountain */
    add_tell("Sunlight plays off the sparkling water of the"
      + " fountain.\n");
    add_tell("The splashing water of the fountain sounds throughout"
      + " the area.\n");
    add_tell("A gust of wind blows spray from the fountain in"
      + " your direction.\n");
    add_tell("A cloud passes before the sun, casting sudden shade over"
      + " the area.\n");

    add_exit("center_b", "west");
    add_exit(ROOMS_DIR + "inside/inn", "north");
    add_exit("/d/Genesis/start/human/town/aop_office", "east");
    add_exit("/d/Genesis/start/human/town/post", "south");

    /*
     * Lets create the actual pool of the fountain here, allowing players
     * to toss things like coins into the thing.
     */
    Pool = clone_object(OBJ_DIR + "fountain_pool");
    Pool->move(this_object());
} /* create_sparkle */


/*
 * Function name:        exa_sign
 * Description  :        provide a description of the sign that is
 *                       hanging here
 * Arguments    :        string arg - which sign do we want?
 * Returns      :        string - the text to display
 */
public string
exa_sign(string arg)
{
    string  sign = ((arg == "sign_inn")
                 ? "inn" : "post office");

    /* A check for the sign rating quest */
    check_rating_form(this_player(), sign);

    return "The sign reads:\n\n"
      + read_file(TEXT_DIR + arg);
} /* exa_sign */


/*
 * Function name:        exa_manhole
 * Description  :        provide a state-dependant description of
 *                       the manhole cover
 * Returns      :        string - the description
 */
public string
exa_manhole()
{
    if (Manhole_Closed)
    {
        return "The manhole is covered by a tight-fitting iron lid"
          + " which is secured in place by a hinge that has been bolted"
          + " to the walkway on one side.\n";
    }

    return "The manhole leads down beneath the walkway, where a ladder"
      + " is visible descending into the depths. The manhole cover has"
      + " been flipped open, and rests to one side of the opening,"
      + " secured in place by a hinge that has been bolted to the"
      + " walkway.\n";
} /* exa_manhole */


/*
 * Function name:        exa_stuff
 * Description  :        Provide state-dependant responses to various
 *                       add_items above
 * Arguments    :        string arg - which item are we describing?
 * Returns      :        string - the description
 */
public string
exa_stuff(string arg)
{
    string  desc;
    object *pool = all_inventory(Pool);

    switch (arg)
    {
        case "lid":
            if (Manhole_Closed)
            {
                return "The lid is covering the manhole.\n";
            }
            
            return "The lid has been pulled open, revealing a"
              + " ladder descending into darkness.\n";
            break;
        case "ladder":
            if (Manhole_Closed)
            {
                return "You find no ladder.\n";
            }

            return "The ladder leads down into darkness beneath the"
              + " opening of the manhole cover.\n";
            break;
        case "opening":
            if (Manhole_Closed)
            {
                return "You find no opening.\n";
            }

            return "The opening leads beneath the street and the"
              + " fountain, though it is hard to know much more from"
              + " up here.\n";
            break;
        case "darkness":
            if (Manhole_Closed)
            {
                return "You find no darkness.\n";
            }

            return "Its dark down there!\n";
            break;
        case "fountain":
            desc =  "The fountain depicts a figure of a fat man with a"
                  + " greedy look in his eyes holding a tray of donuts."
                  + " From the hole in each donut, water sprays high into the"
                  + " air to land in the large basin which surrounds the"
                  + " figure. ";

            if (sizeof(pool))
            {
                desc += "You see " + COMPOSITE_DEAD(pool)
                  + " resting at the bottom of the pool within the basin.";
            }

            return desc + "\n";
        default:
            return ""; /* Should never happen, but just in case. */
            break;
    }

    return ""; /* Should never happen, but just in case */
} /* exa_stuff */


/*
 * Function name:        get_stuff
 * Description  :        allow players to get stuff from the "fountain"
 *                       even though the pool does not include that name.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
get_stuff(string arg)
{
    string  str;

    if (!strlen(arg))
    {
        return 0; /* let the mudlib handle the fail msg. */
    }

    if (!parse_command(arg, ({}),
        "%s 'from' [the] [beautiful] [central] 'fountain' / 'basin'", str))
    {
        return 0; /* mudlib will handle the fail msg */
    }

    /* The idea here is that we just force the player to type the same
     * command, but substitute "pool" for "fountain" or "basin".
     */
    if (this_player()->query_wiz_level())
    {
        write("At this point, we would force the player to get the item"
          + " from the \"pool\" instead of the \"fountain\" using"
          + " command(). Since you are a wizard, that won't work, so just"
          + " type the correct thing yourself.\n");
        return 1;
    }

    this_player()->command("$get " + str + " from pool");
    return 1;
} /* get_stuff */


/*
 * Function name:        init
 * Description  :        add some actions for the player
 */
public void
init()
{
    ::init();

    add_action(get_stuff, "get");
    add_action(get_stuff, "take");
    add_action(get_stuff, "lift");
} /* init */
