inherit "/std/object";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#pragma strict_types
#pragma save_binary

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/gateway.c
 * Purpose    : The gateway to the other side.
 * Located    : Conjured from the spell 'gateway'
 * Created By : Sarr 18.Jun.97
 * Modified By: 
 */

object gMaster;

void
set_master(object mms)
{
    gMaster = mms;
}

void
create_object()
{
    set_name("portal");
    add_name("_gateway_");
    add_adj(({"mystical","black"}));
    set_short("mystical black portal");
    set_long("This is a large, oval-shaped portal floating in the "+
    "air. Within it swirls a mass of black and grey mist. If you "+
    "dare, you may enter it.\n");
    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_M_NO_GET,1);
}

int
do_enter(string str)
{
    NF("Enter what?\n");
    if(str != "portal")
        return 0;
    NF("Only the caster may re-enter the portal.\n");
    if(TP != gMaster)
        return 0;
    write("You step into the "+short()+".\n");
    say(QCTNAME(TP)+" steps into the "+short()+" and vanishes.\n");
    TP->move_living("M",KHIRAA_DIR(temple/rooms/gateway_room));
    say(QCTNAME(TP)+" emerges from the swirling mists.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_enter,"enter");
}

void
shut_portal()
{
    tell_room(E(TO),"The "+short()+" suddenly shrinks to a "+
    "tiny point, then dissapears!\n");
    remove_object();
}

