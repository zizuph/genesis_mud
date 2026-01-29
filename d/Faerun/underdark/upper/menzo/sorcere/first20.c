/*
 *  faerun/underdark/upper/menzo/sorcere/first20.c
 *
 *   
 *  Study on the first floor in the west tower of sorcere.
 *  Created by Midnight, 13-2-2004
 */

#include "defs.h"

#define STUDENT2 P_MENZO_SORCERE + "npc/student_acid"

inherit P_MENZO_SORCERE + "std/base_room";


private object student_acid;

public void
reset_room()
{
    if(!objectp(student_acid))
    {
        student_acid = clone_object(STUDENT2);
        student_acid->move(this_object(), 1);
        student_acid->command("emote takes a step out of the shadows.");
    }

}
/*
 * Function name: create_sorcere_room
 * Description  : Construct a room for the Sorcere part of Menzoberranzan
 */
void create_sorcere_room()
{
	object door;
	
	
	set_short("A half-moon shaped study room in the north tower");
	set_long("You've entered a half-moon shaped study of a wizard " +
                 "student. Darkness envelops the room, except for the " +
                 "weak illumination of a single candle burning " +
                 "on a large wooden desk near the circular window in the " +
                 "room. There's an armchair in one corner near the  " +
                 "doorway and a study oak bookcase standing against " +
                 "the wall on the otherside of the doorway.\n");
                 
        door = clone_object(P_MENZO_SORCERE + "obj/ground_door");
	door->configure_ground_door("east", "w1_20", 
		P_MENZO_SORCERE + "west1");
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
        
        add_exit("west1", "east");

	reset_room();
}