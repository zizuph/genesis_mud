 
/* A Wraith (humanoid) - one of Tulix's friends.                        */
/* Coded 26/1/1992 */
 
inherit "/std/monster";            /* For some reason, lots of monsters */
inherit "/std/act/action";         /* seem to have these statements.    */
inherit "/std/act/chat";           /* I guess mine had better have them */
#include "/d/Emerald/defs.h"
 
 
void
create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("wraith");
    set_pname("wraiths");
    set_race_name("wraith");
    set_short("ghostly wraith");
    set_pshort("ghostly wraiths");
    set_adj("ghostly");
    set_long( "  You don't like the look of this!  "
        +"It's a ghost like apparition of someone.....or rather something!  "
        +"This twisted and evil soul looks just about ready to kill you.  "
        +"If I were you I wouldn't stick around too long. you don't "
        +"really want to end up as one of these, do you?  "
        +"The wraith seems to stare right into your soul.\n" );
 
    add_prop(CONT_I_WEIGHT, 65000);
    add_prop(CONT_I_HEIGHT, 1800);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD,20);
 
    set_gender(2);  /* male=0, female=1, other=2 */
 
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_alignment(-30);
 
    set_default_answer("Leave while you can!\n");  /* A polite answer. */
    /* stats -   STR  DEX  CON  INT  WIS  DIS  */
    set_stats(({  40,  40,  35,  10,  10,  50})); /* My, what fine stats. */
    set_hp(10000);                                /* Fully healed         */
 
    /* Set unarmed attacks and armour classes. */
    set_all_hitloc_unarmed(10);
    set_all_attack_unarmed(10,10);
 
 
    set_attack_chance(8);
 
    /* Set the all important skills.                                      */
    set_skill(SS_WEP_SWORD,40);
 
    set_skill(SS_UNARM_COMBAT,10);
    set_skill(SS_BLIND_COMBAT,40);
    set_skill(SS_PARRY,40);
    set_skill(SS_DEFENCE,30);
 
    set_chat_time(10);                   /* Set speaking interval         */
    add_chat("You will die soon.  ");
 
    set_cchat_time(3);            /* Set combat speaking interval  */
    add_cchat("You will die sooner than I thought.\n");
 
    set_act_time(10);               /* Set action interval           */
    add_act("grin");                /* A few courteous actions       */
    add_act("shiver");
 
    seq_new("do_things");
    seq_addfirst("do_things","@@arm_me");
}
 
arm_me()
{
    object wep;
 
    seteuid(getuid(this_object()));
 
    wep=clone_object( GRAVEYARD_DIR + "wep/swraith");
    wep->move(this_object());
    command("wield all");
}
