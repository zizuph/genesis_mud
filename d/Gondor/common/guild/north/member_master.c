#pragma no_clone
#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/object.c";
#include <macros.h>
#include <stdproperties.h>
#include <std.h>
#include "/d/Gondor/defs.h"
#include "lib/ranger_defs.h"
#include "lib/titles.h"

#define MEMBER_SAVE    RANGER_NORTH_DIR + "member_save"
#define NORTH_SHADOW   RANGER_NORTH_DIR + "ranger_shadow"

mapping Rank_members = ([ ]);
mapping Ranger_names = ([ "elessar" : "Strider", ]);
string *Members = ({ });

static int     inited = 0;

int add_member(string name);
int remove_member(string name);
int query_member(string name);
string *query_members();
public void remove_ranger_name(string name);

void
initialize_master()
{
    if (inited)
        return;

    FIX_EUID
    inited = 1;
    restore_object(MEMBER_SAVE);

    if (!Members)
    {
        Rank_members = ([ ]);
        Members = ({ });
        save_object(MEMBER_SAVE);
    }
}

void
create_object()
{
    set_name("ranger_master");
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_M_NO_INS, 1);
    initialize_master();
}

int
add_member(string name)
{
    if (!strlen(name))
        return -1;

    if (!sizeof(Members))
        Members = ({ });
    name = CAP(LOW(name));
    if (member_array(name, Members) >= 0)
    {
        write_file(NORTH_LOG, "Error: " + name + " joins, but is "
          + "already listed as member. " + ctime(time()) + ".\n");
        return 1;
    }
    if (!Rank_members)
        Rank_members[RECRUIT] = ({ name });
    else if (!sizeof(Rank_members[0]))
        Rank_members[RECRUIT] = ({ name });
    else
        Rank_members[RECRUIT] += ({ name });

    Members += ({ name });
    save_object(MEMBER_SAVE);
    return 1;
}

int
find_rank(string name)
{
    int     i, m;

    if (!strlen(name))
        return -1;
    if (member_array(name, Members) < 0)
        return -2;

    m = sizeof(RANK_TITLES);
    while (i < m)
    {
        if (member_array(name, m_values(Rank_members)[i]) >= 0)
            return m_indexes(Rank_members)[i];
        i++;
    }
}

string
find_rank_title(string name)
{
    int     r;
    r = find_rank(name);
    if (r < 0)
        return "Not member";

    return RANK_TITLES[r];
}

int
remove_from_ranks(string name)
{
    int     r;

    r = find_rank(name);
    if (r >= 0)
    {
        Rank_members[r] -= ({ name });
        save_object(MEMBER_SAVE);
        return 1;
    }
    return 0;
}

int
change_rank(string name, int rank)
{
    int     i,
            m;

    name = CAP(LOW(name));
    m = find_rank(name);
    if (m < 0)
        return -1;
    if (m == rank)
        return 0;
    if (rank >= sizeof(RANK_TITLES))
        return -2;
    Rank_members[m] -= ({ name });
    if (!Rank_members[rank] || !sizeof(Rank_members[rank]))
        Rank_members[rank] = ({ name });
    else
        Rank_members[rank] += ({ name });

    save_object(MEMBER_SAVE);
    return 1;
}

int
remove_member(string name)
{
    name = CAP(LOW(name));
    if (member_array(name, Members) == -1)
        return -1;
    Members -= ({ name });
    remove_from_ranks(name);
    remove_ranger_name(name);
    save_object(MEMBER_SAVE);
    return 1;
}

int
new_member(object pl, string rname)
{
    string  name;
    object  shadow;
    object  brooch;
    object  cloak;
    int     result;

    FIX_EUID

    if (!objectp(pl))
    {
        write_file(RANGER_LOG, 
          "NORTH BUG: No object player sent to new_member.\n");
        return -1;
    }

    name = pl->query_real_name();
    shadow = clone_object(NORTH_SHADOW);
    if ((result = shadow->shadow_me(pl, GUILD_TYPE, GUILD_STYLE, GUILD_NAME)) != 1)
    {
        write_file(RANGER_LOG, "NORTH: " + CAP(name) + " could not be shadowed. "
          + "Result: " + result + ". " + ctime(time()) + ".\n");
        SECURITY->do_debug("destroy", shadow);
        pl->catch_msg("Something went wrong! You could not be made a Ranger!\n"
          + "Please mail Elessar about this.\n");
        return 0;
    }
    if ((result = add_member(name)) != 1)
    {
        write_file(RANGER_LOG, "NORTH: " + CAP(name) + " could not be added to "
          + "members. Result: " + result + ". " + ctime(time()) + ".\n");
        pl->catch_msg("Something went wrong! You could not be made a Ranger!\n"
          + "Please mail Elessar about this.\n");
        return 0;
    }
    brooch = clone_object(GUILD_TOKEN);
    brooch->move(pl, 1);
    cloak = clone_object("/d/Gondor/common/guild/north/obj/grey_cloak");
    cloak->move(pl, 1);
    pl->command("$wear cloak");
    pl->command("$wear brooch");
    write_file(NORTH_LOG,
      CAP(name) + " joins the Rangers of the North, recruited by " + CAP(rname)
        + ", " + ctime(time()) + ".\n");
    return 1;
}

int
is_officer(string name)
{
    int     i;
    i = find_rank(name);
    if (i == OFFICER)
        return 1;
    if (i == CAPTAIN)
        return 2;
    return 0;
}

int query_member(string name)
{
    if (member_array(CAP(LOW(name)), Members) >= 0)
        return 1;
    return 0;
}

string *
query_members()
{
    return Members;
}

mixed
query_rank_members(mixed rk)
{
    int rank;
    if (stringp(rk))
    {
        rank = member_array(rk, RANK_TITLES);
    }
    else
        rank = rk;
    if (rank < 0 || rank > CAPTAIN)
        return -1;

    if (Rank_members[rank])
        return Rank_members[rank];
    else
        return "";
}

public string
query_captain()
{
    if (sizeof(query_rank_members(CAPTAIN)))
        return query_rank_members(CAPTAIN)[0];
    return "";
}

string *
query_officer_titles()
{
    return OFFICER_TITLES + ({ });
}

string *
query_elder_titles()
{
    return ELDER_TITLES + ({ });
}

string *
query_ranger_titles()
{
    return RECRUIT_TITLES + TITLES + ({ });
}

string *
query_recruit_titles()
{
    return RECRUIT_TITLES + ({ });
}

public int
add_ranger_name(mixed ranger, string name)
{
    int     change;
    object  player;

    if (stringp(ranger))
        ranger = LOW(ranger);
    else if (objectp(ranger))
        ranger = ranger->query_real_name();
    else
        ranger = TP->query_real_name();

    player = find_player(ranger);
    if (!objectp(player))
        return -1;

    if (!IS_NRANGER(player))
        return -2;

    if (stringp(Ranger_names[ranger]))
        change = 1;

    Ranger_names[ranger] = name;
    save_object(MEMBER_SAVE);
    return (change + 1);
}

public void
remove_ranger_name(string name)
{
    Ranger_names = m_delete(Ranger_names, LOW(name));
    save_object(MEMBER_SAVE);
}

public mapping query_ranger_names() { return Ranger_names; }

public varargs string
query_ranger_name(string name)
{
    if (!strlen(name))
        name = TP->query_real_name();
    else
        name = LOW(name);

    return Ranger_names[name];
}


