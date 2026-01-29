/* 
 * The Soul of Krynn 
 *   by Lord Rastlin 
 * Version 1.00
 */

/* Inherits */

inherit "/cmd/std/command_driver";

/* Includes */

#include "/sys/filepath.h"
#include "/secure/std.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>

/* Defines */

#define CHECK_SO_WIZ 	if (WIZ_CHECK < WIZ_NORMAL) return 0; \
			if (this_interactive() != this_player()) return 0

#define EXTRA_PATH      "_krynn_ext_path"
#define VER             "V1.00"

/* Prototypes */

string get_file_path(string str);
int my_load(string str);
int my_update(string str);
int my_clone(string str);
int my_goto(string str);

/* The ID of this Soul */
string get_soul_id() {
  return "The Soul of Krynn";
}

/* Soul type */
int
query_tool_soul() { return 1; }

/* The list of functions and verbs */
mapping
query_cmdlist() {

  return ([
    "bomb":	"my_bomb",
    "c":	"my_copy",
    "khelp":	"my_help",
    "lu":	"my_load_update",
    "luc":	"my_load_update_clone",
    "lug":	"my_load_update_goto",
    "path":	"my_set_path",
    "tl":	"my_tail_log"
   ]);
}

/*
 * Function name: get_file_path
 * Description:   Try to get the filepath from the current path, if not ok
 *                try to get it from the extra path, if available
 * Argument:      string: The file name
 * Return:        The filepath (string)
 */
string
get_file_path(string str) {
string curr_path, ext_path, temp, var1, var2;

  if (!strlen(str)) {
    NF("What about a file name?\n");
    return 0;
  }

  curr_path = FTPATH(this_interactive()->query_path(), str);
  ext_path = this_interactive()->query_prop(EXTRA_PATH);

  if (sscanf(str, "%s.%s", var1, var2) != 2) str += ".c";
  if (ext_path) ext_path = FTPATH(ext_path, str);

  if (strlen(curr_path)) 
    if (file_size(curr_path) >= 0) return curr_path;
    else temp = curr_path;

  if (strlen(ext_path))
    if (file_size(ext_path) >= 0) return ext_path;
    else if (!strlen(temp)) temp = ext_path;

  if (!strlen(curr_path) && !strlen(ext_path) && !strlen(temp)) {
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
void
my_load(string str) {

  str->teleledningsanka();
}

/*
 * Function name: my_update
 * Description:   Update an object ... Destruct it..
 * Argument:      string: filepath
 */
void
my_update(string str) {
object obj;

  obj = find_object(str);
  if (obj) obj->remove_object();
}

/*
 * Function name: my_clone
 * Description:   Clone an object and move it.
 * Argument:      string: filepath
 */
void
my_clone(string str) {
object ob;
int num;

  ob = clone_object(str);
  if (!ob) {
    NF("You can not clone: " + str + "\n");
    return 0;
  }
  num = (int)ob->move(environment(this_interactive()));
  if (num) {
    NF("Can't let that object enter this room: " + num + ".\n");
    return 0;
  }
  say(QCTNAME(this_interactive())
    + " fetches something from another dimension.\n");
  num = (int)ob->move(this_interactive());
  switch (num) {
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
my_goto(string str) {
object ob;
string name;

  if (catch(this_interactive()->move_living("X", str))) {
    NF("Invalid file name: " + str + "\n");
    return 0;
  }
}
/*
 * Function name: my_bomb
 * Description:   Destruct all non living objects in a room
 */
int
my_bomb() {
object *obj_arr;
int i, done;

  CHECK_SO_WIZ;

  done = 1;
  i = 0;
  obj_arr = all_inventory(environment(TP));
  while (i < sizeof(obj_arr)) {
    if ((!living(obj_arr[i]) && obj_arr[i] != environment()) || obj_arr[i]->query_npc()) {
      write(obj_arr[i]->query_name() + ": Destructed.\n");
      obj_arr[i]->remove_object();
      done=0;
    }
    i += 1;
  }
  if (done) {
    write("Done.\n");
    say(QCTNAME(TP) + " sends rays of destructions in all directions.\n");
  } 
  else my_bomb();
  return 1;
}  

/*
 * Function name: my_copy
 * Description:   Copy a file from extra path to current dir.
 * Argument:      string: File name and maybe the new name too.
 */
int
my_copy(string str) {
string ext_path, from, to, content;

  CHECK_SO_WIZ;

  if (!strlen(str)) {
    NF("What about a filename?\n");
    return 0;
  }
  if (!(ext_path = this_interactive()->query_prop(EXTRA_PATH))) {
    NF("You need to set the extra path first.\n");
    return 0;
  }
  if (sscanf(str, "%s %s", from, to) == 2) {
    from = FTPATH(ext_path, from);
    to = FTPATH(this_interactive()->query_path(), to);
  }
  else {
    from = FTPATH(ext_path, str);
    to = FTPATH(this_interactive()->query_path(), str);
  }
  content = read_file(from);
  if (content == 0) {
    NF("Failed to read contents of " + from + ".\n");
    return 0;
  }
  /* write_file() will append */
  if (file_size(to) != -1 && !rm(to)) {
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
my_help(string str) {

  CHECK_SO_WIZ;

  if (!strlen(str)) {
    write("The Soul of Krynn " + VER + " was coded by Lord Rastlin - 1992\n"
      + "--------------------------------------------------------\n"
      + "The idea with this soul is that it should make the life\n"
      + "much more easier.\n"
      + "If you want help with any of the commands, type: khelp <command>\n");
    return 1;
  }
  switch(str) {
    case "bomb":
      write("Destruct ALL non living objects in the room.\n"
        + "Should be used with care, since invisible objects\n"
        + "can be destructed too.\n");
      break;

    case "c":
      write("A copy command.\n"
        + "c <filename> [newname]\n"
        + "It will copy a file from the extra path (set with the\n"
        + "path command) to the current dir. But it also works as\n"
        + "a normal cp command.\n"
        + "Examples:\n"
        + "  c apa.c            Copy from extra path to current dir.\n"
        + "  c apa.c bepa.c     Same as above but change the name.\n"
        + "  c misc/apa.c       Copy from extra path + /misc to current dir.\n"
        + "  c apa.c ~/bepa.c   Copy from extra path to your home dir.\n"
        + "  c ~/apa.c bepa.c   Copy from your homedir to current dir.\n");
      break;

    case "lu":
      write("Load and Update in one command.\n"
        + "lu <file>\n"
        + BS("As a normal load and update, but with "
        + "a small feature. If it can't find the file in the current dir, "
        + "then it will look in the extra path (set with the path command). "
        + "This means that you can load and update a file in another dir, "
        + "without giveing the path every time.",70));
      break;

    case "luc":
      write("Load, Update and Clone in one command.\n"
        + "luc <file>\n"
        + BS("As a normal load, update and clone, but with a small feature. "
        + "If it can't find the file in the current dir then it will look in "
        + "the extra path (set with the path command). This means that you "
        + "can load, update and clone a file in another dir, without giveing "
        + "the path every time.",70));
      break;

    case "lug":
      write("Load, Update and Goto in one command.\n"
        + "lug <file>\n"
        + BS("As a normal load, update and goto, but with a small feature. "
        + "If it can't find the file in the current dir then it will look in "
        + "the extra path (set with the path command). This means that you "
        + "can load, update and goto a file in another dir, without giveing "
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
        + "do luc <monster> without giveing any paths. Easy??",70));
      break;

    case "tl":
      write("This is a short version of tail /lplog.\n");
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
my_load_update(string str) {
string file;

  CHECK_SO_WIZ;

  if (!(file = get_file_path(str))) return 1;
  write("File: " + file + "\n");
  write("Updating...");
  my_update(file);
  write("Success.\n");
  write("Loading....");
  my_load(file);
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
my_load_update_clone(string str) {
string file;

  CHECK_SO_WIZ;

  if (!(file = get_file_path(str))) return 1;
  write("File: " + file + "\n");
  write("Updating...");
  my_update(file);
  write("Success.\n");
  write("Loading....");
  my_load(file);
  write("Success.\n");
  write("Cloneing...");
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
my_load_update_goto(string str) {
string file;

  CHECK_SO_WIZ;

  if (!(file = get_file_path(str))) return 1;
  write("File: " + file + "\n");
  write("Updating...");
  my_update(file);
  write("Success.\n");
  write("Loading....");
  my_load(file);
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
my_set_path(string str) {
string path;

  CHECK_SO_WIZ;

  if (!strlen(str)) {
    if ((path = this_interactive()->query_prop(EXTRA_PATH))) {
      write("Extra path: " + path + "\n");
      return 1;
    }
    else {
      write("No extra path set yet.\n");
      return 1;
    }
  }
  path = FTPATH(this_interactive()->query_path(), str);
  if (!strlen(path)) {
    NF("Bad pathname format: " + str + "\n");
    return 0;
  }
  if (file_size(path) != -2) {
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
my_tail_log() {

  CHECK_SO_WIZ;

  tail("/lplog");
  return 1;
}




