/*
 *  faerun/underdark/upper/menzo/melee/first14.c
 *
 *
 *  Corridor on the first floor in the Melee-magthere.
 *  Created by Midnight, 4-4-2004
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
inherit ROOM_IN_BASE;

#define MAX_STUD 3
static object *students = allocate(MAX_STUD);

/*
 * Function name: create_menzo_in_room
 * Description  : Construct a room for the Melee-magthere
 */
void create_menzo_in_room()
{
	set_short("In a shadowy small training room");
	set_long("This is a shadowy small training room, where students " +
                 "can practice alone, in pairs or together with " +
                 "a master. The stone walls are cut in a perfect " +
                 "circle, designed to keep a battle going " +
                 "so no one gets cornered. A rounded opening leads " +
                 "out to a dark corridor.\n");

        add_exit("first13", "north");
        reset_room();

}


void
reset_room()
{
    int index;

    /* Do this first, since we may need to clone. */
    setuid();
    seteuid(getuid());
 
    /* Loop over all elements in the array. */
    for(index = 0; index < MAX_STUD; index++)
    {
        if (!objectp(students[index]))
        {
            students[index] = clone_object(NPC_STUD);
            students[index]->set_restrain_path("/d/Faerun/underdark/drow/menzo/melee");
            students[index]->set_random_move(3);
            students[index]->move(TO);
 
        }
    }

}
