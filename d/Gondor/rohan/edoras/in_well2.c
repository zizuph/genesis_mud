inherit "/d/Gondor/common/room";

#include "/sys/stdproperties.h"
#include <language.h>
#include "/d/Gondor/defs.h"

create_room() 
{
  set_short("Inside well");
  set_long(BS("You find yourself inside this little well. There is a rusty "
    + "ladder nailed to the wall. You can move up and down.\n")); 
  add_exit("/d/Gondor/rohan/edoras/in_well","up",0);
  add_exit("/d/Gondor/rohan/edoras/in_well3","down",0);
  add_item(({"ladder","rusty ladder"}),BS("This ladder is strong "
    + "enough to hold you. Or maybe it will break under your weight. The only way to know is to try it.\n"));
  add_prop(ROOM_I_INSIDE,1);
}

void
drop_item(object ob)
{
  string down_room;

  down_room = EDORAS_DIR + "in_well3";
  if (ob && present(ob))
  {
    tell_room(TO, "The " + ob->query_name() + " falls down.\n");
    ob->move(down_room);
    tell_room(down_room, CAP(LANG_ADDART(ob->query_name())) + " falls down from above.\n");
    down_room->drop_item(ob);
  }
}

void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);

  if(!living(ob))
    set_alarm(1.0, 0.0, &drop_item(ob));
}
