inherit "/std/weapon";
inherit "/lib/keep";

#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>

object wielder;


public void
create_weapon()
{
    set_name("battleaxe");
    add_name(({"weapon","axe"}));
    set_pname("battleaxes");
    add_pname(({"weapons","axes"}));
    set_adj("sturdy");
    add_adj("one-bladed");
    set_short("sturdy one-bladed axe");
    set_pshort("sturdy one-bladed axes");
    set_long("This short axe has a very thick and short handle, " +
      "making it truly hard to use for anyone with a fist smaller " +
      "than a minotaur or an ogre. The wide blade attached to " +
      "the top of the shaft must have been appropriated from a " +
      "halberd, for it is heavy, and out of proportion. It looks " +
      "as if it could do grave damage if swung hard and precise " +
      "enough.\n");
    set_default_weapon(34, 38, W_AXE, W_SLASH, W_ANYH);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_I_WEIGHT, 8500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40,40));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO,
      "This is a neat minotaur axe, as per the books. Due to the unique " +
      "balance, and heavy axehead, minotaurs and ogres with their huge fists " +
      "can do much more damage with it then any other race. The " +
      "enchantment upon it is minor.\n");
    add_prop(MAGIC_AM_ID_INFO,
      ({"This weapon is magically enchanted.\n", 5,
	"The balance of the axe favours minotaurs and ogres.\n", 20}));
    add_prop(MAGIC_AM_MAGIC,({10,"enchantment"}));

    set_wf(TO); 
    seteuid(getuid(TO));    
}

void
minotaur_wield()
{
    if(E(TO) != wielder)
        return;
    wielder->catch_msg("Hah! Now here's a weapon suited for a minotaur!" +
    " Good, thick handle, heavy blade... You feel you could wreak havoc " +
    "and destruction with this axe, and make a few practice slashes. " +
    "The air sings as you cleave it.\n");
say(QCTNAME(wielder) + " looks mighty pleased about the axe, and " +
    "makes a few practice slashes. The air moans as it is cleaved.\n");

    set_hit(40);
    set_pen(44);

    wielder->update_weapon(TO);
}      

void
default_wield()
{
    if(E(TO) != wielder)
        return;

    wielder->catch_msg("The balance of the axe is all wrong " +
       "for you. The handle is too thick and too short, while " +
       "the blade much to heavy for a balanced swing.\n");
    set_hit(34);
    set_pen(38);
    wielder->update_weapon(TO);
}



mixed
wield(object what)
{
    wielder = TP;

    if(TP->query_race_name() == "minotaur")
        set_alarm(1.0, 0.0, "minotaur_wield");
    else
        set_alarm(1.0, 0.0, "default_wield");
    return 0;
}      
