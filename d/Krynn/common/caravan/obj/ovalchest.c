/*
 *      /w/vencar/caravan/obj/ovalchest.c
 *
 *      The secured chest that holds a dragon egg.
 *      Created by Vencar 07/10/2003
 *
 *      Copyright by Peter Bech Lund (Vencar)
 *      10/2003
 *
 *  Based on trapped_chest.c from icewall
 *  found in Krynn.
*/

inherit "/std/receptacle";
inherit "/d/Genesis/lib/trap";
#include "../wagon/wagon.h"
#include "fire.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>


public void
create_receptacle()
{
    set_name("chest");
    set_adj("huge");
    add_adj("egg-shaped");
    set_pshort("white golden-plated eggs");

    set_long("The white golden-steel conical plates with their tips pointing " +
     "outwards forms into a priceless golden egg. " +
     "Each plate mix together with the next, beautifully crafted " +
     "to fit, leaving no trace of what keeps them together. " +
     "The egg is the size of two humans, or a troll, making the value of it " +
     "more than a small kingdom. A peculiar green glow " +
     "shines through the miniscule gaps between the white " +
     "golden-plates.\n" +
     "@@trap_desc@@");

    set_trap_level(60);

    set_trap_desc("You see no physical trap here... Most likely, its " +
       "something magic.\n");

    add_prop(MAGIC_AM_ID_INFO,
      ({"This egg is magically trapped!\n", 1,
        "A magical green light shines through the small gaps between the " +
        "golden plates, indicating something menacing will happen if one " +
        "tries to open it.\n "
        , 10, "The trap is strong and very dangerous", 20,
        "The trap cannot be disarmed, however " +
        "it can be dispelled by magic.\n", 55}));

    add_prop(MAGIC_AM_MAGIC,({60,"enchantment"}));
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_MAX_WEIGHT, 250000);
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(CONT_I_MAX_VOLUME, 300000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_CLOSED, 1);

    add_prop(OBJ_I_VALUE, 3600);

    set_cf(this_object());

    set_key(CHEST_KEY);
}

public void
spring_trap(object who)
{
    int dam;
    object fireobj;

    if (!query_trapped())
    {
        return;
    }

    tell_object( who, "A glyph materialises before you in the air, " +
        "glowing fiercely gold! Before you manage to blink, it " +
        "explodes, burning you badly!!\n");
    tell_room(E(who), "Right before " + QCTNAME(who) + "'s face a strange " +
                      "glyph materialises in the air! Before  " +
                      QCTNAME(who) + " manages to react, it explodes" +
                      "burning " + HIM(who) + " badly!!\n", who);

    /* takes damage */
    dam = (OBJ + "burning_damage")->hurt_player(who, CHEST_FIRE_DAMAGE);

    /* if damaged sustained more than the players fire resistancy
       he will go on fire. */
    if (dam > who->query_magic_res(MAGIC_I_RES_FIRE) )
    {
        fireobj=clone_object(OBJ + "burning_object");
        fireobj->move(who,1);
        fireobj->start(who, CHEST_FIRE_LVL_START,
                       CHEST_FIRE_DOT , FIRE_DEFAULT_DOT_TIME);
    }


    set_trapped(0);
}

public mixed
open(object ob)
{
    spring_trap(this_player());

    return 0;
}

public void
init()
{
    ::init();
    init_trap();
}

int
dispel_magic(int num)
{
    if (num > 60)
    {

        tell_object(TP, "You successfully dispel the trap. The golden glyphs " +
            "suddenly materialise, then crumble to black smoke.\n");
        say(QCTNAME(TP) + " successfully dispels the trap. The golden glyphs " +
            "suddenly materialise, then crumble to black smoke.\n", TP);

        set_trapped(0);

    return 1;
    }

    tell_object(TP, "You fail to dispel the trap!\n");
    spring_trap(TP);
    return 0;
}
