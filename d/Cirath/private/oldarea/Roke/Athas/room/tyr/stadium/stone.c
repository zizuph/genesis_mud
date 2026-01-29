inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#define RINGSIDE "/d/Roke/Athas/room/tyr/stadium/ringside"

create_object()
{
    set_name("stone");
    add_name("test");
    set_short("small stone");
    set_long("A small stone.\n");
    add_prop(OBJ_I_NO_GET,1);
    enable_commands();
    set_no_show(1);
    seteuid(getuid(this_object()));
}

catch_msg(str,obj)
{
    tell_room(RINGSIDE,str,this_object(),obj);
}

query_see_blood(){ return 1;}


