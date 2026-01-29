inherit "/std/door";

create_door()
{
    ::create_door();
    set_door_id("front_door");
    set_pass_command(({"north","n"}));
    set_door_name(({"oaken door","door"}));
    set_other_room("/d/Gondor/minas/houses/ihall");
    set_door_desc("The door is made of solid oak, it's very sturdy and in good condition.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_key("_i_front_door_key");
}

