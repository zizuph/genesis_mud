/*      This is an object of the Calian guild in the crystalline palace.

    coder(s):   Glykron
    history:
                 1.10.93    fix melting                     Glykron
                 1. 5.93    commands into cmdsoul           Glykron
                 22.12.93   emote_list function added       Maniac
                 1.5.94     "if shadow change" code added   Maniac
                   6.94     tell treated as spell           Maniac

    purpose:    to give the projection ability and load the cmdsoul
    exits:      all to square

    objects:    cmdsoul

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

#define GUILD_NAME "Calian warrior's guild"
#define NECK_SUBLOC "neck"
#define OLD_SHADOW "/d/Dville/glykron/palace/guild_sh:"
#define NEW_SHADOW "/d/Calia/tmp/glykron/palace/guild/guild_shadow:"


string team_title = "";
string *poss_titles = ({ " Four Horsemen",
                         " Hit Squad",
                         " Dogs of War", 
                         " Protectors of Calia",
                         " Major Monster Mashers",
                         " Lightning Raiders" });

int
is_calian(object living)
{
    return living->query_guild_name_occ() == GUILD_NAME;
}


int
is_worn()
{
    return query_prop(OBJ_M_NO_DROP) != 0;
}

/*
 * Function name: project_to
 * Description:   executes the project to command
 * Arguments:     str - predicate
 * Returns:       success
 */
int
project_to(string str)
{
    string prep, receiver_name, message;
    object tp, receiver;
    int length;

    if (!str) return 0;

    if (explode(str, " ")[0]  != "to")
        return 0;

    if (sscanf(str, "%s %s", prep, str) != 2)
    {
        NF("Project to whom ?\n");
        return 0;
    }

    if (sscanf(str, "%s %s", receiver_name, message) != 2)
    {
        NF("Project what ?\n");
        return 0;
    }

    NF("Nothing happens.\n");
    tp = TP;
    if (!is_calian(tp))
        return 0; /* project to cannot be used by non-members */


    if (tp->query_mana() < 10)
    {
        NF("You don't feel mentally strong enough to communicate the " +
            "message.\n");
        return 0;
    }

    receiver = find_living(receiver_name);
    if (!receiver || !present("Calia_medallion", receiver))
    {
        NF("Your message is not received.\n");
        return 0;
    }
 

    if (!is_calian(receiver))
    {
        NF("The mind of that player " +
           "is not receptive to your thoughts.\n");
        return 0;
    }

    tp->add_mana(-10);


    /* treat project to as a spell with small fail chance */

    if (tp->resolve_task(TASK_SIMPLE, ({TS_INT}) ) < 1)
    {
       NF("Your concentration lapses and your attempted project " +
          "fails.\n");  
       return 0;
    }

    message = capitalize(NAME) + " projects a thought to you:\n" +
        capitalize(message) + "\n";
    tell_object(receiver, message);
    write("Ok.\n");
    return 1;
}

int
wear(string str)
{
    if (str != "medallion")
        return 0;

    if (!present(THIS, TP))
    {
        NF("You don't have it!\n");
        return 0;
    }

    if (query_prop(OBJ_M_NO_DROP))
    {
        NF("You are already wearing it!\n");
        return 0;
    }

    add_prop(OBJ_M_NO_DROP,
        "You cannot drop the medallion while you are wearing it!\n");
    TP->add_subloc(NECK_SUBLOC, THIS);
    write("You wear the medallion.\n");
    say(QCTNAME(TP) + " wears the medallion.\n");
    return 1;
}

int
remove(string str)
{
    if (str != "medallion")
        return 0;

    if (!present(THIS, TP))
    {
        NF("You don't have it!\n");
        return 0;
    }

    if (!query_prop(OBJ_M_NO_DROP))
    {
        NF("You are not wearing it!\n");
        return 0;
    }

    remove_prop(OBJ_M_NO_DROP);
    TP->remove_subloc(NECK_SUBLOC);
    write("You remove the medallion.\n");
    say(QCTNAME(TP) + " removes the medallion.\n");
    return 1;
}

void
leave_env(object dest, object old)
{
    TP->remove_subloc(NECK_SUBLOC);
    ::leave_env(dest, old);
}

void
check_tax(object tp)
{
    if (!is_calian(tp))
        return;

    tp->set_guild_pref(SS_OCCUP, GUILD_TAX);
    tp->set_learn_pref(TP->query_learn_pref(-1));
}

/* Add a command soul to the player and activate its commands. */
void
check_soul(object tp)
{
    if (!is_calian(tp))
        return;

    tp->add_cmdsoul(CALIAN_SOUL);
    tp->update_hooks();
}


/* make sure player's shadow autoshadow list is correct */
void
check_shadow(object tp)
{
  string *sh_list;
  object shadow;

    sh_list = tp->query_autoshadow_list();
    if (member_array(OLD_SHADOW, sh_list) > -1)
    {
      tp->remove_autoshadow(OLD_SHADOW);
      tp->add_autoshadow(NEW_SHADOW);   
      seteuid(getuid());
      shadow = clone_object(GUILD_SHADOW);
      shadow->shadow_me(tp, GUILD_TYPE, GUILD_STYLE, GUILD_NAME);
      write_file("/d/Calia/tmp/glykron/palace/guild/added", 
      tp->query_name() + " added.\n");
    }
}



/* Give a command list should a Calian type "clist" */
int
cmd_list()

{
   object tp;

   tp = TP;
   if (is_calian(tp))  {
     tp->catch_msg("You can use the following emotes:\n" +
      "-cshake <player(s)>       - give player(s) a Calian handshake.\n" +
      "-clook <player> <message> - give player a look meaning <message>. " + 
      " Calians in the room will understand it, non-Calians will not.\n" +
      "-cwarn                    - make a warning to potential adversaries." +
      "\n-cwar <warcry>            - give a war cry <warcry>.\n" +  
      "-cpraise <player> <str>   - you praise <player> for being such a " +
      "<str> e.g. 'fine warrior'\n" +
      "-ccurse <player> <str>    - you curse <player> for being such a " +
      "<str> e.g. 'feeble coward'\n" +
      "-celeb                    - do one of many possible celebrations\n" +
      "-csong                    - sing one of many possible brief songs\n" +
       "\n");


     tp->catch_msg("\nYou can use the following other commands:\n" +
      "-warriors                  - get a list of active calians.\n" +
      "-swarm <player>            - swarm a player you are fighting.\n" +
      "-move behind <player>      - move behind a player.\n" +
      "-project to <player> <msg> - project a message <msg> to a player.\n" +
      "-cteam <number from 0 - 5> - select a Calian team title.\n" +
      "-cteam                     - says what your team title is.\n" +
      "\n"); 
   }
   else 
     tp->catch_msg("You are not a Calian!\n");

   return 1; 
}


/* The function team_title(str) is intended to be used to set
   a special team title for the Calian should s/he desire, by 
   selecting (using a number) from the preset titles in *poss_titles.
   Typing simply "cteam" results in the player being told what
   team title, if any, has previously been set.
*/
int
cteam(string str)

{
int select;

if (!is_calian(TP))
  return 1;

if (!str)
  {
    if (team_title == "") TP->catch_msg("You've set no team title.\n");
    else
       TP->catch_msg("Your team title is: " + team_title + "\n");
    return 1;
  }
else
  {
   select = atoi(str);
   if ((select < 0) || (select > 5))
     {
       NF("The number chosen is not in the range 0 - 5.\n");
       return 0;
     }
   team_title = TP->query_name() + "'s" +
                                        poss_titles[select];
   TP->catch_msg("Your team title is now set to: " + team_title + "\n");
    return 1;
  }
}


/* query_team_title() returns the team title set for the player */
string
query_team_title()
{
  return team_title;
}



void
init()
{
    ::init();
    add_action("project_to", "project");
    add_action("wear", "wear");
    add_action("remove", "remove");
    add_action("cmd_list", "clist");
    add_action("cteam", "cteam");
    call_out("check_shadow", 1, TP);
    call_out("check_tax", 1, TP);
    call_out("check_soul", 1, TP);

}

/* To prevent this object from recovering automatically, we add this line
 * to make sure it does not recover.
 */
string query_recover() { return 0; }


string
query_auto_load()
{
    if (!query_prop(OBJ_M_NO_DROP)) {
    add_prop(OBJ_I_NO_DROP, 1);
    call_out("remove_prop", 1, OBJ_I_NO_DROP);
    }
    return MASTER;
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
    int myself;

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (subloc != NECK_SUBLOC)
        return me->show_subloc(subloc, me, for_obj);

    myself = for_obj == me;
    return (myself ? "You are" : capitalize(me->query_pronoun()) + " is") +
        " wearing a medallion around " +
        (myself ? "your" : me->query_possessive()) + " neck.\n";
}

void
create_object()
{
    set_name( ({ "medallion", "Calia_medallion" }) );
    set_adj( ({ "calian", "Calian" }) );
    set_short("medallion of Calia");
    set_pshort("medallions of Calia");
    set_long(
        "This medallion bears an insignia of someone thinking very hard.  " +
        "Also, the command \"project to\" is engraved there.\n" +
        "Calians may obtain a list of commands by typing 'clist'." +
         "\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
}

void
enter_env(object dest, object old)
{
    object *obs;
    int i, change;

    obs = all_inventory(dest);

    change = 0;
    for (i = 0; i < sizeof(obs); i++)
    {
	if (obs[i]->id("Calia_medallion") && obs[i] != this_object() &&
	    obs[i]->is_worn() == is_worn())
	{
	    obs[i]->remove_object();
	    change++;
	}
    }

    if (change)
	environment()->catch_msg("The medallions melt together!\n");
}
