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
object wielder;

#define HIT 40
#define PEN 40
 
#define HIT2 35
#define PEN2 35

create_weapon()
{
    set_name(({"clabbard","sword","broadsword"}));
    set_adj("heavy");
    add_adj("steel");
    set_short("heavy steel clabbard");
    set_long("This six foot broadsword is sized to a minotaur's needs. While it would " +
      "be comfortably gripped in one of their huge hands, it can easily be compared in " +
      "size to the two-handed greatswords wielded by the barbarians of Nordmaar. Its cutting " +
      "edge is backed by a serrated saw edge. A blood channel runs the length of the blade, " +
      "making it easier to withdraw from an impaled foe.\n");
    set_default_weapon(HIT,PEN,W_SWORD,W_SLASH,W_BOTH);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_I_WEIGHT, 12000);

    set_wf(TO);
    seteuid(getuid(TO));
}

mixed
wield(object what)
{ 
    wielder = TP;
    return 0;
}
 
mixed
unwield()
{
    wielded = 0;
    return 0;
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
        NF("Perhaps you should pick the "+short()+" up first!\n");
        return 0;
    }
 
    if (query_wielded())
    {
        NF("You can not change the grip on the hilt of the "+short()+" when you are "+
              "wielding it.\n");
        return 0;
    }
 
    if(TP->query_race_name() != "minotaur")
    {
       write("You try and change your grip on the clabbard to wield it one-handed, however "+
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
        write("You change the hilt back from one-handed to two-handed.\n");
        say(QCTNAME(TP) + " changes "+HIS(TP)+" grip around the hilt of "+
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
        write("You change the hilt from two-handed to one-handed.\n");
        say(QCTNAME(TP) + " changes "+HIS(TP)+" grip around the hilt of "+
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

public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    string dam_descr, wep_string;
    object weapon;

    if(sizeof(enemy->query_weapon(-1)))
    {
        if(!random(4))
        {
            if(phurt > 0)
            {

            wep_string = enemy->query_weapon(-1)[0]->query_short();
            weapon = enemy->query_weapon(-1)[0];
 
              if(random(100) < enemy->query_skill(SS_PARRY))
              {
                wielder->catch_msg("You strike out at the " +wep_string+ " wielded " +
                  "by " +QTNAME(enemy)+ ", but " +HE(enemy)+ " manages to parry " +
                  "your attack.\n");
                enemy->catch_msg(QCTNAME(wielder)+ " strikes out at your "+
                  wep_string+ " with " +HIS(wielder)+ " " +short()+ ", but you " +
                  "manage to parry the attack away.\n");
                tell_room(E(wielder), QCTNAME(wielder)+ " strikes out at " +QTNAME(enemy)+
                  " with " +HIS(wielder)+ " " +short()+ ", but "+QTNAME(enemy)+ 
                  " manages to parry the attack away.\n", ({enemy, wielder}));
                return 1;
              }
              wielder->catch_msg("You strike out at the " +wep_string+ " wielded " +
                "by " +QTNAME(enemy)+ ", snaring it in the "+
                "serrated saw edge of your " +short()+ "!\n"); 
              enemy->catch_msg(QCTNAME(wielder) + " strikes out at your " +
                wep_string+ " with " +HIS(wielder)+ " " +short()+ 
                ", snaring it its serrated saw edge!\n");
              tell_room(E(wielder), QCTNAME(wielder)+ " strikes out at " +QTNAME(enemy)+
                "'s " +wep_string+ " with " +HIS(wielder)+ " " +short()+ 
                ", snaring it its serrated saw edge!\n",
                ({enemy, wielder}));
            }
         }
     }
   return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

 
void
init()
{
    ::init();
    add_action(change_handle, "change");
 
 
}
