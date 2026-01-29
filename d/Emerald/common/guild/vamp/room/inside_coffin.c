/* coffin.c created by Shiva@Genesis
 *
 *    revision history:
 *
 *        9.30.00 (Gorboth)  added support for the verbs "l" and "exa"
 *                           while in the coffin. "look and "examine"
 *                           were available, but not the more commonly
 *                           used shortcuts.
 */

#pragma save_binary

#include "../guild.h"

inherit VAMP_ROOM_DIR + "vamp_room";
inherit "/lib/guild_support";

#include <stdproperties.h>

static object outside, owner;

void
create_vamp_room()
{
    set_name( ({ "coffin", "vamp_coffin" }) );
    set_short("Inside a coffin");
    set_em_long("A large and well appointed coffin, lined with black " +
	"velvet and silk.  Across the top, just below the lid, a " +
	"piece of thick velvet is attached at the left side; it " +
	"drapes over your body and tucks into the other side of " +
	"the coffin, protecting you should your coffin be " +
	"opened in the sunlight.  A sturdy lock on the inside " +
	"maintains your security while you rest--safe from the " +
	"sun's deadly rays.\n");
  
    add_prop(ROOM_M_NO_TELEPORT, 1);
    remove_prop(ROOM_I_LIGHT);

    add_prop("_room_s_light_desc", "Darkness soothes your mind and " +
	"rests your eyes.\n");
  
    add_prop(OBJ_S_WIZINFO, "If a coffin is buggy and preventing a " +
        "player from logging in, simply remove it.  The player should " +
        "then be able to log in successfully.  Please notify the " +
        "guildmaster and domain liege of any such bugs.\n");
 
    create_guild_support();
}

void
set_owner(object who)
{
    owner = who;
}

void
set_outside(object obj)
{
    outside = obj;
}

// Get out of the coffin once we are in it
int
rise(string str)
{
    string rise_msg;
  
    if (this_player() == owner)
    {
        rise_msg = COFFIN_MANAGER->query_rise_msg(this_player());
    }
  
    if (strlen(rise_msg))
    {
        tell_room(environment(outside), rise_msg + "\n");
    }
    else
    {
        tell_room(environment(outside), QCTNAME(this_player()) +
            " rises from " +
            ((this_player() == owner) ? POS(this_player()) : "a") +
            " coffin.\n");
    }
  
    this_player()->move_living("M", environment(outside), 1);
  
    return 1;
}

void
gs_hook_start_meditate() { }
 
void
gs_hook_rise() { }

int
gs_hook_catch_error(string str)
{
    if (IS_WIZ(this_player()))
    {
        return 0;
    }
  
    write("You can't seem to focus your mind on that.\n");
    return 1;
}

int
gs_catch_all(string str)
{
    string action = query_verb();
  
    if (action == "rise")
    {
    	if (strlen(str) &&
	    !parse_command(str, ({ }), "'from' [my] / [the] 'coffin'"))
    	{
	    return 0;
    	}
    
    	this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
    	gs_rise();
    	return rise(str);
    }
  
    if (!this_player()->query_prop(LIVE_I_MEDITATES))
    {
        return 0;
    }
     
    action = query_verb();
  
    switch (action)
    {
#if 0
    	case "estimate":
	    return assess(str);
#endif
    	case "meditate":
	    return gs_meditate("");
    	case "set":
	    set_prefs();
	    return 1;
           case "get":
    	case "stats":
    	case "quit":
    	case "commune":
    	case "reply":
    	case "bug":
    	case "typo":
    	case "idea":
    	case "praise":
    	case "sysbug":
    	case "vthirst":
    	case "look":
    	case "examine":
        case "l":
        case "exa":
            case "vamps":
	    return 0;
    	default:
	    return gs_hook_catch_error(str);
    }
}

void
init()
{
    ::init();

    if (this_player() != owner)
    {  
        return;
    }

    set_alarm(0.5, 0.0, &gs_meditate(0));
    this_player()->stop_thirst();
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
  
    ob->start_thirst();
  
    gs_leave_inv(ob, to);
}

int
prevent_enter(object ob)
{
    if (!living(ob))
    {
        write("You don't want to clutter the coffin with such things!\n");
        return 1;
    }

    if (!interactive(ob))
    {
        return 1;
    }

    if (!IS_WIZ(ob) && (ob != owner))
    {
        write("You can't seem to get in.\n");
        return 1;
    }

    return 0;
}

void
move_def_start(object ob)
{
    string start;

    if (!strlen(start = ob->query_default_start_location()) &&
        !strlen(start = ob->query_def_start()))
    {
        return;
    }

    ob->move_living("X", start, 1);
}

void
remove_object()
{
    map(deep_inventory(), move_def_start);
    ::remove_object();
}    
