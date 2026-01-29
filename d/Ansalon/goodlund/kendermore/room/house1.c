/* Kender house in Kendermore, Gwyneth, June 1999 */

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit STREET_DESC;
inherit KENDERMORE_IN;

string *things=({(KOBJ + "doll"), (KOBJ + "candlestick"), (KOBJ + "gbead"), 
    (KOBJ + "kboots"), (KOBJ + "carving"), (KOBJ + "metal"), 
    (KOBJ + "pbottle")}); 

object junk;
int found_junk;
object kender;

void
reset_kendermore_room()
{
    if (!objectp(junk))
    {
        junk=clone_object(things[random(7)]);
        junk->move(TO);
    }
    found_junk = 0;

    if (!kender && !random(2))
    {
        kender = clone_object(KNPC + "std_kender");
        kender->move(TO, 1);
    }
}

void
create_kendermore_room()
{
    set_short("A small kender house");
    set_long("This is just one of many kender houses in Kendermore. " +
        "There is a small window set near the door, a heavy rug on " +
        "the floor, a shelf secured to the wall, and some beds against " + 
        "the far wall. The decoration is sparse, most likely because " + 
        "it wouldn't stay put for long anyways.\n");
    add_item(({"street", "window"}), "@@street_descr@@\n");
    add_item(({"rug", "floor"}), "A heavy rug covers the floor. It doesn't " + 
        "look very interesting. Perhaps that's why it's still here.\n");
    add_item(({"shelf", "wall"}), "The shelf is secured to the wall, and " + 
        "has a few things on it.\n");
    add_item(({"bed", "beds", "far wall"}), "Kender sleep here when not on " + 
        "an adventure.\n"); 
    add_item("door", "You could probably leave the house through the door, " + 
        "unless you'd like to try squeezing through the window instead!\n");

    add_cmd_item(({"through window", "out window", "out of window"}), 
        "squeeze", "@@squeeze_out");
    add_cmd_item("house", "leave", "@@leave_house");
    add_cmd_item(({"bed", "beds"}), ({"make", "search"}), "@@search_beds");
    add_cmd_item("shelf", "search", "@@search_shelf");
    add_cmd_item("rug", ({"search", "lift"}), "@@lift_rug");

    set_tell_time(300);
    add_tell("You hear a shrill voice yelling: Gotcha!\n");
    add_tell("A kender opens the door of the house and walks in. He " + 
        "smiles at you, stops to pick up an object from the ground, " + 
        "opens the door, and walks out again.\n");
    add_tell("Bright laughter rings out from the street.\n");
    add_tell("You hear the sound of glass shattering next door.\n");

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
leave_house()
{
    write("You open the door of the house and walk onto the street.\n");
    say(QCTNAME(TP) + " opens the door to the house and walks out.\n");
    tell_room(KROOM + "street09", "The door opens, and " + QTNAME(TP) +  
        " steps onto the street.\n");
    TP->move_living("M", KROOM + "street09", 1, 0);
    return "";
}

string
squeeze_out()
{
    write("You barely manage to squeeze out the window, but why didn't " +
        "you use the door?\n");
    say(QCTNAME(TP) + " decides to leave the house through the window " + 
        "instead of the door like normal folk.\n");
    tell_room(KROOM + "street09", QCTNAME(TP) + " comes tumbling out " + 
        "the window of a nearby house.\n");
    TP->move_living("M", KROOM + "street09", 1, 0);
    return "";
}
string
lift_rug()
{
    say(QCTNAME(TP) + " lifts the rug and raises a cloud of " +
        "dust.\n" + QCTNAME(TP) + " coughs noisily.\n");
    return "You lift the rug, but all you find is a cloud of dust.\nCover " + 
        "your mouth when you cough noisily!\n";
}

string
search_shelf()
{
    if (found_junk)
    {
        say(QCTNAME(TP) + " searches the shelf.\n");
        return "You find nothing of interest on the shelf.\n";
    }

    clone_object(things[random(6)])->move(TP, 1);
    found_junk = 1;
    say(QCTNAME(TP) + " puts something in " + HIS(TP) + " pocket.\n");
    return ("You search around on the shelf, and find something!\n");
}

string
search_beds()
{
    say(QCTNAME(TP) + " looks in the beds.\n");
    return "You find nothing of interest in the beds.\n";
}
        
