/*
 * Deadend1.c
 *
 * A deadend tunnel in Shelobs lair, Torech Ungol.
 *
 * Olorin, 28 oct 1993, copied and modifed from
 * /Mercade, 18 july 1993
 */

inherit "/d/Gondor/mordor/ungol/lair/std_lair";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define MIN_AWARENESS    25     /* awareness to find the hole in the roof */
#define MIN_STRENGTH     40     /* strength to move boulder */
#define MIN_CLIMB        30     /* climb skill needed to climb up */
#define DAMAGE          100     /* minimum damage when slipping */
#define MAX_FAT_P        50     /* fatigue value when pushing the rock */
#define MAX_FAT_C        50     /* fatigue value when climbing */
#define UP_ROOM         (MORGUL_DIR + "tunnel/hiding1")
#define UP_ROOM2        (MORGUL_DIR + "tunnel/hiding2")

int    boulder = 0;      /* 0 = blocks hole */
int    roll_back_alarm;

void roll_back();
void reset_room();

void
create_room()
{
    add_exit(LAIR_DIR + "deadend1", "northeast",  0, 4);

    make_the_room(" The roof of the cave is hanging rather low here. To the "+
        "south, it almost touches a few large boulders.");
    remove_item("roof");
    remove_item("rocks");
    add_item(({"boulder","boulders","rock","rocks"}), BSN(
        "Some large boulders lie at the southern end of the cave. The roof " +
        "of the cave is running very low there, almost touching the boulders."));
    add_item(({"roof","ceiling"}), VBFC_ME("exa_roof"));
    add_item(({"hole","opening"}), VBFC_ME("exa_hole"));
    add_item(({"crack","slit"}), VBFC_ME("exa_crack"));
    add_prop(OBJ_S_SEARCH_FUN,"do_search");

    reset_room();
}

void init()
{
    ::init();
    add_action("do_climb","climb");
    add_action("do_climb","enter");
    add_action("do_push","push");
    add_action("do_push","move");
}

string do_search(object searcher, string str)
{
    if(!str || (str != "boulder" && str != "boulders" && str != "rock" &&
              str != "rocks" && str != "roof" && str != "ceiling" && str != "crack") )
        return 0;

    if(boulder)
        return 0;

    if(TP->query_skill(SS_AWARENESS) < MIN_AWARENESS)
        return 0;

    say(QCTNAME(TP) + " seems to have found something interesting.\n");
    return BSN("When you examine the roof and the boulders closely, you realize " +
        "that there is a small hole leading upwards, which is blocked by one " +
        "of the boulders. You can see it just barely in the small crack left " +
        "between the roof and the boulder.");
}

string
exa_roof()
{
    string desc;

    desc = "To the south, the roof of the cave is much lower than elsewhere. "+
        "Some large boulders almost reach up to it. ";

    if(boulder)
        desc += "Close to where one of the larger boulders lies there is " +
            "a dark hole in the roof. You might be able to climb through the " +
            "hole into the cave above.";

    return BSN(desc);
}

string exa_hole()
{
    string desc;

    if(boulder)
        desc = "Close to where one of the larger boulders lies there is " +
            "a dark hole in the roof. You might be able to climb through the " +
            "hole into the cave above.";
    else
    {
        if(TP->query_skill(SS_AWARENESS) < MIN_AWARENESS)
            return "You find no hole.\n";

        desc = "In the small crack left between one of the boulders and the " +
            "roof of the cave you make just barely make out a hole that " +
            "might lead up into another cave. But the hole is blocked by the " +
            "boulder below it.";
    }

    return BSN(desc);
}

int filter_living(object x) { return living(x); }

void reset_room()
{
    object *arr = ({});
    object up_room = find_object(UP_ROOM);
    object up_room2 = find_object(UP_ROOM2);

    if(objectp(up_room))
        arr += all_inventory(up_room);
    if(objectp(up_room2))
        arr += all_inventory(up_room2);
    arr = filter(arr,"filter_living",TO);
    if(!sizeof(arr))
        boulder = 0;
}

void set_boulder(int i)
{
    boulder = i;
    tell_room(UP_ROOM,
        "Suddenly, you hear something heavy moving under the hole in the floor.\n");
     if (i && !get_alarm(roll_back_alarm))
        set_alarm(itof(5 + random(15)), 0.0, roll_back);
}

int query_boulder() { return boulder; }

int do_push(string str)
{
    string vb = query_verb();
    int    fat = TP->query_fatigue();
    int    istr = MIN(TP->query_stat(SS_STR), 100);
    int    fat_str;

    NF(CAP(vb) + " what?\n");
    if(!str || (str != "boulder" && str != "rock"))
        return 0;

    fat_str = MAX(0, ((100 - istr) * 100));
    fat_str = fat_str / (100 - MIN_STRENGTH);
    fat_str = MAX_FAT_P + MAX_FAT_P*fat_str/100;

    if(istr < MIN_STRENGTH)
    {
        write(BSN("You stem yourself against the large boulder, " +
            "trying to " + vb + " it to unblock the hole in the roof.")+
            BSN("But even with all your strength you fail to move the " +
            "large boulder a single inch."));
        SAY(" stems "+TP->query_objective()+"self against the large " +
            "boulder, trying to push it to unblock the hole in the roof, "+
            "but "+TP->query_pronoun()+" fails to move the large boulder " +
            "a single inch.");
        TP->add_fatigue(-MAX_FAT_P);
    }
    else if(fat < fat_str)
    {
        NF(BSN("You are too exhausted to "+vb+" the large boulder."));
        return 0;
    }
    else if(boulder)
    {
        write(BSN("You stem yourself against the large boulder and " +
            "with a little push, it rolls back into its old position, " +
            "blocking again the hole in the roof of the cave.")+
            "You are a bit tired.\n");
        SAY(" stems "+TP->query_objective()+"self against the large " +
            "boulder and after a small push the boulder rolls back into " +
            "its old position, blocking again the hole leading " +
            "through the roof of the cave.");
        set_boulder(0);
        TP->add_fatigue(-fat_str/4);
    }
    else
    {
        write(BSN("You stem yourself against the large boulder and " +
            vb + " it a small way, unblocking the hole in the roof.")+
            "Your body aches from the effort!\n");
        SAY(" stems "+TP->query_objective()+"self against the large " +
            "boulder and pushes it a small way, unblocking the hole " +
            "in the roof.");
        set_boulder(1);
        tell_room(TO, BSN("The boulder does not look like it rests well " +
            "balanced in its new position. It might roll back to where it " +
            "was before any moment."));
        TP->add_fatigue(-fat_str);
    }
    return 1;

}

int do_climb(string str)
{
    string vb = query_verb();
    int    cs = TP->query_skill(SS_CLIMB);
    int    fat = TP->query_fatigue();
    int    new_fat;

    NF(CAP(vb) + " where?\n");
    if(!str || (str != "hole" && str != "in hole" && str != "into hole" && str != "through hole" && str != "up"
        && str != "opening" && str != "in opening" && str != "into opening" && str != "through opening"))
        return 0;

    if(!boulder)
    {
        NF("You cannot climb through the hole, it is blocked by the large boulder!\n");
        if(TP->query_skill(SS_AWARENESS) < MIN_AWARENESS)
            NF(CAP(vb) + " where?\n");
        return 0;
    }

    if( fat < (new_fat = MAX(5,MAX_FAT_C - cs)) )
    {
        NF(BSN("You are too exhausted to climb up through the hole."));
        return 0;
    }
    if( cs < (MIN_CLIMB/2 + random(MIN_CLIMB/2)) )
    {
        write("You try to climb up through the hole, but you slip and fall down again.\n");
        say(QCTNAME(TP) + " tries to climb up through the hole, but slips and falls down again.\n");
        TP->heal_hp(-(DAMAGE+(MIN_CLIMB-cs)*10));
        if(!TP->query_hp())
            TP->do_die(TO);
        else
            write("You hurt yourself in the fall.\n");
        TP->add_fatigue(-new_fat/2);
        return 1;
    }

    set_dircmd(str);
    write("You climb up into the hole.\n");
    if(new_fat > 10)
        write("Climbing through the hole turns out to be rather tiring!\n");
    say(QCTNAME(TP) + " leaves climbing up through the hole in the ceiling.\n");
    TP->move_living("M", MORGUL_DIR + "tunnel/hiding1");
    TP->add_fatigue(-new_fat);
    tell_room(UP_ROOM, QCTNAME(TP) + " arrives climbing out of the hole in the ground.\n",TP);
    return 1;
}

void roll_back()
{
    if(!boulder)
        return;

    tell_room(TO, BSN("Suddenly, the large boulder rolls back into its old position, " +
        "blocking the hole in the roof again!"));
    set_boulder(0);
}

string exa_crack()
{
    string desc;

    if(boulder)
        return "You find no crack.\n";
    if(TP->query_skill(SS_AWARENESS) < MIN_AWARENESS)
        return BSN("You can see a small crack between a large boulder and the " +
            "roof of the cave.");
    else
        return BSN("In the small crack left between one of the larger boulders " +
            "and the roof of the cave, you can make out a dark hole in the roof " +
            "leading upwards.");
}
