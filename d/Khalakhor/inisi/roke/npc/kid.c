/*
 * kid.c
 *
 * Used in nyreese/cadu_q1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <macros.h>

string
mknam()
{
    return ({"Bob","John","Gimli","Legolas","Oxfile","Ost",
                 "Glah","Nurk","Ferkel","Gogg"})[random(10)];
}

void
create_monster()
{
    //    add_prop(ROKE_I_RUN_FROM_DISEASE,1);

    /* set_name(mknam()); */
    add_name("child");
    set_pname("children");
    set_pshort("children");
    set_long("A harmless child.\n");
    set_alignment(200);
    default_config_npc(5);

    set_title("the child");
  
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
  
    ::create_monster();

    NEVERKNOWN;
}

int query_knight_prestige(){return -2;}
