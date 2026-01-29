inherit "/d/Gondor/common/room";

#include <stdproperties.h>
#include <macros.h>

create_room() {
  set_short("Sanctuary of Mearas");
  set_long(
"You are inside a large marble building. This looks like a temple. You \n"+
"remember that you read somewhere about a sanctuary dedicated to the \n"+
"Mearas, the famous Rohirrim horses. A great calmness fills your soul.\n");
  add_exit("/d/Gondor/rohan/edoras/path3","south",0);
  add_prop(ROOM_I_INSIDE,1);
}

init()
{
  ::init();

  add_action("do_pray","pray");
}

do_pray(string str)
{
  write(break_string("You kneel to pray, but since you are not a Rohirrim you feel extremely uncomfortable. " +
    "Therefore, you stand up again.\n",75));
  tell_room(this_object(),QCTNAME(this_player()) + " kneels down to pray, but then changes " +
    this_player()->query_possessive() + " mind and stands up again.\n",this_player());
  return 1;
}
