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
#include <macros.h>


#define LOCKED_RM  (ROOM_DIR +"m6")

int clone_urns();

string 
my_long()
{
    if (present("_isabella_urn", TO))
        return "Each niche is filled with an urn. "+
        "You can see "+
        "a striped chalcedony urn, a speckled bloodstone urn, a "+
        "silver and mithril urn, a lapis-lazuli urn, a red "+
        "carnelian urn, round jasper urn, a black onyx urn, a "+
        "garnet-encrusted gold urn, and a milk-white quartz urn "+
        "in the marked niches.\n";
    else
        return "You can see a striped chalcedony urn, a speckled "+
        "bloodstone urn, a silver and mithril urn, a lapis-"+
        "lazuli urn, round jasper urn, "+
        "a black onyx urn, a garnet-encrusted gold urn, and "+
        "a milk-white quartz urn in the marked niches. "+
        "One niche, the fifth niche, is missing an urn. "+
        "The name Isabella is inscribed on it.\n";

}


string exa_fifth()
{
    if (present("_isabella_urn", this_object()))
    {
        return "There is a red carnelian urn in the fifth niche. "+
            "The name Isabella is inscribed on it.\n";
    }           
    else
        return "The fifth niche is empty. The name Isabella is "+
            "inscribed on it.\n";

}

public void
create_container()
{
    set_name(({"niches"}));
    add_name(({"fifth niche","columbarium", "niche"}));
    set_adj(({"unmarked", "empty", "columbarium", "fifth"}));
    set_short("columbarium niches");
    set_long("There are nine niches in this part of the columbarium, "+
        "each of them marked with a name. @@my_long@@ \n");

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

    add_item(({"fifth urn", "fifth niche", "isabella", "Isabella",
        "red carnelian urn", "canelian urn", "red urn"}), "@@exa_fifth");

    seteuid(getuid());
    clone_urns();
}

int
clone_urns()
{
    int i = -1,
	num = 8 - sizeof(all_inventory(this_object()));
    while(++i < num)
	clone_object(OBJ_DIR +"urn_other")->move(this_object(),1);
    return 1;
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
    if (entering->id("_isabella_urn"))
    {
        write("You settle the red carnelian urn into its proper niche.\n");
        LOAD_ERR(LOCKED_RM);
        LOCKED_RM->urn_unlock();
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
        write("The " + ob->short()+ " belongs in "+
            "the niche. Removing it would dishonour the "+
            "dead, and you get a feeling that dishonouring "+
            "these dead is not such a good idea.\n");

    return 1;
}