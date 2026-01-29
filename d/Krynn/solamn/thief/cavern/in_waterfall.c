/* created by Aridor 03/09/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
  set_short("You are falling..");
  set_long("A deafening noise is all around you and have the " +
	   "sensation of falling! Water is all around you, too.\n");
  
  LIGHT;
}

void
flush_down(object who)
{
  set_alarm(itof(random(4)+5),0.0,"flush_em_now", who);
}

void
flush_em_now(object who)
{
  if (random(3))
    if (who->query_hp() > random(who->query_max_hp()))
      {
	write("You hit water with a loud splash!!\n\nPresentmindedly, you "+
	      "grab onto some rocks and drag yourself up.\n");
	who->move_living("M",WATERFALL,1,0);
	return;
      }
  write("You hit water with a loud splash!!\n\nYou can't feel or hear anything " +
	"and suddenly you find yourself floating somewhere in the water.\n");
  who->move_living("M",WATERROOM,1,1,);
}
