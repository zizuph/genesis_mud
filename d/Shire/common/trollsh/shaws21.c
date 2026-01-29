/*
 * Moved the goblin prisoner quest back to original place, Toby May 2008 
 */

inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/
#include "defs.h"
#include "/d/Shire/private/shire_admin.h"
#include <filter_funs.h>

// #define PLAYER_HAS_FOUND    "_Shire_found_hole_in_roots"
#define MISTY_DIR           "/d/Shire/misty/"
create_shawrom()
{

    set_short("Deep in the Trollshaw. Along a path.");
    set_extraline("Here the shaws grow terribly dense. Tall evergreens " +
        "crowd together and make this place seem very narrow.");

    add_item(({"path"}),"There is a path here, going in a east-west direction.\n");
    
//    add_prop(OBJ_S_SEARCH_FUN, "search_roots");
//    add_prop(OBJ_I_SEARCH_TIME, 5);

    
    EAST("shaws20");
    WEST("shaws22");
    SOUTHWEST("shaws25");
    SOUTHEAST("shaws19");
}

/*
void
init()
{
//    init_skill_raise();
    ::init();
    add_action("enter_hole", "enter");
}

string
you_see_hole()
{
    if (TP->query_prop(PLAYER_HAS_FOUND)){
	return "You can also see a hole hidden between roots.\n";
    }
    return "";
}

string
hole_desc()
{
    if (TP->query_prop(PLAYER_HAS_FOUND))
    {
	return "This hole was well hidden among the roots. It is small but "+
	"maybe you can squeeze through it.\n";
    }
    return "You find no hole.\n";
}

string
search_roots(object searcher, string str)
{
    int sum_skills = searcher->query_skill(SS_AWARENESS);

    if((str == "roots") || (str == "tree roots"))
    {
    TELL_ADMIN(TP->query_cap_name() +" is doing Prisoner quest.");
	if(CAN_SEE_IN_ROOM(searcher))
	{
	    if(searcher->query_prop(PLAYER_HAS_FOUND))
	    {
		return "Your search reveals a hole behind some tree roots.\n";
	    }
	    if(sum_skills > 29)
	    {
		searcher->add_prop(PLAYER_HAS_FOUND, 1);
		return "You have found a hole hidden between roots.\n";
	    }
	    else
		return "Your search reveals nothing special.\n";
	}
	else
	    return "Your search reveals nothing special.\n";
    }
    return "";
}

int 
enter_hole(string hole)
{
    object *in_room=FILTER_LIVE(all_inventory(TO));
    int i;

    if((hole=="hole") && TP->query_prop(PLAYER_HAS_FOUND))
    {
	for (i = 0; i < sizeof(in_room); i++)
	    in_room[i]->add_prop(PLAYER_HAS_FOUND,1);
	TP->catch_msg("You squeeze through a hole under the roots.\n");
	say(QCTNAME(TP)+" squeezes through a hole under the roots.\n");
	tell_room(MISTY_DIR+"r2",QCTNAME(TP)+" enters through hole.\n");
	TP->move_living("M",MISTY_DIR+"r2");
	return 1;
    } 
    NF("Enter what?\n");
    return 0;
}
*/
