
inherit "/std/door";

#define PATH "/d/Terel/dark/"
create_door() {
   
   ::create_door();
   
   set_door_id("wooden door");
   
   set_pass_command(({"s", "south", "exit", "out"}));
   
   set_door_desc("A silver-white door inscribed with a cresent moon\n" +
      "leads out of the tower. The door is wood and metal.\n");
   
   set_door_name(({"white door", "door", "tower door", "wooden door"}));
   
   set_other_room(PATH + "hob/entrance");
   
   set_lock_command("lock");
   set_lock_name("lock");
   set_unlock_command("unlock");
   
   set_open(0);
   set_locked(1);
   
   /* The standard door is open and unlocked, if you want it differently you
      should use these functions too:
   
   set_open(i)           1 if open, 0 if closed
      set_locked(i)         1 if locked, 0 if unlocked
      
   There are also plenty of other things you can set in the door, but this
   is all you need. Look in /std/door.c for more details on all the 
   set_functions()
   */
}
