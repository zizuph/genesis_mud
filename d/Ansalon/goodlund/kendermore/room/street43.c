#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit STREET_DESC;
inherit KENDERMORE_OUT;

object box, gem1, gem2, gem3, gem4, gem5, gem6, gem7, kender, flop_gully, wcan;
int found_junk = 0;

void
reset_kendermore_room()
{
    if (!kender)
        {
            kender = clone_object(KNPC + "std_kender");
            kender->move(TO);
        }
    if (!flop_gully)
        {
            flop_gully = clone_object(KNPC + "flop");
            flop_gully->move(TO);
        }
    if (!wcan)
        {
            wcan = clone_object(KOBJ + "w_can");
            wcan->move(TO);
        }
    found_junk = 0;
}

void
create_kendermore_room()
{
    set_short("A small roundabout");
    set_long("@@long_descr");
    add_item(({"house", "houses"}), "Even the houses here have a " + 
        "carefree feeling. " +
        "You might be able to enter one from here.\n");
    add_item(({"kendermore", "city"}), "The city of Kendermore spreads " +
        "out around you in a complicated twisting of streets. It is the " +
        "home of many kender when they aren't adventuring and exploring.\n");
    add_item(({"street", "road"}), "The road is made of cobblestones. " +
        "It winds " + 
        "beyond your view.\n");
    add_item(({"sign", "signs"}), "Best to ask directions instead.\n");
    add_item(({"flowers", "wild flowers", "bed"}), "Red, yellow, pink, " + 
        "white, purple, and orange dazzle the eye. They look very well " + 
        "cared for, growing in rich dark soil.\n"); 
    add_item("roundabout", "It doesn't seem to lead anywhere specific, " + 
        "much like many of the streets in Kendermore.\n");

    add_cmd_item("house", "enter", "@@enter_house");
    add_cmd_item(({"in flower bed", "in bed", "bed", "flower bed"}), "dig", 
        "@@dig_flowers");

    add_exit(KROOM + "street44", "northwest", 0);
    add_exit(KROOM + "street42", "southwest", 0);

    set_tell_time(100);
    add_tell("A kender bumps into you, apologizes and continues on " + 
        "his way.\n");
    add_tell("Bright laughter rings out from nearby.\n");
    add_tell("A kender arrives, excitedly picks up a piece of shiny " + 
        "metal from the ground, and happily skips away.\n");
    add_tell("A small mouse scurries across your path.\n");
    add_tell("A loud crashing sound reaches your ears.\n");
    add_tell("A small bug skitters under a bush.\n");

    reset_kendermore_room();
    return;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

string
long_descr()
{
    return (tod_descr() + season_descr() + "Houses stand on both sides " + 
        "of you. " + street_descr() + " The road continues on its " + 
        "winding way to the northwest following a small roundabout, and " + 
        "to the southwest. Numerous signs point " + 
        "in all directions, but they tend to contradict each other and " + 
        "point in directions where there are no exits. A bed of wild " + 
        "flowers has been planted outside one of the houses.\n");
}

string
enter_house()
{
    write("You open the door of the house and walk in.\n");
    say(QCTNAME(TP) + " opens the door to the house and walks in.\n");
    tell_room(KROOM + "house6", "The door opens, and " + QTNAME(TP) +  
        " enters the house.\n");
    TP->move_living("M", KROOM + "house6", 1, 0);
    return "";
}

string
dig_flowers()
{
    if (found_junk)
    {
        write("You dig around in the flower bed, finding nothing but dirt.\n");
        say(QCTNAME(TP) + " digs carefully in the flower bed.\n");
        return "";
    }

    else
    {
        box = clone_object(KOBJ + "box");
        box->move(TP, 1);
        gem1 = clone_object(KOBJ + "beryl");
        gem1->move(box, 1);
        gem2 = clone_object(KOBJ + "agate");
        gem2->move(box, 1);
        gem3 = clone_object(KOBJ + "diopside");
        gem3->move(box, 1);
        gem4 = clone_object(KOBJ + "star_sap");
        gem4->move(box, 1);
        gem5 = clone_object(KOBJ + "opal");
        gem5->move(box, 1);
        gem6 = clone_object(KOBJ + "tanzanite");
        gem6->move(box, 1);
        gem7 = clone_object(KOBJ + "tigereye");
        gem7->move(box, 1);
 
    }
    found_junk = 1;

    say(QCTNAME(TP) + " digs carefully in the flower bed.\n");
    return ("You dig around in the flower bed, careful not to disturb " + 
        "the living plants.\nYou find a small wooden box!\n");

}

        
