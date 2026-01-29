/* This is Jorwarq, one of the regulars at the Grunts bar.  */
/* Coded 24/12/95 by Tulix III.                             */

inherit "/std/monster";

#include "/d/Emerald/tulix/t_defs.h"
#include "/d/Emerald/common/guild/grunts/grunts_defs.h"

/*
 * Function name: create_monster
 * Description:   define the all basics like race, stats, skills, etc. 
 */
public void 
create_monster()
{
    set_name("jorwarq");
    add_name(({ "drunk", "grunt" }));
    set_title("the drunken young Grunt");
    set_living_name("_jorwarq_");
    
    set_race_name("goblin");
    set_adj(({ "drunken", "young" }));
    
    set_short("drunken young goblin");
    set_long("This is one of the regular clients. He is drunk most of the " +
        "time, which is unusual, as most of the regulars are drunk all of " +
        "the time. He has a generally abusive manner, isn't really " +
        "violent. Unless the bar runs out of beer, of course.\n");
    
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_gender(0); /* Male */
 
    /* Stats -   STR  DEX  CON  INT  WIS  DIS  */
    set_stats(({  90,  80, 100,  60,  60,  80 }));
    set_alignment(-100);

    refresh_mobile();
 
    /* Set unarmed armour class and attacks. */
    set_all_hitloc_unarmed(30);
    set_all_attacks_unarmed(30, 30);

    /* Set the all important skills. */
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_DEFENCE, 70);
    
    set_skill(SS_AWARENESS, 60);
 
    set_chat_time(5);                 /* Set speaking interval            */
    add_chat("gImeE AnudUr beEr!");
    add_chat("dIs iz dA bEzt bAr fUr mIlez.");
    add_chat("gIz a kIsz bArmayd....!");

    set_cchat_time(2);                /* Set combat speaking interval     */
    add_cchat("ShtAnd shtill!");
    
    set_act_time(6);                  /* Set action interval              */
    add_act("grunt drunkenly");       /* Guess which guild he belongs to  */
    add_act("munch");
    add_act("wink barmaid");
    add_act("grdrool barmaid");
    add_act("flob");
    add_act("grope barmaid");
    add_act("ogle barmaid");

    setuid();
    seteuid(getuid());

    set_alarm( 2.0, 0.0, &init_soul(TO) ); /* Add the grunts command soul */
}


/* ***********************************************************************
 * Combat related functions
 */

/*                                     
 * Function name:   arm_me
 * Description:     give the barmaid her armour
 */
public void
arm_me()
{
    object armour;

    armour = clone_object( CAVE_DIR + "arm/fake_collar.c");
    armour -> move(TO);

    command("wear all");
}

/*
 * Function name: attack_object
 * Description:   This function is called when we attack another object
 * Arguments:     enemy - The object we are about to attack
 */
void
attack_object(object enemy)
{
    ::attack_object(enemy);

    /* Scare away our enemy (well, at least try) */
    command("warcry " + lower_case(TP->query_real_name()));
    
    return;
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     enemy - The attacker
 */
void
attacked_by(object enemy)
{
    ::attacked_by(enemy);

    /* Scare away our enemy (well, at least try) */
    command("warcry " + lower_case(TP->query_real_name()));

    return;
}

/* ***********************************************************************
 * Other functions
 */

/*
 * Function name:   init_soul
 * Description:     add the grunts command soul to the trainer
 * Arguments:       living: the living we wish to add the soul to
 */
public void
init_soul(object living)
{
    living->add_cmdsoul(GUILD_SOUL);
}
