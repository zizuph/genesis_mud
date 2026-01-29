/* created by Aridor 03/97 */

#include "../local.h"

inherit ROOM_BASE

object wagon;

mixed
query_to_jail()
{
    return ({"northeast"});
}

void
reset_palan_room()
{
    if (wagon)
      return;
    wagon = clone_object(OBJ + "wagon");
    wagon->move(TO,1);
}

void
create_palan_room()
{
    set_short("A stable with an office.");
    set_long("This is a stable with hay and boxes for horses. The entire " +
	     "floor is covered with hay, and a reserve wagon is standing " +
	     "in the back. At the entrance is a small office.\n");
    add_exit("street4","northeast");

    add_item(({"hay","ground","floor"}),
	     "The entire ground is covered with soft hay, This looks just " +
	     "any other hay you've ever seen.\n");
    add_search(({"hay","ground","floor"}),5,
	       "/std/coins",-2);
    add_item(({"office","entrance","cabin"}),
	     "The office at the entrance is a small cabin made of wood. There " +
	     "is a small window, so that you can buy tickets there.\n");
    add_item(({"wagon","reserve wagon","back"}),
	     "The reserve wagon in the back of the stable looks well in shape, " +
	     "to be used when the normal wagon breaks down or has an accident.\n");
    add_item(({"boxes","horses"}),
	     "They look ordinary.\n");
}

void
init()
{
    ADA("buy");
    ::init();
}

int
buy(string str)
{
    if (!str || str != "ticket")
      return 0;

    clone_object(OBJ + "wagon_ticket")->move(TP,1);
    return 1;
}
