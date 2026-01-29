/* The graveyard standard room, defines the look at grave functions
 *
 * //Nick & Dorak
 */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>

inherit OUTSIDE_BASE;

string
graves()
{
    string filename, *names, str;
    int j;
    
    seteuid(getuid(this_object()));
    filename = GRAVE_LOG + "rooms/room" + TO->query_grave_room();
    if (file_size(filename) > 0)
      {
	  str = read_file(filename);
	  names = explode(str, " ") - ({ "" });
	  j = sizeof(names);
	  if (j < 1)
            return "The graves are all empty, yet to be filled.\n";
	  if (j == 1)
            str = names[0];
	  else
            str = implode(names[0 .. j - 2], ", ") + " and " + names[j - 1];
	  write("You look at the graves and read the names on them:\n");
	  write(break_string(str + ".\n", 70));
	  write("There is text written on each grave which you can read.\n");
	  return "";
      }
    return "You can't make out anything about the graves.\n";
}

mixed
grave_look()
{
    string filename, *names, str, str_name;
    int i;
    
    seteuid(getuid(this_object()));
    str = query_item_rest_command();
    if (!str)
      return "You must tell me what grave you want to read on.\n";
    if ((sscanf(lower_case(str), "grave of %s", str_name) != 1) &&
	(sscanf(lower_case(str), "of %s", str_name) != 1))
      return "'read on grave of <who>' is the right syntax.\n";
    
    filename = GRAVE_LOG + "rooms/room" + TO->query_grave_room();
    if (file_size(filename) < 0)
      return "You can't make out the names on the graves.\n";
    str = read_file(filename);
    names = explode(str, " ");
    str_name = capitalize(str_name);
    if (member_array(str_name, names) >= 0)
      {
	  filename = GRAVE_LOG + extract(str_name, 0, 0) + "/" + str_name;
	  write("You read:\n");
	  cat(filename);
	  return 1;
      }
    
    return "There is no such being buried here.\n";
}

string
graveyard()
{
    write("This is part of the Solace graveyard.\n");
    say(QCTNAME(TP) + " looks all around.\n");
    return "";
}

int
query_grave_room() 
{ 
    return -1; 
}

