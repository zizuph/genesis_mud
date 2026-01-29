// creator(s):  Lilith Oct 96 
// last update: 
// purpose:     Crate with torches only; for the Underdark.
//              It is placed in rooms using the dark_treas_pmodule.c file
// bug(s):
// to-do:

inherit "/d/Avenir/common/dark/smis/std_crate.c";
#include "/d/Avenir/common/common.h"

/* Function name: reset_placed_functions
 * Description:   This function is called from the placer module to 
 *                reset the object. Can be used to fill the object with 
 *                contents. 
 *
 *    For when it is called see:
 *    /d/Avenir/smis/std/placer_mod.c
 *
 *    If it returns 1, the placer will do nothing, but if it returns 0,
 *    the placer will clone a new object.
 *
 */
public int
reset_placed_functions()
{
    int i = -1,
	num = 5 - sizeof(all_inventory(this_object()));
    
    // fill the box with some torches.
    while(++i < num)
	clone_object(BAZAAR + "Obj/misc/ptorch")->move(this_object(),1);
    return 1;
}


void
create_container()
{
    ::create_container();

    seteuid(getuid(TO));
   
    reset_placed_functions();
}

