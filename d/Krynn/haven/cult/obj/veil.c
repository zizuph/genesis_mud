#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/haven/cult/local.h"
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <cmdparse.h>

inherit "/std/object";
inherit "/d/Krynn/rastlin/open/spells2/spellcasting.c";

#define VEIL_SHADOW COBJ + "veil_shadow"
#define VEIL_SUBLOC "_cult_of_morgion_veiled_subloc"

int veiled = 0;

int
query_recover()
{
    return 0;
}

string
query_auto_load()
{
    return MASTER;
}

#include "../spells/mpoison.c"

int
query_spell_mess(string verb, string arg)
{
    write("You whisper a prayer to your master, Morgion, beneath "+
      "your breath.\n");
    return 1;
}

void
create_object()
{
    set_name("veil");
    add_name("veil_of_morgion");
    add_adj("brown");
    set_short("brown veil");
    set_long("A brown veil and hood, which can be worn over your head "+
      "to conceal your identity. Such veils are favoured by clerics "+
      "of Morgion, and should always be worn when spreading disease "+
      "and dissention over the land of Krynn.\n");
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE,0);
    seteuid(getuid(TO));
    add_spell("mpoison", do_mpoison, "Test spell - mpoison");
}

void
init()
{
    add_action("wear_veil", "wear");
    add_action("remove_veil", "remove");
    ::init();
}

int
wear_veil(string str)
{
    NF("Wear what?\n");
    if (!str)
	return 0;

    if (str != "veil" && str != "brown veil")
	return 0;

    NF("You are already wearing your brown veil.\n");
    if (veiled == 1)
	return 0;

    veiled = 1;

    write("Shadows fall across your face as you tie the brown veil "+
      "around your head.\n");
    say(QCTNAME(TP)+"'s face vanishes behind the darkness of the veil "+
      "as "+PRONOUN(TP)+" ties it around "+POSSESSIVE(TP)+" head.\n");

    TP->add_subloc(VEIL_SUBLOC, TO);
    TP->add_prop(LIVE_I_NEVERKNOWN, 1);
    TO->set_no_show();
    clone_object(VEIL_SHADOW)->shadow_me(TP);
    return 1;
}

int
remove_veil(string str)
{
    NF("Remove what?\n");
    if (!str)
	return 0;

    if (str != "veil" && str != "brown veil")
	return 0;

    NF("You are not wearing your brown veil.\n");
    if (veiled == 0)
	return 0;

    veiled = 0;

    write("The shadows surrounding your face vanish as you remove the "+
      "brown veil.\n");
    say(QCTNAME(TP)+"'s face emerges from the shadows of "+POSSESSIVE(TP)+
      " brown veil as "+PRONOUN(TP)+" slowly unties it.\n");

    TP->remove_subloc(VEIL_SUBLOC);
    TP->remove_prop(LIVE_I_NEVERKNOWN);
    TP->remove_shadow(VEIL_SHADOW);
    TO->unset_no_show();
    TO->unset_no_show_composite();
    return 1;
}

string
show_subloc(string subloc, object carrier, object for_obj)
{

    string str;

    if(carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if(for_obj == carrier)
	str = "Your face is concealed behind the darkness of your "+
	"brown veil.\n";
    else
	str = OBJECTIVE(carrier)+" face is concealed beneath the darkness "+
	"of "+POSSESSIVE(carrier)+" brown veil.\n";

    return str;
}

