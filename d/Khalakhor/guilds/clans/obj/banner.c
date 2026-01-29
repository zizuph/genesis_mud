/**********************************************************************
 * - banner.c                                                       - *
 * - A banner that can be carried and waved for Clans of Khalakhor. - *
 * - Created by Damaris@Genesis 05/2006                             - *
 * - Added clan colours Damaris - 08/2006                           - *
 **********************************************************************/
#pragma strict_types

#include "../guild.h"
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/object";

public varargs string
long(string str, object for_obj)
{
	string res = ::long(str, for_obj);
	if (!objectp(for_obj))
	for_obj = this_player();
	if (str || !IS_MEMBER(for_obj))
	return res;
	return res + "You can easily <'wave | display | "+
	"extend' banner>.\n";
}

public void
create_object()
{
	set_name( ({"banner"}) );
	add_prop(OBJ_M_NO_SELL, "The shopkeeper finds it "+
	"uninteresting.\n");
	add_prop(OBJ_I_WEIGHT, 400);
	add_prop(OBJ_I_VOLUME, 200);
	add_prop(OBJ_I_VALUE, 100);
}

void
enter_env(object env, object from)
{
	::enter_env(env, from);
	if (IS_MEMBER(env) || env->query_wiz_level());
}
public void
leave_env(object from, object to)
{
	::leave_env(from, to);
}

public void
appraise_object(int num)
{
	::appraise_object(num);
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
		return "You proudly display your " + short() + ", "+
		"displaying your celtic banner.\n";
	}
	else
	{
		return on->query_The_name(for_obj) + " is proudly displaying "+
		LANG_ADDART(short()) + " celtic banner.\n";
	}
}
int
wave_banner(string str)
{
        if((str == "banner"))
	{
		write("You proudly wave the "+ short(TO) +" high in "+
		"the air.\n\n"+
                	"                  ()__\n"+
                	"                  ||  Z____\n"+
                	"                  ||   |   Z______\n"+
                	"                  ||   |   |  K  |\n"+
                	"                  || C |   |  H  |\n"+
                	"                  || L |   |  A  |\n"+
                	"                  || A | O |  L  |\n"+
                	"                  || N | F |  A  |\n"+
                	"                  || S |   |  K  |\n"+
                	"                  ||   |   |  H  |\n"+
                	"                  ||'''|   |  O  |\n"+
                	"                  ||   |===|  R  |\n"+
                	"                  ||   `'''|=====|\n"+
                	"                  ||       `'''''`\n\n");
		
                say(QCTNAME(TP)+" proudly waves the "+short(TO)+ " high "+
                "in the air.\n\n"+
                	"                  ()__\n"+
                	"                  ||  Z____\n"+
                	"                  ||   |   Z______\n"+
                	"                  ||   |   |  K  |\n"+
                	"                  || C |   |  H  |\n"+
                	"                  || L |   |  A  |\n"+
                	"                  || A | O |  L  |\n"+
                	"                  || N | F |  A  |\n"+
                	"                  || S |   |  K  |\n"+
                	"                  ||   |   |  H  |\n"+
                	"                  ||'''|   |  O  |\n"+
                	"                  ||   |===|  R  |\n"+
                	"                  ||   `'''|=====|\n"+
                	"                  ||       `'''''`\n\n");
                return 1;
	}
	
}

int
display_banner(string str)
{
        if((str == "banner"))
	{
		write("You proudly display the "+ short(TO) +" high in "+
		"the air.\n\n"+
                	"                  ()__\n"+
                	"                  ||  Z____\n"+
                	"                  ||   |   Z______\n"+
                	"                  ||   |   |  K  |\n"+
                	"                  || C |   |  H  |\n"+
                	"                  || L |   |  A  |\n"+
                	"                  || A | O |  L  |\n"+
                	"                  || N | F |  A  |\n"+
                	"                  || S |   |  K  |\n"+
                	"                  ||   |   |  H  |\n"+
                	"                  ||'''|   |  O  |\n"+
                	"                  ||   |===|  R  |\n"+
                	"                  ||   `'''|=====|\n"+
                	"                  ||       `'''''`\n\n");
		
                say(QCTNAME(TP)+" proudly displays the "+short(TO)+ " "+
                "high in the air.\n\n"+
                	"                  ()__\n"+
                	"                  ||  Z____\n"+
                	"                  ||   |   Z______\n"+
                	"                  ||   |   |  K  |\n"+
                	"                  || C |   |  H  |\n"+
                	"                  || L |   |  A  |\n"+
                	"                  || A | O |  L  |\n"+
                	"                  || N | F |  A  |\n"+
                	"                  || S |   |  K  |\n"+
                	"                  ||   |   |  H  |\n"+
                	"                  ||'''|   |  O  |\n"+
                	"                  ||   |===|  R  |\n"+
                	"                  ||   `'''|=====|\n"+
                	"                  ||       `'''''`\n\n");
                return 1;
	}
	
}

int
extend_banner(string str)
{
        if((str == "banner"))
	{
		write("You proudly extend the "+ short(TO) +" forward in "+
		"the air.\n\n"+
                	"                  ()__\n"+
                	"                  ||  Z____\n"+
                	"                  ||   |   Z______\n"+
                	"                  ||   |   |  K  |\n"+
                	"                  || C |   |  H  |\n"+
                	"                  || L |   |  A  |\n"+
                	"                  || A | O |  L  |\n"+
                	"                  || N | F |  A  |\n"+
                	"                  || S |   |  K  |\n"+
                	"                  ||   |   |  H  |\n"+
                	"                  ||'''|   |  O  |\n"+
                	"                  ||   |===|  R  |\n"+
                	"                  ||   `'''|=====|\n"+
                	"                  ||       `'''''`\n\n");
		
                say(QCTNAME(TP)+" proudly extends the "+short(TO)+ " "+
                "forward in the air.\n\n"+
                	"                  ()__\n"+
                	"                  ||  Z____\n"+
                	"                  ||   |   Z______\n"+
                	"                  ||   |   |  K  |\n"+
                	"                  || C |   |  H  |\n"+
                	"                  || L |   |  A  |\n"+
                	"                  || A | O |  L  |\n"+
                	"                  || N | F |  A  |\n"+
                	"                  || S |   |  K  |\n"+
                	"                  ||   |   |  H  |\n"+
                	"                  ||'''|   |  O  |\n"+
                	"                  ||   |===|  R  |\n"+
                	"                  ||   `'''|=====|\n"+
                	"                  ||       `'''''`\n\n");
                return 1;
	}
	
}

void
init()
{
	mixed tmp;
	::init();
	add_action(wave_banner, "wave");
	add_action(display_banner, "display");
	add_action(extend_banner, "extend");
	
	if (!living(environment()))
	return;
	setuid(); seteuid(getuid());
	tmp = (string)SERVER->query_clan(ENV(TO)->query_real_name());
	if (!strlen(tmp))
	{
		set_adj( tmp = ({"bright green","black"}) );
		set_short("weathered celtic banner");
		set_pshort("weathered celtic banners");
	}
	else
	{
		set_adj(tmp = (string)SERVER->query_clan(tmp)[CLAN_CLRS]);
		set_short(implode(tmp, " and ") + " banner");
		set_pshort(implode(tmp, " and ") + " banners");
	}
	add_adj("weathered");
	set_long("          This weathered banner has it's edges\n"+
	"          trimmed " + (tmp[0] == "bright" ? "a bright green stripes" : tmp[0]) + " "+
	"with the background\n          dyed "+
	(tmp[1] == "black" ? "black" : tmp[1]) + ".\n\n"+
                	"                  ()__\n"+
                	"                  ||  Z____\n"+
                	"                  ||   |   Z______\n"+
                	"                  ||   |   |  K  |\n"+
                	"                  || C |   |  H  |\n"+
                	"                  || L |   |  A  |\n"+
                	"                  || A | O |  L  |\n"+
                	"                  || N | F |  A  |\n"+
                	"                  || S |   |  K  |\n"+
                	"                  ||   |   |  H  |\n"+
                	"                  ||'''|   |  O  |\n"+
                	"                  ||   |===|  R  |\n"+
                	"                  ||   `'''|=====|\n"+
                	"                  ||       `'''''`\n\n");
}
