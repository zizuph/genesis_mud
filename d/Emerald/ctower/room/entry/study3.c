inherit "/d/Emerald/ctower/room/entry/study_room";
 
#include <macros.h>
 
void
create_study_room()
{
    set_long(query_long() + "@@passage_desc@@");
    add_exit("hall4", "south");
}

string passage_desc()
{
  return (member_array("passage", query_exit_cmds()) >= 0 ?
      "The fireplace has been pushed aside, revealing a " +
      "hidden passage.\n" : "");
}
   
void close_fireplace()
{
    tell_room(this_object(), "The fireplace quietly moves back into " +
        "place.\n");
    remove_exit("passage");
}

int
push(string str)
{
    string action;

    if (query_verb() == "pull")
    {  
        return ::push(str);
    }

    if (str != "prism" && str != "the prism")
    {
        return 0;
    }
   
    if (member_array("passage", query_exit_cmds()) >= 0)
    {
    	action = " does something to the fireplace.\n";
    	write("You push the prism.\n");
    	close_fireplace();
    }
    else
    {
    	action = " does something to the fireplace which quietly moves "+
	    "aside, revealing a hidden passage";
    	write("You push the prism and the fireplace quietly moves "+
	    "aside, revealing a hidden passage.\n");
    	add_exit("cavern1", "passage");
    }
   
    say(QCTNAME(this_player()) + action + ".\n");
    return 1;
}

void ctower_reset()
{
    close_fireplace();
}
