// -*-C++-*- 
// black mist    /d/Avenir/common/holm/obj/black_mist.c       
// creator(s):   Lilith  04/16/97
// purpose:      Defense for Selkie
// last update:     
// note:         This object is cloned by the selkie npc in combat.
//               It adds levels of darkenss to a room, then dis-
//               sipates after a while.
// bug(s):
// to-do:

inherit "/std/object";
#include "/d/Avenir/include/defs.h"
#include <stdproperties.h>

int    set_timer(int i);             

void
create_object()
{
    set_name("black_mist");
    add_name("mist");
    set_adj(({"roiling", "black"}));
    set_short("roiling black mist");
    set_pshort("roiling black mists");
    set_long("A roiling black mist which absorbs light and sheds "+
        "darkness.\n");
    add_prop(OBJ_I_LIGHT, -3);   
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(MAGIC_AM_MAGIC, ({70, "transformation"}));
    add_prop(MAGIC_AM_ID_INFO,
	({"This mist is magical in nature.\n", 15,
        "It has been called from the sea by a daughter of "+
        "Hizarbin.\n", 25,
        "It darkens a room and obscures the sight.\n", 35,
        "It will dissipate in a short period of time.\n", 40 }));
}
   
void
lift_mist()
{
    remove_prop(OBJ_I_LIGHT);
    ENV(TO)->update_light();   
    tell_room(environment(TO), "The "+ short()+ " flows out to sea, "+
        "where it rapidly dissipates.\n");
    remove_object();
}

void
set_timer(int i)
{
    set_alarm(itof(i), 0.0, lift_mist);
}

