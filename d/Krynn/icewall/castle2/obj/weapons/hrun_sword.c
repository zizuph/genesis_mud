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
    set_name("broadsword");
    add_name(({"weapon","sword"}));
    set_pname("broadswords");
    add_pname(({"weapons","swords"}));
    set_adj("steel");
    add_adj("encrusted");
    set_short("encrusted steel broadsword");
    set_pshort("encrusted steel broadswords");
    set_long("A solid, steel broadsword. The blade looks very " +
        "sharp, though oddly proportioned, as if the thick blade " +
        "was forged for the shorter races. In addition, the very " +
        "tip of it has been snapped off, making it virtually " +
        "impossible to stab with the weapon. The handle and guard " +
        "have been beautifully encrusted with shimmering fire " +
        "opals. The sword has an ancient aura to it, and you " +
        "wonder what history could it tell... if, of course, swords " +
        "could talk.\n");
    set_default_weapon(38, 42, W_SWORD, W_SLASH, W_ANYH);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 7500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40,40));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO,
      "This sword has been crafted in Thorbardin for a dwarven " +
      "prince. The youth, careless as only youths can be, snapped " +
      "the tip of the sword while trying to use it as a leverage, " +        "but the stone slab proved too heavy. Most of the original " +
      "dwarven magic remains within the blade, and it is attuned " +
      "to a dwarven wielder.\n");
    add_prop(MAGIC_AM_ID_INFO,
      ({"This weapon is magically enchanted.\n", 5,
	"The blade was forged in Thorbardin, and seems attuned " +
	"to a dwarven wielder.\n", 20,
	"The sword yearns to be wielded by a dwarf again, and will " +
        "strike true if wielded by one again.\n", 45}));
    add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));

    set_wf(TO); 
    seteuid(getuid(TO));    
}

void
dwarf_wield()
{
    if(E(TO) != wielder)
        return;
    wielder->catch_msg("The sword has a definite dwarven aura to it... " +
      "You feel very happy about the weapon, and reach out to caress the " +
      "sturdy blade with your fingers. The fire opals glow warmly in " +
      "response.\n");
    say(QCTNAME(wielder) + "'s face cracks in a smile as " + HE(wielder) +
      " runs " + HIS(wielder) + " hand over the blade of the jewel " +
      "encrusted broadsword. The fire opals seem to glow in response.\n");

    set_hit(48);
    set_pen(42);

    wielder->update_weapon(TO);
}      

void
default_wield()
{
    if(E(TO) != wielder)
        return;

    wielder->catch_msg("You feel a bit awkard wielding " +
       "a snapped blade... although, come to think of " +
       "it, one could still do some damage with it.\n");
    set_hit(38);
    set_pen(42);
    wielder->update_weapon(TO);
}



mixed
wield(object what)
{
    wielder = TP;

    if(TP->query_race_name() == "dwarf")
        set_alarm(1.0, 0.0, "dwarf_wield");
    else
        set_alarm(1.0, 0.0, "default_wield");
    return 0;
}      
