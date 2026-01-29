/* File         : /d/Khalakhor/guilds/racial/clans/obj/tartan.c
 * Creator      : Tomas@Genesis
 * Date         : Feb 2001         
 * Purpose      : Guild Item for the Clans of Khalakhor Racial Guild
 * Related Files: 
 * Comments     : Taken from my copy of the eil galaith mantle
 * Modifications: 
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";

#include "guild.h"
#include <language.h>
#include <macros.h>
#include <wa_types.h>

string badge();

public string 
query_auto_load()       { return MASTER + ":"; }

public string 
query_recover()         { return 0; }

void init()
{
    mixed tmp;

    ::init();

    if (!living(environment()))
        return;

    setuid(); seteuid(getuid());
    tmp = (string)SERVER->query_clan(ENV(TO)->query_real_name());

    if (!strlen(tmp))
    {
        set_adj( tmp = ({"grey","green"}) );
        set_short("grey green tartan");
        set_pshort("grey green tartans");
    }
    else
    {
        set_adj(tmp = (string *)SERVER->query_clan(tmp)[CLAN_CLRS]);
        set_short(implode(tmp, " and ") + " tartan");
        set_pshort(implode(tmp, " and ") + " tartans");
    }
    add_adj("wool");
    set_long("The Tartan is a woven material, made of wool, having " +
       "stripes of " +(tmp[0] == "soft" ? "grey" : tmp[0]) + " and "+
       (tmp[1] == "grey" ? "grey as well" : tmp[1]) + 
       " varying in breadth. The arrangement of colours " +
       "is alike in warp and weft -- that is, in length and width " +
       "woven, giving the appearance of being a number " +
       "of squares intersected by stripes which cross each other. " +
       "The Tartan patterns are called setts. A large badge or crest " +
       "acts as the clasp which connects either end of the tartan on " +
       "your left side.\n");

}

public varargs string
long(string str, object for_obj)
{
    string res = ::long(str, for_obj);

    if (str || !IS_MEMBER(for_obj))
        return res;

    return res + "Use <clhelp> to assist you with your Clan " +
    "commands.\n";
}

public void
create_object()
{
    set_name( ({"tartan","clothing"}) );
    add_name("_std_khalakhor_wearable_item");
    add_name(OBJECT_ID);

    add_item(({"badge","crest","clasp","buckle"}),badge);

    set_layers(1);
    set_looseness(10);
    set_wf(this_object());
    set_slots(A_BODY | A_L_ARM);

    add_prop(OBJ_S_WIZINFO, "Clan of Khalakhor Racial Guild Item.\n");
    add_prop(OBJ_M_NO_DROP,"Oddly enough, you can't seem to "+
      "do that.\n");
    add_prop(OBJ_M_NO_GIVE, "It's sentimental value is too high "+
      "for you to simply give it away.\n");
    add_prop(OBJ_M_NO_SELL, "The shopkeeper finds it uninteresting.\n");
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_VALUE, 100);
}

public int
wear(object item)
{
    write("You pull the " + short() + " over your shoulders and " +
      "buckle it at your left side.\n");
    say(QCTNAME(TP) + " pulls the " + short() + " on over " +
      HIS + " shoulder, then buckles it at " + HIS + " waist.\n");
    return 1;
}

public int
remove(object item)
{
    write("You unbuckle the " + short() + " then pull it off your shoulder.\n");
    say(QCTNAME(TP) + " unbuckles the " + short() +
      " then pulls it off " + HIS + " shoulder.\n");
    return 1;
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}


string 
badge()
{

    string MYCLAN;
    MYCLAN=SERVER->query_clan(TP->query_real_name());

    switch(MYCLAN)
    {
        case "MacDunn":
            return "The round silver badge " + MACDUNN_BADGE;
            break;
        case "Lohrayn":
            return "The round pewter badge " + LOHRAYN_BADGE;
            break;
        case "MacTabor":
            return "The round platinum badge " + MACTABOR_BADGE;
            break;
        case "MacFadden":
            return "The round golden badge " + MACFADDEN_BADGE;
            break;
        case "MacVay":
            return "The round bronze badge " + MACVAY_BADGE;
            break;
        case "MacFaolain":
            return "The round copper badge "+ MACFAOLAIN_BADGE;
            break;
    }
    return "The round metal badge displays the " +
           "crest of Khalakhor. The crest depicts " +
           "the Celtic cross looming behind two " +
           "lions back to back facing outward.\n";
}


public string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc != GUILD_SUBLOC)
        return this_player()->show_subloc(subloc, on, for_obj);

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == on)
    {
        return "You proudly wear your " + short() + ", " +
        "displaying the colours of your clan.\n";
    }
    else
    {
        return on->query_The_name(for_obj) + " is wearing " +
        LANG_ADDART(short()) + " of the Clans of Khalakhor.\n";
    }
}

