/*
 * /d/Gondor/pelargir/rooms/belfalas04.c
 *
 *
 * Copyright (C) 1999 by Cooper Sherry (Gorboth) and
 *	Nancy L. Mintz (Gnadnar)
 * 
 */

#pragma strict_types

inherit "/d/Gondor/pelargir/pelargir_room";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/pelargir_room.h"

/* prototypes */
public void    create_pelargir_room();
public void    init();
public int     smell_here(string arg);

/*
 * Function name:	create_pelargir_room
 * Description	:	set up the room
 */
public void
create_pelargir_room()
{
    set_part(PART_WEST);
    set_street_name(STREET_BELFALAS);
    set_room_type(TYPE_STREET);

    set_extra_desc(
        "Still a good distance north of the business hub of the"
      + " city, " + STREET_BELFALAS + " travels through a collection"
      + " of pleasant looking dwellings here. Just to the west, a"
      + " strong smell comes from the front porch of one home."
      + " A large stone bridge is visible to the northeast.");

    add_item( ({ "hub", "business hub" }), BSN(
        "Most of the business in Pelargir takes place down the"
      + " road a ways to the south."));
    add_item( ({ "smell", "porch", "front porch", "one home" }), BSN(
        "Just to the west of the road, the front porch of a"
      + " fine looking home proudly boasts a row of freshly made"
      + " cheeses, which hang in the open air. The smell is strong"
      + " indeed!"));
    add_item( ({ "row", "row of cheeses", "row of cheese",
                 "cheese", "cheeses" }), BSN(
        "The cheeses are varied in both size and colour. Some are"
      + " light, and look rather soft. Others are dark, and look"
      + " heavy. All of them are round and smell delicious."));
    add_item( ({ "bridge", "large bridge", "stone bridge",
                 "large stone bridge" }), BSN(
        "To the northeast, a large stone bridge provides passage"
      + " over the waters of the Sirith River."));
    add_item( ({ "river", "sirith", "sirith river", "river sirith",
                 "water", "waters" }), BSN(
        "The waters of the Sirith River are visible to the northeast,"
      + " where they flow through the city in a narrow channel. A"
      + " large stone bridge spans the width of the channel."));
    add_item( ({ "channel", "narrow channel" }), BSN(
        "The channel keeps the waters of the river safely in their"
      + " course as they flow through Pelargir."));

    add_exit((PELAR_DIR + "streets/belfalas03"), "northeast", 0);
    add_exit((PELAR_DIR + "streets/belfalas05"), "south", 0);

} /* create_pelargir_room */

/*
 * function name: init
 * description  : provide some actions to the player
 */
public void
init()
{
    ::init();

    add_action(smell_here, "smell");
    add_action(smell_here, "sniff");
} /* init() */

/*
 * function name:        smell_here
 * description  :        let the player smell the cheese!
 * arguments    :        string arg -- what the player typed
 * returns      :        1
 */
public int
smell_here(string arg)
{
    WRITE("As you inhale, you are struck with a very strong odour"
        + " of well-made cheese.");
    return 1;
} /* smell_here */
