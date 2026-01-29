// file name:   /d/Avenir/common/outpost/seawall.c
// creator(s):  Cirion
// last update: Lilith, Sep 2021 added fisherman prop
// purpose:     The seawall that leads into the tunnel to the Union
//              halls. Aglyna can be summoned from here.
// note:
// bug(s):
// to-do:  

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/include/relation.h"
#include <filter_funs.h>
#include <composite.h>

inherit "/d/Avenir/inherit/room";
inherit "/d/Avenir/inherit/sair_wall";

#define SEE_BEACH ({ "/d/Avenir/common/ships/bazaar/boat_path1" })
#define SEE_BOAT  ({ "/d/Avenir/common/ships/bazaar/deck" }) 
#define SEE_HILL  ({ "/d/Avenir/common/bazaar/extr/hill" })
#define SEE_FLOAT ({ "/d/Avenir/common/bazaar/pier/float" })

object wall;

string 
beach_view()
{
    object *inv, *live, room;
    int i;
 
    inv = ({ });
    for(i = 0; i < sizeof(SEE_BEACH); i++)
    if((room = find_object(SEE_BEACH[i])))
        inv += all_inventory(room);
 
    if(sizeof(inv)) 
    {
        live = FILTER_LIVE(inv);
        live = FILTER_CAN_SEE(live, TP);
        if(sizeof(live))
            return " Down below, at the foot of the cliff, "+
                   "is "+ COMPOSITE_LIVE(live) + ".";
    }
    return "";
}

string 
boat_view()
{
    object *inv, *live, room;
    int i;
 
    inv = ({ });
    for(i = 0; i < sizeof(SEE_BOAT); i++)
    if((room = find_object(SEE_BOAT[i])))
        inv += all_inventory(room);
 
    if(sizeof(inv)) 
    {
        live = FILTER_LIVE(inv);
        live = FILTER_CAN_SEE(live, TP);
        if(sizeof(live))
            return " You can see "+ COMPOSITE_LIVE(live) + 
                   " standing on the deck of the boat.";
    }
    return " You can also see that the ferry between the fort "+
           "and the bazaar is empty of passengers.";
}

string 
float_view()
{
    object *inv, *live, room;
    int i;
 
    inv = ({ });
    for(i = 0; i < sizeof(SEE_FLOAT); i++)
    if((room = find_object(SEE_FLOAT[i])))
        inv += all_inventory(room);
 
    if(sizeof(inv)) 
    {
        live = FILTER_LIVE(inv);
        live = FILTER_CAN_SEE(live, TP);
        if(sizeof(live))
            return " There appears to be "+ COMPOSITE_LIVE(live) +                          " waiting for the boat back to the fort.";
    }
    return "";
}

string 
hill_view()
{
    object *inv, *live, room;
    int i;
 
    inv = ({ });
    for(i = 0; i < sizeof(SEE_HILL); i++)
    if((room = find_object(SEE_HILL[i])))
        inv += all_inventory(room);
 
    if(sizeof(inv)) 
    {
        live = FILTER_LIVE(inv);
        live = FILTER_CAN_SEE(live, TP);
        if(sizeof(live))
            return " At the top "+
                   "of the hill in the bazaar you can "+
                   "just see "+ COMPOSITE_LIVE(live) + ".";
    }
    return " For some unknown reason, the hill in the bazaar "+
           "is quite bare.";
}

void
create_domain_room()
{
	add_prop(ROOM_I_TYPE, ROOM_BEACH);
	add_prop("_live_i_can_fish", "saltwater");

    set_short("edge of a natural seawall");
    set_long("From your vantage here you have excellent "+
        "visibility of the Sybarus cavern. Far below, the "+
        "dark waters of the Sybarus Sea lap gently against "+
        "the base of this natural seawall. In the distance to "+
        "the north, a large island covered with foliage can "+
        "be made out."+
        "@@hill_view@@@@float_view@@@@boat_view@@@@beach_view@@"+
        " An archway to the south leads into a dark tunnel.\n");

    add_item(({"sea","water","ocean","sybarus sea"}), "The dark waters "
       + "far below churn and swirl.\n");
    add_item("island", "The island far to the north is covered "
       + "in greenery, but no further details can be made out.\n");
    add_item("tunnel", "It leads into darkness.\n");

    add_cmd_item(({"water", "sea", "down", "off"}), ({ "jump", "dive",
         "enter", "swim" }), VBFC_ME("dive_off"));
		 
    add_exit(UNION + "room/tunnel/tunnel10", "south");
	
    add_sair_wall();
    set_sair_dest(PORT +"port18");
	add_item(({"wall"}),
        "It is a wall much like all the others in this place.\n");

}

/*
 * If the player dives off the seawall, he will end up
 * at OUTPOST + "boat/boat_path2"
 */
string
dive_off()
{
    write("You gasp for breath and dive off the top of the seawall.\n");
    say(QCTNAME(TP) + " dives off the seawall, into the dark waters far "
        + "below.\n" + CAP(TP->query_pronoun()) + " is quickly lost from "
        + "sight.\n");

    write("You plunge deep into the black water, and the strong currents instantly "
        + "grab hold of you.\nThe current washes you up onto a sandy beach.\n");

    TP->move_living("M", "/d/Avenir/common/ships/bazaar/boat_path2", 1, 1);
    say(QCNAME(TP) + " is washed up onto the beach.\n");

    TP->set_fatigue(0);

    return "";
}

void
summon()
{
    int num_players, num_steeds, how_many, i;
    object *steeds = ({});

    num_players = sizeof(FILTER_PLAYERS(all_inventory(TO)));
    num_steeds = sizeof(filter(all_inventory(TO), &->id("aglyna")));

    how_many = num_players - num_steeds;

    if(how_many <= 0)
    {
         return;
    }

    for(i = 0; i < how_many; i++)
        steeds += ({ clone_object(MON + "aglyna") });

    steeds->move_living("M", TO);

    tell_room(TO, "Flying down from great heights, "
        + COMPOSITE_LIVE(steeds) + " descend" + (sizeof(steeds) == 1 ? "s" : "")
        + ".\n");

}

void
enter_inv(object to, object from)
{
    ::enter_inv(to, from);

    if(IS_SYBARITE(to))
       set_alarm(10.0, 0.0, summon);
}

void init()
{
    sair_init();
    ::init();
}



