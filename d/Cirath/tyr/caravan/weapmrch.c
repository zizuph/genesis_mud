/* weapmrch.c: The weapon shop of Tyr.
 * Updated to Raumdor inherits and standards
 * Also placed a non-readable, but examinable sign here
 * Damaris 5/2001
 */
inherit "/std/room";
inherit "/d/Cirath/lib/shop";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "/d/Cirath/common/mobber.h"


#define STORE  "/d/Cirath/tyr/caravan/weapstor"
#define SHOPKEEP "grik"
#define GONEFISHING !objectp(present(SHOPKEEP, TO))
string
query_shop_sign()
{
    return("\n        You examine the symbols and interpret the sign as.\n\n"+
      "          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n"+
      "          |            Grik's Weaponry             |\n"+
      "          |________________________________________|\n"+
      "          |                                        |\n"+
      "          |     Grik proudly supplies Tyr with     |\n"+
      "          |           much needed weapons.         |\n"+
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
    set_short("grik's weaponry");
    set_long("With the destruction of Sword Street during the plague-"+
             "spawned riots, Grik was forced to move his shop to Caravan "+
             "Way. Business in the sandstone brick structure has been "+
             "superb, especially after the purchase of Tentavvar, "+
             "who had been sold into slavery for stealing from a noble. "+
             "Archways lead north and east to Caravan Way and Tentavvar's "+
             "workroom, while a massive stone door leads south. A sign "+
             "hangs among various weapons that Grik has for sale.\n");

    add_item(({"door", "stone door"}),
              "Its the thickest door you have ever seen, and made of "+
              "solid stone. You would guess it to be the storeroom.\n");
    add_cmd_item(({"door", "stone door"}),
                 ({"open", "pull", "push"}),
              "Just how strong do you think you are anyway?\n");
    add_item(({"sign"}), query_shop_sign);
    INSIDE
    /*
     * The shop-related initializations.
     */
    config_default_trade();
    set_money_give_max(1000);
    set_store_room(STORE);
    set_shopkeep(TYR_NPC+"weapdude.c", this_object());

    add_exit(TYR_CARAVAN+"rd_cw_03.c", "north", 0, 1);
    add_exit(TYR_BONESMITH+"bonesmith.c", "east", 0, 1); 
    add_exit(STORE, "south", wiz_check, 0, 1);
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
    if (weapon_filter(ob)) return 1;
    notify_fail("They only buy weapons here.\n");
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


