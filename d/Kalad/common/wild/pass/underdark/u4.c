/* by Antharanos */
#include "/d/Kalad/defs.h"

#include <macros.h>
#include <filter_funs.h>
#include <ss_types.h>

#define KALAD_FOUND_DOMINION_EXIT "_kalad_found_dominion_exit"

inherit "/d/Kalad/std/room";

public void
create_kalad_room()
{
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   add_prop(ROOM_M_NO_TELEPORT,1);
   add_prop(OBJ_S_SEARCH_FUN, "search_floor");
   set_short("Cave");
   set_long("You can barely see within the dark confines of this cave. "+
      "It seems you've reached a dead end, literally. For the only thing "+
      "that lies east is a solid stone wall and just below that are the "+
      "skeletal remains of some creature.\n");
   add_item(({"solid stone wall","solid wall","stone wall","wall"}),
      "It is rough and unworked, clearly a natural cave wall.\n");
   add_item(({"skeletal remains","remains"}),"A few scattered bones of "+
      "some humanoid creature lie about the floor, it looks human but you cannot be sure that it "+
      "is.\n");
   add_item(({"floor", "ground"}),
      "The floor is relatively smooth in comparison "+
      "with the walls and seems to be more level than other sections of the "+
      "cave floor to the west.\n");
   add_exit(CPASS(underdark/u3),"west","@@check_drowwep",0);
   add_exit(CPASS(underdark/u5), "down", "@@exit_down", 1, 1);
}

public string
search_floor(object me, string arg)
{
   if (member_array(arg, ({"ground", "floor"})) < 0)
      return "";
   if (TP->query_skill(SS_AWARENESS) < 30)
      return "";

   TP->add_prop(KALAD_FOUND_DOMINION_EXIT, 1);
   return "You search the floor carefully and discover a hidden passage "
      + "leading downward!\n";
}

check_drowwep()
{
    object *ob;
    int i;
    ob = deep_inventory(TP);
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->id("drowwep"))
        {
            write("Your drow weapon disintegrates!\n");
            ob[i]->remove_object();
            return 0;
        }
    return 0;
}

int
exit_down()
{
    object *witnesses;
    if (TP->query_prop(KALAD_FOUND_DOMINION_EXIT))
    {
        witnesses = filter(FILTER_CAN_SEE_IN_ROOM(AINV(E(TP)) - ({TP})),
                TP->check_seen);
        foreach (object witness: witnesses)
        {
            if (!witness->query_prop(KALAD_FOUND_DOMINION_EXIT))
            {
                witness->add_prop(KALAD_FOUND_DOMINION_EXIT, 1);
                witness->catch_msg(QCTNAME(TP) + 
                    " uses a hidden passage!\n");
            }
        }
        check_drowwep();
        return 0;
    }
    write("There is no obvious exit down.\n");
    return 1;
}

