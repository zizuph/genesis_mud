
/*
 *  Club Room for the Gellirs of Lars
 *    ... falling to death in the Litillgap
 *    ... not a fearful thing for Larsgellirs
 *    ... a calculated risk
 *
 *  Vitwitch 2022
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "../defs.h"

inherit "/std/room";

/* prototypes */

int is_lgellirroom();
string falling();
void reset_room();
public void create_room();
void enter_inv(object ob, object from);
void abyss_fall( int i, object p );

/* functions */

int
is_lgellirroom()
{
    return 1;
}

string
falling()
{
    return "... you are too busy falling ...";
}

void
reset_room()
{
}


public void
create_room()
{
    set_short(" ");
    set_long("\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_M_NO_ATTACK, "@@falling");
    add_prop(ROOM_M_NO_MAGIC, "@@falling");
    add_prop(ROOM_M_NO_TELEPORT_FROM, "@@falling");
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_M_NO_SCRY, 1);

    reset_room();
}


void
tidy_up_all( object plyr )
{
    object *inv = all_inventory(this_object());

    if ( !sizeof(inv) )
        return;

    foreach ( object obj : inv )
    {
        if ( !objectp(obj) || interactive(obj) ) continue;
	obj->remove_object();
    }

    return;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
    {
       tidy_up_all(ob);
       set_alarm( 1.0, 0.0, &abyss_fall(0,ob) );
    }

}


void
abyss_fall( int i, object p )
{
    if ( p->query_prop(LGELLIR_PROP_LEAP_WARNING) )
        p->remove_prop(LGELLIR_PROP_LEAP_WARNING);

    switch (i)
    {
    case 0:
        p->catch_msg("\n\n...you fall below the horizon...");
        break;
    case 1:
        p->catch_msg("\n\n...you fall beside sheer walls...");
        break;
    case 2:
        p->catch_msg("\n\n...you fall into shrouded darkness...");
        break;
   default:
        // kill the player... there is no survival
        p->catch_msg("\n\n ...you fall beyond mortal bounds...\n");
        int all_hp = p->query_max_hp();
        p->heal_hp(-all_hp);
        p->do_die(this_object());
        return;
    }

    i++;
    set_alarm( 1.0, 0.0, &abyss_fall(i,p) );
    return;
}
