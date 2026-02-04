/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * devils_sword.c
 *
 * used by devils knights in LoD.  This sword is magical.
 *
 * a devils sword Redhawk 92 11 03 
 * modified by Sorgum 941025
 * modified by Mortricia Aug. 1996
 *
 */

#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;

#include "/d/Terel/include/recover.h"
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <language.h>

#define HIT 34
#define MAX_HIT 44
#define PEN 33
#define MAX_PEN 42
#define LIM -99

/*
 * Function name: create_weapon
 * Description:   create the weapon. (standard)
 */
public void
create_weapon()
{
    set_name(({"sword","longsword"}));
    set_pname(({"longswords","swords"}));
    add_pname("weapons");
    set_short("crimson steel longsword");
    set_long("A very deadly sword that looks like it belongs " +
	     "to the devil himself. The sword radiates evil magic and " +
	     "you think you see the fire from hell reflecting in the " +
	     "blade of the sword. The blade doesn't seem to have been " +
	     "made by mortal hands.  It's probably a very powerful weapon.\n");
    set_adj(({"crimson", "steel","devil's", "devils"}));

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(HIT);
    set_pen(PEN);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_VALUE, 345);
    
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 45, "enchantment" }) );
    add_prop(MAGIC_AM_ID_INFO,
	({"Only those who are evil may use me properly.\n", 45}));
    add_prop(OBJ_S_WIZINFO,
	 "Only evil players (< -99) will be able to use this sword " +
	 "to its full potential.\n");
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */
    set_wf(TO);

    /* Last, how shall it be wielded? */
    set_hands(W_RIGHT); /* You can wield it in any hand. */
}

void
update_wep(int a)
{
    if (a < LIM) {
        set_hit(HIT - a/70 > MAX_HIT ? MAX_HIT : HIT - a/70);
        set_pen(PEN - a/80 > MAX_PEN ? MAX_PEN : PEN - a/80);
    } else {
        set_hit(HIT);
        set_pen(PEN);
    }
    if (query_wielded())
        query_wielded()->update_weapon(TO);
}

int
wield(object ob)
{
    int a = TP->query_alignment();
    
    if (a < LIM)
    {
        set_alarm(1.0, 0.0, &update_wep(a));
        TP->catch_msg("You get a feeling of satisfaction as you " +
                      "wield the " + short() + ".\n");
        tell_room(ETP, "As " + QTNAME(TP) + " wields " + LANG_ASHORT(TO) +
                       " " + TP->query_pronoun() +
                       " gets a dangerous look in " +
                       TP->query_possessive() + " eyes.\n", TP);
        return 1;
    }
    return 0;
}

int
unwield(object ob)
{
    set_alarm(1.0, 0.0, &update_wep(0));
}
