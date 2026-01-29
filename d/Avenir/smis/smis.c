// file name:        /d/Avenir/smis/smis.c
// creator(s):       Denis, May'96
// purpose:	     Systems Management Integrated Services (SMIS)
//
//	             This is the main object that handles various types
//		     of controllable objects including quests, information
//		     servers, event servers, and even runtime processes
//		     and provides common interface to them with ability
//		     to check status as well as change something run-time.
//
//		     Part of the purpose is to separate the different things,
//		     eg: quests and rooms these quests are located in,
//		     debug code and code being debugged, etc, etc.
#pragma strict_types
#pragma no_clone
#pragma no_shadow

#include <macros.h>

#include "smis.h"
#include "sys.h"

/* Smis manager save files.
 */
#define SMIS_REGISTERED_OBJECTS		"objects"
#define SMIS_MODULES_TYPES		"types"
#define SMIS_CREATE_NOTIFICATIONS	"cnotify"
#define SMIS_RESET_NOTIFICATIONS	"rnotify"
#define SMIS_MODULES_DATA		"m_data"
#define SMIS_TEMPORARY_SAVE		"tempsave"

/* Offsets in module information array
 */
#define SMIS_OBJECT			0
#define SMIS_DESCRIPTION		1
#define SMIS_OPEN			2
#define SMIS_DISABLED			3


static string gData_dir,
	      gCaption =
"Systems Management Integrated Services: -----------------------------------\n",
              gBottom =
"---------------------------------------------------------------------v." + SMIS_VERSION + "\n";

mapping gStatic_modules,
	gDynamic_modules,

	gStatic_module_types,
	gDynamic_module_types,

        gStatic_create_notifications,
	gDynamic_create_notifications,

	gStatic_reset_notifications,
	gDynamic_reset_notifications,

	gModules_data;


int retrieve_module_notify_info(string module, mixed module_obj, int dynamic);
public int register_smis_module(mixed obj);

static void
setup_smis_manager(string ddir)
{
    gData_dir = ddir;

    gStatic_modules = ([ ]);
    gStatic_module_types = ([ ]);
    gStatic_create_notifications = ([ ]);
    gStatic_reset_notifications = ([ ]);
    gModules_data = ([ ]);

    if (file_size(gData_dir + SMIS_REGISTERED_OBJECTS + ".o"))
	gStatic_modules = restore_map(gData_dir + SMIS_REGISTERED_OBJECTS);

    if (file_size(gData_dir + SMIS_MODULES_TYPES + ".o"))
	gStatic_module_types = restore_map(gData_dir + SMIS_MODULES_TYPES);

    if (file_size(gData_dir + SMIS_MODULES_DATA + ".o"))
	gModules_data = restore_map(gData_dir + SMIS_MODULES_DATA);

    if (file_size(gData_dir + SMIS_CREATE_NOTIFICATIONS + ".o"))
    {
	gStatic_create_notifications =
	    restore_map(gData_dir + SMIS_CREATE_NOTIFICATIONS);
    }

    if (file_size(gData_dir + SMIS_RESET_NOTIFICATIONS + ".o"))
    {
	gStatic_reset_notifications =
	    restore_map(gData_dir + SMIS_RESET_NOTIFICATIONS);
    }

    gDynamic_modules = ([ ]);
    gDynamic_module_types = ([ ]);
    gDynamic_create_notifications = ([ ]);
    gDynamic_reset_notifications = ([ ]);

    // Now we reload the dynamic modules, which objectpointers were
    // saved when someone updated the manager.
    if (file_size(gData_dir + SMIS_TEMPORARY_SAVE))
    {
	map(restore_map(gData_dir + SMIS_TEMPORARY_SAVE)["S"],
	    register_smis_module);
    }
}

public string
query_data_dir()
{
    return gData_dir;
}

/*
 * Function name: check_not_buggy
 * Description:   Tries to load a module into memory if it is not loaded
 *		  yet.
 * Arguments:     module - which module to load.
 * Returns:       0 - The module is buggy, it won't load;
 *		  1 - The modules is (maybe already) loaded into memory.
 */
static int
check_not_buggy(string module)
{
    if (!objectp(module) &&
        !find_object(module) && catch(module->teleledningsanka()))
    {
	SMIS_WRITE_LOG(module + " failed to load.\n");
	return 0;
    }
    else
	return 1;
}

/*
 * Function name: static_module_available
 * Description:   
 * Arguments:     module - The id of the module to load/check.
 * Returns:       The objectpointer to a module if it is loadable and enabled.
 */
static object
static_module_available(string module)
{
    mixed *module_info = gStatic_modules[module];
    string module_file = module_info[SMIS_OBJECT];

    if (!module_info[SMIS_DISABLED])
	return (check_not_buggy(module_file) ? find_object(module_file) : 0);
}

static object
dynamic_module_available(string module)
{
    mixed *module_info = gDynamic_modules[module];

    if (!module_info[SMIS_DISABLED])
	return module_info[SMIS_OBJECT];
}

public object
query_module_available(string module)
{
    if (gStatic_modules[module])
        return static_module_available(module);
    else if (gDynamic_modules[module])
	return dynamic_module_available(module);
    else
	return 0;
}

/************************************************************************
 * Managing modules							*
 ************************************************************************/

/*
 * Function name: register_smis_module
 * Description:   
 * Arguments:     
 * Returns:       
 */
public int
register_smis_module(mixed obj)
{
    int	i, open, dynamic;
    string module, description, *types;

    if (!stringp(obj) && !objectp(obj))
	return 0;
    
    if (!check_not_buggy(obj))
	return 0;

    module = obj->query_module_id();

    if (!strlen(module) || strlen(module) > 10)
	return 0;

    description = obj->query_module_description();
    types = obj->query_module_types();
    open = obj->query_module_open();
    dynamic = obj->query_module_dynamic();

    if (!sizeof(types))
	return 0;

    if (dynamic)
    {
	if (stringp(obj))
	    obj = find_object(obj);

	if (!objectp(obj) ||
	    gStatic_modules[module] || gDynamic_modules[module])
	{
	    return 0;
	}
	else
	{
	    gDynamic_modules[module] = ({ obj, description, open, 0 });

	    // Setup the module types.
	    for (i = 0; i < sizeof(types); i++)
	    {
		if (pointerp(gDynamic_module_types[types[i]]))
		    gDynamic_module_types[types[i]] += ({ module });
		else
		    gDynamic_module_types[types[i]] = ({ module });
	    }

	    retrieve_module_notify_info(module, obj, dynamic);
	    return 1;
	}
    }
    else
    {
	if (gStatic_modules[module] || gDynamic_modules[module])
	{
	    return 0;
	}
	else
	{
	    gStatic_modules[module] = ({ obj, description, open, 0 });
	    save_map(gStatic_modules, gData_dir + SMIS_REGISTERED_OBJECTS);
	    for (i = 0; i < sizeof(types); i++)
	    {
		if (pointerp(gStatic_module_types[types[i]]))
		    gStatic_module_types[types[i]] += ({ module });
		else
		    gStatic_module_types[types[i]] = ({ module });
	    }
	    save_map(gStatic_module_types, gData_dir + SMIS_MODULES_TYPES);

	    retrieve_module_notify_info(module, obj, dynamic);
	    return 1;
	}
    }
}

#define DROP_NOTIFICATION_ONE(modules, notifications)			\
	notify_objs = m_indexes(notifications);				\
	notify_num = sizeof(notify_objs);				\
	for (i = 0; i < notify_num; i++)				\
	{								\
	    notify_obj = notify_objs[i];				\
	    notification_data = notifications[notify_obj];		\
	    notification_data -= ({ module });				\
	    if (sizeof(notification_data))				\
		notifications[notify_obj] = notification_data;  	\
	    else						      	\
		notifications = m_delete(notifications, notify_obj);	\
	}

#define DROP_TYPES_ONE(typemap)					\
	types = m_indexes(typemap);					\
	for(i = 0; i < sizeof(types); i++)				\
	{								\
	    type = types[i];						\
	    typemap[type] -= ({ module });				\
	    if (!sizeof(typemap[type]))					\
		typemap = m_delete(typemap, type);			\
	}
	

/*
 * Function name: drop_smis_module
 * Description:   Handles removing the modules from the list of
 *                registered modules.
 * Arguments:     module - Module to be removed identifier.
 * Returns:       1 - Success;
 *		  0 - Failure.
 */
public int
drop_smis_module(mixed module)
{
    int i, notify_num;
    string *notify_objs, notify_obj,
	   *notify_info, notify_elem,
	   *types, type;
    mixed notification_data, module_obj;

    if (gStatic_modules[module])
    {
	module_obj = gStatic_modules[module][SMIS_OBJECT];

	gStatic_modules = m_delete(gStatic_modules, module);
	save_map(gStatic_modules, gData_dir + SMIS_REGISTERED_OBJECTS);

	DROP_TYPES_ONE(gStatic_module_types);
        save_map(gStatic_module_types, gData_dir + SMIS_MODULES_TYPES);

        DROP_NOTIFICATION_ONE(gStatic_modules,
			      gStatic_create_notifications)
	save_map(gStatic_create_notifications,
		 gData_dir + SMIS_CREATE_NOTIFICATIONS);

        DROP_NOTIFICATION_ONE(gStatic_modules,
			      gStatic_reset_notifications)
	save_map(gStatic_reset_notifications,
		 gData_dir + SMIS_RESET_NOTIFICATIONS);

	return 1;
    }

    if (gDynamic_modules[module])
    {
	module_obj = gDynamic_modules[module][SMIS_OBJECT];

	gDynamic_modules = m_delete(gDynamic_modules, module);
	DROP_TYPES_ONE(gDynamic_module_types)
        DROP_NOTIFICATION_ONE(gDynamic_modules,
			      gDynamic_create_notifications)
        DROP_NOTIFICATION_ONE(gDynamic_modules,
			      gDynamic_reset_notifications)
	return 1;
    }
}

#define RETRIEVE_NOTIFICATION_ONE(modules, notifications)		\
	i = -1;								\
	notify_num = sizeof(notify_info);				\
	while (++i < notify_num)					\
	{								\
	    notify_elem = notify_info[i];				\
	    notification_data = notifications[notify_elem];		\
	    if(!notification_data)					\
		notifications[notify_elem] = ({ module });		\
	    else							\
		notifications[notify_elem] += ({ module });		\
	}

static void
retrieve_module_notify_info(string module, mixed module_obj, int dynamic)
{
    int    i,
	   notify_num;
    string *notify_info,
	   notify_elem;
    mixed  notification_data;

    if (!check_not_buggy(module_obj))
	return;

    notify_info = module_obj->query_create_notification();
    if (!sizeof(notify_info))
	return;

    if (!dynamic)
    {
        RETRIEVE_NOTIFICATION_ONE(gStatic_modules,
				  gStatic_create_notifications)
	save_map(gStatic_create_notifications,
		 gData_dir + SMIS_CREATE_NOTIFICATIONS);

    }
    else
    {
        RETRIEVE_NOTIFICATION_ONE(gDynamic_modules,
				  gDynamic_create_notifications)
    }

    notify_info = module_obj->query_reset_notification();
    if (!sizeof(notify_info))
	return;

    if (!dynamic)
    {
        RETRIEVE_NOTIFICATION_ONE(gStatic_modules,
				  gStatic_reset_notifications)
	save_map(gStatic_reset_notifications,
		 gData_dir + SMIS_RESET_NOTIFICATIONS);
    }
    else
    {
        RETRIEVE_NOTIFICATION_ONE(gDynamic_modules,
				  gDynamic_reset_notifications)
    }
}

/*
 * Function name: reload_module_notify_info
 * Description:   Reloads the information about the requested notifications
 *		  from the module. Is used from the 'nreload' command, but
 *		  Can be used also with the modules, which change their
 *		  notification lists at runtime. (But please, if they do that
 *		  often, make them of dynamic type).
 * Arguments:     module - The identifier of a module, which notification
 *			   information to reload.
 * Returns:       1 - Reload successful
 */
int
reload_module_notify_info(string module)
{
    int i, notify_num;
    string *notify_objs, notify_obj,
	   *notify_info, notify_elem;
    mixed notification_data, module_obj;

    if (gStatic_modules[module])
    {
        module_obj = gStatic_modules[module][SMIS_OBJECT];

	if(!check_not_buggy(module_obj))
	    return 0;

        DROP_NOTIFICATION_ONE(gStatic_modules,
			      gStatic_create_notifications)

        DROP_NOTIFICATION_ONE(gStatic_modules,
			      gStatic_reset_notifications)

	save_map(gStatic_create_notifications,
		 gData_dir + SMIS_CREATE_NOTIFICATIONS);

	save_map(gStatic_reset_notifications,
		 gData_dir + SMIS_RESET_NOTIFICATIONS);

	retrieve_module_notify_info(module, module_obj, 0);

	return 1;
    }

    if (gDynamic_modules[module])
    {
	module_obj = gDynamic_modules[module][SMIS_OBJECT];

        DROP_NOTIFICATION_ONE(gDynamic_modules,
			      gDynamic_create_notifications)
        DROP_NOTIFICATION_ONE(gDynamic_modules,
			      gDynamic_reset_notifications)

	retrieve_module_notify_info(module, module_obj, 1);
	return 1;
    }
}

/*
 * Function name: show_modules_list
 * Description:   Shows module list to object 'who' of (optional) type 'type'.
 * Arguments:     who - The object to receive module list.
 *		  type - The type of registered modules to list.
 * Returns:       
 */
public int
show_modules_list(object who, string type)
{
    int i, access_allowed;
    string res, module,
	   *ids, *types;
    object module_ob;

    if (file_name(previous_object()) != SMIS_CMDSOUL)
	return 0;

    access_allowed = SMIS_ACCESS_ALLOWED(who);
    res = gCaption;
    if (!strlen(type))
    {
	res += "The following modules have been registered:\n\n";
	type = "general";
    }
    else
    {
	res += "The following modules of type '" + type +
	       "' have been registered:\n\n";
    }

    types = m_indexes(gStatic_module_types) - ({ "general", type });
    res += "  Static:\n";
    ids = gStatic_module_types[type];
    for (i = 0; i < sizeof(ids); i++)
    {
	module = ids[i];
	module_ob = find_object(gStatic_modules[module][SMIS_OBJECT]);
	if (access_allowed || gStatic_modules[module][SMIS_OPEN])
	{
	    res += sprintf("     " +
		   (gStatic_modules[module][SMIS_OPEN] ? "O" : "C" ) +
		   (module_ob ? "L" : " ") +
		   (gStatic_modules[module][SMIS_DISABLED] ? " " : "E") +
		   " %-10s: %s\n",
		   module,
		   gStatic_modules[module][SMIS_DESCRIPTION]);
	}
    }

    if (sizeof(types))
    {
	res += "  There are also registered static modules of the following types:\n" +
	       "        " + implode(types, ", ") + ".\n";
    }

    types = m_indexes(gDynamic_module_types) - ({ "general", type });
    res += "\n  Dynamic:\n";
    ids = gDynamic_module_types[type];
    for(i = 0; i < sizeof(ids); i++)
    {
	module = ids[i];
	module_ob = gDynamic_modules[module][SMIS_OBJECT];
	if (access_allowed || gDynamic_modules[module][SMIS_OPEN])
	{
	   res += sprintf("     " +
		  (gDynamic_modules[module][SMIS_OPEN] ? "O" : "C") +
		  (module_ob ? "F" : " ") +
		  (module_ob->query_module_enabled() ? "E" : " ") +
		  " %-10s: %s\n",
		  module,
		  gDynamic_modules[module][SMIS_DESCRIPTION]);
	}
    }

    if (sizeof(types))
    {
	res += "  There are also modules of the following types:\n" +
	       "        " + implode(types, ", ") + ".\n";
    }

    who->catch_tell(res +
		    "\n  [For the list of commands use <smis help commands>]\n" +
		    gBottom);
}

/*
 * Function name: query_module_object
 * Description:   Finds the object with id module_id.
 * Arguments:     module_id - The identifier (not a reference!) of a module
 *			      to find.
 * Returns:       The objectpointer, if module found and 0 if not.
 */
public mixed
query_module_object(string module_id)
{
    mixed ob;

    if (gStatic_modules[module_id])
    {
	ob = gStatic_modules[module_id][SMIS_OBJECT];
	if (check_not_buggy(ob))
	    return find_object(ob);
	else
	    return 0;
    }

    if (gDynamic_modules[module_id])
	return gDynamic_modules[module_id][SMIS_OBJECT];
}

/*
 * Function name: remove_object
 * Description:   Saves the objectpointers to dynamic modules to disk
 *		  to restore it at re-register the modules when the manager
 *		  is loaded into memory.
 *		  The function allows to leave all the registered dynamic
 *		  modules intact, when someone destructs the manager!
 * Returns:       1 (Always, if no errors occur)
 */
public int
remove_object()
{
    mapping tempsave = ([ ]);

    tempsave["S"] = map(m_values(gDynamic_modules),
			&operator([]) (,SMIS_OBJECT));

    if (gData_dir)
        save_map(tempsave, gData_dir + SMIS_TEMPORARY_SAVE);

    destruct();
    return 1;
}

/************************************************************************
 * Module commands redirection.						*
 ************************************************************************/

/*
 * Function name: perform_module_command
 * Description:   Acts as a redirector for 'smis' command, distributes
 *		  commands among the registered modules.
 * Arguments:     
 * Returns:       
 */
public int
perform_module_command(string module, string str)
{
    string foo, function_name;

    if (file_name(previous_object()) != SMIS_CMDSOUL)
	return 0;

    foo = 0;
    if (strlen(str))
    {
	sscanf(str, "%s %s", str, foo);
	    function_name = "perform_" + str + "_command";
    }
    else
    {
	function_name = "perform_empty_command";
    }

    if (gStatic_modules[module] &&
	(SMIS_ACCESS_ALLOWED(this_player()) ||
	    gStatic_modules[module][SMIS_OPEN]))
    {
	return call_other(gStatic_modules[module][SMIS_OBJECT],
	    function_name, foo);
    }

    if (gDynamic_modules[module] &&
	(SMIS_ACCESS_ALLOWED(this_player()) ||
	    gDynamic_modules[module][SMIS_OPEN]))
    {
	return call_other(gDynamic_modules[module][SMIS_OBJECT],
	    function_name, foo);
    }
}

/************************************************************************
 * Run-time patching mechanism						*
 ************************************************************************/

/*
 * Function name: object_created
 * Description:   Notifies all interested registered objects that a particular
 *		  object has been just created.
 * Returns:       1 if object aalso needs to send reset notifications.
 */
public int
object_created(object o_just_created, string s_just_created,
	       string area, string *obj_roles)
{
    object manager = query_module_available(area);
    mixed pa_objects = gStatic_create_notifications[s_just_created];

    if (gStatic_create_notifications[area])
    {
	if(pa_objects)
	    pa_objects += gStatic_create_notifications[area];
	else
	    pa_objects = gStatic_create_notifications[area];
    }

    if (manager)
    {
        manager->notify_object_created(o_just_created, s_just_created,
				       area, obj_roles);
    }

    map(pa_objects, static_module_available)->
	notify_object_created(o_just_created, s_just_created, area, obj_roles);

    map(gDynamic_create_notifications[s_just_created],
	dynamic_module_available)->
	notify_object_created(o_just_created, s_just_created, area, obj_roles);

    map(gDynamic_create_notifications[area], dynamic_module_available)->
	notify_object_created(o_just_created, s_just_created, area, obj_roles);

    if (gStatic_reset_notifications[s_just_created] ||
        gDynamic_reset_notifications[s_just_created])
    {
	return 1;
    }
}

/*
 * Function name: object_reset
 * Description:   Notifies all interested registered modules that a particular
 *		  object has been just was reset.
 */
public void
object_reset(object o_just_reset, string s_just_reset,
	     string area, string *rol_types)
{
    mixed pa_objects = gStatic_reset_notifications[s_just_reset];

    if (gStatic_reset_notifications[area])
    {
	if(pa_objects)
	    pa_objects += gStatic_reset_notifications[area];
	else
	    pa_objects = gStatic_reset_notifications[area];
    }

    map(pa_objects, static_module_available)->
	notify_object_reset(o_just_reset, s_just_reset, area, rol_types);

    map(gDynamic_reset_notifications[s_just_reset],
	dynamic_module_available)->
	notify_object_reset(o_just_reset, s_just_reset, area, rol_types);

    map(gDynamic_reset_notifications[area], dynamic_module_available)->
	notify_object_reset(o_just_reset, s_just_reset, area, rol_types);
}

public mapping
query_static_create_notifications()
{
    if (file_name(previous_object()) != SMIS_CMDSOUL)
	return 0;

    return gStatic_create_notifications;
}

public mapping
query_dynamic_create_notifications()
{
    if (file_name(previous_object()) != SMIS_CMDSOUL)
	return 0;

    return gDynamic_create_notifications;
}

public mapping
query_static_reset_notifications()
{
    if (file_name(previous_object()) != SMIS_CMDSOUL)
	return 0;

    return gStatic_reset_notifications;
}

public mapping
query_dynamic_reset_notifications()
{
    if (file_name(previous_object()) != SMIS_CMDSOUL)
	return 0;

    return gDynamic_reset_notifications;
}

/************************************************************************
 * Module parameters management						*
 ************************************************************************/

public void
set_module_parameter(string module_name, string parameter, string value)
{
    if (!mappingp(gModules_data[module_name]))
	gModules_data[module_name] = ([ ]);

    gModules_data[module_name][parameter] = value;
    save_map(gModules_data, gData_dir + SMIS_MODULES_DATA);
}

public string
query_module_parameter(string module_name, string parameter)
{
    if (mappingp(gModules_data[module_name]))
	return gModules_data[module_name][parameter];
}

public void
remove_module_parameter(string module_name, string parameter)
{
    if (mappingp(gModules_data[module_name]) &&
	gModules_data[module_name][parameter])
    {
	gModules_data[module_name] =
	    m_delete(gModules_data[module_name], parameter);
        save_map(gModules_data, gData_dir + SMIS_MODULES_DATA);
    }
}

/************************************************************************
 * Modules (enabled, disabled) state management				*
 ************************************************************************/

/*
 * Function name: notify_module_enabled
 * Description:   Is called from the module code when it is enabled or disabled.
 *		  Stores the module status information in modules database.
 */
public void
notify_module_enabled(int var)
{
    string module = previous_object()->query_module_id();

    if (gStatic_modules[module])
    {
	gStatic_modules[module][SMIS_DISABLED] = !var;
	save_map(gStatic_modules, gData_dir + SMIS_REGISTERED_OBJECTS);
	return;
    }

    if (gDynamic_modules[module])
    {
	gDynamic_modules[module][SMIS_DISABLED] = !var;
	return;
    }
}

/*
 * Function name: query_module_enabled
 * Returns:       1 - The module is enabled,
 *		  0 - The module is disabled.
 */
public int
query_module_enabled(string module)
{
    if (gStatic_modules[module])
	return !gStatic_modules[module][SMIS_DISABLED];

    if (gDynamic_modules[module])
	return !gDynamic_modules[module][SMIS_DISABLED];
}
