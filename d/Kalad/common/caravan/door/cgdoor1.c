inherit "/std/door";
#include "/d/Kalad/defs.h"
/* by Antharanos with header from Aldarion */
create_door()
{
    set_door_id("cgdoor");
    set_pass_command(({"s","south"}));
    set_door_name(({"pair of massive steel doors","massive steel doors","steel doors","doors","massive doors"}));
    set_other_room("/d/Kalad/common/caravan/caravan_gate");
    set_fail_pass("The Caravan Gate is closed!\n");
    set_open(0);
    set_str(300);
    set_door_desc("These huge double doors are the only way through the "+
      "huge encircling walls of Kabal. Built out of solid steel and "+
      "standing thirty feet in height, as well as several feet in "+
      "thickness, the Caravan Gate is virtually impassable when closed. "+
      "A large winch lies beside the doors.\n");
}

int open_door(string arg)
{
    if(!this_player()->id("cg_gatekeeper"))
	return 0;

    return ::open_door(arg);
}

/*
int
open_door(string arg)
{
    if (member_array(arg, door_name) < 0)
	return 0;

    if (!other_door)
	load_other_door();

    if (!open_status)
    {
	if (lock_status)
	    write(check_call(fail_open[1]));
	else if(!this_player()->id("cg_gatekeeper"))
	{
	    if (this_player()->query_stat(SS_STR) < open_str)
		write("You lack the strength needed.\n");
	}
	else
	{                                                      
	    write("Ok.\n");                                    
	    say(QCTNAME(this_player()) + " " + check_call(open_mess[0]),     
	      this_player());                                
	    do_open_door("");                                  
	    other_door->do_open_door(check_call(open_mess[1]));
	}                                                      
    }                                                          
    else                                                       
	write(check_call(fail_open[0]));                       

    return 1;                                                  
}                                                              
 */
