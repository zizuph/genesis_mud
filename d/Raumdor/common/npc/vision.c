/* Vision, by Sarr */
/* 2017-08-19 Malus: Added set_mm_in, LIVE_I_NO_BODY, OBJ_M_NO_ATTACK */
#include "defs.h"
inherit "/std/monster";

object ob;

string
short()
{
    seteuid(getuid());
    if(!ob)
        ob = clone_object(COMMON_NPC_DIR + "visiono");
    return ob->short();
}
string
query_short()
{
    seteuid(getuid());
    if(!ob)
        ob = clone_object(COMMON_NPC_DIR + "visiono");
    return ob->short();
}


void
create_monster()
{
    set_name("terrible vision");
    set_long("A terrible vision.\n");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_NO_BODY, 1);
    add_prop(OBJ_M_NO_ATTACK, "How would you attack a vision?\n"); 
    set_mm_in("slowly forms in front of you!");
    set_alarm(0.1,0.0,"assemble");
}

void
assemble()
{
    seteuid(getuid());
    if(!ob)
        ob = clone_object(COMMON_NPC_DIR + "visiono");
    ob->move(E(TO));
    remove_object();
}
