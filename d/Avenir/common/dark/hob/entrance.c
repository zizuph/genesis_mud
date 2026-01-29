/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/room";
#include "hob.h"

#define NUM_HOBS 6

private static int counter = NUM_HOBS;
public static mapping keys = ([]);


public void
expire_key(object key)
{
    m_delkey(keys, key);
    if (!key)
        return;

    tell_room(environment(key),
	"The "+ QSHORT(key) +" suddenly breaks, then "+
	"disentegrates into a fine dust.\n");

    key->remove_object();
}

public void
remove_object(void)
{
    foreach(object key, int alarm : keys)
    {
	remove_alarm(alarm);
	expire_key(key);
    }

    ::remove_object();
}

private void
make_key(object hob)
{
    object key = clone_object("/std/key");

    key->set_key(HOBS_KEY);
    key->set_adjs(({"antique", "porcelain"}));
    key->set_short("antique porcelain key");
    key->set_pshort("antique porcelain keys");
    key->set_long("This is an antique key formed of porcelain. "+
	"It has managed to survive the many years despite rough handling "+
	"by hobgoblins. You can still see some of the white from "+
	"underneath the grime.\n");

    if (key->move(hob))
	key->move(hob, 1);

    int alarm = set_alarm(itof(HOBS_KEY_EXPIRE), 0.0, &expire_key(key));
    keys[key] = alarm;
}

private void
load_hobs(object hob)
{
    if (counter < 0)
	return;

    if (!random(counter--) || !counter)
    {
	counter = -1;
	make_key(hob);
    }
}

public void
reset_room(void)
{
    /* Reset the counter. */
    counter = NUM_HOBS;
}

public void
create_room(void)
{
    set_short("Lair Entrance");
    set_long("This blackened cavern echoes sounds of grief coming from "+
      "the deeper parts of the world. The cavern area has been "+
      "crudely carved from the stone. A corridor leads up.\n");

    /* For the magic map. */
    add_prop(ROOM_S_MAP_FILE, "utterdark_hobs.txt");

    add_exit(L1 + "s3c", "up");

    add_npc(MON + "lizard", 1);
    add_npc(MON + "hobgoblin", NUM_HOBS, load_hobs);

    add_object(HOB + "door1", 1, &->load_other_door());
}
