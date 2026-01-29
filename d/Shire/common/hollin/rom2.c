#include "lakeroom.h"

create_lakeroom() {
    set_short("Path");
    set_long("You are walking on a path at the western shore of a lake. "+
	     "The path continues up to the north and south to the dam. ");
    add_item(({"path","shore"}),
             "It winds here north and south at the western shore. "+
             "Looks like it is seldom used, but you can't really tell.\n");
    add_item("dam","Better take a walk further south to examine it.");
    NORTH("rom3");
    SOUTH("rom1");
}
