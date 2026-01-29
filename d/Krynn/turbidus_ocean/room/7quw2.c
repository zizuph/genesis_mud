#include "/d/Krynn/common/defs.h"
#include "/d/Calia/sys/water.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "../local.h"

inherit SAIL_ROOM_BASE;

#include "/d/Krynn/common/herbsearch.h"

#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

#define HARD_TO_SWIM  55
#define B_SPAWN     TURBIDUS + "living/sahuagin_baron"
#define SPAWN       TURBIDUS + "living/sahuagin"

string *herbs = HERB_MASTER->query_herbs( ({ "seabottom","intertide", }) );

object s1, s2, s3, shark;

void
reset_sea_room()
{
    set_searched(0);

    if(!objectp(s1))
    {
        s1 = clone_object(SPAWN);
        s1->arm_me();
        s1->move(TO, 1);
    }
    if(!objectp(s2))
    {
        s2 = clone_object(B_SPAWN);
        s2->arm_me();
        s2->move(TO, 1);
    }
    if(!objectp(s3))
    {
        s3 = clone_object(B_SPAWN);
        s3->arm_me();
        s3->move(TO, 1);
    }
}

void
create_sea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");
 
    add_item(({"turbidus ocean","ocean","sea"}),
        "You swim deep under the surface of the Turbidus Ocean - a massive body of " +
        "that extends from the Courrain Ocean in the east, across northern " +
        "Ansalon to the Sirrion Sea in the west.\n");
    add_item(({"murky waters","murky water","waters","water","dark waters",
        "dark and murky waters","dark waters"}),
        "You are surrounded by dark and murky water that churns malevolently " +
        "around you. These waters are the territory of the hostile shark-kin " +
        "known as the sahuagin - vicious and merciless sea monsters that " +
        "terrorise sailors and other sea creatures that are unfortunate " +
        "enough to fall into their grasp.\n");


    add_item(({"sea stack", "stack", "column", "column of rock",
        "volcanic sea stack", "rock", "volcanic rock"}),
        "You are swimming near a great column of volcanic rock that rises " +
        "from the sea floor here like a black spear of the gods. It " +
        "broadens here to a wide ledge, where a dark ominous cavern " +
        "opens in the side of the sea stack like a great wound.\n");
    add_item(({"ledge","wide ledge"}), "Along the side of the sea stack " +
        "is a wide ledge, which stretches before a dark ominous cavern. " +
        "Upon the ledge in front of the cavern stands a twisted altar " +
        "of coral and bones.\n");
    add_item(({"dark ominous cavern", "ominous cavern", "cavern"}),
        "A dark ominous cavern opens in the side of the sea stack like a " +
        "great wound. Gargantuan in size, it radiates from its depths " +
        "a slumbering malevolence not of the mortal realm.\n");
    add_item(({"altar","twisted altar","bones","coral"}),
        "Upon the ledge before the dark ominous cavern stands an old " +
        "sahuagin altar made from the bones of multitudes of sea creatures " +
        "and seafaring races, twisted together with dead coral. By looks, " +
        "dark sacrifices are made here by the devils of the deep.\n");
    add_item(({"sea floor","floor"}),
        "The waters beneath you are too dark and murky to make out the sea " +
        "floor.\n");

    add_cmd_item(({"down","water","to surface","up" }),
         ({"dive","swim"}),"If you want to swim up or down, just head in that direction!\n");
    add_cmd_item(({"cavern","ominous cavern","dark ominous cavern"}),
         ({"enter"}),
         "Approaching the cavern puts an irrational fear in you " +
         "not of this world! You can not bring yourself to enter " +
         "the cavern.\n");

    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER); 

    add_exit(ROOM + "7quw1", "up", "@@swim_up", 1, 1);
    add_exit(ROOM + "7quw3", "down", "@@swim_down", 1, 1);

    set_sink_path(ROOM + "7quw3");

    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_S_DARK_LONG, "You swim deep under the murky waters " +
        "of the Turbidus Ocean. It is too dark for you to see anything " +
        "in these watery depths.\n");
    add_prop(ROOM_S_DARK_MSG, "dark murky waters of the Turbidus Ocean");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"sea","water"}), 2);

    reset_sea_room();
}

int
swim_up()
{
    write("You swim up towards the surface.\n");
    say(QCTNAME(TP)+ " swims up towards the surface.\n");
    return 0;
}

int
swim_down()
{
    if(this_player()->query_skill(SS_SWIM) > HARD_TO_SWIM)
    {
       write("You dive down further in to the murky waters, swimming powerfully through " +
          "the strong current.\n");
       return 0;
    }

    write("You try and dive down further in to the murky waters, however the current hinders your " +
          "progress. You'll need to improve your swimming if you wish to swim deeper.\n");
    say(QCTNAME(TP) + " tries to dive deeper into the murky sea, however isn't a strong enough " +
          "swimmer to pass through the strong current.\n");
    return 1;
}

string
short_descr()
{
    return "deep under the surface of the Turbidus Ocean, upon a sea stack ledge";
}
 
string
long_descr()
{
    return "You are deep under the surface of Turbidus Ocean within dark and " +
        "murky waters that churn malevolently with a powerful current. " +
        "Before you is a great sea stack that rises from the sea floor, " +
        "rising like a grim volcanic spear to the surface. Here the side of " +
        "the sea stack broadens in to a wide ledge, which stretches before " +
        "a dark ominous cavern that breaches the sea stack like a great wound.\n";
}


