/*
 * - /d/Avenir/union/adverbs.c
 *
 * This parses custom Union Adverbs.
 * It's basically a trimmed down version of
 * /sys/global/adverbs.c with added functionality.
 *
 * There are two versions of each variable, one which all normal
 * operations are based on, and a master one that the Elders may
 * administer and update at later times (or when file is loaded).
 *
 * This is done to maintain the 'anonymity' of the Elders by allowing
 * them to update things right away and have them take effect later.
 *
 * Revisions:
 *   Lucius, Oct  07, 2005: Moved more functionality into this file
 *       from the cmd souls to limit points of failure and keep most
 *       of the functions and functionality in one central spot.
 */
#pragma no_clone
#pragma no_inherit
#pragma no_shadow
#pragma strict_types

#include "defs.h"

#include <macros.h>
#include <adverbs.h>

#define DEFAULT_UADVERBS  ({ "reticently" })

private static string *adverbs = ({ }), *uadverbs = ({ });
private static mapping r_adverbs = ([ ]), r_uadverbs = ([ ]);


/*
 * Parses adverb replacements.
 */
private void
parse_replacements(void)
{
    string *tmp = ({ });

    foreach(string adverb: uadverbs)
    {
	string *arr;

	if (!wildmatch("*:*", adverb))
	    continue;

	tmp += ({ adverb });
	arr = explode(adverb, ":");
	r_uadverbs[arr[0]] = arr[1];
    }

    if (sizeof(tmp))
	uadverbs -= tmp;

    if (!m_sizeof(r_adverbs))
	r_adverbs = secure_var(r_uadverbs);
}

public void
create(void)
{
    setuid();
    seteuid(getuid());

    if (file_size(UNION_ADVERBS) > 5)
	uadverbs = explode(read_file(UNION_ADVERBS), "\n");
    else
	uadverbs = DEFAULT_UADVERBS;

    parse_replacements();

    if (!sizeof(adverbs))
	adverbs = secure_var(uadverbs);
}

private int
pattern_is_adverb(string pattern, int position)
{
    return wildmatch(pattern + "*", adverbs[position]);
}

private int
member_adverb(string pattern)
{
    int low, high, half;

    /* Not a real adverb. */
    if (member_array(pattern, SERVICE_ADVERBS_ARRAY) != -1)
        return -2;

    /* You need at least three characters to identify an adverb. */
    if (strlen(pattern) < 3)
        return -1;

    low = 0;
    high = sizeof(adverbs) - 1;

    while ((low + 1) < high)
    {
        half = ((low + high) / 2);

        if (pattern < adverbs[half])
        {
            high = half;
            continue;
        }

        low = half;
    }

    if (pattern_is_adverb(pattern, low))
        return low;

    if (pattern_is_adverb(pattern, high))
        return high;

    return -1;
}

/*
 * Called by the union shadow to test for a custom adverb.
 */
public string
full_adverb(string pattern)
{
    int index = member_adverb(pattern);

    if (index == -2)
	return pattern;

    if (index == -1)
	return NO_ADVERB;

    if (stringp(r_adverbs[adverbs[index]]))
        return r_adverbs[adverbs[index]];

    return adverbs[index];
}

public string *
query_all_adverbs(void)
{
    return secure_var(adverbs);
}

public string *
query_all_uadverbs(void)
{
    return secure_var(uadverbs);
}

private void
save_adverbs(void)
{
    string *arr = m_indices(r_uadverbs), *list = secure_var(uadverbs);
    int size = sizeof(arr);

    while(size--)
	list += ({ arr[size] + ":" + r_uadverbs[arr[size]] });

    rename(UNION_ADVERBS, UNION_ADVERBS + ".bak");
    write_file(UNION_ADVERBS, implode(sort_array(list), "\n") + "\n");
}

/*
 * Called by the elder_soul to administer the Union adverbs.
 */
public varargs int
update_adverbs(int flag, string adv, string *rep)
{
    switch(flag)
    {
    case 1:  /* Add adverb */
	if (!strlen(adv) || IN_ARRAY(adv, uadverbs))
	    return 0;

        uadverbs += ({ adv });
	save_adverbs();
	break;

    case 2:  /* Add replacement */
	if (!strlen(adv) || !pointerp(rep) || stringp(r_uadverbs[adv]))
	    return 0;

	if (!IN_ARRAY(adv, uadverbs))
	    uadverbs += ({ adv });

	r_uadverbs[adv] = implode(rep, " ");
	save_adverbs();
	break;

    case 3:  /* Remove adverb */
	if (!strlen(adv) || !IN_ARRAY(adv, uadverbs))
	    return 0;

        uadverbs -= ({ adv });
	save_adverbs();
	break;

    case 4:  /* Remove replacement */
	if (!strlen(adv) || !stringp(r_uadverbs[adv]))
	    return 0;

	if (IN_ARRAY(adv, uadverbs))
	    uadverbs -= ({ adv });

	m_delkey(r_uadverbs, adv);
	save_adverbs();
	break;

    default: /* Update */
	r_adverbs = ([ ]);
	adverbs = ({ });
	create();
	break;
    }

    return 1;
}

private static string alphabet = "abcdefghijklmnopqrstuvwxyz";

/*
 * Called locally by show_adverbs to do the actual printed output.
 */
private string
list_adverbs(string *list)
{
    string res, *words;
    int index = -1, size = strlen(alphabet);

    res = "Shadow Union adverbs are:\n-------------------------\n\n";

    while(++index < size)
    {
	words = filter(list, &wildmatch((alphabet[index..index] + "*"), ));

	if (!sizeof(words))
	    continue;

	if (strlen(words[0]) < 16)
	    words[0] = (words[0] + "                ")[..15];

	res += sprintf("%#-76s\n\n", implode(words, "\n"));
    }

    index = -1; size = sizeof(list); words = ({ });

    while(++index < size)
    {
	if (strlen(r_adverbs[list[index]]))
	{
	    words += ({ sprintf("%16s : %s\n",
		list[index], r_adverbs[list[index]]) });
	}
    }

    if (sizeof(words))
    {
	res += "Of these, the following adverbs are replaced with a "+
	    "more suitable phrase:\n\n" + implode(words, "") + "\n";
    }

    return res;
}

/*
 * Called by the 'uadverbs' command to print out a listing of
 * Union specific adverbs similiar to the mudlib 'adverbs' command.
 */
public varargs string
show_adverbs(string str, int flag)
{
    int ix, size;
    string *list, *parts, *words;

    if (!strlen(str))
	return "";

    if (wildmatch("replace*", str))
    {
	string res;

	if (!m_sizeof(r_adverbs))
	    return "There are no adverb replacements to list.\n";

	res = "The following Union adverbs are replaced with a "+
	    "more suitable phrase:\n\n";

	list = sort_array(m_indices(r_adverbs));
	ix = -1; size = sizeof(list);

	while(++ix < size)
	    res += sprintf("%16s : %s\n", list[ix], r_adverbs[list[ix]]);

	return res;
    }

    list = (flag ? secure_var(uadverbs) : secure_var(adverbs));

    if (str == "*" || str == "all")
	return list_adverbs(list);

    parts = explode(implode(explode(lower_case(str), " "), ""), ",");
    ix = -1; size = sizeof(parts); words = ({ });

    while(++ix < size)
    {
	if (strlen(parts[ix]) == 1)
	    parts[ix] += "*";

	words |= filter(list, &wildmatch(parts[ix], ));
    }

    if (!sizeof(words))
	return "No adverbs found with those specifications.\n";

    return list_adverbs(sort_array(words));
}
