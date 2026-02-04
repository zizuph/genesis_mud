/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/door";

#define PATH "/d/Terel/mecien/valley/guild/"

create_door() {
   
   ::create_door();
   
   set_door_id("door");
   set_closed_desc("A carved redwood door leads south.\n");
set_open_desc("A carved redwood door leads south.\n");
   set_pass_command(({"south", "in", "enter"}));
  set_other_room(PATH + "office/inner");
   set_lock_command("lock");
   set_lock_name("lock");
   set_unlock_command("unlock");
    set_door_desc("A beautiful redwood door, carved with intricate "
  + "scrollwork and letters.\n");
  set_door_name(({"redwood door", "door"}));
   add_item("scrollwork", "They are intricate patterns carved upon the door.\n");
   add_item("letters", "Archaic letters carved into the door and inlaid with silver.\n");
   add_cmd_item("letters", "read", "Doctrina Nobis Verbum Veritas\n");
   
   set_open(0);       
   set_locked(1);       
   
}
