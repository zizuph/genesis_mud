inherit "/std/armour";
inherit "/lib/keep";

#include "/d/Krynn/common/defs.h"
#include "../knight/guild.h"
#include <macros.h>
#include <wa_types.h>

#define CRESTED_CLOAK_SUBLOC "knight_of_solamnia_crest_cloak"

string colour = "clear", crest = "blank";
int worn;

int query_recover() { return 0; }

void
set_colour(string col)
{
    colour = col;
}

string
query_colour()
{
    return colour;
}

void
set_crest(string cr)
{
    crest = cr;
}

string
query_crest()
{
    return crest;
}

void
create_armour()
{
    set_name("_knight_cloak");
    add_name("cape");
    set_adj("@@query_colour");
    set_short("@@query_colour@@ cape");
    set_pshort("@@query_colour@@ capes");
    set_long("This @@query_colour@@ cape is made of the finest" +
      " wool. It has been expertly decorated with a crest of" +
      " @@query_crest@@, and ties at the neck. You may 'adjust' the" +
      " brooch, or Knights may 'reveal' their tunics beneath" +
      " the cape.\n");
    add_item("crest", "The crest depicts @@query_crest@@\n");
    add_item("brooch", "The brooch is decorated with the emblem" +
      " of the Knighthood: a crowned kingfisher, clutching" +
      " a rose in its beak, and a sword in its talons.\n");
    add_prop(OBJ_M_NO_BUY, 1);
    set_keep(1);
    set_ac(10);
    set_at(A_ROBE);
    set_af(TO);
    seteuid(getuid(TO));

    worn = 0;
}

mixed
wear(object what)
{
    if (what != TO)
	return 0;

    write("An unbidden air of nobility washes over you as you "+
      "throw the Solamnian cape over your shoulders, fastening "+
      "the brooch at the neck.\n");
    say(QCTNAME(TP)+" throws "+POSSESSIVE(TP)+" Solamnian cape "+
      "over "+POSSESSIVE(TP)+" shoulders and fastens the brooch "+
      "at the neck.\n");
    TP->add_subloc(CRESTED_CLOAK_SUBLOC, TO);
    worn = 1;
    return 1;
}

mixed
remove(object what)
{
    if (what != TO || !TP)
	return 0;

    write("You unfasten the brooch at your neck and pull off the "+
      "Solamnian cape.\n");
    say(QCTNAME(TP)+" unfastens the brooch of "+POSSESSIVE(TP)+
      " Solamnian cape and pulls it off.\n");
    TP->remove_subloc(CRESTED_CLOAK_SUBLOC);
    worn = 0;
    return 1;
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str, col, cr;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    col = query_colour();
    cr = query_crest();
    if (for_obj == carrier)
	str = "Your";
    else
	str = POSSESSIVE(carrier);

    return C(str)+" "+col+" cape is decorated with a "+
    "crest depicting "+cr+".\n";
}

init()
{
    add_action("adjust", "adjust");
    add_action("reveal", "reveal");
    ::init();
}

/* Cape emotes */
int adjust(string str)
{
    object cloak;

    if (!P("_knight_cloak", TP))
	return 0;

    cloak = P("_knight_cloak", TP);

    if (member_array(cloak, TP->query_armour(-1)) < 0)
	return 0;

    NF("Adjust your brooch how?\n");
    if (!str || str != "brooch")
	return 0;

    write("You adjust the brooch of your "+cloak->short()+".\n");
    say(QCTNAME(TP)+" adjusts the brooch of "+POSSESSIVE(TP)+" "+
      cloak->short()+".\n");
    return 1;
}

int reveal(string str)
{
    int lev = TP->query_knight_level();
    string slev;
    object cloak;

    if (str)
	return 0;

    if (!P("_knight_cloak", TP))
	return 0;

    cloak = P("_knight_cloak", TP);

    if (member_array(cloak, TP->query_armour(-1)) < 0)
	return 0;

    if (!MEMBER(TP))
	return 0;

    switch(lev)
    {
    case 5:
	slev = "Order of the Rose";
	break;
    case 4:
	slev = "Order of the Sword";
	break;
    case 3:
	slev = "Order of the Crown";
	break;
    default:
	slev = "Knighthood";
    }

    write("You throw back your "+cloak->short()+", revealing "+
      "your tunic which is decorated with the emblem of the "+
      slev+".\n");
    say(QCTNAME(TP)+" throws back "+POSSESSIVE(TP)+" "+
      cloak->short()+", revealing a tunic decorated with the "+
      "emblem of the "+slev+".\n");
    return 1;
}

