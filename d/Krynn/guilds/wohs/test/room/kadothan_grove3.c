/*
   Test of High Sorcery room
*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <ss_types.h>
#include <language.h>
#include <macros.h>

inherit WOHS_TEST_OUT;

object scout;
int found_orders = 0;

void
reset_tower_room()
{
    if(!objectp(scout))
    {
       scout = clone_object(WOHS_TEST + "living/sleeping_scout");
       scout->arm_me();
       scout->move(TO,1);
    }
}

void
create_tower_room()
{
   set_short("the edge of a grove of tall pine trees");
   set_long("You find yourself at the edge of a peaceful grove of tall " +
       "pine trees. A gentle wind blows through the grove, causing the " +
       "trees to sway serenely above you. There is very little " +
       "undergrowth, with the occasional fern growing amid a deep " +
       "carpet of brown needles from which the lulling drone of " +
       "chirping crickets can be heard. Parting the carpet of needles " +
       "here is a path heading east and west.\n");

   add_item(({"grove","grove of tall pine trees","peaceful grove",
       "forest"}), "You stand within a grove of tall pine trees that " +
       "sway serenely to a gentle highland breeze, almost hypnotically. " +
       "You feel a sense of sleepiness pass over you as you watch the " +
       "trees move, and combined with the intoxicating scent of pine " +
       "you feel your eyelids grow heavy. There is very little " +
       "undergrowth here making it quite easy to navigate through the " +
       "grove. To your west you the grove continues, while to your east " +
       "the grove ends and city streets begin.\n");

   add_item(({"pine trees","trees","tree","pine tree","trunks"}),
       "Tall pine trees surround you here in this grove, swaying " +
       "serenely to a gentle highland breeze, almost hypnotically. You " +
       "feel a sense of sleepiness pass over you as you watch the trees " +
       "move, and combined with the intoxicating scent of pine you feel " +
       "your eyelids grow heavy. As the canopy of the pine trees part " +
       "to your east with the breeze, you notice the houses and shops " +
       "of a great city as well as the minarets of a great imperial " +
       "palace.\n");

   add_item(({"undergrowth","fern","carpet","deep carpet"}),
       "There is very little undergrowth in this grove of pine trees, " +
       "consisting of a deep carpet of brown pine needles and the odd " +
       "fern.\n");

   add_item(({"crickets","chirping crickets","cricket"}),
       "You cannot see any crickets, although you can certainly hear " +
       "their lulling drone which makes you feel increasingly sleepy.\n");

   add_item(({"needles","pine needles","brown pine needles",
       "carpet of needles"}), "A thick carpet of brown pine needles " +
       "covers the ground here.\n");

   add_item(({"path","exit"}), "Running through the carpet of brown " +
       "pine needs here is a path leading west into the grove, and east " +
       "out of the grove on to the streets of a great city.\n");

   add_item(({"city","great city","daltigoth","city streets","streets",
       "houses","shops","edge"}), "To your east the grove of pine " +
       "trees ends and the streets of a great city begins. You notice " +
       "outside the grove a force of Ergothian infantry, cavalry and " +
       "presbyters... an ominous sign for anyone within the grove.\n");

   add_item(({"ergothian infantry","infantry","cavalry","presbyters",
       "army","force"}), "At the entry of the grove to your east you " +
       "can see a large force of Ergothian infantry blockading the " +
       "exit, while cavalry seem to be preparing for an assault. " +
       "Clerical presbyters provide blessings to the soldiers, giving " +
       "you the impression that the military force will be acting upon " +
       "something soon. You notice the commander of the forces near " +
       "the entry of the glade kneeling beside something.\n");

   add_item(({"commander","duke","praetor-general","praetor general",
       "general"}), "Kneeling near the entry of the grove is the " +
       "commander of the army. Wearing the ancient trappings of an " +
       "Ergothian Praetor-General, this commander is one of very high " +
       "military standing. It looks like he is kneeling beside a " +
       "small tree sapling of some kind.\n");

   add_item(({"sapling","tree sapling","small tree sapling",
       "small sapling"}), "Outside the grove you notice the commander " +
       "of the military forces kneeling beside a small tree sapling. " +
       "Strange that a tree sapling would be growing in the middle of " +
       "a city street, and stranger that it had the attention of such " +
       "a large military force.\n");

   add_item(({"imperial palace","palace","minaret","minarets"}),
       "Through the canopy of the trees you can make out a great " +
       "imperial palace to your east, the seat of power of the emperor " +
       "of Ergoth.\n");

   add_item(({"furled military orders","military orders","orders"}),
       "@@exa_orders");

   OUTSIDE;

   add_cmd_item(({"scout","ergothian scout","Ergothian scout",
       "experienced ergothian scout","experienced Ergothian scout"}),
       ({"wake","shake","waken","rouse","awaken","roll","push",
       "slap","kick"}), "@@wake_scout");

   add_search(({"scout","ergothian scout","Ergothian scout",
       "experienced ergothian scout","experienced Ergothian scout"}),
       10,"search_scout",1);

   add_exit(WOHS_TEST + "room/kadothan_grove1", "west", 0);
   add_exit(WOHS_TEST + "room/daltigoth_city1", "east", 0);

   reset_tower_room();

}

string
wake_scout()
{
    if(!objectp(scout))
    {
       return "What?\n";
    }

    if(!scout->query_scout_sleeping())
    {
       return "The scout isn't sleeping!\n";
    }     

    scout->wake_scout(TP);
    return "";
}

string
search_scout(object searcher, string what)
{
    if (CAN_SEE_IN_ROOM(this_player()))
    {
        if(!objectp(scout))
        {
             return ("Search what?\n");
        }

        if(!scout->query_scout_sleeping())
        {
             return ("The scout is awake! You can't search him now!\n");
        }	  

	return ("You notice underneath the scout what looks like " +
            "furled military orders.\n");
    }

    return 0;
}

string
exa_orders()
{
    if(objectp(scout) && scout->query_scout_sleeping())
        return "Underneath the sleeping scout is what looks like " +
            "furled military orders. You would need to push him " +
            "to be able to take them, which will likely wake him. " +
            "Unless he is first dead of course.\n";
    
    return "What?\n";
}
