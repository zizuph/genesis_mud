/* This is the object which is passed to a player suffering
   from the painful effects of the wicked barbed scourge. 
   Sourged players who cannot resist the pain, suffer an
   effective (but temporary) loss of dex. 
   Code (c) Damian Horton, 1997. */
 
#pragma strict_types
#pragma save_binary

inherit "/std/object";
#include "defs.h"

void
create_object()
{
    set_name("_scourge_object_");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_INVIS, 100);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_M_NO_DROP, 1);
    set_no_show();
}

void
init()
{
    set_alarm (30.0,0.0, "end_pain");
    ENV(TO)->add_attack_delay(30, 1);
}



void end_pain()
{
    ENV(TO)->catch_msg("The pain has become bearable.\n");
    remove_object();
}