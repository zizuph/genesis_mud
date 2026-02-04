/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/door";

#define PATH "/d/Terel/mecien/valley/guild/crypt"

create_door() {
   
   ::create_door();
   
   set_door_id("cryptgate");
   set_door_desc("An ornate silver gate. It is an open barred\n"
      +"type, it leads into darkness and mists.\n");
   
  set_open_desc("An ornate silver gate leads east.\n");
  set_closed_desc("An ornate silver gate leads east.\n");
   set_pass_command(({"out","leave", "exit", "east", "e"}));
   set_door_name(({"silver gate","gate"}));
   set_other_room("/d/Terel/mecien/valley/guild/tower_cellar");
   set_lock_command("lock");
   set_lock_name("lock");
   set_unlock_command("unlock");
   
   set_open(0);       
   set_locked(1);       
   
}
