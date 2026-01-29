/*
 *  /d/Emerald/herbs/rotbloom.c
 *
 *  These fungi are unique to Emerald. They harken to a time before
 *  the coming of the Elves, when Val-Shoreil ruled the land with
 *  darkness and chaos. When squeezed, these herbs produce a noxious
 *  odor, which can nauseate a target player and ruin their appetite
 *  for a time.
 *
 *  Copyright (c) July 2004, by Cooper Sherry (Gorboth)
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
    set_name("fungus");
    add_name( ({ "rotbloom" }) );
    set_adj( ({ "green", "soggy", "moist", "brown", "brownish",
                "pungent", "stinky", "smelly" }) );
    set_herb_name("rotbloom");
    set_short("soggy green fungus");
    set_pshort("soggy green fungi");
    set_ingest_verb("squeeze");
    set_unid_long("This piece of fungus is brownish green, moist, and"
                + " incredibly pungent. The stench coming from its"
                + " soggy fibers is almost too much to bear.\n");
    set_id_long("This section of fungus appears to have been ripped"
              + " from the bark of a tree. Its soggy fibers ooze a"
              + " dark and fetid liquid which is among the most foul"
              + " things you have ever smelt. This is a segment of"
              + " Rotbloom, which is known for its nauseating odors,"
              + " especially when squeezed.\n");
    set_herb_value(2000);
    set_id_diff(50);
    set_find_diff(7);
    set_effect(HERB_SPECIAL, "", 0);
    set_decay_time(4000); /* This thing traps its moisture well */
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
    object       rot_cloud;

    if (query_dried())
    {
        write("You squeeze the dried crust of fungus in your hand, where"
            + " it crumbles like wormwood between your fingers and blows"
            + " away in the wind.\n");

        return;
    }

    rot_cloud = clone_object("/d/Emerald/herbs/rotbloom_cloud");
    rot_cloud->move(this_player());

    write("As you squeeze the fungus in your palm, a dark cloud of"
        + " vapor erupts from its pores. You find yourself stiffening"
        + " at its odor, barely daring to inhale. You feel an urge"
        + " to blow the cloud away from you.\n");
    tell_room(environment(environment(this_object())),
        "A small, dark brown cloud of vapor suddenly appears.\n");

    return;
} /* special_effect */
