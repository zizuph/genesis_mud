/* Minotaur Base, by Aridor 10/94
 * original by Splunge, 1/12/94
 *
 *
 * query_crash() added by Macker 10/27/94 
 * hook to trigger other special without masking original one by Torqual 
 * General Pointless Cleanups by Cotillion 2003-01-30
 * Added extra damage for special performed against other Dragonarmy
 * soldiers (works on Icewall only). - Blizzard, 6.10.2003
 * Louie Jan 2006 - Removed extra damage against DAs.
 */

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <macros.h>

inherit M_FILE
inherit "/d/Krynn/std/equip";

/* Undefine this if you do not want minotaurs to delive triple damage to 
   Dragonarmy members */
/*
#define HURT_DRAGONARMY 0
*/

/* prototypes */
int minotaur_special_attack(object enemy);
void arm_me();

/* variables */
/* defines */
#define MINOTAUR_I_OLD_ATTACK "_minotaur_i_old_attack"

void
create_minotaur()
{

    set_adj(({ "huge", "evil" }));

    set_long("@@my_long@@");
    set_act_time(10);
    add_act("emote snorts violently.");
    add_act("emote laughs at you with true amusement.");
    add_act("emote folds his arms across his massive chest.");
    add_act("emote looks you up and down, trying to find a red " + 
        "article of clothing.");
    

    arm_me();
}

void
create_krynn_monster()
{
    setuid();
    seteuid(getuid());
    
    set_name("minotaur");
    set_race_name("minotaur");

    set_stats(({ 100, 85, 110, 90, 50, 100 }));

    set_skill(SS_PARRY, 50);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_WEP_SWORD, 65);
    set_skill(SS_WEP_AXE, 90);
    set_skill(SS_AWARENESS, 33);
    
    /* They have thick skin by default */
    set_all_hitloc_unarmed(40);

    set_alignment(-300 - random(300));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(MINOTAUR_I_OLD_ATTACK,1);


    create_minotaur();
    
    /* We do this after create_minotaur since its stat dependant */
    set_knight_prestige(query_average_stat() * query_average_stat() / 10);

    refresh_mobile();
}

string
my_long()
{
    return ("This is an enormous, and very evil minotaur. His face is that " +
        "of a bull, but he walks upright and is able to use his hands. " +
        "He seems to be a true servant of Takhisis, and he appears to " +
        "be guarding something.\n");
}

public void
attacked_by(object ob)
{
    int  random_talk = random(5);
    
    ::attacked_by(ob);

    if (CAN_SEE_IN_ROOM(TO) && CAN_SEE(TO, ob))
    { 

#ifdef HURT_DRAGONARMY

        if ( ob->query_dragonarmy_occ_member() && 
            wildmatch("/d/Krynn/icewall/castle2/*", file_name(E(ob))) )
        {
            switch (random_talk)
            {
            case 0:
                command("say You triator! You think you can mess with " +
                    "the White Dragonarmy!?");
                command("emote snorts wildly.");
            break;
            case 1:
                command("say You better leave this place! Otherwise our " +
                    "dragons will take care of you!");
            break;
            case 2:
                command("say These barracks belong to the White " +
                    "Dragonarmy! Get lost or we will feed our dragons " +
                    "with you!");
            break;
            case 3:
                command("say Noone will stand against the White Dragonarmy!");
                command("emote roars wildly as " + HE(TO) + " enters the " +
                    "battle.");
            break;
            case 4:
                command("say Scum! Here is some training for you!");
                command("emote roars wildly.");
            break;
            }
            
            return;
            
        }
#endif
   
        command("say My dear " + ob->query_nonmet_name() + 
            ". You should know " +
            "better than to attack a minotaur.");
        command("emote snorts, and shakes his head in disappointment.");
    }
}

public void
help_friend(object ob)
{
    if (!objectp(ob) || query_attack() || environment() != environment(ob))
        return;

    if (!random(3))
        command("say Die enemy of the Minotaur race!");
    command("kill " + OB_NAME(ob));
    attack_object(ob);
}

void
arm_me()
{
    equip(({ "/d/Krynn/solace/lake/obj/flamberge1.c" }));
}


int
special_attack(object enemy)
{
    int attacktype, i, penet;
    mixed* hitresult;
    string how;
    object me=TO;

    /*
     * The ordinary special can be overriden with this prop.
     */
    if (!query_prop(MINOTAUR_I_OLD_ATTACK) ||
        random(4))
    {
        return minotaur_special_attack(enemy);
    }
    
    penet = query_stat(SS_STR);
    penet += random(3*penet);

#ifdef HURT_DRAGONARMY

 /* Minotaurs are more aggressive towards Dragonarmy members. */
    if ( enemy->query_dragonarmy_occ_member() &&
        wildmatch("/d/Krynn/icewall/castle2/*", file_name(E(enemy))) )
    {
        penet *= 2;
    }
    
#endif

    hitresult = enemy->hit_me(penet, W_IMPALE, me, -1);

	if (!sizeof(hitresult)) // Strange things may happen. Runtime fix. Milan 21.7.2004
		return 1;

    how = "misses, momentum carries " + HIM(TO) + " by. At " +
        "the verge of falling on " + HIS(TO) + " belly " +
        HE(TO) + " twists the body and, in amazing display " +
        "of agility, " + HE(TO) + " rolls over the arm and " +
        "ends up on " + HIS(TO) + " feet";
    if (hitresult[0] > 0)
        how = "his horns leaving just a scratch as he charges past";
    if (hitresult[0] > 10)
        how = "cutting wildly with his horns, leaving bloody wounds";
    if (hitresult[0] > 30)
        how = "hitting solidly with the flat of his head, causing a " +
            "resounding 'crack'! " + C(HIS(TO)) + " horns pierce two " +
            "round holes and blood begins to flow";
    if (hitresult[0] > 50)
        how = "goring deeply as he attempts to disembowel his opponent";
    if (hitresult[0] > 70)
        how = "impaling with his horns, then thrashing around madly, " +
            "causing extreme damage";

    enemy->catch_msg("The minotaur charges directly at you, " + how +
        "!\n");
    tell_watcher("The minotaur rushes at " + QTNAME(enemy) + ", "
        + how + "!\n",enemy);

    if (enemy->query_hp() <= 0)
    {
        write("The minotaur shakes his head madly as he throws the " +
            "lifeless body of " + QTNAME(enemy) + " across the room!\n");
        enemy->do_die(TO);
    }
    return 1;

}
/*
 * Function:    minotaur_special_attack
 * Description: it is a hook allowing coder to use minotaur base file and
 *              still be able to code additional special attack that will
 *              possibly be executed
 *              THIS SPECIAL ATTACK WILL BE USED _IF_ normal attack wont
 * Arguments:   object enemy derrived from special_attack function
 * Returns:     1 if welaunched special attack
 *              0 if we did nothing
 */
int
minotaur_special_attack(object enemy)
{
    return 0; // in case we did not mask this function
}
