/*
 *  /d/Emerald/herbs/darkroot.c
 *
 *  This root is unique to Emerald, and grows in forests which
 *  are not visited by the Elves. These roots remember the
 *  times of Darkness, when Val-Shoreil ruled the lands, and
 *  they contain a portion of his former influence. When
 *  chewed, they produce a room-darkening affect for a very
 *  brief time. Once chewed, they are destroyed, and they
 *  can only be chewed if fresh.
 *
 *  Copyright (c) March 2002, by Cooper Sherry (Gorboth)
 */
#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>

/* prototypes */
public void        create_herb();
public void        special_effect();


/*
 * Function name:        create_herb
 * Description  :        set up the herb
 */
public void
create_herb()
{
    set_name("root");
    set_adj( ({ "pitch", "black" }) );
    set_herb_name("darkroot");
    set_short("pitch black root");
    set_pshort("pitch black roots");
    set_ingest_verb("chew");
    set_unid_long("This root is thick, and deep black in color. Thin,"
                + " hairlike strands extend from the main heft of the"
                + " root.\n");
    set_id_long("This is a thick section of Darkroot, which is spoken"
              + " of in the legends of Emerald. Found only in forests"
              + " which have been forgotten by the Elves, these roots"
              + " exist beneath trees which are old enough to"
              + " remember the days before the coming of Telan-Ri -"
              + " days in which Darkness ruled the land. Some claim"
              + " that the roots yet possess a portion of"
              + " that ancient darkness, waiting for a chance to"
              + " release it once again.\n");
    set_herb_value(2000);
    set_id_diff(50);
    set_find_diff(7);
    set_effect(HERB_SPECIAL, "", 0);
    set_decay_time(9000); /* roots do not dry easily */
    set_dryable();
} /* create_herb */


/*
 * Function name:        special_effect
 * Description  :        if the herb is fresh, we clone the darkness
 *                       object into the player's inventory. If not,
 *                       we tell the player how unpleasant the experience
 *                       of chewing a dried darkroot is.
 */
public void
special_effect()
{
    object darkness;

    if (query_dried())
    {
        write("You place the root in your mouth and begin to chew. The"
            + " fibers are so dry and hard, that you can hardly move your"
            + " teeth through them at first. You persist, and chew the"
            + " root into a dark paste, which turns your tongue black,"
            + " and leaves a taste in your mouth that is more unpleasant"
            + " than you can stand. Disgusted, you spit the pulpy mass"
            + " you have created to the ground, where it is lost.\n");

        return;
    }

    if (darkness = present("em_darkroot_pulp", this_player()))
    {
        darkness->extend_duration();

        write("With your mouth still coated with the thick pulp from " +
              "a previous root, you place a fresh one in your mouth and " +
              "begin to chew. As you do so, you taste its muted flavor " +
              "as the fibers fall to pieces between your teeth, the dark " +
              "pulp recoating your mouth and lips.\n");
        return;
    }

    darkness = clone_object("/d/Emerald/herbs/darkroot_pulp");
    darkness->move(this_player(), 1);

    write("You place the root in your mouth and begin to chew. As you"
        + " do so, a strange taste floods over your tongue as the"
        + " fibers fall to pieces between your teeth. Darkness rises"
        + " from your lips, and floods the area.\n");
    tell_room(environment(this_player()),
        "The area is suddenly filled with thick darkness!\n");

    return;
} /* special_effect */
