/*
   Taken from the Eil-Galaith server code. -- Tomas 12/2005
*/

#pragma no_clone
#pragma no_inherit
#pragma strict_types

#include "include/explorer.h"

private mapping members = ([]);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * The save and function for the data.
 * This should always return 1.
 */
private varargs int
save(int no_save)
{
    if (!no_save)
        save_object(file_name(this_object()));
    return 1;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * The member administration functions.
 */
public int
add_member(string who)
{
    if (!strlen(who))
        return 0;

    MLC(who); 

    if (members[who])
       return 0;

    members[who] = ({ time(), 0 });
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

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * The create function, to initialize variables upon load.
 */
public void
create()
{
    setuid(); seteuid(getuid());

 //   if (!restore_object(SAVE))
}
