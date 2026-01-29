/*
 * /d/Gondor/common/guild2/obj/death_flag.c
 *
 * This object marks an initiate to the guild of the Morgul Mages.
 * It will transport the initiate back to the guild after
 * his or her ritual death which is the requirement for joining
 * the guild.
 *
 * Created: Olorin, 5-jan-1994
 *
 * Modification log:
 * By Sarr to be used with the Khiraa guild death entrance.
 *
 */

#pragma save_binary

inherit "/std/object";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"


void 
create_object()
{
    set_name("_khiraa_death_flag");

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

    write("\nYour vision suddenly goes dark, and you feel yourself "+
    "losing consciousness.\n");
    say(QCTNAME(TP)+" suddenly fades away!\n");
    TP->add_prop(KHIRAA_JOIN_INITIATE,1);
    TP->move_living("M",KHIRAA_DIR(temple/rooms/dark_coffin));
    remove_object();
}

void 
init()
{
    ::init();

    set_alarm(2.5, 0.0, &set_up_flag(TP));
}

string 
query_auto_load()
{
    return MASTER;
}
