// file name:		~Avenir/common/dark/mon/ghost.c
// creator(s):		Denis
// revision history:	Jan 96: Added a special name, to aid impquest reset.
//				-=Denis
//			Apr 96: Added use of the statserver to log
//				the ghost deaths.
//				-=Denis
// purpose:
//   It is 'something' the ghost transforms into upon being attacked.
// note:
//   wielding:
//     ~Avenir/common/dark/obj/dblpole.c
//   wearing:
//     ~Avenir/common/dark/obj/dcloak.c
// bug(s):
// to-do:
 
# include "/d/Avenir/common/dark/dark.h"
# include "../l3/l3_defs.h"
# include "/d/Avenir/smis/sys/statserv.h"

inherit "/d/Avenir/inherit/monster";
 
int alarm_id;
object cloak;
 
create_monster()
{
    set_name("elf");
    add_name("ghost");
    add_name(L3_GHOST);
 
    set_adj( "ghostly" );
    set_race_name("elf");
    set_short("ghostly elf");
    set_long(
"The ghost has transformed into a more solid form to protect his post.\n"+
"He wouldn't look like this unless someone had tried to remove him\n"+
"from being a guardian of the altar.\n");
 
    set_gender(G_MALE);
    set_stats( ({100,100,100,100,100,120}) );
    set_knight_prestige(-2000);
    set_alignment(700);
    set_hp(10000);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 85);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_BLIND_COMBAT, 80);
 
    add_prop(CONT_I_WEIGHT, 75 * 1000);
    add_prop(CONT_I_HEIGHT, 200);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(LIVE_I_NO_CORPSE,1);
 
    set_default_answer("say Save your questions for me in my other form.", 1);
    alarm_id=set_alarm(200.0,200.0,"try_ghost_again");
}
 
/*-----[ We need some sort of equipment              ]-----*/
arm()
{
    clone_object(OBJ+"dblpole")->move(TO);
    cloak=clone_object(OBJ+"dcloak");
    cloak->move(TO);
    cloak->add_cloak_ac();
    command("wield all");
    command("wear all");
}
 
/*-----[ Someone killed us?                          ]-----*/
/*-----[ Ahh... anyway they cannot kill our image... ]-----*/
do_die(object killer)
{
    cloak->remove_cloak_ac();
    tell_room(environment(TO),
              "The "+short()+ " loses his solid form.\n");
    environment(TO)->ghost_died();

    STATSERV_LOG_EVENT("impquest", "Ghost died");

    ::do_die(killer);
}
 
/*-----[ Test if we are figting someone and          ]-----*/
/*-----[ if not -> transform back into               ]-----*/
/*-----[ ghost, the guardian of the altar.           ]-----*/
try_ghost_again()
{
    if(!query_attack())
    {
        remove_alarm(alarm_id);
        tell_room(environment(TO),
                  "The "+short()+ " loses his solid form.\n");
        environment(TO)->ghost_returns();
        remove_object();
    }
}
