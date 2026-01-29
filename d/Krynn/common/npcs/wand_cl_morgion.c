/*
 * Wandering Cleric of Morgion
 * He spreads disease about, coded by Aridor and Teth, Feb 21, 1997
 * The 'disease' is located in /d/Krynn/common/poisons/sick.c
 */

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h";
#include <money.h>
#include <filter_funs.h>
#define  SICKNESS  KRPOISON + "sick"

inherit M_FILE

inherit "/std/act/domove";
inherit "/std/act/action";

public void
create_krynn_monster()
{
    int i;

    set_name("cleric of morgion");
    set_living_name("aridors_evil_idea");
    add_name("wandering_cleric_morgion");
    set_race_name("human");
    set_short("cloaked lurking human");
    set_pshort("cloaked lurking humans");
    set_adj("lurking");
    add_adj("cloaked");
    add_name("cleric");

    set_long("This lurking human is obviously someone who does not " +
	     "wish to be noticed. He is cloaked in rags, perhaps to " +
	     "not to draw attention to himself. He also wears an amulet " +
	     "around his neck.\n");

    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(CONT_I_HEIGHT, 180);
    add_prop(CONT_I_WEIGHT, 55000);
    add_prop(LIVE_I_QUICKNESS, 200);

    for(i=0; i<6; i++)
      set_base_stat(i, 50 + random(100));

    set_skill(SS_DEFENCE,        30);
    set_skill(SS_WEP_CLUB,       50);
    set_skill(SS_BLIND_COMBAT,   50);
    set_skill(SS_AWARENESS,      50);
    NEVERKNOWN;

    set_alarm(1.0,0.0,"arm_me");
    MONEY_MAKE_SC(random(60)+60)->move(TO);
    MONEY_MAKE_PC(random(3))->move(TO);

    set_alignment(-900);
    set_knight_prestige(400);

    set_default_answer("For some reason, you are ignored.\n");
    add_ask(" [about] 'morgion'","say You are not worthy to say that " +
	    "name!",1);
    add_ask(" [about] 'takhisis'","say Takhisis has grand plans, " +
	    "and I'm not positive she will fail this time.",1);
    add_ask(" [about] 'chemosh'","say Bah! A fool!",1);
    add_ask(" [about] 'mishakal'","say The Healing Hand is nowhere to " +
	    "be seen! She has abandoned the people, and that is fine by me.",1);
    add_ask(" [about] 'disease' / 'decay'","say Disease and decay please " +
	    "me, and please my master.",1);
    add_ask(" [about] 'master'","say I won't tell the likes of you.",1);
    add_ask(" [about] 'task' / 'help'","say I have a task for " +
	    "you indeed! I wish to see you wither and decay before my " +
	    "eyes!",1);
    add_ask(" [about] 'cleric' / 'priest'","say What business " +
	    "is that of yours?",1);
    
    set_act_time(1);
    add_act("emote skulks about.");
    add_act(({"emote walks beside you and stumbles.","emote catches himself " +
		"by grabbing on your arm, but quickly lets go afterwards.@@infect@@",
		"emote mumbles something.@@infect@@","emote walks away."}));
    add_act("emote stares at you for a moment.@@infect@@");
    add_act("emote lets out a soft, sly chuckle.@@infect@@");
    add_act("emote slumps his posture slightly.");
    add_act("emote glances at the medallion about his neck.@@infect@@");
    add_act("emote attempts to hide within his ragged cloak.");

    set_cact_time(1);
    add_cact("say Your death would please me.@@infect@@");
    add_cact("emote glares at you with stony silence.@@infect@@");
    add_cact("say May you always suffer.@@infect@@");
    add_cact("say Chemosh will welcome you.@@infect@@");
    add_cact("emote touches you with his bony hand.@@infect@@");

    seteuid(getuid());
}

public void
arm_me()
{
    clone_object(KRWEAPON + "wcm_mace")->move(TO);
    clone_object(KRARMOUR + "wcm_amulet")->move(TO);
    clone_object(KRARMOUR + "wcm_rags")->move(TO);
    clone_object(KRARMOUR + "wcm_boots")->move(TO);
    command("wear all");
    command("wield all");
}

#if 0
We call the same function in SICKNESS so there's just one
version of the function around at any time
void
catch_sickness(object who)
{
    object ob;

    if (present("nasty_sickness",who))
      return;
    
    /* Newbies are exempt :) */
    if (who->query_average_stat() < 30)
      return;
    
    /* 1/2 of the time it won't get passed on. */
    if (random(2))
      return;
    
    ob = clone_object(SICKNESS);
    ob->move(who);
    ob->incubate_sickness();
    
    find_living("aridor")->catch_msg("INFECTED: " + who->query_name() + "\n");
    log_file("sickness",ctime(time())[4..15] + " " + who->query_name() + 
	     " infected by Cleric of Morgion\n");
}
#endif

string
infect()
{
    object *ob;
    if (query_attack())
      (SICKNESS)->catch_sickness(query_attack());
    else
    {
        ob = FILTER_LIVE(all_inventory(E(TO))) - ({TO});
        if (ob && sizeof(ob))
	  (SICKNESS)->catch_sickness(ob[random(sizeof(ob))]);
    }
    return "";
}

void
init_living()
{
    if (!random(3))
      (SICKNESS)->catch_sickness(TP);
}

void
immune_to(object ob)
{
    ob->remove_object();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    if (ob->id("nasty_sickness"))
      set_alarm(1.0, 0.0, &immune_to(ob));
}
