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
    object    gear3;
    object    beam1;
    object    gear4;
    object    gear5;

    set_short("a test chamber");
    set_long("This is a test chamber for Gnomish machinery. Beware!\n");

    setuid();
    seteuid(getuid());

    lever = clone_object(THE_DIR + "steering_wheel");
    gear1 = clone_object(THE_DIR + "gear");
    gear2 = clone_object(THE_DIR + "gear");
    gear3 = clone_object(THE_DIR + "gear");
    beam1 = clone_object(THE_DIR + "beam");
    gear4 = clone_object(THE_DIR + "gear");
    gear5 = clone_object(THE_DIR + "gear");

    lever->set_next_machine(gear1);
    gear1->set_next_machine(gear2);
    gear2->set_next_machine(gear3);
    gear3->set_next_machine(beam1);
    beam1->set_next_machine(gear4);
    gear4->set_next_machine(gear5);
    
    gear2->set_prev_machine(gear1);
    gear3->set_prev_machine(gear2);
    beam1->set_prev_machine(gear3);
    gear4->set_prev_machine(beam1);
    gear5->set_prev_machine(gear4);

    gear2->set_clockwise(1);
    gear2->set_adj( ({ "large", "copper" }) );
    gear1->set_adj( ({ "small", "silver" }) );
    gear3->set_adj( ({ "medium", "bronze" }) );
    beam1->set_adj( ({ "long", "warped" }) );
    gear4->set_adj( ({ "average", "nickel" }) );
    gear5->set_clockwise(1);
    gear5->set_adj( ({ "giant", "iron" }) );

    gear1->set_f_delay(0);
    gear1->set_b_delay(0);
    gear2->set_f_delay(0);
    gear2->set_b_delay(0);
    gear3->set_f_delay(0);
    gear3->set_b_delay(0);
    beam1->set_f_delay(0);
    beam1->set_b_delay(0);
    gear4->set_f_delay(0);
    gear4->set_b_delay(0);
    gear5->set_f_delay(0);
    gear5->set_b_delay(0);

    lever->move(this_object());
    gear1->move(this_object());
    gear2->move(this_object());
    gear3->move(this_object());
    beam1->move(this_object());
    gear4->move(this_object());
    gear5->move(this_object());
    
} /* create_room */
