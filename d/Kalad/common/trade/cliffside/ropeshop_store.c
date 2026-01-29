#include "/d/Kalad/defs.h"
#define ROPE "/d/Kalad/common/trade/cliffside/obj/rope.c"

inherit "/d/Kalad/room_std";

void reset_room();

void
create_room()
{
    ::create_room();
    hear_bell = 1;

    add_prop(ROOM_I_INSIDE,1);

    set_short("Cordell's Storeroom");
    set_long("This is a big room, with ropes in it.\n");

    add_exit("/d/Kalad/common/trade/cliffside/ropeshop1","east");

    reset_room();
}

void
reset_room()
{
    ::reset_room();
    if(!present("rope", TO))
    {
        clone_object(ROPE)->move(TO);
        clone_object(ROPE)->move(TO);
        clone_object(ROPE)->move(TO);
        clone_object(ROPE)->move(TO);
        clone_object(ROPE)->move(TO);
        clone_object(ROPE)->move(TO);

    }
}
