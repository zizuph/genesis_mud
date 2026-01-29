/* 
 *  An information book for prospective members.
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
    set_name(({"sacred book","book"}));
    add_name("_spirit_info_book_");
    set_short("sacred book");
    add_name(CEREMONIAL_GARB);
    set_long("It is a sacred book. Perhaps you can read or mread it.\n");
 
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 150);
 
    set_file(SPIRIT_OBJECTS+"infotome.txt");
}
