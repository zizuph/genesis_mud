/* 
 *  Scroll with the Entrance Quest Instructions
 *  for joining the Spirit Circle of Psuchae
 *
 */
 
inherit "/std/scroll";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <config.h>
#include <cmdparse.h>

#include "defs.h"
#include SPIRIT_HEADER

void create_scroll()
{
    set_name(({"holy scroll","scroll"}));
    set_short("holy scroll");
    add_name("_psuchae_holy_scroll_");
    set_long("It is a holy papyrus scroll with newly written arcane "+
       "lettering. Perhaps you can read or mread it.\n");
 
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_M_NO_GIVE,1);
    add_prop(OBJ_M_NO_STEAL,1);
    add_prop(OBJ_M_NO_INS,1);
    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 150);
 
    set_file(SPIRIT_OBJECTS+"joinscroll.txt");
}

string
query_auto_load()
{
    return MASTER + ":";
}

