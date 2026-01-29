/*
 *  /d/Emerald/blackwall/delrimmon/obj/disc.c
 *
 *  Satherel gives this object to players who accept his quest to
 *  go and find Rillian. It's enchantment allows Satherel to
 *  project his mind to the location of the disc.
 *
 *  Copyright (c) June 2002, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"


/* prototypes */
public void        create_object();
public string      describe_disc();
public mixed       test_giveaway();
public int         do_incant(string arg);
public void        init();
public void        focus(object player);
public void        summon_satherel(object player);
public void        satherel_assessment(object player);
public void        end_glow(object player);
public void        get_lost();

/* global variables */
public int        Glowing = 0;



/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("disc");
    add_name("_rillian_finder");
    add_name( ({ "stone" }) );
    add_adj( ({ "polished", "stone" }) );

    set_short("polished stone disc");
    set_long(describe_disc);

    add_item( ({ "symbol", "strange symbol", "rune" }),
        "A rune of some kind has been carved into one side of the"
      + " polished stone disc. It is unclear what it might mean.\n");

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_M_NO_INS, "A strange magical force prevents the"
      + " disc from fitting there.\n");
    add_prop(OBJ_M_NO_GIVE, test_giveaway);
//  add_prop(OBJ_M_NO_DROP, test_giveaway);
    add_prop(OBJ_M_NO_STEAL, "Just as your fingers touch the disc,"
      + " a strange feeling comes over you, and you reconsider your"
      + " action.\n");
} /* create_object */


/*
 * Function name:        describe_disc
 * Description  :        provide the long description, variable based
 *                       on whether the disc is glowing.
 * Returns      :        string - the long description
 */
public string
describe_disc()
{
    string desc = "The blue stone of this disc has been polished so"
                + " that its sides gleam. A strange symbol has been"
                + " carved into one of the two sides. ";

    if (Glowing)
    {
        desc += "The disc is glowing brightly!";
    }

    return desc + "\n";
} /* describe_disc */


/*
 * Function name:        test_giveaway
 * Description  :        only satherel can give the disc to people
 * Returns      :        mixed - 0, satherel holds it, so give it away
 *                               string fail message otherwise
 */
public mixed
test_giveaway()
{
    if (environment(this_object())->query_real_name() == "satherel")
    {
        return 0;
    }

    return "You think about getting rid of the stone disc, and then"
         + " remember that you have things to accomplish with it.\n";
} /* test_giveaway */


/*
 * Function name:        do_incant
 * Description  :        allow the player to trigger the enchantment
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - otherwise
 */
public int
do_incant(string arg)
{
    if (!strlen(arg))
    {
        NFN0("What do you wish to incant?");
    }

    if (arg == "iffinde" ||
        arg == "iffinde!")
    {
        write("You incant: Iffinde!\n");

        if (Glowing)
        {
            this_player()->catch_msg("You have already triggered the"
              + " enchantment within the disc. Your incantation has no"
              + " effect.\n");

            return 1;
        }

        Glowing = 1;
        set_alarm(3.0, 0.0, &focus(this_player()));

        return 1;
    }

    return 0; /* can't parse it ... */
} /* do_incant */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    if (this_player() != environment() ||
        this_player()->query_real_name() == "satherel")
    {
        return;
    }

    if (!this_player()->query_wiz_level())
    {  
    
        setuid();
        seteuid(getuid());
        if (!MANAGER->query_rillian(this_player()))
        {
            set_alarm(1.0, 0.0, get_lost);
            return;
        }
    }

    add_action(do_incant, "incant");
} /* init */


/*
 * Function name:        focus
 * Description  :        trigger the enchantment
 * Arguments    :        object player - the player
 */
public void
focus(object player)
{

    setuid();
    seteuid(getuid());
    if (!MANAGER->query_rillian(player) ||
         MANAGER->query_rillian(player) == "Complete")
    {
        set_alarm(1.0, 0.0, get_lost);
        return;
    }

    player->catch_msg("The stone disc begins suddenly to glow!\n");
    set_alarm(5.0, 0.0, &summon_satherel(player));

    return;
} /* focus */


/*
 * Function name:        summon_satherel
 * Description  :        satherel responds to the enchantment
 * Arguments    :        object player - the player
 */
public void
summon_satherel(object player)
{
    setuid();
    seteuid(getuid());
    if (MANAGER->query_rillian(player) == "Found")
    {
        player->catch_msg("You feel the presence of Satherel in your"
          + " mind. His thoughts speak to you: Why do you use the"
          + " disc? You have already aided me as much as you are able."
          + " Return now to me, and I shall reward you.\n");

        set_alarm(5.0, 0.0, &end_glow(player));
        return;
    }

    if (present("satherel", environment(environment(this_object()))))
    {
        write("The voice of Satherel speaks in your mind: The disc"
          + " is not a plaything. Do not use it without purpose.\n");
        write("The tall regal elf glares at you stonily.\n");

        set_alarm(5.0, 0.0, &end_glow(player));
        return;
    }

    player->catch_msg("You feel the presence of Satherel in your mind."
      + " His thoughts speak to you: I have fixed on your location."
      + " Give me a moment to focus on the area.\n");
    set_alarm(7.0, 0.0, &satherel_assessment(player));

    /* find a way to make the npc respond to these things? */
    return;
} /* summon_satherel */


/*
 * Function name:        satherel_assessment
 * Description  :        satherel determines if this room has any
 *                       bearing on the Rillian mystery
 * Arguments    :        object player - the player
 */
public void
satherel_assessment(object player)
{
    if (environment(player)->id("_torque_quest_rillian_chamber"))
    {
        player->catch_msg("Satherel speaks in your mind: Alas! It is"
          + " no different than the things I have seen through"
          + " others. There is a strange darkness which hangs in"
          + " your location. I definitely sense a presence, which"
          + " is very likely that of Rillian. However, it is not"
          + " possible for me to be sure. You have done enough for"
          + " me, and I thank you for that. Return to me, and I will"
          + " reward you as I am able.\n");

        setuid();
        seteuid(getuid());
        MANAGER->set_rillian(player, "Found");


    }
    else
    {
        player->catch_msg("Satherel speaks in your mind: I sense"
          + " nothing which leads me to believe that Rillian is at"
          + " your current location.\n");
    }

    set_alarm(5.0, 0.0, &end_glow(player));

    return;
} /* satherel_assessment */


/*
 * Function name:        end_glow
 * Description  :        cause the enchantment in the disc to fade
 * Arguments    :        object player - the player
 */
public void
end_glow(object player)
{
    player->catch_msg("The glow in the stone disc fades away.\n");
    Glowing = 0;

    return;
} /* end_glow */


/*
 * Function name:        leave_env
 * Description  :        since this is such a sensitive quest
 *                       item, we break it if it is dropped
 *                       or put in something
 * Arguments    :        object from - where it came from
 *                       object to   - where it went
 */
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (!objectp(from) || !objectp(to) || !living(from))
        return;

    if (!to->query_prop(ROOM_I_IS))
    {
        return;
    }


    tell_room(to, "The " + TO->short() + " shatters into a million"
      + " tiny pieces as it hits the ground!\n");
    set_alarm(0.0, 0.0, "remove_object");
} /* leave_env */


/*
 * Function name:        query_auto_load
 * Description  :        players may keep this item over multiple
 *                       logins
 * Returns      : string - the filename of this module.
 */
public string
query_auto_load()
{
    return MASTER + ":";
} /* query_auto_load */


/*
 * Function name:        get_lost
 * Description  :        remove the object if the player should
 *                       not have it
 */
public void
get_lost()
{
    write("The polished stone disc pulses brilliantly, and"
        + " disappears!\n");

    remove_object();
} /* get_lost */


