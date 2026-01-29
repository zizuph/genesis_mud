#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/estwilde/local.h"
#include "../guild.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Krynn/common/warfare/warfare.h"

inherit DWARF_IN;
inherit "/d/Krynn/common/warfare/recruit_base";
inherit WARFARE_MAP;

void
reset_dwarf_room()
{
    return;
}

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
    if (who->query_real_name() == GUILD_WIZ)
	return 1;
    if (who->query_wiz_level())
	return 0;
    if (who->query_guild_name_occ() == "Dwarven Warriors of the Neidar Clan" &&
	who->query_guild_leader_occ())
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
    if (who->query_real_name() == GUILD_WIZ)
	return 1;
    if (who->query_wiz_level())
	return 0;
    return 1;
}

create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"hall of warriors","hall"}),
      "You stand in the Hall of Warriors, the hall where " +
      "the dwarven clan members and warriors gather " +
      "together.\n");
    add_item(({"passage","storeroom"}),
      "To your north a passage leads to the storeroom " +
      "used by the clan warriors to store their equipment " +
      "when they are not using them.\n");
    add_item(({"chamber of the elders","chamber","sky-blue curtain",
	"curtain"}),
      "To your south a sky-blue curtain separates this room " +
      "from the Chamber of the Elders, the place where the " +
      "clan council gather to discuss council matters.\n");
    add_item(({"table", "war table", "map", "map of krynn"}), 
      "@@exa_table");
    add_item(({"soldiers","miniature soldiers", "armies"}), "Across " +
      "the map of Krynn miniature soldiers have been arrayed, " +
      "indicating the armies vying for control of these lands.\n");

    add_item(({"hole","small hole"}),
      "The hole is very small, just big enough for a coin to pass through. "+
      "It is dark and probably very deep since all the coins that were "+
      "tithed so far are perfectly lost in it.\n");
    add_item(({"sign","instructions"}),
      "@@read_recruit_fund_sign@@");
    add_cmd_item(({"sign","instructions"}),"read",
      "@@read_recruit_fund_sign@@");

    add_exit(GUILD_ROOMS + "store","north",0);
    add_exit(GUILD_ROOMS + "start","west",0);
    add_exit(GUILD_ROOMS + "common","east",0);
    add_exit(GUILD_ROOMS + "elder","south","@@elder_enter");

    clone_object(EPATH + "/obj/clan_board")->move(TO);
    reset_dwarf_room();

    set_army(NEIDAR_ARMY);
}

int
elder_enter()
{
    if(TP->test_bit("Ansalon",3,3) && TP->test_bit("Ansalon",3,4))
    {
	write("You are in disgrace! You cannot enter the council " +
	  "chambers.\n");
	return 1;
    }

    if(TP->test_bit("Ansalon",3,3))
    {
	write("Welcome Thane of the Hill Dwarves!\n");
	return 0;
    }
    if(TP->test_bit("Ansalon",3,4))
    {
	write("Welcome Elder!\n");
	return 0;
    }
    if(TP->query_stat(SS_OCCUP) > 167)
    {
	write("Welcome Chieftain to the council chambers!\n");
	return 0;
    }

    write("Only council members can enter the Chamber of the Elders.\n");
    return 1;
}

string
short_descr()
{
    return "Board room in the Hall of Warriors";
}

string
long_descr()
{
    return "You stand in the board room of the Hall of Warriors, " +
        "where the dwarves gather to discuss various matters of " +
        "varying importance. To your north is an open passage " +
        "that leads to a storeroom, while to your south " +
        "a sky-blue curtain separates this room from the " +
        "Chamber of the Elders. There is also a small hole in " +
        "the wall and a sign with instructions hanging above it. " +
        "A war table sits to the side of the room with a map of " +
        "Krynn upon it, and miniature soldiers of various armies " +
        "arrayed across it indicating who controls what battlefield.\n";
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

