inherit "/std/room";

#include "trade.h"

object smith;

create_room()
{
  set_short("The weaponsmith's forge");
	set_long(BSS("You have entered a hot forge where the weaponsmith "+
		"does his work. He might even be able to fix your "+
		"lousy weapons. There is sand all over the floor, "+
		"and among the glowing coals, you can see crystallized "+
		"sand which has been melted by the immense heat. "+
		"You notice a sign on the wall, stating some "+
		"instructions.\n"));

  add_prop(ROOM_I_NO_ATTACK,1);
  add_prop(OBJ_I_HAS_FIRE,1);

  add_item("sign",
		"There is some writing on the sign.\n");
  add_cmd_item("sign","read",
	   "  If you want to have a weapon repaired, just give it to\n"+
	   "  the weaponsmith and he'll tell you how much it will cost.\n"+
	   "  Then just pay him or regret.\n");

	add_exit(SWO_STR+"road2","east",0);
  INSIDE;
  
  reset_room();
}

reset_room()
{
  if (!smith)
    {
      tell_room(TO,"The weaponsmith arrives.\n");
      smith = clone_object(A_NPC_D+"weaponsmith");
      smith->move(this_object());
      return 1;
    }
}

init()
{
  ::init();
}

leave_inv(obj,to)
{
  ::leave_inv(obj,to);
  if (!living(obj)) return;
  if(smith) smith->someone_left(obj,to);
}



