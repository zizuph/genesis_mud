/* The road through the forest of Raumdor, by Sarr */
#include "defs.h"
inherit SHADOWS_ROOM;
object ob;
mapping xGrid = ([
    "wforest31": 1,
    "wforest32": 2,
    "wforest33": 3,
    "wforest34": 4,
    "wforest35": 5,
    "wforest36": 6,
    "wforest37": 7,
    "wforest52": 8,
    "wforest67": 9,
    "wforest82": 10,
    "wforest83": 11,
    "wforest84": 12,
    "wforest85": 13,
    "wforest86": 14,
    "eforest38": 15,
    "eforest39": 16,
    "eforest40": 17,
    "eforest41": 18,
    "eforest42": 19,
    "nforest12": 20,
    "eforest50": 21,
    "eforest53": 22,
]);
mapping yGrid = ([
    "wforest31": 0,
    "wforest32": 0,
    "wforest33": 0,
    "wforest34": 0,
    "wforest35": 0,
    "wforest36": 0,
    "wforest37": 0,
    "wforest52": 1,
    "wforest67": 2,
    "wforest82": 3,
    "wforest83": 3,
    "wforest84": 3,
    "wforest85": 3,
    "wforest86": 3,
    "eforest38": 3,
    "eforest39": 3,
    "eforest40": 3,
    "eforest41": 3,
    "eforest42": 3,
    "nforest12": 4,
    "eforest50": 5,
    "eforest53": 6,
]);
string random_undead();
string road_long();
string roadWest = "west";
string roadEast = "east";

public int
prevent_enter(object ob)
{
    // Must allow newly cloned NPCs to enter
    if (!environment(ob))
        return 0;

    if (DAY && ob->query_raumdor_undead())
        return 1;
}

void
create_room()
{
    ::create_room();
    set_short("On an old path through a shadowy forest");
    set_long("@@road_long@@");
    add_item("cobblestone","They are old and worn.\n");
    add_item("forest","A dreadful, gloomy forest full of shadows.\n");
    add_item(({"path","road"}),"It is old and worn, made of dirt and stone.\n");
    add_prop(ROOM_S_DARK_LONG, "A dark pathway.\n");
    
}

string
road_long()
{
    string str = "You stand on an old pathway in a shadowy forest, " +
        "traces of cobblestone scattered in the dirt. ";
    if (DAY)
        str += "With the trees parted, the forest does not block the light " +
            "above, which strangely seems to curl around the path. You have " +
            "the feeling that you are safer here than in the forest, " +
            "at least during the day. ";
    str += "All ways lead into the woods but " + roadEast + " and " +
        roadWest + ", where the road continues.\n";
    return str;
}

void
init()
{
    ::init();
    if(interactive(TP))
        set_alarm(1.5,0.0,"summon_undead", TP);

    if (DAY)
    {
        add_prop(ROOM_I_LIGHT, 1);
    }
    else
    {
        add_prop(ROOM_I_LIGHT, 0);
    }
    CLOCK->add_event(this_object());
}

void
event_hook(int hour)
{
    object *list;

    if (DAY && query_prop(ROOM_I_LIGHT) == 0)
    {
        add_prop(ROOM_I_LIGHT, 1);
        tell_room(get_this_object(), "As the morning light crests the " +
                "treetops, the shadows retreat into the forest.\n");
        list = all_inventory(get_this_object());
        foreach (object ob: list)
        {
            if (ob->query_raumdor_undead())
                ob->run_away();
        }
    }
    else if (!DAY && query_prop(ROOM_I_LIGHT) == 1)
    {
        add_prop(ROOM_I_LIGHT, 0);
        tell_room(get_this_object(), "The light of day disappears behind "
                + "the trees, plunging the pathway into shadowy darkness.\n");
        list = filter(all_inventory(get_this_object()), interactive);
        foreach (object player: list)
        {
            set_alarm(1.5,0.0,"summon_undead", player);
        }            
    }
}

void
summon_undead(object player)
{
    if(random(3) || ob || DAY || !present(player,TO)
            || player->query_prop(LIVE_I_UNDEAD))
        return;
    ob = clone_object(random_undead());
    ob->move_living("M",TO);
    ob->restrain_to_forest();
    TELL_SEEN(ob, CAP(LANG_ADDART(ob->query_nonmet_name() +
               " leaps out onto the path!\n")));
}

string
random_undead()
{
     switch(random(19))
     {
         case 0:case 1:case 2:
         return "/d/Raumdor/common/npc/lzombie";
         break;
         case 3:case 4:case 5:
         return "/d/Raumdor/common/npc/gzombie";
         break;
         case 6:case 7:
         return "/d/Raumdor/common/npc/wight";
         break;
         case 8:case 9:case 10:
         return "/d/Raumdor/common/npc/ghoul";
         break;
         case 11:case 12:
         return "/d/Raumdor/common/npc/utroll";
         break;
         case 13:case 14:
         return "/d/Raumdor/common/npc/wraith";
         break;
         case 15:case 16:case 17:
         return "/d/Raumdor/common/npc/lskeleton";
         break;
         case 18:
         return "/d/Raumdor/common/npc/revenant";
         break;
    }
}

mixed
query_waypoint_direction(string waypoint)
{
    if (waypoint == "beach")
        return roadWest;
    if (waypoint == "mountains")
        return roadEast;
    return 0;
}

int *
query_coordinates()
{
    // Note, we're relying on the rooms directories to be the same length
    string room = extract(MASTER_OB(TO), strlen(FOREST_DIR));
    return ({xGrid[room], yGrid[room], 0});
}
