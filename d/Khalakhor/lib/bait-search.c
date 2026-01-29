/*
 * bait-search.c
 * This file is inherited in rooms that you want to be searchable 
 * for fishing bait.
 * This file contains the search function of the room. It will
 * try and see if another search function already was defined,
 * for example for herb searching, and if so call it if the 
 * search string doesn't matches the configured search.
 * Treacher, Sept 2021
*/
#pragma strict_types

#include <ss_types.h>
#include <composite.h>
#include <language.h>
#include <macros.h>

int _baits_present = 0;
int _baits_max = 0;
string _bait_file;
string *_places = ({});
mixed _overridden_search_fun = 0;

string *_bait_search_strings = ({
    "You search for something that could work as bait, " +
        "but you are unlucky and find nothing.",
    "You search for something that could work as bait, " +
        "but there doesn't seem to by anything more to be found here.",
    "Your search is fruitful and you find a %s!",
    "searches thoroughly and finds a %s!"
});

string
search_for_baits(object searcher, string arg)
{
    if(member_array(arg, _places) == -1)
    {
        //Check if overriden search function should be called
        if(_overridden_search_fun)
            return call_other(this_object(), _overridden_search_fun, searcher, arg);
        return 0;
    }

    if(_baits_present <= 0)
    {
      return _bait_search_strings[1] + "\n";
    }
    
    _baits_present -= 1;

    int skill_hunt = searcher->query_skill(SS_HUNTING);
    // 50% chance with superior layman hunting skill, to find a bait 
    if(random(60) > skill_hunt)
    {
       return _bait_search_strings[0] + "\n";
    }

    object bait;
    if(catch(bait = clone_object(_bait_file)))
    {
        return "You feel that something should have been within your grasp, but is missing. " +
               "Maybe you should report to higher authorities about this.\n";
    }

    // 15% chance with superior layman hunting skill, that the bait is a big specimen 
    if(random(200) < skill_hunt)
    {
        bait->make_big();
    }
    bait->move(searcher);
    say(QCTNAME(this_player()) + " " + sprintf(_bait_search_strings[3], bait->query_short()) + "\n");
    return sprintf(_bait_search_strings[2] + "\n", bait->query_short());
}

/*
 * Function name: reset_baits
 * Description:   Resets number of baits available in the room.
 *                Should be called in the rooms reset_room
 */
void
reset_baits()
{
    _baits_present = random(_baits_max + 1);
}

/*
 * Function name: set_up_bait_strings
 * Description:   Sets up the description strings when searching for baits,
 *                if the defaults shouldn't be used
 * Arguments:     bait_strings: Array of strings used for search results
 *                     0: Displayed when search failed
 *                     1: Displayed when room is out of bait
 *                     2: Displayed after successful search.
 *                        Must include pattern %s for bait short desc
 *                     3: Displayed to others in the room after successful serach
 *                        Must include pattern %s for bait short desc
 *
 */       
void
set_up_bait_strings(string *bait_strings)
{
    _bait_search_strings = bait_strings;
}

/*
 * Function name: set_up_baits
 * Description:   Add baits to the room, with default strings as search results.
 * Arguments:     bait_file: Filename of the bait
 *                places:    Array of names of items that can be searched to find baits
 *                max_baits: Max numbers of baits that can be set up at room reset
 *                           Number of baits will be random between 0 and max
 */
varargs int
set_up_baits(string bait_file, string *places, int max_baits = 3)
{
    if(strlen(bait_file) == 0)
        return 0;

    _bait_file = bait_file;
    _places = places;
    _baits_max = max_baits;

    mixed old_prod = this_object()->query_prop(OBJ_S_SEARCH_FUN);
    if(old_prod)
        _overridden_search_fun = old_prod;
    this_object()->add_prop(OBJ_S_SEARCH_FUN, "search_for_baits");

    reset_baits();

    return 1;
}
