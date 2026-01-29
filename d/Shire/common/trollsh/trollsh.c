/*
 * trollsh.c
 *
 * This file contains all functions and variables which are
 * common to all rooms in the Trollshaw forest.
 *
 */
inherit "/d/Shire/common/lib/rom";
#include "defs.h"

/*
 * We will need all the function in this file, so we inherit it.
 */

/*
 * create_rom is the entry point at creation of a Trollshaw room.
 */

static int life;
string *life_list;

create_rom()
{
    /*
     * In all Trollshaw-rooms, you might want to examine the forest.
     */
    
    
    
    add_item(({"forest", "trollshaws", "trollshaw", "trollshaw forest",
	       "shaws", "woods", "trees" , "bushes" , "area"}),
	  "The forest is very dark, swallowing all light coming into it.\n");
    /*
     * Now we make sure that we can make the different rooms
     * having different longs/shorts etc.
     */
    TO->create_trollsh();
    life_list = 
        ({
          "wind",
             "The wind can only be felt, not seen.",
          "crow,scream",
             "The scream came from within the forest.",
          "wolves,sounds",
             "The wolves howl in the distance, let us hope they don't catch scent of you.",
          "forest",
             "The forest is dark indeed.",
          "shadow",
             "It might be just the trees that are moving...and it could be some animal that you scared of."
        });

}

reset_rom()
{
    TO->reset_trollsh();
}

static string *name;

string
add_extra_life()
{
    life = random(5);
    if(name && sizeof(name))
        remove_item(name[0]);
    name = explode(life_list[2*life+1],",");
    add_item(name, life_list[2*life+1]+"\n");
    
    switch(life)
    {
        case 0:
            return
                "A ghostly wind rushes trough the forest, making your bones shiver.";
        case 1:
            return
                "A horrible scream echoes trough the forest, making you tremble. Maybe it "+
                "just was a crow..";
        case 2:
            return
                "Sounds of wolves can be heard in the distance. But then, the forest as a "+
                "habbit of making things sound more distant then they really are.";
        case 3:
            return
                "The forest seems dark and grows large, almost like it want to swallow you.";
        case 4:
            return
                "Suddenly a shadow moves in between the trees..or was it just your own imagination..";
    }
}

string
query_extra()
{
    string extra = "";
    if(random(3)==2)
        extra += add_extra_life();
    return extra;
}
