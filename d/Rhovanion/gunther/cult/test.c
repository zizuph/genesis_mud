/*
** The surcoat of the Guardians of Light.
** This is the autoloading object of that guild.
** 
** By Gunther 940718.
*/ 

inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#define COAT_COLORS ({ "black", "brown", "gray", "dark-green", "dark-red",
		"dark-blue", "russet-colored", "light-green", "yellow", "light-red",
	   "light-blue", "white", "blinding white" })

create_armour()
{
	set_short("unadorned " + get_coat_color() + " surcoat");
	set_long("This is an unadorned " + get_coat_color() + " surcoat such "
		+"as those garments"
		+" often worn by Guardians of Light on pilgrimage. It is simple yet"
		+" somehow manages to stay clean and free from tears.\n");
	set_name("surcoat");
	set_adj("unadorned");
	
	set_ac(6);
	set_at(A_ROBE);
	
	add_prop(OBJ_I_NO_DROP, 1);
	add_prop(OBJ_I_NO_BREAK, 1);
	add_prop(OBJ_I_NO_SELL, 1);
	
	add_prop(OBJ_S_WIZINFO, "This is the autoloading guild object of the "
		+"Guardians of Light. It is unbreakable, undroppable and unsellable."
		+" It features one emote, wipe, and changes color depending on guild"
		+"stat.\n");
}
	
query_auto_load()
{
	return MASTER;
}

string
get_coat_color()
{
	object in;
	int n;

	in = environment(this_object());
	if(!in->query_prop(LIVE_I_IS)) return COAT_COLORS[0];
	if(in->query_guild_name() != "guardians") return COAT_COLORS[0];
	
	/* ok, our guy is valid. lets give them max color at 180 guild
		stat. as tax is high it wont take as long as it sounds. */
	
	n = in->query_stat(SS_OCCUP); 
	n /= 15;
	n ++;
	if(n < 1) n = 1;
	if(n >= sizeof(COAT_COLORS)) n = sizeof(COAT_COLORS) - 1;
	return COAT_COLORS[n];
}
		