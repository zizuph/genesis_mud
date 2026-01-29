
 /*    
    The king of Thalassia

    coder(s):    Jaacar

    history:    21.7.03    coded                        Jaacar
                23.7.03    added defeat code written    Jaacar
                           by Lilith (Thanks Lilith!) 
                12.11.09   Fixed incorrect usage of clone_unique           
 */

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <composite.h>
#include <formulas.h>
#include "defs.h"

#define DEATH_LOG "thal_king_death_log"
#define WOUNDING_OBJ "/d/Genesis/specials/std/wounding_obj_base"
#define THALASSIAN_KING_CHALLENGED "_i_challenged_atlas"

inherit SEA_CREATURES+"triton";
inherit "/d/Calia/std/intro";
inherit "/d/Calia/std/defeat";
inherit "/lib/unique";

void
equip_me()
{
    object this, trident;
    string type;

    this = THIS;
    seteuid(getuid(this));
    // Changed to 66% chance of golden trident being cloned and
    // increased the number of golden tridents slightly
    //   - Petros (January 2009)
    trident = clone_unique(SEA_WEAPONS+"magic_trident", 3,
        SEA_WEAPONS+"ori_trident", 1, 66);
    trident->move(this);
    command("wield trident");
    clone_object(SEA_ARMOURS+"triton_armour")->move(this);
    clone_object(SEA_ARMOURS+"triton_helmet")->move(this);
    command("wear all");
    MONEY_MAKE_PC((1+random(3)))->move(this);
}

void
create_triton()
{
    if (!IS_CLONE)
	return;

    ::create_triton();
    set_long("He is a strikingly beautiful creature with long "+
        "black hair.  He is human in appearance above the waist, "+
        "but has a large fish-like tail instead of legs.  He is "+
        "covered in dark green scales, and has long, sharp claws on "+
        "his webbed fingers.  His friendly smile reveals what look "+
        "like very sharp fish teeth.\n");
    set_race_name("triton");
    set_adj(({"strong","regal-looking"}));
    add_name("king");
    add_name("atlas");
    set_name("Atlas");
    set_title("the King of Thalassia");
    set_base_stat(SS_INT, (150+random(30)));
    set_base_stat(SS_WIS, (150+random(30)));
    set_base_stat(SS_DIS, (150+random(30)));
    set_base_stat(SS_STR, (180+random(30)));
    set_base_stat(SS_DEX, (200+random(30)));
    set_base_stat(SS_CON, (180+random(30)));
    set_skill(SS_WEP_POLEARM, (100));
    set_skill(SS_PARRY, (100));
    set_skill(SS_DEFENCE, (100));
    set_alignment(500);
    add_prop(CONT_I_WEIGHT, 75000);
    add_prop(CONT_I_VOLUME, 75000);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_QUICKNESS, 100);
    set_act_time(15);
    add_act("emote bubbles: Don't be starting any trouble in here.");
    add_act("emote bubbles: Thalassia is a grand city indeed.");
    add_act("emote bubbles: It's rare for me to find someone who is "
        + "worthy to fight me. Who dares to challenge me?");
    add_act("emote bubbles: Many out there desire my trident. But who "
        + "is worthy enough to challenge me for it?");
    set_all_hitloc_unarmed(query_average_stat() / 4);
    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"job","guard"}),
        "say My job is to rule this city.",1);
    add_ask(({"thalassia","Thalassia","city"}),
        "say Thalassia is my home. I have ruled for many years, and "+
        "shall continue to do so for many more.",1);
    add_ask( ({ "challenge", "worthy", "fight" }),
        "say Do you come here for a challenge? If so, by all means "
      + "and I shall reward you with my weapon should you win!", 1);
    add_ask( ({ "trident" }),
        "say My trident, you ask? If you wish it, I dare you to "
      + "challenge me for it!", 1);
}

public string
default_answer()
{
    command("say I do not know of what you speak.");
    return "";
}

public void
do_die(object killer)
{
    object *foos = query_enemy(-1);
    string *killers;
    int challenged = 0;
    
    if (query_hp() > 0)
        return 0;

    if (!killer)
        killer = previous_object();

    if (sizeof(filter(foos, &operator(==)(1) @ 
                      &->query_prop(THALASSIAN_KING_CHALLENGED))))
    {
        challenged = 1;
    }
    
    foos -= ({ killer });
    killers = (foos)->query_name();

    if (killer && environment(TO) == environment(killer)) 
    {
        if (challenged)
        {
            tell_room(environment(TO), QCTNAME(TO) + " says: It seems "
                + "you have lived up to your challenge. I shall reward "
                + "you with my weapon.\n"
                + QCTNAME(TO) + " swims away and slowly fades from "
                + "view.\n");
        }
        else
        {
            tell_room(environment(TO), (QCTNAME(TO) + 
                " says: You thought you could kill me?\n"+
                "Hearty laughter echoes in the room as he "+
                "slowly fades from view.\n"));
        }
    }

    log_file(DEATH_LOG, ctime(time())+" Thalassian King defeated by "+ 
        killer->query_name() +"("+ killer->query_average_stat() +") "+ 
        (sizeof(killers) ? "with "+ COMPOSITE_WORDS(killers) : "solo")+".\n");
    ::do_die(killer);

}

/*
 * Function name: special_attack
 * Description  : Special attack for this npc.
 * Arguments    : enemy - Object pointer to the living to attack.
 * Returns      : 1 - Made attack, no further attacks this round.
 *                0 - No special attack, continue normal combat round.
 */
public int
special_attack(object enemy)
{
    string tar, wat;
    object weapon, cobj;
    object * weapons;
    
    if (random(4))
        return 0;      /* 25% chance of special attack. */

    // Make sure that we can actually attack the target
    if (enemy->query_not_attack_me(this_object(), -1))
    {
        return 0;
    }

    weapons = query_weapon(-1);
    if (!pointerp(weapons) || !sizeof(weapons))
    {
        return 0;
    }
    
    weapon = one_of_list(weapons);
    
    tar = QCTNAME(this_object()) + " thrusts his " + weapon->short()
        + " at you and ";
    wat = QCTNAME(this_object()) + " thrusts his " + weapon->short()
        + " at " + QTNAME(enemy) + " and "; 

    mixed hitresult = ({ -1, -1, -1, -1, -1 });
    cobj = query_combat_object();
    if (cobj->cb_tohit(-1, 100, enemy))
    {
        hitresult = enemy->hit_me(F_PENMOD(weapon->query_pen(), 100), 
                      W_IMPALE, this_object(), -1, -1); 
    }
    
    if (hitresult[0] < 0)
    {
        tar += "just barely misses you.\n";
        wat += "just barely misses " + enemy->query_objective() + ".\n";
    }
    else
    {        
        switch (hitresult[0])
        {
        case 0..5:
            tar += "barely manages to impale you.\n";
            wat += "barely manages to impale " + enemy->query_objective()
                + ".\n";
            break;
        
        case 6..10:
            tar += "manages to pierce you deeply, ripping out your flesh "
                + "as he pulls his " + weapon->short() + " back out.\n";
            wat += "manages to pierce " + QTNAME(enemy) + " deeply, "
                + "ripping out " + enemy->query_possessive() + " flesh "
                + "as he pulls his " + weapon->short() + " back out.\n";
            break;
        
        case 11..20:
            tar += "pierces you through and through, then causing a deep "
                + "bleeding wound as he pulls backwards on his "
                + weapon->short() + ".\n";
            wat += "pierces " + QTNAME(enemy) + " through and through, "
                + "then causing a deep bleeding wound as he pulls backwards "
                + "on his " + weapon->short() + ".\n";
            break;
        
        case 21..40:
            tar += "quickly changes direction and hits you with the base "
                + "of his " + weapon->short() + ", before finally thrusting "
                + "deeply into your body, ripping out flesh from the "
                + "opposite side.\n";
            wat += "quickly changes direction and hits " + QTNAME(enemy)
                + " with the base of his " + weapon->short() + ", before "
                + "finally thrusting deeply into your body, ripping out "
                + "flesh from the opposite side.\n";
            break;
        
        default:
            tar += "devastates you as he pierces your vital organs "
                + "before lifting you briefly in the air and kicking "
                + "you off of his " + weapon->short() + ".\n";
            wat += "devastates " + QTNAME(enemy) + " as he pierces "
                + enemy->query_possessive() + " vital organs before "
                + "lifting " + enemy->query_objective() + " briefly in "
                + "the air and kicking " + enemy->query_objective()
                + " off of his " + weapon->short() + ".\n";
            break;
        }
    }
    
    enemy->catch_msg(tar);
    enemy->tell_watcher(wat, enemy);
    
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(this_object());
        return 1;
    }
    
    // Add a bleeding wound object
    int dam = 0;
    int hid = -1;
    if (sizeof(hitresult) >= 5)
    {
        dam = hitresult[3];
        hid = hitresult[4];
    }
    
    if (dam > 0)
    {
        // Add a bleeding wound object
        setuid();
        seteuid(getuid());
        object wound_obj = clone_object(WOUNDING_OBJ);
        wound_obj->set_wounding_damage(dam / 4);
        wound_obj->set_wounding_hitloc(hid);
        wound_obj->move(enemy);
        wound_obj->start();
    }            

    return 1;
}
