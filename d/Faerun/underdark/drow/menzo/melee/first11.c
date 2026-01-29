/*
 *  faerun/underdark/upper/menzo/melee/first11.c
 *
 *   
 *  Corridor on the first floor in the Melee-magthere.
 *  Created by Midnight, 4-4-2004
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
inherit ROOM_IN_BASE;

#define MAX_STUD 4
static object *students = allocate(MAX_STUD);

/*
 * Function name: create_menzo_in_room
 * Description  : Construct a room for the Melee-magthere
 */
void create_menzo_in_room()
{
	set_short("A dark northern corridor on the first floor");
	set_long("You stand in a corridor in the " +
                 "the Melee-magthere of Menzoberranzan. " +
                 "The floors are swept clean to perfection " +
                 "and a luminous trail of soft crimson red " +
                 "light runs in the middle of the floor, like a " +
                 "trail of blood guiding the way further into " +
                 "the dark corridor. The walls of the corridor " +
                 "are lost in the shadows, but the corridor " +
                 "still feels quite roomy. \n");
		 
        add_exit("first10", "west");
        add_exit("first13", "east");
        add_exit("first12", "south");
        reset_room();     

}


void
reset_room()
{
/*
    int index,
    random_num;

    while(random_num == 0)
    {
        random_num = random(MAX_STUD);
    }

//    Do this first, since we may need to clone. 
    setuid();
    seteuid(getuid());
 
//  Loop over all elements in the array. 
    for(index = 0; index < random_num; index++)
    {
        if (!objectp(students[index]))
        {
            students[index] = clone_object(NPC_STUD);
            students[index]->set_restrain_path("/d/Faerun/underdark/drow/menzo/melee");
            students[index]->set_random_move(3);
            students[index]->move(TO);
 
        }
    }
*/
}
