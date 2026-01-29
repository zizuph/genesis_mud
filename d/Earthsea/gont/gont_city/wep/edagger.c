#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>

private int knife_req; // give mercs a chance

public void
create_weapon()
{
    set_name("peacemaker");
    add_name("knife");
    set_pname("peacemakers");
    add_pname("daggers");
    add_pname("weapons");
    add_name("dagger");
    set_adj("vicious");
    add_adj("midnight-black");
    set_short("vicious midnight-black peacemaker");
    set_pshort("vicious midnight-black peacemakers");
    set_long("This dagger is long and vicious. The blade is midnight black. "+
        "The hilt is made from soft leather that is dyed green wrapped "+
        "around metal. On the very bottom of the weapon is a symbol of two "+
        "crossed axes over a map of the world.\n");
    set_default_weapon(36, 38, W_KNIFE, W_SLASH | W_IMPALE, W_RIGHT);
    set_wf(this_object());
    set_keep(1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO,"This is a very potent dagger. It is very light "+
      "and strong. It has magic in that allows it a high hit and "+
      "penetration. It was made especially for the town marshal to "+
      "keep the town in order.\n");
    add_prop(MAGIC_AM_ID_INFO,({"This weapon is magical and potent\n", 5,
        "You feel a strong will emanating from " +
        "the dagger that you must overcome.\n", 25,
        "The weapon's balance is subject to the magic, "+
        "allowing better wieldability and very high hit rate.\n", 51}));
    add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));
    // Ckrik, 6/18/2021, reduce weight and volume to something more
    // reasonable for a knife.
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 2100);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(36, 38) + 1200);
    knife_req = 60+random(7);
}

public string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

public void
init_recover(string arg)
{
    init_wep_recover(arg);
}

public mixed
wield(object what)
{
    object tp = this_player();

    if(tp->query_skill(SS_WEP_KNIFE) > knife_req &&
        tp->query_base_stat(SS_DIS) > 80 &&
        tp->query_base_stat(SS_DEX) > 80)
    {
        write("You feel a slight tinge of fear as you grip this magnificent "+
            "weapon. You manage to overcome it and take hold of it's power.\n");
        return 0;
    }

    tp->add_panic(random(100)-5);

    return "As you try to take hold of the dagger, an overpowering feel " +
        "of terror rips through your mind and body. You are unable to wield "+
        "the dagger.\n";
}
