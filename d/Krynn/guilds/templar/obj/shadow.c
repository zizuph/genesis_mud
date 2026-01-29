/*
 * The Templars of Neraka guild shadow.
 * Louie 2004
 */
inherit "/std/guild/guild_lay_sh";

#include "../local.h"
#include "titles.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <tasks.h>


/** prototypes **/
public nomask void init_templar_shadow();
public string player_can_join(object player);
int query_guild_level_lay();
public void remove_lay_member();
int query_templar_rank();

private int isFocused = 0;
int query_full_templar_member();

/*
 * Function:    query_guild_title_lay
 * Description: Find the title
 * Returns:     The title 
 */         
public string
query_guild_title_lay()
{
    object emb;
    int i = 0;
    string racename;
    string part1;
    
    if (emb = P(GUILD_OBJ_NAME, shadow_who))
    {
        i = emb->query_holder_level_lay();
    }
    
    racename = shadow_who->query_race_name();
    
    if (ADMIN->query_templar_rank(shadow_who) == TEMPLAR_RANK_BETRAYER)
    {
        return TEMPLAR_BETRAYER_TITLE;
    }

    if (ADMIN->query_templar_rank(shadow_who) > 0)
    {
        part1 = FULL_TEMPLAR_ADJS[i];
    } else
    {   
    
        if (racename == "gnome" ||
            racename == "hobbit" ||
            racename == "elf" ||
            racename == "dwarf")
        {
            part1 = BAD_TEMPLAR_RACE_ADJS[i];
        } else
        {   
            part1 = TEMPLAR_ADJS[i];
        }
    }
    
    return part1 +
        " "+
        TEMPLAR_RANKS[ADMIN->query_templar_rank(shadow_who)];    

}

/**
 * Figure out our level
 */
int
query_guild_level_lay()
{
    return MIN(GUILD_MAX_LEVEL, 
                (query_shadow_who()->query_stat(SS_LAYMAN) / 9));
    
}

/*
 * Standard Shadow stuff below
 */
    
public void
init_lay_shadow(string arg)
{
    setuid();
    seteuid(getuid());
    set_alarm(1.5, 0.0, &init_templar_shadow());
}

public nomask void
init_templar_shadow()
{
    object who = query_shadow_who();
    object mantle, evade_obj;
    int warning_align = GUILD_WARN_ALIGN;
    int min_align = GUILD_MIN_ALIGN;
    
    setuid();
    seteuid(getuid());
    
    if (objectp(mantle = clone_object(OBJ + "mantle")))
    {
        mantle->move(TP, 1);
    }

    // Clone the evade - stagger object.
    if(!P("_templar_evade__object_", who))
    {
        evade_obj = clone_object(OBJ+"tevade");
        evade_obj->set_effect_caster(who);
        evade_obj->set_effect_target(who);
        evade_obj->move(who, 1);
        evade_obj->start();
    }
     
    if (!ADMIN->query_member(who))
    {
            ADMIN->add_member(who);
    }
    who->add_cmdsoul(GUILD_CMDSOUL);
    who->update_hooks();
    
    if (who->query_alignment() > warning_align)
    {
        who->catch_tell("Your alignment is not suitable for "+
            "a Templar Knight, consider your actions!\n");
    }
}

public string
query_guild_name_lay()
{
    return GUILD_NAME;
}

public string
query_guild_style_lay()
{
    return GUILD_STYLE;
}


public int
query_guild_tax_lay()
{
    return GUILD_TAX;
}

/**
 * Define the guild trainer for max player skills
 */
mixed
query_guild_trainer_lay()
{
    return ({ ROOM+"train"});
}

/**
 * Display the names of skills
 */
mixed 
query_guild_skill_name(int type)
{
    if (type == SS_GUILD_ATTACK_SKILL)
    {
        return "tattack";
    }
    
    if (type == SS_GUILD_DEFEND_SKILL)
    {
        return "focus";
    }
    
    if (type == SS_GUILD_SAP_SKILL)
    {
        return "sap";
    }
}

/*
 *  Are we a member of the guild??
 */
int
query_templar_member()
{
    return ADMIN->query_member(query_shadow_who());
}

/*
 * Are we a Templar Knight, Officer, or Lord?
 */
int
query_full_templar_member()
{
    return (query_templar_rank() > TEMPLAR_RANK_WARRIOR);
}

/*
 * Are we a full Templar Knight?
 */
int
query_templar_knight()
{
    return (ADMIN->query_templar_rank(query_shadow_who()) 
        == TEMPLAR_RANK_KNIGHT);
}
 
/*
 * Are we an officer?
 */
int
query_templar_officer()
{
    return (ADMIN->query_templar_rank(query_shadow_who()) 
        == TEMPLAR_RANK_OFFICER);
}

/*
 * Are we THE LORD!!
 */
int
query_templar_lord()
{
    return (ADMIN->query_templar_rank(query_shadow_who()) 
        == TEMPLAR_RANK_LORD);
}

/*
* Find the rank of this person.
*/
int
query_templar_rank()
{
    return ADMIN->query_templar_rank(query_shadow_who());
}

/*
* Set the rank
*/ 
int
set_templar_rank(int i)
{
    return ADMIN->set_templar_rank(query_shadow_who(), i);
}

/*
* Adjust the ranks
*/
int
adjust_templar_rank(int i)
{
    return ADMIN->adjust_templar_rank(query_shadow_who(), i);
}

/**
 * Check if we let the player join other guilds
 */
public int
query_guild_not_allow_join_lay(object player,
                               string type,
                               string style,
                               string name)
{
    string str;
    
    /*don't join 2 layman guilds*/
    if (::query_guild_not_allow_join_lay(player, type, style, name))   
    {
        return 1;
    }

    // Only do the alignment check if this guild is the Templars.
    if(name != GUILD_NAME)
    {
        return 0;
    }

    str = player_can_join(player);
   
   /* If we get a return string, that means the check failed */
   /* and a reason was returned. */
   if (strlen(str))
   {
        write(str + "\n");
        return 1;
   }
     
   return 0;
    
}

/**
 * Does the player qualify to be in the guild
 */
public string
player_can_join(object player)
{
    int a = GUILD_MIN_ALIGN;
    
    /*Templars are a bit like a military religious order*/
    if (player->query_guild_style_occ() == "cleric") {
        return "You are already devoted to the Dark Queen!";
    }
    
    /*We only let in the baddies*/
    if (player->query_alignment() > a) {
        return "Your soul is too pure!";
    }
    
    /*No Kender!*/
    if (player->query_race_name() == "kender")
    {
        return "No kender allowed!";
    }
    
    return "";
}

/**
 * Add the shadow to the player and write out messages
 * This way we don't require a specific room to do it.
 */
public int
add_lay_shadow(object player)
{
    int result = shadow_me(player, "layman", GUILD_STYLE, GUILD_NAME);
    int added = 0;
        
    setuid();
    seteuid(getuid());
    
    switch (result) 
    {
        case 1:
            /* Success */
            write("You join the Templars of Takhisis.\n");
            log_file(JOINED, extract(ctime(time()), 4, 15) + " " +
                TP->query_real_name() + " joined Templars.\n", 500000);
            player->add_cmdsoul(GUILD_CMDSOUL);
            added = 1;
            break;
        case -4:
            /* Existing guilds prevented player from joining */
            write("Your current guild(s) prevent you "+
                "from joining the Templars!\n");
            log_file(PROBLEMS, extract(ctime(time()), 4, 15) + " " +
                TP->query_real_name() + " failed to join Templars " +
                "due to existing guilds: \n\t" + 
                TP->query_guild_name_race() + " (race)\n\t " +
                TP->query_guild_name_occ() + " (occ)\n\t" +
                TP->query_guild_name_lay() + " (lay)\n", 500000);
            break;
        default:
            /* Some other issue */
            write("A bug prevents you from joining the Templars!\n");
            log_file(PROBLEMS, extract(ctime(time()), 4, 15) + " " +
                TP->query_real_name() + " failed to join Templars due " +
                "to a problem with shadow_me()!\n", 500000);
            break;
    }
            
    return added;
}
    
/**
 * Have the player leave the guild
 */
public void
remove_lay_member()
{
    object player = query_shadow_who();
    object mantle;
    
    if (mantle = P(GUILD_OBJ_NAME, shadow_who))
    {
        player->command("$remove mantle");
        mantle->remove_object();
    }
    
    ADMIN->remove_member(player);
    player->clear_guild_stat(SS_LAYMAN);
    player->remove_skill(SS_GUILD_ATTACK_SKILL);
    player->remove_skill(SS_GUILD_SAP_SKILL);
    player->remove_skill(SS_GUILD_DEFEND_SKILL);
    player->remove_cmdsoul(GUILD_CMDSOUL);
    player->update_hooks();
    
    log_file(LEFT, extract(ctime(time()), 4, 15) + " " +
        TP->query_real_name() + " left the Templars.\n", 500000);
        
    /* the std remove */
    remove_guild_lay();
    
}
