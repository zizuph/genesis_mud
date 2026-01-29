/* 
 *  Ceremonial book. This object is found in the cabinet in
 *  the sacristry and contains the preparations and instructions
 *  for various ceremonies.
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
#include COUNCIL_HEADER

void 
create_scroll()
{
    set_name(({"holy tome","tome"}));
    set_short("holy tome");
    add_name(CEREMONIAL_GARB);
    set_long("It is a holy papyrus tome with newly written arcane "+
       "lettering. Perhaps you can read or mread it.\n");
 
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 150);
 
    set_file(SPIRIT_OBJECTS+"certome.txt");
}

static int
read_scroll(string str)
{
    if (!COUNCIL_CODE->is_spirit_elder(TP->query_real_name()))
    {
        NF("You do not understand the text written in the tome.\n");
        return 0;
    }

    ::read_scroll(str);
    return 1;
}
