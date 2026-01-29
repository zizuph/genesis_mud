/*
 * /d/Faerun/guilds/fire_knives/rooms/obj/backpack.c
 *
 *
 */


inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep"; 

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>


void
create_wearable_pack()
{
    set_name("backpack");
    set_adj("dark");
    add_adj(a"leather");
    set_short("dark leather backpack");
	set_long("This is a dark leather backpack. Useful for storing "
	+"items and carrying them on your back.\n");
    set_mass_storage(1); 
    set_keep(1); 
    add_prop(CONT_I_IN, 1);
	add_prop(CONT_I_RIGID, 0);
	add_prop(CONT_I_TRANSP, 0);
	add_prop(CONT_I_CLOSED, 1);
	add_prop(CONT_I_WEIGHT, 300);
	add_prop(CONT_I_VOLUME, 300);
	add_prop(CONT_I_MAX_WEIGHT, 100000);
	add_prop(CONT_I_MAX_VOLUME, 85000);
	add_prop(CONT_I_REDUCE_WEIGHT, 130);
	add_prop(OBJ_I_VALUE, 96);
}