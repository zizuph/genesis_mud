inherit "/d/Gondor/common/room";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"


void
create_room() {
    set_short("Central part of a large network of caves");
    set_long(BSN("Part of a large network of caves, this particular section "+
        "is seemingly devoid of life. Rocks and twigs are scattered about "+
        "the floor, dragged in here by something. A collection of leaves lies "+
        "strewn across the floor. The caves extend farther to the northwest "+
        "and northeast, while it is possible to head back out of the "+
        "caves to the southwest and southeast."));

    add_item(({"rocks","twigs"}),BSN("Not very interesting, just normal rocks and twigs with tiny scratch marks."));
    add_item(({"marks"}),"@@mark_func");
    add_item(({"ceiling"}),BSN("The ceiling is composed of time worn rock."));
    add_item(({"floor"}),BSN("The floor is composed of time worn rock, although there are some tiny marks in it."));
    add_item(({"walls","wall"}),BSN("Composed of time worn rock, there are occasional patches of moss on the walls."));
    add_item(({"patches","patch","moss"}),BSN("A rather common moss, it is slighty phosphorescent."));
    add_item(({"leaves","leaf","collection","collection of leaves"}),
        BSN("A variety of colors and shapes forms this collection of leaves."));

    add_exit(LEB_DIR + "wolfcave/wcave5","northwest",0);  
    add_exit(LEB_DIR + "wolfcave/wcave4","northeast",0);
    add_exit(LEB_DIR + "wolfcave/wcave2","southwest",0);  
    add_exit(LEB_DIR + "wolfcave/cave5","southeast",0);
    add_prop(ROOM_I_TYPE,ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT,random(1));  
    add_prop(ROOM_I_INSIDE,1);           

}

string   
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

