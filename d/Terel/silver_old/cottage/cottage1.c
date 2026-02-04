/*
   This is a cottage, suitable for a witch. Mortricia 920720
 */
inherit "/std/room.c";

#include <stdproperties.h>
#include <macros.h>

#define HOME_DIR "/d/Terel/silver/cottage/"
#define TO       this_object()

object key, witch, door;

public void
close_and_lock()
{
    
    if (witch && present(witch) && present(key, witch))
        witch->close_shut();
}

public void
reset_room()
{
    seteuid(getuid());
    
    if (!witch) {
        witch = clone_object(HOME_DIR + "witch");
        witch->move(TO);
    }
    
    if (!key) {
        key = clone_object(HOME_DIR + "black_key");
        key->move(witch);
        door->set_key(key->query_key());
    }
    
    set_alarm(2.0, -1.0, close_and_lock);
}

public void
create_room()
{
    set_short("Cottage");
    set_long(
        "You are inside a cottage. Most things here are black. Next " +
        "to the stove, there is a heavy iron pot.\n");

    add_item(({"wall", "walls"}), "The walls are all black.\n");
    add_item(({"stove"}), "It's a huge iron stove, and it's still warm.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(HOME_DIR + "outs_cott", "south", 0);

    seteuid(getuid());
    
    clone_object(HOME_DIR + "pot")->move(TO);

    door = clone_object(HOME_DIR + "black_door");
    door->move(TO);

    reset_room();
}
