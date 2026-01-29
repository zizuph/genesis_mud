inherit "/std/object";
inherit "/cmd/std/tracer_tool_base";

#include "/d/Ansalon/common/defs.h"
#include <files.h>
#include <filepath.h>
#include <options.h>
#include <macros.h>

/* These properties are used by this object only. */
#define WIZARD_AS_DIRPATH "_wizard_as_dirpath"
#define WIZARD_S_LAST_DIR "_wizard_s_last_dir"

/* Sarr */

string
query_auto_load()
{
    return MASTER;
}

void
create_object()
{
    set_name("key");
    set_adj("Ansalon");
    set_long("This is the Ansalon help key to make life easier for "+
    "wizards of Ansalon. Do 'ahelp' to get the info.\n");
    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_I_VOLUME,1);
}

void
enter_env(object env, object from)
{
    if(interactive(env))
    {
        if(SECURITY->query_wiz_dom(lower_case(env->query_name())) != 
           "Ansalon")
            set_alarm(1.0,0.0,"remove_the_key",env);
    }
    ::enter_env(env,from);
}

void
remove_the_key(object ob)
{
    set_this_player(ob);
    write("You are not a member of the Ansalon domain, so the "+
    short()+" melts away.\n");
    remove_object();
}

void
init()
{
    ::init();
    add_action("do_ahelp","ahelp");
    add_action("do_log","apr");
    add_action("do_log","abug");
    add_action("do_log","aidea");
    add_action("do_log","arun");
    add_action("do_log","atyp");
    add_action("do_ad","ad");
    add_action("adirlist","adirlist");
}


int
do_ad(string str)
{
    string old_path;
    string new_path;
    string *parts;
    object ob;
    int    auto;

    auto = this_player()->query_option(OPT_AUTO_PWD);

    old_path = this_interactive()->query_path();
    if(extract(str,0,0) == "@")
    {
        if(str == "@log")
            new_path = "/d/Ansalon/log/";
        if(str == "@san")
            new_path = "/d/Ansalon/taman_busuk/sanction/";
        if(str == "@ner")
            new_path = "/d/Ansalon/taman_busuk/neraka/";    
        if(str == "@flot")
            new_path = "/d/Ansalon/balifor/flotsam/";
        if(str == "@std")
            new_path = "/d/Ansalon/std/";
        if(str == "@com")
            new_path = "/d/Ansalon/common/";
        if(!new_path)
        {
            write("No such alias.\n");
            return 1;
        }
    }
    else
    {
    if (!stringp(str))
    {
	new_path = SECURITY->query_wiz_path(this_player()->query_real_name());
    }
    else switch(str)
    {
    case ".":
	new_path = old_path;
        if (auto)    
            write(new_path + "\n");
	else
            write("Ok.\n");
        return 1;

    case "-":
	new_path = this_player()->query_prop(WIZARD_S_LAST_DIR);
	break;

    default:
	new_path = FTPATH(old_path, str);
	break;
    }
    }
    if (file_size(new_path) != -2)
    {
	if (!objectp(ob = parse_list(str)))
	{
	    notify_fail("No such directory '" + str + "'.\n");
	    return 0;
	}

	parts = explode(file_name(ob), "/");
	new_path = implode(parts[0..(sizeof(parts) - 2)], "/");
    }

    write(new_path + "\n");
    this_player()->add_prop(WIZARD_S_LAST_DIR, old_path);
    this_player()->set_path(new_path);
    seteuid(getuid());
    ls(new_path,"");
    return 1;
}

int
do_log()
{
    seteuid(getuid());
    switch(query_verb())
    {
        case "apr":
        tail("/d/Ansalon/log/praise");
        break;
        case "abug":
        tail("/d/Ansalon/log/bugs");
        break;
        case "aidea":
        tail("/d/Ansalon/log/ideas");
        break;
        case "arun":
        tail("/d/Ansalon/log/runtime");
        break;
        case "atyp":
        tail("/d/Ansalon/log/typos");
        break;
    }
    return 1;
}

int
do_ahelp()
{
    write("You can do the following:\n"+
    "ahelp    - This message\n"+
    "apr      - Tail the praise log\n"+
    "abug     - Tail the bug log\n"+
    "aidea    - Tail the idea log\n"+
    "arun     - Tail the runtime log\n"+
    "atyp     - Tail the typos log\n"+
    "ad       - Works like cd, only it lists the files right aver\n"+
    "ad @<al> - Use one of the dir aliases. Do adirlist for list.\n");
    return 1;
}

int
adirlist()
{
    seteuid(getuid());
    cat("/d/Ansalon/common/dir_list");
    return 1;
}

