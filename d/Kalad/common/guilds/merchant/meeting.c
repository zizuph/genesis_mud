inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   set_short("Meeting place of the Merchants Guild of Kabal");
   set_long("You are within the meeting room of the Merchants Guild of Kabal.\n");
   add_exit(CVAN(guild/joinroom),"down",0,-1,-1);
   add_exit(CVAN(guild/office),"up","@@check_guild_rank",-1,-1);
   clone_object(CVAN(guild/private_board))->move(TO);
}
