#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include <options.h>
#include "/d/Krynn/common/defs.h"

#define GAUNTLETS_SUBLOC "gauntlets_subloc"

inherit "/std/armour";
int worn;
int mprop = 0;
int clenched = 0;

create_armour()
{
    set_name("gauntlets");
    add_name("gloves");
    add_adj(({"platinum","chain"}));
    set_short("pair of platinum gauntlets");
    set_long("These gauntlets are made of small plates of platinum, "+
      "connected by intricate platinum chainmail. The workmanship "+
      "is extraordinary, and on the back of the fist is a tiny "+
      "symbol of a platinum dragon.\n");
    set_at(A_HANDS);
    set_ac(25);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VALUE,  5000);
    set_af(TO);
    seteuid(getuid(TO));
    worn = 0;
}

init()
{
    add_action("do_fist", "clench");
    set_alarm(5.0, 0.0, "wear_clench");
    ::init();
}

void
wear_clench()
{
    TP->command("$wear gauntlets");
    set_alarm(10.0, 0.0, "wear_clench2");
}

void
wear_clench2()
{
    TP->command("$clench fists");
}

int
do_fist(string str)
{
    if (worn != 1)
    {
	NF("What ?\n");
	return 0;
    }

    if (!str)
    {
	NF("Clench what? Your fists?\n");
	return 0;
    }

    if (clenched == 1)
    {
	write("You clench your fists again, but you don't feel anything "+
	  "happen.\n");
	return 1;
    }

    if (str == "fists")
    {
	write("You feel power surge through your veins as you clench your "+
	  "fists inside the platinum gauntlets, which begin to shimmer "+
	  "with magical power!\n");
	say(QCTNAME(TP)+"'s platinum gauntlets begin to shimmer with "+
	  "bright silver light as "+PRONOUN(TP)+" clenches "+
	  POSSESSIVE(TP)+" fists.\n");
	TP->set_stat_extra(0, 30);
	TP->add_subloc(GAUNTLETS_SUBLOC, TO);
	set_alarm(60.0, 0.0, "unclench");
	clenched = 1;
	return 1;
    }

    return 0;
}

void
unclench()
{
    if (worn == 1)
    {
	write("The bright shimmering aura around your gauntlets dies down, "+
	  "and you feel the power fade away.\n");
	say("The shimmering aura around "+QTNAME(TP)+"'s gauntlets fades "+
	  "away.\n");
	TP->remove_subloc(GAUNTLETS_SUBLOC);
	TP->set_stat_extra(0, -30);
	clenched = 0;
    }
}

mixed
wear(object what)
{
    if (what = TO)
    {
	write("You pull on the platinum gauntlets.\n");
	say(QCTNAME(TP)+" pulls on "+POSSESSIVE(TP)+" platinum gauntlets.\n");

	worn = 1;
	return 1;
    }

    return 0;
}

mixed
remove(object what)
{
    if (what == TO)
    {

	if (clenched == 1)
	{
	    write("The bright shimmering aura around your gauntlets dies down, "+
	      "and you feel the power fade away.\n");
	    say("The shimmering aura around "+QTNAME(TP)+"'s gauntlets fades "+
	      "away.\n");
	    TP->remove_subloc(GAUNTLETS_SUBLOC);
	    TP->set_stat_extra(0, -30);
	    clenched = 0;
	}

	wearer->catch_msg("You slide off the platinum gauntlets, feeling "+
	  "the power trickle away slowly.\n");
	say(QCTNAME(TP) + " slides off "+POSSESSIVE(TP)+" platinum "+
	  "gauntlets.\n");
	worn = 0;
	return 1;
    }

    return 0;
}

string
show_subloc(string subloc, object carrier, object for_obj)
{

    string str;

    if(carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if(for_obj == carrier)
	str = "Your fists are surrounded by bright silver globes of "+
	"light.\n";
    else
	str = POSSESSIVE(carrier)+" fists are surrounded by bright "+
	"silver globes of light.\n";

    return str;
}

string
query_auto_load()
{
    return MASTER_OB(this_object()) + ":";
}
