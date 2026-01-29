inherit "/std/door";

create_door()
{
  ::create_door();
  set_door_id("lvl1ghs_door");
  set_no_pick(1);
  set_pass_command(({"n","north"}));
  set_door_name(({"wooden door","old door","door"}));
  set_other_room("/d/Gondor/anorien/osgiliath/lvl1_ghs");
  set_door_desc("The great door is made of solid, smooth wood.\n");
  set_lock_command("lock");
  set_lock_name("lock");
  set_lock_desc("An empty keyhole stares back at you.\n");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(1);
  set_key("Key_To_The_Dome_of_Stars");
}
 
