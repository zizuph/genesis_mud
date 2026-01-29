/* /d/Faerun/guilds/half_orcs/rooms/ho_join.c
 *
 * Room in the guildhall.
 *
 * Nerull, 2022
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit HO_STD_OUTDOOR;


/*
 * Function name: do_join()
 * Description  : The function that adds a member of the guild.
 *
 */
int do_join(string str)
{
    object shadow_racial;
    
    // Joining using the Layman slot
    //if (str == "a pact")
    if (str == "heritage")
    {   
        if (this_player()->query_race() == "goblin" 
		|| this_player()->query_race() == "human")
        {			
			if (this_player()->query_guild_name_race())
			{
				write("Return when you have a vacant racial slot.\n");
					
				return 1;
			}
			
			if (HO_MASTER->is_race_ho(this_player()->query_name()))
			{
				write("You are already a member of the Half-orcs.\n");
				return 1;
			}
			
			shadow_racial = clone_object(HO_GUILD_DIR 
			+ "shadows/ho_sh_racial.c");
			
			if (shadow_racial->shadow_me(this_player(), "race", "race", "Half-orcs of Faerun") != 1)
			{
				write("You try to join the Half-orcs (race), but nothing happens.\n");
		   
				return 1;
			}
			
			HO_MASTER->add_race_ho(this_player()->query_name());
			
				
			write("Your limbs stretch and muscles start bulging as "
			+"the old muscular male half orc channels the power of the "
			+"earth. You feel a sharp pain in your lower jaw as tusks start "
			+"growing and your jaw widens to fit them. Suddenly everything "
			+"goes black as you lose consciousness and when you wake up all "
			+"that reminds you of the ritual is a faint dull pain in "
			+"your limbs.\nYou join the Half orcs.\n");

			tell_room(environment(this_player()), this_player()->query_name()
			+ " joined the Half orcs!\n", this_player());
			
			HO_MAPPINGS->set_ho_tusks(this_player()->query_name(), random(13));
			
			this_player()->update_hooks();

			return 1;
		}
		
		write("Only humans or goblins may claim half orc heritage.\n");
					
		return 1;
    }

    write("What do you wish to do? 'claim heritage', perhaps?\n");
            
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
    if (str != "half-orcs")
    {
        write("Do 'leave half-orcs' if "
        +"you want to flee to somewhere else!\n");
        return 1;
    }

    if (this_player()->query_guild_name_race() == RACE_HO_GUILD_NAME)
    {
        write("You leave the Half-orcs!\n");

        tell_room(environment(this_player()), this_player()->query_name()
        +" leaves the Half-orcs!\n", this_player());
        
        HO_MASTER->remove_race_ho(this_player()->query_name());
        
        HO_MAPPINGS->clean_ho_tusks(this_player()->query_name());
        
        this_player()->remove_guild_race();

        this_player()->clear_guild_stat(SS_RACE);

        this_player()->remove_cmdsoul("/d/Faerun/guilds/half_orcs/souls/ho_race");
		
		if (this_player()->query_race() == "goblin")
	    {
			this_player()->set_race_name("goblin");
		}
		
		if (this_player()->query_race() == "human")
	    {
			this_player()->set_race_name("human");
		}		
        
        this_player()->update_hooks();
        
        return 1;
    }
    
    
    write("You are not a member of the "+ RACE_HO_GUILD_NAME + ".\n");
 
    return 1;
}


/*
 * Function name: create_guildhall_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_ho_outdoor()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_LIGHT, 2);
    
    set_short("A small clearing with a campfire");
    
    set_extraline("This is a small clearing in the forest "
	+"that has been made into an improvised camp. Large oaktrees "
	+"surround the clearing giving it a cool shade. There is a "
	+"small hide tent here placed by a campfire. An old "
	+"half orc is sitting by the campfire and looks up at "
	+"you as you approach.");
    
    add_item(({"camp"}),
        "This seems like a semi permanent camp where someone "
		+"lives. It is small enough to support "
		+"perhaps two people.\n");
		
	add_item(({"half-orc", "old half-orc", "muscular half-orc", "old muscular half orc",
	"half orc", "old half orc", "muscular half orc", 
	"old muscular half orc"}),
        "This is an old muscular half orc, clearly in his twillight "
		+"years. He is completely bald with bushy grey eyebrows and a "
		+"white short trimmed beard. Despite his advanced age he is "
		+"clearly retaining the muscles of someone under half his age "
		+"and has a keen, steely gaze fixed on you as if assessing "
		+"your worth.\nIf you are of the race human or goblin, "
		+"you may <claim heritage> to become an half orc. Furthermore, "
		+"you may <leave half-orcs> at this place aswell.\n");
		
    add_item(({"tree", "trees"}),
        "These are large majestic oak trees that sway gently "
		+"in the wind. Trees of this size is without a doubt very old.\n");
		
    add_item(({"tent"}),
        "This is a small tent made of old bear hides. The tent is big "
		+"enough to perhaps fit two people?\n");
		
    add_item(({"campfire"}),
        "The campfire is lit and provides some warmth for whom ever "
		+"sits close to it. A few pots and pans are spread around it "
		+"making it very possible someone is using it to cook food.\n");
		
	add_item(({"pot", "pots"}),
        "These are some old, somewhat rusted metal pots.\n");
		
	add_item(({"pan", "pans"}),
        "These are some old, somewhat rusted metal pans.\n");
		
		      
    add_item(({"floor", "ground"}),
        "The floor is made up of very dark granite. In contrast "
        +"to the white walls, the floor almost looks black. Recessed "
        +"into the floor is a large rectangular fire-pit.\n");		
	
	add_exit("/d/Faerun/swordcoast/south_highroad/rooms/s_hroad08", "south");
	
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

    add_action(do_join, "claim");
    add_action(do_leave, "leave");
}

