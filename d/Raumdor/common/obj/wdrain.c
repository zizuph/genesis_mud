inherit "/std/object";
/* drains strength for a time, Sarr */
#include "/d/Raumdor/defs.h"
int ostr;
int nstr;

void
create_object()
{
    set_name("drain");
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_INVIS,100);
    add_prop(OBJ_M_NO_DROP,1);
    set_no_show();
}

void
init()
{
    ::init();
    set_alarm(0.0,0.0,"drain");
}

void
drain()
{
    object player = E(TO);
    player->catch_msg("You feel your strength drain.\n");
    tell_room(E(player),QCTNAME(player) +" looks weaker.\n",player);
    TP->add_tmp_stat(0,-20,3);
    set_alarm(60.0,0.0,"destroy");
}

void
destroy()
{
    object player = E(TO);
    player->catch_msg("You feel yourself regaining your strength.\n");
    remove_object();

}


