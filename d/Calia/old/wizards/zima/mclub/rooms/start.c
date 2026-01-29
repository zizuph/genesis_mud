/*
 * MCLUB - Starting Location - Dormitory
 *
 * History:
 * Date       Coder         Action
 * -------- --------------- ---------------------------------
 * 3/27/95  Zima            Created as a temp room for discussion of MClub
 *                          Physical location in zima/argos/nwterr/rooms
 *                          (Satyr forest of NWTERR of Argos)
 * 4/3/95   Zima            Permission given by Keeper Mrpr and AoD Tepisch
 *                          to make this a permanent start location
 * 5/30/95  Zima            Room recoded to be dormitory of the MClub
 *                          conclave (club house); Physical location moved
 *                          to Conclave of shrine
 * 5/7/95   Zima            Club board moved to this room
 */
inherit "/std/room";
#include <stdproperties.h>
#include "defs.h"
 
/* prototypes */
void    load_board();
 
void create_room() {
   set_short("Dormitory of the conclave");
   set_long(
      "A row of beds line the northern wall of this quiet room, the "+
      "resting place for those who seek refuge in these stone chambers "+
      "beneath the earth. A doorway leads to the central chamber "+
      "of the conclave to the east.\n");
   add_item(({"beds","bed","row","row of beds"}),
      "The beds are of a simple construction of pine wood, flat "+
      "but comfortable matresses atop each.\n");
   add_item("matresses","There is one on each bed.\n");
 
   add_item(({"chamber","walls","room","dormitory"}),
      "It is too dark to make out much, other than the exit from the "+
      "room to the east.\n");
   add_item("conclave","It is the lower level of the stone shrine.\n");
 
   /* room properties */
   add_prop(ROOM_I_INSIDE,1);
 
   load_board();
 
   /* exits */
   add_exit(ROOM_DIR+"shconcon","east",0);
}
 
void load_board() {
    object bb;
    seteuid(getuid(this_object()));
    bb = clone_object(ROOM_DIR+"mboard/board");
    bb->move(this_object());
}
 
int start (string where) {
   int    rc;
   object TP=this_player();
   if (where != "here") return 0;
   if (InMClub(TP)) {
      rc = TP->set_default_start_location(ROOM_DIR+"start");
      if (rc)
         write("Thou shalt enter this world in this forgotten place now.\n");
      else {
         write("Sorry...there is problem with starting here");
         log_file("Error in start here in mclub/rooms/start.c");
      }
      }
   else write("What?\n");
   return 1;
}
 
void init() {
   ::init();
   add_action("start","start");
}
