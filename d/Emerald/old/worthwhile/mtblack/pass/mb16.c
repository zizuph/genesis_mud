/* MB16.c, the pass over Mt. Black*/
/* Geraden 22 January 1997 */

#include "/d/Emerald/defs.h"

inherit MBLACK_DIR + "pass/pass_common";

void
create_pass()
{
	set_short("A trail near the summit of Mt. Black");
    add_my_desc("The path here becomes very narrow as it passes "+
           "a large thicket of blackberry bushes on the east "+
           "side of the path.\n\n");

   add_prop(OBJ_S_SEARCH_FUN, "search_exit");

   add_item(({"bushes", "thicket", "blackberries"}), "Looking "+
           "closely at the bushes you can see that there are "+
           "very few berries left, probably due to the recent "+
           "cold weather. If you search carefully you might find "+
           "some though.\n");
	add_exit(MBLACK_DIR + "pass/mb17", "north",0,0);
	add_exit(MBLACK_DIR + "pass/mb15", "southwest",0,0);
}

string
search_exit(object player, string str)
{
    if ( str == "bushes" )
     {
       if ( (member_array("east", query_exit_cmds()))!=-1)
        {
           return("Your search reveals nothing more.\n");
         }
       add_exit(ESMIRIN_DIR + "/roads/eroad/er01", "east");
	write_file("/d/Emerald/esmirin/bushes",TP->query_name()+ 
	" found the secret entrance to Esmirin on "
     + ctime(time()) + ".\n");
        return("You search the bushes, but rather than berries "+
	       "you have found a hidden path leading east "+
	       "through the bushes!\n");
	

     }
    return 0;
}


void
reset_room()
{
    tell_room(this_object(), "A gentle wind rustles through "+
              "the bushes.\n");
     remove_exit("east");

    // this will re-hide the exit.
}
