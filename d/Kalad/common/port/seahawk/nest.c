#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Crow's Nest");
    set_long("You are standing in the crow's nest of the Seahawk, which "+
      "is slowly swaying in the wind. A slight wave of nausea washes over you "+
      "when you first gaze out of the nest. From this excellent vantage point "+
      "you get a clear view of the Port District and the bay of Kabal that "+
      "surrounds three sides of it. Above you, seagulls fly, searching "+
      "for a safe place to alight.\n");
    add_item(({"crow's nest","nest"}),"Its what you are standing in.\n");
    add_item(({"port district","district"}),"Peering out over the side "+
      "of the nest, you can see the many wooden buildings of the mainland "+
      "port area.\n");
    add_item(({"bay of kabal","bay","kabal bay"}),"The sparkling waters "+
      "of the enclosing bay gleam a clear blue in color.\n");
    add_item(({"wooden buildings","buildings","building"}),"Very little "+
      "detail can be made out from this distance, just generalities.\n");
    add_item(({"seagulls","seagull"}),"The white-feathered sea birds "+
      "circle the crow's nest, searching for a good spot to land and rest "+
      "their tired wings.\n");

    add_prop(ROOM_NO_TIME_DESC,1);

    add_exit(PORT + "seahawk/mast2",  "down", 0,2);
}

