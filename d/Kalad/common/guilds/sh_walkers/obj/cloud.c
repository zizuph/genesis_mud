inherit "/std/object";
#include "/d/Kalad/defs.h"

/* Sarr */

float last_time;

void
set_cloud_time(float i)
{
    last_time = i;
    set_alarm(i,0.0,"remove_me");
}

float
query_cloud_time()
{
    return last_time;
}

void
create_object()
{
    set_name("cloud");
    add_adj("black");
    add_adj("giant");
    set_short("giant black cloud of dust");
    set_pshort("piles of black dust");
    set_long("A huge amount of black dust that clouds the room!\n");
    add_name("_kalad_dust");
    add_prop(OBJ_I_LIGHT,-5);
    add_prop(OBJ_M_NO_GET,"You wave your hands through the cloud "+
    "around you, but get no dust");
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,10);
}

void
remove_me()
{
    tell_room(E(TO),"The "+short()+" dissapates!\n");
    remove_object();
}


