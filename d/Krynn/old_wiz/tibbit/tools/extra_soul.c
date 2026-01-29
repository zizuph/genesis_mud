#include "/sys/macros.h"
#include <const.h>


inherit "/cmd/std/command_driver";
inherit "/d/Krynn/tibbit/tools/objlib";


#define EIGHTY_SPACES \
"                                                                                "

#define RJUST(STR, NUM) extract(EIGHTY_SPACES + STR, 80 + strlen(STR) - NUM)
#define LJUST(STR, NUM) extract(STR + EIGHTY_SPACES, 0, NUM-1)
#define SPACE(NUM)      extract(EIGHTY_SPACES, 0, NUM-1)

#define PLAYERENV environment(this_interactive())

#define ERRFILE (home() + "/log/errors")
#define NOTIFY_USAGE notify_fail("usage:\n" + helplist[query_verb()])

#define MAX_SHOWN_ARRAYLINES 10
#define BOARDFILE "/d/Wiz/caution/open/boardlist"
#define BOARDCENTRAL "/std/board/board_central"
/*
 * Config:
 */

mapping boardrooms;
mapping boarddirs;
mapping boardages;
mapping helplist;
mapping stock;
mapping player_toggles;

#define OBJSPEC \
  "(See 'soulhelp objects' for the format of <objects>.)\n"


create()
{
  helplist = ([
    "bbs":
	   "bbs\n" +
           "  list avaliable boards.\n" +
	   "bbs age\n" +
           "  list availiable boards, sorted by the age of their last note.\n"+
           "bbs <label>\n" +
           "  examine the given board.\n" +
           "bbs trans <label>\n" +
           "  move you to the given board.\n" +
           "bbs <label> <number>\n" +
           "  read note <number> from the given board.\n",
    "compile":
	   "compile <objects>\n" +
	   "  destructs all objects mentioned in <objects>, updates\n" +
	   "  their master objects, deletes the old log file, and prints\n" +
	   "  the new log file if there was any errors.\n\n" +
	   OBJSPEC,
    "cc":
	   "cc <objects>\n" +
           "  see 'compile'\n",
    "errors":
           "errors {<num>}" +
           "  shows not only the errors in the error log, but also the\n" +
           "  source line with the error. It will show <num> lines\n" +
	   "  before and after the line with the error. Default, if no\n" +
           "  number is given, is no extra lines.\n",
    "grep":
           "grep <string>\n" +
           "  searches for <string> in all files in the current directory\n",
    "inv":
	   "inv {<objects>}\n" +
           "  shows the inventory of listed objects. If no argument, shows\n" +
	   "  your inventory.\n\n" +
	   OBJSPEC,
    "I":
           "I <objects>\n" +
           "  see 'inv'\n",
    "items":
           "items\n" +
           "  lists all items in your environment.\n",
    "set":
           "set\n" +
           "  list possible settings.\n" + 
           "set <setting>\n"+
           "  sets the indicated setting in you.\n" +
           "set <setting> in <living>\n" +
           "  sets the indicated setting in the living object.\n\n" +
           "  The setting are such things as invisible/visible, sex, etc.\n",
    "stock":
	   "stock\n" +
           "  list what common objects are available.\n" +
	   "stock <name>\n" +
           "  clones an object from a list of common object and moves\n" +
	   "  it to you.\n",
    "which":
           "which <functionname> {in} <objects>\n"+
           "  tells wich source file that defines the function \n" +
           "  <functionname> for each object in <objects>\n\n" +
           OBJSPEC,
    "objects":
           "Objects may be specified on the format:\n"+
           "    <object>   or    <env>:<object>\n\n"+
	   "Matching objects will be found by these rules:\n"+
           "(If no <env> is specified, your environment will be used)\n"+
	   "  1) all objects in <env> with id(<object>) != 0\n"+
           "  2) all objects in <env> with filename == <object>\n"+
           "  3) all objects in <env> with master's filename == <object>\n"+
           "  4) the object with filename == <object>\n"+
           "  5) first found living with name == <object>\n"+
           "  6) yourself, if <object> == 'me'\n"+
	   "  7) your enviroment, if <object> == 'here'\n"+
           "when a match is made against a filename, the <object> string\n"+
           "will be expanded into a file path, using '~/', '~wizard/' and\n"+
           "current working directory in the normal way.\n\n"+
           "Environments may be specified recursively:\n"+
           "  <env>:<env>:<object>\n"+
           "and will be found according to these rules:\n"+
           "  1) first object in <previous env> with id(<env>) != 0\n"+
           "+ rule 4-7 above\n",
    "soulhelp":
           "soulhelp\n" +
	   "  lists availiable subjects.\n" +
	   "soulhelp <subject>\n" +
           "  gives help on <subject>.\n"
  ]);
  stock =([
    "mailreader":
	   "/d/Genesis/postmaster/mail_reader",
    "money-maker":
           "/d/Wiz/caution/open/money_maker.c",
  ]);
  player_toggles = ([
    "people known":
	       ({"this_player()", "set_wiz_unmet", 0}),
    "people unknown":
               ({"this_player()", "set_wiz_unmet", 1}),
    "race name elf":
	       ({"this_player()", "set_race_name", "elf"}),
    "race name human":
	       ({"this_player()", "set_race_name", "human"}),
    "gender male":
	       ({"this_player()", "set_gender", G_MALE}),
    "gender female":
	       ({"this_player()", "set_gender", G_FEMALE}),
    "gender neuter":
	       ({"this_player()", "set_gender", G_NEUTER}),
              
  ]);

  load_boards();
}

  
		
/*
 * Standard lfuns:
 */

int query_tool_soul() { return 1; }
int query_cmd_soul()  { return 0; }
string get_soul_id()  { return "caution"; }

mapping query_cmdlist()
{
  return ([
    "bbs":     "do_board",
    "call":    "do_call",
    "cc":      "do_compile",
    "compile": "do_compile",
    "errors":  "do_errors",
    "grep":    "do_grep",
    "inv":     "do_inventory",
    "I":       "do_inventory",
    "items":   "do_items",
    "set":     "do_set",
    "stock":   "do_stock",
    "which":   "do_which",
    "soulhelp":"do_help"
  ]);
}

/*
 * generic aid:
 */



static mixed *list_tail(mixed *a, int start)
{
  int i;
  mixed *val;

  val = ({});
  for (i = start; i < sizeof(a); i++)
    val += ({ a[i] });

  return val;
}

static int longest_strlen(string *a)
{
  int i;
  int max;

  if (!a)
    return 0;

  max = 0;
  for (i = 0; i <sizeof(a); i++)
    if (strlen(a[i]) > max)
      max = strlen(a[i]);

  return max;
}

static string column_order(string *a, int max_width)
{
  int col_num, row_num, str_num;
  int col_width;
  int i, j, k;
  string ret;

  if (!a) return 0;
  if ((str_num = sizeof(a)) < 1) return "\n";

  col_num = 79 / max_width;
  row_num = (str_num - 1) / col_num + 1;   /* str_num / col_num rounded *up* */

  if (col_num < 1) 
    col_num = 1;

  col_width = 79/col_num;
  ret = "";

  for (i = 0; i < row_num; i++) {
    for (j = 0; j < col_num; j++) {
      if ((k = i + j * row_num) < str_num)
	ret += LJUST(a[k], col_width);
    }
    ret += "\n";
  }

  return ret;
}

string *explode_words(string str)
{
  string *strs, *res, tmp;
  int i;

  res = ({ });

  if (sscanf(str, "%s\n", tmp)) 
    str = tmp;

  strs = explode(str + " ", " ");
  for(i = 0; i < sizeof(strs); i++)
    if (strs[i] != "")
      res += ({strs[i]});
  return res;
}


load_boards()
{
  int i;
  string line, name, room, savedir;
  string *strs;

  boardrooms = ([]);
  boarddirs  = ([]);

  seteuid(getuid());

  for (i = 0; (line = read_file(BOARDFILE, i, 1)) != 0; i++) {
    if (line != "\n" && line[0] != '#') {
      strs = explode_words(line);

      if (sizeof(strs) > 1) 	boardrooms[strs[0]] = strs[1];
      if (sizeof(strs) > 2) 	boarddirs[ strs[0]] = strs[2];

    }
  }
}
  
/*
 * Commands:
 */

do_help(string arg)
{
  mixed *helpstrings;
  int len;
  mixed helpstring;
    
  if (!arg) {
    write("help is available on these subjects:\n");
    helpstrings = sort_array(m_indexes(helplist));
    len = longest_strlen(helpstrings) + 5;
    write(column_order(helpstrings, len));
    return 1;
  } else if ((helpstring = helplist[arg]) != 0) {
    write (helpstring);
    return 1;
  }

  notify_fail("type 'soulhelp' for a list of availiable topics.\n");
  return 0;
}


static object find_board(string name, status do_load) 
{
  string location;
  object board;
  object where, origin;

  if ((location = boardrooms[name]) == 0) {
    notify_fail("Never heard about board " + name + "!\n");
    return 0;
  }
  
  LOAD_ERR(location);
  if ((where = find_object(location)) == 0) {
    notify_fail("No location " + location + "!\n");
    return 0;
  }

  if ((board = present("board", where)) == 0) {
    notify_fail("No board in " + location + "!\n");
    return 0;
  }
  
  /* silly little excursion just to make the board load its articles */

  if (do_load) {
    origin = environment(this_interactive());
    this_interactive()->move(where);
    this_interactive()->move(origin);
  }
  return board;
}

static int trans_board(object board) 
{
  object location;
  
  if ((location = environment(board)) != 0) {
    write("You are visibly moved.\n\n");
    this_interactive()->move_living("X", location);
    return 1;
  }
  notify_fail("Weird. I thought I knew where that room was...\n");

  return 0;
}

static int show_board(object board) 
{
  string str;

  if ((str = board->long()) != 0) {
    write(board->long());
    return 1;
  }
}

static int read_board(object board, string msg) 
{
  return board->read_msg(msg);
}

static int list_boards()
{
  mixed *boards;
  int len;

  boards = sort_array(m_indexes(boardrooms));
  len = longest_strlen(boards) + 10;
  write(column_order(boards, len));
  
  return 1;
}

static int board_time(string name)
{
  object board;
  string notename;
  int timeint;
  
  notename = 0;

  if ((board    = find_board(name, 0)) != 0)
    notename = board->query_latest_note(0);

  if (notename == 0 && boarddirs[name] != 0)
    notename = BOARDCENTRAL->query_board(boarddirs[name]);

  if (notename != 0 &&
      sscanf(notename, "b%d", timeint) > 0 &&
      timeint > 0)
    return timeint;
  else
    return 0;
}

status compare_boardages(string a, string b)
{
  return (boardages[a] - boardages[b]);
}

static int list_boards_with_age()
{
  mixed *boards;
  mapping result;
  int i, timeint, len;
  string timestr;
  string *printout;

  boards = m_indexes(boardrooms);
  boardages = ([ ]);
  result = ([ ]);
  printout = ({});

  for (i = 0; i < sizeof(boards); i++) {
    
    if ((timeint = board_time(boards[i])) > 0) 
      timestr = extract(ctime(timeint), 4, 15);
    else
      timestr = "-not loaded-";
    boardages[  boards[i]] = timeint;
    result[boards[i]] = "    " + timestr + "  " + boards[i];
  }
  
  boards = sort_array(m_indexes(boardages), 
		      "compare_boardages", 
		      this_object());
  
  for (i = 0; i < sizeof(boards); i++) {
    printout += ({ result[boards[i]] });
  }
  len = longest_strlen(printout) + 5;
  write(column_order(printout, len));

  return 1;
}

int do_board(string arg)
{
  string str;
  string a, b;
  object board;

  if (!arg || arg == "")                       return list_boards();
  if (arg == "age")			       return list_boards_with_age();
  if (sscanf(arg, "trans %s", a) &&
      (board = find_board(a, 1)) !=0)          return trans_board(board);
  if (sscanf(arg, "%s %s", a, b) &&
      (board = find_board(a, 1)) !=0)          return read_board(board, b);
  else if ((board = find_board(arg, 1)) != 0)  return show_board(board);
}


static int list_stock()
{
  mixed *names;
  int len;

  names = sort_array(m_indexes(stock));
  len = longest_strlen(names) + 5;
  write("Objects in stock:\n" +
	"-----------------\n\n" +
	column_order(names, len));
  
  return 1;
}

int do_stock(string arg)
{
  if (!arg || arg == "")     return list_stock();
  else if (stock[arg])       return make_object(stock[arg]);
  else {
    NOTIFY_USAGE;
    return 0;
  }
}

static int list_set()
{
  mixed *names;
  int len;

  names = sort_array(m_indexes(player_toggles));
  len = longest_strlen(names) + 5;
  write("Flags to set:\n" +
	"-------------\n\n" +
	column_order(names, len));
  
  return 1;
}


mixed set_subst(mixed arg, object player)
{
  if (stringp(arg) && arg == "this_player()")     return player;

  return arg;
}


int do_set(string arg)
{
  mixed *func;
  string what, who;
  object person;
  int i;

  if (!arg || arg == "") 
    return list_set();

  if (((func   = player_toggles[arg]) != 0 &&
       (person = this_player()) != 0) ||
      (sscanf(arg, "%s in %s", what, who) == 2 &&
       (person = find_living(who))        != 0 &&
       (func   = player_toggles[what])    != 0)) {

    call_other(set_subst(func[0], person), 
	       func[1], 
	       set_subst(func[2], person));
    return 1;
  }

  NOTIFY_USAGE;
  return 0;
}



static update_object(string mastername)
{
  object master;

  if ((master = find_object(mastername)) != 0) {
    master->remove_object();
    if (!master) {
      write ("- destructed softly.\n");
    } else {
      "/secure/master"->do_debug("destroy", master);
      write ("- destruct hard.\n");
    }
  }
  catch(call_other(mastername, "???"));
  if (! find_object(mastername)) {
    write ("*** Error in " + mastername + ".\n");
    return 1;
  }
 
  write("Updated master object " + mastername + ".\n");
  return 0;
}


do_compile(arg)
{
  object *objs, master;
  int i, errors;
  string mastername, *updated_masters;

  updated_masters = ({});

  if (arg &&
      (objs = locate_objs_or_files(arg, 0)) != 0 &&
      sizeof(objs) > 0) {

    write("Deleting log file.\n");
    rm(ERRFILE);

    for (i = 0; i < sizeof(objs); i++) {

      if (stringp(objs[i]))
	mastername = objs[i];
      else
	mastername = MASTER_OB(objs[i]);

      if (member_array(mastername, updated_masters) < 0) {

	errors += update_object(mastername);
	updated_masters += ({ mastername });
      }
    }

  } else {
    NOTIFY_USAGE;
    return 0;
  }
    
  if (errors > 0) {
    write("*** ERRORS ***\n");
    cat(ERRFILE);
  }
  return 1;
}



show_inventory(object obj)
{
  object *inv;
  int i;

  if (!obj)
    return 0;

  if ((inv = all_inventory(obj)) == 0)
    return 0;

  write ("Inventory of ");
  if (obj->short())
    write(obj->short());
  write(" ("+file_name(obj)+"):\n");
  for (i = 0; i < sizeof(inv); i++) {
    if (inv[i]->short())
      write(LJUST(inv[i]->short(), 30));
    else 
      write(LJUST("   ---", 30));
    write(LJUST("("+file_name(inv[i])+")", 45) + "\n");
  }
}

do_inventory(arg)
{
  object *objs;
  int i, error;
  string filename, tmp;

  if (!arg) {
    show_inventory(this_interactive());
  
  } else if ((objs = locate_objects(arg, 0)) != 0 &&
	     sizeof(objs) > 0) {
    for (i = 0; i < sizeof(objs); i++) {
      show_inventory(objs[i]);
    }
  } else {
    NOTIFY_USAGE;
    return 0;
  }
  return 1;
}


show_which(string thefunction, object obj)
{
  string str;

  if (!obj || !thefunction)
    return;

  write(LJUST(file_name(obj) + ":", 35));
  if ((str = function_exists(thefunction, obj)) != 0)
    write(LJUST(str + ".c", 37));
  write("\n");
}

show_whichheader(string thefunction)
{
  if (!thefunction) 
    return;
  write(LJUST("In object:", 35));
  write(LJUST("'" + thefunction + "()' is defined by:", 37));
  write("\n------------------------------------------" + 
	"-------------------------------\n");
}


do_which(arg)
{
  string arg1, arg2;
  object *objs;
  int i;

  if (!arg || ! (sscanf(arg, "%s in %s", arg1, arg2) == 2 ||
		 sscanf(arg, "%s %s",    arg1, arg2) == 2)) {
    NOTIFY_USAGE; 
    return 0;
  }

  if ((objs = locate_objs_load_files(arg2, 0)) != 0 &&
      sizeof(objs) > 0) {
    show_whichheader(arg1);
    for (i = 0; i < sizeof(objs); i++) {
      show_which(arg1, objs[i]);
    }
  } else {
    NOTIFY_USAGE;
    return 0;
  }
  
  return 1;
}


static mixed parse_args(string str)
{
  if (!str)
    return ({});

  write ("Cannot handle arguments yet.\n");
  return 0;
}

static string del_ctrl(string str)
{
  switch(str) {
  case "\"":  return "\\\"";
  case "\n":  return "\\n";
  case "\t":  return "\\t";
  default:    return str;
  }
}

static string strval(string val)
{
  return "\"" + implode(map(explode(val, ""), 
				  "del_ctrl", 
				  this_object()), 
			"") + "\"";
}


static string val_to_string(mixed val, int indent);


static string pointerval(mixed *ptr, int indent)
{
  int i, s;
  string ret;

  if (! ptr) 
    return "NULL";

  s = sizeof(ptr); 
  ret = "array [" + s + "]";

  if (s > 0) {

    if (s > MAX_SHOWN_ARRAYLINES)
      s = MAX_SHOWN_ARRAYLINES;
    indent += 2;
    ret += " =\n{\n";
    for (i = 0; i < s; i++)
      ret += (SPACE(indent) + 
	      "[" + i + "]: " + 
	      val_to_string(ptr[i], indent) + "\n");

    ret += "}";
  }
  return ret;
}

static string objectval(object val)
{
  if (val->query_real_name())
    return val->query_real_name();
  else
    return file_name(val);
}

static string val_to_string(mixed val, int indent)
{
  if (intp(val))     return ""+val;
  if (stringp(val))  return strval(val);
  if (objectp(val))  return objectval(val);
  if (pointerp(val)) return pointerval(val, indent);

  return "<unsupported type>";
}


void call_func(object obj, string funcname, mixed *args)
{
  mixed ret;

  if (!obj || !funcname || !args)
    return;

  ret = 0;
  
  switch(sizeof(args)) {
  case 0:
    ret = call_other(obj, funcname);    break;
  default:
    write ("Too many arguments error.\n");
  }

  write(objectval(obj) + " returned " + val_to_string(ret, 0) + "\n");
}


do_call(arg)
{
  string objspec, funcname, argspec;
  object *objs;
  mixed *args;
  int i;
  
  argspec = (string)0;
  if (!arg || ! (sscanf(arg, "%s %s %s", objspec, funcname, argspec) == 3 ||
		 sscanf(arg, "%s %s",    objspec, funcname)          == 2)) {
    NOTIFY_USAGE; 
    write ("  1\n");
    return 0;
  }

  if ((objs = locate_objs_load_files(objspec, 0)) != 0 &&
      sizeof(objs) > 0 &&
      (args = parse_args(argspec)) != 0) {

    for (i = 0; i < sizeof(objs); i++) {
      call_func(objs[i], funcname, args);
    }

  } else {
    NOTIFY_USAGE;
    if (objs != 0)
      write ("Objs exist, with size: " + sizeof(objs) + ".\n");
    if (args != 0)
      write ("Args exist, with size: " + sizeof(args) + ".\n");

    write ("  2\n");
    return 0;
  }
  
  return 1;
}


void grep_file(string str, string filename)
{
  int i;
  string a, b;
  string line;

  for (i = 1; (line = read_file(filename, i, 1)) != 0 ; i++) {
    if (sscanf(" " + line + " ", "%s" + str + "%s", a, b) == 2)
      write (filename + ":" + i + ": " + line);
  }
}

  
void grep_dir(string str, string dirname)
{
  string *dir;
  int i;

  write ("looking for '" + str + "' in '" + dirname + "'.\n");

  if ((dir = get_dir(dirname + "/*")) != 0 && sizeof(dir) > 0) {
    for (i = 0; i <sizeof(dir); i++) {
      grep_file(str, dirname + "/" + dir[i]);
    }
  } else 
    write("Found no files in '" + dirname+ "'\n");
}

  
int do_grep(string arg)
{
  if (!arg) {
    NOTIFY_USAGE;
    return 0;
  }

  grep_dir(arg, pwd());
  return 1;
}


int do_errors(string arg)
{
  int i, j;
  string errorline;
  string srcline, srcfile, error;
  int    srclinenum, margin;

  if (!arg) {
    margin = 0;
  } else if (sscanf(arg, "%d", margin) < 1) {
    NOTIFY_USAGE;
    return 0;
  }

  for (i = 1; (errorline = read_file(ERRFILE, i, 1)) != 0; i++) {
    write(errorline);
    if (sscanf(errorline, "%s line %d:%s", srcfile, srclinenum, error) == 3) {
      for (j = (srclinenum <= margin) ? 1 : srclinenum - margin;
	   j <= srclinenum + margin;
	   j++) {
	srcline = read_file("/"+srcfile, j, 1);
	if (!srcline)
	  break;
	if (j == srclinenum)
	  write ("*** ");
	else 
	  write ("    ");
	write (srcline);
      }
    }
  }
  return 1;
}    


string list_items(object obj)
{
  mixed itemlist;
  int i, len;
  string *item_strs;

  if (!obj || (itemlist = obj->query_item()) == 0)
    return "";

  item_strs = ({});
  for (i = 0; i < sizeof(itemlist); i++)
    item_strs += itemlist[i][0];
  
  if (!sizeof(item_strs))
    return "";

  len = longest_strlen(item_strs);
  return column_order(sort_array(item_strs), len + 3);
}

do_items(arg)
{
  object obj;

  if (!arg) {
    obj = PLAYERENV;
    write("Items:\n" +
	  "------\n" +
	  list_items(obj));
    return 1;
  } else {
    NOTIFY_USAGE;
    return 0;
  }
}

