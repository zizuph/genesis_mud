/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/door";

#define PATH "/d/Terel/mecien/valley/guild/"

create_door() {
   
   ::create_door();
   
   set_door_id("door");
  set_door_desc("A large arcane silver door, inscribed with intricate\n"
 + "patterns and designs, in the center of which is an angelic spirit.\n");
set_closed_desc("An closed arcane silver door leads east.\n");
set_open_desc("An arcane silver door is open to the east.\n");
   set_pass_command(({"east", "in", "enter"}));
   set_door_name(({"silver door","door"}));
   set_other_room(PATH + "lchapel");
   set_lock_command("lock");
   set_lock_name("lock");
   set_unlock_command("unlock");
   
   set_open(0);       
   set_locked(1);       
   
}
