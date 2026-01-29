/*
 * /d/Gondor/lebennin/wolfcave/cave4.c
 *
 *
 * Revision history:
 * modified by Olorin, 5-jun-1993, 
 * modified for use with wolves by Xeros, 4 Nov, 1993
 * inserted a check for no_of_wolves in make_wolf()
 * Updated code - 05/06/96 - By Arren
 */
inherit "/d/Gondor/common/room";

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MAX_WOLVES 5 /* max number of wolves running around */

object *wolves;
int no_of_wolves;
int alarm_id;

void reset_room();

void
create_room()
{
 
    set_short("Eastern part of a large network of caves");
    set_long(BSN("Part of a large network of caves, this particular section "+
        "is seemingly devoid of life. Rocks and twigs are scattered about "+
        "the floor, dragged in here by something. A collection of leaves lies "+
        "scattered about the floor. The caves extend farther to the northwest "+
        "and west, while it is possible to head towards the entrance "+
        "of the caves to the southwest."));

    add_item(({"rocks","twigs"}),BSN("Not very interesting, just normal rocks and twigs with tiny scratch marks."));
    add_item(({"marks"}),"@@mark_func");
    add_item(({"ceiling"}),BSN("The ceiling is composed of time worn rock."));
    add_item(({"floor"}),BSN("The floor is composed of time worn rock, although there are some tiny marks in it."));
    add_item(({"walls","wall"}),BSN("Composed of time worn rock, there are occasional patches of moss on the walls."));
    add_item(({"patches","patch","moss"}),BSN("A wolfher common moss, it is slighty phosphorescent."));
    add_item(({"leaves","collection of leaves"}),BSN("A variety of colors and "+
        "shapes forms this collection of leaves."));

    add_exit(LEB_DIR + "wolfcave/cave6","northwest",0);  
    add_exit(LEB_DIR + "wolfcave/cave5","west",0);
    add_exit(LEB_DIR + "wolfcave/cave3","southwest",0);  
    add_prop(ROOM_I_LIGHT,random(2));  
    add_prop(ROOM_I_INSIDE,1);           
    add_prop(ROOM_I_NO_CLEANUP,1);
    wolves = allocate(MAX_WOLVES);
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


make_wolf()
{
   remove_alarm(alarm_id);
   alarm_id = 0;
  if(!objectp(wolves[no_of_wolves]))
  {
    wolves[no_of_wolves] = clone_object(LEB_DIR+"wolfcave/wolfcub");
    wolves[no_of_wolves]->set_restrain_path(LEB_DIR + "wolfcave/cave");
    wolves[no_of_wolves]->move(TO);
    tell_room(TO,"A fuzzy wolf cub tumbles into the room.\n");
  }
  no_of_wolves++;
  if(no_of_wolves == MAX_WOLVES)
  {
    no_of_wolves = 0;
    return;
  }
   if (!alarm_id)
       alarm_id = set_alarm(itof(200 + random(200)), 0.0, make_wolf);
}

void
add_stuff()
{
    alarm_id = set_alarm(5.0, 0.0, make_wolf);
}

void 
reset_room()
{
    add_stuff();
}
