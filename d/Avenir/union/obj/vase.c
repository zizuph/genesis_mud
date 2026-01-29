#pragma strict_types
#include "../defs.h"

inherit "/std/container";

#include <macros.h>
#include <composite.h>
#include <stdproperties.h>


public void
create_container()
{
    reset_euid();

    set_name("urn");
    add_name(({ "onyx" }));
    set_short("@@empty_str@@onyx urn@@full_str@@");
    set_long("It is an slender urn made from smooth onyx. The stone "+
	"has been worked until it is very thin and delicate, and "+
	"it reflects its surroundings with an eerie, shadow-refraction.\n");

    set_adj(({ "thin", "slender", "smooth", "onyx" }));

    add_prop(OBJ_I_VOLUME, 260);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VALUE, 26);

    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_MAX_VOLUME, 600);
    add_prop(CONT_I_MAX_WEIGHT, 200);
}

public string
empty_str(void)
{
    if (!sizeof(all_inventory()))
	return "empty ";
    else
	return "";
}

public string
full_str(void)
{
    object *flowers = filter(all_inventory(), &->id("flower"));

    if (!sizeof(flowers))
	return "";

    if (sizeof(flowers) > 4)
	return " of flowers";

    return " containing " + COMPOSITE_DEAD(flowers);
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

    write("You smash the "+ short() +" against the ground, shattering "+
	"it completely.\n");
    say(QCTNAME(TP) +" smashes "+ LANG_ADDART(short()) +" against the "+
	"ground, shattering it completely.\n");

    glass = clone_object("/std/heap");
    glass->set_name("sliver");
    glass->add_name("onyx");
    glass->set_adj("broken");
    glass->set_short("sliver of broken onyx");
    glass->set_pshort("slivers of broken onyx");
    glass->set_long("It is a sliver of onxy, broken from "+
	"some deliacate work.\n");
    glass->set_heap_size(random(10)+1);
    glass->add_prop(HEAP_S_UNIQUE_ID, "broken onyx fragment");
    glass->add_prop(OBJ_I_VALUE, 1);
    glass->add_prop(OBJ_I_WEIGHT, 2);
    glass->add_prop(OBJ_I_VOLUME, 8);
    glass->move(ENV(TP));

    all_inventory(TO)->move(ENV(TP), 1);
    set_alarm(0.0, 0.0, remove_object);
    return 1;
}

public void
init(void)
{
    ::init();

    add_action(do_break, "break");
    add_action(do_break, "smash");
}
