#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("High street");
    set_long("You are travelling along High Street, a wide concourse "+
      "paved in cobblestones that stretches to the north and south. "+
      "Bordering the western side of High Street is a large group of trees, "+
      "a park in the adjacent Upper Class district. On the eastern side "+
      "lie several buildings. Large intersections lie just north and south "+
      "of here.\n");

    add_item(({ "high street", "concourse" }),
      "The roadway is paved in slate-grey cobbles that appear worn and "+
      "slightly cracked, though in good condition considering the heavy "+
      "traffic along this street.\n");

    add_item(({ "trees", "park" }),
      "Examining the woods further, you get the impression that its shadowy "+
      "interior would be a safe haven for thieves and other brigands.\n");

    add_item(({ "buildings" }),
      "Tidy-looking wooden structures lining the eastern side of High "+
      "Street. This area looks to be middle-class, where the occupants have "+
      "enough money to not live in hunger, but not enough to live in "+
      "comfort.\n");

    add_exit(CVAN + "high_serv", "north");
    add_exit(CVAN + "high-harvest", "south");
}
