/* Basic door with lockob, coded by Shiva. Used by Marisol
 * (02/23/99) in the Castle at Ovejuno in Emerald. */

inherit "/d/Emerald/std/door";

void
create_castle_door()
{
}

mixed
query_key_id()
{
    return "ovejuno castle master key";
}

nomask void
create_emerald_door()
{
    object lockob;

    set_name("door");
    set_long("A plain door.\n");
    set_open(0);

    lockob = add_default_lock();
    lockob->unlock();
    lockob->set_key(query_key_id());

    create_castle_door();
}
