 
/* graveyard/npc/ghoul.c is cloned by graveyard/ingrave */
 
/* A Ghoul (humanoid) - one of Tulix's friends.                        */
/* Coded 29/1/1992 */
 
inherit "/std/monster";            /* For some reason, lots of monsters */
inherit "/std/act/action";         /* seem to have these statements.    */
inherit "/std/act/chat";           /* I guess mine had better have them */
#include "/d/Emerald/defs.h"
 
 
 
void
create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("ghoul");
    set_pname("ghouls");
    set_race_name("ghoul");
    set_short("disgusting ghoul");
    set_pshort("disgusting ghouls");
    set_adj("disgusting");
    set_long( "This is nasty creature indeed.  It looks at you "
        +"with a glint of malice in it's eyes.  It smells quite foul.  "
        +"I suggest that you think carefully before you attack......\n" );
 
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(CONT_I_WEIGHT,80000);
    add_prop(CONT_I_HEIGHT,222);
    add_prop(LIVE_I_NEVERKNOWN, 1 );
    add_prop(LIVE_I_UNDEAD,45);
 
    set_gender(2);  /* male=0, female=1, other=2 */
 
    /* stats -   STR  DEX  CON  INT  WIS  DIS  */
    set_stats(({  80,  70,  70,  40,  50, 70})); /* My, what fine stats. */
    set_hp(20400);                               /* Fully healed         */
    set_alignment(-200);
 
    /* Set unarmed attacks and armour classes. */
    set_all_hitloc_unarmed(40);
    set_all_attack_unarmed(20,30);
 
    /* We dont want him dying too quick now, do we? */
    add_armour( GRAVEYARD_DIR + "arm/ghoul_chain.c");
    add_weapon( GRAVEYARD_DIR + "wep/aghoul.c");
 
    set_aggressive(0);      /* aggr OR attchc */
 
    /* Set the all important skills. */
 
    set_skill(SS_WEP_AXE,80);
 
    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_BLIND_COMBAT,90);
    set_skill(SS_PARRY,70);
    set_skill(SS_DEFENCE,75);
 
    set_skill(SS_AWARENESS,50);
 
    add_cchat("You will die.");   /* The usual combat talk         */
 
}
 
