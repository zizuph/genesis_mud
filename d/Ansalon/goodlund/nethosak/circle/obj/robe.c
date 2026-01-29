#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/haven/cult/local.h"
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <cmdparse.h>

inherit "/std/object";
inherit "/d/Krynn/rastlin/open/spells2/spellcasting.c";

#define ROBE_SHADOW   "/d/Ansalon/goodlund/nethosak/circle/shadow/robe_shadow"
#define ROBE_SUBLOC   "_cult_of_morgion_veiled_subloc"

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

#include "/d/Krynn/haven/cult/spells/mpoison.c"

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
    set_name("robe");
    add_name("robe_of_morgion");
    add_adj("dark");
    set_short("dark robe");
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
    add_action("wear_robe", "wear");
    add_action("remove_robe", "remove");
    ::init();
}

int
wear_robe(string str)
{
    NF("Wear what?\n");
    if (!str)
        return 0;

    if (str != "robe" && str != "dark robe")
        return 0;

    NF("You are already wearing your robe.\n");
    if (veiled == 1)
        return 0;

    veiled = 1;

    write("For a brief moment shadows surrounds your body and face as "+
          "you wear your dark robe around your body.\n"+
          "The robe twists itself "+
          "around your body and head, completely hiding your identity.\n");
    say(QCTNAME(TP)+" is briefly surrounded by darkness as "+PRONOUN(TP)+
        " wears "+POSSESSIVE(TP)+" dark robe around "+POSSESSIVE(TP)+
        "body.\n"+
        "The robe twists itself around "+ QCTNAME(TP)+ "'s body and head "+
        "completely hiding "+POSSESSIVE(TP)+ "identity.\n");

    TP->add_subloc(ROBE_SUBLOC, TO);
    TP->add_prop(LIVE_I_NEVERKNOWN, 1);
    TO->set_no_show();
    clone_object(ROBE_SHADOW)->shadow_me(TP);
    return 1;
}

int
remove_robe(string str)
{
    NF("Remove what?\n");
    if (!str)
        return 0;

    if (str != "robe" && str != "dark robe")
        return 0;

    NF("You are not wearing your dark robe.\n");
    if (veiled == 0)
        return 0;

    veiled = 0;

    write("The robe releases its grips around you, and allows you to show "+ 
          "yourself.\n");
    say(QCTNAME(TP)+"'s face emerges from the shadows of "+POSSESSIVE(TP)+
      " dark robe as "+PRONOUN(TP)+" slowly unties it.\n");

    TP->remove_subloc(ROBE_SUBLOC);
    TP->remove_prop(LIVE_I_NEVERKNOWN);
    TP->remove_shadow(ROBE_SHADOW);
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
        str = "Your body and face are concealed behind the darkness of your "+
        "dark robe.\n";
    else
        str = OBJECTIVE(carrier)+" body and face are concealed under the "+
        "of "+POSSESSIVE(carrier)+" "+short()+".\n";
    return str;
}
