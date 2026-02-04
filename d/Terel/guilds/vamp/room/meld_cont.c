/* meld_cont.c created by Shiva@Genesis.
 * this room is meant to hold an earthmelded vampire.
 */

inherit "/std/room";

#include "../guild.h"
#include "../defs.h"
#include <stdproperties.h>

static object who_melded, *ld_people = ({ });
static int dest_alarm = 0;

void create_room()
{
    set_long("You can't see anything!\n");
    set_short("Deep within the earth");
    set_no_show();
  
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_SCRY, 1);
    add_prop(ROOM_I_NO_THIRST,1);
    add_prop(CONT_I_LIGHT,-1);
    remove_prop(CONT_I_VOLUME);
    remove_prop(CONT_I_MAX_VOLUME);
    remove_prop(CONT_I_WEIGHT);
    remove_prop(CONT_I_MAX_WEIGHT);
    remove_prop(OBJ_I_VALUE);
  
    add_prop(ROOM_I_INSIDE,1);
    setuid();
    seteuid(getuid());
}

void move_def_start(object ob)
{
    string start;

    if (!strlen(start = ob->query_default_start_location()) &&
        !strlen(start = ob->query_def_start()))
    {
        return;
    }

    ob->move_living("X", start, 1);
}


int catch_all(string str)
{
    string cmd = query_verb();
    mixed where_to;
    
    if (cmd == "rise" && !strlen(str))
    {
        if (environment(this_object()))
        {
            if (!TP->move_living("X",environment(this_object())))
            {
                return 1;
            }
        }
        else
        {
            move_def_start(TP);
            return 1;
        }
    }      
  
    if (TP->query_wiz_level())
    {
        return 0;
    }
  
    switch (cmd)
    {
    	case "quit":
    	case "stats":
    	case "commune":
    	case "reply":
    	case "bug":
    	case "sysbug":
    	case "praise":
    	case "idea":
    	case "typo":
    	case "help":
        case "who":
    	case "vearthmeld":
    	case "vmeld":
    	case "vtelepath":
    	case "vscry":
    	case "vtpath":
    	case "vamps":
    	case "vamplist":
    	case "stop":
    	case "vpresence":
    	case "vthirst":
    	case "vitals":
        case "v":
    	case "health":
        case "h":
    	case "vsun":
        case "videa":
        case "voptions":
	    return 0;
    	default:
  	    write("That is impossible while you are earthmelded.\n");
	    return 1;
    }
}

void init()
{
    ::init();
  
    if (present(TP))
    {
    	add_action(catch_all, "", 1);
    }
}

int still_ld(object who)
{
    return (who && !interactive(who));
}

/* this function called repeatedly when a vampire ld's
 * while melded.  This function takes care of removing
 * the object when appropriate.
 */
void wait_to_destruct()
{
    ld_people = filter(ld_people, still_ld);
  
    if (!sizeof(ld_people))
    {
    	remove_alarm(dest_alarm);
    	dest_alarm = 0;
    
    	if (!sizeof(all_inventory()))
    	{
	    remove_object();
    	}
    }
}

void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
  
  
    /* We want to remove the room if it is empty, but not if
     * someone has linkdied from here.  If we get rid of it in
     * that case, the player will be sent back to his startloc
     * when he revives, and we don't want that.  So, we take
     * precautions so that the room is around as long as there
     * are ld players who might need to use it.
     */
  
    if (!interactive(ob) && IS_VAMP(ob))
    {
        ld_people += ({ ob });
    }
  
    if (!dest_alarm && !interactive(ob))
    {
        dest_alarm = set_alarm(10.0, 10.0, wait_to_destruct);
        return;
    }
  
    if (!dest_alarm && !sizeof(all_inventory()))
    {
        /* keep the container around for a while in case it's 
         * needed by other functions (enter_env(), for instance)
         */
        set_alarm(2.0, 0.0, remove_object);
    }
}

void
update_internal(int l, int w, int v)
{
    /* This container shouldn't distribute light */
    ::update_internal(0, w, v);
}


int prevent_enter(object ob)
{
    return !interactive(ob);
}
     
void remove_object()
{
    map(deep_inventory(), move_def_start);
    ::remove_object();
}    
