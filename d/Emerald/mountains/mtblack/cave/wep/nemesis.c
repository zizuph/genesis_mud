/* The Nemesis sword - originally coded by Tulix I in July 93.        */
/* Total rework by Tulix III 06/08/95.                                */
/* This is the only magical weapon that is found in the 100+ rooms    */
/* in /d/Emerald/cave/ and sub-directories. So make the most of it.   */
/* This weapon is used by /d/Emerald/cave/npc/ogrelord.c.             */
/* He is found once per reboot at /d/Emerald/cave/levelc/cave24c.c.   */

inherit "/std/weapon";
#include "/d/Emerald/defs.h"  /* This weapon uses defines from this file */
#include <wa_types.h>
#include <filter_funs.h>

#pragma strict_types

/* Define shortened names for commonly used functions not in defs.h */ 
#define QW        query_wielded()
#define QPOS(QW)  QW->query_possessive() 

/* Prototype functions */
public string extra_sword_desc();
public void tell_watcher(string fight_message, object wielder, object enemy);

public void
create_weapon()
{
    set_name("sword");
    set_short("nemesis sword");
    add_pname("weapons");
    add_pname("swords");
    set_adj("mithril");
    add_adj("alloy");
    add_adj("nemesis");
    add_adj("Nemesis");
    add_name("sword of nemesis");
    add_name("sword of Nemesis");
    
    set_long("It looks very much like the fabled sword of Nemesis! "  
        + "Legend has it, that the sword was forged from the finest mithril " 
        + "alloy in all of Emerald, and enchanted by the great mage "
        + "Enzalcaspin. It was lost for many years though, and to this day, "
        + "no one knows what happened to it. Even if this isn't the real "
        + "Nemesis sword, you are certain that it is genuine mithril alloy: "
        + "it looks like it would hold its keen edge forever."
        + "@@extra_sword_desc");

    /* Changed to be legal without magical properties - karath  */

    set_hit(33); /* This is a very rare sword indeed. Its excellent weapon */
    set_pen(37); /* class is justified by the difficulty of getting it.    */
                 /* If you think that's just a load of Mylos-type bullshit */
                 /* then please try geting hold of one!  #;-)              */
    
    set_wt(W_SWORD);                    /* Weapon is a type of sword       */
    set_dt(W_SLASH);                    /* Slash damage only               */
    set_hands(W_BOTH);                  /* Weapon is wielded in both hands */
    
    add_prop(OBJ_I_WEIGHT, 14000);                   /* weight 14 kg       */
    add_prop(OBJ_I_VOLUME, 4000);                    /* takes up 4 litres  */
    add_prop(OBJ_I_VALUE, 2000);                     /* worth lots of cash */
    
    /* Removing the indestructable stuff - Karath
    set_likely_dull(0);
    set_likely_corr(0);
    set_likely_break(0);
    */
    
    /* Set props required by /doc/man/general/weapon & weapon_guide */
    /* Removed magical props 
     * add_prop(OBJ_M_NO_BUY, 1);
     * add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
     * add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment"}) );
     * add_prop(MAGIC_AM_ID_INFO, ({ 
     *     "The sword seems magical.\n", 0,
     *     "The sword will get better in combat.\n", 20,
     *     "The sword will shimmer during combat.\n" +
     *     "The sword does more damage while it shimmers.\n", 40,
     *     "This sword was enchanted by the great mage Enzalcaspin.\n" +
     *     "Don't get too excited though, as it was enchanted many " +
     *     "hundereds of years ago, and its power has faded.\n" +
     *     "The sword will shimmer at random times during combat. " +
     *     "While the sword shimmers, the sword has a better penetration, " +
     *     "thus doing more damage to your opponent.\n", 80 }) );
    
     * add_prop(OBJ_S_WIZINFO, "Tired of those boring swords of darkness? "
     *     + "Want something new to wield?\n"
     *     + "Basically, this is a magical sword, and with every attack, "
     *     + "there is a small chance that the wc_pen is increased by between "
     *     + "3 & 10, to give a more effective weapon. This is only temporary, "
     *     + "the wc_pen returning to 44 after a short while. "
     *     + "It's basically a new toy to keep the mortals amused!\n"
     *     + "The sword is cloned by /d/Emerald/cave/npc/ogrelord.c.\n"
     *     + "He is found in /d/Emerald/cave/levelc/cave24c.c (with guards!).\n"
     *     + "If you think its too good, try getting hold of it. *grin*\n");

     * add_item(({"shimmer", "shimmering"}), "@@shimmer_desc");
     */
}

/*
 * Function name: extra_sword_desc
 * Description:   This function adds an extra sentence to the set_long by vbfc
 *                to inform the wielder if the sword is shimmering currently.
 * Returns:       description of the shimmering, or "\n" if not shimmering.
 */
public string
extra_sword_desc()
{
    if ( TO->query_pen() >= 45 )
    {
        return ("\nThe whole sword is shimmering with a mysterious "
              + "magical power!\n");
    }
    else
    {
        return (" The sword seems to shine, but not with a magical aura.\n");
    }
}

/*
 * Function name: did_hit
 * Description:   This function is called every time the weapon has been used 
 *                in an attack. Here we use it to rewrite the messages given
 *                to players involved in the combat.
 * Returns:       1 - message rewritten: 0 - message not rewritten  
 */
varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
        int phit, int dam)
{
    if (phurt == -1) /* Complete miss */
    {
        QW->catch_msg("You swing your sword wildly at " +
            QTNAME(enemy) + ", but miss.\n");
        
        enemy->catch_msg( QCTNAME(QW) + " swings " + QPOS(QW) +
            " sword wildly at you but misses.\n");
    
        tell_watcher( QCTNAME(QW) + " swings " + QPOS(QW) +
            " sword wildly at " + QTNAME(enemy) +
            ", but misses.\n", QW, enemy );
    
    return 1;
    }

    if (phurt == 0) /* No damage to enemy in this attack */
    {
        /* Message to wielder of weapon */
        QW->catch_msg("You narrowly miss " +
            QTNAME(enemy) + " with your sword.\n");
        
        /* Message to victim */
        enemy->catch_msg( QCTNAME(QW) + " narrowly misses you with " 
            + QPOS(QW) + " sword.\n");
    
        /* Message to everyone else in the same room */
        tell_watcher( QCTNAME(QW) + " narrowly misses " + 
            QTNAME(enemy) + " with " + QPOS(QW) + 
            " sword.\n", QW, enemy );
    
        return 1; /* Return 1 as message has been rewritten */
    }

    if (phurt == 1) /* 1% of remaining hp lost in attack */
    {
        QW->catch_msg("You merely scratch the " + hdesc + " of " +
            QTNAME(enemy) + " with your sword.\n");
        
        enemy->catch_msg( QCTNAME(QW) + " merely scratches your " + 
            hdesc + " with " + QPOS(QW) + " sword.\n");
    
        tell_watcher( QCTNAME(QW) + " merely scratches the " + 
            hdesc + " of " + QTNAME(enemy) + " with " + QPOS(QW) + 
            " sword.\n", QW, enemy );
    
        return 1;
    }

    if (phurt ==2) /* 2% of remaining hp lost in attack */
    {
        QW->catch_msg("You cut the " + hdesc + " of " +
            QTNAME(enemy) + " slightly with your sword.\n");
        
        enemy->catch_msg( QCTNAME(QW) + " cuts your " + 
            hdesc + " slightly with " + QPOS(QW) + " sword.\n");
    
        tell_watcher( QCTNAME(QW) + " cuts the " + 
            hdesc + " of " + QTNAME(enemy) + " slightly with " 
            + QPOS(QW) + " sword.\n", QW, enemy );
    
        return 1;
    }

    if (phurt <= 4) /* 3% or 4% of remaining hp lost in attack */
    {
        QW->catch_msg("You slice a piece of skin off the " + hdesc + " of " +
            QTNAME(enemy) + " with your sword.\n");
        
        enemy->catch_msg( QCTNAME(QW) + " slices a piece of skin off your " + 
            hdesc + " with " + QPOS(QW) + " sword.\n");
    
        tell_watcher( QCTNAME(QW) + " slices a piece of skin off the " + 
            hdesc + " of " + QTNAME(enemy) + " with " 
            + QPOS(QW) + " sword.\n", QW, enemy );
        
        if ( TO->query_pen() >= 45) /* Extra messages if sword shimmering */
        {
            QW->catch_msg(QCTNAME(enemy) +" looks angry.\n");
        
            enemy->catch_msg("You look around angrily.\n");
        
            tell_watcher( QCTNAME(enemy) + 
            " looks angry.\n", QW, enemy );
        }
    
        return 1;
    }

    if (phurt <= 8) /* 5% to 8% of remaining hp lost in attack */
    {
        QW->catch_msg("You cut deep into the " + hdesc + " of " +
            QTNAME(enemy) + " with your sword.\n");
        
        enemy->catch_msg( QCTNAME(QW) + " cuts deep into your " + 
            hdesc + " with " + QPOS(QW) + " sword.\n");
    
        tell_watcher( QCTNAME(QW) + " cuts deep into the " + 
            hdesc + " of " + QTNAME(enemy) + " with " 
            + QPOS(QW) + " sword.\n", QW, enemy );
        
        if ( TO->query_pen() >= 45) /* Extra messages if sword shimmering */
        {
            QW->catch_msg(QCTNAME(enemy) +" winces from the deep cut.\n");
        
            enemy->catch_msg("You wince from the deep cut.\n");
        
            tell_watcher( QCTNAME(enemy) + 
            " winces from the deep cut.\n", QW, enemy );
        }
    
        return 1;
    }

    if (phurt <= 16) /* 9% to 16% of remaining hp lost in attack */
    {
        QW->catch_msg("You draw blood from the " + hdesc + " of " +
            QTNAME(enemy) + " with your sword.\n");
        
        enemy->catch_msg( QCTNAME(QW) + " draws blood from your " + 
            hdesc + " with " + QPOS(QW) + " sword.\n");
    
        tell_watcher( QCTNAME(QW) + " draws blood from the " + 
            hdesc + " of " + QTNAME(enemy) + " with " 
            + QPOS(QW) + " sword.\n", QW, enemy );
        
        if ( TO->query_pen() >= 45) /* Extra messages if sword shimmering */
        {
            QW->catch_msg(QCTNAME(enemy) +" cries out in pain.\n");
        
            enemy->catch_msg("You cry out in pain.\n");
        
            tell_watcher( QCTNAME(enemy) + 
            " cries out in pain.\n", QW, enemy );
        }
    
        return 1;
    }

    if (phurt <= 25) /* 17% to 25% of remaining hp lost in attack */
    {
        QW->catch_msg("You viciously slash the " + hdesc + " of " +
            QTNAME(enemy) + " with your sword.\n");
        
        enemy->catch_msg( QCTNAME(QW) + " viciously slashes your " + 
            hdesc + " with " + QPOS(QW) + " sword.\n");
    
        tell_watcher( QCTNAME(QW) + " viciously slashes the " + 
            hdesc + " of " + QTNAME(enemy) + " with " 
            + QPOS(QW) + " sword.\n", QW, enemy );
        
        if ( TO->query_pen() >= 45) /* Extra messages if sword shimmering */
        {
            QW->catch_msg(QCTNAME(enemy) +" recoils in pain from the blow.\n");
        
            enemy->catch_msg("You recoil in pain from the blow.\n");
        
            tell_watcher( QCTNAME(enemy) + 
            " recoils in pain from the blow.\n", QW, enemy );
        }
    
        return 1;
    }

    if (phurt <= 50) /* 26% to 50% of remaining hp lost in attack */
    {
        QW->catch_msg("You wound very deeply the " + hdesc + " of " +
            QTNAME(enemy) + " with your sword.\n");
        
        enemy->catch_msg( QCTNAME(QW) + " wounds very deeply your " + 
            hdesc + " with " + QPOS(QW) + " sword.\n");
    
        tell_watcher( QCTNAME(QW) + " wounds very deeply the " + 
            hdesc + " of " + QTNAME(enemy) + " with " 
            + QPOS(QW) + " sword.\n", QW, enemy );
        
        if ( TO->query_pen() >= 45) /* Extra messages if sword shimmering */
        {
            QW->catch_msg(QCTNAME(enemy) + " screams out loud in pain!\n");
        
            enemy->catch_msg("You scream out loud in pain!\n");
        
            tell_watcher( QCTNAME(enemy) + 
            " screams out loud in pain!\n", QW, enemy );
        }
    
        return 1;
    }

    if (phurt <= 70) /* 51% to 70% of remaining hp lost in attack */
    {
        QW->catch_msg("You virtually slice " + QTNAME(enemy) + 
            " into two pieces with your sword.\n");
        
        enemy->catch_msg( QCTNAME(QW) + " virtually slices you into two" + 
            " pieces with " + QPOS(QW) + " sword.\n");

        tell_watcher( QCTNAME(QW) + " virtually slices " + 
            QTNAME(enemy) + " into two pieces with " + QPOS(QW) + 
            " sword.\n", QW, enemy );
        
        if ( TO->query_pen() >= 45) /* Extra messages if sword shimmering */
        {
            QW->catch_msg(QCTNAME(enemy) + " howls in sheer agony!\n");
        
            enemy->catch_msg("You howl in sheer agony!\n");
        
            tell_watcher( QCTNAME(enemy) + 
            " howls in sheer agony!\n", QW, enemy );
        }
    
        return 1;
    }

    if (phurt <= 120) /* 71% to 120% of remaining hp lost in attack */
    {
        QW->catch_msg("You mercilessly slaughter " + QTNAME(enemy) + 
             " with your sword.\n");
        
        enemy->catch_msg( QCTNAME(QW) + " mercilessly slaughters you" + 
            " with " + QPOS(QW) + " sword.\n");
    
        tell_watcher( QCTNAME(QW) + " mercilessly slaughters " + 
            QTNAME(enemy) + " with " + QPOS(QW) +
            " sword.\n", QW, enemy );
        
        if ( TO->query_pen() >= 45) /* Extra messages if sword shimmering */
        {
            QW->catch_msg(QCTNAME(enemy) + " gasps for a final breath...\n");
        
            enemy->catch_msg("You gasp for a final breath...\n");
        
            tell_watcher( QCTNAME(enemy) + 
            " gasps for a final breath...\n", QW, enemy );
        }
    
        return 1;
    }
    return 0;
}

/*
 * Function name: tell_watcher
 * Description:   Send string to people in the room who want to see the fight.
 * Arguments:     string to be sent, object wielder, object enemy
 */
public void
tell_watcher(string fight_message, object wielder, object enemy)
{
    object *ob_list;
    int i;

    ob_list = FILTER_LIVE(all_inventory(ENV(wielder))) - ({ wielder });
    ob_list -= ({ enemy });
    for ( i=0; i < sizeof( ob_list ); i++ )
    {
        if ( ob_list[i] -> query_see_blood() )
            ob_list[i] -> catch_msg( fight_message );
    }

    return;
}
