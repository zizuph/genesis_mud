/*
 * /d/Gondor/common/obj/tower_surcoat.c
 *
 * the surcoat of the guardss of the citadel in minas tirith
 */

#pragma strict_types

inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/formulas.h"
#include "/d/Gondor/defs.h"

#define SURCOAT_SUBLOC   "_surcoat_subloc"

static int worn;

void
create_object()
{
    set_name("surcoat");
    set_short("black surcoat");
    set_pshort("black surcoats");
    set_adj("black");
    set_long(BSN("This black surcoat is of the kind that is only worn "+
	"by the Guards of the Citadel in Minas Tirith. On the front "+
	"is embroidered in white a tree blossoming like snow, beneath "+
	"a silver crown, and surrounded by seven many-pointed stars."));
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 864);
}

void
init()
{
    add_action("do_wear", "wear");
    add_action("do_remove", "remove");
}

int 
do_wear(string str)
{
    if (str != "surcoat")
    {
	return 0;
    }
    if (!present(TO, TP))
    {
	NF0("Pick it up first.\n");
    }
    if (worn)
    {
	NF0("You are already wearing it.\n");
    }

    if (member_array(SURCOAT_SUBLOC, TP->query_sublocs()) > -1)
    {
	NF0("You are already wearing a surcoat!\n");
    }

    TP->add_subloc(SURCOAT_SUBLOC, TO);
    if (TP->query_armour(A_TORSO))
    {
	WRITE("You wear the surcoat of the Guards of the Citadel over " +
	    "your " + TP->query_armour(A_TORSO)->short() + ".");
	SAY(" wears the " + short() + " over " + TP->query_possessive() +
	     " " + TP->query_armour(A_TORSO)->short() + ".");
    }
    else
    {
	write("You wear the surcoat of the Guards of the Citadel.\n");
	SAY(" wears the " + short() + ".");
    }
    add_prop(OBJ_M_NO_DROP, "Remove the surcoat first.\n");
    worn = 1;
    TO->set_no_show_composite(1);
    return 1;
}

int 
do_remove(string str)
{
    if (str != "surcoat")
    {
	return 0;
    }
    if (!worn)
    {
	NF0("You are not wearing the surcoat!\n");
    }
    TP->remove_subloc(SURCOAT_SUBLOC);
    worn = 0;
    remove_prop(OBJ_M_NO_DROP);
    set_no_show_composite(0);
    write("You remove the black surcoat.\n");
    SAY(" removes the black surcoat.");
    return 1;
}

string 
show_subloc(string subloc, object on, object for_ob)
{
    string data;
    if (subloc == SURCOAT_SUBLOC &&
	!on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
	if (for_ob != on)
	{
	    data = CAP (on->query_pronoun()) +
		" is wearing the surcoat of the Guards of the Citadel";
	    if (on->query_armour(A_TORSO))
	    {
		data = data + " over " +
		    on->query_possessive() + " " +
		    on->query_armour(A_TORSO)->short() + ".";
	    }
	    else
	    {
		data = data + ".";
	    }
	}
	else
	{
	    data = "You are wearing the surcoat of the Guards of the Citadel";
	    if (on->query_armour(A_TORSO))
	    {
		data = data + " over your " +
		    on->query_armour(A_TORSO)->short() + ".";
	    }
	    else
	    {
		data = data + ".";
	    }
	}
	return BSN(data);
    }
    return on->show_subloc(subloc, on, for_ob);
}

void
leave_env(object to, object old)
{
    TP->remove_subloc(SURCOAT_SUBLOC);
    remove_prop(OBJ_M_NO_DROP);
    ::leave_env(to, old);
}
