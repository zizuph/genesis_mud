
#include "local.h"

inherit SHIRE_ROOM;
#define BUSH_PROP "_have_found_the_animal_trail"


void
create_shire_room()
{
    set_short("The path");
    set_long("You are on the path from the lowlands which goes into the " +
        "Misty Mountains. Bushes and trees grow alongside the path, " +
        "blocking your view. To the east, the path climbs up into into the mountains.\n");
    add_item(({"path"}),
        "The path looks wide and well traveled. The ground is packed dirtand winds past trees and bushes.\n");
    add_item(({"trees", "conifer trees", "conifers", "evergreen trees", "evergreens"}),
        "The trees are ancient looking evergreens and rise above you. They block your view of almost anything around here except for the mountains.\n");
    add_item(({"misty mountains", "mountains"}),
        "They rise above you to the north and east. Their tops are white and stand above the trees.\n");

    add_exit(MISTY_DIR + "p1", "east", 0, 1);
    add_exit(ERE_DIR + "misty_link", "southwest", 0, 1);
    add_exit(MISTY_DIR + "hunter_trail01", "northwest", 0, 0, 1);

}


void
init()
{   
    ::init();
 
    add_action("enter_bushes", "enter");
}

string
exa_bush()
{
    if(TP->query_skill(SS_AWARENESS)>15)
    {   
       TP->add_prop(BUSH_PROP,1);
       write("The bushes are waist high and grow thick here. " +
       "Your keen senses notice a rough animal trail leading through the bushes. " +
       "It might be possible to enter the bushes here.\n");
    return "";
    }
    else
       write("The bushes are waist high and grow thick here. They look like they " +
       "have been trampled by wild animals that come here.\n");
       return "";
}

int
enter_bushes(string str)
{
    if(str=="bush" || str=="bushes")
    {
        if(TP->query_prop(BUSH_PROP))
        {    
            write("You push through the brush.\n");
            say(QCTNAME(TP)+" vanishes into a hidden exit somewhere.\n");
            tell_room(MISTY_DIR +"hunter_trail01",QCTNAME(TP) + " arrives.\n");
	    TP->move_living("M", MISTY_DIR +"hunter_trail01",1);
	   
            return 1;
        }
        else
        write("You do not see any "+str+" to enter here.\n");
        return 0;
    }
    notify_fail("Enter what?\n");
    return 0;
}


