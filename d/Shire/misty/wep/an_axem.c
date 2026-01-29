/*
 * Ancient twisted axe
 * Originally forged by the dwarves during the goblin wars of the 
 * First Age, and looted by goblins during that time. Held by Gashnak. 
 * Non magical version is an_axe.c, magical version an_axem.c
 * -- Finwe, Mar 2005
 */

inherit "/std/weapon";
inherit "/lib/keep";


#pragma save_binary

#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
 
int hit = 40 + random(5);
int pen = 40 + random(5);

void
create_weapon()
{
    seteuid(getuid(TO));
    set_name("axe");
    set_adj("ancient");
    set_adj("twisted");
    set_short("ancient twisted axe");
    set_long("This axe was forged by the dwarves ages ago. The axe " +
        "has a long handle and made from a black metal. A deadly looking " +
        "blade sits on it. The blade is forged of mithril and enscribed " +
        "with runes. It looks like the axe was looted during the goblin " +
        "wars in the First Age age. It has been twisted and used by " +
        "that race.\n");
    add_item(({"blade"}),
        "The blade is in the shape of a half circles and attached to " +
        "the top of the handle. The edge is sharp with runes etched into " +
        "the blade.\n");
    add_item("handle", 
        "The handle is made of some unknown black metal. It looks " +
        "strong and is polished smooth. \n");
    add_item(({"runes"}),
        "They are enscribed on the perimeter of the blade in an ancient " +
        "tongue.\n");

    set_default_weapon(hit, pen, W_AXE, W_SLASH | W_BLUDGEON, W_ANYH, TO);
    add_prop(OBJ_I_WEIGHT, 8000 + random(500));
    add_prop(OBJ_I_VOLUME, 1500 + random(200));
    add_prop(OBJ_I_VALUE, 5);
 
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));

    add_prop(MAGIC_AM_ID_INFO, ({
        "This " + short() + " is enchanted.\n", 10,
        "A faint sense of magic emanates from it.\n", 15,
        "The axe seems to hum with a song of dwarven power.\n", 20,
        "It looks to enable you to destroy your foes faster.\n",50}));
    add_prop(OBJ_S_WIZINFO, "This axe has a higher hit and pen.\n");

}
 
void
init()
{
    ::init();
}
