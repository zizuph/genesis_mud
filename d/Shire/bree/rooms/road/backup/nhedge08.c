/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit ROAD_BASE;

#define BUSH_PROP "_bree_hedges_opening"
 
void
create_road_room()
{
//    set_areadesc("small");
//    set_area("path");
//    set_areaname("outside the hedge");
    set_land("North Bree");

    add_my_desc("The dike ends here, but the hedge continues up " +
        "the side of Bree Hill, out of your reach. There are lots " +
        "of claw marks in the ground, and at the base of the hedge " +
        "where animals, or worse, have been clawing at the bushes " +
        "and trees.\n");

//    remove_item(({"bushes", "bush", "shrubs", "trees"}));
//    remove_item(({"shrubs", "trees", "bushes"}));
    remove_item("shrubs");
    remove_item("trees");
    remove_item("bush");
    remove_item("bushes");

    add_item(({"bushes"}),"@@exa_bush");
    add_item(({"small opening", "opening", "small hole", "hole"}),
        "@@exa_hole\n");

    set_add_hedge_road();
//    set_add_bushes();
    set_add_claw_prints();

    add_exit(ROAD_DIR + "nhedge07", "west");

}

void
init()
{   
    ::init();
 
    add_action("enter_tunnel", "enter");
}

string
exa_bush()
{
    if(TP->query_skill(SS_AWARENESS)>15)
    {   
       TP->add_prop(BUSH_PROP,1);
        write("The bushes are tall and grow together into a thick " +
            "wall of vegetation. A small opening has been clawed " +
            "through the bushes.\n");
    return "";
    }
    else
      write("The bushes are tall and grow together into a thick " +
        "wall of vegetation.\n");
       return "";
}

/*
string
exa_bush()
{

    string text;
    if(TP->query_skill(SS_AWARENESS)>15)
    {   
       TP->add_prop(BUSH_PROP,1);
       text = "A small opening has been clawed through the hedge.";
//    return "";
    }
    else
    {
        text = "";
    }
        write("The hedge grows around the perimeter of the town. It is " +
        "very thick and resembles a wall. It offers a measure of " +
        "protection, increased by a deep dike that has been dug " +
        "to the left of the hedge. " +text+"\n");
        return "";

}
*/

int
enter_tunnel(string str)
{
    if(str=="hidden opening" ||
       str=="opening" || 
       str=="bushes" ||
       str=="small opening" || 
       str=="hedge")
    {
        if(TP->query_prop(BUSH_PROP))
        {    
            write("You climb through the small opening in the hedge.\n");
            say(QCTNAME(TP)+" disappears into the hedge.\n");
            tell_room(CAMP_DIR +"tunnel1",QCTNAME(TP) + 
                " comes through the hedge.\n");
	        TP->move_living("M", CAMP_DIR +"path26",1);
	   
            return 1;
        }
//        else
//        write("You do not see any "+str+" to enter here.\n");
//        return 1;
    }
    notify_fail("Enter what? You don't see any way to do that here.\n");
    return 0;
}
