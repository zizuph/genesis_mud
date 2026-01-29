#include <wa_types.h>
#include <language.h>
#pragma strict_types
#pragma save_binary
#include <tattoo_data.h>
#include <composite.h>

/*
 * Function name: query_location_names
 * Description: Returns either the name of a given abbreviated location
 *              or dumps the whole list.  Note that it also tests for
 *              a bad test abbreviation by returning the entire array
 *              as well.
 * Arguments: arg - an optional string. If supplied it must be a valid 
 *            index from tattoo_cover mapping.
 * Returns: Either a string containing the full name of the supplied
 *          abbreviation, or an array containing all of them.
 */
public nomask varargs mixed
query_location_names(string arg)
{
    string *temp;
    int i;
    
    if (arg && strlen(arg) && tattoo_cover[arg])
    {
        return tattoo_cover[arg][1];
    }
    else
    {
    temp = ({});
    for (i = 0; i < sizeof(m_values(tattoo_cover)); i++)
        temp += ({m_values(tattoo_cover)[i][1]});  
    }

    return temp;
}

/*
 * Function name: query_location_abbreviation
 * Description: Returns either the appropriate abbreviation for a given
 *              full location name, or a list of all abbreviations.
 * Arguments: An optional string that is the full name of a tattoo location.
 * Returns: If no argument given, the entire list of abbreviated tattoo
 *          locations. Otherwise returns a string containing the appropriate
 *          abbreviated location.
 */
public nomask varargs mixed
query_location_abbreviation(string str)
{
    int i;
    string location;

    if (strlen(str))
    {
        for (i = 0; i < sizeof(m_values(tattoo_cover)); i++)
        {
            if (m_values(tattoo_cover)[i][1] == str)
            {
                location = m_indexes(tattoo_cover)[i];
                break;
            }
        }
        return location;
    }
    else
    {
        return m_indexes(tattoo_cover);
    }
}

/*
 * Function name: query_armours
 * Description: Returns a description of armours worn over a given location
 * Arguments: str - A string identifying which location to check.
 *            who - A pointer to the player object calling this function.
 * Returns: A string containing the short(s) of the found armour(s).
 */
public nomask string
query_armours(string str, object who)
{
    string *desc = ({});

    foreach(int slot: tattoo_cover[str][0])
    {
        object *items = who->query_clothing(slot);
        if (sizeof(items))
            desc += filter(items->short(), strlen);
    }

    if (sizeof(desc))
        return COMPOSITE_WORDS(desc);
    else
        return "";
}

/*
 * Function name: query_tattoo_adjs
 * Description: Generates either a list of available adjectives, or
 *              verifies existance of supplied tattoo in the list.
 * Arguments: str - an optional string, the adjective to test.
 * Returns: If testing a string - array index for good adj
 *                                -1 for bad adj
 *          Otherwise - An array containing all the adjectives
 */
public nomask varargs mixed
query_tattoo_adjs(string str)
{
    if(!str || !strlen(str))
        return tattoo_adj;

    else
        return (member_array(str, tattoo_adj));
}

/*
 * Function name: query_tattoo_design
 * Description: Verifies existance of tattoo designs
 * Arguments: An integer marking the design array index
 * Returns: 0 - bad design
 *          1 - good design
 */
public nomask mixed
query_tattoo_design(int i)
{
    if (!tattoo_design[i] || !strlen(tattoo_design[i]))
        return 0;
    else
        return 1;
}

/*
 * Function name: make_design
 * Description: Accepts a design description and two adjectives, and
 *              then generates an actual design string that people
 *              see.
 * Arguments: design - A design element from the tattoo_design array.
 *            str1 - an adjective.
 *            str2 - another adjective.
 * Returns: A 'clean' string description of the design.
 */
string
make_design(int design, string str1, string str2)
{
string *darr, a, b, c;
int i;

    darr = explode(tattoo_design[design], " ");

    for (i = 0; i < sizeof(darr); i++)
    {
        if (sscanf(darr[i], "%s##%s##%s", b, a, c) == 3)
        {
        if (a == "LADJECTIVE1")
            darr[i] = b+LANG_ADDART(str1)+c;
        else if (a == "LADJECTIVE2") 
            darr[i] = b+LANG_ADDART(str2)+c;
        else if (a == "ADJECTIVE1")
            darr[i] = b+str1+c;
        else if (a == "ADJECTIVE2")
            darr[i] = b+str2+c;
        }
    }

    a = implode(darr, " ");

    return a;
}

/*
 * Function name: query_sensitive_location
 * Description: Tells if the given location should be default concealed,
 *              i.e. breasts, buttocks, thighs, etc.
 * Arguments: str - the tattoo location (abbrev)
 * Returns: 1 - concealed
 *          0 - visible
 */
public nomask int
query_sensitive_location(string str)
{
    if (member_array(str, sensitive_locations) >= 0)
        return 1;
    else
        return 0;
}

/*
 * Function name: query_guild_design
 * Description: Returns true/false that the given index refers to a guild
 *              tattoo.
 * Arguments i - an integer representing an index in the tattoo_design array.
 * Returns: 1 - Yes, the index is a guild
 *          0 - No, the index isn't a guild.
 */
public nomask int
query_guild_design(int i)
{
    int j;

    for (j = 0; j < sizeof(m_values(guild_tattoos)); j++)
    {
        if (m_values(guild_tattoos)[j][3] == i)
            return 1;
    }
    return 0;
}
