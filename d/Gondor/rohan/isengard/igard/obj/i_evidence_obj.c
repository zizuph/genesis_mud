/*
 * Invoice for the Isengard Evidence Tour.
 *
 * IGARD_OBJ + "i_evidence_obj.c"
 *
 * Alto, 26 August 2002
 *
 */
#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public void
destruct_me() 
{
    object room;
    if (living(room = environment()))
	     room = environment(room);
      tell_room(room, "The invoice blows away in a sudden gust of wind.\n");
      remove_object();
}

public void
do_destruct() 
{
    if (query_verb() == "drop")
	set_alarm(2.0, 0.0, destruct_me);
    return 0;
}

void
create_object()
{
    set_short("discarded invoice");
    set_name("invoice");
    add_name("paper");
    add_name("note");
    set_adj("discarded");
    add_name("_i_evidence_obj_");
    add_prop(OBJ_I_NO_DROP, do_destruct);

    set_long("The small note appears to be an invoice dropped by mistake: \n\n\n"
        + "\tArmoury Keeper, Hail the White Hand!\n\n"
        + "\tThe master requires the construction of the following for his\n"
        + "\tGreat Horde. When the order is complete, we shall invade Edoras.\n\n"
        + "\t3000 greaves\n"
        + "\t2000 bracers\n"
        + "\t3500 chainmails\n"
        + "\t4000 shields\n\n"
        + "\tMay we taste man-flesh soon!\n\n"
        + "\t\t\tBargaschk\n\n\n");

    add_prop(OBJ_I_VOLUME,      100);
    add_prop(OBJ_I_WEIGHT,      100);

}



