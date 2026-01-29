/* /cv/board.c
 *     This is the room with the bulletin board as well as the 
 *     coven commands to claim, add, remove, leave, etc.
 * 
 * Nerull 2021
 * Lilith Nov 2021
 * Coven Location #2 for the Faerun Vampires.
 * Any changes to these rooms should be discussed
 * by the GM of the Vamps and the Liege of Avenir.
 *
 */
 
inherit "/d/Faerun/guilds/vampires/rooms/std/vampires_std_room";

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "/d/Faerun/guilds/vampires/guild.h";

private string action_readsign();

/*
 * Function name: create_vampires_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_vampires_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);
	add_prop("_not_in_flux_zone", 1); //This prevents Source-related room tells.	
    set_short("Boardroom");  
    set_long("This is the boardroom, the place where the business of "
        +"of the coven is conducted. The walls are mostly milky-white "
        +"chalcedony with thick reddish-brown bands of semi-translucent "
        +"agate. The basalt floor is carpeted in fur pelts. There is a "
        +"round table with a handful of chairs around it, a bulletin "
        +"board on the west wall, and a sign in a gilded frame "
        +"posted near the door.\n");    		
   
    room_add_object(VAMPIRES_GUILD_DIR + "boards/cv2_board");
                      
    add_exit("room7", "east");
 
    add_item(({"stone"}), "There is basaltic stone, agate, and chalcedony "
        +"in this room.\n");
    add_item(({"wall", "walls"}), "The walls of the boardroom are mostly "
        +"chalcedony striped with reddish-brown agate.\n");
	add_item(({"agate", "reddish-brown agate", "reddish-brown stone",
        "stripes", "bands"}),
		"Horizontal bands of reddish-brown agate interrupt the milky-white "  
        +"chalcedony of the walls.\n");
	add_item(({"chalcedony", "white chalcedony", "milky-white chalcedony"}),
	    "Polished over the eons to a waxy lustre, this semi-precious stone "
        +"is a lustrous backdrop for the beautiful variagation of the agate "
		+"that runs through it in horizontal bands.\n");
    add_item(({"floor", "ground", "basalt", "basaltic stone"}),
        "The basalt floor is chiseled level and polished to a high gloss that "
        +"accentuates the sparkle of the microcrystals within it. The pelts "
        +"of many creatures have been strewn about to soften the hardness "
        +"of the stone floor.\n");
    add_item(({"pelts", "pelt", "fur", "furs"}), 
        "Fur pelts from creatures all over the world have been strewn upon "
        +"the hard stone floors and across the chairs, softening them and "
        +"muffling sound.\n");		
    add_item(({"table", "wood table", "heartwood", "round table"}),
        "The table is round and made of a single slab of wood cut from a once-"
        +"giant tree. Wood is a very rare commodity here in this utterdark land, "
		+"so this table is a display of enormous wealth. The heartwood " 
        +"gleams darkly.\n");
    add_cmd_item(({"table", "at table"}), ({"sit"}), "You take a seat at the "
        +"table.\n");		
	add_item(({"chair", "chairs"}), "Each chair is made of wood and draped "
        +"in furs to allow for maximum comfort.\n");	
    add_cmd_item(({"chair", "in chair"}), ({"sit"}), "You pull out a chair "
        +"and sit down in it.\n");	
    add_item(({"sign", "gilded frame", "framed sign"}), action_readsign);
    add_cmd_item(({"sign"}), "read", action_readsign);	
	
    reset_faerun_room();
}

private string 
action_readsign()
{
    return "A guilded wooden frame holds a sign that reads:\n"
        +"            For commands relating\n"
        +"              to coven business \n" 
        +"               use <help here>  \n"
        +"\n";
}

/*
 * Function name:  help_here
 * Description:    Provide help for the functions in this room
 */
public int
help_here(string str)
{
    notify_fail("Help what? Help here?\n");
    if (!strlen(str))
	return 0;

    if (str == "here" || str == "coven business")
    {
        write("  The following commands relate to coven business: "
        +"\n\n"
        +"    claim coven             Claim leadership of this coven.\n"
        +"    leave coven             Leave this coven.\n"
        +"\n\n");
        if (VAMPIRES_MASTER->is_coven2_master(this_player()->query_name()))
        {
			write("\n\n"
		    +"  As Coven Master these commands are also available to you:"
            +"    cvadd name              Add a vampire to this coven.\n"
            +"    cvremove name           Remove a vampire from this coven.\n"
            +"    coventransfer name      Make someone else head of this coven.\n"
            +"    resign as covenmaster   Resign as master of this coven.\n"
            +"\n\n");  // maybe add a cvlist to list members of the coven?
        }		
        return 1;
    }

	else
      return 0;
}
int do_claim(string str)
{
    if (str == "coven")
    {
        if (VAMPIRES_MASTER->is_coven2_master(this_player()->query_name()))
        {
            write("You are already the master of this coven!\n");
            
            return 1;
        }
        
        if (VAMPIRES_MASTER->is_coven1_master(this_player()->query_name()))
        {
            write("You are already the master of a different coven!\n");
            
            return 1;
        }
        
        if (VAMPIRES_MASTER->is_coven3_master(this_player()->query_name()))
        {
            write("You are already the master of a different coven!\n");
            
            return 1;
        }
        
        // Must have turned atleast 1 vampire to claim a coven. 2 == 1 turned vampire
        // 3 == 2 turned vampires etc. 1 == default rank.
        if (VAMPIRES_MAPPINGS->query_vampires_rank(this_player()->query_name()) < 2)
        {
            write("To claim a vacant coven, you must have atleast sired one vampire!\n");
            
            return 1;
        }
        
        if (VAMPIRES_MASTER->no_coven2_master() == 1)
        {               
            int current_resilience_rank = VAMPIRES_MAPPINGS->query_vampires_resilience(this_player()->query_name()); 
            int new_resilience_rank = current_resilience_rank - 2;
            
            if (current_resilience_rank < 2)
            {
                write("This action requires two points of immortality, which "
                +"you don't currently have.\n");
                
                return 1;
            }
            
            VAMPIRES_MAPPINGS->set_vampires_resilience(this_player()->query_name(), new_resilience_rank);
            
            VAMPIRES_MASTER->add_coven2_master(this_player()->query_name());
            VAMPIRES_MASTER->add_coven2_member(this_player()->query_name());
        
            write("You claim this coven and the facilities as your "
            +"own!\nYou pay two points of immortality.\n");
            
            COVEN_LOG("coven_log",
            "The vampire " +this_player()->query_name() 
            +" claimed coven 2.\n");
            
            return 1;
        }
        
        write("This coven already has a master!\n");
        
        return 1;
        
    }
    
    return 0;
}


int leave_coven(string str)
{
    if (str == "coven")
    {
        if (VAMPIRES_MASTER->is_coven2_member(this_player()->query_name()))
        {            
            VAMPIRES_MASTER->remove_coven2_master(this_player()->query_name());
            VAMPIRES_MASTER->remove_coven2_member(this_player()->query_name());

            write("You are no longer a member of this coven!\n");
            
            COVEN_LOG("coven_log",
            "The vampire " +this_player()->query_name() 
            +" left coven 2.\n");
            
            return 1;
        }
        
        write("You are not a member of this coven.\n");
        
        return 1;
    }
    
    return 0;
}


int do_resign(string str)
{
    if (str == "as covenmaster")
    {
        if (VAMPIRES_MASTER->is_coven2_master(this_player()->query_name()))
        {            
            VAMPIRES_MASTER->remove_coven2_master(this_player()->query_name());

            write("You resign as the master of the coven!\n");
            
            COVEN_LOG("coven_log",
            "The covenmaster vampire " +this_player()->query_name() 
            +" resigned, now a regular member of coven 2.\n");
            
            return 1;
        }
        
        write("You are not the master of this coven.\n");
        
        return 1;
    }
    
    return 0;
}


int do_add(string str)
{
    if (VAMPIRES_MASTER->is_coven2_master(this_player()->query_name()))
    {           
        if (!str)
        {
            write("Add what vampire to the coven?\n");
            return 1;
        }
        
        if (VAMPIRES_MASTER->is_occ_vampires(str) == 0)
        {
            write("That person is not a full vampire.\n");
            return 1;
        }
        
        if (str == this_player()->query_name())
        {
            write("You can't use this function on yourself.\n");
            return 1;
        }
        
        if (VAMPIRES_MASTER->is_coven2_member(str) == 1)
        {
            write("That vampire is already a member of the coven.\n");
            return 1;
        }
        
        if (VAMPIRES_MASTER->is_coven1_member(str) == 1)
        {
            write("That vampire is already a member of a different coven.\n");
            return 1;
        }
        
        if (VAMPIRES_MASTER->is_coven3_member(str) == 1)
        {
            write("That vampire is already a member of a different coven.\n");
            return 1;
        }
        
        object playa = find_player(str);
        
        if (!playa)
        {
            write("No such vampire in the game.\n");
            return 1;
        }
        
        VAMPIRES_MASTER->add_coven2_member(str);
    
        write("You add "+str+" to the coven!\n");
        
        COVEN_LOG("coven_log",
        "The covenmaster vampire " +this_player()->query_name() 
        +" added "+str+" as a new member of coven 2.\n");
    
        return 1;  
    }
    
    return 0;
}


int do_removemember(string str)
{
    if (VAMPIRES_MASTER->is_coven2_master(this_player()->query_name()))
    {           
        if (!str)
        {
            write("Remove what vampire from the coven?\n");
            return 1;
        }
        
        if (str == this_player()->query_name())
        {
            write("You can't use this function on yourself.\n");
            return 1;
        }
        
        if (VAMPIRES_MASTER->is_coven2_member(str) == 0)
        {
            write("That individual is not a member of the coven.\n");
            return 1;
        }
        
        VAMPIRES_MASTER->remove_coven2_member(str);
    
        write("You remove "+str+" from the coven!\n");
        
        COVEN_LOG("coven_log",
        "The covenmaster vampire " +this_player()->query_name() 
        +" removed "+str+" as a member of coven 2.\n");
    
        return 1;  
    }
    
    return 0;
}


int do_coventransfer(string str)
{
    if (VAMPIRES_MASTER->is_coven2_master(this_player()->query_name()))
    {           
        if (!str)
        {
            write("Transfer the role of covenmaster to whom?\n");
            return 1;
        }
        
        if (str == this_player()->query_name())
        {
            write("You can't use this function on yourself.\n");
            return 1;
        }
        
        if (VAMPIRES_MASTER->is_coven2_member(str) == 0)
        {
            write("That individual is not a member of your coven.\n");
            return 1;
        }
        
        VAMPIRES_MASTER->remove_coven2_master(this_player()->query_name());
        VAMPIRES_MASTER->add_coven2_master(str);
           
        write("You step down as covenmaster and assign "
        +str+" as the new head of the coven!\n");
        
        COVEN_LOG("coven_log",
        "The covenmaster vampire " +this_player()->query_name() 
        +" stepped down and assigned "+str+" as the new covenmaster "
        +"for coven 2.\n");
    
        return 1;  
    }
    
    return 0;
}



public void
autosit(object who)
{
    write("You sit down on one of the chairs at the table.\n");
    say(({ who->query_met_name() + " sits on a chair by the "+
	    "table.\n",
	    who->query_nonmet_name() + " sits on a chair by the "+
	    "table.\n", ""}));
}

/*
 * Function that allows the player to stand
 */
int
action_stand(string str)
{
    this_player()->catch_msg("You get up from your seat at the table.\n");         
    say(QCTNAME(this_player())+" stands up.\n");
    return 1;
}

void
init()
{
    ::init();
	add_action(action_stand, "stand");
	add_action(action_stand, "rise");	
    add_action(leave_coven, "leave");
    add_action(help_here,   "help");
    add_action(do_claim,    "claim");
    add_action(do_resign,   "resign");
  // prefixing with 'cv' since boards have remove action.
    add_action(do_add,      "cvadd");
    add_action(do_removemember, "cvremove");
	add_action(do_coventransfer, "coventransfer");
  // maybe add an action for listing coven members?
}


public void
enter_inv(object to, object from)
{
    ::enter_inv(to, from);

    if (query_interactive(to))
	set_alarm(1.5, 0.0, &autosit(to));
}


public void
leave_inv(object to, object dest)
{
    ::leave_inv(to, dest);

    if (query_interactive(to))
	to->catch_tell("You rise from your chair as you leave the room.\n");
}

void
reset_faerun_room()
{
    ::reset_faerun_room();
}
