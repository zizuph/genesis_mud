inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"


//  Prototypes
void init_msg();

int alarm_id;

create_room() {
   set_short("Silent room in the downs");
   set_long(
      "You are inside the Barrow downs\n"
      + "The pit continues to the north and south.\n"
      + "It is somewhat drier here.\n"
      + "A hole leads further down.\n");
   
   add_item(({"hole"}), 
      "It's a hole in the ground leading down.\n"
      +"A foul smell emanates from it.\n");
   
   add_item(({"smell", "foul smell"}), "It smells like long dead flesh.\n");
   
   add_exit(DOWNS_DIR + "stone2_2", "south");
   add_exit(DOWNS_DIR + "stone31b", "north");
   add_exit(DOWNS_DIR + "stone4_1", "down");
   add_prop(ROOM_I_LIGHT,1);
   add_prop(ROOM_I_INSIDE,1);
   reset_room();
}


reset_room() {
}
init() {
   ::init();
   alarm_id = set_alarm(3.0,0.0,&init_msg());
   
}


void
init_msg() {
   remove_alarm(alarm_id);
   TP->catch_msg("You feel safe, no monsters here.\n");
}
