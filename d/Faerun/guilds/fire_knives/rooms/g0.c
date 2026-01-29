/* /d/Faerun/guilds/fire_knives/rooms/g0.c
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;


public int
block_check()
{
    // Guild has no council, therefore anyone can go upstairs
    if (FIREKNIVES_MASTER->no_boss() == 1 
    && FIREKNIVES_MASTER->no_fist() == 1 
    && FIREKNIVES_MASTER->no_mentor() == 1)
    {
        write("The guard dogs raise their heads to look at you "
        +"suspiciously, but they "
        +"let you pass.\n");
        
        tell_room(environment(this_player()), QCTNAME(this_player())
        +" receives a suspicious glance from the guard dogs, but "
        +"is let through.\n", this_player());
            
        return 0;
    }  
    
    if (present("fireknives_visit_object_conference", this_player()))
    {
       write("The guard dogs raise their heads to look at "
       +"you suspiciously, but they "
       +"let you pass.\n");
        
        tell_room(environment(this_player()), QCTNAME(this_player())
        +" receives a suspicious glance from the guard dogs, but "
        +"is let through.\n", this_player());
            
        return 0;
    }  
    
    if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) == 0)
    {
        if (!this_player()->query_wiz_level())
        {
            write("The guard dogs slowly pace until they "
            +"stand in front of you "
            +"while growling softly, their eyes focused on yours. You decide "
            +"to reconsider your option and take a few steps backwards.\n");

            tell_room(environment(this_player()), QCTNAME(this_player()) 
            +" steps backwards from the dogs as they move in front of "
            + this_player()->query_possessive()
            +", blocking the way.\n", this_player());

            return 1;
        }
    }
      
    write("The guard dogs raise their heads to look at you, then look down "
    +"and turn around in a submissive gesture.\n");
    
    tell_room(environment(this_player()), QCTNAME(this_player())
    +" receives a furtive glance from the dogs before they lower "
    +"their head and turn around in a submissive gesture.\n", this_player());
        
    return 0;
}


int
do_crawl(string str)
{
    if (str == "through hole")
    {
        write("\nYou crawl through the hole.\n\n");

        tell_room(environment(this_object()), QCTNAME(this_player())
        + " crawls through the hole.\n", this_player());
        
        this_player()->move_living("M", FIREKNIVES_GUILD_DIR 
        + "rooms/ledge", 1);
        
        tell_room(FIREKNIVES_GUILD_DIR + "rooms/ledge", QCTNAME(this_player())
        + " arrives crawling through the rift.\n", this_player());
        
        return 1;
    }
    
    write("Crawl through hole, perhaps?\n");
    
    return 1;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("Inside a cold, dank cellar");
    
    set_long("Dripping sounds of something heavier than water "
    +"reverberate across "
    +"the darkness encompassing the "
    +"cell-like passages in this cellar. Its echoes "
    +"bouncing off the clammy walls which "
    +"close in around you as if in a tunnel. "
    +"An acrid smell permeates the area, as "
    +"if from deep inside the humidity "
    +"drifting from the northwest and dissolving "
    +"into a hole near the ground to "
    +"the southwest. The tunnel widens slightly "
    +"to the southeast into a square "
    +"grotto, while far to the northwest, a "
    +"flame-like shimmer of light can be "
    +"discerned. A pair of vicious guard dogs is pacing "
    +"about, guarding the entrance to the northwest.\n"); 

    add_item(({"darkness"}),
    "The darkness is all around you, swallowing "
    +"the surroundings within it. However, there is "
    +"just enough illumination here for you to see "
    +"in the room.\n");
    
    add_item(({"dog", "dogs", "guard dog", "guard dogs", 
    "vicious guard dogs", "vicious dogs"}),
    "These pair of vicious wolf-like grey dogs paces about the "
    +"area, sniffing and carefully watching the movements "
    +"of any nearby creature. They appear to be guarding "
    +"the entrance to the northwest.\n");

    add_item(({"passage", "passages", "tunnel","tunnels"}),
    "The passage within the the cellar feels like a "
    +"tunnel. Although seemingly "
    +"firm and stable, caring for them beyond their "
    +"functionality hasn't been a "
    +"priority for anyone.\n");
    
    add_item(({"walls", "wall"}),
    "The walls emanate a coldness which has turned "
    +"the little air transiting "
    +"through this tunnel into moisture due "
    +"to the lack of ventilation. Green "
    +"patches of moss are scattered around them.\n");
    
    add_item(({"moss"}),
    "Patches of moss have grown from small fissures in the walls.\n");
    
    add_item(({"fissures","fissure","crack","cracks"}),
    "Although firm and stable, the passing of time has left its mark on "
    +"the walls of this tunnel. They shoot upwards from the hole near the "
    +"ground as if they were scratches left by the tools which carved it.\n");
    
    add_item(({"hole"}),
    "To the southwest near the floor is a small "
    +"rectangular hole through which "
    +"you could crawl through if you so desired.\n");

    add_item(({"floor", "ground"}),
    "The floor of the tunnel is well-worn in and "
    +"seems to be frequented rather "
    +"than isolated from life. The patches of "
    +"moss, dirt, and pebbles bear the "
    +"form of what appear to be footsteps.\n");
    
    add_item(({"footstep","footsteps","dirt","pebble","pebbles"}),
    "Found on the ground and marked caked in the "
    +"dirt and moss are what appear to be "
    +"footsteps leading to the southeast.\n");
    
    add_exit(FIREKNIVES_ROOMS_DIR + "c3.c", "northwest", block_check);
    add_exit(FIREKNIVES_ROOMS_DIR + "br.c", "southeast");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


void
init()
{
    ::init();

    add_action(do_crawl, "crawl");
}
