// creator(s):  Lilith Aug 2021
// last update:  
// purpose:     Crate for the BOGL camp
//              customized for use with SMIS placer.
// bug(s):
// to-do:

inherit "/d/Avenir/common/dark/smis/std_crate.c";
#include "/d/Genesis/gems/gem.h"
#include "../dead.h"
#define BOBJ "/d/Avenir/common/bazaar/Obj/"
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
    // fill the box with some different things.
    if (sizeof(all_inventory(this_object())) < 4)
    {
	    clone_object(OBJ + "rushlight")->move(TO, 1);
	    clone_object(OBJ + "rushlight")->move(TO, 1);
	    clone_object(BOBJ+"food/hearty_bread")->move(TO, 1); 
        clone_object(BOBJ+"food/fish")->move(TO, 1);	
	    clone_object(OBJ + "rushlight")->move(TO, 1);
	    clone_object(OBJ + "rushlight")->move(TO, 1);		
    }
    return 1;
}


void
create_container()
{
    ::create_container();

    seteuid(getuid(TO));

    reset_placed_functions();
}

