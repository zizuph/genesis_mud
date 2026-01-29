/***********************************************************
 * Name: Granite war maul.
 * By: Elmore.
 * Date: Jun-2001.
 * Desc: A magical club that the troll shaman is wielding in
 *       Mithas.
 * Restrictions: Restricted to 3.
 ***********************************************************/

#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <options.h>
#include <filter_funs.h>
#include <tasks.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/forest/local.h"

#define HIT 40
#define PEN 45

int wielding_type;

void
create_weapon()
{
    set_name("maul");
    set_adj("granite");
    add_adj("war");
    set_short("granite war maul");
    set_long("Constructed from a thick wooden handle and a heavy granite stone, this "+
             "immense weapon was made to break the bones of an enemy. Leather straps "+
             "around the stone head and handle prevents the head from slipping away "+
             "when the weapon hits a target. You think you might be able to change "+
             "the grip around the handle.\n");
    set_hit(HIT);
    set_pen(PEN);
//    set_wf(TO);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN) + random(10));

    if (random(2))
    {
        add_prop(OBJ_I_VOLUME, 21000);
        add_prop(OBJ_I_WEIGHT, 22000);
    }
    else
    {
        add_prop(OBJ_I_VOLUME, 16000);
        add_prop(OBJ_I_WEIGHT, 17000);
    }
   
    set_likely_corr(1);

    add_prop(OBJ_S_WIZINFO, "This weapon has been enchanted by a shaman in Mithas, "+
        "this has caused an increase in penetration.\n");

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 10, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,
      ({"The weapon is enchanted.\n", 5,
        "The granite stone on this weapon has been enchanted causing an increase "+
        "in damage.\n", 30}));
}

int
change_handle(string str)
{
    if (str != "handle")
    {
        NF("Change what? The handle?\n");
        return 0;
    }

    if (E(TO) != TP)
    {
        NF("Perhaps you should pick "+short()+" up first!\n");
        return 0;
    }

    if (query_wielded())
    {
        NF("You can not change the grip around the handle of the "+short()+" when you are "+
              "wielding it.\n");
        return 0;
    }

    if (wielding_type == 1)
    {
        wielding_type = 0;
	set_hands(W_BOTH);
//        TP->update_weapon(TO);
        write("You change the handle back from one-handed to two-handed.\n");
        say(QCTNAME(TP) + " changes "+HIS(TP)+" grip around the handle of "+
           "the "+short()+".\n");
        return 1;
    }

    if (TP->resolve_task(TASK_DIFFICULT, ({TS_STR, SS_AWARENESS})) > 0)
    {   /* Success */
        wielding_type = 1;
        set_hands(W_ANYH);
//        TP->update_weapon(TO);
        write("You change the handle from two-handed to one-handed.\n");
        say(QCTNAME(TP) + " changes "+HIS(TP)+" grip around the handle of "+
           "the "+short()+".\n");
	return 1;
    }
    else
    {
        write("You fail to wield the weapon in one hand.\n"+
              "You feel exhausted.\n");
        TP->add_fatigue(-50);
    }
    return 1;
}

void
leave_env(object from, object to)
{
    ::leave_env(from,to);
    wielding_type = 0;
    set_hands(W_BOTH);
//    TO->update_weapon(TO);
}

void
init()
{
    ::init();
    add_action(change_handle, "change");
}

