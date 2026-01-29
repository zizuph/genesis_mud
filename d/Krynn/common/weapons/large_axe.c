
/*
 * File name  : on_of_twin_axes.c
 * Description: One of the twin battle-axes which were bound together, but
 *              now, because of some reason are separated.             
 * Creator    : Blizzard
 * Date       : 28.03.2004
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include <tasks.h>

#define  TO_HIT              34
#define  TO_PEN              45

public void
create_weapon()
{
    set_name(({"twin-axe", "axe", "battle-axe" }));
    set_pname(({ "axes", "battle-axes", "twin-axes" }));
    set_adj( ({ "double-bladed", "moon-bladed", "twin", "battle" }) );

    set_short("large double-bladed battle-axe");
    set_pshort("large double-bladed battle-axes");

    set_long("You are holding a large, double-bladed battle-axes. " +
        "Such axes are favourite of strong warriors, as they can " +
        "inflict impressive wounds. A piece of gold chain hangs from " +
        "the handle of this weapon, but you are not sure what it was " +
        "used for. This battle-axe looks durable, but also is very heavy " +
        "so it is not easy to swing with it precisely. Each of its broad " +
        "bladed is shaped like a half moon and seems to be extremely " +
        "sharp.\n");
        
    set_hit(TO_HIT);
    set_pen(TO_PEN);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_ANYH);

    set_wf(TO);
    set_keep(1);
    set_likely_dull(1);
    set_likely_break(1);
    
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }) );
    add_prop(OBJ_S_WIZINFO, "This is one of the twin battle-axes, which " +
        "were bound together, but noware separated for some reason. " +
        "The enchantment that were placed upon it makes the axe heavier " +
        "if wielded as a single weapon. Also it no longer sheds light on " +
        "the surroundings.\n");
    add_prop(MAGIC_AM_ID_INFO, ({
        "This is one of the twin battle-axes. They were bound together " +
        "but now are separated.\n", 10,
        "The battle-axe is much heavier when wielded alone and no longer " +
        "sheds light on its surroundings.\n", 40
        }));
        
    add_prop(OBJ_I_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 15000);
    add_prop(OBJ_I_WEIGHT, 18000);
    add_prop(OBJ_I_VALUE, 1500 + random(500));
}

public mixed
wield(object ob)
{   
    if ( TP->resolve_task(1800, ({ SKILL_WEIGHT, 900, TS_STR })) < 0)
    {
        return "You try to wield the " + short() + ", but you lack " +
            "strength to do that.\n";
    }
                                
    return 0;   
}

