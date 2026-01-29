#include "/d/Krynn/common/defs.h"
#include "/d/Calia/sys/water.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "../local.h"

inherit SAIL_ROOM_BASE;
inherit "/d/Emerald/blackwall/delrimmon/lib/water_effects.c";

#include "/d/Krynn/common/herbsearch.h"

#define HARD_TO_SWIM  45

#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"
#define SPAWN       TURBIDUS + "living/sahuagin"

string *herbs = HERB_MASTER->query_herbs( ({ "intertide", }) );

int sahuagin_cloned = 0;
int can_move = 0;

void
reset_sea_room()
{
    set_searched(0);

    sahuagin_cloned = 0;
    can_move = 0;

    return;
}

void
create_sea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");
 
    add_item(({"turbidus ocean","ocean","sea"}),
        "To your north stretches the Turbidus Ocean - a massive body of water " +
        "that extends from the Courrain Ocean in the east, across northern " +
        "Ansalon to the Sirrion Sea in the west.\n");

    add_item(({"waters", "water"}),
        "These waters are avoided by local sailors, as they are considered " +
        "the surface boundary of feared monsters from the deep. The waters " +
        "here churn malevolently, as if said monsters swam fervently just " +
        "below the surface!\n");

    add_row_exit(ROOM + "6r", "south", "@@becalmed", 1);
    add_row_exit(ROOM + "7s", "east", "@@becalmed", 1);
    add_row_exit(ROOM + "8r", "north", "@@becalmed", 1);
    add_row_exit(ROOM + "7q", "west", "@@becalmed", 1);

    add_exit(ROOM + "7ruw1", "down", "@@swim_down", 1, 1);
    set_sink_path(ROOM + "7ruw1");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"sea","water"}), 2);

    reset_sea_room();
}

int
swim_down()
{
    if(this_player()->query_skill(SS_SWIM) > HARD_TO_SWIM)
    {
       write("You dive down in to the murky waters, swimming powerfully through " +
          "the strong current.\n");
       say(QCTNAME(TP)+ " dives down in to the murky waters and disappears.\n");
       douse_flames(TP);
       return 0;
    }
    write("You try and dive down in to the murky waters, however the current hinders your " +
          "progress and you quickly return to the surface with a gasp. " +
          "You'll need to improve your swimming if you wish to swim deeper.\n");
    say(QCTNAME(TP) + " tries to dive into the murky sea, however isn't a strong enough " +
          "swimmer to pass through the strong current and returns to the surface with a " +
           "gasp.\n");
    return 1;
}

void
sahuagin_spawned()
{
    can_move = 1;
}

void
spawn_sahuagin(object ob)
{
    if(!sahuagin_cloned)
    {
        object s1, s2, s3;
        object ship = ob->query_boat_in();
        tell_room(ship, "From over the rails of the " +ob->short()+
            " clamber monsters from the depths of the sea!\n", ({ }), TO);

        tell_room(ship->query_boat_loc(), "From out of the sea, " +
            "monsters from the depths clamber up the side of the " +
            ob->short()+ " and on to its deck!\n", ({ }), TO);

        s1 = clone_object(SPAWN);
        s1->arm_me();
        s1->move(ship, 1);
        s2 = clone_object(SPAWN);
        s2->arm_me();
        s2->move(ship, 1);
        s3 = clone_object(SPAWN);
        s3->arm_me();
        s3->move(ship, 1);  
        set_alarm(5.0, 0.0, &s1->check_in_combat());
        set_alarm(5.0, 0.0, &s2->check_in_combat());
        set_alarm(5.0, 0.0, &s3->check_in_combat());

        sahuagin_cloned = 1;     
    }

    set_alarm(2.5,0.0, &sahuagin_spawned());
}

int
becalmed()
{
    if(can_move)
        return 0;

    write("Your ship stops, mysteriously becalmed.\n");
    say(QCTNAME(TP)+ " tries to sail the ship, but it is " +
         "mysteriously becalmed.\n");

    object boat_obj = environment(TP)->query_boat_out();

    if(objectp(boat_obj))
        set_alarm(2.5, 0.0, &spawn_sahuagin(boat_obj));

    return 1;
}


string
short_descr()
{
    return turbidus_sea_short();
}
 
string
long_descr()
{
    return turbidus_sea_desc() + "The waters here churn malevolently, " +
        "as if stirred up by something - or somethings - beneath " +
        "the surface. " +query_sailing_difficulty_desc()+ "\n";
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);    

    if(ob->query_ship() && !sahuagin_cloned)
    {
        set_alarm(2.5,0.0, &spawn_sahuagin(ob));
    }
}
