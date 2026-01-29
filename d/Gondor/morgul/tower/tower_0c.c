/*
 * /d/Gondor/morgul/tower/tower_0c.c
 * The central room on the ground floor of the Morgul Tower
 *
 * Olorin, 10-jan-1994
 *
 * Morbeche, 20 Feb 2000 -  Changed to make it so someone cannot
 *                          enter the throne room without agreeing
 *                          that the Nazgul may kill them at will
 *                          and instantly (so I can put in some
 *                          torture devices in the room that do 
 *                          damage and may kill them) 
 */
inherit "/d/Gondor/morgul/tower/tower.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define MORGUL_I_THRONE_WARNING  "_morgul_i_throne_warning"

public int warning();
public void give_warning(object player);
public void get_answer(string str, object player);

void create_morgul_tower_room()
{
    set_level(0);
    set_room_type("large hall");
    set_extra_long("The two rows of pillars extend to the northeast and " +
        "southwest as far as you can see. Running around one of the pillars " +
        "of the northwestern row, a spiral staircase is climbing up to the " +
        "next level of the tower.");

    add_item(({"hall"}), BSN(
        "Two rows of mighty pillars " +
        "divide the hall into three parts. Right now you are in the " +
        "central part between the tow rows. Walking through the pillars, " +
        "you can reach the other parts of the hall."));
    add_item(({"columns", "pillar", "pillars", "row", "rows", "row of pillars", "rows of pillars"}), BSN(
        "The two rows of pillars run diagonally across the large hall from " +
        "the northeast to the southwest. They divide the hall into three " +
        "parts. Each of the pillars is several yards thick and made of " +
        "black stone. In each row, one pillar is slightly thicker than the " +
        "others. In the northwestern row, around this pillar a spiral " +
        "staircase is running upwards."));
    add_item(({"staircase","stairs","spiral staircase"}), BSN(
        "The stairs are winding around the slightly thicker pillar in the " +
        "northwestern row. They are rather steep, and only a slim rail " +
        "protects against falling. The stairs probably lead to the next floor " +
        "of the tower, but their top is lost to view in utter darkness."));

    NO_ROOF
    FLOOR
    WALLS

    add_exit(TOWER_DIR  + "tower_0n",   "north",     0, 1);
    add_exit(TOWER_DIR  + "tower_0ne",  "northeast", 0, 1);
    add_exit(TOWER_DIR  + "tower_0e",   "east",      0, 1);
    add_exit(TOWER_DIR  + "tower_0s",   "south",     0, 1);
    add_exit(TOWER_DIR  + "tower_0sw",  "southwest", warning, 1);
    add_exit(TOWER_DIR  + "tower_0w",   "west",      0, 1);
    add_exit(TOWER_DIR  + "tower_1c",   "up",        0, 4);
    add_exit(CELLAR_DIR + "cellar_1c",  "down",      0, 1);
}

public void
get_answer(string str, object player)
{
    str = LOW(str);
    if ((str == "yes") || (str == "agree") ||
	(str == "aye") || (str == "accept"))
    {
        write(BSN("Enter and consider yourself warned!  The power of the " +
		  "Nine is absolute in His domain!"));
        player->add_prop(MORGUL_I_THRONE_WARNING, 1);
    }
    else
        write(BSN("Those who do not accept the rule of the Nine are " +
		  "unworthy of an audience!"));
}

public void
give_warning(object player)
{
    write("As you begin to enter the throne room, you feel paralyzed as " +
	  "a terrible power enters your mind.\n" +
          "A menacing voice whispers in your head:\n" +
          "    To enter the throne room of the Nine \n" +
	  "    is to place yourself at their terrible \n" +
	  "    mercy.  Do you truly wish to subject  \n"+
	  "    yourself to their scrutiny, knowing that \n" +
	  "    at any moment they may decide to destroy \n"+
"    your pathetic life?  Answer now, Yes or No!\n>");
    input_to(&get_answer(, player), 0);
}                                                                              

public int
warning()
{
    string  gname;

    gname = TP->query_guild_name_occ();

    if (stringp(gname))
    {
        if (gname == GUILD_NAME)
        {
	  if (!TP->query_nazgul())
	    {
            write("Tremble before the power of the Nine, "
		  + TP->query_morgul_title() + "!\n");
            return 0;
	    }
	  else
	    {
	      write("May your decisions be guided by the will of " +
		    "the Red Eye, "+ TP->query_morgul_title()+"!\n");
	      return 0;
	    }
        }
    }

    if (TP->query_prop(MORGUL_I_THRONE_WARNING))
    {
        write("Your life may be forfeit at the whim of the Nine!\n");
        return 0;
    }
    give_warning(TP);
    return 1;
}                                                   
