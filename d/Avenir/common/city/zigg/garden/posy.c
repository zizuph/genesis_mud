/*
 * Revisions:
 * 	Lucius, Jun 2017: Also made 'holdable'.
 *
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/holdable_item";

#include "zigg.h"
#include "flowers.h"

#include <macros.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <stdproperties.h>


private static mixed *unique;
private static int allow_move;


public void
remove_object(void)
{
    all_inventory(TO)->remove_object();
    ::remove_object();
}
/*
 * Because this item will be forcibly emptied during quitting,
 * we need this check to prevent dropping an empty posy/bouquet.
 */
private int
check_drop(void)	{ return !sizeof(all_inventory()); }

private int
cont_prop(void)		{ return allow_move; }

private int
cont_closed(void)	{ return !allow_move; }

private string
my_long(void)
{
    return "This is a posy made up of "+
	COMPOSITE_DEAD(all_inventory(TO)) +".\n";
}

public void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name(({"posy","zigg::posy"}));
    set_short("posy of flowers");
    set_pshort("posies of flowers");
    set_long(my_long);
    set_slots(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 40);
    add_prop(OBJ_I_NO_SELL, 1);
    add_prop(OBJ_M_NO_DROP, check_drop);

    /* Fake a container. */
    add_prop(CONT_I_IN, cont_prop);
    add_prop(CONT_I_CLOSED, cont_closed);
    add_prop(CONT_I_MAX_WEIGHT, 99999);
}

/* Fake a container. */
public int
volume_left(void)	{ return 99999; }

public void
moving(void)		{ allow_move = 1; }

public object *
query_flowers(void)
{
    return all_inventory(TO);
}

public void
update_flowers(void)
{
    object env = environment(TO);
    int total = sizeof(all_inventory(TO));

    if (total >= BOUQ_NUM)
    {
	object ob;

	if (query_interactive(env))
	{
	    env->catch_tell("Your "+ short() +" has become too large "+
		"for a posy so you rearrange it into a bouquet.\n");
	}

	ob = clone_object(BOUQUET);

	if (ob->move(env))
	    ob->move(env, 1);

	map(all_inventory(TO), &->move(ob, 1));
	ob->update_flowers();

	set_alarm(0.0, 0.0, remove_object);
    }
    else if (total < POSY_NUM)
    {
	if (query_interactive(env))
	{
	    env->catch_tell("Your "+ short() +" comes apart from not "+
		"having enough flowers in it.\n");
	}

	map(all_inventory(TO), &->move(env));
	set_alarm(0.0, 0.0, remove_object);
    }
    else
    {
	unique = unique_array(all_inventory(TO), &->query_flower());
	total  = sizeof(unique);
	remove_adj(query_adjs());

	if (total != 1)
	{
	    set_short("posy of flowers");
	    set_pshort("posies of flowers");
	}
	else
	{
	    string str;

	    env = unique[0][0];
	    str = env->query_pname();

	    unique = unique_array(all_inventory(TO), &->query_colour());
	    total  = sizeof(unique);

	    if (total != 1)
	    {
		add_adj(str);
		set_short("posy of "+ str);
		set_pshort("posies of "+ str);
	    }
	    else
	    {
		string col;

		col = env->query_colour();
		add_adj(str); add_adj(col);

		set_short("posy of "+ col +" "+ str);
		set_pshort("posies of "+ col +" "+ str);
	    }
	}

	total = 0;

	foreach(object ob : all_inventory(TO))
	    total += ob->query_prop(OBJ_I_VALUE);

	add_prop(OBJ_I_VALUE, total);
    }

    allow_move = 0;
}

public void
make_random(void)
{
    object ob;
    int num = random(POSY_NUM) + POSY_NUM;

    while(num--)
    {
	ob = clone_object(SINGLE);
	ob->set_flower("random");
	ob->move(TO, 1);
    }

    update_flowers();
}

public void
make_flowers(string type = 0, string col = 0)
{
    object ob;
    int num = random(POSY_NUM) + POSY_NUM;

    if (!strlen(type) || !m_flowers[type])
	return make_random();

    while(num--)
    {
	ob = clone_object(SINGLE);
	ob->set_flower(type, col);
	ob->move(TO, 1);
    }

    update_flowers();
}

public void
hook_smelled(string str)
{
    one_of_list(all_inventory(TO))->hook_smelled(str);
}

/* Handles merging of flowers. */
public void
force_heap_merge(void)
{
    object ob, *obs;
    object env = environment();

    if (!living(env))
	return;

    /* Merge into an existing bouquet. */
    if (objectp(ob = present("zigg::bouquet", env)))
    {
	if (query_interactive(env))
	{
	    env->catch_tell("You merge your "+ short() +
		" into the "+ ob->short() +".\n");
	}

	map(all_inventory(TO), &->move(ob, 1));
	ob->update_flowers();
	remove_object();
	return;
    }

    /* Merge other posies into this posy. */
    obs = FIND_STR_IN_OBJECT("zigg::posies", env);
    if (sizeof(obs) > 1)
    {
	if (query_interactive(env))
	{
	    env->catch_tell("You merge your "+
		COMPOSITE_DEAD(obs) +" into a bouquet.\n");
	}

	ob = clone_object(BOUQUET);

	if (ob->move(env))
	    ob->move(env, 1);

	foreach(object posy : obs)
	    map(all_inventory(posy), &->move(ob, 1));

	ob->update_flowers();
	obs->remove_object();
	return;
    }

    /* Add loose flowers into the posy. */
    obs = FIND_STR_IN_OBJECT("zigg::flowers", env);
    obs = filter(obs, not @ &->query_no_meld());

    if (sizeof(obs))
    {
	if (query_interactive(env))
	{
	    env->catch_tell("You add "+ COMPOSITE_DEAD(obs) +
		" into the "+ short() +".\n");
	}

	moving();
	obs->move(TO);
	update_flowers();
    }
}

public int
pluck_flower(string str)
{
    object ob, tmp;
    string verb = query_verb();

    if (!strlen(str))
	return NF(CAP(verb) + " what from where?\n");

    if (!parse_command(str, TO, "[a] / [the] %o [from] [the] %o", ob, tmp))
	return NF(CAP(verb) + " what from where?\n");

    if ((tmp != TO) || (ob == TO))
	return NF(CAP(verb) + " what from where?\n");

    ob->set_no_meld();
    str = ob->short();

    write("You "+ verb +" "+ LANG_ADDART(str) +
	" from your "+ short() +".\n");
    say(QCTNAME(TP) +" "+ LANG_PWORD(verb) +" "+
	LANG_ADDART(str) +" from "+ HIS(TP) +" "+ short() +".\n");

    moving();

    if (ob->move(TP))
	ob->move(TP, 1);

    update_flowers();
    return 1;
}

public int
merge_flower(string str)
{
    object ob, *obs, tmp;

    if (!strlen(str))
	return NF("Add what to where?\n");

    obs = FIND_STR_IN_OBJECT("zigg::flowers", TP) + ({ TO });

    if (!parse_command(str, obs, "[a] / [the] %o [to] [the] %o", ob, tmp))
	return NF("Add what to where?\n");

    if ((ob == TO) || (tmp != TO))
	return NF("Add what to where?\n");

    ob->set_no_meld();
    str = ob->short();

    write("You add the "+ str +" to your "+ short() +".\n");
    say(QCTNAME(TP) +" adds "+ LANG_ADDART(str) +" to "+
	HIS(TP) +" "+ short() +"\n");

    moving();
    ob->move(TO);
    update_flowers();

    return 1;
}

public int
toss_flower(string str)
{
    object who, ob, *obs;
    string verb = query_verb();

    if (!strlen(str))
	return NF(CAP(verb) +" what?\n");

    obs = all_inventory(ENV(TP));
    obs = filter(obs, query_interactive) + ({ TO });

    if (!parse_command(str, obs, "[the] %o [to] [the] %o", ob, who))
	return NF(CAP(verb) +" what to whom?\n");

    if ((ob != TO) || (who == TO))
	return NF(CAP(verb) +" what to whom?\n");

    str = LANG_PWORD(verb);

    write("You "+ verb +" your "+ short() +" to "+
	who->query_the_name(TP) +", who manages to catch it.\n");
    say(QCTNAME(TP) +" "+ str +" "+ HIS(TP) +" "+ short() +" to "+
	QTNAME(who) +", who manages to catch it.\n", ({ TP, who }));
    who->catch_tell(TP->query_The_name(who) +" "+ str +" "+ HIS(TP) +
	" "+ short() +" to you!\n");

    if (ob->move(who))
	ob->move(who, 1);

    return 1;
}

public int
stomp_flower(string str)
{
    object ob;

    if (!strlen(str))
	return NF("Stomp on what?\n");

    if (!parse_command(str, ({ TO }), "[on] [the] %o", ob))
	return NF("Stomp on the what?\n");

    write("You throw the "+ short() +" down and proceed to "+
	"repeatedly stomp upon it until only a mangled mess is left.\n");
    say(QCTNAME(TP) +" throws "+ HIS(TP) +" "+ short() +" down and "+
	"proceeds to repeatedly stomp upon it until only a mangled "+
	"mess is left.\n");

    ob = clone_object(MANGLED);
    ob->set_mangled(query_name(), short(), plural_short());
    ob->move(ENV(TP));

    map(all_inventory(TO), &->move(ob, 1));
    ob->update_flowers();

    set_alarm(0.0, 0.0, remove_object);
    return 1;
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    holdable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
}

public void
init(void)
{
    ::init();

    if (ENV() != TP)
	return;

    add_action( pluck_flower, "pick"  );
    add_action( pluck_flower, "pluck" );
    add_action( merge_flower, "add"   );
    add_action(  toss_flower, "toss"  );
    add_action(  toss_flower, "throw" );
    add_action( stomp_flower, "stomp" );
    add_action(  help_flower, "help"  );
}
