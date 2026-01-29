/* /d/Faerun/guilds/black_flame/rooms/bf_rackroom1.c
 *
 * Nerull 2022
 *
 */

inherit "/d/Faerun/guilds/black_flame/rooms/std/bf_std_room";

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

#define FIREKNIVES_MASTER "/d/Faerun/guilds/fire_knives/master/occ_fireknives_master.c"


public int
block_non_trustees()
{
    // FKs always have access.
    if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) == 1)
    {
        write("The guard dogs raise their heads to look at you, then look down "
        +"and turn around in a submissive gesture.\n");
    
        tell_room(environment(this_player()), QCTNAME(this_player())
        +" receives a furtive glance from the dogs before they lower "
        +"their head and turn around in a submissive gesture.\n", this_player());
    
        return 0;
    }
      
    // Needs to be a BF member...
    if (BF_MASTER->is_lay_bf(this_player()->query_name()) == 1)
    {
        // ..and needs to be on the exclusive list of FK trustees.
        if (FIREKNIVES_MASTER->is_bf_trustee(this_player()->query_name()) == 1)
        {
            write("The guard dogs raise their heads to look at you, then look down "
            +"and turn around in a submissive gesture.\n");
    
            tell_room(environment(this_player()), QCTNAME(this_player())
            +" receives a furtive glance from the dogs before they lower "
            +"their head and turn around in a submissive gesture.\n", this_player());
        
            return 0;
        }  
        
        // .. else access is denied.
        write("The guard dogs slowly pace until they "
            +"stand in front of you "
            +"while growling softly, their eyes focused on yours. You decide "
            +"to reconsider your option and take a few steps backwards.\n");
            
            tell_room(environment(this_player()), QCTNAME(this_player()) 
            +" steps backwards from the dogs as they move in front of "
            + this_player()->query_objective()
            +", blocking the way to the north.\n", this_player());
            
        return 1;
    }    
    
    // .. else access is denied.
    write("The guard dogs slowly pace until they "
        +"stand in front of you "
        +"while growling softly, their eyes focused on yours. You decide "
        +"to reconsider your option and take a few steps backwards.\n");
        
        tell_room(environment(this_player()), QCTNAME(this_player()) 
        +" steps backwards from the dogs as they move in front of "
        + this_player()->query_objective()
        +", blocking the way to the north.\n", this_player());
        
    return 1;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_bf_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    
    set_short("A bend in the Temple of Kossuth");
    
    set_long("You find yourself in a pretty empty, windowless, curved "
    +"hallway. Aside from the usual torches lighting the area, "
    +"here you also find a rack for weapons and armors. "
    +"The curved nature of the hallway completely hides what "
    +"lies around the corner, but you can proceed southeast "
    +"or northeast to find out. You see a short tunnel "
    +"leading north from here. A pair of vicious guard dogs is pacing "
    +"about, guarding the entrance to the north.\n");
    
    add_item(({"dog", "dogs", "guard dog", "guard dogs", 
    "vicious guard dogs", "vicious dogs"}),
    "These pair of vicious wolf-like grey dogs paces about the "
    +"area, sniffing and carefully watching the movements "
    +"of any nearby creature. They appear to be guarding "
    +"the entrance to the north.\n");
    
    add_item(({"wall", "walls"}),
        "The walls are smooth and white, made from some kind "
        +"of dense stone.\n");
        
    add_item(({"floor", "ground"}),
        "The floor is made up of very dark granite. In "
        +"contrast to the white walls, the floor almost "
        +"looks black.\n");
        
    add_item(({"torch", "torches"}),
        "Pretty standard, wall-hung torches light up the "
        +"area. You’re fairly sure they contribute to "
        +"the heating as well.\n");
        
    
    add_exit(BF_ROOMS_DIR + "bf_rackroom2", "north", block_non_trustees);
    add_exit(BF_ROOMS_DIR + "bf_join", "east");
    add_exit(BF_ROOMS_DIR + "bf_corridor1", "northeast");
    add_exit(BF_ROOMS_DIR + "bf_corridor3", "southeast");
       
    
    room_add_object(BF_GUILD_DIR + "obj/bf1_rack");
                      
    
    reset_faerun_room();
}