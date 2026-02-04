/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/door";

#define PATH "/d/Terel/mecien/valley/guild/"

create_door() {
   
   ::create_door();
   
   set_door_id("door");
set_door_desc(
"It is a beautiful redwood door, carved with intricate scroll work " +
  "and strange letters.\n");
   add_item("letters", "They are carved upon the door and inlaid with silver.\n");
   add_item("carvings", "They are intricate patterns.\n");
   add_cmd_item("letters", "read", "Nos In Veritas Morari");
   set_open_desc("A redwood door leads to the north.\n");
   set_pass_command(({"north", "out", "exit"}));
  set_closed_desc("A carved redwood door leads to the north.\n");
  set_door_name(({"door", "redwood door"}));
  set_other_room(PATH + "library");
   set_lock_command("lock");
   set_lock_name("lock");
   set_unlock_command("unlock");
   
   set_open(0);       
   set_locked(1);       
   
}
