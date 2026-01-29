/*  
 *
 *
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
     
    /*set_long("This is an almost completley invisible shimmering or "
    +"haze, slightly tinted in a blood-red colour, floating in the "
    +"middle of the air. You think it's some sort of a gateway or "
    +"portal to somewhere else. You barely missed this one, but "
    +"your heightened unnatural senses discovered it just barely.\n");
    
    set_name("_anomality_");
    add_name("haze");
    set_adj("blood-red");
    add_adj("shimmering");
    
    set_short("blood-red shimmering haze");

    add_prop(OBJ_M_NO_GET, "The "+short()+" is too heavy to "
    +"move.\n");

    add_prop(OBJ_M_NO_STEAL, "The "+short()+" is too heavy to "
    +"steal.\n");*/
    
    set_long("rough test thingy.\n");
    
    set_name("_testob_");
    add_name("thingy");
    set_adj("rough");
    add_adj("test");
    
    set_short("rough test thingy");

    add_prop(OBJ_M_NO_GET, "The "+short()+" is too heavy to "
    +"move.\n");

    add_prop(OBJ_M_NO_STEAL, "The "+short()+" is too heavy to "
    +"steal.\n");

    add_prop(CONT_I_VOLUME,  45000);
    add_prop(CONT_I_WEIGHT,  500000);
}


int
enter_elder_cave(string str)
{
    int check1 = 0;
    int check2 = 0;
    
    if (str == "testy")
    {
        if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) >= 20)
        {
            check1 = 1;
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) >= 20)
        {
            check2 = 1;
        }
        
        /*if (check1 == 1 && check2 == 1)
        {
            write("You daringly enter the "
		    + short() + "!\n");

            tell_room(environment(this_object()),
            QCTNAME(this_player()) +" fades from view.\n", this_player());
                
            this_player()->move_living("M", "/d/Faerun/guilds/vampires/rooms/elder_cave", 1);
            
            check1 = 0;
            check2 = 0;
            
            return 1;
        }*/
        
        if (check1 == 1 && check2 == 1)
        {
            write("testy testy sucess.\n");

            //tell_room(environment(this_object()),
            //QCTNAME(this_player()) +" fades from view.\n", this_player());
                
            //this_player()->move_living("M", "/d/Faerun/guilds/vampires/rooms/elder_cave", 1);
            
            check1 = 0;
            check2 = 0;
            
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
    
    if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) >= 20)
    {
        xcheck1 = 1;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_reputation (this_player()->query_name()) >= 20)
    {
        xcheck2 = 1;
    }
    
    if (xcheck1 == 1 && xcheck2 == 1)
    {
        return 1;
    }
               
    return 0;
}


/*
 * Function name: create_object()
 * Description  : Creates the object we wish to clone.
 */
void init()
{
    ::init();

    add_action(enter_elder_cave, "testy");
}



