inherit "/std/door";

create_door()
{
  ::create_door();
  set_door_id("steward_door");
  set_pass_command(({"n","north"}));
  set_door_name(({"stone door","great door","door"}));
  set_other_room("/d/Gondor/minas/houses/house_stewards");
  set_door_desc("The great door is made of solid, smooth stone.\n");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(0);
  set_key("Key_To_The_Hallows");
}
