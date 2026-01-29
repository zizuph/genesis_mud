/* created by Aridor 01/18/94 */

#include "../local.h"

inherit ROOM_BASE

object molen;

void
reset_palan_room()
{
  if (molen)
    return;
  molen = clone_object(LIV + "moneylender");
  molen->move_living(0,TO);
}

void
create_palan_room()
{

    set_short("Colin's Moneylending Office");
    set_long("This is a small office with a desk and a few chairs and a big " +
	     "cash register is standing on the desk. On the back wall you can " +
	     "see a safe built into the wall.\n");

    add_exit(ROOM + "street4","northeast",0,1);

    reset_room();
}

query_to_jail()
{
  return "northeast";
}
