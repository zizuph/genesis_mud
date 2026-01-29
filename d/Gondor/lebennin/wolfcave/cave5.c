inherit "/d/Gondor/common/room";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"


void
create_room() {
    set_short("Central part of a large network of caves");
    set_long(BSN("The oddest cave amoung many, this cave has unusual walls "+
        "and is crowded with pillars. Rocks and twigs are scattered about "+
        "the floor, combining with the pillars to make walking room scarce "+
        "and footing treacherous. Passageways slip out between the pillars "+
        "deeper into the caves to the northwest, northeast, west, and east, "+
        "and back out of the caves to the southwest and southeast."));

    add_item(({"rocks","twigs"}),BSN("Not very interesting, just normal rocks and twigs with tiny scratch marks."));
    add_item(({"marks"}),"@@mark_func");
    add_item(({"ceiling"}),BSN("The ceiling is composed of time worn rock."));
    add_item(({"floor"}),BSN("The floor is composed of time worn rock, although there are some tiny marks in it."));
    add_item(({"walls","wall"}),BSN("The walls are unusual in that each seems "+
        "to be formed of the original smoother walls, covered over almost "+
        "completely by growths of moss, and pillars that grew so close "+
        "to the walls they eventually merged with the walls, giving them a "+
        "rippled look."));
    add_item(({"pillar","pillars"}),BSN("Not true pillars, these formed when "+
        "the stalagmites and stalactites grew so big and long they touched "+
        "each other and then eventually grew together, and now appear to be "+
        "solid pillars of stone."));
    add_item(({"patches","patch","moss"}),BSN("A rather common moss, it is slighty phosphorescent."));

    add_exit(LEB_DIR + "wolfcave/wcave3","northwest",0);  
    add_exit(LEB_DIR + "wolfcave/cave6","northeast",0);
    add_exit(LEB_DIR + "wolfcave/wcave2","west",0);
    add_exit(LEB_DIR + "wolfcave/cave4","east",0);
    add_exit(LEB_DIR + "wolfcave/wcave1","southwest",0);  
    add_exit(LEB_DIR + "wolfcave/cave3","southeast",0);
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

