inherit "/std/object";
#include "/d/Kalad/defs.h"

string msg;

void 
set_message(string str)
{
    msg = str;
}


void
create_object()
{
    set_name("message");
    add_name("_kalad_shadow_mess_");
    set_short("message written in red ink on the ground");
    set_long("It is a message scribbled in red ink. You can probably "+
    "read it if you like.\n");
    add_prop(OBJ_M_NO_GET,1);
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,30);
    add_cmd_item("message","read","@@query_message@@");
}

string
query_message()
{
    return msg+"\n";
}


