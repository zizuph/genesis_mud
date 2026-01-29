#include "../../ctower.h"

inherit FINSTD;

#include <macros.h>
 
int curtain;

void add_curtain(int add)
{
    curtain = add;
  
    if (add)
    {
    	add_item(({ "curtain", "prismatic curtain" }),
	    "The curtain is soft yet unyielding.\n");
    	remove_exit("north");
    	return;
    }
  
    add_exit(CTOWER_ROOM_FIN + "mirror", "north");
    remove_item("curtain");
}

void
ctower_reset()
{
    add_curtain(1);
}

void
create_fin()
{
    set_long(query_long() + "@@curtain_desc@@");
    add_exit(CTOWER_ROOM_FIN + "fin5", "south");
  
    ctower_reset();
}

string curtain_desc()
{
    if (curtain) 
    {
      return "A strange, prismatic curtain hangs across the hallway " + 
	  "to the north.\n";
    }
  
    return "";
}

/* 
int
query_exit_state()
{
  return exits_installed;
}
*/
 
void
set_exit_state(int state)
{
    if (curtain)
    {
    	tell_room(this_object(),  "The prismatic curtain is absorbed into "+
	    "the star sapphire.\n");
    	add_curtain(0);
    	return;
    }
  
    tell_room(this_object(), "The star sapphire glows brighter "+
	"and brighter then slowly dims.  When you can see "+
	"again, the prismatic curtain is back.\n");
    add_curtain(1);
}
 
string
query_open_gem()
{
    return "star sapphire";
}
 
string
query_close_gem()
{
    return "star sapphire";
}
 
int
do_nothing(string arg)
{
    if (strlen(arg) && 
        parse_command(arg, ({}), "[the] [prismatic] curtain"))
    {
      notify_fail("You cannot move the curtain!\n");
    }
  
    return 0;
}

void
init()
{
    ::init();
    add_action(do_nothing, "push");
    add_action(do_nothing, "enter");
    add_action(do_nothing, "open");
}
 
