/* OBJECT:  Pumpkin patch 
   CALIA DOMAIN  /d/Calia/valkira/objects/pumpkin.c

   Date      Coder      Action    Comment/Purpose
   ------- ----------- -----------------------------
   9/23/99   Valkira    Created   Place to find a pumpkin
*/


// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <options.h>

// FUNCTIONS

// Function:  choose_pumpkin

/*

Purpose:  Puts a pumpkin in the player's inventory.
Arguments:  none
Returns:  1
*/

int
choose_pumpkin(string str)
{
    if (str == "pumpkin")
    {
    object pumpkin;
    object tp = this_player();
    
    pumpkin = clone_object("/d/Calia/valkira/pumpkin.c");
    pumpkin->move(tp);

    write("You have chosen a pumpkin from the middle of the patch. \n");

    say(QCTNAME(tp) + " takes a pumpkin from the patch.\n");

    return 1;

    }

else

    {

    notify_fail("Choose what?  Only pumpkins are in that patch! \n.");
    return 0;

    }
}

void
init()
{
    ::init();
    add_action(choose_pumpkin, "choose");
}


// OBJECT DEFINITION

void
create_object()

{

    set_short("pumpkin patch");
    set_long("It's a pumpkin patch.  Perhaps you could choose a pumpkin.");
    set_name("patch");
    add_name("pumpkins");
   
    /*  PROPERTIES  */

    add_prop(OBJ_I_WEIGHT, 50000);
    add_prop(OBJ_I_VOLUME, 75000);
    add_prop(OBJ_M_NO_GET, "You can't take the whole pile.\n");


}

