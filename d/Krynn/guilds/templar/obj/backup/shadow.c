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
void switch_focus_state();
private mixed mess_with_weapon(object target, object weapon);
private mixed mess_with_shield(object target, object shield);
private mixed mess_with_dodge(object target);
void print_defence_messages(object target);
void set_is_focused(int i);
void query_is_focused();
int query_guild_level_lay();
public void remove_lay_member();
int query_templar_rank();

// prototypes 
void reset_sap_timer();
void set_sap_timer();
int query_sap_timer();

int query_offensive_attacking();
void set_offensive_attacking();
void reset_offensive_attacking();

int query_offensive_preparing();
void set_offensive_preparing();
void reset_offensive_preparing();

private int isFocused = 0;
int query_full_templar_member();

private mixed *my_focus_list = 
    ({ SKILL_AVG, TS_STR, TS_DEX, TS_WIS, TS_LAYMAN, SKILL_END,
        SS_GUILD_DEFEND_SKILL });
        
private mixed *opp_focus_list =
    ({ SKILL_AVG, TS_DEX, TS_WIS, SKILL_END, SS_AWARENESS }); 

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
    
    set_alarm(1.5, 0.0, &init_templar_shadow());
    
}

public nomask void
init_templar_shadow()
{
    object who = query_shadow_who();
    object mantle;
    int warning_align = GUILD_WARN_ALIGN;
    int min_align = GUILD_MIN_ALIGN;
    
    setuid();
    seteuid(getuid());
    
    if (objectp(mantle = clone_object(OBJ + "mantle")))
    {
        mantle->move(TP, 1);
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

    // We dont want to kick them out, we take away their specials.
    //    if (who->query_alignment() > min_align)
    //    {
    //        who->catch_tell("You are not evil enough to remain "+
    //            "a Templar Knight!\n");
    //        set_alarm(1.5, 0.0, &remove_lay_member());
/*
        ADMIN->remove_member(who);
        who->remove_lay_member();
*/
//        log_file(LEFT, extract(ctime(time()), 4, 15) + " " +
//            TP->query_real_name() + " is booted for " +
//            "having an alignment of "+who->query_alignment()+
//            ".\n", 500000);
    //  }
    
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
    int guild_tax;

    if (query_full_templar_member())
    {
        guild_tax = TEMPLAR_GUILD_TAX;
    } else {
        guild_tax = WARRIOR_GUILD_TAX;
    }
    
    return guild_tax;
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
    
    /*This doesn't check for 2 layman guilds!*/
    
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


/***************************************
****************************************
    SPECIAL ATTACK(S) BELOW
****************************************/
/**
 * Defensive focus special
 */
void
switch_focus_state()
{
    object who = query_shadow_who();
    
    if (query_is_focused())
    {
        who->catch_tell("You stop attempting to defend against attacks.\n");
        set_is_focused(0);
        
    } else
    {
        who->catch_tell("You begin focusing on defending against attacks.\n");
        set_is_focused(1);
        
    }
}

/**
 * Set the focused int 
 * This is used in query_not_attack_me()
 */
void
set_is_focused(int i)
{
    isFocused = i;
}

/**
 * Are we attempting to defend against attacks?
 */
int
query_is_focused()
{
    return isFocused;
}

/**
 * Attempt to defend against incoming attacks. 
 */
public int
query_not_attack_me(object target, int aid)
{
    object who = query_shadow_who(), pot_tar, tar2;
    int cannotAttack = who->query_not_attack_me(target, aid);
    
    /*If we're not getting attacked anyway, don't
     * bother computing everything
     */
    if (cannotAttack)
    {
        return cannotAttack;
    }

    if (!query_is_focused()
        || who->query_prop(LIVE_I_STUNNED)) 
    {
        return cannotAttack;
    }

    /*20% chance of success*/
    if (random(100) > 19)
    {
        return cannotAttack;
    }

    //We only dodge one person, in this order:
    // - The person we're currently hitting, if they are attacking us
    // - Our cb_query_enemy(-1) list, starting with the [0] position
    //   and continuing until we find someone who is attacking us 
    //   directly.
    
    //Is the person we're dodging our query_attack?  If not, check
    //where they fall in our list.
    if (! ((pot_tar = who->query_attack()) && target == pot_tar))
    {
        //Do we have an enemy and are they swinging at us.  If so, we
        //only dodge them, so get out (since if they were swing at us
        //we would have caught it in the IF above this one
        if ((pot_tar = who->query_attack()) 
            && (pot_tar->query_attack() == who))
        {
            return cannotAttack;
        }

        //At this point we know that the person we're attacking isn't
        //attacking us, so we're free to dodge someone else.
        mixed list = who->query_combat_object()->cb_query_enemy(-1);
        int i = sizeof(list);

        //Start at the beginning!
        //If 'target' isn't the first person in our enemy list that
        //is hitting us, get out
        for (int k = 0; k < i; k++)
        {
            //First guy swinging at us
            if (list[k]->query_attack() == who) 
            {
                //Is he the guy we're dodging?
                if (list[k] != target)
                {
                    //No so get out
                    return cannotAttack;
                } else
                {
                    //Yes so continue
                    break;
                }
            }
        }
    }
    
/*
    if (target != who->query_attack())
    {
        return cannotAttack;
    }    
*/    
    if (who->resolve_task(TASK_SIMPLE, my_focus_list, target,
        opp_focus_list) < 1)
    {
        return cannotAttack;
    }

    
    print_defence_messages(target);
    
    return 1;   
    

}

/**
 * When a successful defence occurs, print the messages to
 * those involved
 */
void
print_defence_messages(object target)
{

    object who = query_shadow_who();
    object *weapons = who->query_weapon(-1);
    object *armours = who->query_armour(-1);
    string *messages;
    int hasWeapon = 0;
    int hasShield = 0;
    int shieldLoc = 0;
    
    if (sizeof(weapons))
    {
        hasWeapon = 1;
    }
    
    for (int j = 0; j < sizeof(armours); j++)
    {
        if (armours[j]->id("shield"))
        {
            hasShield = 1;
            shieldLoc = j;
            break;
        }
    }
    
    if (hasWeapon && !random(4))
    {
        messages = mess_with_weapon(target, weapons[0]);
    } else if (hasShield && !random(4))
    { 
        messages = mess_with_shield(target, armours[shieldLoc]);
    } else 
    {
        messages = mess_with_dodge(target);
    }

    who->catch_tell(messages[0]);
    target->catch_tell(messages[1]);
    who->tell_watcher(messages[2], target);
        
}

/**
 * Create the messages when a weapon is used to block
 */
private mixed
mess_with_weapon(object target, object weapon)
{
    object who = query_shadow_who();
    string *message;
    
    message = ({"You parry "+target->query_the_name(who)+"'s attack with "+
        "your "+weapon->query_short()+"!\n",
        who->query_The_name(target)
            +" parries your attack with "+HIS(who)+
            " "+weapon->query_short()+"!\n",
        QCTNAME(who)+" parries "+QTNAME(target)+"'s "
            +"attack with "+HIS(who)+" "+weapon->query_short()
            +"!\n"});
        
    return message;
}

/**
 * Create the messages when a shield is used to block
 */
private mixed
mess_with_shield(object target, object shield)
{
    object who = query_shadow_who();
    string *message;
    
    message = ({"You block "+target->query_the_name(who)
                +"'s attack with "+
                "your "+shield->query_short()+"!\n",
        who->query_The_name(target)
            +" blocks your attack with "+HIS(who)+
            " "+shield->query_short()+"!\n",
        QCTNAME(who)+" blocks "+QTNAME(target)+"'s "+
            "attack with "+HIS(who)+" "+shield->query_short()+"!\n"});
        
    return message;
}


/**
 * Create the messages for a dodge
 */
 
private mixed
mess_with_dodge(object target)
{

    object who = query_shadow_who();
    string *message;
    
    message = ({"You dodge "+target->query_the_name(who)+"'s attack!\n",
        who->query_The_name(target)
            +" dodges your attack!\n",
        QCTNAME(who)+" dodges "+QTNAME(target)+"'s attack!\n"});
        
    return message;     
}

void
set_offensive_attacking()
{
    shadow_who->add_prop(TEMPLAR_ATTACK_RESET, 
                              (time() + ATTACK_RESET_TIME));
}

int
query_offensive_attacking()
{
    return (shadow_who->query_prop(TEMPLAR_ATTACK_RESET) > time());
    
}

void
reset_offensive_attacking()
{
    shadow_who->remove_prop(TEMPLAR_ATTACK_RESET);
}

void
set_offensive_preparing()
{
    shadow_who->add_prop(TEMPLAR_ATTACK_PREP, 
                          (time() + ATTACK_PREP_TIME));
}

int
query_offensive_preparing()
{
    return (shadow_who->query_prop(TEMPLAR_ATTACK_PREP) > time());
}

void
reset_offensive_preparing()
{
    shadow_who->remove_prop(TEMPLAR_ATTACK_PREP);
}

void
reset_sap_timer()
{
    shadow_who->remove_prop(TEMPLAR_SAP_RESET);
}

void
set_sap_timer()
{
    shadow_who->add_prop(TEMPLAR_SAP_RESET, 
                        (time() + SAP_RESET_TIME));
}

int
query_sap_timer()
{
    return (shadow_who->query_prop(TEMPLAR_SAP_RESET) > time());
}
