/* /d/Faerun/guilds/black_flame/rooms/bf_join.c
 *
 * Room in the guildhall.
 *
 * Nerull, 2022
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit BF_STD_OUTDOOR;


public int
block_nonmembers()
{
    if (BF_MASTER->is_lay_bf(this_player()->query_name()) == 1)
    {          
        return 0;
    }    
    
    write("Only members of the Order of the Black Flame can "
    +"move in that direction.\n");
    
    return 1;
}


/*
 * Function name: do_join()
 * Description  : The function that adds a member of the guild.
 *
 */
int do_join(string str)
{
    object shadow_lay;
    object tokena;
    
    // Joining using the Layman slot
    //if (str == "a pact")
    if (str == "fealty to the order of the black flame" 
    || str == "fealty to the Order of the Black Flame")
    {   
        if (this_player()->query_guild_name_lay())
        {
            write("Return when you have a vacant layman slot.\n");
                
            return 1;
        }
        
        if (BF_MASTER->is_bf_lay(this_player()->query_name()))
        {
            write("You are already a member of the Order of the Black Flame.\n");
            return 1;
        }
        
        if (present("bfjoin_cooldwn_obj", this_player()))
        {
            write("You are not eligible for rejoining the Order of "
            +"the Black Flame at this time! Try later.\n");
            
            return 1;      
        }
        
        object join_paralyze;
		
        join_paralyze = clone_object(BF_GUILD_DIR
        +"obj/join_bf_cutscene_paralyze.c")->move(this_player(), 1);
        
        this_player()->update_hooks();

        return 1;
    }

    write("What do you wish to do? 'pledge fealty to the order of the black "
    +"flame', perhaps?\n");
            
    return 1;
}


/*
 * Function name: do_leave()
 * Description  : The function that removes a member of the guild.
 *
 */
int
do_leave(string str)
{
    object gitem;


    if (this_player()->query_guild_name_lay() == LAY_BF_GUILD_NAME)
    {
		if (str == "the order of the black flame" 
		|| str == "the Order of the Black Flame")
		{		
			write("You leave the Order of the Black Flame!\n");

			tell_room(environment(this_player()), this_player()->query_name()
			+" leaves the Order of the Black Flame!\n", this_player());
			
			BF_MASTER->remove_lay_bf(this_player()->query_name());
			
			this_player()->remove_guild_lay();

			this_player()->clear_guild_stat(SS_LAYMAN);

			this_player()->remove_cmdsoul("/d/Faerun/guilds/black_flame/souls/bf_guild_soul_lay");

			this_player()->set_default_start_location(this_player()->query_def_start());
			
			/* Remove any instances of the guild emblem on the player */    
			while (gitem = present(GUILD_ITEM_NAME_LAY, this_player()))
			{
				gitem->remove_object();
			}
			
			clone_object(BF_GUILD_DIR 
			+ "obj/bfjoin_cooldwn_obj")->move(this_player(), 1);

			this_player()->update_hooks();
			
			return 1;
		}
    
	    write("Do 'renounce the order of the black flame' if "
        +"you want to flee to somewhere else!\n");
		
        return 1;
	}

    write("You are not a member of the "+ LAY_BF_GUILD_NAME + ".\n");
 
    return 1;
}


/*
 * Function name: create_guildhall_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_bf_outdoor()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_LIGHT, 2);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    
    set_short("By the large fire-pit");
    
    set_extraline("Here in the center courtyard of the temple, a "
    +"very large rectangular fire-pit has been placed. The "
    +"pit is recessed into the floor with iron fences running "
    +"along the long sides. On the short sides there are "
    +"steps leading down to the massive bed of infernally "
    +"hot coals burning there. Above the fire-pit "
    +"the roof is open, allowing the hot air to escape. "
    +"Despite this constant exchange of air, you still note "
    +"a faint smell of burnt flesh and hair here.");
    
    add_item(({"courtyard"}),
        "The courtyard is paved with the same dark granite as "
        +"the rest of the temple, but it is open to the sky. "
        +"Dominating this courtyard is a large fire-pit. Aside "
        +"from that you see nothing particular here.\n");
        
    add_item(({"floor", "ground"}),
        "The floor is made up of very dark granite. In contrast "
        +"to the white walls, the floor almost looks black. Recessed "
        +"into the floor is a large rectangular fire-pit.\n");
        
    add_item(({"pit", "fire pit", "firepit", "fire-pit"}),
        "The pit is covered in burning coals, and you can feel "
        +"the heat radiating from it. Sometimes flames burst upward "
        +"from the bed of coal only to quickly dissipate again.\n");
        
    add_item(({"smell", "air"}),
        "The hot air surrounding the firepit is smelling slightly "
        +"of burnt flesh and hair.\n");
		
    clone_object(BF_GUILD_DIR 
        + "obj/bf_book")->move(this_object(), 1);
        
    add_exit(BF_ROOMS_DIR + "bf_boardroom", "north", block_nonmembers);
    add_exit(BF_ROOMS_DIR + "bf_train", "east", block_nonmembers);
    add_exit(BF_ROOMS_DIR + "bf_rackroom1", "west", block_nonmembers);
    add_exit(BF_ROOMS_DIR + "bf_entrance", "south");
    
    reset_faerun_room();
}


void
reset_faerun_room()
{
}


void
init()
{
    ::init();

    add_action(do_join, "pledge");
    add_action(do_leave, "renounce");
}

