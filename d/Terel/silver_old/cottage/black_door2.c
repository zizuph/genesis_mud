/*
    A black door in the witch cottage. Mortricia 920722
 */
inherit "/std/door";

#define PATH "/d/Terel/silver/cottage/"

public void
create_door()
{
    ::create_door();

    set_door_id("black_door");
    set_pass_command(({"s", "south"}));
    set_door_name(({"black door", "door"}));
    set_other_room(PATH + "cottage1");

    set_lock_name("lock");
    set_lock_command("lock");
    set_unlock_command("unlock");

/* This door is open and not locked */
    set_open(1);
    set_locked(0);
}
