/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/door";

#define PATH "/d/Terel/mecien/valley/guild/crypt"

create_door() {

  ::create_door();

  set_door_id("cryptgate");
set_door_desc("An ornate silver gate. It is an open barred\n"
    +"type, it leads into darkness and mists.\n");

  set_pass_command(({"west", "in", "enter"}));
   set_open_desc("An ornate silver gate leads into the crypt.\n");
   set_closed_desc("An ornate silver gate leads into a crypt.\n");
  set_door_name(({"silver gate","gate"}));
  set_other_room(PATH + "/foyer");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");

  set_open(0);       
  set_locked(1);       

}
