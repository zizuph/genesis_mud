
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"
#include <stdproperties.h>
#include <macros.h>

#define DROPPED_HANDKERCHIEF "_i_dropped_the_handkerchief_over_the_eye"


reset_room()
{
    if(!present("_sw_ent_quest_rhosgobel_gemstone"))
    {
	clone_object(RHOS+"gemstone")->move(TO);
    }
}


init()
{
    ::init();
    add_action("drop_handkerchief", "drop");
    add_action("get_gemstone", "get");
    add_action("get_gemstone", "take");
}

create_room()
{
    set_short("Secret room");
    set_long("You are in a secret room beneath one of the "+
	"huts of Rhosgobel.  The only light here is let "+
	"in by the trap door above, dim as it is.  There "+
	"is a strange eye-like stone, perfectly round and "+
	"smooth, standing on a pedestal at one side of the "+
	"room.  You feel as though it watches your every "+
	"move.\n");
    
    AE(RHOS+"hut_sw", "up");
    
    add_item(({"eye", "stone"}), "You feel extremely conspicuous "+
	"with that eye watching you.\n");
    add_item("pedestal", "The pedestal is quite nondescript.  "+
	"You are more drawn to look at that strange eye which "+
	"sits atop it.\n");
	
    IN;
    
    reset_room();
}

int
drop_handkerchief(string str)
{
    object obj;
    
    if((str=="handkerchief on eye")||(str=="handkerchief over eye")
	||(str=="handkerchief onto eye"))
	{
	    if(!present("_sw_quest_handkerchief", TP))
	    {
		write("Drop what where?\n");
		return 1;
	    }
	    write("You drop the white handkerchief over the watching "+
		"eye.\n");
        TP->add_prop(DROPPED_HANDKERCHIEF,1);
	    obj=present("_sw_quest_handkerchief", TP);
	    obj->remove_object();
	    return 1;
	}
    return 0;
}

int
get_gemstone(string str)
{
    object obj1, obj2;
    
    if(str=="gemstone")
    {
	if(present("_sw_ent_quest_rhosgobel_gemstone"))
	{
        if(!(TP->query_prop(DROPPED_HANDKERCHIEF)))
	    {
		write("You dare not take the gemstone with that eye "+
		    "watching you from across the room!  If only there "+
		    "were some way to cover it up!\n");
		return 1;
	    }
	    write("With the eye safely covered, you take the gemstone.\n");
	    obj1=present("_sw_ent_quest_rhosgobel_gemstone");
	    obj1->remove_object();
	    obj2=clone_object(RHOS+"gemstone");
	    obj2->move(TP);
	    return 1;
	}
    }
return 0;
}
