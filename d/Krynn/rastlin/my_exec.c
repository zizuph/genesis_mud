/* Aridor, 03/95
 *
 * my_exec.c
 *
 * This soul defines 'Exec'. The only difference to the wizard command
 * 'exec' is that /d/<domain>/<wizard>/defs.h is #included into the
 * exec file as well. This allows for neat shortcuts.
 *
 * Original code taken from /cmd/wiz_cmd_normal.c
 */

#pragma strict_types
#pragma save_binary

inherit "/cmd/std/command_driver";

#include "/sys/macros.h"
#include "/sys/log.h"
#include "/sys/filepath.h"
#include "/sys/filter_funs.h"
#include "/secure/std.h"
#include "/sys/language.h"
#include "/sys/stdproperties.h"

#define CHECK_SO_WIZ 	if (WIZ_CHECK < WIZ_NORMAL) return 0; \
			if (this_interactive() != this_player()) return 0

/* **************************************************************************
 * Return a proper name of the soul in order to get a nice printout.
 */
string
get_soul_id()
{
    return "Exec soul";
}

int
query_tool_soul()
{
    return 1;
}

/* **************************************************************************
 * The list of verbs and functions. Please add new in alfabetical order.
 */
mapping
query_cmdlist()
{
    return ([
	     "Exec":"exec_code",
	     "kman" : "my_man",
	     ]);
}

/*
 * Function name:   exec_write
 * Description:     Write an object file with a function exec_fun()
 *		    that is to be executed. The filename of that file
 *		    is ~/exec_obj.c.
 * Arguments:	    str: the body of the function exec_fun().
 * Returns:	    1 if executing was succesful,
 *		    0 if not; in that case an errormessage has been
 *		    set with notify_fail().
 * Caveats:	    If "str" contains non-executable code, the object
 *		    cannot be loaded, and the gamedriver will give an
 *		    error.
 */
int
exec_write(string str)
{
    object ob;
    string file, master;
    mixed error;

    seteuid(getuid());

    if (!str)
    {
	notify_fail("Nothing to execute.\n");
	return 0;
    }

    file = SECURITY->query_wiz_path(this_player()->query_real_name());

    if (!file)
    {
	notify_fail("Cannot write file.\n");
	return 0;
    }

    master = file + "/exec_obj";

    /* Remove the old copy */
    rm(master + ".c");

    /* Write the new file */
    if (!write_file(master + ".c",
	"inherit \"/std/object\";\n\n" +
	"#include \"/secure/std.h\"\n" +
	"#include \"/sys/adverbs.h\"\n" +
	"#include \"/sys/cmdparse.h\"\n" +
	"#include \"/sys/comb_mag.h\"\n" +
	"#include \"/sys/composite.h\"\n" +
	"#include \"/sys/const.h\"\n" +
	"#include \"/sys/drink_eat.h\"\n" +
	"#include \"/sys/filepath.h\"\n" +
	"#include \"/sys/filter_funs.h\"\n" +
	"#include \"/sys/formulas.h\"\n" +
	"#include \"/sys/herb.h\"\n" +
	"#include \"/sys/language.h\"\n" +
	"#include \"/sys/log.h\"\n" +
	"#include \"/sys/macros.h\"\n" +
	"#include \"/sys/map.h\"\n" +
	"#include \"/sys/math.h\"\n" +
	"#include \"/sys/money.h\"\n" +
	"#include \"/sys/mudtime.h\"\n" +
	"#include \"/sys/obflags.h\"\n" +
	"#include \"/sys/poison_types.h\"\n" +
	"#include \"/sys/seqaction.h\"\n" +
	"#include \"/sys/ss_types.h\"\n" +
	"#include \"/sys/state_desc.h\"\n" +
	"#include \"/sys/stdproperties.h\"\n" +
	"#include \"/sys/subloc.h\"\n" +
	"#include \"/sys/udp.h\"\n" +
	"#include \"/sys/wa_types.h\"\n\n" +
        "#include \"" + file + "/defs.h\"\n\n" +
	"object\nparse(string str)\n{\n    return " +
	"TRACER_TOOL_SOUL->parse_list(str);\n}\n\n" +
	"void\nexec_fun()\n{\n" +
	"    mixed a, b, c, d, e, f, g, h, i, j, k, l, m;\n" +
	"    mixed n, o, p, q, r, s, t, u, v, w, x, y, z;\n\n" +
	"    seteuid(getuid());\n    {\n" +
	str +
	"\n    }\n}\n"))
    {
	notify_fail("Cannot write file.\n");
	return 0;
    }

    /* Update the object, so it will be reloaded */
    ob = find_object(master);
    if (ob)
	SECURITY->do_debug("destroy", ob);
    
    /* Clone the object and call the function exec_fun() in it */
    if (error = catch(ob = clone_object(master)))
    {
	notify_fail("\nError when loading: " + error + "\n");
	return 0;
    }
    write("Executing...\n"); /* Perhaps a call_out is wiser... */
    if (error = catch(ob->exec_fun()))
	write("\nError when executing: " + error + "\n");
    else
	write("\nDone.\n");

    /* Update the object, to spare memory */
    ob->remove_object();
    ob = find_object(master);
    if (ob)
	SECURITY->do_debug("destroy", ob);

    return 1;
}

/*
 * Function name:   exec_edit
 * Description:     Allow players to write multiple lines of code
 * Arguments:	    The text the player entered.
 * Returns:	    1
 */
int
exec_edit(string str)
{
    object tp;
    int quit_exec, error;

    tp = this_player();
    quit_exec = 0;

    if (str == "~q")
    {
	write("Aborted.\n");
	tp->remove_prop("_player_exec_text");
    }
    else if (str != "**")
    {
	if (tp->query_prop("_player_exec_text"))
	    tp->add_prop("_player_exec_text",
			 tp->query_prop("_player_exec_text") + str + "\n");
	else
	    tp->add_prop("_player_exec_text", str + "\n");

	write("]");
	input_to("exec_edit");
    }
    else
	write("Ok, use 'exec' to save and execute it.\n");
    return 1;
}

/* **************************************************************************
 * Here follows the actual functions. Please add new functions in the 
 * same order as in the function name list.
 * **************************************************************************/

/* **************************************************************************
 * Exec - Execute one or more lines of code
 */
int
exec_code(string str)
{
    string code;
    int error;

    if (!str)
    {
	code = this_player()->query_prop("_player_exec_text");
	if (!code || !strlen(code))
	{
	    this_player()->add_prop("_player_exec_text", "");
	    write("Enter code to execute (** to end, ~q to abort).\n]");
	    input_to("exec_edit");
	    return 1;
	}
	else
	{
	    error = exec_write(code);
	    this_player()->remove_prop("_player_exec_text");
	    return error;
	}
    }
    if (str == "clear")
    {
	this_player()->remove_prop("_player_exec_text");
	write("Ok.\n");
	return 1;
    }
    return exec_write(str);
}

int
my_man(string entry)
{
    CHECK_SO_WIZ;

    if (!entry)
    {
        notify_fail("Syntax error, for instructions on usage, do 'help sman'.\n"
);
	return 0;
    }

    return "/cmd/wiz_cmd_apprentice"->lman(entry, "/d/Krynn/common/doc");
}
