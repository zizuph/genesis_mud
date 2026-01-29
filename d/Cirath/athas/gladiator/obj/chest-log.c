/*
 * Gladiator chest logger.
 *
 * The following code is made to allow for creating log files useable
 * to track possible breaking of Genesis rules by some players, who
 * use 'seconds' to steal things out of the chest. The code is not
 * supposed to help mortals directly, so balance/tax issues are void.
 *
 * Of course such processing is not much effective for the driver. It is
 * not meant to run always, enable it only when really needed.
 *
 * It can be disabled/enabled in file chest.c by using appropriate #define
 * 
 * Valen, Feb 2003
 */

#pragma no_clone

#include "files.h"
#include "defs.h"

static mixed objsindex = ([]);
static mixed objsdetails = ({});

static int alarmid;
static int alarmactive = 0;
static int ignore_calls = 0;

public void
create(void)
{
    getuid();
    seteuid(getuid());
    write_file(CHEST_LOG, ctime(time()) + " --- logger engine loaded ---\n");
}

public string
short(void)
{
    return "chest logger";
}

/*
 * This function is used to translate objectpointer into useful description
 * of an object. It is especially needed to log player names instead of
 * funny things like /d/Genesis/race/elf_std#13422
 */

static string
resolve(object ob)
{
    object e;
    string str;

    if(!ob) return "(void)";
    if(IS_PLAYER_OBJECT(ob))
        return "\"" + capitalize(ob->query_real_name() + "\"");
    if(IS_ROOM_OBJECT(ob))
        return "\"" + ob->short() + "\"(" + file_name(ob) + ")";

    e = ob;
    do
    {
    	e = environment(e);
    } while(e && !IS_PLAYER_OBJECT(e) && !IS_ROOM_OBJECT(e));

    str = "\"" + ob->short() + "\"(" + file_name(ob) + ") in ";

    if(!e) return str + "(void)";
    if(IS_PLAYER_OBJECT(e))
        return str + "\"" + capitalize(e->query_real_name() + "\"");
    if(IS_ROOM_OBJECT(e))
        return str + "\"" + e->short() + "\"(" + file_name(e) + ")";

    return str + "unknown environment (" + file_name(e) + ")";
}

/*
 * Main reporting function. It is called by an alarm and processes
 * whole array prepared by individual reports. The idea is to log
 * previous environment when drop/get property is checked, then set
 * alarm, and log new environment after the alarm expires. It is a bit
 * dirty way, but looks like it works nicely and effectively.
 */

static void
make_report(void)
{
    int i;

    alarmactive = 0;

    if(!sizeof(objsdetails)) return;

    for(i = sizeof(objsdetails) - 1; i >= 0; i--)
    {
        object ob, prevenv, newenv;
	string sob;
	
        ob = objsdetails[i][0];		// object moved
        sob = objsdetails[i][2];	// object filename
        prevenv = objsdetails[i][1];	// previous environment

        if(!ob)
        {
            if(prevenv)
            {
                write_file(CHEST_LOG, ctime(time()) +
                " " + sob + " disappeared from " + file_name(prevenv) + "\n");
            }
        }
        else
        {
            newenv = environment(ob);

/*
 * this horrible spell prevents logging of the cases when:
 * 1) previous and new environment are the same
 * 2) previous is the chest and new is a player (borrowing)
 * 3) previous is a player and new is the chest (returning)
 * those 2) and 3) are covered in leave_inv and enter_inv of the chest
 */
	    if(prevenv != newenv &&
               (!prevenv || MASTER_OB(prevenv) != GLAD_CHEST ||
                   !interactive(newenv)) &&
	       (!newenv || MASTER_OB(newenv) != GLAD_CHEST ||
	           !interactive(prevenv)))
            {
                write_file(CHEST_LOG, ctime(time()) +
                " \"" + ob->short() + "\"#" + OB_NUM(ob) +
                " moved from: " + resolve(prevenv) +
                " to: " + resolve(newenv) +
                (this_player() ? " (TP:" +
                    capitalize(this_player()->query_real_name()) +
                    ")": "") + "\n");
                if(IS_PLAYER_OBJECT(newenv) &&
                   !present(CHEST_AGENT_NAME, newenv))
                {
                    clone_object(CHEST_AGENT)->move(newenv, 1);
                }

            }
        }
    }
    objsindex = ([]);
    objsdetails = ({});
}

static void
rm_alarm(void)
{
    if(alarmactive)
    {
    	alarmactive = 0;
    	remove_alarm(alarmid);
    }
}

/*
 * Allocate an alarm that does the logging. There is used an optimization
 * to avoid a lot of pending alarms. If the alarm is already allocated, we
 * just remove and reallocate it, thus delaying it a bit. The alarm always
 * process whole array, so it is not needed to do it more than once for
 * a given array of any size.
 */

static void
mk_alarm(void)
{
    rm_alarm();
    alarmid = set_alarm(1.0, 0.0, make_report);
    alarmactive = 1;
}

public void
report_create(void)
{
    write_file(CHEST_LOG, ctime(time()) + " --- chest loaded ---\n");
}

public void
report_remove(void)
{
    write_file(CHEST_LOG, ctime(time()) + " --- chest removed ---\n");
}

static void
report_move(string sob)
{
    object o;
    int i;
    object ob;

    if(ignore_calls > 0)
    {
        ignore_calls--;
        return;
    }
     
    if(!sob || sob == "") return;

    ob = find_object(sob);
    if(!ob) return;

    if(!objsindex[sob])
    {
	objsindex[sob] = 1;
        objsdetails += ({ ({ob, environment(ob), sob}) });
    }

    mk_alarm();
}

public int
report_get(string ob)
{
    report_move(ob);
    return 0;
}

public int
report_drop(string ob)
{
    report_move(ob);
    return 0;
}

/*
 * Called when an item enters the chest. If the item does not have the
 * property (meaning it is first time donation), we do a dirty thing
 * by setting no-drop and no-get properties. The associated functions do
 * not prevent dropping/getting of the item, but instead they use the
 * calls to trigger alarm that does the actual logging. The alarm is needed
 * because at the time of calling the functions we do not know yet what
 * new environment will the item enter.
 * That ignore_calls thing is another dirty tool, in this case to avoid
 * calling the functions immediately after they are set by add_prop. This
 * is weird thing mudlib does, I'm not sure it is intentional or buggy.
 */

public void
report_enter(object ob, object from)
{
    string str = "";

    if(!IS_WEAPON_OBJECT(ob) && !IS_ARMOUR_OBJECT(ob) &&
       !IS_CONTAINER_OBJECT(ob)) return;

    if(!ob->query_prop("_obj_s_glad_chest_property"))
    {
        str = " donated \"" + ob->short() + "\" (" + file_name(ob) + ")";
        ob->add_prop("_obj_s_glad_chest_property", from->query_real_name());
        if(ob->check_recoverable()) str += "+R";
        if(ob->query_prop_setting(OBJ_M_NO_DROP))
        {
    	    str += " -nodrop";
        }
        else
        {
	    ignore_calls = 1;
    	    ob->add_prop(OBJ_M_NO_DROP,
    	     "@@report_drop:" + CHEST_LOGGER + "|" + file_name(ob) + "@@");
        }

        if(ob->query_prop_setting(OBJ_M_NO_GET))
        {
    	   str += " -noget";
        }
        else
        {
	   ignore_calls = 1;
    	   ob->add_prop(OBJ_M_NO_GET,
    	     "@@report_get:" + CHEST_LOGGER + "|" + file_name(ob) + "@@");
        }
    }
    else
    {
        str = " returned \"" + ob->short() + "\"#" + OB_NUM(ob);
    }

    write_file(CHEST_LOG, ctime(time()) +
        " " + capitalize(from->query_real_name()) +
        str + "\n");
}

public void
report_leave(object ob, object to)
{
    if(ob->query_prop("_obj_s_glad_chest_property"))
    {
        write_file(CHEST_LOG, ctime(time()) +
            " " + capitalize(to->query_real_name()) +
            " borrowed \"" + ob->short() + "\"#" + OB_NUM(ob) + "\n");
        if(!present(CHEST_AGENT_NAME, to))
        {
            clone_object(CHEST_AGENT)->move(to, 1);
        }
    }
}

/*
 * This function is called when player kicks the chest, to sort out
 * nonrecoverable things.
 */

public void
report_sort(object who, object *obs)
{
    int i;

    if(!sizeof(obs)) return;

    write_file(CHEST_LOG, ctime(time()) +
        " " + capitalize(who->query_real_name()) +
        " sorted out the following:\n");

    for(i = sizeof(obs) - 1; i >= 0; i--)
    {
        write_file(CHEST_LOG, ctime(time()) +
            " - \"" + obs[i]->short() + "\"#" + OB_NUM(obs[i]) + "\n");
    }
}

public void
report_linkdeath(object who, int ld)
{
    write_file(CHEST_LOG, ctime(time()) +
        " " + who + (ld ? " linkdied\n":" revived\n"));
}

public void
report_quit(string who)
{
    write_file(CHEST_LOG, ctime(time()) +
        " " + who + " left the game\n");
}

public void
report_death(string who)
{
    write_file(CHEST_LOG, ctime(time()) +
        " " + who + " died\n");
}
