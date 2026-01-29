inherit "/d/Gondor/common/room";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define WEAPONS ({WEP_DIR+"knife",WEP_DIR+"stick",WEP_DIR+"fssword",\
                  WEP_DIR+"qstaff",WEP_DIR+"hatchet",EDORAS_DIR+"obj/fknife",})
void add_stuff();

void
create_room() {
 
    set_short("Northwestern part of a large network of caves");
    set_long(BSN("Part of a large network of caves, this cave bears evidence "+
        "of frequent travel. Rocks and twigs are scattered about "+
        "the floor, dragged in here by something. A collection of leaves lies "+
        "strewn about the floor. A wide passageway leads to the west. "+
        "Other passageways head towards the rest of the caves, leading "+
        "south and southeast."));

    add_item(({"rocks","twigs"}),BSN("Not very interesting, just normal rocks and twigs with tiny scratch marks."));
    add_item(({"marks"}),"@@mark_func");
    add_item(({"ceiling"}),BSN("The ceiling is composed of time worn rock."));
    add_item(({"floor"}),BSN("The floor is composed of time worn rock, although there are some tiny marks in it."));
    add_item(({"walls","wall"}),BSN("Composed of time worn rock, there are occasional patches of moss on the walls."));
    add_item(({"patches","patch","moss"}),BSN("A rather common moss, it is slighty phosphorescent."));
    add_item(({"leaves","collection of leaves"}),BSN("A variety of colors and "+
        "shapes forms this collection of leaves."));

    add_exit(LEB_DIR + "wolfcave/wcaveden","west",0);  
    add_exit(LEB_DIR + "wolfcave/wcave2","south",0);  
    add_exit(LEB_DIR + "wolfcave/wcave3","southeast",0);
    add_prop(ROOM_I_LIGHT,random(2));  
    add_prop(ROOM_I_INSIDE,1);           
  add_prop(ROOM_I_NO_CLEANUP,1);
  enable_reset();
  add_stuff();
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

void
add_stuff()
{
  object weapon;
  if(!present("_hidden_weapon",TO))
  {
    weapon = clone_object(WEAPONS[random(sizeof(WEAPONS))]);
    weapon->add_name("_hidden_weapon");
    weapon->add_prop(OBJ_I_HIDE,5+random(10));
    weapon->move(TO);
  }
}

reset_room()
{
  add_stuff();
}
