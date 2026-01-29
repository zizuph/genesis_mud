/*
 * /d/Sparkle/area/city/bank/room/vault_gem.c
 *
 * This is the gem vault
 * of the Gnomes of Genesis in Sparkle.
 *
 * Created Feb 2009, by Aeg (Matthew Morin)
 * Machine honours to Gorboth (Cooper Sherry)
 */
 
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

inherit BANK_ROOM + "bank_standard";

/* Prototypes */

/*
 * Function name:           create_bank_room
 * Description  :           Creates a room with bank settings
 */
public void
create_bank_room()
{
    object  lever1;
    object  lever2;
    object  tube;
    object  tube2;
    object  gear1;
    object  gear2;
    object  gear3;
    object  gear4;
    object  gear5;
    object  gear6;
    object  gear7;
    object  gear8;
    object  screw1;
    object  screw2;
    
    set_short("Gem vault");
    set_long("This vault is a square room with shelves and cabinets lining "
        + "the walls. The floor and ceiling are made of granite slabs and the "
        + "walls are made of red bricks. Seemingly countless gems are in "
        + "piles on the shelves and on the floor. The exit, to the southwest, "
        + "is a heavy circular door with many levers, gears and buttons.\n\n");

    add_item( ({ "vault", "room", "area" }),
          "This vault is a square room with gem-filled shelves and cabinets "
        + "lining the walls.\n");
        
    add_item( ({ "gem", "gems", "pile", "piles", "heap", "heaps", }),
          "Heaps and piles of gems fill the shelves and "
        + "litter the floor.\n");
        
    add_item( ({ "floor", "ground", "slabs", "granite", "granite slabs" }),
          "The granite slab floor is cold to the touch. It seems thick and "
        + "each slab appears to be very heavy. The ground is littered with "
        + "gems of all type. Two glass tubes stick out from the "
        + "ground.\n");
    
    add_item( ({ "shelves", "shelf", "cabinets", "cabinet" }),
          "The shelves and cabinets are filled to the brim with gems.\n");
        
    add_item( ({ "bricks", "brick", "red bricks", "red brick" }),
          "The bricks are a rich, red colour and seem very thick.\n");
           
    add_item( ({ "walls", "north wall", "northwest wall", "west wall",
                 "south wall", "east wall", "southeast wall",
                 "northeast wall", "northern wall", "northwestern wall",
                 "western wall", "southern wall", "eastern wall",
                 "southeastern wall", "northeastern wall" }),
          "The walls are made of red bricks. They are lined with gem-filled "
        + "shelves and heavy cherry cabinets.\n");
        
    add_item( ({ "southwest wall", "southwestern wall", "door", "vault door",
                 "exit", "circular door", "heavy door", 
                 "heavy circular door" }),
          "The door is a complex gnomish device. You see multiple levers and "
        + "buttons, seemingly countless gears and a whistle or eight.\n");
        
    add_item( ({ "lever", "levers", "button", "buttons", "gears", "gear", 
                 "whistle", "whistles" }),
          "No gnomish device would work without one of these! No gnome "
        + "would be happy with just one...\n");
        
    add_item( ({ "ceiling" }),
          "The ceiling is made of solid-looking, granite slabs. It looks "
        + "impenetrable.\n");
    
    setuid();
    seteuid(getuid());
    
    
    
    lever1   = clone_object(BANK_OBJ + "steering_wheel");
    lever2   = clone_object(BANK_OBJ + "steering_wheel");
    tube    = clone_object(BANK_OBJ + "tube");
    tube2   = clone_object(BANK_OBJ + "tube");
    gear1   = clone_object(BANK_OBJ + "gear");
    gear2   = clone_object(BANK_OBJ + "gear");
    gear3   = clone_object(BANK_OBJ + "gear");
    gear4   = clone_object(BANK_OBJ + "gear");
    gear5   = clone_object(BANK_OBJ + "gear");
    gear6   = clone_object(BANK_OBJ + "gear");
    gear7   = clone_object(BANK_OBJ + "gear");
    gear8   = clone_object(BANK_OBJ + "gear");
    screw1  = clone_object(BANK_OBJ + "screw");
    screw2  = clone_object(BANK_OBJ + "screw");

    gear1->set_no_show_composite(1);
    gear2->set_no_show_composite(1);
    gear3->set_no_show_composite(1);
    gear4->set_no_show_composite(1);
    gear5->set_no_show_composite(1);
    gear6->set_no_show_composite(1);
    gear7->set_no_show_composite(1);
    gear8->set_no_show_composite(1);
    screw1->set_no_show_composite(1);
    screw2->set_no_show_composite(1);
    tube->set_no_show_composite(1);
    tube2->set_no_show_composite(1);
        
    lever1->set_next_machine(gear1);
    gear1->set_next_machine(gear3);
    gear3->set_next_machine(gear5);
    gear5->set_next_machine(gear7);
    gear7->set_next_machine(screw1);
    
    lever2->set_next_machine(gear2);
    gear2->set_next_machine(gear4);
    gear4->set_next_machine(gear6);
    gear6->set_next_machine(gear8);
    gear8->set_next_machine(screw2);
    
    lever1->set_adj( ({ "green", "steering" }) );
    lever2->set_adj( ({ "polished", "steering" }) );

    gear1->set_adj( ({ "large", "nickel" }) );
    gear3->set_clockwise(1);
    gear3->set_adj( ({ "small", "nickel" }) );
    gear5->set_adj( ({ "medium", "nickel" }) );
    gear7->set_clockwise(1);
    gear7->set_adj( ({ "average", "nickel" }) );
    screw1->set_adj( ({ "long", "nickel" }) );
    
    gear2->set_adj( ({ "large", "bronze" }) );
    gear4->set_clockwise(1);
    gear4->set_adj( ({ "small", "bronze" }) );
    gear6->set_adj( ({ "medium", "bronze" }) );
    gear8->set_clockwise(1);
    gear8->set_adj( ({ "average", "bronze" }) );
    screw2->set_adj( ({ "long", "bronze" }) );
    
    gear1->set_f_delay(0);
    gear1->set_b_delay(0);
    gear2->set_f_delay(0);
    gear2->set_b_delay(0);
    gear3->set_f_delay(0);
    gear3->set_b_delay(0);
    gear4->set_f_delay(0);
    gear4->set_b_delay(0);
    gear5->set_f_delay(0);
    gear5->set_b_delay(0);    
    gear6->set_f_delay(0);
    gear6->set_b_delay(0);
    gear7->set_f_delay(0);
    gear7->set_b_delay(0);
    gear8->set_f_delay(0);
    gear8->set_b_delay(0);
    screw1->set_f_delay(0);
    screw1->set_b_delay(0);
    screw2->set_f_delay(0);
    screw2->set_b_delay(0);
    
    tube->move(this_object());
    tube2->move(this_object());
    lever1->move(this_object());
    lever2->move(this_object());
    gear1->move(this_object());
    gear2->move(this_object());
    gear3->move(this_object());
    gear4->move(this_object());
    gear5->move(this_object());
    gear6->move(this_object());
    gear7->move(this_object());
    gear8->move(this_object());
    screw1->move(this_object());
    screw2->move(this_object());
        
    /* Exits */
    add_exit(BANK_ROOM + "guard_room", "southwest", 0);

    
} /* create_bank_room */
