#include "local.h"
inherit TDIR + "throtyl_base";

public void
create_throtyl_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("on a bridge over a lava stream in Sanction");
    set_long("Yep, on a bridge.\n");


    add_exit("/d/Ansalon/taman_busuk/sanction/room/city/street8","south", 0);
    add_std_exits();

    herbs = HERB_MASTER->query_herbs( ({ "mountains", }) );
}

