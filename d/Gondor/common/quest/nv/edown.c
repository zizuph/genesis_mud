/*
 *      /d/Gondor/common/quest/nv/edown.c
 *
 *      A room for the nightvision quest.
 *
 *      Modification log:
 *      March 1997, Olorin: General revision.
 *
 *      Changed exits to new Barrow Downs.
 *      Finwe, December 2001
 *
 *      Updated exits to the new Barrow Downs
 *      Finwe, December 2002
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <filter_funs.h>
#include <macros.h>

#include "/d/Gondor/bits.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

#define IN_BARROW    "/d/Gondor/common/quest/nv/inebarrow"

static int     Year, 
               Arrive_Alarm, 
               Wight_Cloned;
static object  Wight;

public int     make_noise();
public int     southwest_noise();
public string  read_door();

public void
create_gondor() 
{
    set_short("in front of a barrow");
    set_long(BSN(
        "The fog is not as dense here, but the sight before you does not "+
        "in any way comfort you. A set of stone steps lead up "+
        "to a thick stone door, which is fortunately closed, but still radiates the chill "+
        "of despair and evil. The barrow is a small earthen hill, a tomb of some "+
        "warrior killed many hundreds of years ago."));
    add_item("fog", BSN(
        "This fog has become a little less dense here. To the west " +
        "it looks even denser, but that is the only place you can " +
        "go."));  
    add_item( ({ "steps", "step", "stone steps", }), BSN(
        "The stone steps are old, and weather-worn, and on some " +
        "places partially moss-covered. They must have been here " +
        "for centuries."));
    add_item( ({ "door", "doors", "stone door", "stone doors", }), BSN(
        "The stone doors of the barrow must be just as old as " +
        "the steps. There seems to be some words carved in the " +
        "stone surface, but they have been worn down by centuries " +
        "of weather. You can probably read the few words that are " +
        "left.")); 
    add_item( ({ "letters", "text", "words", "carvings"}), read_door);
    add_cmd_item( ({ "letters", "text", "words", "carvings"}), "read",
        read_door);

    add_item("barrow", "The barrow is a tomb from the ancient " +
        "days, the days of the lost realm of Arnor.\n");

// Connects to the Downs in the Shire
    add_exit("/d/Shire/downs/valley1", "west",  make_noise,  5);
    add_exit("/d/Shire/downs/valley2", "southwest", southwest_noise, 4);



// old exits
/*
    add_exit("/d/Shire/common/downs/down4", "east",  make_noise,  5);
    add_exit("/d/Shire/common/downs/down3", "south", south_noise, 4);
    add_exit("/d/Shire/common/downs/down4", "west",  make_noise,  4);
*/
}

public void
reset_room()
{
    Wight_Cloned = 0;
}

public int
southwest_noise() 
{
    write("You stumble to the southwest where the fog seems less " +
        "dense.\n");
    return 0;
}

public int
make_noise() 
{
    write("You stumble around, trying to find a way out of the " +
        "dense fog.\n");
    return 0;
}

public string
read_door()
{
    string  writing  = "\t\t##RE IS LAI# T# R#ST\n" +
                       "\t\t# MAN O# GRE## #KILL AND POW##\n" +
                       "\t\tLIEU##NA## #F THE #OY#L AR## OF #RNOR\n" +
                       "\n\t\t\t###AN##L OF FORN###\n" +
                       "\t\t\t\tDIE# IN ";
    if (Year <= 0)
        Year = random(1973) + 2;
    write(BSN("The engraved words on the stone door are hard to " +
        "read. Some letters are missing, worn away by wind and " +
        "rain, so this is all you manage to read:") +
        writing + Year + "\n");
    say(QCTNAME(TP)+" studies the words on the stone door.\n", TP);
    return "";
}

public void
wight_arrival(object pl)
{
    if (!objectp(Wight) && !Wight_Cloned)
    {
        tell_room(TO, BSN("A cold, cold chill comes over you, " +
            "and a creeping feeling of evil washes over this eerie " +
            "place.")); 
        Wight = clone_object(COMMON_DIR + "quest/nv/wight");
        Wight->arm_me();
        Wight->move(IN_BARROW);
        Wight_Cloned = 1;
        remove_alarm(Arrive_Alarm);
        Arrive_Alarm = set_alarm(4.0, 0.0, &wight_arrival(pl));
        return;
    }

    if (!objectp(Wight))
        return;

    tell_room(TO, BSN("Through the closed stone door a pale " +
        "hand appears, followed by the gaunt body of a man long " +
        "dead. Surely this must be a wight!")); 
    Wight->move_living("M", TO);
    remove_alarm(Arrive_Alarm);
    Arrive_Alarm = 0;
    Wight->start_quest(pl);
}

public void
remove_wight()
{
    if (objectp(Wight))
        Wight->move(IN_BARROW);
}

public void
enter_inv(object ob, object from)
{
    int     seed;

    ::enter_inv(ob, from);

    if (!objectp(from) || !objectp(ob) || !interactive(ob) ||
        (Arrive_Alarm && sizeof(get_alarm(Arrive_Alarm))))
        return;

    // If someone has solved the quest before, the wight won't
    // appear every time:
    if (ob->test_bit("Gondor", TOUR_GROUP, VENGEFUL_WIGHT_BIT))
    {
        sscanf(OB_NUM(TP), "%d", seed);
        if (random(3, seed))
            return;
    }

    if (!objectp(Wight) || !objectp(present(Wight , TO)))
    {
        if (Year <= 0)
            Year = random(1973) + 2;
        Arrive_Alarm = set_alarm(50.0 * rnd(), 0.0,
            &wight_arrival(ob));
    }
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!objectp(to) || !interactive(ob))
        return;

    if (!sizeof(FILTER_PLAYERS(all_inventory(TO))))
        remove_wight();
}

public int query_year() { return Year; }

public int
quester_present()
{
    return sizeof(FILTER_PLAYERS(all_inventory(TO)));
}
