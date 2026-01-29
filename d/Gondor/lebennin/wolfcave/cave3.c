inherit "/d/Gondor/common/room";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_room() {
    set_short("Southeastern part of a large network of caves");
    set_long(BSN("One of many caves in the area, this cave seems overgrown "+
        "with unusual rock formations. Rocks and twigs lay jumbled about on "+
        "the floor. Debris has become lodged between the wall and a huge "+
        "sparkling stalagmite. Tight passageways lead farther to the northwest "+
        "and northeast, and a narrowing passageway heads back to the "+
        "southwest."));

    add_item(({"rocks","twigs"}),BSN("Not very interesting, just normal rocks and twigs with tiny scratch marks."));
    add_item(({"formations","rock formations","formation","rock formation"}),
        BSN("Dull grey spikes of rock hanging from the ceiling or jutting "+
        "from the floor. Some are perfectly conical, others have many ridges "+
        "and crannies running their entire lengths."));
    add_item(({"stalagmite","huge stalagmite","sparkling stalagmite"}),
        BSN("A very large formation of living rock that has grown over the "+
        "centuries drop by crystalizing drop of mineral laden water, this "+
        "stalagmite is unusual both in size, dwarfing you easily by a few "+
        "heads, and in composition, as it is formed almost entirely of "+
        "crystal, with a few streaks of a pale, chalky stone mixed in."));
    add_item(({"marks"}),"@@mark_func");
    add_item(({"ceiling"}),BSN("The ceiling is composed of time worn rock."));
    add_item(({"floor"}),BSN("The floor is composed of time worn rock, although there are some tiny marks in it."));
    add_item(({"walls","wall"}),BSN("Composed of time worn rock, there are occasional patches of moss on the walls."));
    add_item(({"patches","patch","moss"}),BSN("A rather common moss, it is slighty phosphorescent."));
    add_item(({"pile","debris","pile of debris"}),
    BSN("This pile of debris is lodged in a small corner of the area, "+
        "protected from feet and the elements."));

    add_exit(LEB_DIR + "wolfcave/cave5","northwest",0);  
    add_exit(LEB_DIR + "wolfcave/cave4","northeast",0);
    add_exit(LEB_DIR + "wolfcave/cave2","southwest",0);  
    add_prop(ROOM_I_TYPE,ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT,random(2));  
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

