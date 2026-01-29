/* This comment tells emacs to use c++-mode  -*- C++ -*- */
/*
 * ew_boots.c
 *
 * worn by Mergula in LoD.
 *
 * a pair of evil boots Redhawk 921108
 * Modified by Sorgum 941026
 * -Updated to reflect use of new standard armour in Terel.
 *  Torm, Sept 98'
 * -Updated description, added kick ability.
 *  Lilith, June 2005
 * -Added cooldown between kicks
 *  Lilith, Feb 2008
 * -Rewrote the kick code so that it uses proper checks, and has real
 *  messages. Fixed recovery disenchant as well.
 *  Petros, May 2009
 * -Migrated to be an unarmed enhancer, and the kick special 
 *  converted into a bonus attack on successful hits.
 *  Lilith, Oct-Nov 2021
 */
#include "/d/Terel/include/Terel.h"
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>

inherit "/std/unarmed_enhancer.c";

public void
create_unarmed_enhancer()
{
    set_name(({"boots", "pair of boots"}));
    set_pname("pairs of boots");
    set_short("runed black boots with silver-tipped toes");
    set_pshort("runed black boots with silver-tipped toes");
    set_long("These boots are trophies made from the thick hide of a "+
	   "Terellian Troll, killed by Mergula himself. He employed a "+
       "wizard to inscribe the leather with magical runes that emit "+
	   "a faint glow. The toes of the boots are silver-coated steel, "+
       "which means they are more than just fancy footwear - they can "+
	   "do a lot of damage when dealing a well-placed kick.\n");
    set_adj(({"black", "steel-toed", "silver-tipped", "leather",
        "runed"}));
    add_item(({"toes", "silver toes", "silver-tipped toes"}),
       "The toes of these boots have been ornamented with silver "+
       "that has been inscribed with arcane symbols.\n");
    add_item(({"symbols", "arcane symbols", "runes"}), 
	   "You do not know what they mean, but they appear to be symbols "+
	   "from an arcane language, and likely magical in nature.\n");
    add_name("armour");
    add_pname("armours");

    set_default_enhancer(50, 50, W_BLUDGEON, 29, A_FEET, 
        0, this_object());

    set_keep(1);

    /* 1 kilo per foot */
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME,  600);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({40, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,
	    ({"    Drawing from the depths of the earth\n", 20,  
          "    a wizard inscribed runes to enchant\n", 25,  
		  "    these boots commissioned by Mergula.\n", 30,
          "    Whosoever wears these wields weapons\n", 35,
          "    on their feet that damage with the\n", 37, 
          "    force of earth magic.\n", 40}));
    add_prop(OBJ_S_WIZINFO, 
        "This is an unarmed enhancer that does extra damage.  "+
        "This will provide a 50/50 attack from the feet hitlocs.  "+
        "The boots will also provide an extra kick attack "+
        "with a 1 in 5 random chance. The boots will also not "+
        "wear down. These are cloned by Mergula in the LoD.\n");

    add_prop(OBJ_I_VALUE, 578);
}

// Since these boots will now be taking hits from enemies
// as well as hitting enemies, they would wear down fast.
// Making it so these boots will not break.
public void set_condition(int condition)
{
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
                int phit, int dam, int hid)
{
    int result = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam, hid);
    
   
    if (random(5))
    {
        return result;
    }
    
    int pen, aid, bSuccess;
    string attacker_msg, target_msg, watcher_msg;
    
    attacker_msg = "Drawing upon the power of the earth beneath your feet, "
        +"you lash out with one of your black runed boots ";
    target_msg = QCTNAME(TP) + " lashes out at you with one of " 
        + TP->query_possessive() + " black runed boots ";
    watcher_msg = QCTNAME(TP) + " lashes out at " + QTNAME(enemy)
        + " with one of " + TP->query_possessive() + " black runed "
        + "boots ";
        
    pen = 280 + random(280);
    pen -= pen * enemy->query_magic_res(MAGIC_I_RES_EARTH) / 100;
    
    aid = random(2) ? TS_RFOOT : TS_LFOOT;
    bSuccess = 0;
    if (TP->query_combat_object()->cb_tohit(aid, 100, enemy) > 0)
    {
        bSuccess = 1; // the kick was successful
        mixed hitresult = enemy->hit_me(pen, MAGIC_DT, TP, aid);
        string hdesc = "body";
        if (sizeof(hitresult) >= 2)
        {
            hdesc = hitresult[1];
        }
        attacker_msg += "and strike "+ QTNAME(enemy) +"'s "+ 
           hdesc +".\n";
        target_msg += "and lands a kick on your " + hdesc + 
            "that draws its power from the earth itself.\n";
        watcher_msg += "and lands a kick that seems to draw "+
            "its power from the earth itself.\n";
    }    
    else
    {
        attacker_msg += "and miss completely.\n";
        target_msg += "and misses completely.\n";
        watcher_msg += "and misses completely.\n";
    }
    
    TP->catch_msg(attacker_msg);
    enemy->catch_msg(target_msg);
    TP->tell_watcher(watcher_msg, enemy, ({ TP, enemy }) );

    return result;    
}

