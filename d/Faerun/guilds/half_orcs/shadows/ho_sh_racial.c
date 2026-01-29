/* /d/Faerun/guilds/half-orcs/shadows/ho_sh_racial.c
 *
 * Guildshadow
 *
 */

inherit "/std/guild/guild_race_sh";
inherit "/lib/commands";

#include <macros.h>
#include <const.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include "/std/combat/combat.h"
#include "../guild.h"


/*
 * Global variables
 */
public int      query_guild_not_allow_join_race(object player, 
                string type, string style, string name);
static int      query_guild_keep_player(object ob);
public void     init_race_shadow(string str);



static string *tusks = ({ "long",
    "protruding",
    "broken",
    "jagged",
    "thick",
    "yellowing",
    "sharp",
    "short",	
	"damaged",
    "blunt",
    "blooded",
    "blackened",
    "elegant",
});


int
query_tusks()
{
	return HO_MAPPINGS->query_ho_tusks(shadow_who->query_real_name());
}


public string
show_subloc(string subloc, object me, object for_obj)
{
    string str;
	string str2;
	
    if (subloc != "Ho subloc")
    {
        return me->show_subloc(subloc, me, for_obj);
    }
	
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
        return "";
    }
	
    if (for_obj == me)
    {
        str = "You have";
		str2 = "your";
    }
    else
    {
        str = capitalize(me->query_pronoun()) + " has";
		str2 = me->query_possessive();
    }
	
    return str + " a pair of "+tusks[query_tusks()]
	+ " tusks in "+str2+" lower jaw.\n";
}



int query_ho_race()
{
    return 1;
}


public void
add_race_soul()
{
    setuid();
    seteuid(getuid());

    shadow_who->add_cmdsoul(HO_GUILD_DIR 
    + "souls/ho_race");
	
	shadow_who->catch_tell("For Half Orc racial help, type 'hohelp'.\n");

    shadow_who->update_hooks();
}


string
query_guild_title_race()
{ 
    return "";
}


public string
query_guild_name_race()
{
    return RACE_HO_GUILD_NAME;
}


public string
query_guild_style_race()
{
    return TYPE_RACE;
}


public int
query_guild_tax_race()
{
    return TAX_RACE;
}


public mixed
query_guild_trainer_race()
{
    return ({  });
}


public int
query_guild_not_allow_join_race(object player, string type, 
string style, string name)
{
    if (::query_guild_not_allow_join_race(player, type, style, name))
    return 1;
}


public int
query_guild_keep_player(object ob)
{
    return 1;
}


public void
init_race_shadow(string str)
{
    object who = query_shadow_who();
    
    setuid();
    seteuid(getuid());

    ::init_race_shadow();
    
    set_alarm(0.0, 0.0, add_race_soul);
	
	shadow_who->set_race_name("half-orc");
	
	shadow_who->add_subloc("Ho subloc", shadow_who);
}


public void remove_shadow()
{
    shadow_who->remove_cmdsoul(HO_GUILD_DIR 
    + "souls/ho_race");

    shadow_who->update_hooks();

    ::remove_shadow();
}
