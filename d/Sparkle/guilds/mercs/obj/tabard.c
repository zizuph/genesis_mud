/*
 * Tabard object
 *
 * Used to drape shields with the tabard of a sertain merc Lord.
 *
 */
inherit "/std/object";
inherit "/lib/commands";
inherit "/lib/keep";

#include "../merc.h"

#define TABARD_SUBLOC "_merc_guild_tabard_subloc_"

string gLord, gCrest, gFg, gEm, gBg, gGender;
object gShield, gShadow;
int gDraped = 0;

string query_lords_gender();
void   set_lords_gender(string str);
string query_mcrest_lords_gender();

void
set_lord(string lord)
{
    gLord = lord;
    query_mcrest_lords_gender();
}

string
query_lord()
{
    if (!strlen(gLord))
        gLord = CAP(MERC_GUILDMASTER);

    return gLord;
}

string
query_mcrest_lords_gender()
{
    if (query_lord() == CAP(MERC_GUILDMASTER))
	return "Lord";

    gGender = capitalize(MCREST->query_lord_gender(query_lord()));
    return gGender;
}

void set_lords_gender(string str)
{
    gGender = str;
}

string query_lords_gender()
{
    if (!strlen(gGender))
	return query_mcrest_lords_gender();

    return gGender;
}

public int
query_draped()
{
    return gDraped;
}

void
set_crest(string fg, string em, string bg)
{
    gFg = fg;
    gEm = em;
    gBg = bg;

    add_adj(bg);
}

string
*query_crest()
{
    if (!strlen(gFg))
	gFg = "red";

    if (!strlen(gEm))
	gEm = "dragon";

    if (!strlen(gBg))
	gBg = "black";

    return ({ gFg, gEm, gBg });
}

string
query_crest_desc()
{
    string *vowels = ({ "a", "e", "i", "o", "u" });

    if (!strlen(gFg))
	gFg = "red";

    if (!strlen(gEm))
	gEm = "dragon";

    if (!strlen(gBg))
	gBg = "black";

    if (member_array(extract(gBg, 0, 0), vowels) != -1)
        return gFg + " " + gEm + " on an " + gBg + " background";

    return gFg + " " + gEm + " on a " + gBg + " background";
}

string long_desc()
{
    if (gDraped == 0)
	return "This rolled up tabard can be used to 'tdrape' a "+
	    "shield, or 'tundrape' a shield that has already been "+
	    "draped. The tabard bears the crest of a "+query_crest_desc()+
	    ", the sign of the Mercenary "+
	    query_lords_gender()+" "+query_lord()+".\n";

    return "The tabard has been draped over your "+gShield->short()+
	   ", as you proudly display the crest of "+
	   query_lords_gender()+" "+query_lord()+
	   ", a "+query_crest_desc()+". The "+
	   gShield->short()+" can be 'tundrape'd if you wish to roll "+
	   "up the tabard and hide it from sight again.\n";
}

string short_desc()
{
    if (gDraped == 0)
	return gBg+" tabard";

    return "tabard draped over a "+gShield->short();
}

void
create_object()
{
    set_name("tabard");
    add_name(TABARD_ID);
    set_adj(({"merc", "mercenary"}));
    set_short("@@short_desc");
    set_long("@@long_desc");
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    seteuid(getuid(TO));
    set_keep(1);
}

public void
undrape_shield_silently(object ob)
{
    gDraped = 0;
    gShield = 0;
    
    remove_prop(OBJ_M_NO_DROP);
    gShadow->remove_shadow();
   set_no_show_composite(0); 
   ob->remove_subloc(TABARD_SUBLOC);
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (!gShield || !present(gShield, carrier))
        {
	    undrape_shield_silently(carrier);
	    return "";
        }

    if (for_obj == carrier)
	str = "Your";
    else
	str = POSSESSIVE(carrier);

    if (gShield->query_worn() == carrier)
        return capitalize(str)+" "+gShield->short()+" has been draped with a "+
	    "tabard depicting a "+query_crest_desc()+".\n";
    else
	return "";
}

init()
{
    seteuid(getuid(TO));
    set_alarm(0.0,0.0,"setup_tabard", TP);

    add_action("drape_shield", "drape");
    add_action("drape_shield", "tdrape");
    add_action("undrape_shield", "undrape");
    add_action("undrape_shield", "tundrape");

    if (!strlen(gFg))
	gFg = "red";

    if (!strlen(gEm))
	gEm = "dragon";

    if (!strlen(gBg))
	gBg = "black";

    ::init();

}

static int
filter_shield(object x)
{
    return (x->query_at() == A_SHIELD);
}

int drape_shield(string str)
{
    object *obs, shield;

    NF("Drape what?\n");
    if (!str)
	return 0;

    obs = FIND_STR_IN_OBJECT(str, this_player());

    if (!sizeof(obs))
	return 0;

    obs = filter(obs, "filter_shield", this_object());

    if (!sizeof(obs))
	return 0;

    NF("You can only drape one thing! A shield\n");
    if (sizeof(obs) > 1)
        return 0;

    shield = obs[0];

    NF("What?\n");
    if (environment(this_object()) != this_player())
        return 0;

    NF("You can only drape a shield, and a "+obs[0]->short()+
	" is not a shield!\n");
    if (!IS_ARMOUR_OBJECT(shield))
	return 0;

    if (shield->query_at() != A_SHIELD)
	return 0;

    NF("You cannot drape a shield that is strapped to your back. Unstrap "+
	"it first.\n");
    if (shield->query_sheath_object())
        return 0;

    NF("You have already draped the "+gShield->short()+" with your tabard.\n");
    if (gDraped == 1)
	if (!objectp(gShield))
	    gDraped == 0;
           else
            return 0;

    write("You unroll your tabard, draping it over your "+shield->short()+
	" to reveal the crest of "+query_lords_gender()+" "+
	capitalize(gLord)+", a "+query_crest_desc()+".\n");
    say(QCTNAME(TP)+" drapes "+POSSESSIVE(TP)+" "+shield->short()+" with a "+
	"tabard depicting a "+query_crest_desc()+".\n");
    TP->add_subloc(TABARD_SUBLOC, this_object());
    add_prop(OBJ_M_NO_DROP, "Your tabard is draped over your shield, "+
        "it cannot be dropped.\n");
    set_no_show_composite(1);
    gShield = shield;
    gShadow = clone_object(MOBJ + "shield_sh");
    gShadow->set_tabard_object(this_object());
    gShadow->shadow_me(shield);
    gDraped = 1;
    return 1;
}

int undrape_shield(string str)
{
    object shield;

    NF("Undrape what? Your shield?\n");
    if (str && str != "shield" && str != "my shield")
	return 0;

    NF("You have no shield draped!\n");
    if (gDraped == 0)
	return 0;

    write("You roll up your tabard, hiding it from view.\n");
    say(QCTNAME(TP)+" rolls up "+POSSESSIVE(TP)+" tabard, hiding it from "+
	"view.\n");
    remove_prop(OBJ_M_NO_DROP);
    set_no_show_composite(0);
    gShadow->remove_shadow();
    gDraped = 0;
    gShield = 0;
    return 1;
}

string query_auto_load()
{
    return MASTER_OB(this_object()) + ":" + gLord + " " +
	gFg + " " + gEm + " " + gBg;
}

void
init_arg(string str)
{
    int i = sscanf(str, "%s %s %s %s", gLord, gFg, gEm, gBg);

    if (i != 4)
    {
        environment(this_object())->catch_tell("Your tabard seems to have "+
	    "become corrupted, and vanishes without a trace!\n");
	return;
    }

    set_lord(gLord);
    set_crest(gFg,gEm,gBg);
}

