/* This comment tells emacs to use c++-mode  -*- C++ -*- */
/*
 * /d/Terel/LoD/weapon/ew_sword.c
 *
 * Mergula's sword.
 *
 * Revision history:
 * Balance work by Boron 13/Aug/1996 (Added wiz_info)
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
inherit "/lib/keep";

#include <wa_types.h>

#define KILLER  "_wl_killer"

public void
create_weapon()
{
    ::create_weapon();
    
    set_name("sword");
    set_short("blackened steel sword");
    set_long("It is a blackened steel sword. It is very sharp.\n");
    set_adj("steel");
    add_adj("blackened");
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 2200);
    
    set_hit(55);
    set_pen(60);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_wf(TO);
    set_hands(W_BOTH);
    set_keep(0);
    
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 60, "enchantment" }) );
    add_prop(MAGIC_AM_ID_INFO,
	({"This is Mergula's famous sword.", 10,
	  "It can only be wielded by him or his killer.\n", 60}));
    add_prop(OBJ_S_WIZINFO,
	  "This is Mergula's famous sword. It can only be wielded " +
	  "by him or his killer.\n");
}

public int
allowed(object ob)
{
    if (ob->query_name() == query_prop(KILLER))
        return 1;
    return 0;
}

public void
wmsg(object ob)
{
    if (!ob) return;
    ob->catch_msg("The "+short()+" glows faintly as you wield it.\n");
    tell_room(ENV(ob), "The "+short()+" glows faintly as " +
              QTNAME(ob) + " wields it.\n", ob);
}

public void
bomb(object ob)
{
    if (ob && ETO == ob) {
        ob->catch_msg("The "+short()+" disintegrates in a flash " +
                      "of blue light. OUCH! That really hurt!\n");
        tell_room(ENV(ob), "Something " + QTNAME(ob) +
                  " is holding explodes in a blue flash!\n", ob);
        ob->reduce_hit_point(200 + random(50));
        if (ob->query_hp() <= 0) ob->do_die(TO);
        remove_object();
    }
}

public mixed
wield(object wep)
{
    if (!allowed(TP)) {
        set_alarm(8.0, -1.0, &bomb(TP));
        return "Somehow you are not entitled to wield the " + short() +
               ". You better drop it quickly!\n";
    }
    set_alarm(2.0, -1.0, &wmsg(TP));
    return 1;
}

public string
query_recover()
{
    if (allowed(TP)) {
        return MASTER + ":" + query_wep_recover() + "#wl#" +
               query_prop(KILLER) + "##" + query_keep_recover();
    } else {
        return "";
    }
}

public void
init_recover(string arg)
{
    string foo, bar, tmp;
    
    if (!strlen(arg)) return;
    
    init_wep_recover(arg);
    if (sscanf(arg, "%s#wl#%s##%s", foo, tmp, bar) == 3) {
        add_prop(KILLER, tmp);
    }
    init_keep_recover(arg);
}
