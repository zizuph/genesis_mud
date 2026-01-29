/*
 * This boat is part of a quest.  Cloned by reset_room() in
 * ~Cirath/ak_wela/pier4.c
 */

inherit "/std/object";
#include "/d/Cirath/common/defs.h"
#define LEAK_LEN 120
#define OBVIOUS_LEAK 60
#define CAN_SEE_LEAK_INSIDE (TP->query_skill(SS_AWARENESS) > random(5) + 5)
#define CAN_SEE_LEAK_OUTSIDE (TP->query_skill(SS_AWARENESS) > random(5) + 15)

object occupant;


void
create_object()
{
    if (IS_CLONE)
        return;
    set_name("boat");
    add_name("sailboat");
    add_name("_ak_wela_quest_boat_");
    set_short("@@my_short");
    set_long("@@my_long");

// Special properties, for the boat only.
    add_prop("_mast_is_broken", 1);
    add_prop("_boat_is_leaky", 1);

    add_prop(OBJ_M_NO_GET, "It's a little too bulky for you.\n");
    add_prop(OBJ_M_NO_DROP, "Drop what?\n");
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_M_NO_ATTACK, "You'd just end up in the water.\n");

    add_action("enter_boat", "enter");
    add_action("enter_boat", "board");
    add_action("exit_boat", "exit");
    add_action("exit_boat", "disembark");

    add_action("repair", "repair");
    add_action("repair", "fix");
    add_action("repair", "replace");
//  add_action("repair", "patch");
}


string
my_short()
{
    string tmp;

    tmp = "A ";
/*
    if (query_prop("_boat_is_leaky") > OBVIOUS_LEAK)
    {
        if ((ETO == TP && CAN_SEE_LEAK_INSIDE) || CAN_SEE_LEAK_OUTSIDE)
            tmp += "leaky ";
    }
    else if (query_prop("_boat_is_leaky_"))
        tmp += "leaky ";
*/
    if (query_prop("_mast_is_broken_"))
        tmp += "broken-masted ";
    tmp += "sailboat";
}


string
my_long()
{
    string tmp;

    if (TO->query_prop("_mast_is_broken_"))
        tmp = "This poor boat has a splintered stump where its mast " +
              "should be.  The sail attached to the shattered post " +
              "lying in the boat has been shredded into useless rags. " +
              "The boat itself looks fairly sturdy though";
    else
        tmp = "This small, dilapidated sailboat looks rather out of place " +
              "compared to all the large ocean-going ships in this area.  " +
              "Still, with its strong, square canvas sail and sturdy mast, " +
              "it is plenty seaworthy";
/*
    if (query_prop("_boat_is_leaky_") > OBVIOUS_LEAK)
    {
        if (ETO == TP && CAN_SEE_LEAK_INSIDE)
            tmp += ", except for a small crack in the wood on the port side " +
                   "that is slowly dribbling water into the boat";
        else if (CAN_SEE_LEAK_OUTSIDE)
            tmp += ", except for a small crack in the wood " +
                   "on the port side, just above the water line";
    }
    else
*/
    {
        if (ETO == TP)
            tmp += ", except for a large crack in the wood on the port side " +
                   "that is slowly dribbling water into the boat";
        else
            tmp += ", except for a large crack in the wood " +
                   "on the port side, just above the water line";
    }
    tmp += ".\n";
    return tmp;
}

int
enter_boat(string str)
{
    if (!str || str != "boat" || str != "sailboat" )
        return 0;

// Only one person can use the sailboat at a time
    if (query_prop("_in_use_"))
        return 0;

// Don't want people getting in the boat if they can't get any warning
/*
    if (query_prop("_boat_is_leaky") > 24)
    {
        write("As you attempt to step in the boat, a leak on its port side " +
              "cracks wide open, and the boat sinks in seconds.\n");
        return 1;
    }
*/
    occupant = TP;
    tell_room(ETO, QCTNAME(occupant) + " enters the small sailboat.\n", occupant);
    write("You enter the small sailboat.\n");
    move(occupant, 1);
//  set_alarm((float)query_prop("_boat_is_leaky_") / 24.0, 0.0, "expand_leak");
    add_prop("_in_use_", 1);
    occupant->add_prop("_in_Cirath_quest_boat_", 1);
    occupant->add_prop(LIVE_S_EXTRA_SHORT, " in a small sailboat");
    occupant->add_item("boat", "@@in_use_desc");
    occupant->add_cmd_item("boat", ({ "enter", "board" }),
        ({ "There is only enough room for one person in this small boat.\n",
           "There is only enough room for one person in this small boat.\n" }));
    if (file_name(ENV(occupant)) == "/d/Cirath/ak_wela/pier4")
        occupant->move_living("M", "/d/Cirath/ak_wela/dock4", 1);
    set_no_show_composite(1);
}


int
exit_boat()
{
    if (!objectp(occupant) || TP != occupant)
        return 0;
    tell_room(ETO, QCTNAME(occupant) + " gets out of the small sailboat.\n", occupant);

// Take care of all the properties
    remove_prop("_in_use_");
    occupant->remove_prop("_in_Cirath_quest_boat_");
    occupant->remove_prop(LIVE_S_EXTRA_SHORT);
    occupant->remove_item("boat");
    occupant->remove_cmd_item("boat");
//  set_prop("_boat_is_leaky_", remove_alarm("expand_leak"));

// What exit message do we give the player?
    if (ENV(occupant)->query_prop(ROOM_I_TYPE) == ROOM_WATER)
    {
        write("Ok, but it may be dangerous to your health!\n");
        check_swim(occupant);
    }
    else
        write("You get out of the small sailboat.\n");

// Actually move the boat, and make it visible in the room desc
    move(ENV(occupant), 1);
    set_no_show_composite(0);
}


string
in_use_desc()
{
    string tmp;

    tmp = "This is a small, one-man sailboat, already in use.";
    if (query_prop("_mast_is_broken_"))
        tmp += "  It can't go anywhere, because the mast is broken.";
/*
    if (TP->query_skill(SS_AWARENESS) >= 15 && query_prop("_boat_is_leaky_"))
        tmp += "  You can see it has a growing leak on the port side.";
*/
    tmp += "\n";
    return tmp;
}
