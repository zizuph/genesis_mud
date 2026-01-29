/*
 * lizard_shadow.c
 * Shadow of the Lizardman Guild.
 * Modified from the Halfling guild in the Faerun
 * Mirandus, February, 2018
 */

// To test:
// Call *yourname add_autoshadow full/path/name

#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_lay_sh";
inherit "/lib/guild_support";

#include "lizards.h"
#include <language.h>
#include <stdproperties.h>
#include <composite.h>
#include <const.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/std/combat/combat.h"


#define JOINROOM (LIZGUILD + "join")
#define QEXC (shadow_who->query_combat_object())
#define SARMOUR (LIZGUILD + "saurian_skin")


// Prototypes
void            remove_racial_blind();
public void     update_vision(object room);
public void     racial_see_in_dark();
public status   racial_can_see_through_dark();

// Global Variables
static int      visioned_alarm, vision_timestamp;
static status   racial_eyes;
static object   skin_obj;

#define RACE    " Saurian"

private static string *sub_desc = ({
    "tiny claws",
    "short claws",
    "brittle claws",
    "undeveloped claws",
    "growing claws",
    "curved claws",
    "developing claws",
    "sharp claws",
    "menacing claws",
    "deadly claws",
    "savage claws",
    "vicious claws", 
    "intimidating claws", 
    "knifelike claws",
    "razor-sharp claws",
    "devestating claws",
    "lethal claws",
    });

private static string *titles = ({
    "Blooded" + RACE + " Runt", 
    "Growing" + RACE + " Runt", 
    "Fledgling" + RACE + " Runt", 
    "Learning" + RACE + " Gatherer", 
    "Blooded" + RACE + " Gatherer", 
    "Experienced" + RACE + " Gatherer", 
    "Learning" + RACE + " Hunter", 
    "Intrepid" + RACE + " Hunter", 
    "Blooded" + RACE + " Hunter", 
    "Brave" + RACE + " Hunter", 
    "Chosen" + RACE + " Warrior", 
    "Developing" + RACE + " Warrior", 
    "Brave" + RACE + " Warrior", 
    "Scarred" + RACE + " Warrior", 
    "New" + RACE + " Scout", 
    "Confident" + RACE + " Scout", 
    "Trusted" + RACE + " Scout", 
    "Ingenious" + RACE + " Scout", 
    "Valiant" + RACE + " Elder", 
    "Wise" + RACE + " Elder", 
    "Learned" + RACE + " Elder", 
    "Respected Gatherer of the" + RACE,
    "Respected Hunter of the"+ RACE, 
    "Respected Warrior of the"+ RACE, 
    "Respected Scout of the"+ RACE, 
    "Elder"+ RACE, 
    "Ancient"+ RACE, 
    "Wizened"+ RACE, 
    "Revered"+ RACE + " Shaman",
});

/*
 * Function name:   query_guild_tax_layman
 * Description:     Returns the tax for the Lizard Layman guild.
 * Returns:         int - the tax value
*/

nomask public int 
query_guild_tax_lay()
{
    return GUILD_TAX_LAY;
}

/*
 * Function name:   query_guild_name_lay
 * Description:     Returns the name of the layman guild
 * Returns:         string - the name
 */
nomask public string 
query_guild_name_lay()
{
    return "Lizard Fighters";
}

public object
query_saurian_skin()
{
    if (!objectp(skin_obj))
    {
        if (LOAD_ERR(SARMOUR))
            return 0;
        
        setuid();
        seteuid(getuid());
        
        skin_obj = clone_object(SARMOUR);
    }
    
    return skin_obj;
}


public status
racial_can_see_through_dark()
{
    object  room;
    int     natural,
            personal,
            artificial;
    
    room = environment(shadow_who);
    natural = room->query_prop(ROOM_I_LIGHT);
    personal = shadow_who->query_prop(OBJ_I_LIGHT);
    artificial = room->query_prop(OBJ_I_LIGHT);

    // Check if the room is naturally dark.
    if (natural < 1 && natural <= artificial)
    {
        //Check if you are using darkness items.
        if (personal < 0)
            return 0;
        
        // No magical interference.
        return 1;
    }
    
    return 0;
}

/*
 * Function name: racial_see_in_dark
 * Description  : Gives the player nightvision when circumstances allow.
 * Arguments    : None
 */
public void
racial_see_in_dark()
{
    if (!racial_eyes && racial_can_see_through_dark())
    {
        vision_timestamp = time();
        write("Your eyes adjust to the dark setting.\n");
        shadow_who->inc_prop(LIVE_I_SEE_DARK, 1);
        racial_eyes++;
    }
}

public void
update_light(int recursive)
{
    shadow_who->update_internal(recursive);
    shadow_who->catch_msg("You blink your eyes.\n");
}

/*
 * Function name: remove_blind
 * Description  : This is the function that actually decreases the blind
 *                prop of the player. We use dec_prop so that if they are
 *                blinded by another source it doesn't remove that too.
 * Arguments    : None
 *
 */
void
remove_racial_blind()
{
    shadow_who->dec_prop(LIVE_I_BLIND,1);
    write("Your eyes have adjusted to the light.\n");
}

/*
 * Function name: update_vision
 * Description  : Determines what should happen with the players vision
 *                depending on what environment they enter. Also calculates
 *                how long for their vision to return to normal after being
 *                in the dark for a while.
 * Arguments    : Object room - The environment of the player
 */
public void
update_vision(object room)
{
    int light = room->query_prop(ROOM_I_LIGHT);
    
    if (racial_eyes)
    {
        if (light < 1 && racial_can_see_through_dark())
            return;
                
        //How long do they get blinded for based on how long they were in
        //the dark.
        float timer = itof(max(5, min(25, (time() - vision_timestamp) / 10)));
        
        //we use inc_prop so that it just adds to what might already be there.
        shadow_who->inc_prop(LIVE_I_BLIND,1);
        write("Your eyes need to adjust to the brightness after the time "
        +"in the dark.\n");
        set_alarm(timer, 0.0, &remove_racial_blind());
        
        //We use dec_prop so it doesn't remove all sources
        shadow_who->dec_prop(LIVE_I_SEE_DARK, 1);
        racial_eyes--;
        return;
    }
    
    if (visioned_alarm)
    {
        remove_alarm(visioned_alarm);
        visioned_alarm = 0;
    }
    
    //Adjusts the players eyes to see in the dark.
    if (light > 0 || shadow_who->query_prop(LIVE_I_BLIND) > 0)
        return;
    
    if (racial_can_see_through_dark())
    {
        write("Your eyes will need some time to adjust to the darkness\n");
        visioned_alarm = set_alarm(5.0, 0.0, &racial_see_in_dark());
        return;
    }
    
    write("The light in this room is affected by magic. You eyes cannot adapt properly.\n");
}

/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 *
 */
public void
enter_env(object dest, object from)
{
    shadow_who->enter_env(dest, from);
    update_vision(dest);
}

public mixed
wear_arm(object armour)
{
    int result = shadow_who->wear_arm(armour);
    
    if (query_saurian_skin())
        skin_obj->update_saurian_skin();
    
    return result;
}

public mixed
remove_arm(object armour)
{
    int result = shadow_who->remove_arm(armour);
    
    if (query_saurian_skin())
        skin_obj->update_saurian_skin();
    
    return result;
}

public void
update_armour(object armour)
{
    shadow_who->update_armour(armour);
    if (query_saurian_skin() == armour)
    {
        return;
    }
    if (query_saurian_skin())
        skin_obj->update_saurian_skin();
}

public string
race_sound()
{
    return "hisses";
}

public string
actor_race_sound()
{
    return "hiss";
}

/* Function name: query_saurian_level
 * Description:   Get the players numerical guild level
 * Returns:       The numeric guild level
 */
public int
query_saurian_level()
{
    return shadow_who->query_stat(SS_LAYMAN) / 7;
}

/*
 * Function name: query_guild_family_name
 * Description  : If the guild consists of families that give their members
 *                a family name, this function should return true. It
 *                moves the article 'the' to the occupational title of
 *                the member giving:
 *                "<race title>, the <occ title> and <lay title>"
 *                if the player is a member of all major guild types.
 * Returns      : int - true if the function query_guild_title_race()
 *                      returns the family name and not a normal guild
 *                      title.
 */
public int
query_guild_family_name()
{
    string surname = SURNAME_MANAGER->query_saurian_surname(shadow_who);

    if(surname)
      return 1;
    else
      return 0;
}


/* Function name: query_guild_title_lay
 * Description:   We change the title of our members depending on their level
 * Returns:       The title
 */
public string
query_guild_title_lay()
{
   int stat;
   mixed title;

   string surname = SURNAME_MANAGER->query_saurian_surname(shadow_who);

   setuid();
   seteuid(getuid());

   if (!sizeof(titles))
   {
       return "";
   }

   stat = min(sizeof(titles) - 1, query_saurian_level());

   if(surname)
   {
      title = capitalize(surname) + ", the " + titles[stat];
   }
   else
   {
      title = titles[stat];
   }

   return title;
}

/* 
 * Function name: query_guild_skill_name
 * Description:   Give a names for the guild's special skills
 * Arguments:     type - the number of the skill
 * Returns:	  0 if no skill of mine, else the string.
 */
 mixed
 query_guild_skill_name(int type)
 {
     if (type == SS_GUILD_SPECIAL_SKILL)
     {
     return "disembowel";
     }
     return 0;
 }

 string show_subloc( string subloc, object me, object for_obj )
{
    
    int sub_level;
    string str, subclaws;
    mixed clawstr;
    sub_level = min(sizeof(sub_desc) - 1, query_saurian_level());
    subclaws = sub_desc[sub_level];
    
    if (subloc != LIZARD_S_SUBLOC)
    {
        return shadow_who->show_subloc( subloc, me, for_obj );
    }
    if (me->query_prop( TEMP_SUBLOC_SHOW_ONLY_THINGS ))
    {
        return "";
    }
    if (for_obj == me)
    {
        str = "Your hands have ";
    }
    else
    {
        str = capitalize( me->query_possessive() )+ " hands have ";
    }

    clawstr = str + subclaws+".\n";

    return clawstr;
}

 void
 init_guild_member()
 {
    object who = query_shadow_who();
    int news;

    setuid();
    seteuid(getuid());

    if (news)
    {
        shadow_who->catch_tell("\n\nThere is some news about the Saurians. " +
            "See 'help saurian news' for more information.\n\n");
    }
    
    //Add the specifics of the guild
    
    who->add_subloc(LIZARD_S_SUBLOC, this_object());
    
    // Load the object an move it to the player if successful.
    if (query_saurian_skin())
        skin_obj->init_saurian_skin(shadow_who);
    
        
    /* add the guild's soul to the player */
    who->add_cmdsoul(GUILD_SOUL);
    who->set_race_name("saurian");
    
    who->update_hooks();
}


/*
 * Function name: init_lay_shadow()
 * Description:   This function is called from autoload_shadow and may
 *                be used to initialize the shadow when it's loaded.
 * Arguments:     The argument string sent to autoload_shadow.
 */
 void init_lay_shadow(string arg)
 {
     /* delay for a moment so that the player completes all
      * of login before we continue
      */
     set_alarm(1.0, 0.0, init_guild_member);
 }

 /* 
 * Function name: add_lay_shadow
 * Description:   Shadow an object with this shadow
 * Arguments:     object who - the object to shadow
 * Returns:       as shadow_me in /std/guild/guild_base.c
 */
int add_lay_shadow(object who)
{
    return shadow_me(who, "layman", GUILD_STYLE_LAY, GUILD_NAME_LAY);
}

/*
 * Function name: remove_lay_member
 * Description:   remove this member from the guild
 */
 void
 remove_lay_member()
 {
     object who = query_shadow_who();
     /* Remove special skills */ 
     who->remove_skill(SS_GUILD_SPECIAL_SKILL);
     /* Clear the player's guild stat */
     who->clear_guild_stat(SS_LAYMAN);
    /* Remove the guild soul */
    who->remove_cmdsoul(GUILD_SOUL);
    if (objectp(skin_obj))
    {
        skin_obj->remove_object();
    }
    who->update_hooks();
    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_lay();
}