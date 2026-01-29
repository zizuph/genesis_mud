/*
 *    shadow.c
 *
 * Guild shadow for the Amazon racial guild
 *
 * Baldacin@Genesis, Nov 2003   
 *
 */
 
inherit "/std/guild/guild_race_sh.c";
#include <ss_types.h>
#include <macros.h>
#include <ss_types.h>
#include "../defs.h"

/*
 * Function name: query_guild_tax_race
 * Description  : give the amount of tax the guild charges
 * Returns      : int - The tax amount
 */
public int
query_guild_tax_race()
{
    return TAX;
}

/*
 * Function name : query_guild_name_race
 * Description  : Standard function that returns the guild name.
 *                This will be used in such things as listing
 *                your guilds while meditating.
 * Returns       : string - the guild name
 */
public string
query_guild_name_race()
{
    return GUILD_NAME;
}

/*
 * Function name: query_guild_style_race
 * Description  : return the guild style for this guild
 * Returns      : string - the style
 */
public string
query_guild_style_race()
{
    return STYLE;
}

/*
 * Function name: query_guild_trainer_race
 * Description:   Return one or more references to the object that define
 *                sk_train_max for the player. The returned refernce can
 *                be a string reference, an object pointer or an array of
 *                those.
 * Returns:       See description.
 */
public mixed
query_guild_trainer_race()
{
	return TRAINING;
}

/* Function name: query_guild_title_race
 * Description  : Handles the guild title
 * Returns      : string - the title
 */
public string
query_guild_title_race()
{
    return SERVER->query_amazon_race_title(shadow_who);
}


/*
 * Function name: query_guild_not_allow_join_race
 * Description  : This is called when our member tries to join
 *                another guild. The type, style and name of the
 *                other guild is sent as argument and we can deny
 *                our member to join that guild if we want.
 *                This is also called each time a player logs on.
 *                Reasons for denial:
 *                - Tried to join another racial guild
 * Arguments    : object player - the player to test
 *                string type   - the guild type
 *                string style  - the guild style
 *                string name   - the guild name
 * Returns      : int 1 - if the player is denied
 *                    0 - if the player is allowed
*/
public int
query_guild_not_allow_join_race(object player, string type,
string style, string name)
{
    return ::query_guild_not_allow_join_race(player,
    type, style, name);
}

string
check_allowed(object who)
{
    if (who->query_gender() != 1)
    {
        return "You are not a female! We could never let "+
			"anything else defend our settlement!\n";
    }
    if ((who->query_race() != "human") &&
        (who->query_race() != "ghost"))
    {
        return "You are not a human! We could never let "+
			"anything else defend our settlement!\n";
    }

    return 0;    
}

void
leave_amazons(mixed reason = "")
{
    SERVER->leave_amazons(shadow_who, reason);  
}

/* function name: query_guild_keep_player
 * Description:   This gives you a chance to tell if you want to keep the
 *                the player when the shadow is autoloading when a player
 *                logs on.
 * Arguments:     player - the player
 * Returns:       1 - keep player, 0 - kick him out.
 */
static int
query_guild_keep_player(object ob)
{
    string reason = check_allowed(ob);
    
    if (stringp(reason))
    {
        
        set_alarm(1.0, 0.0, &leave_amazons(reason));
    }
    return 1;
    
}


void
init_member()
{
    setuid();
    seteuid(getuid());

    if (!objectp(shadow_who))
    {
        return;
    }
    
    shadow_who->add_subloc(AMAZON_SUB, this_object());                        	
    shadow_who->add_cmdsoul(SOUL);
    shadow_who->update_hooks();
    
    if (!present("amazon_race_token", shadow_who))
        clone_object(OBJ+"token")->move(shadow_who, 1);

    SERVER->register_age(shadow_who);
    
    if (SERVER->query_board_change() >= SERVER->query_board_notify(shadow_who))
    {
        write("\nThe Amazon guild board contains new information.\n\n");
        SERVER->register_board_notify(shadow_who);
    }
}

void
init_race_shadow(string str)   
{
    set_alarm(0.5, 0.0, &init_member());
}

public string *                                                                
parse_command_id_list()
{
    string *ret;
    ret = (string *)shadow_who->parse_command_id_list();
    return ret += ({"amazon"});
}


string
show_subloc(string subloc, object me, object for_obj)
{
    string str;
   
	if (subloc != AMAZON_SUB)
	return shadow_who->show_subloc(subloc, me, for_obj);

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";
   
    if (for_obj == me)
	str = "You have ancient and mystic symbols drawn on "+
	  "your body.\n";
    else
	str = capitalize(me->query_pronoun()) + " has ancient "+
	  "and mystic symbols drawn on "+me->query_possessive()+
	  " body.\n";
   
    return str;
}