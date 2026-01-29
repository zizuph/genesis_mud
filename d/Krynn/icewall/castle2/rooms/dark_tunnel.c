#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"

#include <macros.h>
#include <ss_types.h>

inherit ICEINROOM;

void
create_icewall_room()
{
    set_short("Wide, darkened tunnel");
    set_long("@@long_descr@@");


    add_exit("huge_warehouse","east");
 
    add_cmd_item(({"fissure","cave"}),"enter","@@careless_entry");

    add_item("fissure","A natural opening in the west end of the " +
        "tunnel. Further on, it widens into a large, darkened " +
        "cave. However, the way there is blocked by many sharp " +
        "stalagmites.\n");
    add_item(({"cave","darkened cave"}),"You cannot see much " +
        "from here. Try to enter it for a closer look.\n");
    add_item(({"wall","walls"}),"The rough stone of the walls " +
        "is covered with icy blue frost. Here and there someone " +
        "appears to have worked on it.\n");
    add_item(({"floor","carpet"}),"The floor is covered thick with " +
        "ice. Hard as steel, it makes your footing extremely unsure.\n");
    add_item(({"tunnel","dark tunnel"}),"The tunnel appears to have " +
        "a natural origin. However, in several places it was widened " +
        "to allow easier passage. For some reason the work " +
        "has been left unfinished, and ice begins to creep back " +
        "over the wounded rock like a wondrous crystal balm.\n");
    add_item(({"stalagmite","stalagmites"}),"Of various heights, " +
        "the stalagmites date back to a different Age, when " +
        "Icewall was a warm land, and free water ran over its rocks. " +
        "The stalagmites look dangerous to the careless passerby - " +
        "their sharp points and icy edges seem as unforgiving as nature " +
        "can get.\n");

    set_tell_time(800);

    add_tell("Without warning, you lose your footing on the black " +
        "ice. Skidding sideways, you manage to regain your balance " +
        "by steadying yourself with hand placed upon the frosty wall.\n");
    add_tell("More snow slides down from the cliff, landing at " +
        "the entrance of the cave. The tunnel grows a bit darker.\n");
    add_tell("A distant cry echoes down the tunnel. The muted sound " +
        "is all but unrecognisable.\n");
    add_tell("There is some noise coming further from the east... " +
        "Grunting noise.\n");

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

{ return ("" +
    "You stand in a long and dark tunnel. Frost lines the walls, " +
    "and a layer of ice makes the floor slick and dangerous. " +
    "Further east the tunnel enters something akin to a huge " +
    "warehouse, while to the west, through a natural fissure, " +
    "you notice a stalagmite fenced cave.\n");
}


int
careless_entry()
{

    if((TP->query_stat(SS_DEX)) < random(160))
    {
        write("You carelessly attempt to enter the cave, but slip " +
            "on the thick ice and fall right by the fissure! Your " +
            "overconfidence costs you a " +
            "few bruises, as sharp stalagmites dig into your body. Maybe " +
            "next time you should try to pass the stalagmites more " +
            "carefully.\n");
        say(QCTNAME(TP) + " tried to carelessly walk west, into the " +
            "cave, but slipped and fell, bruising " + HIS(TP) + " body on the " +
            "sharp stalagmites.\n");
        TP->heal_hp(-100);
        return 1;
    }
    
    write("Without concern, you simply enter the fissure and walk " +
        "through the stalagmites. " +
        "Maybe its your luck, or maybe you were a penguin in your last " +
        "incarnation, but you navigate easily on the slick ice and " +
        "reach the cave safely.\n");
    say(QCTNAME(TP) + " with a careless stride easily finds " + HIS(TP) +
        "way through the sharp stalagmites and enters the cave.\n");
    tell_room(ROOMSK + "dark_cave", "Striding carelessly " +
        "through the stalagmites, " + QTNAME(TP) + " arrives from the " +
        "tunnel.\n");
    TP->move_living("through the fissure", ROOMSK + "dark_cave",1,0);
    return 1;   
}


int
pass(string str)
{
    if(str != "carefully through stalagmites")
    {
        notify_fail("Pass how? Through what?\n");
        return 0;
    }
    
    write("Picking your way carefully, you avoid the sharp spires " +
        "of the stalagmites, and enter the cave.\n");
    say(QCTNAME(TP) + " makes " + HIS(TP) + 
        " way through the sharp spires of " +
        "the stalagmites, and very carefully enters the cave.\n");
    tell_room(ROOMSK + "dark_cave", 
        "Winding " + HIS(TP) + " way " +
        "carefully through the sharp stalagmites " + QTNAME(TP) + 
        " arrives from the tunnel.\n");
    TP->move_living("through the fissure", ROOMSK + "dark_cave",1,0);
    
    return 1;
}

void
init()
{
    ::init();
    add_action(pass, "pass");
}
