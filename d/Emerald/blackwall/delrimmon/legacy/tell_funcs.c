/* 
 * Functions:
 * tell_players_in_domain(string domain, string text)
 * tell_players_in_domain_out(string domain, string text)
 * tell_players_in_next_room(object this_room, string text)
 * tell_wizards_in_domain(string wizard, string domain)
 *
 * Originally from /d/Gondor/common/lib/tell_funs.c
 */
#pragma save_binary
#pragma strict_types

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

public object *get_players_in_dir(string dir);

/*
 * Function name: query_in_domain
 * Description:   check if player is in a domain
 * Arguments:     domain - the domain name
 *                player - the player name or object
 * Returns:       1/0
 */
public int
query_in_domain(string domain, mixed player)
{
    object  room;

    if (stringp(player))
        player = find_player(lower_case(player));
    if (!objectp(player))
        return 0;
    if (!objectp(room = environment(player)))
        return 0;

    return (room->query_domain() == capitalize(lower_case(domain)));
}

public string
query_in_dir(object ob)
{
    string *subdir,
            path;
    int     s;
    object  tmp;

    if (!objectp(ob))
        return 0;

    while (ob && !ob->query_prop(ROOM_I_IS))
    {
        ob = environment(ob);
    }

    if (!ob)
    {
        return "";
    }

    // Check for a link room
    if (!stringp(path = ob->query_link_master()))
    {
        // Room is not a link room, so use the file name
        path = file_name(ob);
    }

    subdir = explode(path, "/");

    s = sizeof(subdir) - 2;
    return implode(subdir[0..s], "/") + "/";
}

public int
query_in_same_dir(object ob1, object ob2)
{
    return (query_in_dir(ob1) == query_in_dir(ob2));
}

static int
filter_emerald(object pl)
{
    object  room;

    if (!objectp(room = environment(pl)))
	return 0;

    return (room->query_domain() == "Emerald");
}

public void
tell_players_in_dir(string dir, string text)
{
    get_players_in_dir(dir)->catch_tell(text);
}

public object *
get_players_in_dir(string dir)
{
    return filter(users(), &wildmatch(dir) @ query_in_dir);
}

public void
tell_players_in_same_dir(object ob, string text)
{
    filter(users(), &query_in_same_dir(ob, ))->catch_tell(text);
}

/*
 * Function name: find_room
 * Description:   Find the object pointer to the room that
 *                is the environment of the target or the target.
 * Argument:      A player name or an object pointer to a player
 *                or a file name of a room.
 * Returns:       the room
 */
public object
find_room(mixed target)
{
    object  room;

    // is target already an object pointer?
    if (objectp(target))
	room = target;
    // if not, is it the name of a player?
    else if (stringp(target))
    {
        room = find_player(lower_case(target));
	// or the file name of a room?
	if (!objectp(room))
	{
	    catch(target->short());
	    room = find_object(target);
	}
    }

    // Did we find something?
    if (!objectp(room))
	return 0;

    while (!room->query_prop(ROOM_I_IS))
        if (!objectp(room = environment(room)))
	    return 0;

    return room;
}

/*
 * Function name: query_subdir
 * Description:   Find the subdir for a room or the environment 
 *                of a player.
 * Argument:      target - player name or object pointer or room name.
 * Returns:       ({ "Domain", "subdir" })
 */
public string *
query_subdir(mixed target)
{
    string *path,
            name;
    object  room;

    room = find_room(target);
    if (!objectp(room))
	return 0;

    // Normal room:
    if (wildmatch("/d/*", name = file_name(room)))
    {
        path = explode(name, "/");
    }
    // Link-room:
    else if (stringp(name = room->query_link_master()) &&
        wildmatch("/d/*", name)) 
    {
        path = explode(name, "/");
    }

    if (sizeof(path) > 2)
        return ({ path[2], path[3] });
    else if (sizeof(path) > 1)
        return ({ path[2], 0 });
    else
        return ({ 0, 0 });
}

/*
 * Function name: query_in_same_subdir
 * Description:   are ob1 and ob2 in the same subdir?
 * Arguments:     see query_subdir, 
 * Returns:       1/0
 */
public int
query_in_same_subdir(mixed ob1, mixed ob2)
{
    string *r1, 
           *r2;

    ob1 = find_room(ob1);
    ob2 = find_room(ob2);

    if (!objectp(ob1) || !objectp(ob2) || (ob1 == ob2))
        return 0;

    r1 = query_subdir(ob1);
    r2 = query_subdir(ob2);

    if (!sizeof(r1) || !sizeof(r2)) 
        return 0;

    return ( (r1[0] == r2[0]) && (r1[1] == r2[1]) );
}

/*
 * Function name: tell_players_in_same_subdir
 * Description:   Sends a message to all players in the same
 *                subdirectory as room or player target.
 * Argument:      target - a room or a player name (string or object)
 * Returns:       array of players that received the message
 */
public varargs object *
tell_players_in_same_subdir(mixed target, string text, int all = 0, 
			    object *oblist = 0)
{
    object *player;
    int n, s;

    player = filter(users(), &query_in_same_subdir(target, ));
    if (pointerp(oblist))
	player -= oblist;

    if (!all) 
        player -= filter(player, &->query_prop(ROOM_I_INSIDE) @
            environment);

    player->catch_tell(text);

    return player;
}


#if 0
XXX this conflicts with nomask query_domain() in /std/room.c
public string
query_domain(mixed player)
{
    object  room;
    if (stringp(player))
        player = find_player(lower_case(player));
    if (!objectp(player) || !objectp(room = environment(player)))
        return 0;
    return room->query_domain();
}
#endif

public void
tell_players_in_domain(string domain, string text)
{
    filter(users(), &query_in_domain(domain, ))->catch_tell(text);
}

public void
tell_players_in_domain_out(string domain, string text)
{
    object *player;

    player = filter(users(), &query_in_domain(domain, ));
    filter(player, not @ &->query_prop(ROOM_I_INSIDE) @
        environment)->catch_tell(text);
}

public void
tell_next_room(object this_room, string text)
{
    int     i, s;
    string *rooms;

    seteuid(getuid(this_object()));
    rooms = this_room->query_exit_rooms();

    for (i = 0, s = sizeof(rooms); i < s; i++)
        tell_room(rooms[i], text);

    seteuid(0);
}

public object *
tell_next_room_with_dir(mixed this_room, string text)
{
    int     i, s, n;
    mixed  *room_arr = ({ });
    object *players = ({ });

    if (stringp(this_room))
	this_room = find_object(this_room);
    if (!objectp(this_room))
        return 0;

    seteuid(getuid(this_object()));
    room_arr = this_room->query_exit_rooms();

    for (i = 0, s = sizeof(room_arr); i < s; i++)
    {
	if (stringp(room_arr[i]))
	{
	    catch(room_arr[i]->short());
	    room_arr[i] = find_object(room_arr[i]);
	}
        if (!objectp(room_arr[i]))
            ;
        else if ((n = member_array(file_name(this_room), 
				   room_arr[i]->query_exit_rooms())) > -1)
	{
            tell_room(room_arr[i], text + " the " + 
		      room_arr[i]->query_exit_cmds()[n] + ".\n");
	    players += FILTER_PLAYERS(all_inventory(room_arr[i]));
	}
        else
	{
            tell_room(room_arr[i], text + " somewhere nearby.\n");
	    players += FILTER_PLAYERS(all_inventory(room_arr[i]));
	}
    }

    seteuid(0);

    return players;
}
