/* temple/npc/monk.c is cloned by temple/court_e.c
    and monastery.c */
inherit "/std/monster";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/lib/prestige.h"
#include "/d/Emerald/lib/make_money.h"
 
void
create_monster()
{
    set_name("monk");
    set_adj("silent");
    set_race_name("human");
    set_short("silent monk");
    set_long("He looks like he is quite dedicated. He also "+
      "does not look like the talkative type.\n");
 
    set_base_stat(SS_STR, 20);
    set_base_stat(SS_DEX, 30);
    set_base_stat(SS_CON, 25);
    set_base_stat(SS_INT, 40);
    set_base_stat(SS_WIS, 60);
    set_base_stat(SS_DIS, 75);
 
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_HERBALISM, 20);
    set_skill(SS_FORM_DIVINATION, 25);
    set_skill(SS_ELEMENT_LIFE, 40);
    set_skill(SS_APPR_MON, 70);
    set_skill(SS_AWARENESS, 45);
 
    set_hp(10000);
 
    add_prop(OBJ_I_WEIGHT, 19000);
    add_prop(CONT_I_MAX_WEIGHT, 180000);
    add_prop(OBJ_I_VOLUME, 89000);
    add_prop(CONT_I_MAX_VOLUME, 100000);
    set_alignment(150-random(200));
}
 
void arm_me()
{
  clone_object(TEMPLE_DIR + "arm/m_robe")->move(TO,1);
  clone_object(TEMPLE_DIR + "obj/h_book")->move(TO,1);
  MAKE_MONEY;
  command("wear all");
}
 
/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    object *arr;
    int i;
 
    ::attacked_by(ob);
 
    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(this_object(), ob);
}
 
/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *                attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
        return;
 
    if (random(10))
        set_alarm(1.0,0.0,"help_friend",attacker);
}
 
/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
 command("say Do you need help, my friend?");
        command("kill " + lower_case(ob->query_real_name()));
    }
}
 
