/* /d/Faerun/guilds/vampires/rooms/cv1_entryway.c
 *
 * Nerull 2021
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit VAMPIRES_STD_ROOM;

public int
block_check()
{
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 1)
    {          
        if (VAMPIRES_MASTER->is_coven1_member(this_player()->query_name()) == 1)
        { 
            return 0;
        }
    }        
    
    write("A magical field of force blocks you from "
    +"going in that direction.\n");
    
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

    set_short("Entryway");
    
    set_long("The entryway unfolds into a grand and open space, "
    +"giving the impression of regality and opulence. The marble "
    +"floors are deep shades of midnight and reflect the light from the "
    +"various candles burning around the room. There are various "
    +"portraits on the walls of the entryway, but the forms in "
    +"the pictures are oddly blurred. The wood of the walls is a "
    +"deep mahogany, which reflects the light in a way that "
    +"causes an eerie glow. There are doorways to adjacent "
    +"chambers, but more detail is enshrouded in darkness.\n");
    
    add_item(({"walls", "wall" }),
        "The walls are made from a polished, dark, mahogany "
        +"wood that reflects the light from the candles causing "
        +"an eerie glow.\n");

    add_item(({"floors", "floor", "ground" }),
        "The floors are made of marble and are a deep shade, "
        +"akin to the dark night sky. They are reflecting the "
        +"light from various candles.\n");

    add_item(({"marble"}),
        "The marble of the floors is of a deep, dark shade.\n");
           
    add_item(({"candle", "candles" }),
        "Blood-red candles flicker throughout the entryway "
        +"helping to cast an eerie radiance.\n");
                      
    add_item(({"picture", "pictures" }),
        "The silhouettes in the portraits are oddly blurred, "
        +"not allowing their identities to be known.\n");
                      
    add_item(({"portrait", "portaits" }),
        "Various pictures hanging throughout the hall. "
        +"Oddly, the forms depicted are blurred.\n");
                      
    add_item(({"wood" }),
       "The wood of the walls is a polished mahogany "
       +"with a deep dark richness.\n");
                      
    add_item(({"doorways"}),
       "There are doorways that extend into adjacent chambers, "
       +"but the depth of darkness inhibits further details.\n");
    

    add_exit(VAMPIRES_GUILD_DIR + "rooms/cv1_boardroom", "west", block_check);
    add_exit(VAMPIRES_GUILD_DIR + "rooms/cv1_crypt", "east", block_check);
    add_exit(VAMPIRES_GUILD_DIR + "rooms/cv1_lounge", "north", block_check);
    
    add_exit("/d/Faerun/underdark/dark_dom/rooms/tu03", "south");
    
    reset_faerun_room();
}


int do_claim(string str)
{
    if (str == "coven")
    {
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_4(this_player()->query_name()) > 0)
        {
            if (VAMPIRES_MASTER->is_coven1_master(this_player()->query_name()))
            {
                write("You are already the master of this coven!\n");
                
                return 1;
            }
            
            if (VAMPIRES_MASTER->is_coven2_master(this_player()->query_name()))
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
            
            if (VAMPIRES_MASTER->no_coven1_master() == 1)
            {
                VAMPIRES_MASTER->add_coven1_master(this_player()->query_name());
                VAMPIRES_MASTER->add_coven1_member(this_player()->query_name());
            
                write("You claim this coven and the facilities as your own!\n");
                
                COVEN_LOG("coven_log",
                "The vampire " +this_player()->query_name() 
                +" claimed coven 1.\n");
                
                return 1;
            }
            
            write("This coven already has a master!\n");
            
            return 1;
        }
    }
    
    return 0;
}


int leave_coven(string str)
{
    if (str == "coven")
    {
        if (VAMPIRES_MASTER->is_coven1_member(this_player()->query_name()))
        {            
            VAMPIRES_MASTER->remove_coven1_master(this_player()->query_name());
            VAMPIRES_MASTER->remove_coven1_member(this_player()->query_name());

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
        if (VAMPIRES_MASTER->is_coven1_master(this_player()->query_name()))
        {            
            VAMPIRES_MASTER->remove_coven1_master(this_player()->query_name());

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
    if (VAMPIRES_MASTER->is_coven1_master(this_player()->query_name()))
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
        
        if (VAMPIRES_MASTER->is_coven1_member(str) == 1)
        {
            write("That vampire is already a member of the coven.\n");
            return 1;
        }
        
        if (VAMPIRES_MASTER->is_coven2_member(str) == 1)
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
        
        VAMPIRES_MASTER->add_coven1_member(str);
    
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
    if (VAMPIRES_MASTER->is_coven1_master(this_player()->query_name()))
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
        
        if (VAMPIRES_MASTER->is_coven1_member(str) == 0)
        {
            write("That individual is not a member of the coven.\n");
            return 1;
        }
        
        VAMPIRES_MASTER->remove_coven1_member(str);
    
        write("You remove "+str+" from the coven!\n");
        
        COVEN_LOG("coven_log",
        "The covenmaster vampire " +this_player()->query_name() 
        +" removed "+str+" as a member of coven 1.\n");
    
        return 1;  
    }
    
    return 0;
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
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

