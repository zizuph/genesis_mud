/* By Sarr to be used with the Khiraa guild.
 *
 */

#pragma save_binary

inherit "/std/object";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"


void 
create_object()
{
    set_name("_khiraa_death_flag2");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_STEAL, 1);

    set_no_show();
}

void 
set_up_flag()
{
    if (TP->query_ghost())
        return;

    if(query_prop(KHIRAA_JOIN_INITIATE))
        remove_object();
    TP->move_living("M",KHIRAA_DIR(temple/rooms/dark_coffin));
    tell_object(TP,"Remember to go back to your coffins and 'start here'.\n");
    remove_object();
}

void 
init()
{
    ::init();
    set_alarm(3.5, 0.0, &set_up_flag(TP));
}

string 
query_auto_load()
{
    return MASTER;
}
