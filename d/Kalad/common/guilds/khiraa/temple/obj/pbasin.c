inherit "/std/container";
#include "/d/Kalad/defs.h"

void
create_container()
{
    set_name("basin");
    set_adj(({"glowing","steel"}));
    set_short("glowing steel basin");
    set_long("This is a steel basin, painted black and covered "+
    "with many strange runes, that is supported by three strong "+
    "and ornately decorated legs. Within the basin, you see a "+
    "pool of glowing water. You can see the bottom, as the "+
    "water is crystal clear, but glowing with an eerie green "+
    "color.\n");
    add_prop(OBJ_M_NO_GET,1);
    add_prop(CONT_I_MAX_WEIGHT,100000);
    add_prop(CONT_I_MAX_VOLUME,1000000);
    add_prop(OBJ_I_LIGHT,1);
}

void
move_it(object ob)
{
    tell_room(E(TO),"The "+ob->short()+" dissolves away into the "+
    "green glowing water!\n");
    ob->move("/d/Kalad/common/guilds/khiraa/temple/rooms/temple_rack");
    tell_room(E(ob),"The "+ob->short()+" slowly appears in the room.\n");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    set_alarm(1.0,0.0,&move_it(ob));
}

