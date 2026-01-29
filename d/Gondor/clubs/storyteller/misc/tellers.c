/*
 * Revisions:
 * Updated file so any wizard can make changes
 * - Finwe, February 2018
 */

#include <std.h>
#include <files.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/clubs/storyteller/defs.h"

#define TELLER_SAVE   "/d/Gondor/clubs/storyteller/misc/teller_save"

mapping       Tellers = ([ ]);
string 	      *Librarians = ({ });
string	      *Banned = ({ });

public nomask void
create()
{
    FIX_EUID;
    restore_object(TELLER_SAVE);
    seteuid(0);

}

public nomask int
add_member(string name, int age)
{
    name = CAP(LOW(name));
    FIX_EUID;
    if (member_array(name, m_indexes(Tellers)) >= 0)
        return -1;    // Already a member, do not add again.
    Tellers[name] = ({ 1, age });
    save_object(TELLER_SAVE);
    return 1;
}

public nomask int
remove_member(string name)
{
    name = CAP(LOW(name));
    FIX_EUID;
    if (member_array(name, m_indexes(Tellers)) < 0)
        return -1;
    Tellers = m_delete(Tellers, name);
    save_object(TELLER_SAVE);
    return 1;
}

public nomask int
query_member(string name)
{
    name = CAP(LOW(name));

    if (member_array(name, m_indexes(Tellers)) == -1)
	return 0;

    return Tellers[name][0];
}

public nomask int
query_join_age(string name)
{
    name = CAP(LOW(name));
    FIX_EUID;
    if (member_array(name, m_indexes(Tellers)) == -1)
        return 0;    // Not a member

    return Tellers[name][1];
}

public nomask int
authenticate(object ob)
{
//    if (SECURITY->query_wiz_rank(ob->query_real_name()) == WIZ_ARCH ||
//        SECURITY->query_wiz_dom(ob->query_real_name()) == "Gondor" ||
//	ob->query_name() == "Morrigan")

    if (this_player()->query_wiz_level())
        return 1;

    return 0;
}

public nomask int
add_librarian(string name)
{
    name = CAP(LOW(name));
    FIX_EUID;

    if (!authenticate(this_player()))
	return 0;

    if (member_array(name, m_indexes(Tellers)) < 0)
        return 0;

    if (member_array(name, Librarians) != -1)
	return 0;

    if (!sizeof(Librarians))
	Librarians = ({ name });
       else
        Librarians += ({ name });

    save_object(TELLER_SAVE);
    return 1;
}

public nomask string
*query_librarians()
{
    return Librarians;
}

public nomask int
query_librarian(string name)
{
    name = CAP(LOW(name));
    FIX_EUID;

    if (member_array(name, Librarians) == -1)
        return 0;

    return 1;
}

public nomask int
remove_librarian(string name)
{
    name = CAP(LOW(name));
    FIX_EUID;

    if (file_name(previous_object()) != (STORYT_DIR + "rooms/foyer") &&
        !authenticate(this_player()))
	return 0;

    if (member_array(name, Librarians) == -1)
        return 0;

    Librarians -= ({ name });
    save_object(TELLER_SAVE);
    return 1;
}

public nomask int
ban_player(string name)
{
    name = CAP(LOW(name));
    FIX_EUID;

    if (!authenticate(this_player()))
	return 0;

    /* If a player is a member, remove him */
    if (member_array(name, m_indexes(Tellers)) != -1)
    {
        remove_member(name);
    }

    /* If a player is a librarian, remove him */
    if (member_array(name, Librarians) != -1)
    {
        remove_librarian(name);
    }

    if (member_array(name, Banned) != -1)
	return 0;

    if (!sizeof(Banned))
	Banned = ({ name });
       else
        Banned += ({ name });

    save_object(TELLER_SAVE);
    return 1;
}

public nomask int
pardon_player(string name)
{
    name = CAP(LOW(name));
    FIX_EUID;

    if (!authenticate(this_player()))
	return 0;

    if (member_array(name, Banned) == -1)
        return 0;

    Banned -= ({ name });
    save_object(TELLER_SAVE);
    return 1;
}

public nomask int
query_banned(string name)
{
    name = CAP(LOW(name));
    FIX_EUID;

    if (member_array(name, Banned) == -1)
        return 0;

    return 1;
}
