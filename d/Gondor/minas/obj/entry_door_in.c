inherit "/std/door";

create_door()
{
  ::create_door();
  set_door_id("entry_door");
  set_pass_command(({"e","east"}));
  set_door_name(({"steel door","door"}));
  set_other_room("/d/Gondor/minas/citadel/tower_entrance");
  set_door_desc("The great door is made of solid, polished steel.\n");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(1);
}
