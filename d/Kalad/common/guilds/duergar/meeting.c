inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Korat */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("The meeting area of the Duergar-clan");
   set_long("This inner chamber is decorated with old sarcophaguses "+
      "along the walls, making it a fitting area for the Duergar-clan "+
      "to discuss and argue. Remember though, only one argument can win, "+
      "namely your ultimate leader's thoughts! So check your titles well. "+
      "If you find out that you soon will start to kill your "+
      "debating opponents, then leave to the north.\n");
   add_item("sarcophagus","They are some old and fairly "+
      "cracked stone-coffins. They are all looted ages ago.\n");
   add_exit("/d/Kalad/common/guilds/duergar/train","north",0,-1,-1);
   set_noshow_obvious(1);
   clone_object("/d/Kalad/common/guilds/duergar/private_board")->move(TO);
}
