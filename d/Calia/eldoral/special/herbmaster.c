/*
 * herbmaster.c
 *
 * This lib module is inherited into the baserooms of areas in Eldoral
 * which make extensive use of herbs. Called from the create function
 * of each baseroom, it is designed to select the herbs to place randomly
 * from the lists available, based on which subdir the area is. Also,
 * which herbs in the list are selected randomly, so while amanita might
 * be possible to find in one room one day, it might not be the next.
 *
 * Coded by Khail, Jan 13/97
 *
 * Modifications
 *   - Added breadroot to the shore rooms. It's an open area with temperate
 *     climate. There is also no breadroot in Calia other than this.
 *       Petros, April 2009
 *
 */
#pragma strict_types

#include "defs.h"

inherit "/d/Krynn/std/herbsearch";

mapping allherbs = (["mountain" : ({"amanita",
                                    "bunchberry",
                                    "cladina",
                                    "labr_tea",
                                    "lady_slipper",
                                    "grey_willow",
                                    "fireweed",
                                    "blk_currant",
                                    "chicory",
                                    "raspberry"}),
                     "forest"   : ({"amanita",
                                    "bunchberry",
                                    "chantrelle",
                                    "cladina",
                                    "fireweed",
                                    "fdlhead",
                                    "labr_tea",
                                    "lady_slipper",
                                    "onoclea"}),
                     "shore"    : ({"cattail",
                                    "chokecherry",
                                    "grey_willow",
                                    "hop",
                                    "breadroot",
                                    "raspberry"}),

                   ]);

/*
 * Function name: resolve_dir
 * Description  : Resolves the passed filename in terms of which subdir
 *                of /d/Calia/eldoral the filename belongs to.
 * Arguments    : str - A string which is the filename of an object.
 * Returns      : A string which should be a subdir of /d/Calia/eldoral.
 */
public string
resolve_dir(string str)
{
    string *arr;

    if (!str || !strlen(str))
        return "";

    arr = explode(str, "/");
    if (sizeof(arr) >= 4)
        return arr[4];
    else
        return "";
}

/*
 * Function name: random_herbs
 * Description  : Generates up to 4 random herbfiles from a given array.
 * Arguments    : herbs - A string array containing herb files. If fewer
 *                        than four elements are in the passed array, the
 *                        function returns all of them.
 * Returns      : A string array containing as many as 4 herbfiles randomly
 *                selected from the passed 'herbs' array.
 */
public mixed
random_herbs(string *tempherbs)
{
    int i;
    string *arr,
           rand;

    if (sizeof(tempherbs) <= 3)
        return tempherbs;

    arr = ({});

    for (i = 0; i < 3; i++)
    {
        rand = tempherbs[random(sizeof(tempherbs))];
        arr += ({HERBPATH + rand});
        tempherbs -= ({rand});
    }

    return arr;
}

/*
 * Function name: setup_my_herbs
 * Description  : Adds the actual herbs to a room. This function is
 *                typically called from a baseroom, but can be called
 *                in an actual room, with an argument passed that will
 *                prevent herbs from being added to the room.
 * Arguments    : no_herbs - Optional integer, any positive value will
 *                           prevent herb placement.
 * Returns      : n/a
 */
public varargs void
setup_my_herbs(int no_herbs = 0)
{
    string *tempherbs,
           subdir;
    int special;
 
  /* Test for 'no_herbs' var, if NO_HERBS do nothing, if */
  /* NO_HERB_FILES, just add props. */  
    if (no_herbs == NO_HERB_FILES)
    {
        TO->add_prop(OBJ_S_SEARCH_FUN, "herb_search");
        TO->add_prop(OBJ_I_SEARCH_TIME, 5);
        return;
    }

    if (no_herbs == NO_HERBS)
        return;

  /* Abort if this room already has a search fun set. */ 
    if (TO->query_prop(OBJ_S_SEARCH_FUN))
        return;

  /* Make sure this room is one that has herbs listed. */
    if (!strlen(subdir = resolve_dir(file_name(TO))))
        return;

    if (!TO->query_herb_files())
    {
        if (!allherbs[subdir])
            return;

 
      /* Get a listing of possible herbs to select from, based on which */
      /* directory this is. */
        tempherbs = allherbs[subdir];
    }
    else
    {
        tempherbs = TO->query_herb_files();
        TO->remove_herb_files();
    }

  /* Add the herbs and search routines. */
    set_up_herbs(random_herbs(tempherbs));    
}

public void
reset_room()
{
    TO->set_searched(random(2));
}       
