/*
    /doc/examples/mobiles/troll.c

    JnA 920115

    A sample monster

    Monsters are humanoid creatures that get humanoid attacks and
    hitlocations predefined. We need not bother to set these if we
    do not want to, it will be managed for us.

    This troll gives an example of how to use the sequence actions in
    combination with VBFC. It is used to wield and wear.

*/
inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/d/Terel/common/terel_defs.h"
#define PORDIR TOWNDIR + "mansion/porcia/"

#define WEP PORDIR + "ssword"
#define ARM PORDIR + "s_armour"
#define HAT PORDIR + "helmet"
#define SHOES PORDIR + "boots"

int frust_mode;

create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
	return;

    set_name("guard");
    set_race_name("human");
    set_adj("bored");
    set_long("He is very bored. However, he also looks very strong!!\n");

    /* Average stat:  
     */
     default_config_npc(50);
     set_stats(({90,70,70,100,100,100}));

    /* But we want it to have more hitpoints
     */
    set_hp(10000);
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_PARRY, 58);
    set_skill(SS_WEP_SWORD, 90);

    seq_new("do_things");
    seq_addfirst("do_things", ({"@@arm_me"}));

    set_chat_time(4);
    add_chat("Damn I'm so bored... like to play a NIM game?");
    add_chat("Type 'nim' to start a new NIM game.");
    add_chat("Each of us can remove any number of stones from one heap.");
    add_chat("Whoever removes the last stone at all wins the game.");

    set_alignment(0);
    frust_mode = 0;

}

void
frustrate() {
    frust_mode = 1;
    call_out("unfrustrate",8);
    tell_room(environment(this_object()),
     "The guard looks terribly frustrated and distracted he was beaten..\n");
}

void
unfrustrate() {
    frust_mode = 0;
    tell_room(environment(this_object()),
     "The guard seems to feel better now and looks at you carefully.\n");
}

int
getfrust() {
  return frust_mode;
}

arm_me()
{
   object wep, arm, hat, shoe, money;

    /* In VBFC's euid == 0, must fix cause we want to clone things
    */
    seteuid(getuid(this_object()));

    wep = clone_object(WEP);
    wep->move(this_object());
    command("wield sword");

    arm = clone_object(ARM);
    arm->move(this_object());
    command("wear armour");

    hat = clone_object(HAT);
    hat->move(this_object());
   command("wear helmet");

    shoe = clone_object(SHOES);
    shoe->move(this_object());
    command("wear boots");


}

