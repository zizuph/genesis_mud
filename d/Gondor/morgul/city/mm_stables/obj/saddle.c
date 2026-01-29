/*
 *  /d/Gondor/morgul/city/mm_stables/obj/saddle.c
 *
 *  The saddle made for the stables of Minas Morgul.
 *
 *  Deagol, August 2002
 */

inherit "/std/object";

#include <stdproperties.h>

#include "../mm_stables.h"

void
create_object()
{
    ::create_object();
    
    set_name("saddle");
    set_pname("saddles");
    set_adj("black");
    set_short("black saddle");
    set_long("The saddle is orderly stored in the rack.\n");
    
    MM_STABLES_NO_GET;
}
