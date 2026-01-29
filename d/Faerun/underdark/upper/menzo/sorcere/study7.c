/*
 *  faerun/underdark/upper/menzo/sorcere/study7.c
 *
 *   
 *  Study on the third floor in the main tower of sorcere.
 *  Created by Midnight, 8-3-2004
 */

#include "defs.h"

inherit P_MENZO_SORCERE + "std/base_room";
#define MASTER1 P_MENZO_SORCERE + "npc/master2_viper"
private object master_viper;
object door;

/*
 * Function name: reset_room
 * Description  : Called when the room is reset, allows us to clone the
 *              : mage again
 */
public void reset_room()
{
    // Close, lock and arm the door
    door->reset_trapped_door();
    if(!objectp(master_viper))
    {
       master_viper = clone_object(MASTER1);
       master_viper->move(this_object(), 1);
       master_viper->command("emote takes a step out of the shadows.");
        
    }

}


/*
 * Function name: create_sorcere_room
 * Description  : Construct a room for the Sorcere part of Menzoberranzan
 */
void create_sorcere_room()
{
	
	
	set_short("A dark spacious office in the main tower");
	set_long("You've entered a spacious study of a wizard " +
                 "master. Darkness envelops the room, except for the " +
                 "weak illumination of a single candle burning " +
                 "on a large wooden desk near the circular window in the " +
                 "room. There's an armchair in one corner near the  " +
                 "doorway and a study oak bookcase standing against " +
                 "the wall on the otherside of the doorway.\n");
                 
        // Create and configure all doors
	door = clone_object(P_MENZO_SORCERE + "obj/third_master_door");
	door->configure_ground_door("west", "s7_3", 
		P_MENZO_SORCERE + "third3");
	door->move(this_object());
		 
	add_item(({"doorway"}),
        "The doorway is wide open without any door and thus provides no " +
        "privacy for the wizard students.\n");
      
        add_item(({"candle"}),
        "The weak flame of a candle light is, although needed for the " +
        "student, hurtful to the eyes of a drow. The flame of the " +
        "candle flickers as it burns in the darkness.\n");
        
         add_item(({"desk"}),
        "A wooden desk stands near the only window of the room " +
        "and is made of slender polished cherry wood.\n");
        
        add_item(({"armchair"}),
        "A comfortable armchair dressed in shimmering dark blue " +
        "velvet stands in the corner of the room.\n");
        
        add_item(({"bookcase"}),
        "A sturdy bookcase made of oak stands against the wall " +
        "next to the doorway. Books and parchments, glass bottles " +
        "and pouches fills the shelves of the bookcase.\n");
        
        add_item(({"books"}),
        "Books of various sizes and age are placed in a seemingly " +
        "random order in the bookcase.\n");
        
        
        add_item(({"parchments"}),
        "Parchments are rolled up or folded carefully and placed  " +
        "within the bookcase.\n");
        
        add_item(({"bottles"}),
        "Glass bottles are stacked all over in the bookcase, some " +
        "are the size og large jars, while others are just a " +
        "finger-height small. Some seems empt, while others contains " +
        "something unidentifiable.\n");
          
        add_item(({"floor"}),
        "The floor is hard beneath you and made by solid black rock. " +
        "Although the floor is hard, the echoes of the steps are " +
        "mysteriously absorbed into silence.\n");
        
        add_exit("third3", "west");
       

	
    reset_room();
}