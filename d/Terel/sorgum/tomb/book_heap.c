inherit "/std/object.c";

#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "tomb.h"

#define BS(message)    break_string(message, 70)

int     key_gone_flag = 0;

create_object()
{
     seteuid();
     set_name("heap");
     set_short("decayed heap of books");
     set_long(BS("a great formless heap of books in the centre of " + 
		 "the room.\n"));
     add_prop(OBJ_I_VALUE, 0);
     add_prop(OBJ_M_NO_GET, "The heap is too decayed for you to pick it " +
			       "up.  You might be able to search through " +
			       "it though.\n");
     add_prop(OBJ_S_SEARCH_FUN, "do_search");
      
}

reset_object()
{
     key_gone_flag = 0;
}

string
do_search()
{
     object key;

     if (!key_gone_flag) {
	  key_gone_flag = 1;
	  key = clone_object(TOMBDIR + "tomb_key");
	  if (key->move(TP)) 
	      key->move(environment(TP));
	  key->set_key(TOMB_DOOR_KEY);
	  say(QCTNAME(TP) + " finds something in the heap\n");
	  return "You uncover and pick up a stone key.\n";
     }
     else {
	     if (random(4) == 0) {
		  key = clone_object(TOMBDIR + "tomb_key");
		  if (key->move(TP)) 
		       key->move(environment(TP));
		  key->set_key(TOMB_DOOR_KEY);
		  say(QCTNAME(TP) + " finds something in the heap.\n");
		  return "You uncover and pick up a stone key.\n";     
	     }
	     else
	  return "You don't find anything in the heap, but it seems " +
		 "that somone else may have searched through it recently.\n";
	}
}


