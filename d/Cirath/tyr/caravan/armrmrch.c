/* armrmrch.c: Birk the armour merchants shop.
 * Updated to Raumdor inherits and standards
 * Also placed a non-readable, but examinable sign here
 * Damaris 5/2001
 */
inherit "/std/room";
inherit "/d/Cirath/lib/shop";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "/d/Cirath/common/mobber.h"

#define STORE  "/d/Cirath/tyr/caravan/armrstor"
#define SHOPKEEP "birk"
#define GONEFISHING !objectp(present(SHOPKEEP, TO))
string
query_shop_sign()
{
    return("\n        You examine the symbols and interpret the sign as.\n\n"+
      "          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n"+
      "          |        Birk's leather and hides        |\n"+
      "          |________________________________________|\n"+
      "          |                                        |\n"+
      "          |     Birk proudly supplies Tyr with     |\n"+
      "          |           leathers and hides.          |\n"+
      "          |                                        |\n"+
      "          |   This shop operates like any other.   |\n"+
      "          |   To see what items are for sale       |\n"+
      "          |          please use <list>.            |\n"+
      "          |                                        |\n"+
      "          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n"); 
}

void create_room()
{
    ::create_room();
    set_short("birk's leather and hides");
    set_long ("Thanks to his new location near Caravan Gate, Birk "+
              "has been doing brisk trade in used armour. Now situated "+
              "in a shack across the street from the weapons merchant, "+
              "the armoury has become a favored stop for local and "+
              "traveller alike. Some examples of Birk's work hang on the "+
              "walls, as does a sign. A door north is blocked by thick "+
              "metal bars while Caravan Way is to the south.\n");

    add_item(({"door", "bar", "bars", "metal bars", "metal bar"}),
              "Further proof of Birk's recent success, the bars are made "+
              "of rare steel, and so think that it would take a half-"+
              "giant to lift or bend them. They block the door fully.\n");
    add_cmd_item(({"bar", "bars", "metal bars", "metal bar", "door"}),
                   ({"bend", "lift", "open", "pull", "push"}),
              "Just how strong do you think you are anyway?\n");
    add_item(({"sign"}), query_shop_sign);
    INSIDE
    /*
     * The shop-related initializations.
     */
    config_default_trade();
    set_money_give_max(1000);
    set_store_room(STORE);
    set_shopkeep(TYR_NPC+"armrdude.c", this_object());

    add_exit(TYR_CARAVAN+"rd_cw_03.c", "south", 0, 1);
    add_exit(STORE, "north", wiz_check, 0, 1);
    clone_here(CIRATH_COMMON + "tbarrel")->move(this_object());
    reset_room();
}

int
shop_hook_allow_sell(object ob)
{
    if (GONEFISHING)
    {
        notify_fail("Sell to who?\n");
        return 0;
    }
    if (armour_filter(ob)) return 1;
    notify_fail("They only buy armour here.\n");
    return 0;
}

int
shop_hook_allow_buy(object ob)
{
    if (GONEFISHING)
    {
        notify_fail("Nobody seems to be here to sell you anything.\n");
        return 0;
    }
    return 1;
}
int
do_read(string str)
{
    if (str != "sign")
    {
	notify_fail("Read what?\n");
	return 0;
    }

    write("It is forbidden to read in Tyr.\n");
    return 1;
}
      
void init()
{
    ::init();
    init_shop();
    add_action(do_read, "read");
}
