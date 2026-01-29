/* standard oponent by Milan */

inherit "/std/monster";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

public void
do_die(object killer)
{
    /* Did I die ? */
    if (query_hp() > 0)
        return;
        
    killer->notify_you_killed_me(this_object());
    // this does not die...
}

void
arm_me()
{
    object ob;

    setuid();
    seteuid(getuid());

    ob = clone_object("/std/weapon");
    ob->set_name("sword");
    ob->set_adj("standard");
    ob->set_default_weapon(40, 40, W_SWORD, W_IMPALE | W_SLASH, W_ANYH);
    ob->set_likely_dull(-500);
    ob->set_likely_break(-500);
    ob->update_prop_settings();
    ob->move(this_object(), 1);

    ob = clone_object("/std/armour");
    ob->set_name("helm");
    ob->set_adj("standard");
    ob->set_ac(40);
    ob->set_at(A_HEAD);
    ob->set_likely_cond(-500);
    ob->set_likely_break(-500);
    ob->update_prop_settings();
    ob->move(this_object(), 1);

    ob = clone_object("/std/armour");
    ob->set_name("shield");
    ob->set_adj("standard");
    ob->set_ac(40);
    ob->set_at(A_SHIELD);
    ob->set_likely_cond(-500);
    ob->set_likely_break(-500);
    ob->update_prop_settings();
    ob->move(this_object(), 1);

    ob = clone_object("/std/armour");
    ob->set_name("mail");
    ob->set_adj("standard");
    ob->set_ac(40);
    ob->set_at(A_BODY);
    ob->set_likely_cond(-500);
    ob->set_likely_break(-500);
    ob->update_prop_settings();
    ob->move(this_object(), 1);

    command("wield all");
    command("wear all");
}

void
create_monster()
{
    set_name("oponent");
    set_adj("standard");
    add_prop(CONT_I_WEIGHT,75000);   /* 75 Kg */
    add_prop(CONT_I_HEIGHT,180);     /* 180 cm */

    set_stats(({ 100, 100, 100, 100, 100, 100}));
    refresh_living(); /* full hp, mana, fatigue */

    set_skill(SS_DEFENCE, 80);
    set_skill(SS_WEP_SWORD,   90);
    set_skill(SS_PARRY,   30);
    
    set_alarm(0.0, 0.0, arm_me);
}
