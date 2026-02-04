/*
 * /d/Terel/mountains/ghastly_keep/obj/g_veil.c
 *
 * Ghastly veil 
 *
 * Znafsnuf
 *
 * - Language tweak complete (Gorboth)
 */

inherit "/std/armour";
 
#include <stdproperties.h>
#include <wa_types.h>
#include "defs.h";
 
void
create_armour()
{
    set_name("veil");
    set_short("ghostly veil");
    set_long("A transparent looking veil. It feels like "
    	    + "touching arctic air.\n");
    set_ac(20);
    set_am(({ 0, 0, 0 }));
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE, 360);
}