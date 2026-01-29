/*
 *    std_amazon.c  
 *
 * A standard amazon.
 *
 * Baldacin@Genesis, Nov 2003   
 *
 */
#include "../defs.h"
#include <macros.h>
#include <stdproperties.h>
inherit "/std/monster";
inherit LIB+"equip";
 
void
create_amazon()
{
}

nomask void
create_monster()
{
    set_name("amazon");
    set_race_name("human");
    set_gender(G_FEMALE);
    set_alignment(0);
    set_all_hitloc_unarmed(query_average_stat() / 4);
    create_amazon();
}
