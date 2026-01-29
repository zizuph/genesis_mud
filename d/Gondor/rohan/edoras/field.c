/*
 * A field in Edoras
 *
 * Revision history:
 * /Mercade, 26 November 1993; enhanced the bag-manipulation.
 *
 * 01 march 2007, Toby: Added some items as per typo log (entry in early 2005 ^^ )
 */

inherit "/d/Gondor/common/lib/town";

#include <macros.h>
#include "/d/Gondor/defs.h"

// Prototype
void reset_room();

int    hittat;
object bgate, *guard = allocate(2);

void
create_room()
{
    hittat = 0; 
    hillside = "east";
    height = 1;
    road = 0;
    density = 1;
    extraline = "This is a green field of grass, where Rohirrim keep their proud horses, the Mearas. " +
    "The ground seems soft here. Kingsroad is to the west, and on all other sides of the field you " +
    "can see the city wall. To the north, a stone building stands with its back to the wall.";

    add_item(({"wall","walls","city wall"}),
       "The city wall is made from big solid stones. It is well guarded and definitely impossible to climb.\n");
    add_item(({"building","barracks"}),
       "It is a low building which uses the city wall as its northern wall. The thatched roof slopes down from the wall " +
       "to the field in front of the building. Almost in the middle of the building's front side, there is a large " +
       "iron gate. Some of the small windows  have iron bars in front of them. All in all it looks a lot like a prison, " +
       "but it could as well be military barracks.\n");
    add_item(({"ground","grass","earth"}), "The ground is covered with thick dark green grass. It is very soft. \n");
    add_item(({"field", "green field", "grassy field"}), "It is a field of grass, taller in places but mostly " +
       "shorter. It is where the Rohirrim keep their proud horses. The ground is quite soft here.\n");
    add_item(({"house","houses"}), "They are regular houses of Rohan, nothing special about them.\n");

    add_exit(EDORAS_DIR + "path1","west",0);
    add_exit(EDORAS_DIR + "rooms/stable","south",0);

    bgate = clone_object(EDORAS_DIR + "rooms/fieldgate");
    bgate->move(TO);
    make_the_room();

    reset_room();
}

void
init()
{
    add_action("do_dig","dig");
    ::init();
}

// Clone some guards here in stead of a marh
void
reset_room()
{
    int i = sizeof(guard);

    while(i--)
	if (!objectp(guard[i]))
	{
	    guard[i] = clone_object(EDORAS_DIR + "npc/rguard");
	    guard[i]->arm_me();
	    guard[i]->move_living("away", TO);
	}

    // Reset the quest
    hittat = 0;
    /*
       object horse;
       if(!present("horse",TO))
       {
	  horse =clone_object(EDORAS_DIR + "npc/mearas");
	  horse->move(TO);
       }
     */
}

int
do_dig(string str)
{
    object sak,
    gem;

    if(!str||str=="ground" || str == "here" || str == "in ground" ||str=="grass")
    {
	if(hittat==0)
	{
	    write("You dig in the ground and find a dirty bag.\n");
	    say(QCTNAME(TP)+" digs in the ground and finds something.\n");
	    seteuid(getuid(TO));
	    sak = clone_object("/d/Gondor/rohan/edoras/obj/bag");
	    gem = clone_object("/d/Gondor/common/obj/gems");
	    gem->set_gem_type("amber");
	    gem->set_heap_size(1 + random(3));
	    gem->move(sak, 1);
	    clone_object(EDORAS_DIR + "obj/fknife")->move(sak, 1);
	    sak -> move(TO);
	    hittat=1; 
	}
	else
	{
	    write("You dig in the ground but you don't find anything.\n");
	    SAY(" digs and gets " + POSSESSIVE(TP) + " fingers dirty.");
	}
	return 1;
    }

    NFN0("Dig where?");
}
