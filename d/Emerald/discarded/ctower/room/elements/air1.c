#include "../../ctower.h"

inherit AIRSTD;
 
#include <tasks.h>
#include <stdproperties.h> 

#define LIVE_I_FOUND_DIAMOND "_live_i_found_ctower_diamond"
 
string exa_desc();

void
create_air()
{
    add_exit("mist",  "north");
    add_exit("smoke", "west");
    add_exit("elem5", "east");
    add_exit("elem3", "south");
  
    remove_item("air");
  
    add_item(({"air", "wind", "winds"}), exa_desc);
  
    add_prop(OBJ_S_SEARCH_FUN, "search_it");
}
 
string
search_it(object player, string what)
{
    int success;
   
    if (what != "air" && what != "wind" && what != "winds")
    {
      return 0;
    }
  
    success = player->resolve_task(TASK_SIMPLE, ({ TS_INT, SS_AWARENESS }));
    if (!this_player()->query_prop(LIVE_I_FOUND_DIAMOND) && success > 0) 
    {
    	player->add_prop(LIVE_I_FOUND_DIAMOND, 1);
    	return "Your search reveals a diamond in the wind!\n";
    }
  
    return 0;
}
 
string
exa_desc()
{
    if (!this_player()->query_prop(LIVE_I_FOUND_DIAMOND))
    {
        return "The wind is incredibly fierce.  Hey didn't "+
	    "you see something?!\n";
    }
  
    return "The wind is incredibly fierce.\n";
}
 
int
get_it(string str)
{
    object gem;
    int    success;
   
    notify_fail("Get what?\n");
    if (str != "diamond")
    {
        return 0;
    }
   
    if (!this_player()->query_prop(LIVE_I_FOUND_DIAMOND))
    {
        return 0;
    }
   
    success = this_player()->resolve_task(TASK_ROUTINE, ({ TS_DEX, TS_DEX }));
    if (success > 0) 
    {
    	gem = clone_object(CTOWER_OBJ + "airgem");
    	gem->move(this_player(), 1);
    
    	write("You quickly grab the diamond.\n");
    	return 1;
    }
  
    write("You try to get the diamond but just aren't quick enough.\n");
    write("You overextend yourself, throwing yorself off balance.  " +
	"The wind crashes you into a wall!\n");
  
    this_player()->reduce_hit_point(this_player()->query_max_hp() / 10);
    if (this_player()->query_hp() <= 0)
    {
        this_player()->do_die(this_object());
    }
  
    return 1;
}

void
init()
{
  ::init();
 
  add_action(get_it, "get");
  add_action(get_it, "take");
}
