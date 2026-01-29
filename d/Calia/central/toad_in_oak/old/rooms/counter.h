/*
 * /d/Calia/central/toad_in_oak/specials/counter.h
 *
 * This is the header for a function to count all instances of a given object
 * in a given array of rooms. This file also includes a nubmer of defintions
 * to make it easy to create groups of rooms to search. 
 *
 * HISTORY: [99-07-22] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// DEFINTIONS

#define CR_ENTRANCES    ({  TOAD_IN_OAK_ROOMS_GROUND + "entrance_north", \
                            TOAD_IN_OAK_ROOMS_GROUND + "entrance_west"})
#define CR_GARDEN_FLOWER ({ TOAD_IN_OAK_ROOMS_GROUND + "garden_flower_north", \
                            TOAD_IN_OAK_ROOMS_GROUND + "garden_flower_east",  \
                            TOAD_IN_OAK_ROOMS_GROUND + "garden_flower_south", \
                            TOAD_IN_OAK_ROOMS_GROUND + "garden_flower_west"})
#define CR_GARDENS  CR_GARDEN_FLOWER + \
                    ({  TOAD_IN_OAK_ROOMS_GROUND + "garden_vegetable" , \
                        TOAD_IN_OAK_ROOMS_GROUND + "garden_mushroom"})
#define CR_GREEN    ({  TOAD_IN_OAK_ROOMS_GROUND + "green_ne", \
                        TOAD_IN_OAK_ROOMS_GROUND + "green_nw", \
                        TOAD_IN_OAK_ROOMS_GROUND + "green_se", \
                        TOAD_IN_OAK_ROOMS_GROUND + "green_sw"})
#define CR_LAKE     ({  TOAD_IN_OAK_ROOMS_GROUND + "lake_shore", \ 
                        TOAD_IN_OAK_ROOMS_GROUND + "lake_swimming"})
#define CR_PATH     ({  TOAD_IN_OAK_ROOMS_GROUND + "path_01", \
                        TOAD_IN_OAK_ROOMS_GROUND + "path_02", \
                        TOAD_IN_OAK_ROOMS_GROUND + "path_03", \
                        TOAD_IN_OAK_ROOMS_GROUND + "path_04", \
                        TOAD_IN_OAK_ROOMS_GROUND + "path_05", \
                        TOAD_IN_OAK_ROOMS_GROUND + "path_06", \
                        TOAD_IN_OAK_ROOMS_GROUND + "path_07", \
                        TOAD_IN_OAK_ROOMS_GROUND + "path_08", \
                        TOAD_IN_OAK_ROOMS_GROUND + "path_09", \
                        TOAD_IN_OAK_ROOMS_GROUND + "path_10", \
                        TOAD_IN_OAK_ROOMS_GROUND + "path_11", \
                        TOAD_IN_OAK_ROOMS_GROUND + "path_12", \
                        TOAD_IN_OAK_ROOMS_GROUND + "path_13"}) 
#define CR_POND     ({  TOAD_IN_OAK_ROOMS_GROUND + "pond_shore", \
                        TOAD_IN_OAK_ROOMS_GROUND + "pond_surface" })
#define CR_TRAIL    ({  TOAD_IN_OAK_ROOMS_GROUND + "trail_01", \
                        TOAD_IN_OAK_ROOMS_GROUND + "trail_02", \
                        TOAD_IN_OAK_ROOMS_GROUND + "trail_03", \
                        TOAD_IN_OAK_ROOMS_GROUND + "trail_04", \
                        TOAD_IN_OAK_ROOMS_GROUND + "trail_05", \
                        TOAD_IN_OAK_ROOMS_GROUND + "trail_06" })
#define CR_ALL_GROUND   CR_ENTRANCES + \
                        CR_GARDENS + \
                        CR_GREEN + \
                        CR_LAKE + \
                        CR_PATH + \
                        CR_POND + \
                        CR_TRAIL + \
                        ({  TOAD_IN_OAK_ROOMS_GROUND + "great_oak", \
                            TOAD_IN_OAK_ROOMS_GROUND + "spring" })
#define CR_POND_VISIBLE CR_POND + 
                        ({  TOAD_IN_OAK_ROOMS_GROUND + "path_02", 
                            TOAD_IN_OAK_ROOMS_GROUND + "path_03", 
                            TOAD_IN_OAK_ROOMS_GROUND + "path_11"})
                                
                         

// FUNCTIONS

/*
 * Function name: count
 * Description:   Counts the number of clones of a given object in the 
 *                 supplied rooms
 * Arguments:     Array of filenames to search, filename to search for. 
 * Returns:       number of objects found. 
 */
int
count(string *rooms, string find)
{
    object current_room;
    int x, count = 0; 

    /* We need to loop through all of the rooms in the list given. */ 
    for (x = 0; x < sizeof(rooms); x++)
    {
        /*  Attempt to find each room. It's not a big deal if we don't
            find it since there can't be anything in an unloaded room.  */ 
        current_room = find_object(rooms[x]); 
            
        if (current_room)
        {
            /*  Here we pack a lot into two lines to do the actual counting. */             
            count += sizeof(filter(deep_inventory(current_room),  
                &wildmatch(find + "*") @ file_name)); 
        }
    }

    return count; 
}


