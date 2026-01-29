#include <cmdparse.h>

inherit "/d/Krynn/dumrik/room";

create_room() {
  set_short("test");
  set_long("Long desc.\n");
}

init()
{
  ::init();
    add_action("shit1","shit1");
}


int
shit1()
{
  object *rastlin;
  
  rastlin = ({ find_player("dumrik") });
  rastlin += ({ find_player("rastlin") });
  rastlin += ({ find_player("dumrikjr") });

  say("\n" + COMMAND_DRIVER->desc_many(rastlin));
  
}
