 
/*
 * Crumbs to feed the fish in the 
 * pool in the Telseron castle
 * By Finwe
 * March 1997
 */
 
#include "/d/Emerald/defs.h"
inherit "/std/object";
 
create_object()
{
    set_name("crumbs");
    set_short("handful of crumbs");
    set_adj( "chunky");
    set_long("This is a handful of crumbs from broken ice cream " +
        "cones. The crumbs are of various sizes and seem to " +
        "have been missed when the floor was swept.\n");
}
 
 
void
init()
{
    ::init;
    add_action("eat_crumbs", "eat");
}
 
 
eat_crumbs(string str)
{
    NF("Eat what?\n");
 
    if (str == "crumbs")
    {
        TP->catch_msg("The crumbs don't look very appetizing.\n");
        return 1;
    }
}
