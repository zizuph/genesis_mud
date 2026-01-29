/* Standard file for any room to be considered within the Forest of Shadows */
/*
 * Added a header for monster sizes, and setting stats depending on
 * night or daytime.
 *
 * Nerull 20/5-09.
 */
/* 2017-06-26 Malus: Fixed spammy messages, late spawning */ 
/* 2017-08-19 Malus: Monster spawning improvements */
/* 2017-09-17 Malus: Removed rain effects */ 
/* 2017-11-20 Malus: Renaming from raum_room_std.c, changing location */
/* 2018-07-08 Malus: Spawn for non-players (like steeds) and randomize time */ 
#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit STD_ROOM;

object monster;

void
create_room()
{
    ::create_room();
    add_room_tell(({
        "From the distance, you hear the eerie howling of a wolf.\n",
        "Dark shadows flutter past you at the corner of your eye.\n",
        "Someone grins evilly.\n",
        "An owl hoots in the distance.\n",
        "You notice a pair of red eyes staring at you from within the "+
          "dark shadows of the forest.\n",
        "You hear a loud crash in the distance.\n",
        "You have the feeling of being watched.\n",
    }));
    set_alarm(1.0,0.0,"reset_room");
}

varargs public mixed
long(string str, object for_obj)
{
    int i;
    string ret;  /*string to return*/

    if (!str)
    {
        if (obj_long)
            ret = check_call(obj_long + TO->query_time_desc(), for_obj);
        else
            ret = "You see a non-descript object.\n";

        while ((i = member_array(0, room_descs)) >= 0)
          room_descs = exclude_array(room_descs, i, i + 1);
        if (room_descs)
        for (i = 1; i < sizeof(room_descs); i += 2)
            ret = ret + check_call(room_descs[i]);

        if (!TO->query_noshow_obvious())
          return ret + TO->exits_description();
        else
          return ret;
    }
    if (!pointerp(obj_items))
        return 1;

    for (i = 0; i < sizeof(obj_items); i++)
        if (member_array(str,obj_items[i][0]) >= 0)
        {
            return (strlen(obj_items[i][1]) ?
                    (string) check_call(obj_items[i][1]) :
                    "You see nothing special.\n");
        }
    return 1;
}

void
reset_room()
{
    ::reset_room();
    set_searched(0);
}

string
random_day_monster()
{
    string *monsters = ({
        COMMON_NPC_DIR + "utroll",
        COMMON_NPC_DIR + "wight",
        COMMON_NPC_DIR + "ghoul",
        COMMON_NPC_DIR + "gskeleton",
        COMMON_NPC_DIR + "giskeleton",
        COMMON_NPC_DIR + "lzombie",
        COMMON_NPC_DIR + "lzombie",
        COMMON_NPC_DIR + "gzombie",
    });
    return monsters[random(sizeof(monsters))];
}

string random_night_monster()
{
    switch(random(32))
    {
        // 1 in 8
        case 0..3: 
            return COMMON_NPC_DIR + "utroll";
        case 4..7:
            return COMMON_NPC_DIR + "wight";
        case 8..11:
            return COMMON_NPC_DIR + "ghoul";
        case 12..15:
            return COMMON_NPC_DIR + "giskeleton";
        // 3 in 32
        case 16..18:
            return COMMON_NPC_DIR + "wraith";
        // 1 in 16
        case 19..20:
            return COMMON_NPC_DIR + "apparition";
        case 21..22:
            return COMMON_NPC_DIR + "shade";
        case 23..24:
            return COMMON_NPC_DIR + "spectre";
        case 25..26:
            return COMMON_NPC_DIR + "druj";
        case 27..28:
            return COMMON_NPC_DIR + "odic";
        case 29..30:
            return COMMON_NPC_DIR + "revenant";
        // 1 in 32
        case 31:
            return COMMON_NPC_DIR + "vision";
    }
}

void
call_monsters(object player, object location)
{
    int i = random(10);
    string path;

    // Don't spawn if this room spawned something that's still around 
    // Make sure the player that triggered this is in the room
    // The undead don't bother with each other
    // The undead don't bother with certain others
    // Spawn more likely at night
    if (objectp(monster)
            || !present(player,location)
            || player->query_prop(LIVE_I_UNDEAD)
            || player->query_prop(UNDEAD_I_NO_AUTO)
            || i < 7
            || (DAY && i < 9))
        return;

    if (DAY)
        path = random_day_monster();
    else
        path = random_night_monster();

    monster = clone_object(path);
    monster->restrain_to_forest();
    monster->move_living("X", location);
}

void
init()
{    
    ::init();
    /*
     * Turning this on for NPCs too. It makes sense that, say, a live horse 
     * would attract the undead, even if its rider didn't
     *
     * if (interactive(TP))
     */
    set_alarm(itof(random(5)+1)+rnd(), 0.0, &call_monsters(TP, TO));
}
