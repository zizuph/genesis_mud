/*
 *  /d/Sparkle/area/city/obj/gnome/test_room.c
 *
 *  A room in which to test the mechanics of the gnomish machinery.
 *
 *  Created October 2008, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/room";

/* Definitions */
#define            THE_DIR ("/d/Sparkle/area/city/obj/gnome/")

/* Prototypes */
public void        create_room();


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    object    lever;
    object    gear1;
    object    gear2;

    set_short("a test chamber");
    set_long("This is a test chamber for Gnomish machinery. Beware!\n");

    setuid();
    seteuid(getuid());

    lever = clone_object(THE_DIR + "steering_wheel");
    gear1 = clone_object(THE_DIR + "3_position_shaft");
    gear2 = clone_object(THE_DIR + "3_position_shaft");

    lever->set_next_machine( ({ gear1, gear2 }) );

    gear2->set_adj( ({ "large", "copper" }) );
    gear1->set_adj( ({ "small", "silver" }) );

    lever->move(this_object());
    gear1->move(this_object());
    gear2->move(this_object());
} /* create_room */