/*   Coded by Arman Kharas 23 August 2003  */

inherit "/std/weapon";
inherit "/lib/keep";

#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h> 
#include <macros.h>

#define HIT 58
#define PEN 58

#define HIT2 50
#define PEN2 50

#define EQRN enemy->query_race_name()

/* This weapon is more effective against creatures that hate fire */
int enemy_type = 0;


void
create_weapon()
{
    set_name(({"greatsword","sword", "firebrand"}));
    set_adj(({"elaborate","carved"}));
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_short("elaborately-carved greatsword");    
    set_long("This is a massive two-handed sword of ancient design. The blade "+
     "is forged from a ruby-hued alloy, along which elaborate flame-like carvings " +
     "run along its length.  It stands easily six feet from tip to pommel, and the " +
     "blade is extremely wide, stretching out almost to the edge of the quillions " +
     "on the hilt. You have little doubt that a great deal of space and strength " +
     "would be needed to wield this weapon effectively.\n");
    
    set_hit(HIT2);
    set_pen(PEN2);
    set_wt(W_SWORD);
    set_hands(W_BOTH);
    set_dt(W_SLASH);
    set_wf(TO);
    set_likely_dull(1);

    add_item(({"carvings","flame-like carvings"}), "Along the length of the greatsword "+
      "are carvings that make it look like the sword is engulfed in flames.\n");
    
    add_prop(OBJ_I_WEIGHT, 20000);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_I_VALUE, 7000);  

    add_prop(OBJ_I_RES_FIRE, 100);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 80, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"The elaborately-carved greatsword seems " +
        "to be magical.\n",1, "This blade requires powerful strength to be wielded. "+
        "It is embued with powerful enchantments that make it far more " +
        "deadly than other two-handed blades. It is resistant " +
        "to magical fire.  It is particularly effective " +
        "against undead and those that fear the flame.\n",35}));

    seteuid(getuid(TO));    
}

void
state_change(int hit, int pen)
{

    set_hit(hit);
    set_pen(pen);
    
    if (wielded && wielder)
        wielder->update_weapon(this_object());
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
                int phit, int dam)
{
    int r;
    
    r = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    
    if ((enemy->query_prop(LIVE_I_UNDEAD) > 0) || (EQRN == "troll") ||
        (EQRN == "frost giant") || (EQRN == "yeti") || (EQRN == "thanoi"))
    {
        /* Switch to high power */
        if (!enemy_type)
        {
            state_change(HIT, PEN);
            enemy_type = 1;
        }
        
    }
    else
    {
        /* Switch to low power */
        if (enemy_type)
        {
            state_change(HIT2, PEN2);
            enemy_type = 0;
        }
        
    }
    
    return r;
}


void
wield_message1()
{
    if(E(TO) != wielder)
        return;
    wielder->catch_msg("The blade on the elaborately-carved "+
      "greatsword glows crimson as you wield this mighty weapon. " +
      "A voice whispers in your head:\n\n"+
      "            I am Life. Passion. Honour. Fire.\n"+
      "        I am Bane of Ice. Death. Fear. Cowardice.\n"+
      "                    I am Firebrand.\n"+
      "             Take me to battle mighty one!\n"+
      "                 I shall not fail you.\n\n");
 
    tell_room(E(wielder),"The blade of " + QTNAME(wielder) +
      "'s elaborately-carved greatsword glows crimson as "
      + PRONOUN(wielder) + " wields the mighty weapon.\n", wielder);
}
 
 
 
 
mixed
wield(object what)
{
    if(TP->query_stat(SS_STR) <= 90)
        return "You are not strong enough to to wield " +
        "this greatsword!\n";
 
    set_alarm(1.0, 0.0, "wield_message1");
    return 0;
}
