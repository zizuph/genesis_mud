#pragma no_clone
#pragma no_shadow
#pragma no_inherit
#pragma strict_types
/*
 * ~/manager.c
 *
 * The management object for renting
 * private rooms in the baths.
 *
 * Revisions:
 *	Lucius, Jul 2017: Created.
 *
 */
#include "bath.h"

private static string this_file = file_name(this_object());
/*
 * rooms = ([
 *   room # : ({ ROOM, CONNECTING ROOM, }),
 * ])
 */
private static mapping rooms = ([
      "one": ({ "priv_1",  "arc_sw", }),
     "four": ({ "priv_4",  "arc_nw", }),
    "seven": ({ "priv_7",  "arc_ne", }),
      "ten": ({ "priv_10", "arc_se", }),
]);
/*
 * rented = ([
 *   room : ({ renter, key_id, alarm_id, key_ob, }),
 * ])
 */
public mapping rented = ([]);

#define RENTER	0
#define KEY	1
#define ALARM	2
#define KEYOB   3

/* 30 Minutes */
#define ALARM_IVAL	1800.0

public int
valid_room(string room)
{
    return sizeof(rooms[room]);
}

public string *
query_vacancies(void)
{
    return m_indices(rooms) - m_indices(rented);
}

public mixed *
query_rented(string room)
{
    return rented[room];
}

public string
query_room_key(string room)
{
    if (!sizeof(rented[room]))
	return "unset";

    return rented[room][KEY];
}

public int
vacate_room(string room)
{
    mixed *data = rented[room];
    object key, obj = find_object(BATHRM + rooms[room][0]);

    if (!sizeof(data))
	return 1;

    if (objectp(obj) && !obj->clean_room())
    {
	data[ALARM] = set_alarm(ALARM_IVAL, 0.0, &vacate_room(room));
	return 0;
    }

    if (strlen(rented[room][KEYOB]) &&
	objectp(key = find_object(rented[room][KEYOB])) &&
	objectp(obj = environment(key)))
    {
	tell_room(obj, "The "+ key->short() +" dissolves.\n");
    }

    key->remove_object();

    m_delkey(rented, room);
    save_object(this_file);
    return 1;
}

public int
rent_room(string room, object who)
{
    if (!strlen(room) || !objectp(who))
	return 0;

    if (!valid_room(room))
	return 0;

    if (sizeof(rented[room]))
	return 0;

    rented[room] = ({ file_name(who),
	"_melchoir_key_" + (10000 + random(10000)), 
    	set_alarm(ALARM_IVAL, 0.0, &vacate_room(room)),
	0, /* Placeholder */
    });

    object temp = (BATHRM + rooms[room][1])->get_this_object();
    temp = temp->query_bath_door();
    temp->set_key(rented[room][KEY]);

    save_object(this_file);
    return 1;
}

public object
get_room_key(string room)
{
    if (!strlen(room) || !rented[room])
	return 0;

    object key = clone_object(BATHOB + "priv_key");

    if (!objectp(key))
    {
	vacate_room(room);
	return 0;
    }

    key->set_room(room);
    key->set_key(rented[room][KEY]);

    rented[room][KEYOB] = file_name(key);
    return key;
}

public void
create(void)
{
    setuid();
    seteuid(getuid());

    if (file_size(this_file + ".o") > 0)
	restore_object(this_file);

    foreach(string room: m_indices(rented))
	vacate_room(room);
}

public void
remove_object(void)
{
    save_object(this_file);
    destruct();
}

public void
debug_alarms(void)
{
    dump_array(get_all_alarms(), "BA: ");
}
