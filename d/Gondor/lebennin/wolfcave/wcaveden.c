/*
 * /d/Gondor/lebennin/wolfcave/wcaveden.c
 *
 *
 *
 * Revision history:
 * Updated code - 05/06/96 - By Boron
 */
inherit "/d/Gondor/common/room";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

object wolf;
int n;
void reset_room();

void
create_room()
{
    set_short("Northwestern part of a large network of caves");
    set_long(BSN("Deep within a large network of caves, this cave is unique "+
        "when compared to the others. The floor is fairly smooth and bare, "+
        "aside from a collection of branches and some debris piled up against "+
        "a natural stone column. Sparkling stalactites jut down from "+
        "the ceiling like so many jagged teeth. A narrow passageway leads "+
        "to the east out of the cave."));

    add_item(({"marks"}),"@@mark_func");
    add_item(({"ceiling"}),BSN("The ceiling is composed of time worn rock."));
    add_item(({"floor"}),BSN("The floor is composed of time worn rock, although there are some tiny marks in it."));
    add_item(({"walls","wall"}),BSN("Composed of time worn rock, there are occasional patches of moss on the walls."));
    add_item(({"patches","patch","moss"}),BSN("A rather common moss, it is slighty phosphorescent."));
    add_item(({"pile","debris","pile of debris"}),
    BSN("The debris is thickly piled up against the column where it "+
        "fuses with the wall. The debris almost appears to have been "+
        "deliberately piled up there."));
    add_item(({"column"}),BSN("Actually a tremendous stalactite that has "+   
        "fused to the wall."));
    add_item(({"stalactites","stalactite","teeth","sparkling stalactites"}),
        BSN("Amazing formations of living rock, these stalactites have "+
        "undoubtedly seen many strange and wonderous things."));
    add_item(({"branches","branch"}),BSN("Oddly shaped branches, some are "+
        "curved and thin, others thicker and rounded at the end. All have "+
        "odd marks upon them, however, and they lay tumbled about like a "+  
        "stretched out man, just to the side of the column."));

    add_exit(LEB_DIR + "wolfcave/wcave5","east",0);  
    add_prop(ROOM_I_TYPE,ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT,-(random(2)));
    add_prop(ROOM_I_INSIDE,1);           
    add_prop(OBJ_I_SEARCH_TIME,2+random(3));
    add_prop(OBJ_S_SEARCH_FUN,"do_search");

  enable_reset();
  reset_room();
}

string   
mark_func() 
{
/* depending on intelligence and tracking and awareness, the player might get a  */
/* bonus clue as to what is in this cave. The caves are mostly for newbies.      */
    string rt_text;
    rt_text = " bends down to study the markings on the branches and floor.";
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
    object sak;

    if(!str || (str != "debris" && str != "here" && str != "pile of debris" && 
        str != "in debris") )
    {
        NF("Search where?\n");
        return 0;
    }

    if(present("_wolf_dad",TO))
        return BSN("You try to search the den, but the wolf stops you from doing it thoroughly.");

    if(n>0)
    {
        seteuid(getuid(TO));
        sak=clone_object(LEB_DIR + "obj/chest");
        clone_object(LEB_DIR + "obj/silverware")->move(sak);
        clone_object(LEB_DIR + "obj/plates")->move(sak);
        clone_object(LEB_DIR + "obj/goblet")->move(sak);
        clone_object(LEB_DIR + "obj/sernote")->move(sak);
        sak->move(TO);
        SAY(" searches through some debris and finds a battered chest!");
        n--;
        return BSN("After some time, you discover a battered chest carefully hidden in the debris!");
    }
    return 0;
}

add_wolfdad()
{
  if(!objectp(wolf))
  {
    wolf = clone_object(LEB_DIR + "wolfcave/wolfdad");
    wolf->move(this_object());
    tell_room(TO,"A lanky grey wolf bounds into the area.\n");
  }
}

void reset_room()
{
    set_alarm(1.0, 0.0, add_wolfdad);
    n = 1;
}

