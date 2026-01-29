// file name:        /d/Avenir/smis/module.c
// creator(s):       Denis, May'96
// revision history: Denis, Dec'96: Merged it with module_base.c file.
//                   Lilith Dec'07: updated reset room, it was taking 
//                                  1-2 hours for roms to reset.
//                   Lucius Dec'07: 15 minutes is far too short, adjusted
//                          to be more inline with the standard. Mudlib
//                          minimum is 45 mins (2700 seconds), the average,
//                          90 mins is what the vast majority use. Also,
//                          modifed it to be a variable time each cycle.
#pragma strict_types
#pragma no_clone

#include <files.h>

#include "smis.h"
#include "sys.h"

static string gCaption = 
"SMIS module: --------------------------------------------------------------\n",
              gBottom = 
"---------------------------------------------------------------------------\n";

static private string	gModule_id,
			gModule_description,
			*gModule_types,
			*gExpects_create_notify,
			*gExpects_reset_notify,
			*gAttached_modules;

static private int	gModule_open,
			gModule_dynamic,
			gModule_enabled,
			gModule_reset_alarm_id;

int query_module_open();
int query_module_dynamic();
string query_module_id();
void shutdown_module();

/*
 * Function name: create_module
 */
void
create_module()
{
}

/*
 * Function name: >>
 * Description:   A constructor. Kewl thing to have.
 */
>>()
{
    setuid();
    seteuid(getuid());
    gExpects_create_notify = ({ });
    gExpects_reset_notify = ({ });
    gModule_types = ({ "general" });
    gAttached_modules = ({ });
    create_module();
    gModule_enabled = SMIS_MANAGER->query_module_enabled(gModule_id);
}

/*
 * Function name: <<
 * Description:   A destructor. Kewl thing to have as well.
 */
<<()
{
    if(query_module_dynamic())
	SMIS_MANAGER->drop_smis_module(query_module_id());
    shutdown_module();
}

nomask static void
set_module_id(string id)
{
    gModule_id = id;
}

nomask public string
query_module_id()
{
    return gModule_id;
}

/*
 * Function name: set_module_description
 * Description:   Sets the description of the module.
 * Arguments:     desc - the description.
 */
nomask static void
set_module_description(string desc)
{
    gModule_description = desc;
}

/*
 * Function name: query_module_description
 * Returns:       the description of the module.
 */
nomask public string
query_module_description()
{
    SMIS_CHECK_CALLER;

    return gModule_description;
}

nomask static void
set_module_types(string *types)
{
    gModule_types = types;
}

nomask public string *
query_module_types()
{
    return gModule_types;
}

/*
 * Function name: set_create_notification
 * Description:   Set the array of object filenames (without .c)
 *                to receive the creation notification events of.
 * Arguments:     ln - the array to
 */
nomask static void
set_create_notification(string *ln)
{
    gExpects_create_notify = ln;
}

nomask public string *
query_create_notification()
{
    SMIS_CHECK_CALLER;

    return gExpects_create_notify;
}

nomask static string *
internal_query_create_notification()
{
    return gExpects_create_notify;
}

/*
 * Function name: set_create_notification
 * Description:   Set the array of object filenames (without .c)
 *                to receive the reset notification events of.
 * Arguments:     ln - the array to
 */
nomask static void 
set_reset_notification(string *ln)
{
    gExpects_reset_notify = ln;
}

nomask public string *
query_reset_notification()
{
    SMIS_CHECK_CALLER;

    return gExpects_reset_notify;
}

/*
 * Function name: set_module_open
 * Description:   Sets if the module is open to the outiseders to operate.
 * Arguments:     1 - The module is of open type (public usage).
 *		  0(default) - The module is of closed type
 *			       (domain private usage).
 */
nomask static void
set_module_open(int ex)
{
    gModule_open = ex;
}

/*
 * Function name: query_module_open
 * Returns:       1, if the module can answer command requests from
 *		  other domain wizards,
 *		  0 - if the module is confidential.
 */
nomask public int
query_module_open()
{
    return gModule_open;
}

/*
 * Function name: query_module_reference
 * Description:   Returns the reference to the module, which can be stored
 *		  in global variable, saved to disk, etc.
 * Returns:       The reference string.
 */
nomask public string
query_module_reference()
{
    return OBJECT_DOMAIN + ":" + gModule_id;
}

/*
 * Function name: reset_module
 * Description:   Function to override for module reset.
 */
public void
reset_module()
{
}

/*
 * Function name: enable_module_reset
 * Description:   Enables resetting of the module (for placer-type modules).
 */
nomask static void
enable_module_reset(void)
{
    if (gModule_reset_alarm_id)
	reset_module();

    float delay = itof(2000 + random(2500) + random(2500));
    gModule_reset_alarm_id = set_alarm(delay, 0.0, enable_module_reset);
}

nomask int
query_module_reset_alarm()
{
    return gModule_reset_alarm_id;
}

static void
restart_module()
{
}

/*
 * Function name: shutdown_module
 * Description:   Function that will be called when the module is shut down.
 */
static void
shutdown_module()
{
}

nomask public void
set_module_enabled(int en)
{
    if(gModule_enabled != en)
    {
        gModule_enabled = en;
	if(en)
	    restart_module();
	else
	    shutdown_module();
        SMIS_MANAGER->notify_module_enabled(en);
    }
}

nomask public int
query_module_enabled()
{
    return gModule_enabled;
}

nomask static void
set_module_dynamic(int tmp)
{
    gModule_dynamic = tmp;
}

/*
 * Function name: query_module_dynamic
 * Returns:       1 - If module is dynamic,
 *		  0 - If module is static.
 */
nomask public int
query_module_dynamic()
{
    return gModule_dynamic;
}

/*
 * Function name: set_attached_modules
 * Description:   Sets the attached modules. The attached modules will
 *                receive the _creation_notifications passed received
 *		  by this module.
 * Arguments:     modules - The array of module ids.
 */
public void
set_attached_modules(string *modules)
{
    gAttached_modules = modules;
}

/*
 * Function name: add_attached_module
 * Description:   Adds a module to the list of attached modules.
 * Arguments:     module - The module id.
 */
public void
add_attached_module(string module)
{
    gAttached_modules += ({ module });
}

public void
notify_object_created(object o_just_created, string s_just_created,
		      string area, mixed obj_types)
{
    map(gAttached_modules, SMIS_MANIP->find_smis_module_available)->
	notify_object_created(o_just_created, s_just_created, area, obj_types);
}

public void
notify_object_reset(object o_just_reset, string s_just_reset,
		    string area, mixed obj_types)
{
}

static string
desc_module()
{
    return "";
}

public int
perform_empty_command()
{
    object obj = this_object();

    SMIS_CHECK_CALLER;

    write(gCaption +"Reference: "+ 
	  SECURITY->domain_object(obj) +":"+ obj->query_module_id() +
	  "\n\n" + desc_module() + gBottom);

    return 1;
}

/*
 * Function name: query_alarms
 * Description:   Needed for the 'Dump <module filename> alarms' to work.
 * Returns:       
 */
nomask public mixed *
query_alarms()
{
    return get_all_alarms();
}
