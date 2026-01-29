// file name:     overseer.c
// creator(s):    Lilith   09/26/97
// purpose:       Flag down sedan chairs
/*
 * Revisions:
 * 	Lucius, Sep 2017: Changed the 'summon' method a bit, shorten delay
 * 	                  and summon chairs for the entire team.
 * 	                  Created a new base file to reduce duplication.
 */
#pragma strict_types

inherit "/d/Avenir/inherit/sybarite";
inherit "/d/Avenir/inherit/helper";
inherit "/d/Avenir/inherit/death_crier";

#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/paths.h"
#include "/d/Avenir/include/relation.h"

#include <money.h>
#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <stdproperties.h>

public string *Sadj1 = ({
    "pleasant","smiling","eager","sincere","composed",
    "enthusiastic", "kindly", "helpful"
});
public string *Sadj2 = ({ "overseer"});
public string *Seyes = ({
    "dark-brown","pale blue","dark green","leaf green",
    "gray","thrilling black","serene blue", "sparkling black",
    "blue-black","coal-black","steel-gray","gray-green"
});
public string *Shair = ({
    "gray-streaked","caramel-coloured","ebony black","fiery-red",
    "silky dark","silky black","curly dark","unusual milk-white",
    "wavy brown","mahogany brown","light brown","chestnut brown",
    "blue-black","deep auburn","chocolate brown"
});

public int alarm_id, summoning;
public string eyes, hair, adj1, adj2, loc_str, chair_path;


public string query_eyes(void)		{ return eyes; }
public string query_hair(void)		{ return hair; }
public void set_eyes(string str)	{ eyes = str;  }
public void set_hair(string str)	{ hair = str;  }


static string
my_long(void)
{
    string poss = query_possessive(), pro = query_pronoun();

    return capitalize(pro) +" is "+
	LANG_ADDART(implode(query_adjs(), " ")) +" "+
	query_race_name()+".\n"+
	capitalize(pro) +" has the grace and dignity of bearing "+
	"characteristic of shadow-elves. "+ capitalize(poss) +
	" skin is so pale and translucent it is tinted blue in "+
	"some places by "+ poss +" veins.\n"+
	capitalize(pro) +" appears to be an overseer, charged "+
	"with finding sedan chairs for people "+ loc_str +".\n"+
	capitalize(poss) +" "+ query_hair() +" hair is cropped "+
	"very short.\n"+ capitalize(pro) +" has "+ query_eyes() +
	" eyes.\n";
}

/*
 * set_morph sets the various attributes of the
 * npc, making it unique 10 different ways.
 */
static void
set_morph(void)
{
    set_race_name("half-elf");
    set_gender(random(2));

    set_adj(one_of_list(Sadj1));
    add_adj(one_of_list(Sadj2));
    set_eyes(one_of_list(Seyes));
    set_hair(one_of_list(Shair));
}

/* Create the npc */
public void
create_monster(void)
{
    /* if I'm not a clone, do not proceed */
    if (!IS_CLONE)
	return;

    /* Make sure sybarite stuff is initialized */
    ::create_sybarite();

    /* You're all individuals! */
    set_morph();

    set_name("overseer");
    set_long(my_long);
    add_name(({"foreman", "boss", "supervisor"}));
    set_alignment(0);

    MAKE_SYBARITE;
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(OBJ_M_NO_MAGIC, "The Idrys protect those who serve.\n");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_leftover("/d/Avenir/inherit/leftover", "heart",1, "", 0,0);
    add_leftover("/d/Avenir/inherit/leftover", "intestine",1, "", 0,0);

    set_skill(SS_DEFENCE, random(20) + 60);
    set_skill(SS_2H_COMBAT, random(20) + 60);
    set_skill(SS_WEP_SWORD, random(20) + 60);
    set_skill(SS_AWARENESS, random(40)+ 60);
    set_skill(SS_WEP_KNIFE, random(20) + 70);
    set_skill(SS_BLIND_COMBAT, random(20)+ 40);
    set_all_attack_unarmed(30, 30);
    set_all_hitloc_unarmed(15);
    set_appearance_offset(-10); // always good-looking

    default_config_npc(random(60) + 100);

    set_act_time(1);
    add_act("say If you need a chair, just ask.");
    add_act("say Can I help you?");
    add_act("emote looks at you from the corner of "+
	query_possessive() + " eyes.");

    set_cact_time(7);
    add_cact("glare mercilessly enemy");
    add_cact("say Plalgus will curse you for this.");
    add_cact("say Flee from me and I will not follow. You are not "+
	"a foe worthy of giving chase.");
    add_cact("say From whence thou came, so shall I return you.");
    add_cact("say I will feed your corpse to a troloby!");

    set_default_answer("@@what_me@@");
    add_ask(({"sigil", "what sigil", "where do I get a sigil"}),
	"Sigils are provided to those who are members of a House, "+
	"or who are invited into the City on House business.", 1);

    add_ask(({"help", "ride", "chair", "sedan", "sedan chair"}),
	"@@help_ask@@");

    /* So we help other sybarite npcs in combat */
    set_helper_friends( ({ "defender", "dej" }) );
}

/*
 * equip_me is called in the npc when it is cloned by the
 * placer module.
 */
public void
equip_me(void)
{
    string *arr = ({ COM +"obj/knife", BAZAAR +"Obj/wield/cane" });

    MONEY_MAKE_SC(random(10))->move(TO);
    MONEY_MAKE_PC(random(3))->move(TO);

    if (query_gender() == G_MALE)
        arr += ({ BAZAAR +"Obj/worn/codpiece" });
    else
        arr += ({ BAZAAR +"Obj/worn/jpants" });

    equip(arr);
}

private void
summon(int num)
{
    int count;

    summoning = 0;

    while(--num >= 0)
    {
	object steed = clone_object(chair_path);
	steed->move_living("M", environment(TO));
	count++;
    }

    if (count == 1)
    {
	tell_room(environment(TO), "A bondservant pulling a sedan "+
	    "chair runs up to the overseer and smiles helpfully.\n");
    }
    else
    {
	tell_room(environment(TO), capitalize(LANG_NUM2WORD(count)) +
	    " bondservants pulling sedan chairs run up to the "+
	    "overseer and smile helpfully.\n");
    }
}

public string
help_ask(void)
{
    if (!CAN_SEE(TO, TP))
    {
        command("emote looks around suspiciously");
        command("say I must be hearing things.");
        return "";
    }

    if (summoning)
    {
	command("say Give me a few moments, I'm already waiting "+
	    "on some sedans to arrive.");
	return "";
    }

    object *team = FILTER_PRESENT(TP->query_team_others());
    int num = sizeof(team);

    command("say Of course, let me get you "+
	(num ? "and your teammates " : "") + "a chair.");
    command("smile help");
    command("whistle loud");

    summoning = set_alarm(3.0, 0.0, &summon(1 + num));
    return "";
}

public string
what_me(void)
{
    if (!CAN_SEE(TO, TP))
    {
        command("emote looks angrily about.");
        return "";
    }

    switch(random(4))
    {
        case 0:
            command("say I can only help you find a sedan chair!");
            break;
        case 1:
            command("say You are not permitted to ask that question.");
            break;
        case 2:
            command("smile nervous");
            break;
        case 3:
            command("say I'm nobody. Why are you asking me questions?");
            break;
    }
    return "";
}

public void
check_meet(object tp)
{
    alarm_id = 0;

    if (!present(tp, environment(TO)))
	return;

    if (IS_SYBARITE(tp))
        command("say to "+ tp->query_real_name() +" Good day.");
    else if (random(2))
	command("bow to "+ tp->query_real_name());
}

public void
init_living(void)
{
    ::init_living();

    if (!alarm_id && interactive(TP) && CAN_SEE(TO, TP))
	alarm_id = set_alarm(2.0, 0.0, &check_meet(TP));
}

public string
query_exp_title(void)
{
    return "sybarite";
}

public int
special_attack(object victim)
{
    switch(random(10))
    {
        case 2: command("heal");
        case 5: command("skick");
            return 1;
        case 6: command("skick");
            return 1;
        case 9: command("cure");
            return 0;
    }
    return 0;
}
