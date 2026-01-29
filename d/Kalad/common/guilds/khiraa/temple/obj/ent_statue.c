/* 
 * /d/Kalad/common/guilds/khiraa/temple/obj/ent_statue.c
 * Purpose    : Entrance statue
 * Located    : ~khiraa/temple/rooms/t4
 * Created By : Sarr 12.Mar.97
 * Modified By: 
 */ 

#include "/d/Kalad/defs.h"
inherit "/std/object";

void
create_object()
{
    set_name("statue");
    add_adj("large");
    set_long("This statue, made of solid black marble, stands about "+
    "twelve feet high. It looks like a robed humanoid holding a "+
    "sword in one hand, and a skull in the other. Looking deeper "+
    "in its dark hood, you see a skeletal face. Deep within those "+
    "dark sockets of eyes, two eerie red pin-sized lights glow. "+
    "Around the neck of the thing is a black grim-skulled medallion.\n");
    add_prop(OBJ_M_NO_GET,1);
}

