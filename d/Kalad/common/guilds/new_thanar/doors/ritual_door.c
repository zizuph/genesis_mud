/* The door for the Ritual Chamber where one can summon the 
*  Deity Thanar in the new fight. 
*  
*  by Mirandus - February 21, 2018
*/

inherit "/std/door";
#include "../local.h"

/*
 * Function name: create_door
 * Description:   creates the door
 * 
 */
create_door()
{
   set_door_id("thanar ritual door");
   set_pass_command(({"s","south","enter door"}));
   set_door_name(({"gilded door","door"}));
   set_long("This is beautifully gilded door. It is made of an ornate and "
      + "rare material that is found only in the depths of Kalad. It has been "
      + "engraved with marvellous details and appears to be impenetrable.\n");
   set_other_room(BASE + "ritual_chamber");
   set_fail_pass("The door is closed by some magical force.\n");
   set_open(0);
   set_locked(0);
}

/*
 * Function name: open_door
 * Description:   Open the door.
 * Arguments:     arg - arguments given
 */
int
open_door(string arg)
{
    object medallion;
    
    if (!this_door(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n", 0);
        return 0;
    }
    
    if (!objectp(medallion = present("_thanar_medallion_", this_player())))
    {
        notify_fail("A voice booms inside of your head: Fool. You expect "
        +"to pass into this chamber ill-prepared. That would bring doom and "
        +"death. Return when you have the key.\n",0);
        return 0;
    }
    write("A voice booms inside of your head: You have come prepared. "
    +"Excellent! You may enter the chamber. Be warned, should you summon "
    +"The Deity, Thanar, you had best be ready.\n");
    return ::open_door(arg);
}

int
pass_door(string arg)
{
    if (query_open() == 1)
    {
        ::pass_door(arg);
        
        do_close_door("The gilded door swings shut with a boom!\n");
                       
        if (other_door)
        other_door->do_close_door("The gilded door swings shut "
        + "with a boom!\n");
        
    }
    else
    {
        write(check_call(fail_pass));
        return 1;
    }
    return 1;
}