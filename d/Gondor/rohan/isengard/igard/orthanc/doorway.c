/*
 *  ORTHANC + "doorway.c"
 *
 *  Isle of rock at the base of Orthanc.
 *
 *  Last modified by Alto, 19 October 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/binbit.c";

#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <tasks.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"
#include "/d/Gondor/bits.h"

inherit IGARD_LIB + "igard_funcs.c";

public void        create_gondor();
public string      long_desc();
public int         summon_saruman();

object             actor, *inv;

public void
create_gondor()
{
    set_short("At the great door of Orthanc");
    set_long(&long_desc());

    sky_add_items();
    outside_add_items();
    plain_add_items();

    add_item(({"room", "area", "surroundings", "threshold", "place",
        "landscape"}), long_desc);

    add_item(({"stair", "stairs", "steps", "flight", "broad stairs"}),
        "Falling away from the tower to the west is a broad flight of "
        + "twenty-seven stairs. They look extremely inviting.\n");
    add_item(({"door", "great door"}), "The great door is made from "
        + "iron and looms far over your head. It looks entirely "
        + "indestructable, just like the tower it opens into.\n");
    add_item(({"window", "shuttered window"}), "Above the great door "
        + "there is a large window. It is closed behind two large iron "
        + "shutters.\n");
    add_item(({"shutter", "shutters", "iron shutter", "iron shutters"}),
        "The window is closed by two large iron shutters. Even if you could "
        + "somehow find purchase enough to climb to them, it would take "
        + "gargantuan strength to even dent them, let alone open them from "
        + "the outside.\n");
    add_item(({"balcony"}), "Over the door is a balcony, from which the "
        + "master of Orthanc can stand and gaze into the eastern sky. "
        + "It is fenced along its length by sturdy iron bars.\n");
    add_item(({"bar", "bars", "iron bar", "iron bars", "sturdy iron bars"}),
        "The balcony below the window is fenced with sturdy iron bars.\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(ORTHANC + "entrance_stair",  "east");

    reset_room();
}


string
long_desc()
{
    return "You stand upon the threshold of the great door of Orthanc, "
      + "called Mount Fang by the Men of the West, although the word means "
      + "'the cunning mind' among the Rohirrim. Over the door is a shuttered "
      + "window, opening upon a balcony hedged with iron bars."
      + sky_desc() + " Falling away to the east is a flight of twenty-seven "
      + "broad stairs, hewn by some unknown art of the gleaming black stone "
      + "of Isengard. Something not quite tangible, like a breath of "
      + "malice and brooding, radiates from the tower.\n";
}


public int
reward_courier()
{
    string  who = TP->query_real_name();

    if (!present(who, TO))
        return 1;

    if (TP->test_bit("gondor", IGARD_GROUP, IGARD_COURIER_BIT))
        return 1;

    TP->set_bit(IGARD_GROUP, IGARD_COURIER_BIT);
    TP->add_exp_quest(IGARD_COURIER_EXP);
    TP->catch_msg("You feel more experienced!\n");
    TP->remove_prop(GOODIE_IGARD_QUEST);
    TP->remove_prop(BADDIE_IGARD_QUEST);
    TP->remove_prop(FINISHED_IGARD_WALL);
    TP->remove_prop(FINISHED_FURNACE_IGARD);
    TP->remove_prop(FINISHED_ORCWARG_IGARD);
    TP->remove_prop(FINISHED_IGARD_CAVERNS);
    TP->remove_prop(SENT_IGARD_ORTHANC);
    LOG_QUEST(TP, IGARD_COURIER_EXP, "IGARD COURIER QUEST");

    return 1;
}


public int
summon_saruman()
{
    actor = TP;
    inv = all_inventory(TP);

    if ((!SIO) && (!WIZARD))
    {
        actor->catch_tell("A sneering voice from above shouts: You have no "
            + "business here, cur! Begone!\n"
            + "Light and wind suddenly explode around you.\n");
        tell_room(environment(actor), "A sneering voice from above shouts: "
            + "You have no business here, cur! Begone!\n"
            + QCTNAME(actor) + " is blown high into the air as light and "
            + "wind suddenly explode around " + HIM_HER(actor) + "!\n", 
            ({actor}));

        actor->move_living("M", IGARD_ROOM + "catapult_room.c", 1, 0);

        return 1;
    }


    if (actor->test_bit("gondor", IGARD_GROUP, IGARD_COURIER_BIT))
    {
        actor->catch_tell("A sneering voice from above shouts: I want no more "
            + "from you, puppy! Begone!\n"
            + "Light and wind suddenly explode around you.\n");
        tell_room(environment(actor), "A sneering voice from above shouts: "
            + "I want no more from you, puppy! Begone!\n"
            + QCTNAME(actor) + " is blown high into the air as light and "
            + "wind suddenly explode around " + HIM_HER(actor) + "!\n", 
            ({actor}));

        actor->move_living("M", IGARD_ROOM + "catapult_room.c", 1, 0);

        return 1;
    }


    if (sizeof(filter(inv, &->id("_igard_courier_missive_"))))
    {
        actor->catch_tell("A sneering voice from above shouts: You are late, "
            + "dog. Where have you been? Take your reward "
            + "and begone ere you learn the displeasure of Saruman to "
            + "your unending dismay.\n"
            + "A few mumbled incantations from above bring a sudden snap "
            + "of wind through the area. The missive is snatched from your "
            + "hand and blown up and over the balcony.\n");
        tell_room(environment(actor), "A sneering voice from above shouts: "
            + "You are late, "
            + "dog. Where have you been? Take your reward "
            + "and begone ere you learn the displeasure of Saruman to "
            + "your unending dismay.\n"
            + "A few mumbled incantations from above bring a sudden snap "
            + "of wind through the area. A small missive is snatched from "
            + "the hand of " + QTNAME(actor) + " and blown up and over the "
            + "balcony.\n", ({actor}));
        actor->command("drop missive");

        actor->catch_msg("\nYou feel rather wicked for betraying King Theoden!\n");
        actor->adjust_alignment(-1000);
        reward_courier();
        return 1;
    }


    if (sizeof(filter(inv, &->id("_igard_prisoner_missive_"))))
    {
        actor->catch_tell("A sneering voice from above shouts: Ahh, I have "
            + "been waiting for this. Waiting overlong, in fact! At last I "
            + "shall rid myself of the Rohirrim dogs. Now begone and leave "
            + "me to my thoughts!\n"
            + "A few mumbled incantations from above bring a sudden snap "
            + "of wind through the area. The missive is snatched from your "
            + "hand and blown up and over the balcony.\n");
        tell_room(environment(actor), "A sneering voice from above shouts: "
            + "Ahh, I have "
            + "been waiting for this. Waiting overlong, in fact! At last I "
            + "shall rid myself of the Rohirrim dogs. Now begone and leave "
            + "me to my thoughts!\n"
            + "A few mumbled incantations from above bring a sudden snap "
            + "of wind through the area. A small missive is snatched from "
            + "the hand of " + QTNAME(actor) + " and blown up and over the "
            + "balcony.\n", ({actor}));
        actor->command("drop missive");

        actor->catch_msg("\nYou feel rather good about robbing Isengard of "
            + "victory!\n");
        actor->adjust_alignment(1000);
        reward_courier();
        return 1;
    }


    if (WIZARD)
    {
        actor->catch_tell("A condescending voice from above says: Welcome, "
            + "lesser colleague of mine. You would do well to heed the "
            + "counsel of Saruman the Wise. Have you come seeking it?\n");
        tell_room(environment(actor), "A condescending voice from above "
            + "says: Welcome, "
            + "lesser colleague of mine. You would do well to heed the "
            + "counsel of Saruman the Wise. Have you come seeking it?\n", 
            ({actor}));
        return 1;
    }

    else
    {
        actor->catch_tell("A sneering voice from above shouts: You have no "
            + "business here, cur! Begone!\n"
            + "Light and wind suddenly explode around you.\n");
        tell_room(environment(actor), "A sneering voice from above shouts: "
            + "You have no business here, cur! Begone!\n"
            + QCTNAME(actor) + " is blown high into the air as light and "
            + "wind suddenly explode around " + HIM_HER(actor) + "!\n", 
            ({actor}));

        actor->move_living("M", IGARD_ROOM + "catapult_room.c", 1, 0);

        return 1;
    }

    return 1;
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
     {
         set_alarm(5.0, 0.0, &summon_saruman());
         sky_add_items();
     }

    if(ob->id("_igard_prisoner_missive_") || ob->id("_igard_courier_missive_"))
    {
         ob->remove_object();
    }
}

