/* 
 * The Soul of Krynn             (/d/Krynn/common/krynn_soul.c)
 *
 *
 * Version 1.00 by Lord Rastlin,   01/92
 *       commands: lu, luc, lug, path, bomb, c, khelp, tl.
 * Version 2.00 by Aridor&Rastlin, 03/95
 *       updated commands: lu->ul, luc->ulc, lug->ulg, c->copy.
 *       added commands:   Exec, kman, tb, ti, td, tr, tt, tp.
 * Version 2.01 by Aridor          03/95
 *       added command:    qq - suggested by Stevenson
 *       added commands:   loadmany - (original code by Plugh)
 *                         grep     - (original code by Caution)
 *                                    (both taken from
 *                                     /d/Krynn/aridor/grep&load)
 * Version 2.02 by Rastlin         04/95
 *       added command:    dl - A domain tell to be used by the
 *                              Krynn and Ansalon domain.
 * Version 2.03 by Aridor          04/95
 *       removed the commands: loadmany, grep.
 *       the commands grep and loadmany are now available from
 *       /d/Krynn/aridor/open/grep&load.
 * Version 2.04 by Aridor          05/95
 *       added command:    extractlog - A command to move log
 *                              entries to the subdirs.
 *                              Command coded by Rastlin.
 * Version 2.10 by Aridor          05/96
 *       remove commands:  dl,dle,Exec,
 *                 since the commands are now standard cmds.
 *                              
 */

/* Inherits */

inherit "/cmd/std/command_driver";

/* Includes */

#include <filepath.h>
#include <std.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

/* Defines */

#define CHECK_SO_WIZ 	if (WIZ_CHECK < WIZ_NORMAL) return 0; \
			if (this_interactive() != this_player()) return 0

#define EXTRA_PATH      "_krynn_ext_path"
#define VER             "V2.04"
#define GENESISHOST     (host_name ? host_name : "spica3")
#define THIS_DOMAIN     (SECURITY->query_wiz_dom(this_interactive()->\
						 query_real_name()))
#define QUEST_LOGS      "/d/" + THIS_DOMAIN + "/common/log/quests/"
#define LINES           1000
#define WORKROOM        ("/d/" + THIS_DOMAIN + "/workroom")


/* Prototypes */

string get_file_path(string str);
int my_load(string str);
int my_update(string str);
int my_clone(string str);
int my_goto(string str);
string get_host_name();

/* Global Variables */

static string host_name = get_host_name();

/* The ID of this Soul */
string 
get_soul_id() 
{
    return "Krynnsoul";
}

/* Soul type */
int
query_tool_soul() 
{
    return 1;
}

/* The list of functions and verbs */
mapping
query_cmdlist() 
{
    
    return (["bomb":	"my_bomb",
	     "copy":	"my_copy",
	     "dl" :     "dragonlance_tell",
	     "dle" :    "dragonlance_emote",
	     "extractlog":"extractlogs",
	     /*"Exec":    "exec_code",*/
	     "khelp":	"my_help",
	     "kman":    "my_man",
	     "path":	"my_set_path",
	     "qq":      "query_quest",
	     "tb":      "my_tail_log",
	     "td":      "my_tail_log",
	     "ti":      "my_tail_log",
	     "tl":      "my_tail_log",
	     "tp":      "my_tail_log",
	     "tr":      "my_tail_log",
	     "dtrust":  "do_trust",
	     "tt":      "my_tail_log",
	     "ul":	"my_load_update",
	     "ulc":	"my_load_update_clone",
	     "ulg":	"my_load_update_goto"
	     ]);
}

/* Function name: get_host_name
 * Description:   Find out the name of the machine the mud is on.
 */
string
get_host_name()
{
    string *files = get_dir("/");
    int i;
    string str;
    for(i=0;i<sizeof(files);i++)
      if (sscanf(files[i],"%s.debug.log",str) == 1)
	return str;
}

/*
 * Function name: get_file_path
 * Description:   Try to get the filepath from the current path, if not ok
 *                try to get it from the extra path, if available
 * Argument:      string: The file name
 * Return:        The filepath (string)
 */
string
get_file_path(string str) 
{
    string curr_path, ext_path, temp, var1, var2;
    
    if (!strlen(str)) 
      {
	  NF("What about a file name?\n");
	  return 0;
      }
    
    curr_path = FTPATH(this_interactive()->query_path(), str);
    ext_path = this_interactive()->query_prop(EXTRA_PATH);
    
    if (sscanf(str, "%s.%s", var1, var2) != 2) 
      str += ".c";
    if (ext_path) 
      ext_path = FTPATH(ext_path, str);
    
    if (strlen(curr_path)) 
      if (file_size(curr_path) >= 0) return curr_path;
      else temp = curr_path;
    
    if (strlen(ext_path))
      if (file_size(ext_path) >= 0) 
	return ext_path;
      else if (!strlen(temp)) 
	temp = ext_path;
    
    if (!strlen(curr_path) && !strlen(ext_path) && !strlen(temp)) 
      {
	  NF("Invalid file name.\n");
	  return 0;
      }
    return temp;
}

/*
 * Function name: my_load
 * Description:   Load the give file. This function is just made to get
 *                all the errors in the same line. ;-)
 * Argument:      string: filepath
 */
int
my_load(string str) 
{
  string err = catch(str->teleledningsanka());
  if (err)
      {
        write("Error:\n    " + err);
	return 0;
      }
    return 1;
}

/*
 * Function name: my_update
 * Description:   Update an object ... Destruct it..
 * Argument:      string: filepath
 */
void
my_update(string str) 
{
    object obj;
    
    obj = find_object(str);
    if (obj) 
      obj->remove_object();
    if (obj) 
      SECURITY->do_debug("destruct",obj);
}

/*
 * Function name: my_clone
 * Description:   Clone an object and move it.
 * Argument:      string: filepath
 */
void
my_clone(string str) 
{
    object ob;
    int num;
    
    ob = clone_object(str);
    if (!ob) 
      {
	  NF("You can not clone: " + str + "\n");
	  return 0;
      }
    num = (int)ob->move(environment(this_interactive()));
    if (num) 
      {
	  NF("Can't let that object enter this room: " + num + ".\n");
	  return 0;
      }
    say(QCTNAME(this_interactive())
	+ " fetches something from another dimension.\n");
    num = (int)ob->move(this_interactive());
    switch (num) 
      {
	case 0:
	  write("Success.\n");
	  break;
	  
	case 1:
	  write("To heavy for destination.\n");
	  break;
	  
	case 2:
	  write("Can't be dropped.\n");
	  break;
	  
	case 3:
	  write("Can't take it out of it's container.\n");
	  break;
	  
	case 4:
	  write("The object can't be inserted into bags etc.\n");
	  break;
	  
	case 5:
	  write("The destination doesn't allow insertions of objects.\n");
	  break;
	  
	case 6:
	  write("The object can't be picked up.\n");
	  break;
	  
	case 7:
	  write("Other (Error message printed inside move() function).\n");
	  break;
	  
	case 8:
	  write("To big volume for destination.\n");
	  break;
	  
	default:
	  write("Strange, very strange error in move: " + num + "\n");
	  break;
    }
}

/*
 * Function name: my_goto
 * Description:   Teleport somewhere
 * Argument:      string: filepath
 */
void
my_goto(string str) 
{
    object ob;
    string name;
    
    if (catch(this_interactive()->move_living("X", str))) 
      {
	  NF("Invalid file name: " + str + "\n");
	  return 0;
      }
}
/*
 * Function name: my_bomb
 * Description:   Destruct all non living objects in a room
 */
int
my_bomb() 
{
    object *obj_arr;
    int i, done;
    
    CHECK_SO_WIZ;
    
    done = 1;
    i = 0;
    obj_arr = all_inventory(environment(TP));
    while (i < sizeof(obj_arr)) 
      {
	  if ((!living(obj_arr[i]) && obj_arr[i] != environment()) ||
	      obj_arr[i]->query_npc()) 
	    {
		write(obj_arr[i]->query_name() + ": Destructed.\n");
		obj_arr[i]->remove_object();
		done=0;
	    }
	  i += 1;
      }
    if (done) 
      {
	  write("Done.\n");
	  say(QCTNAME(TP) + " sends rays of destructions in all directions.\n");
      } 
    else 
      my_bomb();
    return 1;
}  

/*
 * Function name: my_copy
 * Description:   Copy a file from extra path to current dir.
 * Argument:      string: File name and maybe the new name too.
 */
int
my_copy(string str) 
{
    string ext_path, from, to, content;
    
    CHECK_SO_WIZ;
    
    if (!strlen(str)) 
      {
	  NF("What about a filename?\n");
	  return 0;
      }
    if (!(ext_path = this_interactive()->query_prop(EXTRA_PATH))) 
      {
	  NF("You need to set the extra path first.\n");
	  return 0;
      }
    if (sscanf(str, "%s %s", from, to) == 2) 
      {
	  from = FTPATH(ext_path, from);
	  to = FTPATH(this_interactive()->query_path(), to);
      }
    else 
      {
	  from = FTPATH(ext_path, str);
	  to = FTPATH(this_interactive()->query_path(), str);
      }
    content = read_file(from);
    if (content == 0) 
      {
	  NF("Failed to read contents of " + from + ".\n");
	  return 0;
      }
    /* write_file() will append */
    if (file_size(to) != -1 && !rm(to)) 
      {
	  NF("Failed to remove " + to + "\n");
	  return 0;
      }
    write_file(to, content);
    write("Done.\n");
    return 1;
}
  
/*
 * Function name: my_help
 * Description:   A help function for the commands
 * Argument:      string: The command you want help about
 * Return:        True if success
 */
int
my_help(string str) 
{
    
    CHECK_SO_WIZ;
    
    if (!strlen(str)) 
      {
	  write("The Soul of Krynn " + VER + "    original idea by Lord Rastlin\n" +
		"--------------------------------------------------------\n" +
		"The idea with this soul is that it should make the life\n" +
		"much more easier.\n" +
		"If you want help with any of the commands, type: khelp <command>\n" +
		"These commands are currently available:\n" +
		"  bomb             copy             extractlog\n" +
		"  kman             ul               ulc\n" +
		"  ulg              path             qq\n" +
		"  tb               td               ti\n" +
		"  tl               tp               tr\n" +
		"  tt               grep             loadmany\n");
	  return 1;
      }
    switch(str) 
      {
	case "bomb":
	  write("Destruct ALL non living objects in the room.\n"
		+ "Should be used with care, since invisible objects\n"
		+ "can be destructed too.\n");
	  break;
	  
	case "copy":
	  write("A copy command.\n"
		+ "copy <filename> [newname]\n"
		+ "It will copy a file from the extra path (set with the\n"
		+ "path command) to the current dir. But it also works as\n"
		+ "a normal cp command.\n"
		+ "Examples:\n"
		+ "  copy apa.c            Copy from extra path to current dir.\n"
		+ "  copy apa.c bepa.c     Same as above but change the name.\n"
		+ "  copy misc/apa.c       Copy from extra path + /misc to current dir.\n"
		+ "  copy apa.c ~/bepa.c   Copy from extra path to your home dir.\n"
		+ "  copy ~/apa.c bepa.c   Copy from your homedir to current dir.\n");
	  break;
	  
	case "extractlog":
	  write("Extract logs from the domain log directory into specific dirs.\n" +
		"extractlog <pathname w/out domain> [whichlogs]\n" +
		"  [whichlogs] can be empty (= all logs) or contain any letters\n" +
		"   of 'btip', with b = bugs, t = typos, i = ideas, p = praise.\n" +
		"Allows to extract the typo, bug, idea and praise log entries of\n" +
		"a certain area into this area's log dir.\n" +
		"This is useful to keep the general logs tidy and to get all the\n" +
		"log entries for your area in one place.\n\n" +
		"Examples:\n" +
		"  extractlog pax b          Extract the bug log of the pax dir.\n" +
		"  extractlog solamn/palan   Extract all four logs for the solamn/palan dir.\n");
	  break;

	/*case "Exec":
	  write("Exec a short program.\n" +
		"Exec [string]\n" +
		BS("As a normal exec, but it includes the file /d/<domain>/<wizard>/defs.h" +
		   "if the file is present. This allows for personal #defines, #inludes and " +
		   "even functions to be called.\n",70));
	  break;
	  */
	case "grep":
	  write("NOT AVAILABLE IN THIS SOUL ANYMORE: clone /d/Krynn/aridor/open/grep&load INSTEAD.\n" +
		"Grep files in the current directory for a string.\n" +
		"grep [-rv] <string>,    grep -u\n" +
		BS("You need to cd to the directory you want to grep in and must " +
		   "of course have read access for it to work. <string> is then " +
		   "searched for in all files in that dir. Options:",70) +
		"   -r   Recursive. Search all subdirectories as well.\n" +
		"   -v   Verbose. Display filenames of each file before grepping it.\n" +
		"   -u   Update/Reset. In case the grepper gets stuck or whatever,\n" +
		"        reset it again.\n" +
		"NOTE: Make sure that you use the correct grep, you may have more than one. ;-)\n");
	  break;

	case "kman":
	  write("The " + THIS_DOMAIN + "  manual!\n" +
		"kman <options>\n" +
		"To see a list of options, please do 'help lman'. To get an overview " +
		"what's in the " + THIS_DOMAIN + " manual type: 'kman -k *'. The kman command will " +
		"direct you to the " + THIS_DOMAIN + " documentation directory where you can " +
		"find info on " + THIS_DOMAIN + " specific coding, rules and general topics. If " +
		"there is something you don't find in there, please feel free to add " +
		"it. Informing the liege that you'd like something added might work, " +
		"too, but is not guaranteed.\n" +
		"Here's an (incomplete) how to use 'kman':\n" +
		" kman <string>    : Manual info on this topic. If <string> has a wild-\n" +
		"                    card (see below), pick the first match.\n" +
		" kman -k <string> : List all topics containing <string>.\n" +
		"    <string>      : If <string> has a trailing or leading '*', this\n" +
		"                    is treated as a wildcard.\n" +
		" kman -D <domain> <options>: Look in the manual of <domain> instead your own.\n");
	  break;

	case "loadmany":
	  write("NOT AVAILABLE IN THIS SOUL ANYMORE: the std 'load' command will do this now.\n" +
		"Load several files in one go.\n" +
		"loadmany <files>\n" +
		BS("You give a filename (may contain a * as wildcard) and all " +
		   "files matching will be tried and loaded.",70));
	  break;

	case "qq":
	  write("qq [quest_name]\n" +
		BS("Look at who solved the Krynn quests recently. Giving 'qq' without " +
		   "argument, list all quests and the time they were last solved. " +
		   "To see who the last solvers of a certain quest were, give the " +
		   "quest_name (ie. 'qq tour1') as argument.",70));
	  break;
	case "ul":
	  write("Update and Load in one command.\n"
		+ "ul <file>\n"
		+ BS("As a normal update and load, but with "
		     + "a small feature. If it can't find the file in the current dir, "
		     + "then it will look in the extra path (set with the path command). "
		     + "This means that you can update and load a file in another dir, "
		     + "without giving the path every time.",70));
	  break;
	  
	case "ulc":
	  write("Update, Load and Clone in one command.\n"
		+ "ulc <file>\n"
		+ BS("As a normal update, load and clone, but with a small feature. "
		     + "If it can't find the file in the current dir then it will look in "
		     + "the extra path (set with the path command). This means that you "
		     + "can update, load and clone a file in another dir, without giving "
		     + "the path every time.",70));
	  break;
	  
	case "ulg":
	  write("Update, Load and Goto in one command.\n"
		+ "ulg <file>\n"
		+ BS("As a normal update, load and goto, but with a small feature. "
		     + "If it can't find the file in the current dir then it will look in "
		     + "the extra path (set with the path command). This means that you "
		     + "can update, load and goto a file in another dir, without giving "
		     + "the path every time.",70));
	  break;
	  
	case "path":
	  write("Set an extra path.\n"
		+ "path <a path>\n"
		+ BS("With path you can set an extra path "
		     + "that is used by some of the commands in this soul (path without "
		     + "a argument will show the set path, if any). It makes it "
		     + "possible to work in two directorys at one time. If you are doing "
		     + "a monster with some weapons. The monster is in one directory and "
		     + "the weapons in another. Then you set the extra path to the "
		     + "monster's directory and uses cd to set the weapons' directory. "
		     + "Now you can edit the weapon without giveing any paths and you can "
		     + "do 'ulc <monster>' without giving any paths. Easy??",70));
	  break;
	  
	case "tb":
	  write("This is a short version of 'tail /d/" + THIS_DOMAIN + "/log/bugs'.\n");
	  break;

	case "td":
	  write("This is a short version of 'tail /" + GENESISHOST + ".debug.log'.\n");
	  break;

	case "ti":
	  write("This is a short version of 'tail /d/" + THIS_DOMAIN + "/log/ideas'.\n");
	  break;

	case "tl":
	  write("This is a short version of 'tail /lplog'.\n");
	  break;
	  
	case "tp":
	  write("This is a short version of 'tail /d/" + THIS_DOMAIN + "/log/praise'.\n");
	  break;

	case "tr":
	  write("This is a short version of 'tail /d/" + THIS_DOMAIN + "/log/runtime'.\n");
	  break;

	case "tt":
	  write("This is a short version of 'tail /d/" + THIS_DOMAIN + "/log/typos'.\n");
	  break;

	default:
	  NF("No help on that available.\n");
	  return 0;
	  break;
      }
    return 1;
}
      
/*
 * Function name: my_load_update
 * Description:   Load and Update in one function
 * Argument:      string: The file to load and update
 * Return:        An error or success
 */
int
my_load_update(string str) 
{
    string file;
    
    CHECK_SO_WIZ;
    
    if (!(file = get_file_path(str))) 
      return 1;
    write("File: " + file + "\n");
    write("Updating...");
    my_update(file);
    write("Success.\n");
    write("Loading....");
    if (!my_load(file))
      return 1;
    write("Success.\n");
    return 1;
}

/*
 * Function name: my_load_update_clone
 * Description:   Load, Update and Clone in one function
 * Argument:      string: The file to load, update and clone
 * Return:        An error or success
 */
int
my_load_update_clone(string str) 
{
    string file;
    
    CHECK_SO_WIZ;
    
    if (!(file = get_file_path(str))) return 1;
    write("File: " + file + "\n");
    write("Updating..");
    my_update(file);
    write("Success.\n");
    write("Loading....");
    if (!my_load(file))
      return 1;
    write("Success.\n");
    write("Cloning...");
    my_clone(file);
    return 1;
}

/*
 * Function name: my_load_update_goto
 * Description:   Load, Update and Goto in one function
 * Argument:      string: The file to load, update and goto to
 * Return:        An error or success
 */
int
my_load_update_goto(string str) 
{
    string file;
    
    CHECK_SO_WIZ;
    
    if (!(file = get_file_path(str))) return 1;
    write("File: " + file + "\n");
    write("Updating..");
    my_update(file);
    write("Success.\n");
    write("Loading....");
    if (!my_load(file))
      return 1;
    write("Success.\n");
    my_goto(file);
    return 1;
}

/*
 * Function name: my_set_path
 * Description:   Set the extra path.
 * Argument:      The new path
 * Returns:       True if success.
 */
int
my_set_path(string str) 
{
    string path;
    
    CHECK_SO_WIZ;
    
    if (!strlen(str)) 
      {
	  if ((path = this_interactive()->query_prop(EXTRA_PATH))) 
	    {
		write("Extra path: " + path + "\n");
		return 1;
	    }
	  else 
	    {
		write("No extra path set yet.\n");
		return 1;
	    }
      }
    path = FTPATH(this_interactive()->query_path(), str);
    if (!strlen(path)) 
      {
	  NF("Bad pathname format: " + str + "\n");
	  return 0;
      }
    if (file_size(path) != -2) 
      {
	  NF("Not a directory: " + path + "\n");
	  return 0;
      }
    write("Extra path set to: " + path + "\n");
    this_interactive()->add_prop(EXTRA_PATH,path);
    return 1;
}
  
/*
 * Function name: my_tail_log
 * Description:   tail /lplog
 */
int
my_tail_log() 
{
    
    CHECK_SO_WIZ;

    switch(query_verb())
      {
	case "tb": 
	  tail("/d/" + THIS_DOMAIN + "/log/bugs");
	  break;
	case "ti": 
	  tail("/d/" + THIS_DOMAIN + "/log/ideas");
	  break;
	case "tp": 
	  tail("/d/" + THIS_DOMAIN + "/log/praise");
	  break;
	case "tr":
	  tail("/d/" + THIS_DOMAIN + "/log/runtime");
	  break;
	case "tt": 
	  tail("/d/" + THIS_DOMAIN + "/log/typos");
	  break;
	case "td":
	  tail ("/" + GENESISHOST + ".debug.log");
	  break;
	case "tl": 
	  tail("/lplog");
	  break;

      }
    return 1;
}

#if 0
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
	(file_size(file + "/defs.h") > 0 ?
	 "#include \"" + file + "/defs.h\"\n\n" : "") +
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
    write("Executing...\n"); /* Perhaps an alarm is wiser... */
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
#endif

/* The Krynnish Manual! */
int
my_man(string entry)
{
    string oldpath, domain, dom = 0;
    int ret;
    string *args;

    CHECK_SO_WIZ;

    if (!entry)
    {
        NF("Syntax error, for instructions on usage, do 'khelp kman'.\n");
	return 0;
    }
    
    args = explode(entry," ") - ({0,""});
    if (args[0] == "-D")
      {
	dom = args[1];
	entry = implode(args[2..]," ");
      }

    /* This may be an ugly patch, but it works ;-) */
    oldpath = this_interactive()->query_path();

    domain = SECURITY->query_wiz_dom(this_interactive()->query_real_name());
    if (this_interactive()->query_name() == "Rastlin")
      domain = "Krynn";
    if (dom && stringp(dom))
      domain = C(L(dom));

    write("The " + domain + " manual:\n");
    this_interactive()->set_path("/d/" + domain + "/common/doc");
    ret = this_interactive()->command("lman " + entry);
    this_interactive()->set_path(oldpath);

    return ret;
}

/* The Krynnish quest log checker */

int
query_quest(string which)
{
    mixed dir;
    string last,oldpath;
    int i;
    if (!which)
      {
	  dir = get_dir(QUEST_LOGS);
	  write("Quests in Krynn:\n" +
		"Name                        Last solved\n");
	  for(i=0;i<sizeof(dir);i++)
	    {
		last = ctime(file_time(QUEST_LOGS + dir[i]));
		write(sprintf("%-12s%40s\n",dir[i], last));
	    }
	  return 1;
      }
    if (file_size(QUEST_LOGS + which) >= 0)
      {
	  write("Last solvers of: " + which + "\n");
	  tail(QUEST_LOGS + which);
	  return 1;
      }
    /* doesn't seem possible currently...*/
    if (SECURITY->exist_player(which))
      {
	  write("Solved quests of: " + which + "\n");
	  dir = get_dir(QUEST_LOGS);
	  write("Quests in Krynn:\n" +
	        "Name                        Solved when\n");
	  oldpath = TP->query_path();
	  TP->set_path(QUEST_LOGS);
	  TP->command("trust grepper");
	  TP->command("grep " + L(which));
	  TP->command("grep " + C(L(which)));
	  TP->set_path(oldpath);
	  return 1;	  
      }
      
    write("No such quest found!\n");
    return 1;
}

#if 0
/*
 * Tell a player a message.
 */
public varargs int
filter_tell(string player_name, string *misc, string sep = "")
{
    object player;

    if ((player_name != misc[0]) && (player = find_player(player_name)))
    {
        player->catch_msg("@ DRAGONLANCE " + C(misc[0]) + sep + misc[1] + "\n");
        return 1;
    }
    else
        return 0;
}
#endif
/*
 * Tell all the wizards in Krynn and Ansalon a message
 */
public int
dragonlance_tell(string str)
{
    string *members, *told, told_mess;
    int size, i = 0;

    CHECK_SO_WIZ;

    write("This channel has been closed. Please use 'line dragon' from " +
	  "now on. Maybe 'alias dl line dragon' will do the trick..:)\n");
    return 1;
#if 0    
    if (!str || !strlen(str))
        return 0;

    members = SECURITY->query_domain_members("krynn");
    members += SECURITY->query_domain_members("ansalon") + ({});
    members += ({ "rastlin" });
    
    told = filter(members, &filter_tell(,({TP->query_real_name(), str}), ": "));

    size = sizeof(told);

    if (!size)
        return NF("There is no one here to hear you.\n");

    told_mess = "DL: You told: " + C(told[i]);

    while (++i < size)
        told_mess += ", " + C(told[i]);

    if (TP->query_get_echo())
        told_mess += ".\nYou DLtold: " + str;

    TP->catch_msg(told_mess + "\n");
    return 1;
#endif
}

/*
 * Emote something to  all the wizards in Krynn and Ansalon
 */
public int
dragonlance_emote(string str)
{
    string *members, *told, told_mess;
    int size, i = 0;

    CHECK_SO_WIZ;

    write("This channel has be closed. Please use 'linee dragon' from now " +
	  "on. Maybe 'alias dle linee dragon' will do the trick..:)\n");
    return 1;
#if 0
    if (!str || !strlen(str))
        return 0;

    members = SECURITY->query_domain_members("krynn");
    members += SECURITY->query_domain_members("ansalon") + ({});
    members += ({ "rastlin" });
    
    told = filter(members, &filter_tell(,({TP->query_real_name(), str}), " "));

    size = sizeof(told);

    if (!size)
        return NF("There is no one here to hear you.\n");

    told_mess = "DL: You emote to: " + C(told[i]);

    while (++i < size)
        told_mess += ", " + C(told[i]);

    if (TP->query_get_echo())
        told_mess += ".\nYou DLemote: " + C(TP->query_real_name()) + " " + str;

    TP->catch_msg(told_mess + "\n");
    return 1;
#endif
}


/******************************* Extractlog ****************************
 * some service functions first
 * 
 * Function:	read_log
 * Arguments:	logarea - A part of the path, ie 'pax', 'solace'
 *		logname - The name of the log to scan
 *		logdir  - Put the result files here
 * Description:	Extract all the log text according to a certain area
 *		and put them in a file. It will also save a new version
 *		of the log, with all the extracted text removed.
 */
public void
read_log(string logarea, string logname, string logdir)
{
    int end_file, size_lines, line_nr, start, t, found_area, save, i;
    string t1, t2, file;
    string area_log, new_log, buffer;
    mixed lines;

    area_log = "";
    new_log = "";
    start = 1;
    line_nr = 0;
    end_file = 0;

    if (file_size(logdir) == -1)
      mkdir(logdir);

    while(!end_file)
      {
	  buffer = read_file("/d/" + THIS_DOMAIN + "/log/" + logname, start, LINES);

	  if (!buffer)
	    return;
	    
	  lines = explode(buffer, "\n");
	  size_lines = sizeof(lines);
	  
	  if (size_lines < LINES)
	    end_file = 1;

	  while (line_nr < size_lines)
	    {
		i = sscanf(lines[line_nr], "%s %d %d %s (%s)", t1, t, t, file,t2);
		
		if (i == 5 && sscanf(file, "/d/" + THIS_DOMAIN + "/" + logarea +
				     "/%s", t1) == 1)
		  {
		      area_log += lines[line_nr] + "\n";
		      
		      found_area = 1;
		      
		      while (found_area)
			{
			    if (++line_nr >= LINES)
			      {
				  start += LINES;
				  
				  buffer = read_file("/d/" + THIS_DOMAIN + "/log/"
						     + logname, start, LINES);
				  
				  lines = explode(buffer, "\n");
				  size_lines = sizeof(lines);
				  
				  line_nr = 0;
				  save = 1;
				  
				  if (size_lines < LINES)
				    end_file = 1;
			      }
			    
			    if ((line_nr >= size_lines) && (size_lines < LINES))
			      {
				  write_file(logdir + logname, area_log);
				  write_file(logdir + logname + ".new", new_log);
				  return;
			      }
			    
			    if (sscanf(lines[line_nr], "%s %d %d %s (%s)", t1, t,
				       t, file, t2) != 5)
			      area_log += lines[line_nr] + "\n";
			    else
			      found_area = 0;
			}
		  }
		else
		  {
		      new_log += lines[line_nr] + "\n";
		      line_nr++;
		  }
		
		if (save)
		  {
		      write_file(logdir + logname, area_log);
		      write_file(logdir + logname + ".new", new_log);
		      area_log = "";
		      new_log = "";
		      save = 0;
		  }
	    }
	  
	  write_file(logdir + logname, area_log);
	  write_file(logdir + logname + ".new", new_log);
	  area_log = "";
	  new_log = "";
	  line_nr = 0;
	  start += LINES;
      }
}

/*
 * Function:	move_file
 * Arguments:	oldfile - The name of the old file
 * 		newfile - The name of the new file
 * Description: Move a file from one place to another and if the file
 *		already exists on the new place remove it.
 */
public int
move_file(string oldfile, string newfile)
{
    string buffer;
    int size, i, counter;

    rm(newfile);

    size = file_size(oldfile);

    i = 0;
    counter = 0;

    while (i < size)
    {
	buffer = read_file(oldfile, (counter * 1000) + 1, 1000);
	i += strlen(buffer);
	write_file(newfile, buffer);
	counter++;
    }

    rm(oldfile);
}

public void
do_log(string path, string file, string newpath)
{
    write("Scanning log: '" + file + "' for directory '" + path + "'...");
    read_log(path, file, newpath);
    write("Done.\n");
    move_file(newpath + file + ".new",
	      "/d/" + THIS_DOMAIN + "/log/" + file);
}

/* extractlog
 * Allows to extract the typo, bug, idea and praise log entries of
 * a certain area into this area's log dir.
 * This is useful to keep the general logs tidy and to get all the
 * log entries for your area in one place.
 *
 * Syntax: 'extractlog <pathname> [whichlogs]'
 *         [whichlogs] can be empty (= all logs) or contain any letters
 *          of 'btip', with b = bugs, t = typos, i = ideas, p = praise.
 *     eg. 'extractlog solamn/palan'
 *     eg. 'extractlog pax b'    (b stands for bugs)
 */
int
extractlogs(string str)
{
    int i;
    string path, logs, whichpath, dummy;

    NF("Extract what logs and from where?\n");
    if (!str)
      return 0;
    i = sscanf(str,"%s %s",path,logs);
    if (i == 0)
      {
	  logs = "bpit";
	  path = str;
      }
    else if (i != 2)
      return 0;

    if (!logs)
      logs = "bpit";

    whichpath = "/d/" + THIS_DOMAIN + "/" + path + "/log/";
    if (sscanf(logs,"%sb%s",dummy,dummy) == 2)
      do_log(path,"bugs",whichpath);
    if (sscanf(logs,"%st%s",dummy,dummy) == 2)
      do_log(path,"typos",whichpath);
    if (sscanf(logs,"%si%s",dummy,dummy) == 2)
      do_log(path,"ideas",whichpath);
    if (sscanf(logs,"%sp%s",dummy,dummy) == 2)
      do_log(path,"praise",whichpath);
    
    return 1;
}

public int
do_trust(string str)
{
    string op, who, type;
    
    if (!str || !strlen(str))
    {
	write(WORKROOM->query_trusted());
	return 1;
    }

    if (sscanf(str, "%s %s %s", op, who, type) != 3)
	return notify_fail("Wrong number of args, 'khelp dtrust' for more info.\n");

    if (op == "add")
    {
	if (type == "board")
	{
	    if (!WORKROOM->trust_add_board(who))
	    {
		write(capitalize(who) + " is already trusted.\n");
		return 1;
	    }
	    write(capitalize(who) + " has been added to the board group.\n");
	    return 1;
	}
	else
	    if (type == "line")
	    {
		WORKROOM->trust_add_line_board(who);
		write(capitalize(who) + " has been added to the line group.\n");
		return 1;
	    }
	write("Wrong group kind. Either 'line' or 'board'.\n");
	return 1;
    }
    if (op == "remove")
    {
	if (type == "board")
	{
	    WORKROOM->trust_remove_board(who);
	    write(capitalize(who) + " has been removed from the board group.\n");
	    return 1;
	}
	else
	    if (type == "line")
	    {
		WORKROOM->trust_add_line_board(who);
		write(capitalize(who) + " has been removed from the line group.\n");
		return 1;
	    }
	write("Wrong group kind. Either 'line' or 'board'.\n");
	return 1;
    }
    write("Wrong option given. Either 'add' or 'remove'.\n");
    return 1;
}
