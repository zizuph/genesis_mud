inherit "/std/room";
inherit "/cmd/std/command_driver";

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/common/defs.h"
#include "defs.h"
#include <cmdparse.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>
#include "/d/Cirath/common/teamer.h"

#define GLANCEOUT (CAMP + "c1.c")

void
create_room()
 {
  set_short("Walkway on the Gith Fortress");
  set_long("You are at the northern point of the walkway that skirts "
  	+"the gith encampment.  A low battlement is here to protect "
  	+"anyone standing here.  You can glance over the wall to see "
  	+"if anything is going on outside the front of the fortress.\n");
  add_item(({"mountainside","mountain"}),"The mountain looms to the south, "
  	+"its flat face stretching up above the towers situated against "
  	+"it, before becoming covered in small rocky outcroppings.\n");
  add_item("wall","It is a large sanstone wall circling the gith "
  	+"camp.  There is a narrow walkway atop it that you are "
  	+"standing on.\n");
  add_item("ladder","It is cut into the surface of the tower itself "
  	+"with hardly enough room for your foot to fix in the hole.\n");
  add_item(({"shelters","tents"}),"They are scattered through out the "
        +"fortress, mainly "
        +"against the inside of the stone walls of the fortress.  It looks "
        +"as if they could house a large number of gith.  You might be able "
        +"to get inside them somehow.\n");
  add_item("walkway","You are standing on top of a narrow walkway atop "
  	+"the wall of the gith fortress.\n");
  add_item(({"towers","tall towers","tower"}),"These two tall stone towers "
  	+"stretch up against the side of the mountain behind them like "
  	+"two thin reeds.\n");
  add_item("valley","The rocky valley leads away to the north.\n");
  
  add_exit(CAMP + "c29","southwest");
  add_exit(CAMP + "c28","southeast");
  set_alarm(1.0,0.0,"reset_room");
}
void
reset_room()
{
    if (leader) return;
  bring_room_team(GITH_NPC+"gith2",1,1,GITH_NPC+"gith2",1);

}
void
init()
{
    ::init();
    add_action("glance", "glance");
}

mixed
return_obj_in_seats()
{
    return (all_inventory(TO));
}

int
glance(string str)
{
    object glancee, *inv, *obs, *ppl;
    string desc, *ctants;
    int i;

    if (!strlen(str))
    {
        write(GLANCEOUT->long());
           inv = (GLANCEOUT->return_obj_out());
 //             obs = FILTER_SHOWN(FILTER_DEAD(inv));
        ppl = FILTER_LIVE(inv);

        if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
        write(desc + ".\n");

        if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
        write(desc + ".\n");

        for (i = 0; i < sizeof(ppl); i++)
        {
            ctants = map(ppl[i]->query_enemy(-1), "fights", this_object(),
            ppl[i]);

            if (sizeof(ctants))
            ctants -= ({ 0 });

            if (sizeof(ctants) == 1)
              desc = LD_FIGHT1(ctants[0]);
            else if (sizeof(ctants) > 1)
              desc = LD_FIGHT_MANY(ctants);
            else
              desc = 0;

            if (desc)
              write(LD_FIGHT_DESC(desc, ppl[i]));
         }
         return 1;
    }

    if(glancee = (GLANCEOUT->return_out(str)))
    {
        write(glancee->long());
        return 1;
    }
    write("Glance at what?\n");
    return 1;
}

object
return_out(string what_be_here)
{
    object *thing_list;
    if(!sizeof(thing_list=(FIND_STR_IN_OBJECT(what_be_here, TO))))
        return 0;
    return thing_list[0];
}

mixed
return_obj_out()
{
     return (all_inventory(TO));
}

