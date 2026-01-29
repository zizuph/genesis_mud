inherit "/std/door";

/* Toby */

void
create_door()
{
   set_door_id("treasury_door");
   set_pass_command(({"e","east"}));
   set_door_name(({"heavy black iron door","heavy door","iron door","black door","door"}));
   set_other_room("/d/Kalad/common/sewers/lizards_lair/before.c");
   set_door_desc("It is a heavy iron door.\n");
   set_fail_pass("The door is locked with a heavy black iron lock.\n");
   set_open(0);
   set_locked(1);
   set_key(745);
}
