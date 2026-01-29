#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit ICEINROOM;

void
create_icewall_room()
{
    set_short("A darkened, icy cave");
    set_long("@@long_descr@@");


    add_exit("cliff_new","west","@@noleave_cave",1,1);
    
    add_cmd_item(({"fissure","tunnel"}), "enter", "@@careless_entry@@");

    add_item("fissure","A natural opening in the east side of " +
        "the cave. Further on, it widens into a long, darkened " +
        "tunnel. However, the way there is blocked by many sharp " +
        "stalagmites.\n");
    add_item(({"tunnel","darkened tunnel"}),"You cannot see much " +
        "from here. Try to enter it for a closer look.\n");
    add_item(({"mound","fresh mound","fresh snow","mounds"}),"A" +
        " thick mound of fresh snow blocks the entrance to the cave. " +
        "You could, however, try to push your way in.\n");
    add_item(({"wall","walls"}),"You cannot tell much about it, " +
        "the layer of ice is simply too thick.\n");
    add_item(({"floor","carpet"}),"The floor is covered thick with " +
        "heavy snow. Due to the freezing temperature, it cracks loudly " +
        "under each and every step.\n");
    add_item(({"cave","inside","ceiling"}),"The cave is quite large" +
        ", a true consolation in this frigid wasteland. " +
        "It shelters you nicely from the biting wind, and is " +
        "just a bit too small to fit a dragon.\n");
    add_item(({"stalagmite","stalagmites"}),"Of various heights, " +
        "the stalagmites date back to a different Age, when " +
        "Icewall was a warm land, and free water ran over its rocks. " +
        "The stalagmites look dangerous to the careless passerby - " +
        "their sharp points and icy edges seem as unforgiving as nature " +
        "can get. One should never be too careless when walking through " +
        "them.\n");

    set_tell_time(800);
    add_tell("Shadows play on the wall, making the ice even more " +
        "gloomy and mysterious.\n");
    add_tell("Wind picks up at the entrance of the cave, scattering " +
        "snow and most likely chilling everybody outside to the bone. " +
        "You must admit you're quite happy with this cave protecting " +
        "you from the icy jabs.\n");
    add_tell("You think you have just heard a strange shriek " +
        "carried here by the everpresent freezing wind.\n");
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
    "This natural cave leads deeply into the side of the cliff. " +
    "Its walls are covered by solid, smooth ice, and "+
    "on the floor, heavy carpet of snow crunches under "+
    "your feet. " +
    "To the east, a fissure opens in the side of the cave. " +
    "Looking deeper, you see that it quickly turns into a wide tunnel " +
    "which leads upwards, towards what you believe is the " +
    "direction of the Icewall Castle. The mouth of the " +
    "tunnel is barbed with sharp and wicked looking " +
    "stalagmites. To the west, the cave opens, and over " +
    "mounds of fresh snow you can see the outside.\n");
}


int
noleave_cave()
{
    write("You attempt to walk out of the cave, but there is too " +
        "much snow blocking the exit! You could try to push through, " +
        "though.\n");
    say(QCTNAME(TP) + " tries to walk west, out of the cave, but mounds " +
        "of fresh snow block" + HIS(TP) + " way effectively.\n");
    return 1;
}

int
push(string str)
{
    if(str != "through snow")
    {
        notify_fail("Push through what?\n");
        return 0;
    }

    if((TP->query_stat(SS_STR)) < 100)
    {
        say(QCTNAME(TP) + " tried to make" + HIS(TP) + " way " +
            "through the snow but is too weak to do it.\n");
        write("You try to push through the mound of snow but " +
            "are too weak to continue.\n");
        TP->add_fatigue(-50);
        return 1;
    }
    
    if((TP->query_fatigue()) < 50)
    {
        say(QCTNAME(TP) + " tried to make" + HIS(TP) + " way " +
            "through the snow but is too tired to do it.\n");
        write("You try to push through the mound of snow but " +
            "are too tired continue.\n");
        TP->add_fatigue(-50);
        return 1;
    }
    
    write("Grudging your way through the mounds of snow, you " +
        "force your way out of the cave. Behind you, more snow " +
        "slides down from the cliff, obliterating your tracks.\n");
    say("With an effort, " + QTNAME(TP) + " pushes through " +
        "the mounds of snow at the base of the cliff " +
        "and exits the dark cave. Behind " + HIM(TP) + ", more " +
        "snow slides down from the cliff, blocking the path again.\n");
    tell_room(ROOMSK + "cliff_new", "Grudging " + HIS(TP) + " way " +
        "through the mound " +
        "of snow, " + QTNAME(TP) + " arrives from the cave.\n");
    
    TP->move_living("into the outside world", ROOMSK + "cliff_new",1,0);
    TP->add_fatigue(-50);
    
    return 1;
}


int
careless_entry()
{

    if(((TP->query_stat(SS_DEX))/2 + (TP->query_stat(SS_WIS)) / 2) < 
        TP->query_stat(SS_STR))
    {
        write("You carelessly attempt to enter the tunnel, but slip " +
            "on the thick ice and fall! Your overconfidence costs you a " +
            "few bruises, as sharp stalagmites dig into your body. Maybe " +
            "next time you should try to pass the stalagmites more " +
            "carefully.\n");
        say(QCTNAME(TP) + " tried to carelessly walk east, into the " +
            "tunnel, but slipped and fell, collecting a bloody bruise from the " +
            "sharp stalagmites.\n");
        TP->heal_hp(-(TP->query_max_hp() / 3));

        if (TP->query_hp() <= 0)
            TP->do_die(this_object());

        return 1;
    }
   
    write("Without concern, you simply walk through the stalagmites. " +
        "Maybe its your luck, or maybe you were a pinguin in your last " +
        "incarnation, but you navigate easily on the slick ice and " +
        "reach the fissure.\n");
    say(QCTNAME(TP) + " with a careless stride easily finds " + HIS(TP) +
        "way through the sharp stalagmites and enters the tunnel east.\n");
    tell_room(ROOMSK + "dark_tunnel", 
        "Striding carelessly " +
        "through the stalagmites, " + QTNAME(TP) + " arrives from the " +
        "cave.\n");
    TP->move_living("through the fissure", ROOMSK + "dark_tunnel",1,0);
    return 1;   
}


int
pass(string str)
{
    if(str != "carefully through stalagmites")
    {
        notify_fail(capitalize(query_verb()) + " how? Through what?\n");
        return 0;
    }
    
    write("Picking your way carefully, you avoid the sharp spires " +
        "of the stalagmites, and enter the tunnel.\n");
    say(QCTNAME(TP) + " makes " + HIS(TP) + 
        " way through the sharp spires of " +
        "the stalagmites, and very carefully enters the tunnel.\n");
    tell_room(ROOMSK + "dark_tunnel", "Winding " + HIS(TP) + " way " +
        "carefully through the sharp stalagmites " + QTNAME(TP) + 
        " arrives from the cave.\n");
    TP->move_living("through the fissure", ROOMSK + "dark_tunnel",1,0);

    return 1;
}

void
init()
{
    ::init();

    add_action(push, "push");
    add_action(pass, "pass");
    add_action(pass, "walk");

}
