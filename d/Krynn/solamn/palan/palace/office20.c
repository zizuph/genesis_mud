/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

object judge;

string
query_to_jail()
{
  return "END_TOKEN";
}

void
create_palan_room()
{
    set_short("Judge");
    set_long(BS("This is the Judge's office. There are cupboards filled "
          +  "with books here, as well as a high desk. You can see several"
          +  " more chairs facing the desk.", SL));

    add_exit(PALACE + "hall7","west",0,0);

    add_item(({"cupboards","cupboard","desk","high desk","chair","chairs"}),
               "You can't see anything special, except that it is "
              +"made from wood.\n");
    add_item(({"books","book"}), "They are neatly stacked in the cupboard, " +
              "safely away from prying eyes like yours.\n");
    reset_room();
}

void
reset_palan_room()
{
    seteuid(getuid(TO));
    if (judge)
      return;
    judge = clone_object(LIV + "judge");
    judge->move_living(0,TO);
}
