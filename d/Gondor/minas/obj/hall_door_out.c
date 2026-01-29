inherit "/std/door";

create_door()
{
  ::create_door();
  set_door_id("hall_door");
  set_pass_command(({"w","west"}));
  set_door_name(({"metal door","great door","door"}));
  set_other_room("/d/Gondor/minas/citadel/kings_hall");
  set_door_desc("The great door is made of solid, polished metal.\n");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(0);
  set_key(991188226);
}
