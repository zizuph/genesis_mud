/* This is Luptord, the barmaid who serves the drinks in the Grunts   */
/* bar. Shes also  quite tough, after working in such a wrough joint. */
/* Coded 24/12/95 by Tulix III.                                       */

inherit "/std/monster";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Emerald/tulix/t_defs.h"
#include "/d/Emerald/common/guild/grunts/grunts_defs.h"

public void load_grunts_soul();

/*
 * Function name: create_monster
 * Description:   define the all basics like race, stats, skills, etc. 
 */
public void 
create_monster()
{
    set_name("luptord");
    add_name(({ "barmaid", "grunt" }));
    set_title("the Grunts barmaid");
    set_living_name("_luptord_");
    
    set_race_name("goblin");
    set_adj(({ "tough", "old" }));
    add_adj(({ "crusty", "old" }));
    
    set_short("tough old goblin barmaid");
    set_long("This crusty old goblin is responsible for keeping the " +
        "occupants of the bar happy - in other words, to keep them " +
        "supplied with beer. Working in such a rough place has given her " +
        "a great deal of experience in working with even the most rowdy " +
        "customers. It might be wise not to give her too much trouble.\n");
    
    add_prop(LIVE_I_QUICKNESS, 180);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_S_GRUNTS_WARCRY, "GEt Owt Ov mY bAr!");
    add_prop(OBJ_S_WIZINFO, "This is the Grunts barmaid.\n" +
        "A worthy adversary if you're looking for someone to fight...\n" );

    set_gender(1); /* Female */
 
    /* Stats -   STR  DEX  CON  INT  WIS  DIS  */
    set_stats(({ 190, 160, 180, 100, 100, 120 }));      /* Tough */
    set_alignment(-150);                  /* No angel, for sure. */

    add_prop(OBJ_I_WEIGHT, 100000);
    refresh_mobile();
 
    /* Set unarmed armour class and attacks. */
    set_all_hitloc_unarmed(35);      /* Yeah, shes rough, tough, */
    set_all_attack_unarmed(35, 35);  /* and dangerous to know... */

    /* Set the all important skills. */
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_BLIND_COMBAT, 70);
    set_skill(SS_DEFENCE, 90);
    
    set_skill(SS_AWARENESS, 80);
 
    set_chat_time(5);                 /* Set speaking interval            */
    add_chat("gEt yOor beEr Ere.");
    add_chat("I recOmen dA mOonshyne.");
    add_chat("Da gwUnts cun gEt vIolunt In Ere sumtImz.");
    add_chat("Da bAnk dUz wEll sInze dA bAr oBenEd Ub.");
    add_chat("Da bEzt voOd iz mAybE dA wIbs.");

    set_cchat_time(2);                /* Set combat speaking interval     */
    add_cchat("StOopid scUm.");
    
    set_act_time(6);                  /* Set action interval              */
    add_act("grunt happily");         /* Guess which guild she belongs to */
    add_act("munch");
    add_act("pick nose");
    add_act("flick grunt");
    add_act("flob");
    add_act("grshake all");
    add_act("knuckles");

    setuid();
    seteuid(getuid());

    set_alarm( 1.0, 0.0, load_grunts_soul );
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
}

public void
load_grunts_soul()
{
    add_cmdsoul( GUILD_SOUL );
    update_hooks();
    return;
}
