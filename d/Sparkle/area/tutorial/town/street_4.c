/*
 *  /d/Sparkle/area/tutorial/town/street_4.c
 *
 *  This road heads through northern Greenhollow. This
 *  room teaches about quitting and its effects on your
 *  inventory, etcetera.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* definitions */
#define  TUTORIAL_CHAPTER    24  /* the chapter for the sign */


/* prototypes */
public void        create_silverdell();
public void        init();
public void        hint(string arg);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("in northern Greenhollow between the Bank and Post Office");
    set_long("The road travels through northern Greenhollow here,"
      + " passing between two very important buildings. To the east"
      + " is a post office, and to the west is a bank. The road"
      + " continues to the north and southwest.\n\n");

    add_road_items();
    add_outdoor_items();
    add_town_items();

    add_item( ({ "northern greenhollow", "north greenhollow" }),
        "Northern Greenhollow contains many of the most important"
      + " buildings in town.\n");
    add_item( ({ "important building", "important buildings",
                 "building", "buildings", "two buildings" }),
        "Two very important buildings border the road here. West"
      + " you see the Bank of Greenhollow, and to the east is the"
      + " Greenhollow Post Office.\n");
    add_item( ({ "west", "bank", "greenhollow bank",
                 "bank of greenhollow" }),
        "The Bank of Greenhollow is a very impressive building"
      + " indeed! Its tall columns support a high marble roof, beneath"
      + " which a set of sturdy wooden doors allow entry into the"
      + " structure. Within, you can manage your money.\n");
    add_item( ({ "column", "columns", "tall column", "tall columns" }),
        "The columns which support the roof of the bank are fluted, and"
      + " rise perhaps thirty feet in height.\n");
    add_item( ({ "marble roof", "high marble roof", "marble" }),
        "The rooftop of the bank is made of very fine marble, which"
      + " is probably why it requires columns to support its weight.\n");
    add_item( ({ "sturdy door", "sturdy doors", "sturdy wooden door",
                 "sturdy wooden doors", "wooden door", "wooden doors" }),
        "Even the doors of the bank look impressive. Perhaps it is"
      + " important for banks to prove that they do a good job with money"
      + " by spending it on their buildings.\n");
    add_item( ({ "east", "office", "post", "post office",
                 "greenhollow post office" }),
        "The Greenhollow Post Office is just east of the road here. Though"
      + " it appears to be a fairly modest structure, it is likely that"
      + " great efficiency takes place within. You can go there to send"
      + " or receive mail.\n");

    prevent_attacks();
    reset_room();

    add_exit("street_5", "north");
    add_exit("post_office", "east");
    add_exit("street_3", "southwest");
    add_exit("bank", "west");
} /* create_greenhollow */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(hint, "hint");
} /* init */


/*
 * Function name:        hint
 * Description  :        give the player a hint if they get stuck
 * Arguments    :        string - what the player typed
 * Returns      :        int 1
 */
public int
hint(string arg)
{
    write("A hint? Sure ... don't get overwhelmed by all of the"
      + " information in town here. If it is seeming like too much to"
      + " take in all at once, feel free to explore and adventure. You"
      + " can always come back and study the tutorial signs more"
      + " later.\n");

    return 1;
} /* hint */


/*
 * Function name:       reset_room
 * Description  :       restore signs and npcs as needed
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */

