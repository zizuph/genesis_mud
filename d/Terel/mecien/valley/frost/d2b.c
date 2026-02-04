inherit "/std/door";

#include "/d/Terel/mecien/valley/frost/local.h"

create_door() {
   
   ::create_door();
   
   set_door_id("west door");
   set_door_desc("It is a massive wooden door.\n");
   set_closed_desc("A massive door leads east.\n");
   set_open_desc("A massive door is open to the east.\n");
   set_pass_command(({"east"}));
   set_door_name(({"west door","door"}));
   set_other_room(PATH + "r1");
   set_lock_command("lock");
   set_lock_name("lock");
   set_unlock_command("unlock");
   
   set_open(0);       
   set_locked(0);       
   
}
