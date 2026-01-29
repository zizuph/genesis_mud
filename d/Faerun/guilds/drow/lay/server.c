/*
 * drow/lay/server.c
 *
 * This is the Guild Manager for the drow layman guild.
 */
/*
 * IMPORTANT NOTE
 *
 * The server does VERY little cross-checking of data
 * to see if things should be allowed or not.  This is
 * not the place to do it either, the server should be
 * kept as simple as possible, it is only meant to act
 * as a data repository.
 *
 * All checks need to be done in whatever code seeks
 * to manipulate this data.
 */
#pragma no_clone
#pragma no_inherit
#pragma no_shadow
#pragma save_binary
#pragma strict_types

#include "guild.h"

inherit (P_FAERUN_LIB + "log");

/*
 * mapping members = ([
 *    (string)name: ({ (string)title, (int)options,
 *                     (int)last active, }),
 *    ])
 */
private mapping members = ([]);
#define MAX_BACKUPS  10
private int backups = 1;

/* Default values for new members/houses. */
#define NEW_MEMBER      ({ "", 0, 0 })
/* Convenience macro. */
#define MLC(name) if (objectp(name)) name = name->query_real_name(); \
		  else name = lower_case(name);

/*
 * Creates and restores the object file.
 */
private void
create(void)
{
    setuid();
    seteuid(getuid());

    catch(restore_object(GUILD_LOGS + "server"));
}

/*
 * This saves the variables to an object file.
 */
private void
save_state(void)
{
    string file = (GUILD_LOGS + "server");

    catch(rename(file + ".o", file + ".o." + backups));
    /* Keep some backups in case of disaster. */
    if (++backups > MAX_BACKUPS)
	backups = 1;

    save_object(file);
}

/*
 * This updates the last active field of a member.
 */
public void
update_last_active(mixed name)
{
    MLC(name);

    if (!members[name])
	return;

    members[name][M_ACTIVE] = time();
    save_state();
}

/*
 * This queries the last active field of a member.
 */
public int
query_last_active(mixed name)
{
    MLC(name);
    if (!members[name])
	return 0;

    return members[name][M_ACTIVE];
}

/*
 * Adds a member to the guild server.
 * mixed name = name of member to add.
 */
public varargs int 
add_member(mixed name, string *adjs)
{
    MLC(name);
    members[name] = NEW_MEMBER;
    GLOG(JOINLOG, CAP(name) +" joined the Drow Layman.");
    save_state();
    return 1;
}

/*
 * Remove a member from the guild server.
 * mixed name = name of member to remove.
 */
public int
remove_member(mixed name)
{
    MLC(name);

    if (!members[name])
	return 0;

    GLOG(LEFTLOG, CAP(name) +" departed the Drow Layman guild.");
    members = m_delete(members, name);
    save_state();
    return 1;
}

/*
 * Query a specific member of the guild.
 * mixed name = member to query against.
 */
public mixed 
query_member(mixed name) 
{
    MLC(name);

    if (!members[name])
	return 0;
    else
	return secure_var(members[name]);
}

/*
 * Set a guild members title.
 * mixed name - member to modify.
 * string title - The title to set.
 */
public int
set_member_title(mixed name, string title)
{
    MLC(name);

    if (!members[name])
	return 0;

    members[name][M_TITLE] = title;
    save_state();
    return 1;
}

/*
 * Query a guild members title.
 * mixed name - the member to query.
 */
public string
query_member_title(mixed name)
{
    MLC(name);

    if (!members[name])
	return "";
    else
	return members[name][M_TITLE];
}

/*
 * Set a guild members options.
 * mixed name - member to modify
 * int opt - options to set.
 * int add - (optional)How to add the option.
 */
public varargs int
set_member_options(mixed name, int opt, int add)
{
    MLC(name);

    switch(add)
    {
    case 1:
	members[name][M_OPTIONS] |= opt;
	break;
    case -1:
	members[name][M_OPTIONS] ^= opt;
	break;
    default:
	members[name][M_OPTIONS] = opt;
	break;
    }

    save_state();
    return members[name][M_OPTIONS];
}

/*
 * Query a guild members options.
 * mixed name - member to check against.
 * int opt - (optional) binop options to check for.
 */
public varargs int
query_member_options(mixed name, int opt)
{
    MLC(name);

    if (!opt)
	return members[name][M_OPTIONS];
    else
	return (members[name][M_OPTIONS] & opt);
}

/*
 * Query the members of the guild.  By default returns a formatted list.
 * int arg = (optional) Just return an array of members.
 */
public varargs mixed
query_members(int arg)
{
    if (arg)
	return m_indices(members);
    else
	return sprintf("%#-75s", implode(m_indices(members), "\n"));
}

/*
 * Called from /d/Faerun/domain_link.c when a player
 * is purged or deleted.  This will let us clean up
 * various things.
 */
public void
check_deleted_player(mixed name)
{
    string house;

    MLC(name);
    if (!members[name])
	return;

    remove_member(name);
}
