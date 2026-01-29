/*
* Street of Gont City
*
* Coded by Porta 971017/
*/

#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>
inherit "/d/Earthsea/lib/room_tell";

#include <macros.h>

private object *sailors = allocate(3);

public void
reset_room()
{
    int i = random(3);

    while(i--)
    {
        if(!sailors[i])
        {
            sailors[i] = clone_object("/d/Earthsea/gont/gont_city/liv/sailor" + (random(5)+1));
            sailors[i]->move(this_object());
            sailors[i]->command("emote swaggers in.");
        }
    }
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Street northeast of a large park");
    set_long("The narrow cobbled street continues along"+
        " the edge of a large green park, stretching out"+
        " southwest of here. A low stone wall surrounds"+
        " the park, and you can see a small gate set in"+
        " it, where a gravel path leads into a thick"+
        " grove of oak trees. On the other"+
        " side of the street are old stone buildings, almost"+
        " embedded by the vines and ivy climbing their"+
        " walls. Everything is peaceful here, and the only"+
        " sounds heard are birds singing in the crowns of"+
        " the trees and the breeze rustling leaves and"+
        " branches. Just to the north is a fairly large wooden"+
        " building, where you see travellers coming and going."+
        " To the east you can catch a glimpse"+
        " of the many masts of the ships anchored in the"+
        " harbour.\n");
    add_item("park","The park stretches out to the"+
        " southwest, lush and green with many groves"+
        " of trees and grass lawns between. A low stone"+
        " wall surrounds the park, but there is a gate"+
        " here allowing entrance.\n");
    add_item((({"gate", "small gate"})),
        "There is a small narrow gate made of brass set into "+
        "the low stone wall. Currently it is open to all.\n");
    add_item(({"road","street"}),"The street is cobbled"+
        " and fairly empty of people here, leading from the"+
        " northwest to the east.\n");
    add_item("wall","A low stone wall surrounds the park"+
        " southwest of here. You see moss growing in the"+
        " gaps between the cut black stones it is built of.\n");
    add_item("trees","Oak trees and birches seem to be"+
        " dominating in the park, but you can also make out"+
        " other hardwood trees like elms and ashes.\n");
    add_item("path","A gravel path disappears into a thick"+
        " grove of oaks to the southwest.\n");
    add_item("buildings","Some fairly old-looking stone"+
        " buildings occupy the space northeast of this street,"+
        " almost overgrown with ivy and vines.\n");
    add_item("birds","Once in a while you see a bird fly"+
        " between the trees of the park.\n");
    add_item("masts","Looking east between the houses you"+
        " can spot the masts of ships anchored in the harbour"+
        " of Gont City. You would probably end up at the"+
        " water's edge by continuing east.\n");
    add_item(({"vines","ivy"}),"Vines and ivy climb the"+
        " stone walls of the houses, embedding them in lush"+
        " green vegetation.\n");
    add_tell("A flock of songbirds flies into the park, and you "+
        "hear them chirping in the trees.\n");
    add_tell("A sea breeze stirs the boats' rigging in the harbour, "+
        "making a sound like a thousand tiny silver bells.\n");
    add_tell("Hand in hand, a pair of lovers make off to the "+
        "quiet area of the park, looking at each other with longing.\n");
    set_tell_time(120);
    add_cmd_item((({"wall", "low wall"})), "climb", "Why don't "+
        "you just enter the park the normal way, through the "+
        "gate to the southwest?\n");
    add_exit("../park_1", "southwest", "@@enter_park");
    add_exit("../adv_guild", "north");
    add_exit("city_road14", "east");
    add_exit("city_road12", "northwest");
    reset_room();
}

public int
enter_park()
{
    object tp = this_player();

    tp->catch_tell("You enter the park through the " +
        "gate in the low stone wall.\n");
    say(QCTNAME(tp)+" enters the park through the gate in the"+
        " stone wall.\n");

    return 0;
}
