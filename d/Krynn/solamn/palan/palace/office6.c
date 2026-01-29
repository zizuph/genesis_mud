/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE


object judge;


string
query_to_jail()
{
  return "south";
}


void
reset_palan_room()
{
    seteuid(getuid(TO));
    if (judge)
      return;
    judge = clone_object(LIV + "divorce_judge");
    judge->move_living(0,TO);

}

void
create_palan_room()
{
    set_short("Divorce Office");
    set_long(BS("You are standing in the divorce office of Palanthas. " +
		"Since the need of this institution in Palanthas has " +
		"increased drastically in the past, an extra office had " +
		"to be established. So here you are now. Of course, " +
		"any divorce taking place here will be valid everywhere " +
		"in the world, not just here.", SL));

    INSIDE;

    add_exit(PALACE + "hall5","south",0,0);

    reset_room();
}

 
