#pragma strict_types
 
inherit "/std/guild/guild_occ_sh";
inherit "/cmd/std/command_driver";
#include "defs.h"
#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define LEVEL_BY_GUILD_STAT
#define QSW query_shadow_who()
#define SET(x, y) if (QSW->query_skill(x) > y) \
      (y < 1 ? QSW->remove_skill(x) : QSW->set_skill(x, y))
 
 /* Standard functions for any occupational guild */
int query_guild_tax_occ() { return TAX; }
string query_guild_style_occ() { return GUILD_STYLE; }
string query_guild_name_occ() { return GUILD_NAME; }
string query_def_post() { return ("/d/Cirath/chukel/ciubori/houses/post"); }
public mixed query_guild_trainer_occ()
        { return "/d/Cirath/guilds/barbarians/room/btr"; }

     /* Pre-declaration of important functions */
varargs void kick_out_barb(int spare);
        
int
query_guild_keep_player(object ob)
{
    	ob->add_subloc("barb_subloc", this_object());
	set_alarm(1.0, 0.0, "check_barb", ob);    
    	return 1;
}

void
check_barb(object obp)
{	
    	string name = obp->query_real_name();
    	 
    	obp->catch_msg("Hail true barbarian!\nHail Crom!\nGreet thy king!\n"); 
    	
    	if(!present(BRAC_ID, obp))
        	(MANAGER)->give_brac(obp);
    	    	
    	if (member_array(BARB_SOUL, obp->query_cmdsoul_list()) < 0)
    	{
        	obp->add_cmdsoul(BARB_SOUL);
        	obp->update_hooks();
    	}    	
}  

/* Function name: query_guild_not_allow_join_occ
 * Description:   Check if we allow that the player joins another guild.
 * Arguments:     player - the player
 *                type, style, name - the type, style and name of the
 *                intended guild.
 * Returns:       1 if we do not allow, else 0
 */  
 
int
query_guild_not_allow_join_occ(object player, string type, string style, string
name)
{
    	if (::query_guild_not_allow_join_occ(player, type, style, name))
        	return 1;

    	notify_fail("We Barbarians don't want mages in our ranks.\n");
    	if (style == "magic")
        	return 1;
   	notify_fail("We Barbarians don't want wise asses in our ranks.\n");
    	if (style == "psionicts")
        	return 1;    
            
    	return 0;
}

string
query_clan_name(object ob)
{
  	if(ob->query_skill(SS_BARB_SCORE) == 1)      return "White Eagle Clan";
  	else if(ob->query_skill(SS_BARB_SCORE) == 2) return "Mammoth Clan";

  	return "*no clan*";
}

/* Function name: query_barbarian_level
 * Description:   Get the players numerical guild level
 * Returns:       The numeric guild level
 */
int
query_barb_level()
{
#ifdef LEVEL_BY_GUILD_STAT
  	return shadow_who->query_base_stat(SS_OCCUP) / 15;
#else
  	return shadow_who->query_base_skill(SS_BARB_SCORE);
#endif
}

/*
 * Function name: query_guild_title_occ
 * Description:   Gives the guild title.
 * Returns:       Guess what.
 */

string query_guild_title_occ()
{
    	int stat, max_stat, cnslot;
    	object this_barb = shadow_who;
 
    	if (present(COUN_BRAC_ID, this_barb))
    	{
        	if (present(HIGH_BRAC_ID, this_barb)) return BARB_HIGH_TITLE;
        
        	cnslot=QUERY_COUN_MEMB(lower_case(this_barb->query_name()));
        	if (cnslot>0) return BARB_ELDER_SLOTS[cnslot-1]+" "+BARB_ELDER_TITLE;
    	}
     	
    	stat = query_barb_level();
    	max_stat = sizeof(MAIN_TITLES) - 1;
    	if (stat < 0) stat = 0;
    	else if (stat > max_stat) stat = max_stat;
 
    	return (MAIN_TITLES[stat]) + " Barbarian";
}

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *                me      - I
 *                for_obj - The looker
 * Returns:       The string the looker shall see
 */
 
string
show_subloc(string subloc, object me, object for_obj)
{
    	if (subloc != "barb_subloc")
        	return shadow_who->show_subloc(subloc, me, for_obj);
        
    	if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        	return "";    

	if (me->query_skill(SS_BARB_SCORE)==1)
	{
    		return(for_obj == me ? "You belong to the White Eagle Clan.\n" : 
    		CAP(me->query_pronoun()) + " is a White Eagle Clan member.\n");
	}
	else if (me->query_skill(SS_BARB_SCORE)==2)
	{
    		return(for_obj == me ? "You belong to the Mammoth Clan.\n" : 
   		CAP(me->query_pronoun()) + " is a Mammoth Clan member.\n");
	}
	else
	{
 		return(for_obj == me ? "You smell like a true Barbarian.\n" :
 		CAP(me->query_pronoun()) + " smells like a true Barbarian.\n");
	}
}

mixed
query_guild_skill_name(int type)
{
  	if (type == SS_SLAYING)         return "slaying";
  	else if (type == SS_BONKING)    return "headbut enemy";
  	else if (type == SS_BARB_SCORE) return "";
  	else if (type == SS_CHOPPING)   return "chop enemy";
  	else if (type == SS_BLOCKING)   return "block enemy";
  	else if (type == SS_HOLDING)    return "hold enemy";
  	else if (type == SS_STABBING)   return "stab enemy";

  	return 0;
}

varargs void
kick_out_barb(int spare)
{
    	object brac;
    	string str;
    	int i;
  
    	while(brac = present(BRAC_ID, shadow_who)) brac->remove_object();
 
    	shadow_who->remove_cmdsoul(BARB_SOUL);
    	shadow_who->update_hooks();
 
    	SET(SS_SLAYING, 0);
    	SET(SS_BONKING, 0);
    	SET(SS_CHOPPING, 0);
    	SET(SS_BLOCKING, 0);
    	SET(SS_HOLDING, 0);
    	SET(SS_STABBING, 0);
    	SET(SS_BARB_SCORE, 0);
    	TP->remove_prop(BARB_LEAVE);
    	
    	setuid(); seteuid(getuid());      
    	shadow_who->catch_msg("You are no longer a herder.\n"); 
       
  	//  if(!IS_WIZ(shadow_who)&&extract(str=shadow_who->query_real_name(),-2)!="jr")
  	//  add when guild is ready for playertesting
  
    	write_file(BARBQUIT,TP->query_real_name()+" left Barbarians "+
            	extract(ctime(time()),4,15)+"\n");
    	tell_room(TO,LM);
	tell_room("/w/luther/workroom",LM);
	
      	shadow_who->setup_skill_decay();
    	shadow_who->clear_guild_stat(SS_OCCUP);
    	remove_guild_occ();
}

#ifndef LEVELS_BY_GUILD_STAT
int 
set_skill(int skill, int level)
{
    	if (skill == SS_BARB_SCORE && !IS_WIZ(previous_object()) && 
                 !previous_object()->query_barb_challenge())
    	return 0;
 
    	return shadow_who->set_skill(skill, level);
}
#endif