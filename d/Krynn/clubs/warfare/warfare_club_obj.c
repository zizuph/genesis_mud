/* created by Arman 22 June 2018
 * 
 * This is the guild object for participants in the warfare system.
 *
 */
inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include "defs.h"

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <cmdparse.h>

/*prototypes*/
void soul(object ob);
public int valid_owner();

string *gColour = ({ "red", "blue", "green", "black", "white" });

string 
query_auto_load() 
{
    return MASTER_OB(TO);
}

void
check_if_owner_still_member()
{
    if (!environment() || !living(environment()))
	return;
    
    if (!IS_CLUB_MEMBER(TP))
    {
	remove_object();
    }
}

string
long_desc()
{
    string army = CLUB_MANAGER->query_warfare_army_name(TP);

    if(!army)
        return "This small circle of dark steel is a token held by " +
        "those who actively participate in the War of the Lance. " +
        "You may find out more about your role in this battle for " +
        "domination through <help krynn warfare>.\n";
    else
        return "This small circle of dark steel is a token held by " +
        "those who support the " +army+ " in the War of the Lance. " +
        "You may find out more about your role in this battle for " +
        "domination through <help krynn warfare>.\n";
}

/*
 * Function name: valid_owner
 * Description  : Checks whether the owner has the rights to this object
 */
public int 
valid_owner()
{
    object user = this_player();
    if (!IS_CLUB_MEMBER(user)) 
    {
        return 0;
    }

    return 1;
}

public void
update_warfare_object(object user)
{
    long_desc();
    user->remove_subloc("the_warfare_club");
    user->add_subloc("the_warfare_club", TO);
}

void
convert_warfare_army(object user, string new_army, string guild_army)
{
        if(new_army)
        {
            user->catch_msg("You change your steel blood chit from the " +
                CLUB_MANAGER->query_warfare_army_name(user)+ " to the " +
                CLUB_MANAGER->convert_warfare_army_name(new_army)+ ".\n");
            CLUB_MANAGER->set_warfare_army(user, guild_army);
            CLUB_MANAGER->add_krynn_war_player_stats(user, guild_army, 0, 0);

            update_warfare_object(user);
        }
}


/*
 * Function name: valid_army
 * Description  : Checks whether the owner has the rights to this object
 */
public void 
check_invalid_army()
{
    object user = this_player();
    string current_army = CLUB_MANAGER->query_warfare_army(user);
    string new_army, guild_army;

    // Check if a DA is supporting a non-DA army
    if (user->query_dragonarmy_occ_member() &&
        !(CLUB_MANAGER->query_warfare_dragonarmy(user))) 
    {
        guild_army = user->query_dragonarmy_division() + " dragon army";
        new_army = CLUB_MANAGER->convert_warfare_army_name(guild_army);

        convert_warfare_army(user, new_army, guild_army);
        return;
    }

    // Check if a DA is supporting a different DA army
    if (user->query_dragonarmy_occ_member()) 
    {
        guild_army = user->query_dragonarmy_division() + " dragon army";
        guild_army = CLUB_MANAGER->query_warfare_army_string(guild_army);

        if(guild_army != current_army)
        {
            new_army = CLUB_MANAGER->convert_warfare_army_name(guild_army);
            convert_warfare_army(user, new_army, guild_army);
            return;
        }
    }

    // Check if a Neidar is supporting a different army
    if (user->query_guild_name_occ() == "Dwarven Warriors of the Neidar Clan") 
    {
        guild_army = "Neidar Clan";

        if(guild_army != current_army)
        {
            new_army = CLUB_MANAGER->convert_warfare_army_name(guild_army);
            convert_warfare_army(user, new_army, guild_army);
            return;
        }
    }

    // Check if a Knight is supporting a different army
    if (user->query_guild_name_occ() == "Solamnian Knights") 
    {
        guild_army = "Knights";

        if(guild_army != current_army)
        {
            new_army = CLUB_MANAGER->convert_warfare_army_name(guild_army);
            convert_warfare_army(user, new_army, guild_army);
            return;
        }
    }

    // Check if an Elven Archer is supporting a different army
/*
    if (user->query_guild_name_occ() == "Ansalon Elvish Archers") 
    {
        guild_army = "Free People";

        if(guild_army != current_army)
        {
            new_army = CLUB_MANAGER->convert_warfare_army_name(guild_army);
            convert_warfare_army(user, new_army, guild_army);
            return;
        }
    }
*/

    // Check if a PoT is supporting a non-DA army
    if (user->query_guild_name_occ() == "Priests of Takhisis" &&
        !(CLUB_MANAGER->query_warfare_dragonarmy(user))) 
    {
        string colour = ONE_OF(gColour);
        guild_army = colour + " dragon army";
        new_army = CLUB_MANAGER->convert_warfare_army_name(guild_army);

        convert_warfare_army(user, new_army, guild_army);
        return;
    }

    // If the player no longer meets the requirements to support
    // that army
    if(!CLUB_MANAGER->query_valid_warfare_army(user, current_army))
    {
        guild_army = "Free People";

        new_army = CLUB_MANAGER->convert_warfare_army_name(guild_army);
        convert_warfare_army(user, new_army, guild_army);
        return;

    }

    // Check if a Throtyl Marauders aresupporting a non-DA army or
    // not free people
    if (user->query_guild_name_lay() == "Raiders of Throtyl" &&
        !(CLUB_MANAGER->query_warfare_dragonarmy(user))) 
    {
        if(current_army == "Free People")
            return;

        new_army = CLUB_MANAGER->convert_warfare_army_name("Free People");

        convert_warfare_army(user, new_army, guild_army);
        return;
    }

}

void
create_object()
{
    set_name("_warfare_club_object_");
    set_pname("_warfare_club_object_s");
    add_name("chit");
    add_adj("blood");
    add_adj("steel");
    set_short("steel blood chit");    
    set_long("@@long_desc");

    // Don't allow this to be sold.
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);                          
    add_prop(OBJ_M_NO_SELL, 1); 
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT); 
    
    // By setting this, players should not know that this is in their
    // inventory.
    // set_no_show();
    
    setuid();
    seteuid(getuid());
}

void
remove_guild_object()
{
    remove_object();
}

public void
enter_env(object ob, object from)
{
    ::enter_env(ob, from);
    mixed oblist;

    if (ob)
    {
	oblist = FIND_STR_IN_OBJECT("all _warfare_club_object_s", ob);
	oblist -= ({ 0, TO });
	if(oblist && sizeof(oblist) > 0)
	    set_alarm(2.0, 0.0, &remove_guild_object());
    }

    if (!interactive(ob) || from)
	return;

    if(!valid_owner())
    {
        set_alarm(0.1, 0.0, &remove_guild_object());
        return;
    }

    set_alarm(0.5, 0.0, &check_invalid_army());
    
    ob->add_subloc("the_warfare_club", TO);

    set_alarm(1.0, 0.0, &soul(ob));
    
    setuid();
    seteuid(getuid());
}


/*
 * Function name: soul
 * Description:   Add the cmdsoul to the member
 */
void
soul(object ob)
{
    int i;
    string *souls;
    
    setuid();
    seteuid(getuid(TO));

    souls = ob->query_cmdsoul_list();
    for (i = 0; i < sizeof(souls); i++)
	ob->remove_cmdsoul(souls[i]);
    for (i = 0; i < sizeof(souls); i++)
	if (souls[i] != CLUB_SOUL)
	    ob->add_cmdsoul(souls[i]);
    ob->add_cmdsoul(CLUB_SOUL);
    ob->update_hooks();
}


string
show_subloc(string subloc, object me, object for_obj)
{
    string army;

    if (!IS_CLUB_MEMBER(me))
	return "";

    if (CLUB_MANAGER->query_warfare_subloc_incognito(TP))
	return "";

    army = CLUB_MANAGER->query_warfare_army_name(me);

    if (for_obj == me)
        return  "You are supporting the war efforts of the " +army+ ".\n";
    else
        return capitalize(me->query_pronoun()) + " is supporting the " +
            "war efforts of the "+army+".\n";    
}
