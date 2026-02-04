/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/door";

#define PATH "/d/Terel/mecien/valley/guild/courtyard/"

create_door() {
   
   ::create_door();
   
   set_door_id("winery");
   set_pass_command(({"east", "out", "exit"}));
set_closed_desc("A closed door leads out.\n");
set_open_desc("An open door leads out.\n");
   set_door_name( ({"winery", "door"}) );
   set_other_room(PATH + "ve");
   set_lock_command("lock");
   set_lock_name("lock");
   set_unlock_command("unlock");
   
   set_open(0);       
   set_locked(1);       
   
}
