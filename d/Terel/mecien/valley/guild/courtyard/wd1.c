/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/door";

#define PATH "/d/Terel/mecien/valley/guild/courtyard/"

create_door() {
   
   ::create_door();
   
   set_door_id("winery");
  set_door_desc(
"It is an old reddish wooden door. Upon it is inscribed a large\n"
+"four-pointed star around which is a wreath of grape leaves.\n"
);
   set_pass_command(({"west", "in", "enter"}));
set_closed_desc("A closed wooden door leads into the building.\n");
set_open_desc("An open wooden door leads into the building.\n");
   set_door_name( ({"winery", "door"}) );
   set_other_room(PATH + "winery");
   set_lock_command("lock");
   set_lock_name("lock");
   set_unlock_command("unlock");
   
   set_open(0);       
   set_locked(1);       
   
}
