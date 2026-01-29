/*  /d/Raumdor/common/beach/bountiful/obj/sulphur.c
 *
 *  Crate supply item.
 *
 *  Nerull, 2021
 *
 */


inherit "/std/object";
#include "../defs.h";
#include <stdproperties.h>
#include <macros.h>


void
create_object()
{
    set_name("_pure_sulphur");
    add_name("sulphur");
    add_name("lump");
    add_name("lump of sulphur");
    
    set_short("lump of sulphur");
    set_pshort("lumps of sulphur");
    
    set_long("This is a lump of purified yellow sulphur, probably "
    +"useful for alchemic purposes.\n");
    
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 8000);
}