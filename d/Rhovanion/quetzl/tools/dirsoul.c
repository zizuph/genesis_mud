inherit "/cmd/std/tracer_tool_base";

#include <std.h>
#include <macros.h>

#define WIZARD "/cmd/wiz_cmd_normal"
#define APPRENTICE "/cmd/wiz_cmd_apprentice"
#define HELP_FILE "/d/Rhovanion/quetzl/open/dirshelp"

int sf1(string arg);
public int query_tool_soul() { return 1; }
public string get_soul_id() { return "Quetzl's dir soul"; }

public mapping
query_cmdlist()      
{
    return ([
         "qcat":"sf1",
         "qcd":"qcd",
         "qclone":"sf1",
         "qcmdsoul":"sf1",
         "qcp":"sf2",
         "qed":"sf1",
         "qgoto":"sf1",
         "qindent":"sf1",
         "qload":"sf1",
         "qls":"sf1",
        "qmkdir":"sf1",
         "qmore":"sf1",
         "qmv":"sf2",
         "qpushd":"sf1",
         "qpopd":"sf1",
         "qrm":"sf1",
         "qrmdir":"sf1",
         "qtail":"sf1",
         "qtoolsoul":"sf1",
         "qupdate":"sf1",
    ]);
}

public void
reset_euid()
{
    seteuid(getuid(this_interactive()));
}

public mapping
get_map_back()
{
    string sdirst;

    reset_euid();

    sdirst = (string)SECURITY->query_wiz_path((string)this_interactive()->
        query_real_name());
    if (file_size(sdirst + "/.qcd.o") >= 0)
        return restore_map(sdirst + "/.qcd");
    else
        return ([]);
}

public void
replace_old_map(mapping dirst)
{
    string sdirst;
    reset_euid();

    sdirst = (string)SECURITY->query_wiz_path((string)this_interactive()->
        query_real_name());
    save_map(dirst, sdirst +"/.qcd");
}

public string
switch_dir(string arg)
{
    mapping dirst;
    string *stuff, predir;

    reset_euid();

    if (!strlen(arg))
        return arg;

    stuff = explode(arg, "/");
    dirst = get_map_back();
    predir = dirst[stuff[0]];

    if (!predir)
        return arg;

    stuff = exclude_array(stuff, 0, 0);
    if (sizeof(stuff))
        arg = predir + "/" + implode(stuff, "/");
    else
        arg = predir;

    return arg;
}

public int
del_dir(string arg)
{
    mapping dirst;

    dirst = get_map_back();

    notify_fail("That isn't a directory shortcut.\n");
    if (!dirst[arg])
        return 0;

    dirst = m_delete(dirst, arg);
    replace_old_map(dirst);

    write("Directory shortcut " + arg + " deleted.\n");
    return 1;
}

public int
new_dir(string arg)
{
    mapping dirst;
    string dalias, dpath;

    reset_euid();

    dirst = get_map_back();
    
    if (!strlen(arg))
        return 0;

    notify_fail("Proper syntax is qcd -n <alias> <dir>\n");
     if (!parse_command(arg, this_player(), "%w %s", dalias, dpath))
        return 0;

    notify_fail("That alias already exists.  Delete it if you want.\n");
    if (dirst[arg])
        return 0;

    dirst += ([ dalias:dpath ]);
    replace_old_map(dirst);
     write("Directory shortcut " + dalias + " added as " + dpath + "\n");
    return 1;
}

public int
back_up_dir(string arg)
{
    string currdir, *stuff;

    reset_euid();

    notify_fail("qcd -b what?\n");
    if (strlen(arg))
        return 0;

    currdir = (string)this_interactive()->query_path();

    stuff = explode(currdir, "/");
    stuff = exclude_array(stuff, sizeof(stuff)-1, sizeof(stuff)-1);
    currdir = implode(stuff, "/");
    return APPRENTICE->cd(currdir);
}

public int
list_dirs(string arg)
{
    mixed ind, vals;

    int i; mapping dirst;

    reset_euid();

    notify_fail("qcd -l what?\n");
    if (strlen(arg))
        return 0;

    dirst = get_map_back();
    ind = m_indexes(dirst);
    vals = m_values(dirst);

    write("You have the following directory aliases:\n\n");
    for (i = 0; i < sizeof(ind); i++)
        write (ind[i] + ":  " + vals[i] + "\n");
    
    write ("\n");
    return 1;
}

public int
clear_dirs(string arg)
{
    mapping dirst;

    reset_euid();

    notify_fail("qcd -c what?\n");
    if (strlen(arg))
        return 0;

    dirst = ([]);
    replace_old_map(dirst);
    write ("All directory aliases deleted.\n");
    return 1;
}

public int
dirs_help(string arg)
{
    notify_fail("qcd -h does not use any other arguments.\n");
    if (strlen(arg))
        return 0;

    this_player()->more(HELP_FILE);
    return 1;
}

public int
sf1(string arg)
{
    string verb;

    reset_euid();

    arg = switch_dir(arg);
    verb = extract(query_verb(), 1, strlen(query_verb()));

    return this_interactive()->command(verb + " " + arg);
}

public int
sf2(string arg)
{
    string *args;
    args = explode(arg, " ");
    if (sizeof(args) < 2)
        return sf1(arg);
    return sf1(args[0] + " " + switch_dir(args[1]));
}

public int
qcd(string arg)
{
    string newarg, option;

    newarg = "";
    reset_euid();

    if (!strlen(arg))
        return APPRENTICE->cd(arg);

    if (sscanf(arg, "-%s %s", option, newarg) != 2)
         if (!sscanf(arg, "-%s", option))       
            return APPRENTICE->cd(switch_dir(arg));

    notify_fail("Help on the dir soul can be obtained with qcd -h\n");
    switch (option)
    {
        case "n": return new_dir(newarg);
        case "d": return del_dir(newarg);
        case "b": return back_up_dir(newarg);
        case "l": return list_dirs(newarg);
        case "c": return clear_dirs(newarg);
        case "h": return dirs_help(newarg);
    }
}
