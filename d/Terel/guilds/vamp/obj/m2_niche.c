//-*-C++-*-
// file name:      
// creator(s):     Lilith June 2008
// last update:    
// note: 
// bug(s):
// to-do:

inherit "/std/container";
#include "../defs.h"
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

object urn;

void
fill_niche()
{
    reset_euid();
    if (!urn)
    {
        urn = clone_object(OBJ_DIR +"urn");
        urn->move(TO, 1);
    }
}

int
clone_urns()
{
    int i = -1,
	num = 7 - sizeof(all_inventory(this_object()));
    while(++i < num)
	clone_object(OBJ_DIR +"urn_other")->move(this_object(),1);
    return 1;
}

string 
my_long()
{
    if (present("_columbarium_urn", TO))
        return "There is a red carnelian urn resting in one of the unmarked niches.\n";
    else
        return "\n";
}

public void
create_container()
{
    set_name("niches");
    add_name(({"unmarked niche", "unmarked niches", "empty niche", 
        "empty niches", "niche"}));
    set_adj(({"unmarked", "empty", "columbarium"}));
    set_short("columbarium niches");
    set_long("There are nine niches in this part of the columbarium. "+
        "Six of the niches are "+
        "marked with names and filled with urns. You can see "+
        "a large alabaster urn, an ornate jade urn, a black marble urn, "+
        "a wide golden urn, an ancient iron urn, and a pale amethyst urn "+
        "in the marked niches. "+
        "There are three unmarked niches, a sad reminder that a "+
        "great family's line ended prematurely. @@my_long@@");
    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(OBJ_M_NO_GET, "It cannot be moved.\n");
    set_no_show_composite(1);  //don't want it to show up in room desc.

    seteuid(getuid());
    fill_niche();
    clone_urns();
}



/*
 * Function name: prevent_enter
 * Description:   Called when an object is trying to enter this container to
 *                see if we will allow it in.
 * Arguments:     object ob - the object that is trying to enter.
 * Returns:       1 - The object is not allowed to enter
 *                0 - The object is allowed to enter
 */
int
prevent_enter(object entering)
{
    if (entering->id("_columbarium_urn"))
    {
        write("You settle the red carnelian urn into an unmarked niche.\n");
        return 0;
    }
    if (sizeof(all_inventory(this_object())) > 9)
    //I'm full, lets let player know.
    {
        write("The "+ short() +" is full.\n");
        return 1;
    }
    if (!entering->id("_columbarium_urn"))
    {
        write("The " + entering->short()+ " does not belong in "+
            "the niche. Placing it there would dishonour the "+
            "dead, and you get a feeling that dishonouring "+
            "these dead is not such a good idea.\n");
        return 1;
    }   

    return 0;
}

/*
 * Function name: prevent_leave
 * Description:   Called when an object is trying to leave this container
 *                to see if we allow it to leave.
 * Arguments:     object ob - the object trying to leave
 * Returns:       1 - The object is not allowed to leave
 *                0 - The object is allowed to leave
 */

int 
prevent_leave(object ob)
{
    if (ob->id("_columbarium_urn"))
        return 0;
    else
        write("The " + ob->short()+ " belongs in "+
            "the niche. Removing it would dishonour the "+
            "dead, and you get a feeling that dishonouring "+
            "these dead is not such a good idea.\n");
    return 1;
}