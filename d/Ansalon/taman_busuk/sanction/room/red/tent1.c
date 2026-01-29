#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCINROOM;
inherit "/d/Krynn/common/warfare/recruit_base";
inherit "/d/Krynn/common/warfare/warfare_map";

/* Redefine this function if you want only special people to be able to recruit.
 * Returns: 0 = Not allowed to recruit
 *          1 = Allowed to recruit
 * Default is 0
 */
int
hook_allowed_to_recruit(object who)
{
    if (!who)
	return 1;
    if (who->query_name() == "Aridor" || who->query_name() == "Arman" ||
      who->query_name() == "Milan")
	return 1;
    if (who->query_wiz_level())
	return 0;
    if (who->query_color() == "red" && who->query_dragonarmy_promotions() > 1)
	return 1;
    return 0;
}


/* Redefine this function if you want only special people to be able to raise funds.
 * Returns: 0 = Not allowed to raise funds
 *          1 = Allowed to raise funds
 * Default is 1
 */
int
hook_allowed_to_raise_funds(object who)
{
    if (who->query_name() == "Aridor" || who->query_name() == "Arman" ||
      who->query_name() == "Milan")
	return 1;
    if (who->query_wiz_level())
	return 0;
    return 1;
}

void
create_sanction_room()
{
    set_short("fund raising tent of the Red Dragonarmy");
    set_long("@@long_descr");

    add_item(({"white canvas tent","canvas tent","tent"}),
      "@@long_descr");
    add_item(({"sign","instructions"}),
      "@@read_recruit_fund_sign@@");
    add_cmd_item(({"sign","instructions"}),"read",
      "@@read_recruit_fund_sign@@");
    add_item(({"table", "war table", "map", "map of krynn"}), 
      "@@exa_table");
    add_item(({"soldiers","miniature soldiers", "armies"}), "Across " +
      "the map of Krynn miniature soldiers have been arrayed, " +
      "indicating the armies vying for control of these lands.\n");

    set_army("Red Dragon Army");

    add_exit(SRED + "r2","southwest",0);
}

string
long_descr()
{
    return "You stand within a white canvas tent used by the " +
    "Red Dragonarmy soldiers. The heat in here is rather " +
    "oppressive, not surprising considering the tents location, " +
    "on the edge of the city of fire and lava, Sanction. " +
    "A sign with instructions hangs here, while in a corner " +
    "of the tent a war table with a map of Krynn sits - miniature " +
    "soldiers of various armies arrayed across it." +
    "\n";
}

string
exa_table()
{
    say(QCTNAME(TP)+ " examines the soldiers arrayed on the war " +
        "table with interest.\n");
    return "You look at the map on the war table, examining the " +
        "locations of the various armies vying for control of " +
        "Krynn...\n" + exa_warmap();
}

void
init()
{
    init_recruit();
    ::init();
}

