/* New Vingaard Keep West Hallway One */

#include "../../guild.h"
#include <ss_types.h>
#include <macros.h>

inherit IN_BASE;

object bronzebanner, crownbanner;
string message = " The banners can probably be removed if you wish, or "+
"replaced, as the case may be.\n";

void
reset_vin_room()
{
}

string
extra_desc()
{
    if (P(bronzebanner, TO) && P(crownbanner, TO))
        return "A "+crownbanner->short()+" and a "+bronzebanner->short()+
    " decorate the walls.\n";
    else if (P(bronzebanner, TO) && !P(crownbanner, TO))
        return "A "+bronzebanner->short()+" decorates the wall.\n";
    else if (P(crownbanner, TO) && !P(bronzebanner, TO))
        return "A "+crownbanner->short()+" decorates the wall.\n";
    else if (!P(crownbanner, TO) && !P(bronzebanner, TO))
        return "\n";
}

string
long_desc()
{
    return "This is the western hallway in the upper level of " +
    "Vingaard Keep. The sturdy walls of the Keep surround " +
    "you, a reminder of the steadfast discipline of the Knights " +
    "of Solamnia. A feeling of peace radiates from the west. " +
    "A mounted boar's head stares down at you from the wall. Hanging " +
    "beside it is a small plaque. "+extra_desc();
}

string
bronze_banner()
{
    if (P(bronzebanner, TO))
        return "A "+bronzebanner->short()+" decorates the wall here. "+
    message;
    else
        return "Examine what?\n";
}

string
crown_banner()
{
    if (P(crownbanner, TO))
        return "A "+crownbanner->short()+" decorates the wall here. "+
    message;
    else
        return "Examine what?\n";
}

string
banners()
{
    if (!P(crownbanner, TO) && !P(bronzebanner, TO))
        return "Examine what?\n";
    
    return extra_desc() + message;
}

void
create_vin_room()
{
    bronzebanner = clone_object(VOBJ + "bronze_banner");
    bronzebanner->set_no_show();
    bronzebanner->move(TO);
    crownbanner = clone_object(VOBJ + "crown_banner");
    crownbanner->set_no_show();
    crownbanner->move(TO);
    
    set_short("West Hallway");
    set_long("@@long_desc");
    
    AI(({"banner", "banners"}), "@@banners");
    AI("bronze banner", "@@bronze_banner");
    AI("crown banner", "@@crown_banner");
    AI(({"walls","wall"}),"The walls of granite impose a silent feeling of " +
        "something very ancient and reverent.\n");
    AI("floor","Of granite, it is the sturdy foundation on which you " +
        "tread.\n");
    AI("ceiling","The ceiling floats high above you.\n");
    AI(({"head","boar","mounted boar","mounted head","mounted boar's head",
                "boar's head"}),"The boar stares down at you with glassy eyes. " +
        "Tusks sprout from its snout.\n");
    AI("tusks","They appear to be quite sharp.\n");
    AI(({"glassy eyes","eyes"}),"It is almost as if the boar was staring " +
        "right back at you!\n");
    AI("snout","The snout is in fine condition, although it misses its " +
        "truffle snuffling days, to be sure.\n");
    AI(({"small plaque","plaque"}),"The plaque is modest, simple bronze " +
        "on maple.\n");
    ACI(({"plaque","small plaque"}),"read","\nThis boar killed by William " +
        "Fletcher, Knight of the Crown.\nThe tenth of Gildember, 336 AC.\n");
    
    AE(VROOM + "chapel", "west", 0);
    AE(VROOM + "startroom", "east", 0);
    
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
    
    if (str != "bronze banner" && str != "crown banner")
        return 0;
    
    NF("You don't have a banner, or you don't have the ones that go here.\n");
    if (!P(bronzebanner, TP) && !P(crownbanner, TP))
        return 0;
    
    NF("You don't have the "+str);
    if (str == "bronze banner" && P(bronzebanner, TP))
        {
        bronzebanner->set_no_show();
        bronzebanner->move(E(TP));
        write("You replace the "+bronzebanner->short()+".\n");
        say(QCTNAME(TP)+" replaces the "+bronzebanner->short()+".\n");
        return 1;
    }
    
    if (str == "crown banner" && P(crownbanner, TP))
        {
        crownbanner->set_no_show();
        crownbanner->move(E(TP));
        write("You replace the "+crownbanner->short()+".\n");
        say(QCTNAME(TP)+" replaces the "+crownbanner->short()+".\n");
        return 1;
    }
}

int
remove(string str)
{
    
    NF("Remove what? A banner?\n");
    if (!str)
        return 0;
    
    NF("Remove which banner? The crown banner or the bronze banner?\n");
    if (str == "banner")
        return 0;
    
    NF("The "+str+" is not here.\n");
    if (str == "bronze banner" && !P(bronzebanner, TO))
        return 0;
    
    if (str == "crown banner" && !P(crownbanner, TO))
        return 0;
    
    if (str == "bronze banner")
    {
        bronzebanner->unset_no_show();
        bronzebanner->unset_no_show_composite();
        bronzebanner->move(TP);
        write("You gently take the "+bronzebanner->short()+" from the wall.\n");
        say(QCTNAME(TP)+" gently takes the "+bronzebanner->short()+" from the "+
            "wall.\n");
        return 1;
    }
    
    if (str == "crown banner")
    {
        crownbanner->unset_no_show();
        crownbanner->unset_no_show_composite();
        crownbanner->move(TP);
        write("You gently take the "+crownbanner->short()+" from the wall.\n");
        say(QCTNAME(TP)+" gently takes the "+crownbanner->short()+" from the "+
            "wall.\n");
        return 1;
    }
}

