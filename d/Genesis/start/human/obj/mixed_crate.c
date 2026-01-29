// creator(s):  Lilith Oct 96
// last update: 
// purpose:     Mixed treasure crate for the Underdark.
//              It is placed in rooms using the dark_treas_pmodule.c file
// bug(s):
// to-do:

inherit "/d/Avenir/common/dark/smis/std_crate.c";
#include "/d/Avenir/common/common.h"
#include "/d/Genesis/gems/gem.h"

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
    object gem;
    // fill the box with some different things.
    if (sizeof(all_inventory(this_object())) < 2)
    {
	clone_object(BAZAAR +"Obj/misc/ptorch")->move(this_object(),1);
	clone_object(BAZAAR +"Obj/misc/ptorch")->move(this_object(),1);
	clone_object(DARK +"obj/sausage")->move(this_object(),1);  
	clone_object(DARK +"obj/knife")->move(this_object(),1);
	gem = RANDOM_GEM(GEM_RARE);
                  gem->move(this_object(), 1);
	gem = RANDOM_GEM(-1);
                  gem->move(this_object(),1);
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

