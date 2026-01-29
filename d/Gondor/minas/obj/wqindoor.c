inherit "/std/door";

create_door()
{
  ::create_door();
  set_door_id("wq_door");
  set_pass_command(({"s","south"}));
  set_door_name(({"wooden door","door"}));
  set_other_room("/d/Gondor/minas/houses/wqhouse1");
  set_door_desc("The door is made of aged wood, and looks worn.\n");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(0);
}
