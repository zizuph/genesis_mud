/* New Vingaard Keep West Hallway One */

#include "/d/Krynn/common/defs.h"
#include "../../guild.h"
#include <ss_types.h>
#include <macros.h>

inherit IN_BASE;

object silverbanner, swordbanner, mirror;
object guard;
object misc_rack;

string message = " The banners can probably be removed if you wish, or "+
"replaced, as the case may be.\n";

void
reset_vin_room()
{
    if (!guard)
    {
    guard = clone_object(VNPC + "gunthar_guard");
    guard->move(TO);
    }

    if (!misc_rack)
    {
        misc_rack = clone_object(VOBJ + "misc_rack");
        misc_rack->move(TO);
    }


}

string
extra_desc()
{
    if (P(silverbanner, TO) && P(swordbanner, TO))
    return "A "+swordbanner->short()+" and a "+silverbanner->short()+
    " decorate the walls.\n";
    else if (P(silverbanner, TO) && !P(swordbanner, TO))
    return "A "+silverbanner->short()+" decorates the wall.\n";
    else if (P(swordbanner, TO) && !P(silverbanner, TO))
    return "A "+swordbanner->short()+" decorates the wall.\n";
    else if (!P(swordbanner, TO) && !P(silverbanner, TO))
    return "\n";
}

string
long_desc()
{
    return "This is the eastern hallway, leading towards an office "+
    "to the east. Leaning against the north wall is a silvered mirror, "+
    "and the hub of the hallways is to the west. "+extra_desc();
}

string
silver_banner()
{
    if (P(silverbanner, TO))
    return "A "+silverbanner->short()+" decorates the wall here. "+
    message;
    else
    return "Examine what?\n";
}

string
sword_banner()
{
    if (P(swordbanner, TO))
    return "A "+swordbanner->short()+" decorates the wall here. "+
    message;
    else
    return "Examine what?\n";
}

string
banners()
{
    if (!P(swordbanner, TO) && !P(silverbanner, TO))
    return "Examine what?\n";

    return extra_desc() + message;
}

void
create_vin_room()
{
    silverbanner = clone_object(VOBJ + "silver_banner");
    silverbanner->set_no_show();
    silverbanner->move(TO);
    swordbanner = clone_object(VOBJ + "sword_banner");
    swordbanner->set_no_show();
    swordbanner->move(TO);

    set_short("East Hallway");
    set_long("@@long_desc");

    AI(({"banner", "banners"}), "@@banners");
    AI("silver banner", "@@silver_banner");
    AI("sword banner", "@@sword_banner");
    AI("walls","The walls are constructed of typical granite, with the " +
      "exception of the east wall.\n");
    AI(({"north wall","south wall"}),"It is constructed of the typical " +
      "granite.\n");
    AI("west wall","There is no west wall.\n");
    AI("east wall","The east wall is a construction of rocks and mortar. " +
      "Perhaps something is being constructed behind it.\n");
    AI(({"rocks","mortar","rocks and mortar","construction"}),"Work " +
      "is not completed, by the looks of it.\n");
    AI(({"typical granite","granite"}),"The granite is grey, with flecks " +
      "of white and black.\n");
    AI(({"ceiling","floor"}),"It is made of the typical granite.\n");

    AE(VROOM + "startroom", "west", 0);
    AE(VROOM + "war_room", "east", "@@check_knight");

    reset_vin_room();

    mirror = clone_object(VOBJ + "mirror.c");
    mirror->move(TO);


}

init()
{
    add_action("replace", "replace");
    add_action("remove", "remove");
    add_action("allow", "allow");
    ::init();
}

int
check_knight()
{
    string str;

    if (!guard || !P(guard, E(TP)))
    return 0;

    if (TP->query_wiz_level())
    return 0;

    if (TP->query_knight_sublevel() == 11)
    {
    if ((ADMIN)->is_grandmaster(TP->query_name()))
    {
        write("The "+guard->short()+" lets you pass, recognizing "+
          "you as the Grand Master.\n");
        return 0;
    }

    if (TP->query_knight_level() == 3)
        str = "High Warrior";
    else if (TP->query_knight_level() == 4)
        str = "High Clerist";
    else if (TP->query_knight_level() == 5)
        str = "High Justice";

    write("The "+guard->short()+" lets you pass, recognizing "+
      "you as the "+str+".\n");
    return 0;
    }

    if (TP->has_position() == POSITIONS[1])
    {
    write("Recognizing you as the Swordmaster of Solamnia, the "+
      guard->short()+" allows you to pass.\n");
    return 0;
    }

    if (TP->has_position() == POSITIONS[2] ||
      TP->has_position() == POSITIONS[3] ||
      TP->has_position() == POSITIONS[4])
    {
    write("Recognizing you as a leader in the armies of Solamnia, "+
      "you are allowed to pass by the "+guard->short()+".\n");
    return 0;
    }

    if (!TP->has_position() && !TP->query_prop("_i_may_pass"))
    {
    write("The "+guard->short()+" refuses to let you pass, and "+
      "tells you that a ranking Knight must 'allow' you to "+
      "enter the room to the east.\n");
    return 1;
    }

    write("The "+guard->short()+" remembers you and lets you pass.\n");
    return 0;
}

int
allow(string str)
{
    NF("Allow whom to enter?\n");
    if (!str)
    return 0;

    NF("You may not vouch for others.\n");
    if (!TP->has_position() && TP->query_knight_sublevel() != 11)
    return 0;

    NF("There is no one of that name here!\n");
    if (!find_living(L(str)) || !P(find_living(L(str)), E(TP)))
    return 0;

    write("You vouch for "+C(str)+" to pass.\n");
    find_living(L(str))->catch_msg(QCTNAME(TP)+" vouches for you to "+
      "pass.\n");
    find_living(L(str))->add_prop("_i_may_pass", 1);
    return 1;
}

int
replace(string str)
{

    NF("Replace what? A banner?\n");
    if (!str)
    return 0;

    if (str != "silver banner" && str != "sword banner")
    return 0;

    NF("You don't have a banner, or you don't have the ones that go here.\n");
    if (!P(silverbanner, TP) && !P(swordbanner, TP))
    return 0;

    NF("You don't have the "+str);
    if (str == "silver banner" && P(silverbanner, TP))
    {
    silverbanner->set_no_show();
    silverbanner->move(E(TP));
    write("You replace the "+silverbanner->short()+".\n");
    say(QCTNAME(TP)+" replaces the "+silverbanner->short()+".\n");
    return 1;
    }

    if (str == "sword banner" && P(swordbanner, TP))
    {
    swordbanner->set_no_show();
    swordbanner->move(E(TP));
    write("You replace the "+swordbanner->short()+".\n");
    say(QCTNAME(TP)+" replaces the "+swordbanner->short()+".\n");
    return 1;
    }
}

int
remove(string str)
{

    NF("Remove what? A banner?\n");
    if (!str)
    return 0;

    NF("Remove which banner? The sword banner or the silver banner?\n");
    if (str == "banner")
    return 0;

    NF("The "+str+" is not here.\n");
    if (str == "silver banner" && !P(silverbanner, TO))
    return 0;

    if (str == "sword banner" && !P(swordbanner, TO))
    return 0;

    if (str == "silver banner")
    {
    silverbanner->unset_no_show();
    silverbanner->unset_no_show_composite();
    silverbanner->move(TP);
    write("You gently take the "+silverbanner->short()+" from the wall.\n");
    say(QCTNAME(TP)+" gently takes the "+silverbanner->short()+" from the "+
      "wall.\n");
    return 1;
    }

    if (str == "sword banner")
    {
    swordbanner->unset_no_show();
    swordbanner->unset_no_show_composite();
    swordbanner->move(TP);
    write("You gently take the "+swordbanner->short()+" from the wall.\n");
    say(QCTNAME(TP)+" gently takes the "+swordbanner->short()+" from the "+
      "wall.\n");
    return 1;
    }
}





