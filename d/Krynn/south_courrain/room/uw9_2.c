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
#define W_SPAWN     LIVING + "triton_warleader"
#define SPAWN       LIVING + "triton"


string *herbs = HERB_MASTER->query_herbs( ({ "seabottom","intertide", }) );

object s1, s2, s3;

void
reset_sea_room()
{
    set_searched(0);

    if(!objectp(s1))
    {
        s1 = clone_object(SPAWN);
        s1->move(TO, 1);
    }
    if(!objectp(s2))
    {
        s2 = clone_object(W_SPAWN);
        s2->move(TO, 1);
    }
    if(!objectp(s3))
    {
        s3 = clone_object(W_SPAWN);
        s3->move(TO, 1);
    }

}

void
create_sea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");
 
    add_item(({"courrain ocean","ocean","sea"}),
        "You swim deep under the surface of the Courrain Ocean that " + 
        "stretches along the coastline of Ansalon.\n");
    add_item(({"dark waters","dark water","waters","water","dark waters",
        "dark and murky waters"}),
        "You are surrounded by dark water of the Courrain, a sullen and " +
        "heavy pressure reminding you of the grand expanse around you. " +
        "Beneath you is a deep sea trench that cuts through the ocean " +
        "floor like a huge wound, known as Leviathan's Deep.\n");
    add_item(({"deep sea trench", "sea trench", "trench", "floor",
        "leviathan's deep", "leviathans deep", "ocean floor"}),
        "Beneath you is a deep sea trench known as Leviathan's " +
        "Deep. It is rumoured to be the home of merfolk who fiercely " +
        "protect their realm from intruders.\n");

    add_cmd_item(({"down","water","to surface","up" }),
        ({"dive","swim"}),
        "If you want to swim up or down, just head in that direction!\n");

    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER); 

    add_exit(ROOM + "uw9_1", "up", "@@swim_up", 1, 1);
    add_exit(ROOM + "uw9_3", "down", "@@swim_down", 1, 1);

    set_sink_path(ROOM + "uw9_3");

    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_S_DARK_LONG, "You swim deep under the dark waters " +
        "of the Courrain Ocean. It is too dark for you to see anything " +
        "in these watery depths.\n");
    add_prop(ROOM_S_DARK_MSG, "dark sullen waters of the Courrain Ocean");

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
       write("You dive down further in to the dark waters, swimming " +
          "powerfully through the strong current.\n");
       return 0;
    }
    write("You try and dive down further in to the dark waters, " +
        "however the current hinders your progress. You'll need to " +
        "improve your swimming if you wish to swim deeper.\n");
    say(QCTNAME(TP) + " tries to dive deeper into the dark sea, however " +
        "isn't a strong enough swimmer to pass through the strong current.\n");
    return 1;
}

string
short_descr()
{
    return "deep under the surface of the Courrain Ocean";
}
 
string
long_descr()
{
    return "You are deep under the surface of Courrain Ocean within dark and " +
        "sullen waters that spread before you in all directions. Beneath " +
        "you is a deep sea trench known as Leviathan's Deep that cuts " +
        "through the ocean floor like a great wound. " +
        "\n";
}
