/* 
 * Room in the Thanarian Cathedral in Kabal
 * /d/Kalad/common/guilds/new_thanar/upper_mid5.c
 */

#include "../local.h"

inherit THANAR_STD_ROOM; 

/*
 * Function name: create_std_thanar()
 * Description  : Constructor for the room, modify this to change room.
 */
create_std_thanar()
{
    string long1, long2, long3;
    
    //Selects the random long description strings.
    long1 = one_of_list(LONG1);
    long2 = one_of_list(LONG2);
    long3 = one_of_list(LONG3);
    
    set_short("Inside the Cathedral");
    set_long(long1+long2+long3+"\n"); 
    
           
    add_exit(RDIR + "upper_mid4","west");
    add_exit(RDIR + "upper_mid6","east");
    add_exit(RDIR + "inner_mid","south");
    add_exit("/d/Kalad/common/guilds/new_thanar/guildhall/room/entrance.c"
    ,"north", "@@cannot_enter_temple", 1, "@@cannot_see_exit");
    
    //Sets the no exit message for unlisted directions.
    set_no_exit_msg(get_all_no_exits(({"s","n"})),
    "The rest of the Cathedral is still under construction.\n");

    //Adds the NPCs, # of them and arms them
    //add_npc(LIV +"mpriest", 1, &->arm_me());
    //add_npc(LIV +"caster_priest", 1, &->arm_me());
    
    //Clone the sphere for those seeking to transition.
    clone_object(PARENT + "guildhall/thanar_sphere")->move(this_object());
    
    reset_room();
}

public void
notify_wizard_of_restricted_access()
{
    // Give a message to wizards that they can enter because they are
    // wizards, even though normally this should not be accessible.
    if (this_player()->query_wiz_level() > 0)
    {
        write("Since you are a wizard, you are allowed entry.\n");
    }
}

/*
 * Function name: cannot_see_exit()
 * Description  : Determines who is able to see an exit in a room
 */
public int
cannot_see_exit()
{
    if (this_player()->query_race_name() == "human" ||
    this_player()->query_race_name() == "wraith")
    {
        //Allow humans and wraiths to see exit to Thanar guild
        return 0;
    }
    
    if (this_player()->query_wiz_level() > 0)
    {
        return 0;
    }
    
    return 1;
}

/*
 * Function name: cannot_enter_temple()
 * Description  : Stops someone from entering even if they can't see exit.
 */
public int
cannot_enter_temple()
{
    if (!cannot_see_exit())
    {
        notify_wizard_of_restricted_access();
        return 0;
    }
    // Non-wizards cannot use these exits.
    write("Only Humans may enter.\n");
    return 1;
}    