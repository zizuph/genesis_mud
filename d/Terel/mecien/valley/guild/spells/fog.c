/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*  Mystic Cloud.c */
/*  janus 921029 */

inherit "/std/object";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define BS(xx)    break_string(xx, 72)
#define TO        this_object()
#define TP        this_player()
#define NF(xx)    notify_fail(xx)
#define ETO       environment(TO)
#define MSGS      ({\
       "The eerie fog seems to engulf you.",\
       "The eerie fog gets even darker.",\
       "The eerie fog changes its shape."\
       })

int duration = 0;
int stuff_id;
object fog_room;

init()
{
    ::init();
    add_action("do_enter", "enter");
}

int
do_enter(string str)
{
    if (!strlen(str) || ((str != "fog") )) {
	NF("Enter what?\n");
	return 0;
    }

    if (!fog_room) {
	NF("That is not possible at the moment.\n");
	return 0;
    }

    if (!MEMBER(TP)) {
	NF("Mystic forces prevent you from entering.\n");
	return 1;
    }

    TP->move_living("into the eerie fog", fog_room);
    return 1;
}

create_object()
{
    set_name("mystic_fog");
    add_name("fog");
    add_name("cloud");
    set_short("eerie fog");
    set_long(
    "A thick and mysterious cloud of fog, it seems to shift and\n"
   +"tumble about as if alive.\n"
    );
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,10000);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_M_NO_GET,"You grasp at it in vain.\n");
    add_prop(MAGIC_AM_MAGIC,({90,"summoning"}));
    stuff_id = set_alarm(1.0, 10.0, "do_stuff");

}

set_duration(int d)
{
    set_alarm(itof(d), -1.0, "fog_depart");
}

set_fog_room(object room)
{
    fog_room = room;
}

fog_depart()
{
    int i;
    object *pl;
    
    add_prop(OBJ_I_LIGHT, 0);
    ETO->update_light(1);
    tell_room(ETO, BS("The "+short()+" dissolves into nothing.\n"));
    remove_alarm(stuff_id);
    pl = all_inventory(fog_room);
    for (i = 0; i < sizeof(pl); i++) {
	if (interactive(pl[i])) {
	    pl[i]->catch_msg("The ancient fog dissipates.\n");
	    tell_room(pl[i]->query_prop("_fog_last_room"), QCTNAME(pl[i]) +
		      " comes out of the diminishing fog.\n");
	    pl[i]->move_living("M", pl[i]->query_prop("_fog_last_room"));
	}
    }
    remove_object();
}
    
do_stuff()
{
    int i;

    i = random(sizeof(MSGS));
    tell_room(ETO, BS(MSGS[i]) + "\n");
    add_prop(OBJ_I_LIGHT, -1 + random(2));
    ETO->update_light(1);
}

