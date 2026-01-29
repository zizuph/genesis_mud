#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include <options.h>
#include "/d/Krynn/common/defs.h"

#define PLATEMAIL_SUBLOC "platemail_subloc"

inherit "/std/armour";
int worn, mprop = 0;

create_armour()
{
    set_name("platemail");
    add_name("fullplate");
    add_adj(({"platinum","plate","full"}));
    set_short("platinum fullplate armour");
    set_long("A finer set of armour you have never seen. The metal "+
      "is resplendant platinum, pure and shining. On the breastplate "+
      "is the symbol of the Triumvirate:  The Crown, the Sword, and "+
      "the Rose.\n");
    set_at(A_BODY | A_ARMS | A_LEGS);
    set_ac(50);
    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VALUE, 25000);
    set_af(TO);
    seteuid(getuid(TO));
    worn = 0;
}

init()
{
    set_alarm(1.0, 0.0, "wear_fullplate");
    ::init();
}

void
wear_fullplate()
{
    TP->command("$wear fullplate");
}

mixed
wear(object what)
{
    if (what == TO)
    {
	write("You carefully don the platinum fullplate, marvelling at how "+
	  "light and wonderfully the weight is distributed over your body.\n");
	say(QCTNAME(TP)+" carefully dons the platinum fullplate, and the "+
	  "armour begins to shimmer, casting a silver glow.\n");
	TP->set_skill(24, (TP->query_skill(24) + 25));
	TP->add_subloc(PLATEMAIL_SUBLOC, TO);      

	if (!TP->query_prop(MAGIC_I_RES_MAGIC))
	{
	    TP->add_prop(MAGIC_I_RES_MAGIC, 50);
	    mprop = 1;
	}

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
	wearer->catch_msg("You hesitantly remove the platinum fullplate "+
	  "armour, and you suddenly feel very vulnerable.\n");
	say(QCTNAME(TP) + " hesitantly removes "+POSSESSIVE(TP)+" shimmering "+
	  "platinum fullplate.\n");
	TP->set_skill(24, (TP->query_skill(24) - 25));
	TP->remove_subloc(PLATEMAIL_SUBLOC);

	if (mprop == 1)
	{
	    TP->remove_prop(MAGIC_I_RES_MAGIC);
	    mprop = 0;
	}

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
	str = "Your breastplate is adorned with a crowned kingfisher "+
	"clutching a bright sword in its talons and a rose in its beak.\n";
    else
	str = C(POSSESSIVE(TP))+" breastplate is adorned with a crowned kingfisher "+
	"clutching a bright sword in its talons and a rose in its beak.\n";

    return str;
}

string
query_auto_load()
{
    return MASTER_OB(this_object()) + ":";
}
