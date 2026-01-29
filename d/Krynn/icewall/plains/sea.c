/* Created by Macker and Stevenson
 * 
 * last update: Aridor 10/97, fixed the seamonster
 *              to be cloned only a limited number
 *              of times per reset.
 */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <stdproperties.h>
inherit ICEOUTROOM;

int num_fish = 3;
int sea_mon = 2;

void
reset_icewall_room()
{
    if (num_fish < 3)
      num_fish = 3;
    if (sea_mon < 2)
      sea_mon = 2;
}

void
init() 
{
    ADA("enter");
    ADD("fishfunc","catch");
    ADA("drink");
    ::init();
}

void
create_icewall_room() 
{
    set_short("Sea Shore");
    set_long("You stand before the Sea of Icewall. It is very salty and pretty "
	     + "devoid of life, although an occasional fish may be seen in it. On the "
	     + "ground are small shells and residue washed in from the sea. A strange "
	     + "land is rumoured to lie somewhere out in the sea but none have ever "
	     + "returned alive to tell the tale. "
	     + "You may return to the glacier by entering the cave to the south. "
	     + "\n");
    
    add_prop(ROOM_I_TYPE,ROOM_BEACH);
    add_item("sea",
	     "It is cold and salty. Very little life can survive in it.\n");
    add_item("cave",
	     "It is just south of you.\n");
    add_item(({"shell","residue","ground"}),
	     "The ground is covered with tiny shells "
	     + "and residue washed up from who knows where.\n");
    add_item("mountain",
	     "They are south of you, blocking you off from the rest "
	     + "of the glacier.\n");
    reset_icewall_room();
}

int 
enter(string arg) 
{
    if (arg == "cave") 
    {
	write("You plug your nose and rush into the salt-filled cave.\n");
	say(QCTNAME(TP)+" runs into the cave.\n");
	TP->move_living("M",ICE_PLAINS+"plain_7",1,0);
	say(QCTNAME(TP) + " arrives from the cave entrance gasping for air.\n");
	return 1;
    }
    NF("What?\n");
    return 0;
}

int 
fishfunc(string str) 
{
    object fish, monster;
    NF("Catch what?\n");
    if (!P("icepole",TP)) 
      return 0;
    if (str != "fish" && str != "fish with pole") 
      return 0;
    if (!num_fish) 
    {
	NF("I guess they just aren't biting today.\n");
	return 0;
    }
    if (TP->test_bit("Krynn",2,17))
    {
        NF("It seems you've done enough fishing here already.\n");
        return 0;
    }
    monster = P("seamonster", TO);
    if (monster)
    {
	write("You dare cast the line out into the sea. The seamonster " +
	      "doesn't seem to like it very much.\n");
	tell_room(TO, QCTNAME(TP) + " tries to catch a fish but " +
		  "is hindered by a seamonster.\n", TP);
	monster->command("kill " + TP->query_real_name());
	return 1;
    }
    if (random(10) > 5 && sea_mon > 0)
    {
	write("You cast the line far out into the sea and "
	      + "instead of a fish jumping for it, a very hideous "
	      + "monster from the oceans depths surfaces.\n");
	tell_room(TO, QCTNAME(TP) + " tries to catch a fish but "
		  + "catches something else.\n", TP);
	sea_mon--;
	monster = clone_object(ICE_CAST_M + "seamonster");
	monster->move(TO);
	monster->command("kill " + TP->query_real_name());
	return 1;
    }
    
    write("You cast the line far out into the sea and "
	  + "before it even touches the water, a large fish jumps "
	  + "out of the water and gets hooked.\n");
    fish = clone_object(ICE_CAST_O + "fish");
    if (!fish->move(TP))
      write("You place the fish into your inventory.\n");
    else
    {
	write("You drop the fish on the ground.\n");
	fish->move(TO);
    }
    num_fish--;
    say(QCTNAME(TP) + " jerks " + TP->query_possessive() + " fishing "
	+ "pole towards the sea "
	+ "and immediately catches a fish.\n");
    return 1;
}


int drink(string str)
{
    NF("Drink what?\n");
    if (str != "water" && str != "seawater" && str != "from sea")
      return 0;
    
    write("Phewwww!  Yuk!  It is WAY too salty.\n");
    say(QCTNAME(TP) + " is wracked by convulsions as "
	+ PRONOUN(TP) + " tries to drink from the salty sea.\n" );
    return 1;
}
