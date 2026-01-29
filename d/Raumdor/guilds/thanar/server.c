/**********************************************************************
 * - server.c                                                       - *
 * - Thanar human race guild server                                 - *
 * - Original code Created by Lucius                                - *
 * - Modified by Damaris@Genesis 3/2004                             - *
 **********************************************************************/

#pragma no_clone
#pragma no_inherit
#pragma strict_types

#include "guild.h"

private mapping members = ([]);
private mapping covens  = ([]);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * The save and function for the data.
 * This should always return 1.
 */
private varargs int
save(int no_save)
{
    if (!no_save)
        save_object(SAVE);
    return 1;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * The coven administration functions.
 */
public varargs int
update_covens(int delete)
{
    int sz;
    string *tmp;

    /*
     * This simply adds in new covens into the server and synchs
     * up coven colours from the defined values in case they changed.
     */
    tmp = m_indexes(COVENS); sz = sizeof(tmp);
    while (--sz >= 0)
    {
        if (!covens[tmp[sz]])
        {
            covens[tmp[sz]] = ([]);
        }

        covens[tmp[sz]][COVEN_CLRS] = COVENS[tmp[sz]][COVEN_CLRS];
    }

    /*
     * This will remove covens that are no longer defined and
     * will make members of the defunct coven, covenless.
     * Use with extreme discretion.
     */
    if (delete)
    {
        tmp = m_indexes(covens); sz = sizeof(tmp);
        while (--sz >= 0)
        {
            if (!(COVENS[tmp[sz]]))
            {
                string *arr = m_indexes(covens[tmp[sz]]) - ({ COVEN_CLRS });
                int    size = sizeof(arr);

                while (--size >= 0)
                {
                    members[arr[size]][CNAME] = 0;
                }
                covens = m_delete(covens, tmp[size]);
            }
        }
    }
    return save();
}

public int
add_to_coven(string who, string coven, string by)
{
    if (!strlen(who) || !strlen(coven) || !strlen(by))
        return 0;

    MLC(who); MLC(by); MCAP(coven);

    if (!members[who] || !members[by])
        return 0;

    if (!covens[coven])
        return 0;

    if ((who != by) && (members[by][CNAME] != coven))
        return 0;

    members[who][CNAME] = coven;
    covens[coven][who] = ({ time(), by });
    return save();
}

public int
remove_from_coven(string who, string by)
{
    string coven;

    if (!strlen(who) || !strlen(by))
        return 0;

    MLC(who); MLC(by);

    if (!members[who] || !members[by])
        return 0;

    coven = members[who][CNAME];

    if (members[by][CNAME] != coven)
        return 0;

    members[who][CNAME] = 0;
    covens[coven] = m_delete(covens[coven], who);
    return save();
}

public mixed
query_coven(string arg)
{
    if (!strlen(arg))
        return secure_var(covens);

    if (arg == "all")
    {
        if (!m_sizeof(covens))
            return ({});

        return secure_var(sort_array(m_indexes(covens)));
    }

    if (covens[MCAP(arg)])
        return secure_var(covens[arg]);

    if (members[MLC(arg)])
        return members[arg][CNAME];
}

public int
set_librarian(string who, int set_as)
{
   if (!strlen(who) )
        return 0;

    MLC(who);

    if (!members[who] )
        return 0;

    members[who][SPEC] = set_as;
    return save();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * The member administration functions.
 */
public int
add_member(string who, string surname, int special)
{
    if (!strlen(who) || !strlen(surname))
        return 0;

    MLC(who); MCAP(surname);

    if (members[who])
        return 0;

    if (member_array(surname, SURNAMES) == -1)
        return 0;

    members[who] = ({ time(), surname, special, 0 });
    return save();
}

public int
change_surname(string who, string surname)
{
    if (!strlen(who) || !strlen(surname))
        return 0;

    MLC(who); MCAP(surname);

    if (!members[who])
        return 0;

    if (member_array(surname, SURNAMES) == -1)
        return 0;

    members[who][FNAME] = surname;

    return save();
}

public int
remove_member(string who)
{
    if (!strlen(who))
        return 0;

    MLC(who);

    if (!members[who])
        return 0;

    remove_from_coven(who, who);
    members = m_delete(members, who);

    return save();
}

public mixed
query_member(string who)
{
    if (!strlen(who))
        return secure_var(members);

    MLC(who);

    if (who == "all")
    {
        if (!m_sizeof(members))
            return ({});

        return secure_var(sort_array(m_indexes(members)));
    }

    if (!members[who])
        return 0;

    return members[who];
}

/* 
 * Function name: query_librarians
 * Description  : Find out the name(s) of the librarian(s).
 * Returns      : string * - array of names.
 */
public string *
query_librarians()
{
    string *names = m_indices(members);
    string *result = ({ });
    int index;

    for (index = 0; index < sizeof(names); index++)
    {
        if ((sizeof(members[names[index]]) > SPEC) && (members[names[index]][SPEC] == 1))
        {
            result += ({ names[index] });
        }
    }
    return result;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * The create function, to initialize variables upon load.
 */
public void
create()
{
    setuid(); seteuid(getuid());

    if (!restore_object(SAVE))
        update_covens();
}
