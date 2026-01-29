/*
 * /d/Gondor/morgul/tower/tower_0w.c
 * The west room on the ground floor of the Morgul Tower
 *
 * Olorin, 10-jan-1994
 *
 * Revision history:
 *   Added functionality for magical transport to audience_chamber
 *     -Gorboth, 18-Sep-1997
 * Morbeche, 20 Feb 2000 - Modified so that player must agree to
 *                         let the Nazgul kill them before they
 *                         can enter the throne room
 */
#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower.c";

#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define MORGUL_I_THRONE_WARNING "_morgul_i_throne_warning"

#define  CHAMBER        "/d/Gondor/morgul/tower/audience_chamber"
#define  LOG_FILE       "morgul_chamber"

//  Prototypes
string  exa_peephole();
void    do_log(object ob, string logtxt);

public int warning();
public void give_warning(object player);
public void get_answer(string str, object player);

public void 
create_morgul_tower_room()
{
    set_level(0);
    set_room_type("large hall");
    set_extra_long("This is the west end of the hall. A row of"
           + " mighty black pillars to the southeast divides it from"
           + " the central part. A gleam of red light sparkles"
           + " from the wall here.");

    add_item(({"hall"}), BSN(
        "The halls extends to the northeast along a row of pillars. " +
        "Beyond the pillars lies the central part of the hall, which " +
        "you can reach by walking either south or east."));
    add_item(({"columns", "pillar", "pillars", "row", "rows", "row of pillars", "rows of pillars"}), BSN(
        "A rows of pillars runs diagonally across the large hall from " +
        "the northeast to the southwest. They divide this part of the hall " +
        "from the rest. Each of the pillars is several yards thick and made of " +
        "black stone."));
    add_item( ({"wall", "walls", "blocks", "stone blocks"}), BSN(
        "The walls are made of black square stone blocks. The blocks fit"
      + " so well that there are hardly any seams visible between them."
      + " The surface of the blocks has been polished so it is very smooth"
      + " and seems to absorb light. Engraved in the wall to the west"
      + " is the visage of a lidless eye."));
    add_item( ({"eye", "visage", "lidless eye",
                "visage of a lidless eye"}), BSN(
        "The eye has been cunningly carved into the stone of the wall,"
      + " and bears at its center a single dazzling ruby."));
    add_item( ({"ruby", "dazzling ruby", "rubies"}), BSN(
        "A single dazzling ruby of amazing size has been set into"
      + " the western wall to form the iris at the center of a lidless"
      + " eye which has been carved there."));
    add_item( ({"peephole", "peep hole", "hole"}), exa_peephole);

    add_no_roof();
    add_floor();

    add_exit(TOWER_DIR  + "tower_0n",  "northeast", 0, 1);
    add_exit(TOWER_DIR  + "tower_0c",  "east",      0, 1);
    add_exit(TOWER_DIR  + "tower_0sw", "south", warning, 1);
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

int
check_occupants()
{
    object *occupants,
            Chamber;

    CHAMBER->short();
    Chamber = find_object(CHAMBER);
    occupants = FILTER_PLAYERS(all_inventory(Chamber));

    return sizeof(occupants);
}

int
touch_eye(string str)
{
    object *others = FILTER_PLAYERS(all_inventory(TO));
    string  logtxt = " entered the morgul alcove ";
    int     i;

    if (str != "eye" && str != "ruby" && str != "rubies" &&
        str != "lidless eye" && str != "carving" &&
        str != "visage" && str != "engraving")
    {
        NFN0("What do you wish to " + query_verb() + "?");
    }

    if (TP->query_nazgul() < 1)
    {
        write("The carven visage flashes a brilliant red,"
              + " sending a sharp pain up your arm!\n");
        say(QCTNAME(TP) + " reaches out to touch the wall, and"
                        + " then instantly recoils as a sudden"
                        + " flash of red light flickers along "
                        + TP->query_possessive() + " arm.\n");

        TP->heal_hp(-20);
        if (TP->query_hp() <= 0)
        {
            TP->command("$wail");
            logtxt = " was KILLED by the eye ";
            do_log(TP, logtxt);
            TP->do_die(TO);
        }

        return 1;
    }

    if (check_occupants())
    {
        write(BSN("The visage carved into the wall glows dully as you "
                 + query_verb() + " it, illuminating a previously"
                + " invisible peephole below its carven form."));

        return 1;
    }

    tell_room(TO, "A burning flash of red light blinds you"
                + " momentarily!\n");

    while(i < sizeof(others))
    {
        others[i]->move_living("M", CHAMBER, 1, 1);
        do_log(others[i], logtxt);
        i++;
    }

    return 1;
}

void
init()
{
    ::init();

    add_action(touch_eye, "touch");
    add_action(touch_eye, "push");
    add_action(touch_eye, "pull");
    add_action(touch_eye, "feel");
    add_action(touch_eye, "rub");
}

string
exa_peephole()
{
    string  pdesc,
           *lnames;

    CHAMBER->load_me();
    lnames = FILTER_LIVE(all_inventory(find_object(CHAMBER)));

    pdesc = "Placing your eye to the peephole, you see the following,"
          + " bathed in a dull red glow:\n\n";

    pdesc += "This seems to be a featureless chamber with smooth"
           + " black stone walls.";

    if (sizeof(lnames) > 1)
    {
        pdesc += " The forms of " + COMPOSITE_LIVE(lnames) + " can"
               + " be clearly seen within, apparently absorbed in"
               + " discussion of some form. Yet all this seems to"
               + " you as from a great distance, and there is no"
               + " sound whatsoever to be heard.";
    }

    else if (sizeof(lnames) > 0)
    {
        pdesc += " The form of " + COMPOSITE_LIVE(lnames) + " can"
               + " be clearly seen within, moving slowly about the"
               + " chamber.";
    }

    else
    {
        pdesc += " Currently, the chamber appears to be empty.";
    }

    return BSN(pdesc);
}

void
do_log(object ob, string logtxt)
{
    log_file(LOG_FILE, ob->query_name() + " ("
      + ob->query_average_stat() + ")" + logtxt + "on: "
      + ctime(time()) + ".\n");

    return;
}
