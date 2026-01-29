inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

string mark_func();
int    leave_me();

public void
create_gondor()
{
    set_short("southern part of a large network of caves");
    set_long(BSN("Part of a large network of caves, this particular section "+
        "is seemingly devoid of life. Rocks and twigs are scattered about "+
        "the floor. A forbidding overhang virtually hides these caves, and "+
        "very effectively blocks the view out."));

    add_item("overhang", "A solid rock formation over the entrance.\n");
    add_item(({"rocks","twigs"}), 
	"Not very interesting, just normal rocks and twigs with tiny scratch marks.\n");
    add_item(({"marks"}), mark_func);
    add_item(({"ceiling"}), "The ceiling is composed of time worn rock.\n");
    add_item(({"floor"}), "The floor is composed of time worn rock, although " +
	     "there are some tiny marks in it.\n");
    add_item(({"walls","wall"}), "Composed of time worn rock, there are " +
	     "occasional patches of moss on the walls.\n");
    add_item(({"patches","patch","moss"}), 
	     "A rather common moss, it is slighty phosphorescent.\n");

    add_exit(LEB_DIR + "wolfcave/cave2","north",0);  
    add_exit(LEB_DIR + "road/wqfield5","southeast", leave_me, 2);  
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, random(2));  
    add_prop(ROOM_I_INSIDE, 1);           
}

string
mark_func()
{
    /* depending on intelligence and tracking and awareness, the player might get a 
       bonus clue as to what is in this cave. The caves are mostly for newbies. */
    string rt_text = " bends down to study the markings on the rocks, twigs, and floor.";
    say(({ BSN(METNAME + rt_text), BSN(ART_NONMETNAME + rt_text),
        BSN(UNSEEN_NAME + rt_text) }));
    if ((TP->query_skill(SS_AWARENESS) + TP->query_skill(SS_TRACKING) + 
	 TP->query_stat(SS_INT)) > 35)
    {    
	return BSN("Studying the marks, you make them out to be claw and teeth "+
            "marks from wolves. From the marks, you can tell that at least one " +
            "very large and powerful wolf roams these caves, and a few cubs too.");
    }
    return BSN("If only you were a bit smarter and wiser in woodcraft, you "+
	       "might be able to tell something more.");
}

int 
leave_me()
{
    write("You breath a sigh of relief as you deeply inhale some fresh air.\n");
    return 0;
}
