inherit "/std/monster";

#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#define	NAMES	({ "bill", "bob", "pete" })
#define	RACE	({ "human", "dwarf", "elf", "goblin", "hobbit" })
#define	ADJ	({ "drunk", "blitzed", "tanked" })

void return_introduce(string who);
void give_back(object *what);
void drink_up(object ob);

string *people = ({ });

void
create_monster()
{
    object coins;
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

    set_long("He looks like he've had quite a few drinks. He wouldn't mind " +
             "some more, however.\n");

    add_prop(CONT_I_WEIGHT, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 90000);
    add_prop(CONT_I_VOLUME, 48000);
    add_prop(CONT_I_MAX_WEIGHT, 80000);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_gender(0);

    set_stats( ({ 15+random(85), 12+random(88), 24+random(76),
		   7+random(93), 18+random(82), 10+random(90) }) );

    heal_hp(10000);

    set_act_time(5);
    add_act("giggle");
    add_act( ({ "say I need another drink!", "buy beer", "drink beer", "burp" }) );
    add_act("wink all");
    add_act("say Would you care to buy me a drink?");

    trig_new("%w 'introduces' %s", "react_introduce");

    seteuid(getuid());

    coins=clone_object("/std/coins");
    coins->set_coin_type(MONEY_TYPES[1]);
    coins->set_heap_size(40);
    coins->move(this_object());
}

int
react_introduce(string by, string who)
{
    string *apa;

    by = explode(who, " ")[1];
    apa = explode(by, "\n");
    if(apa[0] == "as:")
    {
        if(member_array(apa[1], people) < 0)
        {
            people += ({apa[1]});
            who = lower_case(apa[1]);
            set_alarm(itof(random(5) + 1), 0.0, &return_introduce(who));
            return 1;
        }
        return 0;
    }
    return 0;
}

void
return_introduce(string who)
{
    object obj;
    int    ran;
    
    if (obj = present(who, environment())) {
	if (!interactive(obj))
	    return;
	ran = random(3);
	if (ran == 0)
	    command("introduce myself to " + who);
	else if (ran == 1)
	    command("bow " + who);
	else if (ran == 2)
	    command("say Nice to meet you, " + capitalize(who) + ".");
    }
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
