/*
 * /d/Gondor/lebennin/wolfcave/wcave2.c
 *
 *
 * Revision history:
 * modified by Olorin, 5-jun-1993
 * inserted a check for no_of_rats in make_rat()
 * Updated code - 05/06/96 - By Boron
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define MAX_RATS 5 /* max number of rats running around */
#define WEAPONS ({WEP_DIR+"knife",WEP_DIR+"stick",WEP_DIR+"fssword",\
                  WEP_DIR+"qstaff",WEP_DIR+"hatchet",EDORAS_DIR+"obj/fknife",})

public string  mark_func();
public void    reset_room();

int     n,
        alarm_id,
        no_of_rats;
object *rats = allocate(MAX_RATS);

public void
create_gondor()
{
    set_short("western part of a large network of caves");
    set_long(BSN("Part of a large network of caves, this particular section "+
        "is seemingly devoid of life. Rocks and twigs are scattered about "+
        "the floor, dragged in here by something. A collection of leaves lies "+
        "strewn about the floor. The caves extend farther to the north, northeast, "+
        "and east, while it is possible to head towards the entrance "+
        "of the caves to the southeast."));
    add_item(({"rocks","twigs"}), "Not very interesting, just normal rocks " +
	     "and twigs with tiny scratch marks.\n");
    add_item(({"marks"}), mark_func);
    add_item(({"ceiling"}), "The ceiling is composed of time worn rock.\n");
    add_item(({"floor"}), "The floor is composed of time worn rock, although " +
	     "there are some tiny marks in it.\n");
    add_item(({"walls","wall"}), "Composed of time worn rock, there are " +
	     "occasional patches of moss on the walls.\n");
    add_item(({"patches","patch","moss"}), "A rather common moss, it is " +
	     "slighty phosphorescent.\n");
    add_item(({"leaves","collection of leaves"}),
	     "A variety of colors and shapes forms this collection of leaves.\n");

    add_exit(LEB_DIR + "wolfcave/wcave5","north",0);
    add_exit(LEB_DIR + "wolfcave/wcave3","northeast",0);
    add_exit(LEB_DIR + "wolfcave/cave5","east",0);
    add_exit(LEB_DIR + "wolfcave/wcave1","southeast",0);  
    add_prop(ROOM_I_LIGHT,random(2));  
    add_prop(ROOM_I_INSIDE,1);  
    add_prop(ROOM_I_NO_CLEANUP,1);
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

public void
make_rat()
{
    remove_alarm(alarm_id);
    alarm_id = 0;
    if (!objectp(rats[no_of_rats]))
    {
	rats[no_of_rats] = clone_object(NPC_DIR+"rat");
	rats[no_of_rats]->set_restrain_path(LEB_DIR + "wolfcave/");
	rats[no_of_rats]->move(TO);
	tell_room(TO,"A filthy rat squeezes out of a tiny crack in the wall.\n");
    }
    no_of_rats++;
    if (no_of_rats == MAX_RATS)
    {
	no_of_rats = 0;
	return;
    }
    if (!alarm_id)
	alarm_id = set_alarm(itof(200 + random(200)), 0.0, make_rat);
}

public void
reset_room()
{
    object  weapon;
    alarm_id = set_alarm(5.0, 0.0, make_rat);
    if (!present("_hidden_weapon", TO))
    {
	weapon = clone_object(WEAPONS[random(sizeof(WEAPONS))]);
	weapon->add_name("_hidden_weapon");
	weapon->add_prop(OBJ_I_HIDE, 5+random(10));
	weapon->move(TO);
    }
}

