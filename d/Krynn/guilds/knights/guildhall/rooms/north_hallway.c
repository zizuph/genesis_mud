/* New Vingaard Keep North Hallway One */

#include <ss_types.h>
#include <macros.h>
#include "../../guild.h"

inherit IN_BASE;

object goldbanner, rosebanner;

string message = " The banners can probably be removed if you wish, or "+
                 "replaced, as the case may be.\n";

void
reset_vin_room()
{
}

string
extra_desc()
{
    if (P(goldbanner, TO) && P(rosebanner, TO))
    {
        return "A "+rosebanner->short()+" and a "+goldbanner->short()+
               " decorate the walls.\n";
    }
    else if (P(goldbanner, TO) && !P(rosebanner, TO))
    {
        return "A "+goldbanner->short()+" decorates the wall.\n";
    }
    else if (P(rosebanner, TO) && !P(goldbanner, TO))
    {
        return "A "+rosebanner->short()+" decorates the wall.\n";
    }
    else if (!P(rosebanner, TO) && !P(goldbanner, TO))
    {
        return "\n";
    }
}

string
long_desc()
{
    return "This is the northern hallway in the upper level of Vingaard " +
        "Keep. This room is only sparsely decorated, as it is a " +
        "connecting room. The sole ornament is a bearskin on the floor. " +
        "West is the post office, while east lies the Knights' Chamber. " +
        "The armoury of the Knights of Solamnia sits to the north. "
        +extra_desc();
}

string
gold_banner()
{
    if (P(goldbanner, TO))
    {
        return "A "+goldbanner->short()+" decorates the wall here. "+
               message;
    }
    else
    {
        return "Examine what?\n";
    }
}

string
rose_banner()
{
    if (P(rosebanner, TO))
    {
        return "A "+rosebanner->short()+" decorates the wall here. "+
               message;
    }
    else
    {
        return "Examine what?\n";
    }
}

string
banners()
{
    if (!P(rosebanner, TO) && !P(goldbanner, TO))
    {
        return "Examine what?\n";
    }    
    return extra_desc() + message;
}

void
create_vin_room()
{
    goldbanner = clone_object(VOBJ + "gold_banner");
    goldbanner->set_no_show();
    goldbanner->move(TO);
    rosebanner = clone_object(VOBJ + "rose_banner");
    rosebanner->set_no_show();
    rosebanner->move(TO);
    
    set_short("North Hallway");
    set_long("@@long_desc");
    
    AI(({"banner", "banners"}), "@@banners");
    AI("gold banner", "@@gold_banner");
    AI("rose banner", "@@rose_banner");
    AI(({"knights' chamber","chamber","Knights' Chamber","Chamber"}),
        "It is the gathering place of members of the Knights of Solamnia.\n");
    AI(({"office","post office"}),"It is where many Knights communicate " +
        "with the outside world.\n");
    AI("armoury","It is where the Knights of Solamnia keep their equipment, "+
        "when it is not in use.\n");
    AI("ceiling","The ceiling is composed of granite.\n");
    AI("floor","The floor is composed of granite. Part of it is covered " +
        "by a bearskin.\n");
    AI(({"walls","wall"}),"Every wall is made of granite, the solid rock " +
        "that most of Vingaard Keep is made of.\n");
    AI(({"granite","rock","solid rock"}),"It is a volcanic rock.\n");
    AI(({"skin","bearskin","fur"}),"The fur is of an Ice Bear, " +
        "most definitely killed in the Icewall region of Ansalon.\n");
    ACI(({"skin","bearskin","fur"}),({"lift","get","move"}),"The bearskin " +
        "seems content to remain where it is, although it is a certainty " +
        "that it would much rather still be on the bear.\n");
    
    AE(VROOM + "knight_po", "west", 0);
    AE(VROOM + "armoury", "north", 0);
    AE(VROOM + "knightroom", "east", 0);
    AE(VROOM + "startroom", "south", 0);
    
    reset_vin_room();
}

init()
{
    add_action("replace", "replace");
    add_action("remove", "remove");
    ::init();
}

int
replace(string str)
{
    
    NF("Replace what? A banner?\n");
    if (!str)
        return 0;
    
    if (str != "gold banner" && str != "rose banner")
    {
        return 0;
    }

    NF("You don't have a banner, or you don't have the ones that go here.\n");
    if (!P(goldbanner, TP) && !P(rosebanner, TP))
    {
        return 0;
    }
    
    NF("You don't have the "+str);
    if (str == "gold banner" && P(goldbanner, TP))
    {
        goldbanner->set_no_show();
        goldbanner->move(E(TP));
        write("You replace the "+goldbanner->short()+".\n");
        say(QCTNAME(TP)+" replaces the "+goldbanner->short()+".\n");
        return 1;
    }
    
    if (str == "rose banner" && P(rosebanner, TP))
    {
        rosebanner->set_no_show();
        rosebanner->move(E(TP));
        write("You replace the "+rosebanner->short()+".\n");
        say(QCTNAME(TP)+" replaces the "+rosebanner->short()+".\n");
        return 1;
    }
}

int
remove(string str)
{
    
    NF("Remove what? A banner?\n");
    if (!str)
        return 0;
    
    NF("Remove which banner? The rose banner or the gold banner?\n");
    if (str == "banner")
        return 0;
    
    NF("The "+str+" is not here.\n");
    if (str == "gold banner" && !P(goldbanner, TO))
        return 0;
    
    if (str == "rose banner" && !P(rosebanner, TO))
        return 0;
    
    if (str == "gold banner")
    {
        goldbanner->unset_no_show();
        goldbanner->unset_no_show_composite();
        goldbanner->move(TP);
        write("You gently take the "+goldbanner->short()+" from the wall.\n");
        say(QCTNAME(TP)+" gently takes the "+goldbanner->short()+" from the "+
            "wall.\n");
        return 1;
    }
    
    if (str == "rose banner")
    {
        rosebanner->unset_no_show();
        rosebanner->unset_no_show_composite();
        rosebanner->move(TP);
        write("You gently take the "+rosebanner->short()+" from the wall.\n");
        say(QCTNAME(TP)+" gently takes the "+rosebanner->short()+" from the "+
            "wall.\n");
        return 1;
    }
}
