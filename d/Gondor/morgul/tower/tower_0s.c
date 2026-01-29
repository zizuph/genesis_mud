/*
 * /d/Gondor/morgul/tower/tower_0s.c
 * The south room on the ground floor of the Morgul Tower
 *
 * Olorin, 10-jan-1994
 * Morbeche, 20 Feb 2000 - Modified to make a player agree to
 *                         the power of the Nine before entering
 */
inherit "/d/Gondor/morgul/tower/tower.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define MORGUL_I_THRONE_WARNING "_morgul_i_throne_warning"

public int warning();
public void give_warning(object player);
public void get_answer(string str, object player);

void create_morgul_tower_room()
{
    set_level(0);
    set_room_type("large hall");
    set_extra_long("This is the south end of the hall. A row of mighty " +
        "pillars to the northwest divides it from the central part.");

    add_item(({"hall"}), BSN(
        "The halls extends to the northeast along a row of pillars. " +
        "Beyond the pillars lies the central part of the hall, which " +
        "you can reach by walking either north or west."));
    add_item(({"columns", "pillar", "pillars", "row", "rows", "row of pillars", "rows of pillars"}), BSN(
        "A rows of pillars runs diagonally across the large hall from " +
        "the northeast to the southwest. They divide this part of the hall " +
        "from the rest. Each of the pillars is several yards thick and made of " +
        "black stone."));

    NO_ROOF
    FLOOR
    WALLS

    add_exit(TOWER_DIR  + "tower_0c",  "north",     0, 1);
    add_exit(TOWER_DIR  + "tower_0e",  "northeast", 0, 1);
    add_exit(TOWER_DIR  + "tower_0sw", "west",  warning, 1);
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
