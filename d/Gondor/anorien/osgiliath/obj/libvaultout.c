inherit "/std/door";

create_door()
{
  ::create_door();
  set_door_id("libvault_door");
  set_pass_command(({"e","east"}));
  set_door_name(({"metal door","iron door","door"}));
  set_other_room("/d/Gondor/anorien/osgiliath/libvault");
  set_door_desc("The great door is made of solid, strong iron.\n");
  set_lock_command("lock");
  set_lock_name("lock");
  set_lock_desc("A dusty keyhole stares back at you.\n");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(1);
  set_key("Key_To_The_Osg_Lib_Vault");
}
