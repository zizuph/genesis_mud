/* Mortis 12.2005 
 * Way to enter wood?  Found by smell?
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit MERCH_BASE;

#define FLED_GROVE        "_palanthas_fled_shoikan_grove"
#define CORPSE "/d/Krynn/solamn/palanthas/merchants/obj/mage_corpse"

object corpse;

string
query_to_jail()
{
  return "east";
}

void
reset_palan_room()
{
    if(!objectp(corpse))
    {
        corpse = clone_object(CORPSE);
        corpse->move(TO, 1);
    }
}

void
create_palan_room()
{
    SHORT("within the perimeter of the Shoikan Grove");
    LONG("You stand within the perimeter of a grove of enormous oak trees. " +
        "However this isn't any normal grove of oaks! Terrible to behold, " +
        "these oaks are gnarled and twisted, their bark as black as pitch, " +
        "ripped with gashes that ooze sap the colour of blood. Black, " +
        "shapeless things flit about the branches, as if in mockery of " +
        "birds. And pale, hollow faces peer from the shadows, their lips " +
        "twisting as if seeking the warmth of blood. Darkness and cold " +
        "hang thick here, along with the stench of death and decay. The " +
        "ground here is so damp it is a struggle to take steps.\n");

    ITEM(({"oak", "oaks", "tree", "trees", "grove", "shoikan grove",
        "oak trees","enormous oaks","enormous oak trees"}),
	"You stand within the perimeter of a grove of enormous oaks, " +
        "although much larger than any oaks you've ever previously seen. " +
        "A chill radiates from the trees here, a paralyzing unnatural cold " +
        "more severe than anything you have felt before.\n");

    ITEM(({"black shapeless things","shapeless things","things"}),
        "Black, shapeless things flit about the branches of the grove... " +
        "Malevolent mockeries of birds.\n");

    ITEM(({"pale hollow faces","hollow faces","faces"}),
        "The shadows cast by the enormous oak trees hide the guardians of " +
        "the grove - spectres and mohrgs, or ghouls hungry for the warm " +
        "blood of the living.\n");

    ITEM(({"ground"}), "The ground here is very damp, so much so that it " +
        "sucks at your feet when you walk.\n");

    EXIT(MERCH + "tohs", "north", 0, 0);
    EXIT(MERCH + "s_grove", "south", "@@dont_go_south", 0);

    reset_palan_room();
}

void
flee_room(object ob)
{
    ob->catch_tell("You are overcome with gibbering terror, and attempt to " +
        "flee the grove!\n");
    tell_room(TO, QCTNAME(ob)+ " is suddenly overcome with irrational " +
        "fear and flees!\n", ob, ob);  
    ob->add_panic(200);
    ob->add_prop(FLED_GROVE, 1);
    ob->set_whimpy_dir("north");
    ob->run_away();
}

void
add_grove_panic(object ob)
{
    if(!present(ob, TO))
        return;

    if(ob->query_panic() > 800)
    {
       set_alarm(0.5,0.0, &flee_room(ob));
    }
    ob->add_panic(80);
    if(random(2))
        ob->catch_tell("You feel a sense of growing dread here amongst the " +
            "enormous oaks of the Shoikan Grove.\n");
    else
        ob->catch_tell("Whispers from the shadows of the oak trees promise " +
            "a death full of terror and pain.\n");
    set_alarm(60.0,0.0, &add_grove_panic(ob));
}

void
stay_in_room(object ob)
{
    ob->catch_tell("You feel terror radiating from the enormous oaks of the " +
        "Shoikan Grove batter at your protection spells!\n");
    set_alarm(20.5,0.0, &add_grove_panic(ob));
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(ob))
        return;

    if (ob->query_npc() && ob->query_prop(LIVE_I_UNDEAD))
        return;
 
    if (!(ob->has_protect_dragonfear_shadow()) && 
        !(ob->query_wiz_level()))
    {
       set_alarm(1.5,0.0, &flee_room(ob));
    }

    if (ob->has_protect_dragonfear_shadow())
    {
       set_alarm(1.5,0.0, &stay_in_room(ob));
    }
    else if (!ob->query_wiz_level())
    {
       set_alarm(0.5,0.0, &add_grove_panic(ob));
    }
}

int
dont_go_south()
{
    write("You try and go south towards the centre of the Shoikan Grove, when " +
        "a voice whispers to you: 'None may enter until the master of both " +
        "past and present returns here with power!'\n\n");
    flee_room(TP);

    return 1;
}