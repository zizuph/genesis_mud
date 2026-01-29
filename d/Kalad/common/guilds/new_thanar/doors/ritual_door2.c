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
   set_pass_command(({"n","north","enter door"}));
   set_door_name(({"gilded door","door"}));
   set_long("This is beautifully gilded door. It is made of an ornate and "
      + "rare material that is found only in the depths of Kalad. It has been "
      + "engraved with marvellous details and appears to be impenetrable.\n");
   set_other_room(BASE + "ritual_entrance");
   set_fail_pass("The door is closed, maybe you should open it?\n");
   set_open(0);
   set_locked(0);
}

int
open_door(string arg)
{
    object medallion;
    
    if (!this_door(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n", 0);
        return 0;
    }

       
    if(this_player()->query_attack())
    {
        notify_fail("Thanar prevents you from opening the door\n");
        return 0;
    }
    write("The door swings open silently upon its huge hinges.\n");
    return ::open_door(arg);
}

int
pass_door(string arg)
{
    
    if (present("_thanar_npc"))
    {
        write("You can't get close to the door to pas through\n");
        return 1;
    }
    
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