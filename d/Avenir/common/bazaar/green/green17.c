// Green17 (/d/Avenir/common/bazaar/green/green17.c)
// creator(s):   Tepisch Dec 1994
// last update: Lilith Sep 2021: Changed the way the gate works so it is
//              less dependent on the gatekeeper for people leaving the Holm.
//              His add_acts etc were getting out of sync. The gate here now
//              acts like the Third Gate--players can let themselves out. But.
//              They won't be able to let themselves out if they are still full
//              of "adrenaline".
//              Lilith 6:50 PM 4/21/97 (updated herbsearch)
//              Ilyian (April 1995): added gate, bench, and gatekeeper
// purpose:     A place for herbs, flowers, and veggies to be found
//
// note:       THIS ROOM STOPS FIGHTS FOR THOSE LEAVING THE HOLM
// bug(s):
// to-do:

inherit "/d/Avenir/common/bazaar/green/std_green.c";

#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/d/Avenir/common/herbs/herbsearch.h"

static object gatekeeper;
string *herbs = HERB_MASTER->query_herbs( ({"garden", "forest"}) );

void
reset_room()
{
    set_searched(-3);

    if (!objectp(gatekeeper))
    {
        gatekeeper = clone_object(BAZAAR+"NPCS/gatekeeper");
        gatekeeper->equip_me();
        gatekeeper->move_living("M", this_object());
        gatekeeper->do_sit();
    }
}

void
create_room()
{
    SHORT("South-central garden");
    make_the_room("There are mature-looking plants in this section of "+
        "the garden, and a long, high stone wall covered in ivy "+
        "extends to the south. A large boulder rests to the east, its "+
        "face chiselled flat so that a stone bench could be placed "+
        "flush against it.\nA silver garden gate blocks the way south.\n");

    AE(GREEN + "green13", "north", 0);
    AE(GREEN + "s_shore", "south", "@@try_south");

    AI("boulder", "It is craggy and dark, glittering with feldspar.\n");
    ACI("boulder", "climb", "You climb up the boulder.\nSeeing "+
      "little of interest up here, you decide to climb back down.\n");
    AI(({"gate", "silver gate", "garden gate", "silver garden gate"}),
      "This silver gate gleams from the light. It is high, and from both "+
      "sides of it extend a wall. It has a small latch in the middle, "+
      "with a lock beneath it. Through the gate, you can see the edge "+
      "of the island, with dark water gently lapping at the shore. On "+
      "the other side, a large, arched bridge stretches across the water "+
      "to another island.\n");
    ACI(({"gate", "silver gate", "garden gate", "silver garden gate"}),
      ({"unlock", "open", "close", "pick", "knock"}), 
      "As you approach it, an uncomfortable current of energy pulses "+
      "through you, pressing you backwards.\n"); 
    AI(({"lock", "latch"}), "The latch and the lock, both, are oddly shaped "+
      "and inscribed with magical symbols of unknown provenance.\n");
    AI(({"symbols", "magical symbols"}), "They appear magical in nature.\n");
    add_prop(OBJ_S_WIZINFO, "As of Sept 2021, the gatekeeper no longer "+
	    "opens the gate for people returning from the Holm--they can now "+
		"do it for themselves. This reduces movement time and the out-of-"+
		"sync issues with the gatekeepers add_acts and the gate. However, "+
		"players who aren't relaxed from combat yet can't open the gate "+
		"until the adrenaline is gone--their hands are too shaky.\n");

  
    /*
     * This array provides the herbs to be found, the places to be 
     * searched, and the search delay.
     */
    set_up_herbs(({ ONEOF(herbs), ONEOF(herbs), ONEOF(herbs) }), 
        ({ "garden","beds","soil", "brush", "shrubs", "ivy" }), 5);

    add_herb_file(HERB + "narcissus");
  
    clone_object(BAZAAR + "Obj/misc/bench.c")->move(TO);   //put bench here
    reset_room();
}

int
try_south()
{   
    write("As you approach the gate, an uncomfortable current of energy "+
        "pulses through you, pressing you backwards.\n"); 
    return 1;
}

void
enter_inv(object ob, object from)
{
    object *enemies;

    ::enter_inv(ob, from);

    if (interactive(ob) && 
       (file_name(from) == "/d/Avenir/common/bazaar/green/s_shore"))
    {
        enemies = ob->query_enemy(-1);
        ob->stop_fight(enemies);
        enemies->stop_fight(ob);
    }                            
}


