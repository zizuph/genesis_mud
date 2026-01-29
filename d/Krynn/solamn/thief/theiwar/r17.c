/* created by Aridor 05/19/94 */

#include "../local.h"

inherit LIGHTDARKROOM;

#include RND_MEET

object dwarf, form;

void
reset_ld_room()
{
    if (!dwarf)
      {
	  dwarf = RANDOM_MEET(THEIWARTABLE);
	  dwarf->move_living("xxx",TO);
	  DOORROOM->add_inhabitant(dwarf);
      }
    if (!form || form->query_prop(OBJ_I_BROKEN))
      {
	  form = clone_object(OBJ + "formblock");
	  form->set_produce(OBJ + "hammer2");
	  form->move(TO,1);
      }
}

void
create_ld_room()
{
    set_short("In the livingquarters");
    set_long("@@my_long");
    
    add_exit(THEIWAR + "r19", "southeast");
    
    add_item(({"bed","stone bed"}),
	     "It's a normal bed, but made from stone.\n");
    add_item(({"furniture","chair","table","board"}),
	     "It looks normal, except for the fact that it's " +
	     "made from stone.\n");
    add_item(({"floor","ceiling","wall","walls","rock"}),
	     "It's hard rock.\n");
    
    reset_room();
}


string
my_long()
{
    return "You are in a chamber that looks like the living quarters " +
      "of a dwarf. There is a stone bed and some furniture made from " +
      "stone here, a chair, table and a board.\n";

}

