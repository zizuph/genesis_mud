/* room2.c
   Mort 911004 */

inherit "/std/room";

/*
 * Function name: create_room()
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */

create_room() {

    set_short("Landing");
   set_long("A set of stairs has been carved into the cliff\n" +
           "walls of the valley, it leads up into the misty\n" +
  "heights. A large forest spreads out to the north\n"
 +"from the stairs landing.\n");
   add_exit("/d/Terel/mecien/valley/ledge", "up", 0);
   add_exit("/d/Terel/mecien/valley/sf/fe", "northeast", 0);
}

/*
 * Function name:
 * Description  :
 */

