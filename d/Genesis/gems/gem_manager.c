/*
 * /d/Genesis/gems/gem_manager.c
 *
 * This module contains the routines related to the gem system.
 *
 * All gems must be registered here.
 * Domain gems can be registered by defining query_gem_list in domain_link.c
 */

#pragma no_clone
#pragma no_inherit
#pragma strict_types
#pragma no_shadow

#include "gem.h"

#include <files.h>
#include <macros.h>
#include <stdproperties.h>

/*
 * Global variables.
 */
static mapping all_gems = ([ ]);
static string *all_names;
static int *all_rarities;

/*
 * Prototype.
 */
nomask mixed query_gem_property(string name, int index);

/*
 * Function name: sort_gem_rarity
 * Description  : Sorter for the gems. Designed to make the order of
 *                decreasing rarity of gems.
 * Arguments    : string name1: - the name of the first gem to check.
 *              : string name2: - the name of the second gem to check.
 * Returns      : int -1/0/1 - smaller/equal/larger.
 */
int
sort_gem_rarity(string name1, string name2)
{
    if (all_gems[name1][GEM_INDEX_RARITY] == all_gems[name2][GEM_INDEX_RARITY])
    {
        return 0;
    }
    return ((all_gems[name1][GEM_INDEX_RARITY] > all_gems[name2][GEM_INDEX_RARITY]) ? 1 : -1);
}

/*
 * Function name: load_gems
 * Description  : Generates the basic index of the gem master with all gems
 *                in the directory of Genesis gems.
 */
static void
load_gems()
{
    object *links = map(SECURITY->query_domain_links() , find_object) - ({ 0 });

    foreach (object link: links)
    {
        string *files = link->query_gem_list();

        if (!pointerp(files))
            continue;

        foreach (string filename: files)
        {
            /* Remove the .o if any. */
            if (sscanf(filename, "%s.c", filename))
                continue;

            if (LOAD_ERR(filename))
                continue;

            all_gems[filename] = ({
                    filename->query_gem_type(),
                    filename->query_gem_ptype(),
                    filename->query_gem_colour(),
                    filename->query_gem_rarity(),
                    filename->query_prop(HEAP_I_UNIT_VALUE),
                    filename->query_prop(HEAP_I_UNIT_VOLUME),
                    filename->query_prop(HEAP_I_UNIT_WEIGHT),
                    filename->query_random_placement()
                });
        }
    }
}

/*
 * Function name: register_gem
 * Description  : Service function for domains to register gems.
 * Arguments    : string filename - the filename of the gem.
 *                string type - the type of the gem.
 *                string ptype - the plural type of the gem.
 *                string colour - the colour of the gem.
 *                int rarity - the rarity of the gem.
 *                int value - the value of the gem in cc.
 *                int volume - the volume of the gem in ml.
 *                int weight - the weight of the gem in gram.
 */
public void
register_gem(string filename, string type, string ptype, string colour,
    int rarity, int value, int volume, int weight)
{
    /* Remove the .c if any. */
    sscanf(filename, "%s.c", filename);

    all_gems[filename] = ({ type, ptype, colour, rarity, value, volume, weight });

    /* Get all gem names and sort the array according to rarity. */
    all_names = sort_array(m_indices(all_gems), "sort_gem_rarity");
    /* Get the rarities of the gems in the same order. */
    all_rarities = map(all_names, &query_gem_property(, GEM_INDEX_RARITY));
}

/*
 * Function name: create
 * Description  : Constructor. We use this to sort the all_names array in
 *                order of decreasing rarity of gems.
 */
void
create()
{
    setuid();
    seteuid(getuid());

    load_gems();
    /* Get all gem names and sort the array according to rarity. */
    all_names = sort_array(m_indices(all_gems), "sort_gem_rarity");
    /* Get the rarities of the gems in the same order. */
    all_rarities = map(all_names, &query_gem_property(, GEM_INDEX_RARITY));
}

/*
 * Function name: identify_gems
 * Description  : Finds out which gems could be meant with a certain name.
 * Arguments    : string str - the text to match.
 * Returns      : string * - the array of gems that matches, or ({ }).
 */
public mixed
identify_gems(string str)
{
    string *result = ({ });

    foreach(string name: m_indices(all_gems))
    {
        if ((str == all_gems[name][GEM_INDEX_TYPE]) ||
            (str == all_gems[name][GEM_INDEX_PTYPE]) ||
            (str == (all_gems[name][GEM_INDEX_COLOUR] + " "+ all_gems[name][GEM_INDEX_TYPE])) ||
            (str == (all_gems[name][GEM_INDEX_COLOUR] + " "+ all_gems[name][GEM_INDEX_PTYPE])))
        {
            result += ({ name });
        }
    }

    return result;
}

/*
 * Function name: query_gem_properties
 * Description  : Returns an array with the properties of a gem type.
 * Arguments    : string name - the (file) name of the gem.
 * Returns      : mixed - the array with properties.
 */
nomask mixed
query_gem_properties(string name)
{
    return secure_var(all_gems[name]);
}

/*
 * Function name: query_gem_property
 * Description  : Get an individual property of a gem.
 * Arguments    : string name - the (file) name of the gem.
 * Returns      : mixed - the value of the property (int or string).
 */
nomask mixed
query_gem_property(string name, int index)
{
    /* Access failure, not a valid name of a gem. */
    if (!pointerp(all_gems[name]))
    {
        return 0;
    }
    return all_gems[name][index];
}

/*
 * Function name: query_gem_names
 * Description  : Get the names of all gems that are of the given rarity or
 *                less rare. If GEM_ALL or an invalid rarity, then all gems
 *                are returned.
 * Arguments    : int rarity - the required rarity (or less rare) or GEM_ALL
 * Returns      : string * - the list of gem (file) names.
 */
nomask string *
query_gem_names(int rarity)
{
    int index;

    index = member_array(rarity, all_rarities);
    if (index == -1)
    {
        return secure_var(all_names);
    }
    return all_names[index..];
}

/*
 * Function name: query_gem_names_of_rarity
 * Description  : Returns all gems of exactly the requested rarity. Instead
 *                of using GEM_ALL on this routine, use query_gem_names() to
 *                get all gems.
 * Arguments    : int rarity - the requested rarity or GEM_ALL.
 * Returns      : string * - the gem (file) names.
 */
nomask string *
query_gem_names_of_rarity(int rarity)
{
    return filter(all_gems, &operator(==)(rarity, ) @
        &query_gem_property(, GEM_INDEX_RARITY));
}

/*
 * Function name: random_gem
 * Description  : Get a gem of a certain rarity or less rare. It just
 *                picks one gem from the list.
 *                THIS IS NOT WHAT YOU WANT!
 * Arguments    : int rarity - the requested rarity or GEM_ALL
 * Returns      : object - the object of the gem, or 0.
 */
nomask object
random_gem(int rarity = -1)
{
    string *gems;

    gems = query_gem_names(rarity);

     /* Can the gems be randomly placed? */
    gems = filter(gems, &operator([])(, GEM_INDEX_RANDOM) @ &operator([])(all_gems, ));

    if (!sizeof(gems))
        return 0;

    setuid();
    seteuid(getuid());

    return clone_object(one_of_list(gems));
}

/*
 * Function name: random_gem_by_rarity
 * Description  : Get a gem of a certain rarity or less rare. It considers
 *                the rarity of the gems.
 * Arguments    : int rarity - the requested rarity or GEM_ALL
 * Returns      : object - the object of the gem, or 0.
 */
nomask varargs object
random_gem_by_rarity(int rarity = -1)
{
    string *gems = query_gem_names(rarity);

    /* Can the gems be randomly placed? */
    gems = filter(gems, &operator([])(, GEM_INDEX_RANDOM) @ &operator([])(all_gems, ));

    if (!sizeof(gems))
        return 0;

    int sum;
    foreach (string gem: gems) {
        sum += all_gems[gem][GEM_INDEX_RARITY];
    }
    int ran = random(sum);

    int progress;
    foreach (string gem: gems) {
        progress += all_gems[gem][GEM_INDEX_RARITY];

        if (progress >= ran)
        {
            return clone_object(gem);
        }
    }

    /* Should never get here */
}
