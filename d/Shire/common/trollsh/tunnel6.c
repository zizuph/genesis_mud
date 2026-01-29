inherit "/d/Shire/common/lib/rom";

#include "/d/Shire/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

// #define MY_PROP "_found_the_lever_hidden"

int open;
create_rom()
{
	set_short("A passage under the trollshaws");
	set_long("You have entered a place in the tunnels where the road "
		+"turns more to the east, but still heads north. It is very dark in here "
		+"so you can not see what is beyond the opening. On "
		+"the ground gore and blood floats in a big puddle. Scattered "
		+"bones and skulls lay here as a reminder of nasty beasts "
		+"who wandered these tunnels far back in time. The walls are "
		+"dark and absorb most of the light that shines here.\n");
		
	add_item(({"blood","gore"}),"It looks like some troll left their guts here...\n");
	add_item(({"wall", "walls"}), "@@exa_wall");
	add_item(({"skulls", "bones"}), "They do not look like regular human bones. "
	                               +"The skulls have an irregular shape.\n"); 			    

//	add_item("lever","@@exa_lever");

/*
	add_item(({"mark","marks"}),
   			 "The marks on the wall are made by something "
			+"sliding across it...\nA lever, perhaps?\n");
*/	
	add_exit(TROLLSH_DIR + "tunnel4", "northeast",0,2);
	add_exit(TROLLSH_DIR + "tunnel5", "north", 0, 2);
	
	add_call("pull", "[the] [hidden] 'lever'", "pull_lever");
	//add_call("search","[the] 'wall'","search_wall");
	
	add_prop(ROOM_I_LIGHT, 1);
    add_prop(OBJ_I_SEARCH_TIME, 3);
//    add_prop(OBJ_S_SEARCH_FUN, "search_wall2");
    reset_room();

}
/*
string
lever_long()
{
    if (TP->query_prop(MY _PROP))
    return "There is a lever on the wall.\n";
    else return "The wall looks black and smooth. There are some strange marks on it.";
}

string
exa_lever()
{
    if (TP->query_prop(MY_PROP))
        return "A small lever is hidden in the wall, you might try to pull it.\n";
        else
        return "Examine what?\n";
}
*/
string
exa_wall()
{
//    if (TP->query_prop(MY_PROP))
//    return "The wall is black and smooth.\n";
//    else
    return "The walls are black and smooth.\n";
}

string
search_wall2(object me, string str)
{
	if(str == "wall" || str == "walls")
	{	
/*
      if (me->query_skill(SS_AWARENESS) > 25 + random(26))
      {

	    me->add_prop(MY_PROP, 1);
	    return "You find something hidden in the wall.\n"+
		"It's a lever, right in front of your big fat nose!.\n";
	    //say(QCTNAME(me)+" finds something hidden in the wall.\n");
      }
	  else
*/
	    return "You search the walls up and down without any result.\n";
	}
	return ""; 
}
/*
pull_lever(string arg)
{
    notify_fail("What exactly are you trying to do?\n");
    if(arg !="lever")
    return 0;
    if (open)
    {
      write("You pull the lever desperatly, but nothing happens. Maybe the "
           +"door already is open?\n");
      say(QCTNAME(TP) + " desperatly pulls the lever, but nothing happens.\n");
    }
    else    
	  write("You pull the lever on the wall, but nothing happens.\n");
}
*/

void
reset_room()
{
/*
    object spiderweb;

    seteuid(getuid());

    if (!present("_shire_spiderweb_",TO))
    {
        spiderweb = clone_object("/d/Shire/scav_hunt/spiderweb");
        spiderweb->move(TO);
    }
*/
}

