/*
 * /d/Gondor/common/quests/smuggler/arindel.c
 * 
 * The dealer to whom the herb should be delivered in Minas Tirith 
 *
 * Revision:
 * Updated code: May 30. 1996 by Boron
 * Updated code: Feb 20, 1997 by Olorin
 */
#pragma strict_types

inherit "/d/Gondor/std/monster.c";
inherit "/d/Gondor/common/lib/logkill.c";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

public void    do_bit_test(object pl);

public void
create_gondor_monster()
{
    set_name("arindel");
    add_name(({"darkhand", "arindel darkhand","Arindel Darkhand","lieutenant","shade"}));
    set_race_name("human");
    set_title("Darkhand, the Lieutenant of the Shades");
    set_living_name("arindel");
    set_adj(({"well-dressed","concerned"}));
    set_long("This man is quite well-dressed, and looks to be in good condition,\n"+
	     "but he looks quite concerned about something.\n");
    set_stats(({ 35, 37, 40, 55, 39, 24 }));
    add_prop(CONT_I_WEIGHT,78000);
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    add_prop(CONT_I_HEIGHT,184);
    set_skill(SS_WEP_KNIFE,45);
    set_skill(SS_DEFENCE,45);
    set_skill(SS_PARRY,45);
    set_skill(SS_BLIND_COMBAT,45);
    set_skill(SS_AWARENESS,45);
    set_alignment(-250 - random(150));
    set_act_time(7);
    add_act("say Business is bad here in Minas Tirith now because of all the guards.");
    add_act("say I wish someone could go and help Fredor to bring some herbs here.");
    add_act("twiddle");
    add_act("sigh");
    add_act("say Don't hang around too long, ok?");
    add_cact("say Hey, stop it! What have I ever done to hurt you??");
    add_cact("shout Help! I'm innocent!");
    add_cact("scream");
    add_cact("say I didn't do it! Nobody saw me! Can't prove anything!");
    add_cact("say Leave me alone! I'm a peaceful man!");

    set_equipment( ({ WEP_DIR + "dagger", 
		      MINAS_DIR + "shades/priv_key", }) );
}

int
greet(object obj)
{
    command("bow "+obj->query_real_name());
    command("introduce myself to "+obj->query_real_name());
    return 1;
}

public void
init_living() 
{
    ::init_living();
    
    if (!TP->query_npc())
	set_alarm(4.0, 0.0, &greet(TP));
}

public void
not_correct_item(object *things)
{
    command("shout What have you done with the green leaf??");
    command("shout This is not what I want!");
    command("steam");
    command("say Get it back right away, or you'll be in trouble!");
    command("give "+things[1]->query_name()+" to "+things[0]->query_real_name());
    command("spit");
}

public void
not_carrier(object from)
{
    command("say Hmm...you are the courier? Well, ok, thanks for your help!");
    command("unlock wooden door with key");
    command("open wooden door");
    command("west");
    command("close wooden door");
}

public void
not_quest_herb(object from)
{
    command("say Ah...a herb! Nice of you, really nice.");
    command("think");
    do_bit_test(from);
}

public void
friendly(object from)
{
    command("say Thanks, "+from->query_race_name()+", but I don't think I need that.");
    command("say Why don't you act as a courier for me,");
    command("say and bring me a herb from Fredor?");
    command("say He can be found down in the Harlond.");
    command("smile");
}

public void
repulse()
{
    command("say Please leave at once! I'm too busy to talk to you!");
}

public void
do_thank(object pl) 
{
    string hname = pl->query_real_name();
    if (environment(pl) != environment(TO)) 
	return 0;
    set_act_time(1);
    LOG_QUEST(pl, 0, "HERB SMUGGLER - ONCE MORE");
    pl->remove_prop("_gondor_quest_is_smuggler");
    seq_clear("do_things");
    command("say Ah!");
    seq_addfirst("do_things",({"smile "+hname,"whisper "+hname+
     " I am most grateful that you are helping us once more!","whisper "+hname+
     " Our organization will certainly remember your deeds.","smile",
     "whisper "+hname+" Leave now, but remember:","whisper "+hname+
     " Power to the Shades!","grin","wave","@@go_west"}));
}

public void
do_add_exp(object pl)
{
    string  hname = pl->query_real_name();

    seteuid(getuid(TO));
    pl->set_bit(GONDOR_GROUP, HERB_SMUGGLER_BIT);
    if (pl->query_prop("_gondor_quest_smuggler_runaway")) 
    {
	command("say Too bad you were discovered by the cityguards.");
	pl->add_exp_quest(HERB_SMUGGLER_EXP/2);
	LOG_QUEST(pl, HERB_SMUGGLER_EXP/2, "HERB SMUGGLER - RUNAWAY");
	command("sigh");
	command("say We are grateful that you tried to help us with this.");
	command("say But it was stupid to let the guards discover you.");
	command("say Now it will be even more dangerous for us in the future!");
	command("say Go now, and don't come back here.");
	command("say We won't need your help anymore!");
    }
    else 
    {
	pl->add_exp_quest(HERB_SMUGGLER_EXP);
	LOG_QUEST(pl, HERB_SMUGGLER_EXP, "HERB SMUGGLER");
	command("smile "+hname);
	command("say I am most thankful that you helped us with this!");
	command("thank "+hname);
	MONEY_MAKE_GC(2)->move(TO);
	command("give 2 gold coins to " + hname);
	command("whisper "+hname+" I will personally put in a good word " +
		"for you in the Shade-council!");
	command("smile");
	command("say Leave now, but remember:");
	command("whisper "+hname+" Power to the Shades!");
	command("grin");
    }
    pl->adjust_alignment(-200);
    tell_object(pl,"You feel more experienced.\n");
    pl->remove_prop("_gondor_quest_smuggler_runaway");
    pl->remove_prop("_gondor_quest_is_smuggler");
}

public void
go_east()
{
    command("unlock wooden door with key");
    command("open wooden door");
    command("east");
    command("lock wooden door with key");
    command("close wooden door");
}

public void
go_west()
{
    command("unlock wooden door with key");
    command("unlock door with key");
    command("open wooden door");
    command("west");
    command("close wooden door");
    command("lock wooden door with key");
    command("drop leaf");
    set_alarm(200.0, 0.0, go_east);
}

public void
do_reward(object pl)
{
    string hname = pl->query_real_name();

    if (!present(pl,environment(TO))) 
	return 0;
    set_act_time(1);
    seq_clear("do_things");
    do_add_exp(pl);
    command("wave");
    go_west();
}

public void
do_bit_test(object pl)
{
    if (pl->test_bit("Gondor",GONDOR_GROUP, HERB_SMUGGLER_BIT)) 
	do_thank(pl);
    else 
	do_reward(pl);
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);  

    if (!objectp(from))
	return;
    if (obj->is_quest_herb() && !from->query_prop("_gondor_quest_is_smuggler"))
	set_alarm(2.0, 0.0, &not_carrier(from));
    else if (!obj->is_quest_herb() && from->query_prop("_gondor_quest_is_smuggler"))
	set_alarm(2.0, 0.0, &not_correct_item( ({from,obj}) ) );
    else if (!obj->is_quest_herb() && !from->query_prop("_gondor_quest_is_smuggler"))
	set_alarm(2.0, 0.0, &friendly(from) );
    else if (obj->is_quest_herb())
	set_alarm(2.0, 0.0, &do_bit_test(from) );
}

public int query_knight_prestige() { return 400; }
