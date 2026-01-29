/*
 * ~sm_leather.c
 *
 * Avenir version of smithing leather.
 * Original:  /d/Shire/smiths/obj/sm_leath.c
 */
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

public void
create_object(void)
{
    set_name("skin");
    set_adj("troloby");
    set_short("troloby skin");
    set_pshort("troloby skins");
    set_long("This is a hardened piece of troloby skin that "+
	"can be used as leather for wrapping the hilts of weapons "+
	"and in the making of armours.\n");

    /* For smiths. */
   add_name(({"leather","smiths_leather","_avenir_skin"}));

   add_prop(OBJ_I_VOLUME, 100);   
   add_prop(OBJ_I_WEIGHT, 100);   
   add_prop(OBJ_I_VALUE, 50 + (random(50)));
}
