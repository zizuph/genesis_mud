/* /d/Faerun/sunken_ruins/rooms/bountiful.c
 *
 * Nerull 2019
 *
 */
 
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "defs.h";

inherit STD_SUNKEN_OUTDOOR;

int position;
int direction;
int events;
int boarding_on;


string sea()
{
    if (position == 1)
    {
        return "Far to the east you see the coastline of the "
            +"mainland. Open sea with rolling waves and seagulls "
            +"pride the view in all other direction, giving you "
            +"a feeling of tranquility.\n";
    }
    
    if (position == 2)
    {
        return "There is no land or islands in sight. Accompanued "
            +"with only the high waves crashing into the front and "
            +"sides of the ship, you sort of feel isolated. The sea "
            +"parts only at the visible horizon.\n";
    }
    
    if (position == 3)
    {
        return "The sea is particulary unfriendly in this area, "
            +"causing the ship to roll heavily each time waves "
            +"crash into one of the sides. There is no land in "
            +"sight.\n";
    }
    
    if (position == 4 || position == 5 || position == 6)
    {
        return "High waves crash into the side of the ship with "
            +"great force. You sense droplets of seawater in "
            +"your face and on your hands. The dark waters "
            +"below looks both tempting and frigthening "
            +"at the same time. There is no land in sight.\n";
    }
    
    if (position == 7)
    {
        return "The sea is suprisingly calm here, as if the ship "
            +"were sailing into a silent port. There are no other ships, "
            +"islands or land in sight.\n";
    }
    
    if (position == 8)
    {
        return "Far into the west, you spot a group of islands. Dark "
            +"canopy of clouds hanging over the islands gives them a purple "
            +"haze. The sea with foaming waves creates a spectacular nice "
            +"view.\n";
    }
    
    if (position == 9)
    {
        return "Far into the southwest, you spot a group of islands. Dark "
            +"canopy of clouds hanging over the islands gives them a purple "
            +"haze. The sea is definitely calmer here, and particulary "
            +"soothing for the soul...\n";
    }
    
    if (position == 10)
    {
        return "you are in the middle of the sea at a good distance from "
            +"purple-hazed islands. The sea is relatively calm with some "
            +"nice rolling waves that hugs the side of the ship.\n";
    }
    
    return "Beyond the deck of the Bountiful you see trees, vegetation "
        +"and a rocky beach to the east and open but calm sea to "
        +"the west. The coastline from this position"
        +"covers a large variety of rocks and beaches from north "
        +"to south as far as the eye can see. You believe it's safe "
        +"to disembark the ship if your intention is to get back to "
        +"the mainland of the Sword Coast.\n";
}


int move_events()
{
    seteuid(getuid());
    //events = events + 1;
    
    object bountiful_sh, bountiful_se;
    
    // Sailing from the Swordcoast
    if (direction == 1)
    {
        position = position + 1;
        
        tell_room(this_object(), "Sailing to the Purple islands.\n");
    }
    
     // Sailing to the Swordcoast
    if (direction == 0)
    {
        position = position - 1;
        
        tell_room(this_object(), "Sailing to Swordcoast.\n");
    }
    
    // Destination position in the middle of the sea
    // where players can disembark and jump into the 
    // sea, or climb onboard.
    if (position == 0)
    {
        boarding_on = 1;
        
        tell_room(this_object(), "Disembark, Swordcoast!\n");
		
		tell_room(DEFAULT_DIR + "rooms/beach", "A three masted frigate "
		+"sails in from the west and stops at the white beach.\n");
        
        if (direction != 1)
        {
            direction = 1;
        }
        
        bountiful_sh = clone_object(DEFAULT_DIR 
        + "obj/bountiful_shore")->move(DEFAULT_DIR + "rooms/beach", 1);
        
        //set_alarm(30.0, 0.0, &bountiful_sh->remove_me());
    }
    
    if (position == 10)
    {
        boarding_on = 1;
        
        tell_room(this_object(), "Disembark, Sunken city.\n");
		
		tell_room(DEFAULT_DIR + "rooms/ow1", "A three masted frigate "
		+"sails in from the southeast and stops here.\n");
        
        if (direction != 0)
        {
            direction = 0;
        }

        bountiful_se = clone_object(DEFAULT_DIR 
        + "obj/bountiful_sea")->move(DEFAULT_DIR + "rooms/ow1", 1);
 
        //set_alarm(30.0, 0.0, &bountiful_se->remove_me());
    }
    
    return 1;
}


void
create_sunken_outdoor()
{
    set_short("On the deck of the ship Bountiful");
    
    set_extraline("Standing out in the open air of the deck on the "
        +"ship the Bountiful, you can see the city of Martira bay to "
        +"one side and the open Sea of Sorrows on the other. This "
        +"frigate has three masts with massive "
        +"sails. Open deck has some of the larger cannons and "
        +"cannon balls strapped in place and ready "
        +"for use. At one end of the deck lies the rudder and "
        +"steering wheel while at the the other lies the bow "
        +"of the ship with it's ghastly skeletal figurehead.\n");
    
    add_item( ({"sea", "view"}), sea);
    
    //add_item( ({"martira bay"}), martira_bay);
    
    add_item( ({"cannons", "cannon", "iron cannon", "iron cannons"}),
        "Cannons placed on heavy metal tracks that "
        +"allows for them to be pushed forward for use and pulled back for "
        +"loading. The cast iron design makes them incredibly heavy and it "
        +"would take a team of many to move them.\n");
    
    add_item( ({"tracks", "cannon tracks", "track", "cannon track"}),
        "Well-built iron tracks are set into the floor to "
        +"allow for the movement of the cannons both forwards and "
        +"backwards.\n");
    
    add_item( ({"cannon balls", "balls", "ball", "cannon ball",
        "iron ball", "iron balls",}), "Large iron cannon balls designed "
        +"to be fired from the cannons are piled like a pyramid of "
        +"death and destruction. Heavy canvas straps are connected "
        +"to iron rings in the floor and criss-crossed over the "
        +"cannon balls to hold them in place.\n");
    
    add_item( ({"straps", "canvas straps", "strap", "canvas strap",
        "heavy canvas straps", "heavy canvas strap",
        "heavy strap", "heavy straps"}), "Heavy canvas straps are "
        +"connected to iron rings in the floor and criss-crossed over "
        +"the cannon balls to hold them in place.\n");
    
    add_item( ({"figurehead", "ghastly figurehead",
        "skeletal figurehead"}), "Carved entirely out of wood in "
        +"immaculate detail is a skeleton. His head is clean "
        +"and skeletal with huge vacant eyes as black "
        +"as the depths of the sea. His mouth is stuck in an eternal grin "
        +"daring the ocean to take him. In one hand he holds a "
        +"scythe indicating death and despair "
        +"while in the other he holds a heart representing what has been "
        +"lost and the eternity of this crews voyage.\n");
    
    add_item( ({"heart", "held heart", "figurehead heart"}), "A heart, "
        +"not the anatomical heart but a typical "
        +"heart, is held out in the skeletal hand towards the sea in "
        +"defiance.\n");
    
    add_item( ({"scythe", "figurehead scythe"}), "Curved blade resting "
        +"atop a long shaft used to cut wheat, or in some cases, sever "
        +"heads from torsos.\n");
    
    add_item( ({"mizzen-masts", "mizzen-mast",
        "mizzenmasts", "mizzenmast", "mast", "masts"}), "Three tall "
        +"mizzen-masts sprout from the ships deck towards the "
        +"heavens. Made of solid wood they have seen better days. "
        +"Still they seem unnaturally sturdy.\n");
    
    add_item( ({"sails", "sail", "black sails", "black sail"}), "Rolled "
        +"up sheets of black sails lie at the top of the mizzen-masts "
        +"ready to be unfurled at a moments notice to "
        +"catch the wind and thrust the ship into motion.\n");

        
    position = 0;
    direction = 1;
    events = 0;
    
    set_alarm(30.0, 30.0, &move_events());
    
    reset_room();
}


/*
 * Function name: enter_ship()
 * Description  : Determines if possible to enter the ship.
 */
int
leave_ship(string str)
{
    if (str == "ship" || str == "bountiful" || str == "frigate")
    {
        if (position == 0)
        {
            write("You disembark from the frigate Bountiful.\n");

            tell_room(DEFAULT_DIR + "rooms/beach_w", QCNAME(this_player())
            +" arrives from the frigate.\n", this_player());

            tell_room(environment(this_object()), QCTNAME(this_player())
            + " arrives from the frigate.\n", this_player());

            this_player()->move_living("M", DEFAULT_DIR + "rooms/beach", 1);

            return 1;
        }
        
        if (position == 10)
        {
            write("You jump overboard and into the cold sea.\n");

            tell_room(DEFAULT_DIR + "rooms/ow1", QCNAME(this_player())
            +" crashes in from above and plunges into the cold water!\n", this_player());

            tell_room(environment(this_object()), QCTNAME(this_player())
            + " crashes in from above and plunges into the cold water!\n", this_player());

            this_player()->move_living("M", DEFAULT_DIR + "rooms/ow1", 1);

            return 1;
        }
        
        write("The Bountiful is not anywhere near the shore or the target "
        +"location. You better wait for a more proper time to disembark.\n");
    }

    return 0;
}


/*
* Function name: init()
* Description  : Enables the commands when a mortal enters.
*/
void init()
{
    ::init();
    add_action(leave_ship, "disembark");
    add_action(leave_ship, "leave");
}


void
reset_room()
{
    ::reset_room();
}
