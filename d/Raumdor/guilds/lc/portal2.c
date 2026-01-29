/*
 * Temporary portal, connecting the clubs to Sparkle and vice
 * versa. - Nerull.
 */

inherit "/std/object";

#include <ss_types.h>
#include <stdproperties.h>

#define  GCIN    "/d/Raumdor/guilds/gc/room/join"
#define  GCOUT   "/d/Raumdor/open/projects/office"

#define  LCIN    "/d/Shire/anduin/east/rd05"
#define  LCOUT   "/d/Raumdor/open/projects/office"

void
destroy_port()
{
    tell_room(environment(this_object()), "The "
    +this_object()->query_short() + " suddenly " +
    "collapses into itself and vanishes!\n");
    
    remove_object();
}




create_object()
{

    set_name("portal");
    add_name("_portal1");
    set_adj("huge");
    add_adj("red");
    set_short("huge red portal");
    set_long("This is a huge red portal which has a peculiar " +
    "two-dimensional surface rising from the " +
    "ground resembling the shape of a whirling maelstrom. It is " +
    "simply red, no variation in colour and no dirt " +
    "clinging to it.\n");
    add_prop(OBJ_I_VALUE, 80000);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_RES_MAGIC, 100);

    //set_alarm(90.0,0.0, &destroy_port());
}



int
do_port(string str)
{
        
    if(str != "portal")
    {
        write("enter portal, perhaps?\n");
        return 1;
    }


    tell_room(LCOUT, this_player()->query_name()
    +" arrives in a puff of smoke!\n", this_player());
        
    tell_room(environment(this_object()), this_player()->query_name()
    +" enters the "+short()+"!\n", this_player());
                
    this_player()->move_living("M", LCOUT, 1);
    
    return 1;
}



void
init()
{
    ::init();
    add_action(do_port, "enter");
}

