
/*
 * Louie April 2006 - Set greed to 100.
 */
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit "/d/Ansalon/taman_busuk/sanction/std/i_room_base";
inherit "/lib/shop";
inherit "/d/Ansalon/common/cheater";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#define STORE_ROOM SCITY + "pawn_store"

void
create_sanction_room()
{
    config_default_trade();
    set_money_greed_buy(100);
    set_money_greed_sell(100);
    set_short("The Thieves Underground, before a shadowy pawn shop");
    set_long("You find yourself under the slums of Sanction at the beginning " +
      "of the cities catacombs. A torch hangs from an iron sconce that " +
      "is secured to one of the stone walls here, its sputtering " +
      "light casting deep shadows around you. In the wall to " +
      "your north a small window has been cut into a neighbouring " +
      "basement, and is used by the local thieves of this " +
      "city as a pawn shop, where they can get rid of hot items " +
      "and buy necessary supplies. You can <list> and " +
      "<sell> items here. A ladder here leads up and out " +
      "while a passageway into the Thieves Underground starts to " +
      "your south.\n");

    add_item(({"catacombs","passageway","thieves underground",
	"underground"}),
      "You stand at the beginning of the Thieves Underground, a maze " +
      "of passageways and catacombs beneathe the city of Sanction " +
      "that are used by various denizens ranging from thieves, " +
      "to curious kender, to the walking dead and various nasties " +
      "that live in such subterannean areas.\n");
    add_item(({"torch","iron sconce","sconce"}),
      "A torch rests in a rust iron sconce, lighting the area " +
      "in a malevolent glow.\n");
    add_item(({"wall","north","window","small window","shop","pawn shop"}),
      "To your north is a small window. Goods pass through " +
      "from here into a neighbouring basement, traded for cash, making " +
      "this place the unofficial pawn store for all local thieves.\n");
    add_item("basement","You cannot see into the basement, as it " +
      "is far too dark in there.\n");
    add_item("ladder","A ladder leads up to a local brothel from " +
      "here.\n");

    add_exit(SCITY + "brothel_north","up",0);
    add_invis_exit(SCITY + "pawn_store","north","@@wiz_check");
    add_exit("","south","@@enter_underworld");


    set_store_room(STORE_ROOM);
}

int
enter_underworld()
{
    write("Fumes from the local volcanoes fill these caverns at the " +
      "moment. Come back later when they have been dispersed.\n");
    return 1;
}

void
init()
{
    ::init();   /* You MUST do this in a room-init */
    init_shop(); /* Get the commands from the shop */
}


void
init_shop()
{    
    add_action("do_list", "list");
    add_action("do_buy", "buy");
    add_action("do_sell", "sell");
    add_action("do_value", "value");
    add_action("do_show","show");

}

/*
* Function name:   wiz_check
* Description:     Check if a player is a wizard
   * Returns:         0 if the player is a wizard
   *                  1 otherwise
*/
int
wiz_check()
{
    if(this_player()->query_wiz_level() || this_player()->query_npc())
	return 0;
    write("You try and climb through the small window, but a " +
      "shadowy figure on the other side laughs and pushes you " +
      "back.\n");
    say(QCTNAME(TP) + " tries to climb through the window " +
      "to your north but fails.\n");
    return 1;
}

int
do_buy(string str)
{
    if (check_cheater(this_player()))
	return 1;
    return ::do_buy(str);
}

int
do_sell(string str)
{
    if (check_cheater(this_player()))
	return 1;
    return ::do_sell(str);
}
