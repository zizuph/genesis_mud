inherit "/std/door";

void
create_door()
{
    ::create_door();
    set_door_id("baranor_door");
    set_pass_command(({"n","north"}));
    set_door_name(({"wooden door", "brown door", "door"}));
    set_other_room("/d/Gondor/minas/houses/b_garden");
    set_door_desc("The door is made of wood painted brown.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
}
