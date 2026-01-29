#include "defs.h"
inherit STD_ROOM;
/* By Sarr */

object ob;
void reset_room();

void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    ::create_room();
    set_short("In a dingy hole");
    set_long("You land in a dark, dingy hole. The walls around "+
    "you are made of black stone, and they are covered with moss "+
    "and mold. The air is foul smelling, and the feeling of death "+    
    "strong.\n");
    reset_room();
    clone_object(DRAKMERE_DIR + "mhdoor2")->move(TO);
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(COMMON_NPC_DIR + "bloody_skeleton");
        ob->move_living("xxx",TO);
    }
}

int *
query_coordinates()
{
    return ({63, 2, -1});
}

