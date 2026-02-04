/*
 * Magical Battleaxe for the Body Guard
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include <tasks.h>        
#include <formulas.h> 
#include <stdproperties.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <options.h>
#include <filter_funs.h>

void
create_weapon()
{
    set_name("battleaxe");
    set_pname("battleaxes");
    add_name("axe");
    set_adj("long-handled");
    set_adj("steel");
    set_short("long-handled steel battleaxe");
    set_pshort("long-handled steel battleaxes");
    set_long("The "+ short() +" seems lighter than usual. " +
       "Its two cresent shaped blades have been sharpened, then " +
       "serrated forming sinister looking edge's. The haft " +
       "is made from a solid piece of oak polished with oil to " +
       "help prevent warping then wrapped in soft leather straps " +
       "woven in a criss-cross pattern providing a better grip.\n");

    set_default_weapon(40, 47, W_AXE, W_IMPALE|W_SLASH, W_ANYH, TO);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_S_WIZINFO, "This weapon has been forged using magical "+
                   "means. the blade is sharper then usual.\n");

    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

    add_prop(MAGIC_AM_ID_INFO,
        ({"The blade has been honed to a very fine edge. Its quality " +
          "exceeds that of normal means. The weight of the " + 
          short() +" appears lighter than usual.\n",10}));

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_I_WEIGHT, 4500);
    add_prop(OBJ_I_VALUE, 7000);

    add_cmd_item("tag","read","The tag reads: axelean.\n");
}


init()
{
    ::init();
    add_action("do_axelean", "axelean");
}


int
do_axelean()
{

    write("You lean upon the " + short() +" attempting " +
       "catch your breath.\n");
    say(QCTNAME(TP) + " leans upon " +HIS_HER+" " +short()+ " attempting " + 
       "to catch " + HIS_HER + " breath.\n");

    return 1;
  }

