/*
 * Drunk, modified to support new introduction system by Alaron August 5, '96
 */

inherit "/std/monster";

#include "/d/Emerald/defs.h"
#include "/d/Emerald/lib/prestige.h"

#define	NAMES	({ "rnor", "jarret", "noror" })
#define	RACE	({ "human", "dwarf", "elf", "goblin", "hobbit" })
#define	ADJ	({ "drunk", "blitzed", "tanked" })

void do_random(string who);
void give_back(object *what);
void drink_up(object ob);

void
create_monster()
{
    int    ran;

    if (!IS_CLONE)
	return;

    ran=random(sizeof(NAMES));
    set_name(NAMES[ran]);
    set_living_name("_" + NAMES[ran] + "_");

    add_name("drunk");

    ran=random(sizeof(RACE));
    set_race_name(RACE[ran]);

    add_adj("slightly");
    ran=random(sizeof(ADJ));
    add_adj(ADJ[ran]);

    set_long("He looks like he've had quite a few drinks. He "+
	     "wouldn't mind some more, however.\n");
  set_alignment(150-random(301));

    add_prop(OBJ_I_WEIGHT, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 90000);
    add_prop(OBJ_I_VOLUME, 48000);
    add_prop(CONT_I_MAX_WEIGHT, 80000);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_gender(0);

    set_stats( ({ 30+random(30), 30+random(30), 30+random(30),
		   20+random(20), 20+random(20), 30+random(30) }) );

    set_act_time(5);
    add_act("giggle");
    add_act( ({ "say I need another drink!", "buy beer", "drink beer", "burp" }) );
    add_act("wink all");
    add_act("say Would you care to buy me a drink?");


}

public
void
add_introduced(string who)
{
    object obwho = find_player(who);

    if (obwho &&
	!obwho->query_met(this_object()))
        set_alarm(itof(random(5)+1),0.0,&do_random(who));
}

void
do_random(string who)
{
    int ran;
   
    ran = random(3);
    if (ran == 0)
	command("introduce myself to " + who);
    else if (ran == 1)
	command("bow " + who);
    else if (ran == 2)
	command("say Nice to meet you, " + capitalize(who) + ".");
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (from && living(from))
	if (!ob->query_alco_amount())
      set_alarm(2.0, 0.0, &give_back(({ ob, from })));
	else
      set_alarm(2.0, 0.0, &drink_up(ob));
}

void
give_back(object *what)
{
    if (!what[0])
	return;

    command("say What would I want with this??");
    if (what[1])
	command("give " + what[0]->query_name() + " to " +
		what[1]->query_real_name());
    command("drop " + what[0]->query_name());
    if (present(what[0]))
	what[0]->remove_object();
}

void
drink_up(object ob)
{
    if (!ob)
	return;

    command("say Cheers!");
    command("drink " + ob->query_name());
    if (ob)
	ob->remove_object();
}
