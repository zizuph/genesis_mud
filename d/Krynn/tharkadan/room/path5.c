#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit THARK_OUT;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"mountains","hills",}));
object wolf;

void
reset_tharkadan_room()
{
    set_searched(random(2));

    if((GET_SEASON == WINTER) && (!objectp(wolf)))
    {
        setuid();
        seteuid(getuid());
        wolf = clone_object(LIVING + "winter_wolf");
        wolf->move(TO);
        wolf->command("hide");
    }

    if((GET_SEASON != WINTER) && (objectp(wolf)))
    {
        wolf->command("emote leaves with the winter snows.");
        wolf->remove_object();
    }
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"snow","snow-covered","snow-covered ground",
	"white","snow-covered land","winters snow","winter's snow"}),
      "@@add_item_snow");
    add_item(({"path","road","rugged pass","rugged path","trail"}),
      "@@add_item_path");

    add_exit(ROOM + "path6","southwest","@@snow_blocked");
    add_exit(ROOM + "path4","northwest",0);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs), ONE_OF(herbs) }), ({ "pass","ground" }), 6);

    reset_tharkadan_room();
}

string
short_descr()
{
    return short_mountain_desc();
}

string
long_descr()
{
    return long_mountain_desc()+"\n";
}

/*  Seems to bug out, causing darkness in the room

public void
enter_inv(object ob, object from)
{
    if((ob->query_average_stat() < 150) && objectp(wolf))
    {
      set_alarm(2.5,0.0, &wolf->command("growl " + ob->query_real_name()));
      set_alarm(4.5,0.0, &wolf->command("kill " + ob->query_real_name()));
    }
}

*/
