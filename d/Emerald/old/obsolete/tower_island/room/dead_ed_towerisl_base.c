inherit "/d/Emerald/std/room";

#include "../defs.h"

static int load_clone_handler = 0;

public void
create_towerisl_room()
{
}

nomask void
create_emerald_room()
{
    create_towerisl_room();
    if (load_clone_handler)
    {
        set_clone_handler(TOWERISL_DIR + "clone_handler");
    }
}

public varargs void
add_door_exit(mixed key, mixed dest, string cmd, mixed block, mixed tired,
    mixed noshow)
{
    object door;

    add_exit(dest, cmd, block, tired, noshow);

    setuid();
    seteuid(getuid());

    door = clone_object(TOWERISL_OBJ + "cell_door");
    door->set_key(key);
    door->set_pass_command(({ cmd[0..0], cmd }));
    door->set_door_id(dest);
    door->set_other_room(dest);
    door->move(this_object(), 1);

}

inherit "/d/Emerald/std/room";

#include "../defs.h"

static int load_clone_handler = 0;

public void
create_towerisl_room()
{
}

nomask void
create_emerald_room()
{
    create_towerisl_room();
    if (load_clone_handler)
    {
        set_clone_handler(TOWERISL_DIR + "clone_handler");
    }
}

public varargs void
add_door_exit(mixed key, mixed dest, string cmd, mixed block, mixed tired,
    mixed noshow)
{
    object door;

    add_exit(dest, cmd, block, tired, noshow);

    setuid();
    seteuid(getuid());

    door = clone_object(TOWERISL_OBJ + "cell_door");
    door->set_key(key);
    door->set_pass_command(({ cmd[0..0], cmd }));
    door->set_door_id(dest);
    door->set_other_room(dest);
    door->move(this_object(), 1);

}
Q
