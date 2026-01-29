#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

#define PASS_NOT_OK "_pass_not_ok"
#define GUARD3 "/d/Earthsea/gont/gont_city/liv/guard3"

private object *guards = allocate(3);

public void
reset_room()
{
    int i = 3;

    while(i--)
    {
        if(!objectp(guards[i]))
        {
            guards[i] = clone_object(GUARD3);
            guards[i]->move(this_object(), 1);
            guards[i]->command("emote marches in.");
        }
    }
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("On the land bridge");
    set_long("The road passes over the narrow"+
        " landbridge across the moat into the"+
        " great Port of Gont, through an arch of stone set in"+
        " the thick city walls. The dark stone walls tower"+
        " up high above you, shadowing the sun. On both"+
        " sides, the landbridge drops steeply down into the moat,"+
        " where you can see the swirling grey sea water,"+
        " in constant movement from the waves rolling"+
        " in. People pass by on their way in and out"+
        " from the city, driving small carts or on foot.\n");
    add_item("landbridge","You are standing on a narrow"+
        " strip of land, reaching across the moat surrounding"+
        " the great Port of Gont. On the landbridge is a"+
        " road, passing through the open gates of the city.\n");
    add_item("walls","The dark walls made by cut stone towers"+
        " up high above you here just outside the gate,"+
        " shadowing the sun.\n");
    add_item("moat","Below you is the wide moat surrounding"+
        " the Port of Gont, filled with swirling seawater,"+
        " set in a constant movement by the large waves rolling"+
        " in.\n");
    add_item(({"arch","gate"}),"The road passes through an"+
        " arch of stone in the city wall, wide enough to let"+
        " two wagons pass side by side.\n");
    add_item("road","The road leads inside the great Port"+
        " of Gont through the city gate.\n");
    add_item("water","Below the grey sea water in the moat"+
        " is in a constant circular motion, swirling around"+
        " in the rhytm of the large waves coming in from the"+
        " sea.\n");
    add_item("people","The people passing by are mostly"+
        " farmers, but you can also see a foreign looking"+
        " traveller in strange clothes here and there.\n");
    add_exit("out_landbridge", "north");
    add_exit("inside_gate", "south", "@@allow_pass");
    reset_room();
}

public int
allow_pass()
{
    object tp = this_player();
    object guard;
    int i = 3;

    if(guard = present("_guard3_", this_object()))
    {
        if(tp->query_prop(PASS_NOT_OK))
        {
            guard->command("shout Invaders!! don't let "+
                tp->query_objective() + " pass! Sound the alarm!");

            while (i--)
	    {
                if(objectp(guards[i]))
                    guards[i]->command("kill "+ tp->query_real_name());
            }

            guard->command("shout Get "+ tp->query_objective() + "!!");
            tp->catch_msg("An arrow goes whizzing past your head.\n");

            return 1;
        }

        tp->catch_msg("The guard allows you to pass.\n");
        guard->command("say Move along now! Don't block the gate!");

        return 0;
    }

    return 0;
}
