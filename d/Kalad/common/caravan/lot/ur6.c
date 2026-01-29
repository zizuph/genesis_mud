#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    add_prop(ROOM_I_LIGHT, 0);

    add_prop(ROOM_S_DARK_LONG, "A dark passage.\n");

    add_prop(ROOM_S_DARK_MSG, "Its far too dark in this place to");

    set_short("An underground passage");
    set_long("You are within a dark passage.\n"+
      "You can barely see inside this dark and dismal passageway. "+
      "From what little light there is you can make out reeking piles of "+
      "filth scattered across the ground. The walls and ceiling, which are "+
      "entirely made of mud, are covered with dozens of disgusting bugs. "+
      "Dark passages lead away towards the southwest and northeast.\n");

    add_item(({ "filth" }),
      "It is so disgusting that words cannot adequately describe its revolting "+
      "qualities. It lies in stinking piles all over the passage.\n");

    add_item(({ "walls", "ceiling", "wall" }),
      "The entire passage is made solely of mud. It surprises you that the "+
      "passageway has not collapsed upon you, considering the lack of "+
      "visible supports. Crawling all over the passage are dozens of filthy "+
      "bugs.\n");

    add_item(({ "bugs" }),
      "Filthy creatures! Many cockroaches, centipedes and other nasty "+
      "insects are swarming all over the walls and ceiling of this passage.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/ur5", "southwest");
    add_exit(CVAN + "lot/ur7", "northeast");
}
