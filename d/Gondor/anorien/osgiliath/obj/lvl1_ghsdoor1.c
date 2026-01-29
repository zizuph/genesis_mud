inherit "/std/door";

create_door()
{
  ::create_door();
  set_door_id("lvl1ghs_door");
  set_pass_command(({"s","south"}));
  set_door_name(({"wooden door","door"}));
  set_other_room("/d/Gondor/anorien/osgiliath/lvl1corr2");
  set_door_desc("The door is made of solid, smooth wood.\n");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(1);
}
