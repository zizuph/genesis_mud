/* cv/room1.c
 * Lilith Oct 2021
 * Coven Location #2 for the Faerun Vampires.
 * Any changes to these rooms should be discussed
 * by the GM of the Vamps and the Liege of Avenir.
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "/d/Faerun/guilds/vampires/guild.h";

inherit VAMPIRES_STD_ROOM;

public int
block_check()
{
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 1)
    {          
        if (VAMPIRES_MASTER->is_coven2_member(this_player()->query_name()) == 1)
        { 
            return 0;
        }
    }        
    
    write("Something dark and dire repels you from going in that "+
        "direction.\n");
    
    return 1;

}


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
	set_short("crevice");
	set_long("Dark and so unobtrusive as to be unnoticable, you have a "+
        "sense that something of importance is here, as if the living "+
		"stone is parturient with a power of ancient provenance. "+	
	    "The air contains the faintest hint of warmth, "+
        "heated as it is by the magma flowing through the abyss "+ 
        "south of you. Crystals sprout around the jagged openings "+
        "that lead north and west from here.\n");

    add_exit("room2", "north", block_check);  
	add_exit("room8", "west", block_check);  
    add_exit("cv_ledge", "south");
    
	add_item(({"stone", "volcanic stone", "basalt", "basaltic stone"}),
        "The stone appears to be a basalt made when magma cooled. It is "
        +"dark with a hint of warmth, and striped with agate.\n");
	add_item(({"agate", "colourful agate", "agates", "stripes"}),	
        "Formed eons ago when heated gases were trapped in these magma "
        +"tunnels and then slowly cooled. They are beautiful, forming "
        +"ribbons, bands, and lacy swirls.\n");				
   add_item(({"crystal", "crystals", "opening"}),
        "Small crystals can be seen along the edges of openings that "+
        "were broken between this crevice and a larger void beyond.\n"); 		
     
    reset_faerun_room();

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
            +" claimed coven 1.\n");
            
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
            +" left coven 1.\n");
            
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
            +" resigned, now a regular member of coven 1.\n");
            
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
        +" added "+str+" as a new member of coven 1.\n");
    
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
        +" removed "+str+" as a member of coven 1.\n");
    
        return 1;  
    }
    
    return 0;
}


void
init()
{
    ::init();

    add_action(do_claim, "claim");
    add_action(do_resign, "resign");
    add_action(do_add, "add");
    add_action(do_removemember, "remove");
    add_action(leave_coven, "leave");
}
