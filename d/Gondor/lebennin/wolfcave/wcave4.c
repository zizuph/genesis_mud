/*
 * Revision Feb 2000 Stern: adapted to genesis gem system
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define GEM_DIR "/d/Genesis/gems/obj/"

public string   mark_func();

int n;

void reset_room();

public void
create_gondor() 
{
    set_short("northern part of a large network of caves");
    set_long(BSN("Part of a large network of caves, growls echo from "+
        "the ceiling and walls here. Rocks and twigs are scattered about "+
        "the floor, apparently dragged here by something. A pile of debris is "+
        "lodged in a corner of the cave. Narrow passageways lead to the "+
        "southwest and southeast. Some larger branches lay sprawled "+
        "about the floor in an oddly familiar pattern."));
    
    add_item(({"rocks","twigs"}), "Not very interesting, just normal "
	     + "rocks and twigs with tiny scratch marks.\n"); 
    add_item(({"branches","pattern","branch"}), BSN("These branches "
	+ "are a dull, yellowed white, and oddly shaped. The pattern "
        + "vaguely resembles that of a human being laying spread-eagle."));
    add_item(({"marks"}), mark_func);
    add_item(({"ceiling"}), "The ceiling is composed of time worn rock.\n");
    add_item(({"floor"}), "The floor is composed of time worn rock, "
	     + "although there are some tiny marks in it.\n"); 
    add_item(({"walls","wall"}), "Composed of time worn rock, there "
	     + "are occasional patches of moss on the walls.\n"); 
    add_item(({"patches","patch","moss"}), "A rather common moss, it "
	     + "is slighty phosphorescent.\n"); 
    add_item(({"pile","debris","pile of debris"}),
	     BSN("This pile of debris is lodged in a small corner of "
		 + "the area, protected from feet and the "
		 + "elements. Who knows what treasures it might hold."));

    add_exit(LEB_DIR + "wolfcave/wcave3","southwest",0);  
    add_exit(LEB_DIR + "wolfcave/cave6","southeast",0);
    add_prop(ROOM_I_TYPE,ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT,random(2));  
    add_prop(ROOM_I_INSIDE,1);           
    add_prop(OBJ_I_SEARCH_TIME, 2+random(3));
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    reset_room();
}

public string   
mark_func() 
{
/* depending on intelligence and tracking and awareness, the player might get a  */
/* bonus clue as to what is in this cave. The caves are mostly for newbies.      */
    string rt_text;
    rt_text = " bends down to study the markings on the rocks, twigs, and floor.";
    SAY(rt_text);
    if((TP->query_skill(SS_AWARENESS)+TP->query_skill(SS_TRACKING)+TP->query_stat(SS_INT))>35)
    { 
        return BSN("Studying the marks, you make them out to be claw and teeth "+
            "marks from wolves. From the marks, you can tell that at least one very "+       
            "large and powerful wolf roams these caves, and a few cubs too.");
    }
    return BSN("If only you were a bit smarter and wiser in woodcraft, you "+
        "might be able to tell something more.");
}

public string
do_search(object player, string str) 
{
    object  sack,
            gem;

    if(!str || (str != "debris" && str != "here" && str != "pile of debris" && 
        str != "in debris") )
    {
        NFN("Search where?");
        return 0;
    }

    if (n > 0)
    {
        seteuid(getuid(TO));
        sack = clone_object(LEB_DIR + "obj/sack");
        clone_object(LEB_DIR + "obj/corpants")->move(sack, 1);
        (gem = clone_object(GEM_DIR + "onyx"))->move(sack, 1);
        sack->move(TO);
        SAY(" searches through some debris and finds a soiled sack!");
        n--;
        return BSN("After some time, you discover a soiled sack buried in the debris!");
    }
    return 0;
}

void 
reset_room()
{
    if (!n && !random(2))
        n = 1;
}
