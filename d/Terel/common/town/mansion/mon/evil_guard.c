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
#include <money.h>

#define WEP "/d/Terel/common/weapon/dagger"


create_monster()
{
    /* We ignore the master object 
     */
    if (!IS_CLONE) 
	return;
   set_name("guard");
   set_living_name("meltock");
   set_race_name("human");
   set_short("evil guard");
   set_adj("evil");
   set_long("He is just a plain old human guarding an exit.\n" +
            "He however, does stink of evil.  This is the first " +
            "time you have\never smelled evil.\n");

    /* Average stat: 5 
     */
     default_config_npc(50);

    /* But we want it to have more hitpoints
     */
    set_hp(5000);
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_PARRY, 48);
   set_skill(SS_WEP_KNIFE, 40);

    seq_new("do_things");
    seq_addfirst("do_things", ({"@@arm_me"}));

    set_chat_time(1);
   add_chat("HA!  You should have seen that old man try to stop " +
            "us from taking\nthat girl.  Funniest thing I ever did see.\n");
   add_chat("Hey Gered, what are we going to do with the body?\n");
   add_chat("Are you a virgin?\n");

   set_alignment(-250);

}

arm_me()
{
   object wep, arm, hat, shoe, money;

    /* In VBFC's euid == 0, must fix cause we want to clone things
    */
    seteuid(getuid(this_object()));

    wep = clone_object(WEP);
    wep->move(this_object());
   command("wield dagger");


   money=MONEY_MAKE_SC(3);
   money->move(this_object());

}

/*
 * Find some player somewhere and go there
 */
find_someone(name)
{
    object ob;

    ob = find_player(name);

    if (!ob)
	return 0;

    move_living("X",environment(ob));
    return 0;
}
