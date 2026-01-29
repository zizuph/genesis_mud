inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */
create_room()
{
   ::create_room();
   INSIDE;
   set_short("A hallway inside the Duergar Clan's hideout.");
   set_long("A hallway leading east towards the inner parts of "+
      "this crypt that the Duergar-clan has taken as theirs. "+
      "There is not much of interest in here, except the usual rubble on the floor.\n");
   add_item("rubble","Its the normal rubbish that hundreds of "+
      "dewars has left behind them.\n");
   add_item("cellar","It is dark and uninviting, with "+
      "a stench drifting out from the cracks in the door.\n");
   add_item("door","The door looks old but still will "+
      "keep unwanted people outside since its construction of "+
      "oak and hinges of hard metal makes it into a solid object.\n");
   add_exit("/d/Kalad/common/guilds/duergar/joinroom","east");
   
   clone_object("/d/Kalad/common/wild/pass/dwarf/door/door2")->MOVE(TO);
}
