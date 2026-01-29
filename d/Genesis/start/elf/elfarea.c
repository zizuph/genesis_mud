
#include "stddefs.h"
#include "/config/sys/map_defines.h"

#pragma save_binary

inherit STRINGLIB;
inherit MISCLIB;


mapping hidden_items;
mapping directions;


// Whilst I like the idea of area-specific report commands, the area covered by
//  this file now consists only of a single room, and the single-line commands
//  are unlike the standard report commands. So I'm disabling them.
//  Lavellan, 2011/02/23      (Last modified 1995/11/16)

init()
{
/*  add_action("my_bug_log", "bug");
  add_action("my_bug_log", "praise");
  add_action("my_bug_log", "idea");
  add_action("my_bug_log", "typo");*/
}

int my_bug_log(string str)
{
  string logfile;

  logfile = 0;

  logfile = LOGDIR + query_verb();

  if (query_verb() == "praise" &&
      lower_case(str) == "nob nar") {
    write("The 'praise' command is intended for telling the local wizard\n"+
	  "what you like in his/her/its area. It is *not* polite to fill\n" +
	  "his/her/its log files with *junk*. Beware, other wizards may be\n"+
	  "even more irritated than I am.\n");
    return 1;
  }

  seteuid(getuid(this_object()));

  if (str) {
    write_file(logfile,
	       extract(ctime(time()), 4, 9) + " " +
	       file_name(environment(this_player())) +
	       " (" + capitalize((string) this_player()->query_real_name()) +
	       ")\n" + str + "\n");
    notify(MAINTAINER,
	   query_verb() + " ("+
	   capitalize(this_player()->query_real_name()) + "):\n" +
	   "**   "+ str);
    write(WRAP("Your comment has been noted and sent to the maintainer of the "+
	       "elf area. Thank you, all feedback is appreciated.\n"));
    return 1;
  }
}


do_log(string file, string str)
{
  string logfile;

  logfile = 0;

  logfile = LOGDIR + file;

  seteuid(getuid(this_object()));

  write_file(logfile,
	     extract(ctime(time()), 4, 9) + " " +
	     file_name(this_object()) + " " + 
	     str + "\n");
}

string native_knowledge(string native, string foreign) 
{
  if (this_player() && IS_NATIVE(this_player()))
    return native;
  else
    return foreign;
}

status hidden_item_present(string obj_id)
{
  return (hidden_items && 
	  hidden_items[obj_id] && 
	  hidden_items[obj_id][0] > 0);
}

string hidden_item_desc(string obj_id, string present_desc, string absent_desc)
{
  return (hidden_item_present(obj_id) ?
	  present_desc: absent_desc);
}

void restock_hidden_item(string objfile, int min_obj_num, string obj_id)
{
  if (! hidden_items)
    hidden_items = ([ ]);

  hidden_items[obj_id] = ({ min_obj_num, objfile });
}

string get_hidden_item(string obj_id, string succ_message, string fail_message)
{
  object obj;
  string str;

  if (! hidden_item_present(obj_id)) {
    notify_fail(fail_message);
    return 0;
  }

  do_log("hidden", 
	 capitalize(this_player()->query_real_name()) + 
	 " managed to find the " + obj_id + ".");

  seteuid(getuid(this_object()));

  if ((str = catch(obj = clone_object(hidden_items[obj_id][1]))) != 0)
    notify(MAINTAINER, "*\n*" + hidden_items[obj_id][1] + "\n" + str + "*\n");
  else
    if(obj != 0)
      switch (obj->move(this_player())) {
      case 0:
	hidden_items[obj_id][0]--;
	return succ_message;
      case 1:
	return "That would make your pack far to heavy for you.\n";
      case 8:
	return "It's too big.\n";
      default:
	return "You fail to grip it.\n";
      }
} 


/*
 * void restock_object(string objfile, int min_obj_num, string obj_id);
 *
 * If there is less than <min_obj_num> objects responding to
 * <obj_id> in the inventory, then clone more from <objfile>.
 */

void restock_object(string objfile, int min_obj_num, string obj_id)
{
  object *inv;
  object obj;
  string str;
  int i, num;


  seteuid(getuid(this_object()));
  
  inv = all_inventory(this_object());
  num = 0;
  for (i = 0; i < sizeof(inv); i++)
    if (inv[i] && inv[i]->id(obj_id))
      num++;
  
  for (i = num; i < min_obj_num; i++) {
    if ((str = catch(obj = clone_object(objfile))) != 0)
      notify(MAINTAINER, "*\n*" + objfile + "\n" + str + "*\n");
    else
      obj->move(this_object());
  }
}

int block_exit_temporarily()
{
  write("Unfortunately, due to a sudden shortage of substance in the web\n" +
	"of reality, you're prevented from using that destination. Please\n" +
        "try again at a later date.\n");

  return 1;
}


/*
 * Automatic linkage to the map.
 */


string new_coordinate(int global, int local, int delta)
{
  local += delta;

  if (local < 0)           return "" + (global - 1) + "." + MAP_SL_MAX;
  if (local > MAP_SL_MAX)  return "" + (global + 1) + ".0";
    
  return "" + global + "." + local;
}
	

void tie_to_map(string maparea, int x, int sub_x, int y, int sub_y)
{
  string dir, *dirs, *exits, *exception;
  int i;
  string dx, dy;
  string center, dest;
  object area;

#if USE_MAP

  if (!directions)
    directions = DIRECTIONS;

  dirs   = m_indexes(directions);
  exits  = this_object()->query_exit_cmds();

  for (i = 0; i <sizeof(dirs); i++) {
    dir = dirs[i];
    if (member_array(dir, exits) < 0) {
      dx = new_coordinate(x, sub_x, directions[dir][0]);
      dy = new_coordinate(y, sub_y, directions[dir][1]); 
      dest = ("x" + dx + "y" + dy);
      this_object()->add_exit("@@map_file|"+dest + "@@", dir, 0);
    }
  }
  
  this_object()->set_noshow_obvious(1);

#endif
}