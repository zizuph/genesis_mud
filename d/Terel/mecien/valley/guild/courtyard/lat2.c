/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/door";

#define PATH "/d/Terel/mecien/valley/guild/"

create_door() {
   
   ::create_door();
   
   set_door_id("lattice");
   set_door_desc("It is a silver gate of intricate lattice work, the whole\n"
      + "looking like some cosmic pattern. In the midst of it is a\n"
      + "four-pointed star.\n");
   set_closed_desc("A silver lattice leads out to the north.\n");
   set_open_desc("A silver lattice leads out to the north.\n");
   set_pass_command(({"north", "out", "exit"}));
   set_door_name(({"lattice","door"}));
   set_other_room(PATH + "courtyard/portico");
   set_lock_command("lock");
   set_lock_name("lock");
   set_unlock_command("unlock");
   
   set_open(0);       
   set_locked(1);       
   
}
