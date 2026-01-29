/*
 *  /d/Gondor/morgul/city/mm_stables/obj/saddlebag.c
 *
 *  The saddlebag made for the stables of Minas Morgul.
 *
 *  Deagol, August 2002
 */

inherit "/std/container";

#include <stdproperties.h>

#include "../mm_stables.h"

void
create_container()
{
    ::create_container();
    
    set_name("saddlebag");
    set_pname("saddlebags");
    set_adj(({"black", "leather"}));
    set_short("black leather saddlebag");
    set_long("The black leather saddle is orderly stored in the rack.\n");
    
    MM_STABLES_NO_GET;
}
