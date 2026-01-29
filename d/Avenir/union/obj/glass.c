inherit "/std/container";

#include <macros.h>
#include <language.h>
#include <stdproperties.h>

#include "../defs.h";

public nomask void
create_container()
{
    reset_euid();

    set_name("glass");
    add_name(({ "crystal", "goblet", "_crucible_component" }));
    set_short("@@empty_str@@crystal goblet");
    set_long("Made from thin, delicate faceted crystal, this goblet "+
	"rests on a long stem of blown glass.\n");

    set_adj(({ "thin", "delicate", "crystal", "faceted", "empty" }));

    add_prop(OBJ_I_VOLUME, 99);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VALUE, 26);

    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_MAX_VOLUME, 80);
    add_prop(CONT_I_MAX_WEIGHT, 80);
}

public string
empty_str(void)
{
    if (!sizeof(all_inventory()))
	return "empty ";
    else
	return "";
}

public int
do_break(string str)
{
    object glass, ob;

    NF(CAP(query_verb()) + " what?\n");
    if (!strlen(str))
	return 0;

    if (!parse_command(str, TP, "[the] %o", ob) || ob != TO)
	return 0;

    write("You smash the "+ short() +" against the ground, shattering it "+
	"completely.\n");
    say(QCTNAME(TP) +" smashes "+ LANG_ADDART(short()) +" against the "+
	"ground, shattering it completely.\n");

    glass = clone_object("/std/heap");
    glass->set_name("shard");
    glass->add_name(({"glass", "_crucible_component"}));
    glass->set_adj("broken");
    glass->set_short("shard of broken glass");
    glass->set_pshort("shards of broken glass");
    glass->set_long("It is a shard of broken glass, the remenants "+
	"of what was previously fine crystal.\n");
    glass->set_heap_size(random(10)+1);
    glass->add_prop(HEAP_S_UNIQUE_ID, "broken glass");
    glass->add_prop(OBJ_I_VALUE, 1);
    glass->add_prop(OBJ_I_WEIGHT, 2);
    glass->add_prop(OBJ_I_VOLUME, 8);
    glass->move(ENV(TP));

    all_inventory(TO)->move(ENV(TP), 1);
    set_alarm(0.0, 0.0, remove_object);

    return 1;
}

public mixed
water(void)
{
    object who, where, *inv, *things;

    who = ENV(TO);
    if (living(who))
	where = ENV(who);

    inv = all_inventory(who) + all_inventory(where);
    things = filter(inv, &->query_prop(OBJ_I_CONTAIN_WATER));

    if (!sizeof(things))
	return 0;

    return things[0];
}

/* replace this object with a full glass */
public void
fill_with_water()
{
    catch(clone_object(OBJ + "glass_of_water")->move(ENV(TO), 1));
    set_alarm(0.0, 0.0, remove_object);
}

public int
do_fill(string str)
{
    object ob;
    string nihil;

    NF(CAP(query_verb())+" what?\n");
    if (!strlen(str) || !parse_command(str, TP,
	    "[the] / [a] / [an] %o %s", ob, nihil) || ob != TO)
	return 0;

    /* Check the room type for water */
    if (ENV(TP)->query_prop(ROOM_I_TYPE) == ROOM_BEACH ||
	ENV(TP)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER ||
	ENV(TP)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER ||
	ENV(TP)->query_prop(OBJ_I_CONTAIN_WATER))
    {
	write("You "+ query_verb() +" "+ LANG_THESHORT(TO) +
	    " with water.\n");
	say(QCTNAME(TP) +" "+ query_verb() +"s "+ HIS(TP) +
	    " "+ QSHORT(TO) +" with water.\n");
	fill_with_water();
	return 1;
    }

    /* Am I on a ship? */
    if (function_exists("create_deck", ENV(TP)) ||
	function_exists("create_ship", ENV(TP)))
    {
	write("You lean over the side of the ship and "+
	    query_verb() +" "+ LANG_THESHORT(TO) +" with sea water.\n");
	say(QCTNAME(TP) +" leans over the side of the ship and "+
	    query_verb() +"s "+ HIS(TP) +" "+ QSHORT(TO) +
	    " with sea water.\n");

	fill_with_water();
	return 1;
    }

    /* Am I carrying something that contains water? */
    NF("You see no water nearby suitable for drinking.\n");
    if (!water())
	return 0;

    write("You "+ query_verb() +" "+ LANG_THESHORT(TO) +" from "+
	LANG_THESHORT(water()) +".\n");
    say(QCTNAME(TP) +" "+ query_verb() +"s "+ HIS(TP) +" "+ QSHORT(TO) +
	" from "+ LANG_THESHORT(water()) +".\n");

    fill_with_water();
    return 1;
}

public void
init(void)
{
    ::init();

    add_action(do_break, "break");
    add_action(do_break, "smash");
    add_action(do_fill,  "fill");
}
