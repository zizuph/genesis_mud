/* New Vingaard Keep South Hallway One */

/* Added better response when trying to replace the brass banner.
 * This was done due to complaints from the knights that they
 * couldn't make it work.
 * -- Navarre December 2006 
 */

#include "../knight/guild.h"
#include <ss_types.h>
#include <macros.h>

inherit IN_BASE;

object brassbanner, kn1, kn2;
string message = " The banners can probably be removed if you wish, or "+
"replaced, as the case may be.\n";
object smith_rack;


void
reset_vin_room()
{
    if(!brassbanner)
    {
      brassbanner = clone_object(VOBJ + "brass_banner");
      brassbanner->set_no_show();
      brassbanner->move(TO);
    }

    if (!kn1)
    {
    kn1 = clone_object(VNPC + "gunthar_guard");
    kn1->move(TO);
    }
    if (!kn2)
    {
    kn2 = clone_object(VNPC + "gunthar_guard");
    kn2->move(TO);
    }

    if (!smith_rack)
    {
        smith_rack = clone_object(VOBJ + "smith_rack");
        smith_rack->move(TO);
    }

}

string
extra_desc()
{
    if (P(brassbanner, TO))
    return "A "+brassbanner->short()+" and a dark crimson Solamnic banner "+
    "bearing a copper dragon decorate the walls.\n";
    else
    return "A dark crimson Solamnic banner bearing a copper dragon deco"+
    "rates the wall.\n";
}

string
long_desc()
{
    return "This is the southern hallway in the upper level of " +
    "Vingaard Keep. Stairs lead upwards to the south, disappearing " +
    "beneath thick curtains as they rise. A slight draft blows " +
    "through this room. "+extra_desc();
}

string
brass_banner()
{
    if (P(brassbanner, TO))
    return "A "+brassbanner->short()+" decorates the wall here. "+
    message;
    else
    return "Examine what?\n";
}

string
copper_banner()
{
    return "A dark crimson Solamnic banner bearing a copper dragon decorates "+
    "the wall here. "+message;
}

string
banners()
{
    return extra_desc() + message;
}

void
create_vin_room()
{
    set_short("South Hallway");
    set_long("@@long_desc");

    AI(({"banner", "banners"}), "@@banners");
    AI("brass banner", "@@brass_banner");
    AI("copper banner", "@@copper_banner");
    AI("stairs","The stairs lead upwards to the south.\n");
    AI(({"draft","slight draft"}),"Caressing the curtains, the draft " +
      "originates from the south.\n");
    AI(({"thick curtains","curtains"}),"The thick red curtains " +
      "ripple in the slight draft. They are obviously meant to " +
      "prevent some of the cold from entering the guildhall.\n");
    AI(({"wall","ceiling","floor"}),"It is made of granite.\n");
    AI("walls","They are made of granite.\n");
    AI("granite","A grey rock that is volcanic in origin, quarried from " +
      "the Vingaard Mountains.\n");

    AE(VROOM + "startroom", "north", 0);
    AE(VROOM + "balcony", "south", "@@go_south", 0);

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
    if (!str)
    {
        if(P(brassbanner, TP))
        {     
            NF("Replace what? The brass banner?\n");
            return 0;
        }
        NF("Replace what? A banner?\n");
        return 0;
    }

    if(!P("banner", TP))
    {
        NF("But you don't even have a banner!\n");
	return 0;
    }


    if(str == "a banner")
    {
         NF("You have to be more specific!\n");
         return 0;
    }

    if (str != "brass banner" && str != "the brass banner")
    {
        NF("That is not the kind of banner that would go here.\n");
        return 0;
    }
    if (P(brassbanner, TP))
    {
      brassbanner->set_no_show();
      brassbanner->move(E(TP));
      write("You replace the "+brassbanner->short()+".\n");
      say(QCTNAME(TP)+" replaces the "+brassbanner->short()+".\n");
      return 1;
    }
    NF("You would need to actually have that banner before you can replace it here.\n");
    return 0;    
}

void
move_me(object liv)
{
    say("You look around suddenly, but see no sign of "+QTNAME(liv)+".\n");
    write("You step into what seems like a closet of sorts!\n");
    liv->move(VROOM + "armoire");
}

int
remove(string str)
{

    NF("Remove what? A banner?\n");
    if (!str)
    return 0;

    NF("Remove which banner? The brass banner or the copper banner?\n");
    if (str == "banner")
    return 0;

    NF("The "+str+" is not here.\n");
    if (str == "brass banner" && !P(brassbanner, TO))
    return 0;

    if (str == "brass banner")
    {
    brassbanner->unset_no_show();
    brassbanner->unset_no_show_composite();
    brassbanner->move(TP);
    write("You gently take the "+brassbanner->short()+" from the wall.\n");
    say(QCTNAME(TP)+" gently takes the "+brassbanner->short()+" from the "+
      "wall.\n");
    return 1;
    }

    if (str == "copper banner")
    {
    write("As you go to remove the dark crimson Solamnic banner bearing a "+
      "copper dragon from the wall, you realize that is covering some "+
      "kind of hidden passageway. Moving the banner aside, you step "+
      "through...\n");
    set_alarm(1.0, 0.0, "move_me", TP);
    return 1;
    }
}

int
go_south()
{
    write("You pass through the curtains and head up the stairs, outside.\n");
    return 0;
}

