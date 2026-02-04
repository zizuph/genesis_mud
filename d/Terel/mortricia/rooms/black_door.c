/*
    A black door in the witch cottage. Mortricia 920722
 */
inherit "/std/door";

#define PATH "/d/Terel/common/forest/cottage/"

create_door() {
    ::create_door();

    set_door_id("black_door");
    set_pass_command(({"n", "north"}));
    set_door_name(({"black door", "door"}));
    set_other_room(PATH + "cottage2");

    set_lock_name("padlock");
    set_lock_command("lock");
    set_unlock_command("unlock");

/* This door is closed and locked */
    set_open(0);
    set_locked(1);
}
