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

    add_cmd_item(({"down","water","to surface","up" }),
         ({"dive","swim"}),"If you want to swim up or down, just head in that direction!\n");

    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER); 

    add_exit(ROOM + "8ruw1", "up", "@@swim_up", 1, 1);
    add_exit(ROOM + "8ruw3", "down", "@@swim_down", 1, 1);

    set_sink_path(ROOM + "8ruw3");

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
    return "deep under the surface of the Turbidus Ocean";
}
 
string
long_descr()
{
    return "You are deep under the surface of Turbidus Ocean within dark and " +
        "murky waters that churn malevolently with a powerful current. " +
        "\n";
}


