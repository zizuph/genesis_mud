/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/door";

#define PATH "/d/Terel/mecien/valley/guild/courtyard/"

create_door() {
   
   ::create_door();
   
   set_door_id("shed");
  set_door_desc(
 "Its a simple wooden door, it is carved with roses.\n"
);
   set_pass_command(({"northeast", "out", "exit"}));
set_closed_desc("A closed wooden door leads out of the building.\n");
set_open_desc("An open wooden door leads out of the building.\n");
   set_door_name(({"shed","door"}));
   set_other_room(PATH + "sh1");
   set_lock_command("lock");
   set_lock_name("lock");
   set_unlock_command("unlock");
   
   set_open(0);       
   set_locked(0);       
   
}
