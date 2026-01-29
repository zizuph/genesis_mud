/*  
 *
 *  Portal to the Elder Vampire sanctuary
 *
 *  Nerull 2023.
 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "../guild.h";


/*
 * Function name: create_object()
 * Description  : Creates the object we wish to clone.
 */
void
create_object()
{
    setuid();
    seteuid(getuid());
     
    set_long("This is an almost completley invisible shimmering "
    +"field of magic floating in the "
    +"middle of the air. Instinctively, you know it's a portal to "
    +"the sanctuary of the Elder Vampires.\n");
    
    set_name("_elder_access_");
    add_name("field");
    add_name("portal");
    set_adj("obfuscated");
    add_adj("shimmering");
    
    set_short("obfuscated shimmering field");
       
    
    add_prop(OBJ_M_NO_GET, "The "+short()+" can't be taken.\n");

    add_prop(OBJ_M_NO_STEAL, "The "+short()+" can't be taken.\n");
    
    add_prop(OBJ_M_NO_GET, "The "+short()+" can't be taken.\n");

    add_prop(OBJ_M_NO_STEAL, "The "+short()+" can't be taken.\n");

    add_prop(CONT_I_VOLUME,  45000);
    add_prop(CONT_I_WEIGHT,  500000);
}


int
enter_elder_sanctuary(string str)
{
    int check1 = 0;
    int check2 = 0;
    
    int vamp_agex;
    
    vamp_agex = atoi(VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()));
    
    if (str == "portal" || str == "shimmering field" 
    || str == "shimmering portal" || str == "obfuscated shimmering field"
    || str == "obfuscated shimmering portal" || str == "obfuscated portal" 
    || str == "obfuscated field")
    {
        // Wizards can always see us.
        if (this_player()->query_wiz_level())
        {
            write("You enter the "
            + short() + "!\n");

            tell_room(environment(this_object()),
            QCTNAME(this_player()) +" is suddenly gone!\n", this_player());
                
            this_player()->move_living("M", "/d/Faerun/guilds/vampires/rooms/elder_sanctuary", 1);
            
            return 1;
        }
        
        if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 0)
        {
            return 0;
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_5(this_player()->query_name()) == 0)
        {
            return 0;
        }
        
        if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) >= 20)
        {
            check1 = 1;
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_reputation (this_player()->query_name()) >= 20)
        {
            check2 = 1;
        }
        
        if (check1 == 1 && check2 == 1)
        {
            write("You enter the "
            + short() + "!\n");

            tell_room(environment(this_object()),
            QCTNAME(this_player()) +" is suddenly gone!\n", this_player());
                
            this_player()->move_living("M", "/d/Faerun/guilds/vampires/rooms/elder_sanctuary", 1);
            
            return 1;
        }
    }
    
    check1 = 0;
    check2 = 0;
    
    return 0;
}


public int 
check_seen(object for_obj)
{
    int xcheck1 = 0;
    int xcheck2 = 0;
    
    // Wizards can always see us.
    if (for_obj->query_wiz_level())
    {
        return 1;
    }
    
    if (VAMPIRES_MASTER->is_occ_vampires(for_obj->query_name()) == 0)
    {
        return 0;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_5(for_obj->query_name()) == 0)
    {
        return 0;
    }
    
    if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(for_obj->query_name()) >= 20)
    {
        xcheck1 = 1;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_reputation (for_obj->query_name()) >= 20)
    {
        xcheck2 = 1;
    }
    
    if (xcheck1 == 1 && xcheck2 == 1)
    {
        return 1;
    }
    
    xcheck1 = 0;
    xcheck2 = 0;
    
    return 0;
}


/*
 * Function name: create_object()
 * Description  : Creates the object we wish to clone.
 */
void init()
{
    ::init();

    add_action(enter_elder_sanctuary, "enter");
}



