
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
    reset_euid();

    if(!find_living("_castle_guard_entry"))
    {
        object guard;
	guard=clone_object(RHUN+"npc/castle_guard");
        guard->set_living_name("_castle_guard_entry");
        guard->move(TO);
    }
}

create_room()
{
    set_short("Castle entry");
    set_long("You are at the entry to a ruined castle.  The "+
	"gate that once hung here has long since eroded away, leaving "+
	"only rusted hinges to mark its passing.  You stand on the "+
	"threshold of the imposing brick building, with its walls "+
	"rising up above high above you.  The winds whip through "+
	"the passes of these mountains with an unnatural ferocity.  "+
	"You may head out into the wind to the south, following a "+
	"narrow mountain path, step inside to the ruined castle's "+
	"entryway to the north.\n");

    add_item(({"gate", "hinges"}), "A large, sturdy gate must once "+
	"have hung here, guarding the castle's entrance.  Now, "+
	"nothing remains of it save some old, rusted hinges.\n");
    add_item(({"building", "brick", "wall", "walls", "castle"}), 
	"You are standing just at the entrance to a tall castle of "+
	"grey stone.  Its walls rise up above you quite high.  You "+
	"may head inside by going north from here.\n");
    add_item(({"south", "path"}), "A narrow dirt path winds its "+
	"slow way along the mountain ledges, heading southward from "+
	"here.\n");

    AE(RHUN+"castle/entryway","north");
    AE(RHUN+"hills/p6","south");

    reset_room();

}

