/*
 *  faerun/underdark/upper/menzo/tierbreche/plateau12.c
 *
 *  
 *  Created by Midnight, 13-12-2004
 */

#include "defs.h"
#include <macros.h>

inherit P_MENZO_TIERBRECHE + "std/base_room";

#define JOIN_ROOM "/d/Faerun/guilds/drow/race/drow_join"


/*
 * Function name: create_tierbreche_room
 * Description  : Construct a room for the Tier Breche part of Menzoberranzan
 */
void create_tierbreche_room()
{
	set_short("In the middle of Tier Breche");
	set_long("You are right in the middle of Tier Breche,  " +
                 "you can see the three buildings which towers upon this " +
                 "plateau. The rocks along side of the path glows " +
                 "with a soft dark blue shimmer. Stalactites hang down " +
                 "from high above like sharp deadly pikes. " +
                 "The plateau you are walking on stands in spectacular " +
                 "contrast to the rough-looking ceiling. " +
                 "The ground is smoothly cut directly into the " +
                 "caverns rock, and it almost have the polished shiny finish " +
                 "of decorative marble. The magical glow from the surrounding " +
                 "buildings are mirrored into the stone floor beneath you. " +
                 "An impressive circular column of vibrating crimson red light " +
                 "is raised from the stone floor and vanishes out of sight " +
                 "in the darkness of the cavern ceiling.\n");
		 
	add_item(({"column"}),
        "The crimson red light vibrates with a low humming sound, " +
        "it beckons you to come closer and enter its burning red " +
        "glow.\n");
        
                
        add_item(({"plateau", "tier breche"}),
        "This is the Tier Breche. You can spot three buildings " +
        "on top of the plateau. The plateau is the highest point " +
        "above the city in this two-mile wide cavern.\n");
        
        
        add_item(({"buildings", "building"}),
        "On top of the plateau you can spot three very different " +
        "buildings. One gracefully curving many-spired tower, one " +
        "giant building shaped like a pyramid and finally an " +
        "intriguing building shaped like a giant spider.\n");
        
        add_item(({"first building", "sorcere"}),
        "The tower which houses the wizard academy of Menzoberannzan " +
        "is gracefully curved with many spires.\n");
        
        add_item(({"second building"}),
        "The building of the Melee-Magthere is shaped like an impressive " +
        "pyramid. It houses the warrior academy of Menzoberranzan.\n");
        
        add_item(({"third building"}),
        "The priestesses of Lloth studies in a huge building shaped " +
        "like a giant spider.\n");
        
        add_item(({"rocks"}),
        "They are made of smooth stone which has been magically altered " +
        "to glow in a soft dark blue shimmering light. They mark the " +
        "path between the entrance of Tier Breche and Sorcere.\n");
        
                
        add_item(({"stalactites"}),
        "The mineral-laden water has dripped down along the rock " +
        "from the ceiling of the cavern and during countless of centuries " +
        "it has formed gigantic stalactites which looms over the city.\n");
        
        add_item(({"stalagmites"}),
        "Rock formations of various sizes has been formed like pointed " +
        "pikes from the grouns and up towards the cavern ceiling high" +
        "above. The mineral-heavy water drops continuously downwards " +
        "from the ceiling to make the protusions grow slowly over " +
        "centuries.\n");
        
        set_atmosphere_interval(2);
        add_atmosphere("The crimson red light of the column vibrates with a " +
                       "low humming sound.\n");
               

      
        add_exit(JOIN_ROOM, "up", "@@enter");

        add_exit("plateau11", "east");
        add_exit("plateau13", "west");
}
enter() 
{
	if (this_player()->query_race() != "elf" || 
	    this_player()->query_race_name() != "drow") 
	    { write("You step right into a magical barrier and are rejected " +
	    	      "to enter the column because you are not of elven or drow heritage!\n"); 
	    	say(QCTNAME(this_player()) + " tries to enter the column, but is magically rejected.\n");
        return 1; 
      }
        else
      {
        
        say(QCTNAME(this_player()) + " steps into the column.\n");
        write("The red swirling light quickly swirls around you and with the " +
              "effect of a surface tornado, you are transported in a direction " +
              "which is hard to sense.\n");

        write("You spin...\n");
        write("and spin...\n");
        write("and spin...\n");
        write("With a final spin, you are cast out of the crimson column!\n");
        return 0;
      }

        
        
               

}