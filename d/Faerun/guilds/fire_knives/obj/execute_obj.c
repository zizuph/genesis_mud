/*
 * /d/Faerun/guilds/fire_knives/obj/execute_obj.c
 *
 *
 * Coded by Nerull, 2018
 *
 */

#include "../guild.h";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit "std/object";

void
remove_me()
{
    remove_object();
    
    return;
}


int
bleed_me()
{
    setuid();
    seteuid(getuid());
    
    object TISP = environment(this_object());
    
    object bleed_to_death_obj;

    bleed_to_death_obj = clone_object(FIREKNIVES_GUILD_DIR 
    + "obj/bleed_to_death_obj")->move(TISP, 1);
    
    remove_me();

    return 1;
}


/*
 * Function name: create_monster()
 * Description  : Sets up our monster.
 */
nomask void create_object()
{
    seteuid(getuid());

    set_name("execute_obj");
    
    add_prop(OBJ_I_INVIS, 100);
    
    set_no_show();

    set_short("execute_obj");
    set_long("execute_obj.\n");

    add_prop(CONT_I_WEIGHT, 1);
    add_prop(CONT_I_HEIGHT, 1);
    
    set_alarm(4.0, 0.0, &bleed_me());
}