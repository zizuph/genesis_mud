inherit "/std/receptacle";
inherit "/d/Genesis/lib/trap";
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <stdproperties.h>

object ioun1, ioun2;

public void
create_receptacle()
{
    set_name("chest");
    set_adj("sturdy");
    add_adj("ironwood");
    set_pshort("sturdy ironwood chests");

    set_long("Not a single nail has been used to create this chest. " +
     "The wood flows together smoothly, as if someone brought it " +
     "alive and melded it with in harmony. Banded with iron and big enough to hold sacks of " +
     "grain, the chest looks like it could resist the tugging efforts " +
     "of an army of kender... speaking of whom, the chest's ornate lock " +
     "appears open. Something tells you that its not grain the chest holds, but " +
     "something infinitely more precious - and that there never was " +
     "a reason to lock it with such primitive means.\n" +
     "@@trap_desc@@");
 
    set_trap_level(60);

    set_trap_desc("You see no physical trap here... Most likely, its " +
       "something magic.\n"); 

    add_prop(MAGIC_AM_ID_INFO,
      ({"This chest is magically trapped!\n", 1,
	"Magical exploding glyphs were used to protect it from unwary " +
	"adventurers.\n", 10, "The trap is strong and very dangerous", 20,
        "The trap cannot be disarmed, however the " +
	"glyphs can be dispelled by magic.\n", 55}));

    add_prop(MAGIC_AM_MAGIC,({60,"enchantment"}));
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_MAX_WEIGHT, 250000);
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(CONT_I_MAX_VOLUME, 300000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_CLOSED, 1);

    add_prop(OBJ_I_VALUE, 3600);

    set_cf(this_object());

    set_key("NO_KNOWN_KEY_YET");
}

public void
spring_trap(object who)
{
    if (!query_trapped())
    {
        return;
    }

    who->catch_tell("A glyph materialises before you in the air, " +
        "glowing fiercely gold! Before you manage to blink, it " +
        "explodes, burning you badly!!\n");
    who->heal_hp(-(900 + random(900)));
    say("Right before " + QTNAME(who) + "'s face a strange glyph " +
        "materialises in the air! Before " + QTNAME(who) + " manages " +
        "to react, it explodes, burning " + HIM(TP) + " badly!!\n");
    if (who->query_hp() < 1)
    {
	who->do_die(this_object());
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
