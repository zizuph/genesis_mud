#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <options.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>
#include "/d/Ansalon/common/defs.h"
 
inherit "/std/weapon";
inherit "/lib/keep";
 
int wielding_type;

#define HIT 30
#define PEN 39
 
#define HIT2 35
#define PEN2 35

create_weapon()
{
    set_name("tessto");
    set_adj("heavy");
    add_adj("wooden");
    set_short("heavy wooden tessto");
    set_long("This great weapon, the tessto, is commonly wielded by the minotaurs " +
      "of the Blood Sea one handed, although most races would have trouble wielding " +
      "in two! Made of hardwood, this club is heavier than a lot of metal weapons, " +
      "and is cleverly weighted so as to maximize damage. Nasty looking spikes " +
      "protrude from its head, adding to its deadliness.\n");
    set_default_weapon(HIT,PEN,W_CLUB,W_BLUDGEON,W_BOTH);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_I_WEIGHT, 18000);

    set_wf(TO);
}

int
change_handle(string str)
{
 
    if (str != "grip")
    {
        NF("Change what? The grip?\n");
        return 0;
    }
 
    if (E(TO) != TP)
    {
        NF("Perhaps you should pick "+short()+" up first!\n");
        return 0;
    }
 
    if (query_wielded())
    {
        NF("You can not change the grip on the handle of the "+short()+" when you are "+
              "wielding it.\n");
        return 0;
    }
 
    if(TP->query_race_name() != "minotaur")
    {
       write("You try and change your grip on the tessto to wield it one-handed, however "+
       "find it too awkward. Only a minotaur would know how best to wield this weapon in "+
       "one hand.\n");
       return 1;
    }
 
    if (wielding_type == 1)
    {
        wielding_type = 0;
        set_hands(W_BOTH);
        set_hit(HIT);
        set_pen(PEN);
    if (wielded && wielder)
        wielder->update_weapon(this_object());
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
        set_hit(HIT2);
        set_pen(PEN2);
 
    if (wielded && wielder)
        wielder->update_weapon(this_object());
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
    set_hit(HIT);
    set_pen(PEN);
    
    if (wielded && wielder)
        wielder->update_weapon(this_object());
//    TO->update_weapon(TO);
}
 
void
init()
{
    ::init();
    add_action(change_handle, "change");
 
 
}