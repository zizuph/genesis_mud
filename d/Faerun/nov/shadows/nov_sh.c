/*
 *
 * Evil laymanguild. Based on the Necromancers of Velsharoon.
 *
 * 9/6/2004  -- Tilorop 
 */
 
 
inherit "/std/guild/guild_lay_sh";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <language.h>
#include "../nov.h"


#define TP  this_player() 
#define TO  this_object()
#define MAX_GUILD_LEVEL 10
#define MIN_GUILD_LEVEL 1



public int      query_guild_not_allow_join_lay(object player, string type, string style, string name);
static int      query_guild_keep_player(object ob);
public void     init_lay_shadow(string str);
public void     leave_nguild();


static string *titles = ({ "Initiate Student of Velsharoon",
    "Lesser Student of Velsharoon",
    "Student of Velsharoon",
    "Higher Student of Velsharoon",
    "Master Student of Velsharoon",
    "Lesser Arcanist of Velsharoon",
    "Arcanist of Velsharoon",
    "Higher Arcanist of Velsharoon",
    "Master Arcanist of Velsharoon",
    "Lesser Corrupter of Velsharoon",
    "Corrupter of Velsharoon",
    "Higher Corrupter of Velsharoon",
    "Master Corrupter of Velsharoon",
    "Lesser Heretic of Velsharoon",
    "Heretic of Velsharoon",
    "Higher Heretic of Velsharoon",
    "Master Heretic of Velsharoon",
    "Lesser Defiler of Velsharoon",
    "Defiler of Velsharoon",
    "Higher Defiler of Velsharoon",
    "Master Defiler of Velsharoon",
    "Minor Deathbringer of Velsharoon",
    "Deathbringer of Velsharoon",
    "Black Deathbringer of Velsharoon",
    "Master Deathbringer of Velsharoon",
});   


int
query_guild_level_lay()
{
		
    return MIN(MAX_GUILD_LEVEL, query_shadow_who()->query_stat(SS_LAYMAN) / 15);
}


int i_am_incognito = 1;

int
query_incognito()
{
  return i_am_incognito;
}

void
set_incognito(int i)
{
  i_am_incognito = i;
}


string 
query_guild_title_lay()
{
	
	if(query_incognito()) 
	{
		return "";
	}
	
	
	if (shadow_who->query_skill(PUNISHED) == 1)
	{
		return "Punished Student of Velsharoon";
	}
	
	if (shadow_who->query_skill(COUNCIL) == 1)
	{
		return "High Magus of Necromancy, Hand of Velsharoon";
	}
	
	if (shadow_who->query_skill(COUNCIL) == 2)
	{
		return "Arch Magus of Necromancy, Hand of Velsharoon";
	}
	
	if (shadow_who->query_stat(SS_LAYMAN) >= 395)
	{
		return "Master Deathbringer of Velsharoon";
	}

    return titles[query_guild_level_lay()];
}




 
public string 
query_guild_name_lay()
{
    return GUILDNAME; 
}


public string
query_guild_style_lay()
{
    return "magic"; 
}
 

public int
query_guild_tax_lay()
 {
    return TAX;
}


public mixed
query_guild_trainer_lay()
{       
    return NOV_DIR + "temple/ntrain";
}


public int
query_guild_not_allow_join_lay(object player, string type, string style, string name)
{
    if (::query_guild_not_allow_join_lay(player, type, style, name))
        return 1;
}


public int
query_guild_keep_player(object ob)
{
    return 1;
}


/*void
do_die(object killer)
{
    
    shadow_who->command("say Death means nothing to me, fool!");
    shadow_who->command("cackle");
    shadow_who->do_die(killer);
}*/


public void
check_alignment()
{   
    if (shadow_who->query_alignment() > -100)
    {
        shadow_who->write("Your alignment have surpassed what is tolerable " +
        "for any who serve Velsharoon!\nYou die!\n");
        //set_alarm(0.0, 0.0, &leave_nguild(shadow_who));        
    }
    
    else if (shadow_who->query_alignment() > -300)
    {
        shadow_who->write("Lord Velsharoon does not tolerate your alignment! Descend " +
        "swiftly or pay the ultimate price for Defiance!\n");
    }   
}

    
public string
show_subloc(string subloc, object me, object for_obj)
{
    string str;

    if (subloc != "Nov subloc")
    {
        return me->show_subloc(subloc, me, for_obj);
    }

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
        return "";
    }

    if (for_obj == me)
    {
        str = "You are";
    }
    else
    {
        str = capitalize(me->query_pronoun()) + " is";
    }

    return str + " a Necromancer of Velsharoon.\n";

}


public void
add_soul()
{
    shadow_who->add_cmdsoul(NOV_DIR + "souls/nov_soul");
    shadow_who->update_hooks();
}


public void
leave_nguild()
{
   object token1, token2;	
	
   shadow_who->remove_skill(ABILITY1);
   shadow_who->remove_skill(ABILITY2);
   shadow_who->remove_skill(COUNCIL);
   shadow_who->remove_skill(PUNISHED);
   shadow_who->remove_guild_lay();
   shadow_who->clear_guild_stat(SS_LAYMAN);
   shadow_who->remove_cmdsoul(NOV_DIR +"souls/nov_soul");
   NOV_MANAGER->remove_nov_member(shadow_who->query_name());
   shadow_who->update_hooks();
   
   if (present("_novtoken", shadow_who))
    {
    	token1 = "_novtoken"->query_short();
    	
        shadow_who->catch_msg("The "+token1+" vanishes into thin air.\n");
        "_novtoken"->remove_object();
    }
    
    if (present("_novec_token", shadow_who))
    {
    	token2 = "_novec_token"->query_short();
    	
        shadow_who->catch_msg("The "+token2+" magically disappear.\n");
        "_novec_token"->remove_object();
    }
}


public int
query_nov_memb()
{
   return NOV_MANAGER->query_nov_member(shadow_who->query_real_name());
}


public int 
is_nov()
{
   return 1;
}



public void
init_lay_shadow(string str)
{
        ::init_lay_shadow();
      
    shadow_who->add_subloc("Nov subloc", TO);
    set_alarm(0.0, 0.0, add_soul);
 

}


//string actor_race_sound() { return "say"; }
//string race_sound() { return "booms hollowly"; }


