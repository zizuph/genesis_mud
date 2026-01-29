/* The guild object for the Sindar racial guild.
 */

#pragma save_binary

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <wa_types.h>
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/guild/sindar_racial/sindar_racial.h"

void
create_object()
{
    set_name("sextant");
    add_adj(({"silver" ,"precision"}));
    add_name(GUILD_OBJ_ID);
    set_short("precision sextant");
    set_long("This precison sextant is made of silver. " +
        "To learn more about the Sindar, type 'help sindar'.\n");

    add_prop(OBJ_I_WEIGHT,  20);
    add_prop(OBJ_I_VOLUME,   5);
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_M_NO_DROP,  1);
    add_prop(OBJ_M_NO_STEAL, 1);

}



/*
 * Function name: query_auto_load
 * Description  : Return the filename of this module to allow it to be
 *                autoloadable.
 * Returns      : string - the filename of this module.
 */
public string 
query_auto_load() 
{
    return MASTER + ":"; 
}

void
enter_env(object inv,object from)
{
    ::enter_inv(inv,from);

    if (!interactive(inv))
	return;
    if (inv->query_ghost())
	return;

    set_alarm(3.0, 0.0, "check_guild_obj", inv);
}


void
check_guild_obj(object ob)
{
    if (!IS_MEMBER(TP))
    {
    ob->catch_msg("\n\nA mournful voice echos in your mind saying: " +
        "You are no longer a Sindar and cannot possess your sextamt.\n");
    ob->catch_msg("Your sextant disintegrates.\n\n");
    remove_object();
	return;
    }
}
