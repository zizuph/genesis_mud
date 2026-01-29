/*
 *  /d/Sparkle/guilds/new_merc/neutral_start.c
 *
 *  This is the startroom for Mercs who do not wish to reside with either
 *  good or evil faction in the Guildhall, but simply wish to bunk in a
 *  neutral fashion.
 *
 *  Created May 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;

#include <macros.h>
#include <stdproperties.h>

/* Prototypes */
public void        create_merc_room();
public void        init();
public int         lie_bed(string arg);
public int         rise(string arg);
public void        leave_inv(object ob, object to);
public int         start(string str);
public int         wake_cook(string arg);

/* Definitions */
#define        BUNK_PROP    "_bunk_prop"


/*
 * Function name:        create_merc_room
 * Description  :        set up the room with area presets
 */
public void
create_merc_room()
{
    object   door;

    set_short("in the general sleeping quarters of the Mercenary Guild");
    set_long("Bunks line the walls of this fairly large"
      + " chamber within the lodge. It is here that any Mercenary"
      + " may come and <bunk> with their guildmates after a long"
      + " day of fortune seeking.\n\n");

    try_item( ({ "bunk", "bunks", "bed", "beds", "bunk bed",
                 "bunk-bed", "bunk beds", "bunk-beds" }),
        "The bunks may not be the most luxurious accomodations that"
      + " can be found in the realms, but they are a welcome sight"
      + " to any Mercenary who has been forced on more than one"
      + " occasion to use the roots of a tree to pass a long"
      + " sleeping period.\n");
    try_item( ({ "root", "roots", "roots of a tree", "tree roots" }),
        "A mediocre bunk beats that any day of the week!\n");
    try_item( ({ "mediocre bunk", "mediocre bunks" }),
        "Perhaps ... but tree roots can't even claim to be"
      + " mediocre for sleep. These are first rate by comparison!\n");
    try_item( ({ "wall", "walls" }),
        "The walls are lined with bunks here. Did you want to examine"
      + " a particular one?\n");
    try_item( ({ "north wall", "northern wall", "wall to the north" }),
        "The north wall is lined with many bunks, which are"
      + " interrupted midway through by a sturdy wooden door"
      + " that leads out of the chamber.\n");
    try_item( ({ "west wall", "western wall", "wall to the west" }),
        "The western wall is narrower than those to the north"
      + " and south, and only provides space for a few bunks"
      + " spaced between windows which look out onto the training"
      + " yard.\n");
    try_item( ({ "training yard", "yard" }),
        "The training yard is visible through windows in the"
      + " western wall. You can't see much detail from here, but"
      + " you do hear the occasional yell or clash of steel.\n");
    try_item( ({ "yell", "shout", "occasional yell" }),
        "GAAAARRRRRRRRRRR!\n");
    try_item( ({ "clash", "clash of steel" }),
        "CLANG! CHINK!!\n");
    try_item( ({ "south wall", "southern wall", "wall to the south" }),
        "There are a great many bunks lining the southern wall,"
      + " which is just as wide as the northern one, but is not"
      + " interrupted by a doorway.\n");
    try_item( ({ "great many bunks" }),
        "Yeah ... must be a dozen or so.\n");
    try_item( ({ "dozen", "dozen bunks" }),
        "1, 2, 3, 4 ... counting is fun.\n");
    try_item( ({ "east wall", "eastern wall", "wall to the east" }),
        "The wall to the east has few bunks, and no windows. It"
      + " does, however, boast a painted blue door right in the"
      + " middle of its length.\n");
    try_item( ({ "snoring", "snore", "snores", "loud snore",
                 "loud snoring" }),
        "No shortage of that in here, is there?\n");
    try_item( ({ "mercenary", "mercenaries", "man", "woman",
                 "sleeper", "sleepers", "sleeping mercenary",
                 "sleeping mercenaries", "sleeping people",
                 "sleeping person", "sleeping man",
                 "sleeping woman", "person", "weary mercenary" }),
        "Numerous people lie sleeping in nearby bunks.\n");

    add_cmd_item( ({ "mercenary", "mercenaries", "sleeper",
                     "sleeping mercenary", "sleeping man",
                     "sleeping woman", "sleeping person",
                     "man", "woman", "person" }),
                  ({ "wake", "disturb" }),
        "You know ... that would make you a jerk. Are you a jerk?"
      + " Lets not be a jerk.\n");

    add_indoor_view();
    add_indoor_lodge_view();

    add_prop(ROOM_I_INSIDE, 1);

    add_tell("A weary mercenary enters the room, crosses to a"
      + " nearby bunk, stretches, and lies down to sleep.\n");
    add_tell("Loud snoring issues from a nearby bunk.\n");
    add_tell("One of the sleeping mercenaries begins talking"
      + " in her sleep, but then rolls over and is silent.\n");
    add_tell("A sudden burst of muffled laughter comes from the"
      + " door to the north. A sleeping mercenary lifts his head,"
      + " glares momentarily at the door, and then turns over"
      + " and begins snoring.\n");

    setuid();
    seteuid(getuid());

    door = clone_object(DOORS_DIR + "broom_w");
    door->move(this_object());
    door = clone_object(DOORS_DIR + "neutral_s");
    door->move(this_object());
} /* create_room */


/*
 * Function name:        init
 * Description  :        add_some actions to the player
 */
public void
init()
{
    ::init();

    add_action(lie_bed, "lie");
    add_action(lie_bed, "lay");
    add_action(lie_bed, "sleep");
    add_action(lie_bed, "rest");
    add_action(rise, "get");
    add_action(rise, "stand");
    add_action(rise, "rise");
    add_action(start, "start");
    add_action(start, "bunk");
    add_action(wake_cook, "wake");
} /* init */


/*
 * Function name:        lie_bed
 * Description  :        Allow players to lie down on the bunks
 *                       and rest a bit
 * Arguments    :        string arg - what was typed after the
 *                                    verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
lie_bed(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    if (this_player()->query_prop(BUNK_PROP))
    {
        write("But you are already " + query_verb() + "ing"
          + " somewhere!\n");
        return 1;
    }

    if ( (query_verb() == "lay" || query_verb() == "lie") &&
        arg == "down")
    {
        notify_fail("Lie down on what? One of the bunks perhaps?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[down] [on] [upon] [one] [of] [the] 'bunk' / 'bed'"
      + " / 'bunks' / 'beds'"))
    {
        notify_fail("Perhaps you want to " + query_verb() + " on"
          + " one of the bunks?\n");
        return 0;
    }

    write("You lie down on one of the bunks and rest a bit.\n");
    say(QCTNAME(this_player())
          + " crosses over to one of the bunks and lies down.\n");
    this_player()->add_prop(BUNK_PROP, 1);
    this_player()->add_prop(LIVE_S_EXTRA_SHORT, 
        " is lying on one of the bunks");

    return 1;
} /* lie_bed */


/*
 * Function name:        rise
 * Description  :        Allow the player to get up from the bed
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
rise(string arg)
{
    if (!strlen(arg) && query_verb() == "get" &&
        this_player()->query_prop(BUNK_PROP))
    {
        notify_fail("Get up, perhaps?\n");
        return 0;
    }

    if (!this_player()->query_prop(BUNK_PROP))
    {
        if (query_verb() != "get")
        {
            notify_fail("You are already on your feet.\n");
        }

        return 0;
    }

    write("You get up from the bunk. Ahh ... that felt good.\n");
    say(QCTNAME(this_player())
          + " gets up from the bunk " + this_player()->query_pronoun()
      + " was lying on.\n");
    this_player()->remove_prop(BUNK_PROP);
    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);

    return 1;
} /* rise */


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 *
 * This function is redefined to force players to stand up before
 * leaving if they are currently lying on a bunk.
 */
public void
leave_inv(object ob, object to)
{
    object   oldtp;

    ::leave_inv(ob, to);
   
    if(!objectp(to) || !objectp(ob))
    {
        return;
    }

    oldtp = this_player();
    set_this_player(ob);

    if (this_player()->query_prop(BUNK_PROP))
    {
        write("You get up from the bunk before leaving.\n");
        tell_room(this_object(), "(having gotten up from the"
          + " bunk first.)\n");
        this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
        this_player()->remove_prop(BUNK_PROP);
    }

    set_this_player(oldtp);
} /* leave_inv */



/*
 * Function name:        start
 * Description  :        Allow guild members to start here
 * Arguments    :        string str -- what was typed following the verb
 * Returns      :        1 -- they tried to start here, 0 -- no arg
 */
public int
start(string str)
{
    notify_fail("Start here? If you want to, just <bunk here>.\n");

    if (!strlen(str))
    {
        return 0;
    }

    if (str != "here")
    {
        return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
        write("Only Mercenaries are welcome to bunk here!\n");
        return 1;
    }

    if (this_player()->query_default_start_location() ==
        GUILD_STARTLOC)
    {
        notify_fail("You've already got yourself a bunk here."
          + " No need to reestablish that.\n");
        return 0;
    }

    if (this_player()->set_default_start_location(GUILD_STARTLOC))
    {
        write("You find a bunk that isn't already occupied, and"
          + " make it your own. Ahh ... its good to have a place"
          + " to rest your head after a long day of adventure.\n\n"
          + "You will start here when you enter the realms from"
          + " now on.\n");
    }
    else
    {
        write("Sorry, some problem prevents you from starting here."
          + " Please mail Gorboth at once!\n");
    }

    return 1;
} /* start */


/*
 * Function name:        wake_cook
 * Description  :        allow players to try to wake the cook if
 *                       he is sleeping
 * Arguments    :        string arg - what was typed following the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
wake_cook(string arg)
{
    mixed    cook;

    if (!strlen(arg))
    {
        /* No fail msg necessary. This is handled with a cmd_item above */
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [sleeping] [slow] [glassy] [eyed] [glassy-eyed]"
      + " 'cook'"))
    {
        return 0;
    }

    cook = (present("_merc_guild_cook", this_object()));

    if (!cook)
    {
        notify_fail("The cook isn't even here!\n");
        return 0;
    }

    if (!cook->query_prop(BUNK_PROP))
    {
        notify_fail("The cook doesn't appear to be sleeping.\n");
        return 0;
    }

    write("You roughly shake the shoulder of the sleeping cook.\n");
    say(QCTNAME(this_player()) + " walks over and wakes up the cook.\n");

    cook->wake_me();

    return 1;
} /* wake_cook */