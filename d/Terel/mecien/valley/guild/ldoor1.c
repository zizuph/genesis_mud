/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/door";

#define PATH "/d/Terel/mecien/valley/guild/"

create_door() {
   
   ::create_door();
   
   set_door_id("door");
  set_door_desc("A large arcane silver door, inscribed with intricate\n"
  + "patterns and designs.\n");
set_closed_desc("An closed arcane silver door leads east.\n");
set_closed_desc("A closed arcane silver door.\n");
   set_pass_command(({"west", "out", "exit"}));
   set_door_name(({"silver door","door"}));
   set_other_room(PATH + "ss2");
   set_lock_command("lock");
   set_lock_name("lock");
   set_unlock_command("unlock");
   
   set_open(0);       
   set_locked(1);       
   
}
