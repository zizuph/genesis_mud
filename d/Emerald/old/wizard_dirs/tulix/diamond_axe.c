/* The Diamond edged axe - originally coded 01/09/95 by Tulix III.         */
/* Based on the Nemesis sword as it was on 29/08/95 (Original by Tulix I). */
/* This weapon is used by /d/Emerald/conq_tower/npc/giant_goblin.c         */

#include "/d/Emerald/defs.h"  /* This weapon uses defines from this file */
inherit "/std/weapon";
#include <wa_types.h>
#include <filter_funs.h>

/* Defines not in defs.h */ 
#define QW             query_wielded()
#define QPOS(QW)       QW->query_possessive() 
#define FREEZE_OBJECT  CONQ_TOWER_DIR + "obj/freeze_object"

/* Global variable */
public int glow;   /* Value is 1 if diamonds are glowing, 0 if not glowing */

/* Prototype functions */
public void do_freeze(object victim, int base_delay);
public string extra_axe_desc();
public void reset_axe();
public string diamonds_desc();
public void tell_watcher(string fight_message, object wielder, object enemy);

public void
create_weapon()
{
    set_name("axe");
    set_short("diamond edged axe");
    set_adj("diamond edged");
    add_adj("diamond");
    add_name("weapon");

    set_long("This is no ordinary axe. Diamonds have been set along the "  
        + "cutting edge of the blade, dramatically enhancing the " 
        + "effectiveness of an already fearsome weapon. It is far too big "
        + "to wield in one hand, and requires a lot of strength to wield. "
        + "If you can wield it though, be sure it will serve you well."
        + "@@extra_axe_desc");

    set_hit(40);
    set_pen(44);   
    
    set_wt(W_AXE);                 /* Weapon is a type of axe         */
    set_dt(W_SLASH|W_BLUDGEON);    /* Give slash & bludgeon damage    */
    set_hands(W_BOTH);             /* Weapon is wielded in both hands */
    
    setuid();
    seteuid(getuid(this_object()));
    
    add_prop(OBJ_I_WEIGHT, 16000); /* Weight 16 kg       */
    add_prop(OBJ_I_VOLUME, 4000);  /* Takes up 4 litres  */
    add_prop(OBJ_I_VALUE, 2000);   /* Worth lots of cash */
    
    /* Set props required by /doc/man/general/weapon & weapon_guide */
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 35, "enchantment"}) );
    add_prop(MAGIC_AM_ID_INFO, ({ 
        "The axe seems magical.\n",  0,
        "The axe will do something magical in combat.\n",  20,
        "The diamonds in the axe will glow during combat.\nIf you hit "+
        "your opponent with the axe while the diamonds glow, your opponent " +
        "will be affected.\n",  40,
        "This axe is magical. During random points during combat,\n" +
        "the diamonds set along the blade of the axe will glow. " +
        "If you hit your opponent with the axe while the diamonds are " +
        "glowing, then your opponent will freeze.\n" +
        "This effect is only temporary, however. " +
        "Shine on, you crazy diamond!\n",  80 }) );
    
    add_prop(OBJ_S_WIZINFO, "This is a magical axe. "
        + "It will freeze your opponent briefly at random times during "
        + "combat, assuming you do manage to hit while the dimonds glow. "
        + "This axe is cloned by /d/Emerald/conq_tower/npc/giant_goblin.c.\n"
        + "He is found in /d/Emerald/conq_tower/towertop.c (with guards).\n"
        + "Shine on, you crazy diamond!\n");

    add_item(({"diamond", "diamonds"}), "@@diamonds_desc");
}

/*
 * Function name: do_freeze
 * Description:   This function freezes the enemy for a period of time.
 * Arguments:     victim     = the enemy
 *                base_delay = base time period enemy is frozen for (seconds)
 */
public void
do_freeze(object victim, int base_delay)
{
    int random_delay;
    object freeze_object;

    random_delay = 20; /* For debug pruposes. Will be random(x) */

    freeze_object = victim->present("diamond_axe_freeze_object");
    if (freeze_object)
    {
        freeze_object->unfreeze_victim();
    }

    freeze_object = clone_object(FREEZE_OBJECT);
    freeze_object -> set_unfreeze_delay(base_delay + random_delay);
    freeze_object -> move(victim);

    return;
}


/*
 * Function name: extra_axe_desc
 * Description:   This function adds an extra sentence to the set_long via vbfc
 *                to inform the wielder if the diamonds are currently glowing.
 * Returns:       description of the diamonds, or "\n" if not glowing.
 */
public string
extra_axe_desc()
{
    if ( glow == 1 )
        return ("\nThe diamonds along the edge of the blade are glowing!\n");
    else
        return ("\n");
}

/*
 * Function name: diamonds_desc
 * Description:   This function adds the add_item vbfc 'diamonds' to the axe.
 * Returns:       Description of the diamonds, even if not glowing.
 */
public string
diamonds_desc()
{
    if ( glow == 1 )
        return ("\nThe diamonds along the edge of the blade are glowing!\n");
    else
        return ("\nThe diamonds are not gem quality, but seem special...\n");
}

/*
 * Function name: try_hit
 * Description:   This function called every time the weapon is to be used 
 *                in an attack. Here we use it to decide when to freeze the
 *                opponent, on average once every twenty attacks. 
 * Returns:       1 - carry on with attack: 0 - skip attack (not used)  
 */
public int 
try_hit(object ob)
{
    int a,b;
 
    a=random(20);
 
    if (a!=0)                                       /* Not lucky this time */
        return 1;
 
    if ( glow == 1 )
        return 1;                       /* diamonds may already be glowing */
 
    glow = 1;                                 /* Set diamonds glowing      */
    
    TO->add_prop(OBJ_I_LIGHT, 1);                /* The diamonds really glow  */
    
    QW->update_weapon( TO );                  /* Weapon already wielded    */
 
    tell_room(ENV(QW), "The diamonds set in the axe wielded by " + QTNAME(QW)+ 
        " suddenly start to glow!\n", QW);    /* Tell others about glow    */
                                         
    QW->catch_msg("The diamonds set along the blade of your axe suddenly " +
        "start to glow!\n");                  /* Tell wielder too          */

    a = 20;
    
    set_alarm( itof(a), 0.0, reset_axe);      /* Set alarm for axe reset   */

    return 0;
}
 
/*
 * Function name: reset_axe
 * Description:   This function called to stop the diamonds glowing
 */
public void
reset_axe()
{
    if ( glow == 0)
        return;

    glow =0;
    
    if (QW)                              /* axe might not be wielded now */
    {
        QW->update_weapon( TO );
        
        tell_room(ENV(QW), "The diamonds set in the axe wielded by "
            + QTNAME(QW) + " stop glowing.\n", QW);
 
        QW->catch_msg("The glow from the diamonds set in the blade of your " +
            "axe fades away.\n");
    }
    else
    {
        tell_room( EO, "The glow from the diamonds in the axe fades away.\n");
    }
    
    TO->remove_prop(OBJ_I_LIGHT);

    return;
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
        QW->catch_msg("You swipe your axe violently at " +
            QTNAME(enemy) + ", but miss.\n");
        
        enemy->catch_msg( QCTNAME(QW) + " swipes " + QPOS(QW) +
            " axe violently at you, but misses.\n");
    
        tell_watcher( QCTNAME(QW) + " swipes " + QPOS(QW) +
            " axe wildly at " + QTNAME(enemy) +
            ", but misses.\n", QW, enemy );
    
    return 1;
    }

    if (phurt == 0) /* No damage to enemy in this attack */
    {
        /* Message to wielder of weapon */
        QW->catch_msg("Your axe only misses " +
            QTNAME(enemy) + " by a whisker.\n");
        
        /* Message to victim */
        enemy->catch_msg( QCTNAME(QW) + " misses you " +
            " only by a whisker with " + QPOS(QW) + " axe.\n");
    
        /* Message to everyone else in the same room */
        tell_watcher( QCTNAME(QW) + " misses " + 
            QTNAME(enemy) + " with " + QPOS(QW) + 
            " axe, but only by a whisker.\n", QW, enemy );
    
        return 1; /* Return 1 as message has been rewritten */
    }

    if (phurt == 1) /* 1% of remaining hp lost in attack */
    {
        QW->catch_msg("You just manage to hit the " + hdesc + " of " +
            QTNAME(enemy) + " with your axe.\n");
        
        enemy->catch_msg( QCTNAME(QW) + " just manages to hit your " + 
            hdesc + " with " + QPOS(QW) + " axe.\n");
    
        tell_watcher( QCTNAME(QW) + " just manages to hit the " + 
            hdesc + " of " + QTNAME(enemy) + " with " + QPOS(QW) + 
            " axe.\n", QW, enemy );
    
        return 1;
    }

    if (phurt ==2) /* 2% of remaining hp lost in attack */
    {
        QW->catch_msg("You bruise the " + hdesc + " of " +
            QTNAME(enemy) + " slightly with your axe.\n");
        
        enemy->catch_msg( QCTNAME(QW) + " bruises your " + 
            hdesc + " slightly with " + QPOS(QW) + " axe.\n");
    
        tell_watcher( QCTNAME(QW) + " bruises the " + 
            hdesc + " of " + QTNAME(enemy) + " slightly with " 
            + QPOS(QW) + " axe.\n", QW, enemy );
    
        return 1;
    }

    if (phurt <= 4) /* 3% or 4% of remaining hp lost in attack */
    {
        QW->catch_msg("You hack some flesh off the " + hdesc + " of " +
            QTNAME(enemy) + " with your axe.\n");
        
        enemy->catch_msg( QCTNAME(QW) + " hacks some flesh off your " + 
            hdesc + " with " + QPOS(QW) + " axe.\n");
    
        tell_watcher( QCTNAME(QW) + " hacks some flesh off the " + 
            hdesc + " of " + QTNAME(enemy) + " with " 
            + QPOS(QW) + " axe.\n", QW, enemy );
        
        if ( glow == 1 )          /* Freeze enemy if diamonds glow       */
        {
            do_freeze(enemy, 2);  /* Freeze the enemy for a short period */
            
            QW->catch_msg(QCTNAME(enemy) +" looks slightly stunned.\n");
        
            enemy->catch_msg("You stunned slightly by a " + 
                "shock from the axe.\n");
        
            tell_watcher( QCTNAME(enemy) + 
            " looks slightly stunned by the blow from the axe.\n", QW, enemy );
        
            reset_axe();          /* Stop diamonds glowing */
        }
    
        return 1;
    }

    if (phurt <= 8) /* 5% to 8% of remaining hp lost in attack */
    {
        QW->catch_msg("You pound the " + hdesc + " of " +
            QTNAME(enemy) + " with your axe.\n");
        
        enemy->catch_msg( QCTNAME(QW) + " pounds your " + 
            hdesc + " with " + QPOS(QW) + " axe.\n");
    
        tell_watcher( QCTNAME(QW) + " pounds the " + 
            hdesc + " of " + QTNAME(enemy) + " with " 
            + QPOS(QW) + " axe.\n", QW, enemy );
        
        if ( glow == 1 )          /* Freeze enemy if diamonds glow       */
        {
            do_freeze(enemy, 3);  /* Freeze the enemy for a short period */
            
            QW->catch_msg(QCTNAME(enemy) +" is stunned by the axe.\n");
        
            enemy->catch_msg("You are stunned by a shock from the axe.\n");
        
            tell_watcher( QCTNAME(enemy) + 
            " looks stunned by a shock from the axe.\n", QW, enemy );
        
            reset_axe();          /* Stop diamonds glowing */
        }
    
        return 1;
    }

    if (phurt <= 16) /* 9% to 16% of remaining hp lost in attack */
    {
        QW->catch_msg("You beat blood out of the " + hdesc + " of " +
            QTNAME(enemy) + " with your axe.\n");
        
        enemy->catch_msg( QCTNAME(QW) + " beats blood out of your " + 
            hdesc + " with " + QPOS(QW) + " axe.\n");
    
        tell_watcher( QCTNAME(QW) + " beats blood out of the " + 
            hdesc + " of " + QTNAME(enemy) + " with " 
            + QPOS(QW) + " axe.\n", QW, enemy );
        
        if ( glow == 1 )          /* Freeze enemy if diamonds glow       */
        {
            do_freeze(enemy, 4);  /* Freeze the enemy for a short period */
            
            QW->catch_msg(QCTNAME(enemy) +" looks shocked.\n");
        
            enemy->catch_msg("You get a shock from the axe.\n");
        
            tell_watcher( QCTNAME(enemy) + 
            " looks shocked by the blow from the axe.\n", QW, enemy );
        
            reset_axe();          /* Stop diamonds glowing */
        }
    
        return 1;
    }

    if (phurt <= 25) /* 17% to 25% of remaining hp lost in attack */
    {
        QW->catch_msg("You spitefully gash the " + hdesc + " of " +
            QTNAME(enemy) + " with your axe.\n");
        
        enemy->catch_msg( QCTNAME(QW) + " spitefully gashes your " + 
            hdesc + " with " + QPOS(QW) + " axe.\n");
    
        tell_watcher( QCTNAME(QW) + " spitefully gashes the " + 
            hdesc + " of " + QTNAME(enemy) + " with " 
            + QPOS(QW) + " axe.\n", QW, enemy );
        
        if ( glow == 1 )          /* Freeze enemy if diamonds glow       */
        {
            do_freeze(enemy, 5);  /* Freeze the enemy for a short period */
            
            QW->catch_msg(QCTNAME(enemy) +" is badly shocked.\n");
        
            enemy->catch_msg("You get a bad shock from the axe.\n");
        
            tell_watcher( QCTNAME(enemy) + 
            " looks badly shocked by the blow from the " +
            "axe.\n", QW, enemy );
        
            reset_axe();          /* Stop diamonds glowing */
        }
    
        return 1;
    }

    if (phurt <= 50) /* 26% to 50% of remaining hp lost in attack */
    {
        QW->catch_msg("You wound badly the " + hdesc + " of " +
            QTNAME(enemy) + " with your axe.\n");
        
        enemy->catch_msg( QCTNAME(QW) + " wounds badly your " + 
            hdesc + " with " + QPOS(QW) + " axe.\n");
    
        tell_watcher( QCTNAME(QW) + " wounds badly the " + 
            hdesc + " of " + QTNAME(enemy) + " with " 
            + QPOS(QW) + " axe.\n", QW, enemy );
        
        if ( glow == 1 )          /* Freeze enemy if diamonds glow       */
        {
            do_freeze(enemy, 6);  /* Freeze the enemy for a short period */
            
            QW->catch_msg(QCTNAME(enemy) +" is very badly shocked.\n");
        
            enemy->catch_msg("You get a very bad shock from the axe.\n");
        
            tell_watcher( QCTNAME(enemy) + 
            " looks very badly shocked by the blow from the " +
            "axe.\n", QW, enemy );
        
            reset_axe();          /* Stop diamonds glowing */
        }
    
        return 1;
    }

    if (phurt <= 70) /* 51% to 70% of remaining hp lost in attack */
    {
        QW->catch_msg("You almost cut " + QTNAME(enemy) + 
            " in half with your axe.\n");
        
        enemy->catch_msg( QCTNAME(QW) + " almost cuts you in half " + 
            "with " + QPOS(QW) + " axe.\n");

        tell_watcher( QCTNAME(QW) + " almost cuts " + 
            QTNAME(enemy) + " in half with " + QPOS(QW) + 
            " axe.\n", QW, enemy );
        
        if ( glow == 1 )          /* Freeze enemy if diamonds glow       */
        {
            do_freeze(enemy, 6);  /* Freeze the enemy for a short period */
            
            QW->catch_msg(QCTNAME(enemy) +" is very badly shocked.\n");
        
            enemy->catch_msg("You get a very bad shock from the axe.\n");
        
            tell_watcher( QCTNAME(enemy) + 
            " looks very badly shocked by the blow from the " +
            "axe.\n", QW, enemy );
        
            reset_axe();          /* Stop diamonds glowing */
        }
    
        return 1;
    }

    if (phurt <= 99) /* 71% to 99% of remaining hp lost in attack */
    {
        QW->catch_msg("You barbarically slaughter " + QTNAME(enemy) + 
             " with your axe.\n");
        
        enemy->catch_msg( QCTNAME(QW) + " barbarically slaughters you" + 
            " with " + QPOS(QW) + " axe.\n");
    
        tell_watcher( QCTNAME(QW) + " barbarically slaughters " + 
            QTNAME(enemy) + " with " + QPOS(QW) +
            " axe.\n", QW, enemy );
        
        if ( glow == 1 )          /* Freeze enemy if diamonds glow       */
        {
            do_freeze(enemy, 6);  /* Freeze the enemy for a short period */
            
            QW->catch_msg(QCTNAME(enemy) +" is very badly shocked.\n");
        
            enemy->catch_msg("You get a very bad shock from the axe.\n");
        
            tell_watcher( QCTNAME(enemy) + 
            " looks very badly shocked by the blow from the " +
            "axe.\n", QW, enemy );
        
            reset_axe();          /* Stop diamonds glowing */
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

public int
wield(object wep)
{
    if (this_player()->query_stat(SS_STR) < 100)
    {
        write("The battleaxe is far too heavy for you to wield.\n");
        return -1;
    }

    return 0;
}
