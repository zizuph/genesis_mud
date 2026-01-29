
/*
 * banshee.c
 *
 * An undead Banshee for the Undead Tunnels near
 * Eldoral
 *
 * Copyright (C): Jaacar (Mike Phipps), October 8th, 2003
 *
 * - Removed obsolete tell_watcher function (Petros)
 * - Rewritten to use the new undead base (Petros)
 */

#include "defs.h"
inherit ELDORAL_UNDEAD_HUMANOID;

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <formulas.h>
#include <composite.h>
#include <tasks.h>

void
create_undead_creature()
{
    set_short("old grey-haired banshee");
    set_adj(({"old","grey-haired"}));
    set_race_name("banshee");
    set_long("This creature is the spirit of an evil female elf. "+
        "She is now merely a floating, luminous phantom of her former "+
        "self. She is old and withered and her hair is wild and unkempt. "+
        "She is wearing tattered rags and her face is a mask of pain and "+
        "anguish, but hatred and ire burn brightly in her eyes.\n");

    set_alignment(-600);
    set_gender(G_FEMALE);
    add_prop(OBJ_I_RES_MAGIC, 20);
    set_aggressive(1);

    set_act_time(30);
	add_act("emote lets out a loud wail.");
	add_act("emote cries out in pain.");

    set_cact_time(15);
    add_cact("emote lets out a loud sorrowful wail.");
    add_cact("emote seems to phase in and out of sight.");
    add_cact("emote reaches out ominously with her ghostly hand.");
    
    default_config_undead(130); 

    set_all_hitloc_unarmed( ({ 40, 40, 40 }) );

    set_exp_factor(125); // extra 20% panic and very hard hitting
                         // special that happens pretty often without
                         // checks for cb_tohit.
}

public void
add_treasure(object npc)
{
    ::add_treasure(npc);
    MONEY_MAKE_GC(random(2)+2)->move(npc);    
}

public void
equip_undead(object npc)
{
    object gloves;

    gloves = clone_object(TUN_ARMOURS+"snake_gloves");
    gloves->move(npc);
    npc->command("wear gloves");
}

/*
 * Function name: special_attack
 * Description  : Special attack for this NPC
 * Arguments    : enemy - Object pointer to the living to attack.
 * Returns      : 1 - Made attack, no further attacks this round.
 *                0 - No special attack, continue normal combat round.
 */
public int
special_attack(object enemy)
{
    int success, pen, panic;
    string tar, wat;
    
    if (random(3))
        return 0;      /* 33% chance of special attack. */

    // Though a shriek cannot really be avoided by evasion, we will still
    // check query_not_attack_me
    if (enemy->query_not_attack_me(this_object(), -1))
    {
        return 0;
    }

    // A banshee cannot wail if she is silenced
    if (this_object()->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        enemy->catch_tell("The banshee opens her mouth to direct a "
            + "shrieking wail towards you, but cannot seem to make "
            + "a sound.\n");
        enemy->tell_watcher("The banshee opens her mouth to direct a "
            + "shrieking wail towards " + QTNAME(enemy) + ", but cannot "
            + "seem to make a sound.\n");
        return 0;
    }
    

    tar = "The banshee lets out a loud wail directed at you. ";
    wat = "The banshee lets out a loud wail directed at " + QTNAME(enemy)
        + ". ";
        
    success = this_object()->resolve_task(TASK_ROUTINE, ({ TS_DIS }),
                enemy, ({ TS_DIS }) );
    pen = 100;  
    panic = 1; // start with 1% of panic value
    switch (success)
    {
        case -1050..0:
            tar += "You maintain full control of your senses and cover "
                + "your ears to reduce the pain induced by the high-pitched "
                + "sound.\n";
            wat += QTNAME(enemy) + " maintains full control of "
                + enemy->query_possessive() + " senses and covers "
                + enemy->query_possessive() + " ears in an attempt "
                + "to reduce the pain from the high-pitched sound.\n";
            break;
        
        case 1..20:
            pen = 150;
            panic = 5; // 5% of max panic
            tar += "You have trouble maintaining control of your senses "
                + "as the your head rings with pain from the high-pitched "
                + "wail.\n";
            wat += QTNAME(enemy) + " looks very panicky as " + enemy->query_pronoun()
                + " tries to maintain control.\n";
            break;
            
        case 21..40:
            pen = 300;
            panic = 10;
            tar += "You can barely focus on your movements as your mind is "
                + "overcome by the high-pitched wail.\n";
            wat += QTNAME(enemy) + " looks to be having difficulty "
                + "controlling " + enemy->query_possessive() + " movements.\n";
            break;
            
        case 41..60:
            pen = 450;
            panic = 15;
            tar += "You feel blood start to drip out of your ears and feel "
                + "an overwhelming urge to flee to somewhere safe.\n";
            wat += QTNAME(enemy) + " starts to bleed out of " 
                + enemy->query_possessive() + " ears and appears to "
                + "be ready to flee.\n";
            break;
        
        case 61..80:
            pen = 600;
            panic = 20;
            tar += "Your head feels like it is going to explode, and you "
                + "become very panicky as you lose control of your "
                + "movements.\n";
            wat += QTNAME(enemy) + " looks very panicky as " + enemy->query_pronoun()
                + " tries to maintain control of " + enemy->query_possessive()
                + " movements.\n";
            break;
        
        default:
            pen = 750;
            panic = 25;
            tar += "You start to feel extremely panicky and feel yourself "
                + "losing completely control of your senses. Your head "
                + "throbs with pain and it feels like it is going to "
                + "explode.\n";
            wat += QTNAME(enemy) + " looks like " + enemy->query_pronoun()
                + " is losing complete control of " + enemy->query_possessive()
                + " senses.\n";
            enemy->add_panic(100);
            break;
    }
    
    enemy->catch_tell(tar);
    enemy->tell_watcher(wat, enemy);
    
    enemy->add_panic(F_PANIC_WIMP_LEVEL(enemy->query_stat(SS_DIS)) * panic / 100);
    // Deal damage depending on the difference in discipline    
    mixed hitresult = enemy->hit_me(pen, MAGIC_DT, 
                                    this_object(), -1, -1);
    send_debug_message("eldoral_banshee", "Damage inflicted is " 
                       + hitresult[3]);
    
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(this_object());
    }
    
    return 1;
}

public void
do_die(object killer)
{
    tell_room(environment(this_object()), "The banshee lets out a loud "
        + "wailing noise. There is a blinding flash of light, causing "
        + "you to avert your eyes for a moment. When you look back, the "
        + "banshee is gone.\n");
    ::do_die(killer);
}
