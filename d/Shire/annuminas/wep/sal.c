/* Axe forged by the Dunedain of Annuminas. 
 * Wielded by a Orc captain patrolling the area.
 * By Finwe, April 2002
 */

inherit "/std/weapon";
inherit "/lib/keep";
inherit "/cmd/std/command_driver";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <options.h>


#define STR(x) x->query_stat(SS_STR)
#define WEAPON_HIT 40
#define WEAPON_PEN 40

object wielder;

void
create_weapon()
{
    set_name("lochaber");
    add_name("axe");
    add_pname(({"axes","lochaber"}));
    set_adj("strong");
    set_adj("ancient");
    set_short("strong ancient lochaber");
    set_long("This is a "+short()+". It was given as a gift to the " +
        "Kings of the Dunedain when they resided in Annuminas. Now, " +
        "it has been plundered from the armory of that destroyed city. " +
        "It looks like it was once a great weapon, well balanced and " +
        "deadly, for the edges are sharp and it looks hefty, despite " +
        "its age. A faint sense of magic seems to emanate from it, " +
        "yet doesn't seem strong enough to do any good. Wielded by a " +
        "skilled warrior, the "+short()+" can probably do some " +
        "serious damage.\n");

    add_item(({"blades"}),
        "They are both half circles of steel extending from the handle " +
        "by a ridge of metal. They are secured to the handle by steel " +
        "rivets.\n");
    add_item(({"metal ridge", "ridge of metal"}),
        "The ridge of metal is part of the blades. It is narrow with " +
        "one end connected to the backs of both blades and the other " +
        "end riveted to the top of the handle.\n");
    add_item(({"rivets", "rivet", "steel rivets", "steel rivet", 
            "steel pins", "steel oin", "pin", "pins"}),
        "The rivets are steel pins that hold the blades to the top " +
        "of the handle. The tops of the rivets are engraved inividually " +
        "with either a star, a moon or a sun.\n");
    add_item(({"handle", "haft"}),
        "The handle is a long rod of steel tapering to the top. Two " +
        "large blades are attached to the top of the handle.\n");
    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_AXE);
    set_dt(W_IMPALE | W_BLUDGEON);
    set_hands(W_ANYH);
    set_wf(TO);
    add_prop(OBJ_M_NO_SELL,"The "+short()+" is too valuable to sell.\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"Given as a gift by the Dwarves before " +
        "the Last Alliance to the kings of the Dunedain, the axe was " +
        "once a very great weapon. Now, it is but a shadow of its  "+
        "former strength. Nonetheless, it still retains some power.\n",1}));


    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(WEAPON_HIT,WEAPON_PEN));

    seteuid(getuid(TO));
}

init()
{
    ::init();
    add_action("do_wield", "wield");
}


int
do_wield()
{
    TO->query_hands();
    if(STR(TP)>75)
    {
        write("You raise the axe above your head and roar with battle lust.\n");
        tell_room(QCTNAME(TP) + " raises the "+short()+" above "+HIS_HER(TP)+
            " head and roars with battle lust.\n");
    }

    return 0;
}

int
query_hands()
{

    if(STR(TP)>75)
        return wep_hands = W_ANYH;
    else 
	    return wep_hands = W_BOTH;
}
