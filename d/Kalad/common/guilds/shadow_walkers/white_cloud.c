inherit "/std/object";
#include "/d/Kalad/defs.h"

string dmsg;

void
create_object()
{
    set_name("cloud");
    set_adj("white");
    add_adj("dust");
    set_short("white dust cloud");
    set_long("A huge cloud of white dust in the air, making it hard "+
    "to see.\n");
    add_prop(OBJ_M_NO_GET,1);
    add_prop(OBJ_I_LIGHT,-10);
    set_alarm(4.0,0.0,"remove_object");
}

void
enter_env(object to, object from)
{
    dmsg = to->query_prop(ROOM_S_DARK_MSG);
    to->add_prop(ROOM_S_DARK_MSG,"There is too much dust to");
    ::enter_env(to,from);
}

void
remove_object()
{
    E(TO)->add_prop(ROOM_S_DARK_MSG,dmsg);
    tell_room(E(TO),"The cloud clears away and you can see again.\n");
    ::remove_object();
}

