/*
 * /d/Faerun/guilds/vampires/obj/scrybreak_obj.c
 *
 *
 * Coded by Nerull, 2022
 *
 */
inherit "std/object";
#include "../guild.h";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <filter_funs.h>


void
remove_me()
{
    //environment(this_object())->add_prop(LIVE_M_NO_SCRY, environment(this_object())->query_prop(LIVE_M_NO_SCRY) + 1);
    //environment(this_object())->catch_tell("The power of the blood conceals you from curious "
    //+"distant eyes.\n");
    remove_object();
    
    return;
}


void
redscryprop()
{
    environment(this_object())->add_prop(LIVE_M_NO_SCRY, environment(this_object())->query_prop(LIVE_M_NO_SCRY) - 1);
    environment(this_object())->catch_tell("The power of the blood will no longer conceal you from curious "
    +"distant eyes due to your engagement in combat.\n");
    return;
}


/*
 * Function name: create_monster()
 * Description  : Sets up our monster.
 */
nomask void create_object()
{
    seteuid(getuid());

    set_name("_scrybreak_ob");
    
    add_prop(OBJ_I_INVIS, 100);
    
    set_no_show();

    set_short("scrybreak_obj");
    set_long("scrybreak_obj.\n");

    add_prop(CONT_I_WEIGHT, 1);
    add_prop(CONT_I_HEIGHT, 1);
    
    //set_alarm(0.1, 0.0, &redscryprop());
    set_alarm(0.1, 0.0, &remove_me());
}