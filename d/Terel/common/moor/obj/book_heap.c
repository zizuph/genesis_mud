inherit "/std/object.c";

#include "/d/Terel/include/Terel.h"
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

int     key_gone_flag = 0;

void
reset_object()
{
     key_gone_flag = 0;
}

string
do_search(string str)
{
    object key;
 
    if (!key_gone_flag) 
    {
	  key_gone_flag = 1;
	  key = clone_object(TOMBDIR + "tomb_key");
	  key->set_key(TOMB_DOOR_KEY);
	  key->move(TP, 1);
	  say(QCTNAME(TP) + " finds something in the heap of books.\n");
	  return "You uncover and pick up a stone key.\n";
     }
     else 
	 {
		// Random chance 1 in 4 of getting one.
	    if (random(4) == 0) 
		{
          key = clone_object(TOMBDIR + "tomb_key");
	      key->set_key(TOMB_DOOR_KEY);
	      key->move(TP, 1);
		  say(QCTNAME(TP) + " finds something in the heap of books.\n");
		  return "You uncover and pick up a stone key.\n";     
	    }
	    else
	    return "You don't find anything in the heap, but it seems " +
		  "that somone else may have searched through it recently.\n";
	}
}



void
create_object()
{
    set_name("heap");
    set_short("decayed heap of books");
	add_name(({"heap of books", "books"}));
    set_long("A great formless heap of books in the centre of " + 
		 "the room, moldering on the sagging floor.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_GET, "The heap is too decayed for you to pick it " +
       "up. You might be able to search through it though.\n");
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    reset_object();      
}
