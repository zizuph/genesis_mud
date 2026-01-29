inherit "/std/door";

create_door()
{
  ::create_door();
  set_door_id("pedoor");
  set_pass_command(({"s","south"}));
  set_door_name(({"wooden door","door"}));
  set_other_room("/d/Gondor/minas/houses/peyard");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(1);
}
