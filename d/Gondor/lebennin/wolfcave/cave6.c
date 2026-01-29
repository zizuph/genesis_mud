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

int n = 0;

void reset_room();

void
create_gondor() 
{
    set_short("northeastern part of a large network of caves");
    set_long(BSN("Part of a large network of caves, this particular section "+
        "is seemingly devoid of life. Rocks and twigs are scattered about "+
        "the floor, dragged in here by something. A pile of debris is lodged "+
        "in one corner of the area. The caves extend farther to the northwest, "+
        "while it is possible to head back out of the caves to the southwest "+
        "and the southeast."));

    add_item(({"rocks","twigs"}),BSN("Not very interesting, just normal rocks and twigs with tiny scratch marks."));
    add_item(({"marks"}),"@@mark_func");
    add_item(({"ceiling"}),BSN("The ceiling is composed of time worn rock."));
    add_item(({"floor"}),BSN("The floor is composed of time worn rock, although there are some tiny marks in it."));
    add_item(({"walls","wall"}),BSN("Composed of time worn rock, there are occasional patches of moss on the walls."));
    add_item(({"patches","patch","moss"}),BSN("A rather common moss, it is slighty phosphorescent."));
    add_item(({"pile","debris","pile of debris"}),
    BSN("This pile of debris is lodged in a small corner of the area,  "+
        "protected from feet and the elements. Who knows what treasures it "+
        "might hold."));

    add_exit(LEB_DIR + "wolfcave/wcave4","northwest",0);  
    add_exit(LEB_DIR + "wolfcave/cave5","southwest",0);
    add_exit(LEB_DIR + "wolfcave/cave4","southeast",0);  
    add_prop(ROOM_I_TYPE,ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT,random(2));  
    add_prop(ROOM_I_INSIDE,1);           
    add_prop(OBJ_I_SEARCH_TIME,2+random(3));
    add_prop(OBJ_S_SEARCH_FUN,"do_search");

    reset_room();
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

string
do_search(object player, string str) 
{
    object sak,
           gem;

    if (!strlen(str) || ((str != "debris") && (str != "here") && 
        (str != "pile of debris") && (str != "in debris") ) )
    {
        NFN("Search where?");
        return 0;
    }

    NFN("You search through some debris for a while, but you do not "
        + "find anything of interest.");

    if (TP->query_skill(SS_AWARENESS) < (20 + random(21)))
        return 0;

    if (n-- > 0)
    {
        seteuid(getuid(TO));
        sak = clone_object(EDORAS_DIR + "obj/bag");
        gem = clone_object(OBJ_DIR + "gems");
        gem->set_gem_type("amber");
        gem->set_heap_size(1 + random(3));
        if (gem->move(sak))
            gem->move(sak, 1);
        gem = clone_object(OBJ_DIR + "gems");
        gem->set_gem_type("agate");
        gem->set_heap_size(1 + random(2));
        if (gem->move(sak))
            gem->move(sak, 1);
        sak->move(TO);
        SAY(" searches through some debris and finds a dirty bag!");
        return BSN("After some time, you discover a dirty bag buried in the debris!");
    }

    return 0;
}

void 
reset_room()
{
    if (!n && !random(2))
        n = 1;
}
