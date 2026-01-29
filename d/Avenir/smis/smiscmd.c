// file name:        /d/Avenir/smis/smiscmd.c
// creator(s):       Denis May'96
// purpose:          Smis manager command interface.
#pragma strict_types
inherit "/cmd/std/command_driver";

#include "smis.h"
#include "sys.h"

#define SMIS_HELP_DIR			(SMIS_DIR + "doc/help/")
#define SMIS_SHORT_HELP			(SMIS_HELP_DIR + "short")


static string	gCaption =
"Systems Management Integrated Services Command Redirector: ----------------\n",
		gBottom =
"---------------------------------------------------------------------v." + SMIS_VERSION + "\n";

/* Prototypes.
 */
static string form_notifications(mapping notf);

public string get_soul_id()    { return "SMIS"; }
public int    query_cmd_soul() { return 1;      }

public mapping
query_cmdlist()
{
    return ([ "smis":	"smis" ]);
}

static string
get_cmdname(string get_from)
{
    sscanf(get_from, "perform_%s_command", get_from);
    return get_from;
}

public int
smis(string command)
{
    string foo, manager;

    setuid();
    seteuid(getuid());
    
    if (!strlen(command))
	command = "";

    sscanf(command, "%s %s", command, foo);

    manager = capitalize(command);
    if (SMIS_DOMAIN_EXISTS(manager))
    {
	manager = SMIS_MANAGER_DOM(manager);

	if (strlen(foo))
	{
	    command = foo;
            sscanf(command, "%s %s", command, foo);
	}
	else
	{
	    command = 0;
	}
    }
    else
    {
	manager = SMIS_MANAGER_DOM(SMIS_WIZARD_DOMAIN_OB(this_player()));
    }

    if (!strlen(command))
	command = "list";

    if (!find_object(manager) && catch(manager->telelednignsanka()))
    {
	write(
"Sorry the domain you specified (or domain taken by default) either doesn't\n" +
"have a smis manager instance, or it is unavailable for some reason.\n");
	return 1;
    }

    switch(command)
    {
    case "help":
	if (foo)
	{
	    if (file_size(SMIS_HELP_DIR + foo) > -1 )
	    {
	        this_player()->catch_msg(gCaption +
				     read_file(SMIS_HELP_DIR + foo) + gBottom);
	    }
	    else
	    {
		this_player()->catch_msg(gCaption +
		 "\nSMIS help topic you requested doesn't exist.\n\n" + gBottom);
	    }
	}
	else
	{
	    this_player()->catch_msg(gCaption +
		read_file(SMIS_SHORT_HELP) + gBottom);
	}
	return 1;

    /* Getting the list of registered modules? */
    case "list":
	manager->show_modules_list(this_player(), foo);
	return 1;

    /* Enqiring what creation notification triggers are present */
    case "cnotify":
	this_player()->more(gCaption +
	     "    Static modules create notification list:\n\n" +
	     form_notifications(manager->query_static_create_notifications()) +
	     "\n\n    Dynamic modules create notification list:\n\n" +
	     form_notifications(manager->query_dynamic_create_notifications()) +
	     gBottom, 0, 0);
	return 1;

    case "rnotify":
	this_player()->more(gCaption +
	      "    Static modules reset notification list:\n\n" +
	      form_notifications(manager->query_static_reset_notifications()) +
	      "\n\n    Dynamic modules reset notification list:\n\n" +
	      form_notifications(manager->query_dynamic_reset_notifications()) +
	      gBottom, 0, 0);
	return 1;

    case "nreload":
	if (manager->reload_module_notify_info(foo))
	{
	    write(gCaption + "\nReload notification information OK.\n\n" +
		  gBottom);
	}
	else
	{
	    write(gCaption + "\nReload notification information FAILURE.\n\n" +
		  gBottom);
	}
	return 1;

    /* Registering a new one? */
    case "register":
	if (manager->register_smis_module(foo))
	    write("Ok.\n");
	else
	    write("Registration failed.\n");
	return 1;

    /* Dropping the unneeded one? */
    case "drop":
	if (manager->drop_smis_module(foo))
	    write("Ok.\n");
	else
	    write("Drop module failed.\n");
	return 1;

#if 0
    case "cmdlist":
	{
	    string *functions, *cmds, res;
	    mixed module_obj;

	    module_obj = manager->query_module_object(foo);
	    functions = SECURITY->do_debug("functionlist", module_obj);
	    functions = filter(functions, &wildmatch("perform_*_command",));
	    cmds = map(functions, get_cmdname) - ({ "empty" });
	    res = gCaption;
	    foreach(string str: cmds)
		res += str + "\t\t";
	    write(res + "\n" + gBottom);

	    return 1;
	}
#endif

    case "enable":
	{
	    object module_obj;

	    module_obj = manager->query_module_object(foo);
	    if (!module_obj)
	    {
		write(gCaption +
		      "\nNo such module exists or is unloadable.\n\n" +
		      gBottom);
		return 1;
	    }
            module_obj->set_module_enabled(1);
            write(gCaption + "\nThe module is now enabled.\n\n" + gBottom);
            SMIS_WRITE_LOG(this_player()->query_real_name() +
		           " enabled the '" + foo + "' module.\n");
	    return 1;
	}

    case "disable":
	{
	    object module_obj;

	    module_obj = manager->query_module_object(foo);
	    if (!module_obj)
	    {
		write(gCaption +
		      "\nNo such module exists or is unloadable.\n\n" +
		      gBottom);
		return 1;
	    }
            module_obj->set_module_enabled(0);
            write(gCaption + "\nThe module is now disabled.\n\n" + gBottom);
            SMIS_WRITE_LOG(this_player()->query_real_name() +
		           " disabled the '" + foo + "' module.\n");
	    return 1;
	}

    /* Maybe it is a module id? */
    default:
        if (manager->perform_module_command(command, foo))
	    return 1;
	else
	{
            notify_fail("Wrong SMIS command or module name" +
		(strlen(foo) ? ".\n" :
		    " or no default command handler in module.\n"));
	    return 0;
	}
    }
}

static string
form_notifications(mapping notf)
{
    string str = "";
    mapping data = ([ ]);

    foreach(string key, string *arr: notf)
    {
	foreach(string val: arr)
	{
	    if (!pointerp(data[val]))
		data[val] = ({ });

	    data[val] += ({ key });
	}
    }

    foreach(string key, string *arr: data)
    {
	str += key + ":\n    ";
	str += implode(sort_array(arr), "\n    ");
	str += "\n";
    }

    return str;
}
