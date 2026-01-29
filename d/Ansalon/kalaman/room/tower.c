#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KALAMAN_OUT;
object hoopak;

#define PLAYER_I_CLIMB_TOWER "_player_i_climb_tower"

void
reset_kalaman_room()
{
    if(!objectp(hoopak))
    {
	hoopak = clone_object(KOBJ + "weapon/quest_hoopak");
	hoopak->move(TO);
    }
}

create_kalaman_room()
{
    set_short("At the top of a beacon tower");
    set_long("@@long_descr");

    add_item(({"beacon tower","tower"}),
      "@@long_descr");
    add_item(({"kalaman","city"}),
      "To your southwest you can make out the walled city of Kalaman.\n");
    add_item("harbour",
      "Beneath you is the harbour of Kalaman, a dock for boats travelling " +
      "down the Vingaard River into Solamnia.\n");
    add_item(({"light","great light"}),
      "A great light burns here as a signal to ships approaching " +
      "Kalaman.\n");
    add_item(({"river","vingaard river"}),
      "Looking to your north the estuary of the Vingaard River opens " +
      "up into the Turbidus Ocean.\n");

    add_exit(KROOM + "path6","down",0);

    reset_kalaman_room();
}

string
long_descr()
{
    string str;

    str = "You find yourself perched precariously on the top of a beacon tower " +
    "at the edge of the harbour in Kalaman. " +
    "Before you a great light burns brightly, signalling to all those " +
    "who sail the Vingaard River where the breakwater begins.";

    return BSN(str);
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(!living(ob))
	return;

    if(ob->query_prop(PLAYER_I_CLIMB_TOWER))
	return;

    ob->add_prop(PLAYER_I_CLIMB_TOWER, 1);
}
