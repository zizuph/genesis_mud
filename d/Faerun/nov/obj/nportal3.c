inherit "/std/object";

#include <ss_types.h>
#include <stdproperties.h>
#include "../nov.h"


void
destroy_port()
{
	tell_room(environment(this_object()), "The "+this_object()->query_short() + " suddenly " +
	"collapses into itself and vanishes!\n");
        remove_object();
}


void
arrive_port()
{
	tell_room(environment(this_object()), "A huge black hexagon-shaped portal suddenly " +
	"materializes from the shadows!\n");
	
	this_object()->remove_name("hexagon");
	this_object()->set_name("portal");
	
	this_object()->set_adj("huge");
        this_object()->remove_name("rune");
        this_object()->remove_adj("floating");
	
	set_short("huge black hexagon-shaped portal");
        set_long("This is a huge black hexagon-shaped portal of black negative " +
        "energy. The huge black portal has a peculiar two-dimensional surface rising from the " +
        "ground resembling the shape of a hexagon. It is simply black, no variation " +
        "in colour and no dirt clinging to it.\n");
	
	this_object()->remove_prop(IAMHEXRUNE);
}


create_object()
{
    set_name("hexagon");
    add_name("drawing");
    set_adj("magical");
    add_adj("transparent");
    set_short("magical transparent hexagon");
    set_long("This is a transparent hexagon floating in midt air, created by " +
               "someone skilled in the arts of conjuration magic.\n");
    add_prop(OBJ_I_VALUE, 80000);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_STEAL, "This is just a drawing of a hexagon. Your hands pass through it " +
    "harmlessly.\n");
    add_prop(OBJ_M_NO_GET, "This is just a drawing of a hexagon. Your hands pass through it " +
    "harmlessly.\n");
    add_prop(OBJ_I_RES_MAGIC, 100);
    
    
    add_prop(IAMHEXRUNE, 1);
    
    set_alarm(60.0,0.0, &arrive_port());
    set_alarm(70.0,0.0, &destroy_port());
}

int
do_port(string str)
{
	
	if (str == "portal" && this_object()->query_prop(IAMHEXRUNE))
	{
        write("What ?\n");
        return 1;
        }

	
        if(str != "portal")
        {
        write("What ?\n");
        return 1;
        }

        if (this_player()->query_prop(NACCEPTED))
        {
        	tell_room(NOV_DIR + "temple/bport", this_player()->query_name() + " suddenly arrives out of " +
                "nowhere!\n", this_player());
        
                tell_room(environment(this_object()), this_player()->query_name() + " enters " +
                 "the "+short()+"!\n", this_player());
                
                this_player()->move_living("M", NOV_DIR + "temple/nport", 1);
                
                return 1;
        }
        

        if (this_player()->query_guild_name_lay() != GUILDNAME)
        {
        	write("The "+short()+" repels you when you try to enter it!\n");
        	
        	tell_room(environment(this_object()), this_player()->query_name() + " tries " +
                "to enter the "+short()+", but is quickly repelled by " + 
                "an invisible force!\n", this_player());
        	return 1;
        }
        
        	
       
   
       
        tell_room(NOV_DIR + "temple/bport", this_player()->query_name() + " suddenly arrives out of " +
        "nowhere!\n", this_player());
        
        tell_room(environment(this_object()), this_player()->query_name() + " enters " +
        "the "+short()+"!\n", this_player());
                
        this_player()->move_living("M", NOV_DIR + "temple/nport", 1);
        
        return 1;
}



void
init()
{
    ::init();
    add_action(do_port, "enter");
}