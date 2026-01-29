inherit "/std/door";

create_door()
{
  ::create_door();
  set_door_id("libvault_door");
  set_pass_command(({"w","west"}));
  set_door_name(({"metal door","door"}));
  set_other_room("/d/Gondor/anorien/osgiliath/library1");
  set_door_desc("The door is made of solid, strong iron.\n");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(1);
}
