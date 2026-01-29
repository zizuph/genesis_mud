#pragma strict_types
#pragma save_binary
#pragma no_clone

#include <macros.h>

mapping uniques;
static mapping current;

/*
 * Function name: create
 * Description  : Starts up the unique master.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create()
{
    current = ([]);
    restore_object(MASTER);
    if (!mappingp(uniques))
        uniques = ([]);
}

/*
 * Function name: query_uniques
 * Description  : Queries the 'uniques' mapping.
 * Arguments    : n/a
 * Returns      : Mapping describing the 'uniques' var.
 */
public mapping
query_uniques()
{
    return uniques + ([]);
}

/*
 * Function name: purge_uniques
 * Description  : Resets the 'uniques' variable to a
 *                blank mapping.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
purge_uniques()
{
    uniques = ([]);
    setuid();
    seteuid(getuid());
    save_object(MASTER);
}

/*
 * Function name: remove_uniques
 * Description  : Removes an entry from the 'uniques' variable.
 * Arguments    : string str - the filepath of the unique object
 *                             to remove from the 'uniques' var.
 * Returns      : n/a
 */
public void
remove_uniques(string str)
{
    uniques = m_delete(uniques, str);
    setuid();
    seteuid(getuid());
    save_object(MASTER);
}

/*
 * Function name: query_current
 * Description  : Queries the 'current' variable, containing all
 *                the unique weapons which have checked in.
 * Arguments    : n/a
 * Returns      : mapping containing the 'current' var.
 */
public mapping
query_current()
{
    return current + ([]);
}

/*
 * Function name: add_unique
 * Description  : Adds a new object to the 'unique' mapping for
 *                this file to track.
 * Arguments    : string what - filename of the object to make unique.
 *                int num - the number of instances of the unique 
 *                          object allowed. Default is 1.
 *                string rep - filename of the replacement object, if
 *                             any. Default is no replacement.
 * Returns      : n/a
 */
public varargs void
add_unique(string what, int num = 1, string rep = "")
{
    if (!mappingp(uniques))
        uniques = ([]);
    uniques[what] = ({num, rep});
    setuid();
    seteuid(getuid());
    save_object(MASTER);
}

/*
 * Function name: check_unique
 * Description  : Checks to see if the previous object is unique, 
 *                and if so, decides whether to allow it in the game,
 *                or to destruct it and replace it if necessary.
 * Arguments    : n/a
 * Returns      : 0 - Object was destroyed as exceeding unique limit.
 *                1 - Object is not violating unique limits, if any.
 */
public int
check_unique()
{
    string str;
    object what,
           who;

  /* Get the object to test. */
    what = previous_object();

  /* Get the object to test's environment, if the object exists, */
  /* otherwise ignore it. */
    if (what)
        who = environment(what);
    else
        return 1;

  /* Ignore the object if it doesn't have an environment. */
    if (!who)
        return 1;
  
  /* Get the file name of the object to test. */
    str = MASTER_OB(what);

  /* Ignore the object if it's filename isn't in the uniques var. */
    if (!uniques[str])
        return 1;

  /* If there are currently the max. number of objects matching */
  /* the determined filename, dest the object and replace it if */
  /* necessary. */
    if (current[str] && (current[str] >= uniques[str][0]))
    {
        if (strlen(uniques[str][1]))
        {
            what->remove_object();
            clone_object(uniques[str][1])->move(who);
        }
        else
            what->remove_object();
        return 0;
    }

  /* Otherwise if the object is a unique, but below the limit, */
  /* increment the 'current' mapping and let it go. */
    else if (current[str])
        current[str] += 1;
    else
        current[str] = 1;

    return 1;
}

public string
clone_check(string str)
{
    if (!uniques[str] || !uniques[str][0] || !current[str])
        return str;

    if (current[str] >= uniques[str][0])
        return uniques[str][1];
}
