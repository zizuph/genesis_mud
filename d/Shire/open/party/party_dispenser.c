inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>
#include "party.h"

void do_press2(object obj);

void
create_object()
{
    seteuid(getuid());
    set_name(({"partytool dispenser", "dispenser", "machine"}));
    set_pname(({"partytool dispensers", "dispensers", "machines"}));
    set_short("partytool dispenser");
    set_pshort("partytool dispensers");
    set_long(break_string("It's a mechanical device containing an infinite "
	+ "number of PartyTools (tm) and should, upon pressing a button, "
	+ "extrude, spray or otherwise feed out its content. Simply put: "
	+ "it is most commonly used for vending the PartyTool (tm). About "
	+ "the PartyTool (tm): you need it to create a party.\n", 70)
	+ "There is a button on the machine, and little manual hangs on a "
	+ "cord.\n");

    add_item("button", "It is labeled: press me.\n");
    add_item("cord", "The cord keeps the manual near the machine.\n");
    add_item("manual", "@@manual_text");
    add_prop(OBJ_M_NO_GET, "It's way too heavy.\n");
}

void
init()
{
    ::init();

    add_action("do_press", "press");
    add_action("do_press", "push");
    add_action("do_slap", "slap");
    add_action("do_slap", "pat");
    add_action("do_slap", "hit");
    add_action("do_slap", "smash");
    add_action("do_read", "read");
}

int
do_press(string str)
{
    if (str != "button")
    {
	notify_fail("Press what?\n");
	return 0;
    }
    write("You press the button...\n");
    say(QCTNAME(this_player()) + " presses the button on the partytool (tm) "
      + "dispenser.\n");
    set_alarm(3.0, 0.0, &do_press2(this_player()));
    return 1;
}

void
do_press2(object obj)
{
    if (!obj || environment(obj) != environment())
	return;

    obj->catch_msg("Nothing seems to happen.\nPerhaps you should give the "
	+ "dispenser a firm pat on the side.\n");
}

int
do_slap(string str)
{
    object *obs, ob;
    string txt, qp;

    notify_fail(query_verb() + " what?\n");

    if (!str)
	return 0;

    obs = FIND_STR_IN_OBJECT(str, environment(this_player()));

    if (!obs || !sizeof(obs) || obs[0] != this_object())
	return 0;

    /* Test whether a partytool should appear */
    if (!((this_player()->query_wiz_level() ||
        (this_player()->test_bit("Shire", 0, 0) == 1 &&
         this_player()->query_base_stat(SS_LAYMAN) > 30))))
    {
	write("You slap the partytool (tm) dispenser.\n"
	    + "Nothing happens. Perhaps you cannot use the machine?\n");
	say(QCTNAME(this_player()) + " gives the partytool (tm) dispenser "
	  + "a firm pat on the side, but nothing happens.\n");
	return 1;
    }

    qp = this_player()->query_pronoun();
    txt = "You hear a rumble coming from deep within the machine... Suddenly "
        + "a PartyTool(tm) pops out!";
    write(break_string("You slap the PartyTool(tm) dispenser. " + txt
	+ " You quickly take it and move a step away from the dispenser.\n",
	  70));
    txt = " gives the vending machine a slap on its side! " + txt + " " + qp
        + " quickly takes it and moves a step away from the dispenser.\n";
    say(({break_string(METNAME + txt, 70), break_string(TART_NONMETNAME + txt,
        70)}));

    ob = clone_object(PARTY_TOOL);

    if (ob->move(this_player()))
    {
	write("You clumsily drop the PartyTool(tm) on the floor.\n");
	say(QCTNAME(this_player()) + " clumsily drops the PartyTool(tm) on "
	  + "the floor.\n");
	ob->move(environment(this_player()));
    }
    return 1;
}

string
manual_text()
{
    return break_string(
	  "This vending machine, the PartyTool and all associated things "
	+ "are (tm)... [blablabla... Ah!] WARNING: due to the mess from "
	+ "cakefights and the not too strong stomachs of certain people, "
	+ "the party room has to be decontaminated after each party. "
	+ "Cleaning will take around " + HOURS_BETWEEN_PARTIES + " hours. "
	+ "During this time, no other party can be started. So, be sure "
	+ "to know what you are doing when you are starting a party.\n", 70);
}

int
do_read(string str)
{
    if (str != "manual")
    {
	notify_fail("Read what?\n");
	return 0;
    }
    write(manual_text());
    return 1;
}
