/* coded by Torqual */
inherit "/d/Genesis/ship/ship";

#include <cmdparse.h>

#include "/d/Ansalon/common/defs.h" 
#include "/d/Ansalon/balifor/flotsam/ship3/local.h"

int no_board_enabled = 1;

private void
load_priv(string ob)
{
    (ob)->load_me();
    (ob)->set_no_disembark();
}

void
create_ship()
{
    object goar;

    seteuid(getuid());

    set_deck(DECK2);

    set_alarm(0.0, 0.0, &add_deck(DECK1));
    set_alarm(0.0, 0.0, &load_priv(DECK1));
    set_alarm(0.0, 0.0, &add_deck(DECK3));
    set_alarm(0.0, 0.0, &load_priv(DECK3));

    goar = clone_object(CAPTAIN);
    set_captain(goar);
    set_places_to_go(({
	PIER3,
	SEA1,
	SEA2,
	SEA3,
	SEA4,
	SEA5,
	MITHAS1,
	SEA5,
	SEA4,
	SEA3,
	SEA2,
	SEA1,
      }));

    set_time_between_stops(({
	23,
	3,2,3,3,2,
	24,
	2,3,3,2,3
      }));

    set_ticket_id(TICKET_NAME);
    set_name("ship");
    add_name("longboat");
    add_name(SHIP_NAME);
    add_adj("small");
    add_adj("gleaming");
    set_long("This longboat is outfitted with mast with large square " +
	"sail. Both sideboards, drapped with shields of variouse " +
	"sizes and colours, are polished up so the wood's "+
	"surface gleams with reflected light. At the stem of the boat "+
	"some craftsman placed figure of huge curved horn from what "+
	"the ship got its name - The Longhorn.  \n");
    add_item(({"sail", "large sail", "rectangular sail",
         "large rectangular sail"}),"Great red sail billow above you " +
         "as a strong wind off the Bloodsea blows past. " +
        "It sure helps oarsmen in their hard work.\n");
    add_item("mast", "Single beam of wood is set into the bottom of " +
        "longboat providing holding for large rectangular sail.\n");
    add_item(({"the Longhorn","longhorn","the longhorn","Longhorn"}),
      "You take appraising look at the longboat. Designed for swift " +
      "sailing and quick maneuvers, this ship is ideal for marine battles " +
      "as well as for quick raids on the villages up the shallow "+
      "rivers. On both its sides there are rows of 8 oars, currently pulled "+
      "in. Both sides of the longboat are decorated with "+
      "various war trophies\n");
    add_item(({"shields", "trophies", "war trophies"}), "Someone has "+
	"placed a row of shields at each of "+
	"ship's sideboards. Huge, medium and small of all shapes and colours, "+
	"they made impressive display of past glorry of the ship and "+
	"its crew.\n"); 

}

board(mixed what)
{
    object ticket, *tmp;
    object goar = present("goar", E(TO));
    
    if (!no_board_enabled &&
	(TP->query_guild_name_lay() != "Pirate of the Bloodsea") &&
	(TP->query_wiz_level() < 1 ) &&
	(!TP->query_npc()))
    {
	goar->command("say Right now we do not take "+
		"any passengers. Maybe next time.");
	return 1;
    }
    if (what && (!sizeof(tmp =
	  FIND_STR_IN_OBJECT(what, environment(this_player()))) ||
	this_object() != tmp[0]))
	return 0;
    if (this_player()->query_average_stat() >= 20)
	return ::board(what);

    write("You board the ship.\n");
    environment(this_player())->set_dircmd(what);
    this_player()->move_living("boarding the ship", query_deck()[0]);
    return 1;
}
