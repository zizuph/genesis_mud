/*
 * Sunlight Shadow Code
 *
 * This file is included in the Vampire shadow, and controls the sunlight
 * effect. This effect was rewritten from the original one because the
 * original effect was mostly cosmetic, with no real drawbacks and penalties.
 *
 * Created by Petros, October 2009 
 *
 * Reused by Nerull, 2021.
 */
 
#include "../guild.h";
#include <mail.h>
#include <stdproperties.h>

// Global Variables
public int Con_drained;
public int Last_notify;

// Vampires can normally withstand minimal levels of sunlight exposure that 
// may occur during the night. Dawn/Dusk is where they begin to burn
#define VAMP_SUNLIGHT_TOLERANCE 5

#define COFFIN_ROOM   "/d/Faerun/guilds/vampires/rooms/coffin"


int
vampires_skill_adjustment(int i)
{
    setuid();
    seteuid(getuid());    
    
    // OCC skills
    int wep_skillbase;
    int twoh_combat_base;
    int blind_combat_base;
    int parry_base;
    int defense_base;
    int acrobat_base;
    int awareness_base;
    
    
    // Layman & Race skills
    int appr_mon_base;
    int climb_base;
    int tracking_base;
    int loc_sense_base;    
    int unarm_combat_base;
    
    int appr_val_base;
    int language_base;
    int trading_base;
    int open_lock_base;
    int spellcraft_base;
    
    // Specific guildskill
    int anatomy_base;
      
    object player = shadow_who;

    int age = VAMPIRES_MAPPINGS->query_vampires_gauge(shadow_who->query_name());
    
    int skillgain1;
    int skillgain2;
    int skillgain3;
    int skillgain4;
    int skillgain5;
       
    switch(age)
    {
        case 1451..1500:        
        wep_skillbase = 80;
        twoh_combat_base = 80;
        blind_combat_base = 60;
        parry_base = 65;
        defense_base = 65;
        acrobat_base = 55;
        awareness_base = 80;
        anatomy_base = 80;
        break;
        
        case 1501..1700:
        wep_skillbase = 85;
        twoh_combat_base = 85;
        blind_combat_base = 65;
        parry_base = 70;
        defense_base = 70;
        acrobat_base = 60;
        awareness_base = 85;
        anatomy_base = 85;
        break;
        
        case 1701..2000:
        wep_skillbase = 90;
        twoh_combat_base = 90;
        blind_combat_base = 70;
        parry_base = 75;
        defense_base = 75;
        acrobat_base = 65;
        awareness_base = 90;
        anatomy_base = 90;
        break;
        
        case 2001..3000:
        wep_skillbase = 93;
        twoh_combat_base = 93;
        blind_combat_base = 70;
        parry_base = 80;
        defense_base = 80;
        acrobat_base = 70;
        awareness_base = 93;
        anatomy_base = 93;
        break;
        
        case 3001..99999:
        wep_skillbase = 100;
        twoh_combat_base = 100;
        blind_combat_base = 80;
        parry_base = 85;
        defense_base = 85;
        acrobat_base = 75;
        awareness_base = 100;
        anatomy_base = 100;
        break;
    }
    
    // Player compromised, OCC skills reduced when 
    // exposed to sunlight.
    // DIABLED ATM - THIS BUGS AND CURRENT INVESTIGATION.
    /*if (i == 1)
    {
        wep_skillbase = 61;
        twoh_combat_base = 61;
        blind_combat_base = 61;
        parry_base = 61;
        defense_base = 61;
        acrobat_base = 61;
        awareness_base = 61;
        
        anatomy_base = 61;
    }*/
    
    // Skilladjustments only happens for OCC vampires.
    if (VAMPIRES_MASTER->is_occ_vampires(shadow_who->query_name()) == 1)
    {        
        if (VAMPIRES_MAPPINGS->query_weaponskill_selection(shadow_who->query_name()) == 1)      
        {
            shadow_who->set_skill(SS_WEP_SWORD, wep_skillbase);
            
            shadow_who->set_skill(SS_WEP_POLEARM, 30);
            shadow_who->set_skill(SS_WEP_AXE, 30);
            shadow_who->set_skill(SS_WEP_KNIFE, 30);
        }
        
        if (VAMPIRES_MAPPINGS->query_weaponskill_selection(shadow_who->query_name()) == 2)      
        {
            shadow_who->set_skill(SS_WEP_POLEARM, wep_skillbase);
            
            shadow_who->set_skill(SS_WEP_SWORD, 30);
            shadow_who->set_skill(SS_WEP_AXE, 30);
            shadow_who->set_skill(SS_WEP_KNIFE, 30);
        } 
        
        if (VAMPIRES_MAPPINGS->query_weaponskill_selection(shadow_who->query_name()) == 3)      
        {
            shadow_who->set_skill(SS_WEP_AXE, wep_skillbase);
            
            shadow_who->set_skill(SS_WEP_POLEARM, 30);
            shadow_who->set_skill(SS_WEP_SWORD, 30);
            shadow_who->set_skill(SS_WEP_KNIFE, 30);
        }
        
        if (VAMPIRES_MAPPINGS->query_weaponskill_selection(shadow_who->query_name()) == 4)      
        {
            shadow_who->set_skill(SS_WEP_KNIFE, wep_skillbase);
            
            shadow_who->set_skill(SS_WEP_POLEARM, 30);
            shadow_who->set_skill(SS_WEP_AXE, 30);
            shadow_who->set_skill(SS_WEP_SWORD, 30);
        }
        
        if (VAMPIRES_MAPPINGS->query_weaponskill_selection(shadow_who->query_name()) == 0)      
        {
            shadow_who->set_skill(SS_WEP_KNIFE, 30);            
            shadow_who->set_skill(SS_WEP_POLEARM, 30);
            shadow_who->set_skill(SS_WEP_AXE, 30);
            shadow_who->set_skill(SS_WEP_SWORD, 30);
        }
              
        // Racial skills
        shadow_who->set_skill(SS_OPEN_LOCK, 50); 
        shadow_who->set_skill(SS_HERBALISM, 50);
        shadow_who->set_skill(SS_TRACKING, 60); 
        shadow_who->set_skill(SS_LANGUAGE, 50); 
        shadow_who->set_skill(SS_CLIMB, 60);
        shadow_who->set_skill(SS_APPR_MON, 50); 
        
                

        // Layman skills                
        shadow_who->set_skill(SS_LOC_SENSE, 60); 
        shadow_who->set_skill(SS_ELEMENT_AIR, 60);
        shadow_who->set_skill(SS_ELEMENT_WATER, 60);
        shadow_who->set_skill(SS_ELEMENT_DEATH, 60);       
        shadow_who->set_skill(SS_FORM_ABJURATION, 60);
        shadow_who->set_skill(SS_FORM_CONJURATION, 60);
        shadow_who->set_skill(SS_FORM_ENCHANTMENT, 60);
        shadow_who->set_skill(SS_FORM_ILLUSION, 60);
        shadow_who->set_skill(SS_SPELLCRAFT, 60);  
            

        // OCC skills
        shadow_who->set_skill(SS_2H_COMBAT, twoh_combat_base);
        shadow_who->set_skill(SS_BLIND_COMBAT, blind_combat_base);        
        shadow_who->set_skill(SS_PARRY, parry_base);
        shadow_who->set_skill(SS_DEFENSE, defense_base);
        shadow_who->set_skill(SS_ACROBAT, acrobat_base);
        shadow_who->set_skill(SS_AWARENESS, awareness_base);        

        // Guildskill
        shadow_who->set_skill(SS_ANATOMY, anatomy_base);
        
        return 1;
    }
    
    // Guildskill - for spawns only.
    shadow_who->set_skill(SS_ANATOMY, 50);
    shadow_who->set_skill(SS_FORM_ENCHANTMENT, 50);
    shadow_who->set_skill(SS_ELEMENT_DEATH, 50);    
    shadow_who->set_skill(SS_SPELLCRAFT, 50);
}


void
expel_vampire()
{
    if (VAMPIRES_MASTER->is_failed_vampire(shadow_who->query_name()) == 1)
    {
        shadow_who->command("destroymevampire vampirevampie");
        shadow_who->command("scream");
    }
    
    /*if (VAMPIRES_MASTER->is_lay_vampires(shadow_who->query_name()) == 0)
    {
        shadow_who->command("destroymevampire vampirevampie");
    }*/
}


public void
process_outside_sunlight(object player, object room)
{
    vampires_skill_adjustment(0);
    
    if (player->query_ethereal() == 1)
    {
        return;
    }
    
    if (player->query_prop(VAMPIRE_IS_ETHEREAL))
    {
        return;
    }
    
    if (Last_notify > 0)
    {
        player->catch_msg("You find temporary refuge from the burning "
            + "sun.\n");
    }
    
    Last_notify = 0;
    
    player->set_compromised(0);
}


public void
process_inside_sunlight(object player, object room, int sunlight)
{
    if (player->query_ethereal() == 1)
    {
        return;
    }
    
    if (player->query_ghost() == 1)
    {
        return;
    }
    
    if (player->query_linkdead())
    {
        return;
    }
    
    if (player->query_prop(VAMPIRE_IS_DAYWALKER))
    {
        //player->catch_msg("While ability 'Daywalker' is activated, sunlight "
        //+"will not harm you.\n");
        return;
    }
    
    if (player->query_prop(VAMPIRE_IS_ETHEREAL))
    {
        //player->catch_msg("Being in the ethereal realm, sunlight "
        //+"will not harm you.\n");
        return;
    }
    
    if (player->query_trickortreat_costume())
    {
        return;
    }
    
    string test = query_shadow_who()->query_ethereal();
    
    if (Last_notify % 5 == 0 || !random(4))
    {
        if (player->query_ethereal() == 1)
        {
            return;
        }
        
        int max_hp = player->query_max_hp();
        int current_hp = player->query_hp();
        int hp_percentage = current_hp * 100 / max_hp;

        string burn_message;
        
        //switch (percentage_lost)
        switch (hp_percentage)
        {
        case 0..10:
                burn_message = "Flames wrack your entire body and you convulse "
                    + "with pain as your whole body disintegrates.\n";
                    
                player->tell_watcher(QTNAME(shadow_who) + " is entirely engulfed in "
                +"flames and is convulsing by the pain, rapidly disintegrating into "
                +"dust!\n");                
                break;
            
        case 11..25:
                burn_message = "Parts of your body burst into flames as you "
                + "continue to be exposed to the sun.\n";
                
                player->tell_watcher(QTNAME(shadow_who) + " is screaming horribly while "
                +"being partly engulfed in searing hot flames!\n");
                break;    
            
        case 26..50:
                burn_message = "You feel yourself losing control of your limbs "
                + "as your very core is being disintegrated by the flaming "
                + "sun.\n";
                
                player->tell_watcher(QTNAME(shadow_who) + " is screaming horribly while "
                +"pale skin blackening by the scorching rays of the sun!\n");
            break;
            
        case 51..75:
                burn_message = "You are in excruciating pain as you suffer "
                + "from the searing heat of the sun.\n";
                
                player->tell_watcher(QTNAME(shadow_who) + " seems to be in searing "
                +"pain by the rays of the sun!\n");
            break;
            
        case 76..90:
                burn_message = "Your burned skin begins to crackle and fall "
                + "apart under the continued assault of the sun.\n";
                
                player->tell_watcher(QTNAME(shadow_who) + "'s skin seems to react badly to "
                +"the rays of the sun!\n");
            break;
            
        case 91..100:
            burn_message = "Your skin burns under the heat of the sun.\n";
            
            player->tell_watcher(QTNAME(shadow_who) + " seems to react to the rays of "
            +"the sun!\n");
            break;
        }
        
        player->catch_msg(burn_message);
    }
    
    ++Last_notify;
    
    vampires_skill_adjustment(1);
    
    player->heal_hp(-150);
    
    player->set_compromised(1);
    
    if (player->query_hp() <= 0)
    {
        setuid();
        seteuid(getuid());
    
        player->catch_msg("The intensity of the sun consumes your body!\nYou turn "
        +"into an incorporeal misty state, that dissipates from the area!\n");
        
        player->tell_watcher(QTNAME(shadow_who) + " flares with great intensity, being "
        +"consumed entirely by the flames!\nThe smoke and mist dissipates "
        +"from the area.\n");
        
        player->add_prop(LIVE_I_NO_CORPSE, 1);
        
        clone_object("/d/Faerun/guilds/warlocks/obj/war_dust")->move(environment(player), 1);
                     
        // Vampires can avoid being permanently destroyed by consuming 
        // a point of immortality. Only occ Vampires can gain such
        // points, so layman vampires will always be destroyed by
        // the sun.      
        if (VAMPIRES_MAPPINGS->query_vampires_resilience(player->query_name()) > 0)
        {
            int current_resilience_rank = VAMPIRES_MAPPINGS->query_vampires_resilience(player->query_name());
            int new_resilience_rank = current_resilience_rank - 1;
            
            VAMPIRES_MAPPINGS->set_vampires_resilience(player->query_name(), new_resilience_rank);  

            VAMPIRES_MAPPINGS->set_thirst_gauge(player->query_name(), 1);
                        
            if (VAMPIRES_MAPPINGS->query_vampires_resilience(player->query_name()) == 0)
            {               
                clone_object(VAMPIRES_GUILD_DIR + "obj/immpoint_reward_obj")->move(player, 1);
            }
        
            player->catch_msg("The sunlight has defeated you!\n");
            
            // NONXP vampires don't lose xp during death, and will never
            // visit Lars. They will pay a different price fitting for their
            // kind.    
            if (VAMPIRES_MASTER->is_nonxp_vampire(player->query_name()))
            {
                shadow_who->move_living("M", VAMPIRES_GUILD_DIR + "rooms/coffin", 1);
                
                return;
            }
                   
            player->do_die();
            
            SURVIVEBURN_LOG("survivedburn_log",
            "The Vampire (Spawn) " +player->query_name() 
            +" was burned by the sun, but saved by immpoint. Immpoints left : "+new_resilience_rank+"\n");

            return;         
        }
        
        player->catch_msg("The sunlight has destroyed you!\n");
        
        //VAMPIRES_MASTER->remove_lay_vampires(player->query_name());
               
        VAMPIRES_MASTER->add_failed_vampire(player->query_name());
        
        
        // Vampire Spawns are guildkicked when killed by the sun.
        clone_object(VAMPIRES_GUILD_DIR + "obj/expel_obj")->move(player, 1);
        set_alarm(1.0, 0.0, &expel_vampire());
        
        player->expel_vampire();
        
        LEAVE_LOG("leave_log",
        "The Vampire (Spawn) " +player->query_name() 
        +" was destroyed by the sun.\n");
        
        CREATE_MAIL("Destruction", "Vampires", player->query_name(), "",
        "You was destroyed by the rays of the sun.\n");
    }    
}


/*
 * Function:    query_sunlight_level
 * Description: This checks a room for the amount of sunlight that is in
 *              it. It uses the Genesis Timekeeper's code to do most of
 *              the sunlight calculations.
 */
public int
query_sunlight_level(object room)
{
    object player = shadow_who;
    
    setuid();
    seteuid(getuid());    
    
    int sunlight = GENESIS_TIMEKEEPER->query_sunlight(player);
    
    if (sunlight < VAMP_SUNLIGHT_TOLERANCE
      || room->query_prop(OBJ_I_LIGHT) <= 0)
    {
        // If the room itself is dark, or sunlight levels are too low,
        // we allow the vampire to heal from any burning that they may
        // have encountered by returning 0 for the sunlight levels
        return 0;
    }
    
    return sunlight;    
}


/*
 * Function:    check_sunlight
 * Description: This is the function called by the repeating alarm in the
 *              shadow every 5.0 seconds. It will drain the vampire if it
 *              finds the vampire exposed in sunlight.
 */
public void 
check_sunlight()
{
    setuid();
    seteuid(getuid());    
    
    object player = shadow_who;
    
    //Hack to prevent runtime.
    if (!player)
    {
        return;
    }

    /*if (!player->query_relaxed_from_combat())
    {
        if (VAMPIRES_MAPPINGS->query_vampires_gauge(player->query_name()) >= 1451)
        {
            if (!present("_scrybreak_ob", player))
            {
                object scrybreak = clone_object(VAMPIRES_GUILD_DIR + "obj/scrybreak_obj");       
                scrybreak->move(player, 1);           
            }
        }
    } */   
 
    object room = environment(player);
    
    int vampirespawn_countdwn;
    int age;
 
    if (VAMPIRES_MASTER->is_failed_vampire(shadow_who->query_name()) == 1)
    {
        // Target expelled.       
        object expelob = clone_object(VAMPIRES_GUILD_DIR + "obj/expel_obj");
        
        expelob->move(shadow_who, 1);

        shadow_who->command("destroymevampire vampirevampie");
        
        return;
    }
    
    if (!objectp(player) || !objectp(room))
    {
        // Should never happen
        return;
    }   
 
    if (player->query_prop(VAMPIRE_IS_ETHEREAL))
    {
        return;
    }
    
    if (player->query_trickortreat_costume())
    {
        return;
    }

    /*string *coffins;

	coffins = COFFIN_MANAGER->query_all_coffins();

    for (int i = 0; sizeof(coffins) > i; i++)
    {
        // We wont find coffins when we already have one.
        if (coffins[i] == player->query_real_name())
        {
            return;
        }
        else
        {
            object powertoken;
            
            if (powertoken = present("_vampire_powers_unlock_ob", player))            
            {
                player->catch_tell("You no longer have a coffin!\n"
                +"You feel part of your power is drained, and "
                +"you are more restricted!\n");
                
                powertoken->remove_object();
                
                return;
            }
        }
    }    */
    
    if (player->query_ethereal() == 0)
    {
        int sunlight = query_sunlight_level(room);
        
        if (!sunlight)
        {
            process_outside_sunlight(player, room);
            
            return;
        }
        
        process_inside_sunlight(player, room, sunlight);    
    }   
}
