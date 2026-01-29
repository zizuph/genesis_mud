/**********************************************************************
 * - shadow.c                                                       - *
 * - Shadow for Thanar race guild                                   - *
 * - Created by Damaris@Genesis 3/2004                              - *
 **********************************************************************/
#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_race_sh";

#include "guild.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <alignment.h>

static private mixed data;

public int
query_guild_tax_race()		{ return GUILD_TAX; }

public string
query_guild_style_race()	{ return GUILD_STYLE; }

public string
query_guild_name_race()		{ return GUILD_NAME; }

public string *
query_guild_trainer_race()
{
    return ({ (ROOM + "train") });
}

object
compare_stats(object ob1, object ob2)
{
    /* Returns the bigger stats of the two players */
    if (ob1->query_average_stat() >= ob2->query_average_stat())
        return ob1;
    return ob2;
}

public int
query_guild_family_name()	{ return 1; }

public string
compose_thanar_title()
{
   int sz, rank, tsz, title, stat;

   stat = shadow_who->query_base_stat(SS_RACE);

   if(stat > 70)
   {
      rank = stat-70;
      sz = sizeof(TITLES);
      rank = rank/(30/sz);
      return TITLES[MAX(MIN(rank, sz-1), 0)];
   }

   sz = sizeof(RANK);
   rank = stat / (70/sz);
   tsz = sizeof(TITLE1);
   title = shadow_who->query_average_stat() / (150/tsz);

   return TITLE1[MAX(MIN(title, tsz-1), 0)] + " " + 
      RANK[MAX(MIN(rank, sz-1), 0)]
   ;
}

public string
query_guild_title_race()
{
   object *obs,me;
   string str,title;
   int i;
    if (!sizeof(data))
	return "";

    str = data[FNAME] + (data[CNAME] ?
      " of the " + data[CNAME] + " Coven, " : ", ");
 
   
   title = compose_thanar_title();

   if(title == TITLES[sizeof(TITLES)-1])
   {
      obs = filter(users(), &operator(==)(title, ) @
         &->compose_thanar_title()
      );
       for(i=0;i<sizeof(obs);i++)
       {
          if(compare_stats(shadow_who,obs[i]) != shadow_who)
            {
                if(data[SPEC] == 1)
                return str+title+" and "+LIBRARY_TITLE;
             else
                return str+title+" of Thanar";
            }
              
       }
      return str+SPECIAL_TITLE;
   }

    if(data[SPEC] == 1) // guild librarian
    {
        return str +title+" and "+LIBRARY_TITLE;
    }  
      
   return str+title+" of Thanar";
}

public int
leave_guild_race()
{
    int tmp;
    object ob;

    shadow_who->catch_tell("You are no longer a member of the " +
      GUILD_NAME + ".\n");

    shadow_who->remove_cmdsoul(SOUL);
    shadow_who->update_hooks();
    shadow_who->clear_guild_stat(SS_RACE);
    shadow_who->setup_skill_decay();
    shadow_who->remove_subloc(GUILD_SUBLOC);

    while(ob = present(OBJECT_ID, shadow_who))
	ob->remove_object();

    if (shadow_who->query_default_start_location() == STARTLOC)
	shadow_who->set_default_start_location(shadow_who->query_def_start());

    SERVER->remove_member(shadow_who->query_real_name());

    SCROLLING_LOG(LOG + "leave",
      capitalize(shadow_who->query_real_name()) +
      " left the " + GUILD_NAME + ". <--");

    return remove_guild_race();
}

private mixed
acceptable_member(object who)
{
    if(who->query_race() != "human" || -1 == member_array(who->query_race_name()
        , VALID_SUBRACES) )
    {
	return "Only humans may join the " + GUILD_NAME + "!\n";
    }
    return 1;
}

public int
query_guild_keep_player(object ob)
{
    mixed why;

    if (stringp(why = acceptable_member(ob)))
    {
	tell_object(ob, why);
	set_alarm(2.0, 0.0, leave_guild_race);
    }

    return 1;
}

private void
init_guild()
{
    /* This is to prevent server lookups for every 'who' command. */
    data = SERVER->query_member(shadow_who->query_real_name());
    shadow_who->add_cmdsoul(SOUL);
    shadow_who->update_hooks();
}

public void
update_thanar_shadow(void)
{
    data = SERVER->query_member(shadow_who->query_real_name());
}

public void
init_race_shadow(string arg)
{
    setuid();
    seteuid(getuid());
    set_alarm(1.0, 0.0, init_guild);
}

public int
add_race_shadow(object who)
{
    return shadow_me(who, "race", GUILD_STYLE, GUILD_NAME);
}
