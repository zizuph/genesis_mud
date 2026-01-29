/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III */

inherit "/std/room";

#include "default.h"
#include "/d/Emerald/mountains/mtblack/cave/lichen.h"

/* Global variable */
object npc;

int taken_once;
/* Prototype function */
public void reset_room();

public void 
create_room()
{
    taken_once = 0;
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("A dark cave");    
    set_long("   "+
	     "This cave is just a tunnel, that seems to run fairly straight " +
	     "from northwest to southeast. There is very little else to say " +
	     "about the cave except to keep a look out for Ogres. There is a "+
	     "small crack in the wall here.\n\n");

    add_item("lichen", 
        "There is lichen growing on the volcanic rock. It is very fragile, " +
        "and cumbles to dust when you touch it.\n");
    add_item(({"walls","wall"}), 
        "The walls are cold, and damp to touch. It seems to be volcanic " +
        "rock that these caves are made of. Pretty hard stuff it is, too.\n" +
        "There is some lichen growing on the wall.\n");
    add_item(({"roof","ceiling"}), 
        "What little you can see above you suggests that the roof is made " +
        "of the same rock as the walls, volcanic rock. At least you can " +
        "be fairly sure the roof won't be falling down, as volcanic rock " +
        "is pretty tough stuff.\n");
    add_item(({"floor","ground"}),
        "The floor on which you are standing seems very firm, and is made " +
        "of volcanic rock. There is some lichen growing on the floor.\n");
    
    add_item( ({"crack", "small crack"}),
	     "The crack is about the size of an ogre hand. It is too "+
	     "dark inside the crack to see anything from here.\n");

#if 0
    add_prop(OBJ_S_SEARCH_FUN, "search_me");
#endif

    add_exit(THIS_DIR+"cave22c", "northwest", 0, 1);
    add_exit(THIS_DIR+"cave14c", "southeast", 0, 1);
    
    reset_room();
}

string
search_me(object ob, string str)
{
    object throne_room;
    if (str != "crack")
	return 0;

    if (!LOAD_ERR("/d/Emerald/telberin/castle/th5"))
    {
	throne_room = find_object("/d/Emerald/telberin/castle/th5");
       if (!throne_room->query_stolen())
	{
	    return "You search the hole behind the crack but "+
		"find nothing.\n";
	}
    }
    else {
	write("HUGE BUG! FIX ME!\n");
	return "HUGE HUGE BUG.\n";
    }

    if (taken_once)
    {
	return("You reach into the crack but the emptiness that greets "+
	      "your hand betrays the fact that someone has been searching "+
	      "there before you and may have taken the contents of the "+
	      "small opening.\n");
    }

    write("You reach your hand into the crack and grab hold of "+
	  "several glinting objects. They drop to the cave floor "+
	  "before you can get a better grip on them.\n");
    say(QCTNAME(ob)+" reaches "+TP->query_possessive()+" hand into "+
	"the crack and pulls out several glinting items, dropping them "+
	"to the cave floor.\n");
    taken_once = 1;

    reset_euid();

    clone_object("/d/Emerald/obj/jewelry/bracelet")->move(TO);
    clone_object("/d/Emerald/obj/jewelry/crown")->move(TO);
    clone_object("/d/Emerald/obj/jewelry/earrings")->move(TO);
    clone_object("/d/Emerald/obj/jewelry/ring")->move(TO);
    clone_object("/d/Emerald/obj/jewelry/necklace")->move(TO);

    if (present(npc))
    {
	npc->command("shout TEEF! NO STEAL ME SHINIES!");
	npc->set_aggressive(1);
        npc->attack_object(ob);
	npc->command("shout ME WANT SHINIES! NO CAN HAVE EM!");
    }
    return "It looks as though someone had hidden jewelry in that crack!\n";
}

public void
reset_room()
{
    if (!objectp(npc))
    {
        npc=clone_object(CAVE_DIR + "npc/nasty_ogre");
        npc->arm_me();
        npc->move_living("into a cave", this_object(), 1, 1);
    }

    taken_once = 0;
}

