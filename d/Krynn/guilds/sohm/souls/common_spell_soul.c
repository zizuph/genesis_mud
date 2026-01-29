/*
 * Common spell soul for SoHM and WoHS
 *
 * Created by Arman March 2016
 */

#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

/* 
 * Function name: get_soul_id
 * Description:   Give a name for this soul
 * Returns:       string - the soul's id
 */
public string
get_soul_id() 
{ 
    return "Common Krynn Spell Soul"; 
}

/*
 * Function name: query_cmd_soul
 * Description:   identify this as a valid cmdsoul
 * Returns:       1
 */
public int 
query_cmd_soul() 
{ 
    return 1; 
}
  
public mapping
query_cmdlist()
{
    return ([
        /* Spell name : Function name */
        "edarmolik"         : "do_ability",
        "arcanisvaes"       : "do_ability",
        "wievaixen"         : "do_ability",
        "suacovisp"         : "do_ability",
        "shochraos"         : "do_ability",
        "kampiunarcanis"    : "do_ability",
        "ukrisrivek"        : "do_ability",
        "talkarpas"         : "do_ability",
        "ickrakarcanis"     : "do_ability",
        "arcanfethos"       : "do_ability",
        "apianak"           : "do_ability",
        "bakmadaingis"      : "do_ability",
        "ixenner"           : "do_ability",
        "xarzithnar"        : "do_ability",
        "riyitchikohk"      : "do_ability",
        "odenarcanis"       : "do_ability",
        "ripeidronik"       : "do_ability",
        "hewavers"          : "do_ability",
        "vistoma"           : "do_ability",
        "levexlaraek"       : "do_ability",
        "uvelucavaes"       : "do_ability",
        "shirak"            : "do_ability",
        "ehtahxiekiv"       : "do_ability",
        "ehtahhewa"         : "do_ability",
        "kadenadon"         : "do_ability",
        "zhinpersvek"       : "do_ability",
        "whedabra"          : "do_ability",
        "trothdraconis"     : "do_ability",
        "trothixen"         : "do_ability",
        "trothuvelucal"     : "do_ability",
        "trothgul"          : "do_ability",
        "trothshochraos"    : "do_ability",
        "trothweyog"        : "do_ability",
        "viraxregpos"       : "do_ability",
        "ricindenthanus"    : "do_ability",
        "reelojawa"         : "do_ability",
        "chikohk"           : "do_ability",
        "okiai"             : "do_ability",
        "ickrakfethos"      : "do_ability",
        "pabfrahrir"        : "do_ability",
        "wintektor"         : "do_ability",
        "ixengarmth"        : "do_ability",
        "ganimshochraos"    : "do_ability",
        "tonashingis"       : "do_ability",
        "jennufethos"       : "do_ability",
        "trotharcanis"      : "do_ability",
        "tonashkepesk"      : "do_ability",
        "kepeskwiivai"      : "do_ability",
        "arcanossalur"      : "do_ability",
        "edarvirednith"     : "do_ability",
        "virednith"         : "do_ability",
        "temep"             : "do_ability",
        "xiekxilunwai"      : "do_ability",
        "nasirmitne"        : "do_ability",
        "haddross"          : "do_ability",
        "ixenchasid"        : "do_ability",
        "trothocuir"        : "do_ability",
        "plythusuiaerl"     : "do_ability",
        "thirkusio"         : "do_ability",
        "jikmadakethend"    : "do_ability",
        "nuadealdoer"       : "do_ability",
        "dotonobsule"       : "do_ability",
        "sjachbuala"        : "do_ability",
        "iniksuaco"         : "do_ability",
        "skaerenpab"        : "do_ability",
        "suacotrekis"       : "do_ability",
        "svihossalur"       : "do_ability",
        "reskafar"          : "do_ability",
        "hexlithdrevab"     : "do_ability",
        "welunyoweth"       : "do_ability",
        "suacodrevab"       : "do_ability",
        "xarzithinloilfrey" : "do_ability",
        "edarjikmada"       : "do_ability",
        "thirkualtiui"      : "do_ability",

        // npc spells not available to players
        "aurakdisarm"       : "do_ability",
        "aurakfire"         : "do_ability",

        // Memorise spell commands
        "memorise"          : "memorise",
        "memorize"          : "memorise",
        "unmemorise"        : "unmemorise",
        "unmemorize"        : "unmemorise",
        // Component collection and spell support commands
        "bleed"             : "sbleed",
        "sbleed"            : "sbleed",
        "visposuvundi"      : "shistory",
        "steleport"         : "steleport",
        "wteleport"         : "steleport",
    ]);
}

public mapping
query_ability_map()
{
    return ([
        "shochraos"        : SOHM_SPELLS + "lightning_bolt",
        "edarmolik"        : SOHM_SPELLS + "stoneskin",
        "arcanisvaes"      : SOHM_SPELLS + "magic_missile",
        "suacovisp"        : SOHM_SPELLS + "wind_whisper",
        "wievaixen"        : SOHM_SPELLS + "faerie_fire",
        "kampiunarcanis"   : SOHM_SPELLS + "read_magic",
        "ukrisrivek"       : SOHM_SPELLS + "speak_with_dead",
        "talkarpas"        : SOHM_SPELLS + "wand_light",
        "ickrakarcanis"    : SOHM_SPELLS + "detect_magic",
        "arcanfethos"      : SOHM_SPELLS + "magic_shield",
        "apianak"          : SOHM_SPELLS + "fire_dart",
        "bakmadaingis"     : SOHM_SPELLS + "prismatic_spray",
        "ixenner"          : SOHM_SPELLS + "flame_lance",
        "xarzithnar"       : SOHM_SPELLS + "ice_strike",
        "riyitchikohk"     : SOHM_SPELLS + "fools_curse",
        "odenarcanis"      : SOHM_SPELLS + "identify",
        "ripeidronik"      : SOHM_SPELLS + "blink",
        "hewavers"         : SOHM_SPELLS + "mage_strength",
        "vistoma"          : SOHM_SPELLS + "truesight",
        "levexlaraek"      : SOHM_SPELLS + "enchant_weapon",
        "uvelucavaes"      : SOHM_SPELLS + "acid_arrow",
        "shirak"           : SOHM_SPELLS + "light_spell",
        "ehtahxiekiv"      : SOHM_SPELLS + "scry_spell",
        "ehtahhewa"        : SOHM_SPELLS + "divine_wizards",
        "kadenadon"        : SOHM_SPELLS + "blur",
        "zhinpersvek"      : SOHM_SPELLS + "invisibility_spell",
        "whedabra"         : SOHM_SPELLS + "gloom",
        "trothdraconis"    : SOHM_SPELLS + "protect_fear",
        "trothixen"        : SOHM_SPELLS + "protect_fire",
        "trothuvelucal"    : SOHM_SPELLS + "protect_acid",
        "trothgul"         : SOHM_SPELLS + "protect_cold",
        "trothshochraos"   : SOHM_SPELLS + "protect_lightning",
        "trothweyog"       : SOHM_SPELLS + "protect_poison",
        "viraxregpos"      : SOHM_SPELLS + "reflect_damage",
        "ricindenthanus"   : SOHM_SPELLS + "psychic_blast",
        "reelojawa"        : SOHM_SPELLS + "dominate",
        "chikohk"          : SOHM_SPELLS + "curse",
        "wintektor"        : SOHM_SPELLS + "scare",
        "okiai"            : SOHM_SPELLS + "dazzle",
        "ickrakfethos"     : SOHM_SPELLS + "detect_resistance",
        "pabfrahrir"       : SOHM_SPELLS + "breath_water",
        "ixengarmth"       : SOHM_SPELLS + "fireball",
        "ganimshochraos"   : SOHM_SPELLS + "chain_lightning",
        "tonashingis"      : SOHM_SPELLS + "ballistic_spray",
        "jennufethos"      : SOHM_SPELLS + "greater_magic_shield",
        "trotharcanis"     : SOHM_SPELLS + "protect_magic",
        "tonashkepesk"     : SOHM_SPELLS + "meteor_storm",
        "kepeskwiivai"     : SOHM_SPELLS + "storm_fury",
        "arcanossalur"     : SOHM_SPELLS + "teleport",
        "edarvirednith"    : SOHM_SPELLS + "eruption",
        "virednith"        : SOHM_SPELLS + "detonate",
        "temep"            : SOHM_SPELLS + "haste",
        "xiekxilunwai"     : SOHM_SPELLS + "portents_and_omens",
        "nasirmitne"       : SOHM_SPELLS + "featherweight",
        "haddross"         : SOHM_SPELLS + "gravity",
        "ixenchasid"       : SOHM_SPELLS + "flaming_fist",
        "trothocuir"       : SOHM_SPELLS + "protect_divination",
        "plythusuiaerl"    : SOHM_SPELLS + "vulnerability_magic",
        "thirkusio"        : SOHM_SPELLS + "polymorph_self",
        "jikmadakethend"   : SOHM_SPELLS + "shatter",
        "nuadealdoer"      : SOHM_SPELLS + "rune_of_welcome",
        "dotonobsule"      : SOHM_SPELLS + "mirror_portal",
        "sjachbuala"       : SOHM_SPELLS + "shadow_veil",
        "iniksuaco"        : SOHM_SPELLS + "scouring_wind",
        "skaerenpab"       : SOHM_SPELLS + "geyser",
        "suacotrekis"      : SOHM_SPELLS + "wind_gust",
        "svihossalur"      : SOHM_SPELLS + "teleport_team",
        "reskafar"         : SOHM_SPELLS + "rift",
        "aurakdisarm"      : SOHM_SPELLS + "aurak_disarm_spell",
        "aurakfire"        : SOHM_SPELLS + "aurak_flame_spell",
        "hexlithdrevab"    : SOHM_SPELLS + "toxic_blast",
        "welunyoweth"      : SOHM_SPELLS + "stellar_alignment",
        "suacodrevab"      : SOHM_SPELLS + "cyclonic_blast",
        "xarzithinloilfrey" : SOHM_SPELLS + "ice_shard",
        "edarjikmada"      : SOHM_SPELLS + "foreshock",
        "thirkualtiui"     : SOHM_SPELLS + "polymorph_self_bird",
    ]);
}

int
query_sohm_spell_level(string str)
{
    if(str == "dotonobsule")
      return SOHM_CANTRIP_SPELL;
    if(str == "ehtahhewa")
      return SOHM_CANTRIP_SPELL;
    if(str == "ickrakarcanis")
      return SOHM_CANTRIP_SPELL;
    if(str == "jikmadakethend")
      return SOHM_CANTRIP_SPELL;
    if(str == "kampiunarcanis")
      return SOHM_CANTRIP_SPELL;
    if(str == "nuadealdoer")
      return SOHM_CANTRIP_SPELL;
    if(str == "riyitchikohk")
      return SOHM_CANTRIP_SPELL;
    if(str == "suacotrekis")
      return SOHM_CANTRIP_SPELL;
    if(str == "ukrisrivek")
      return SOHM_CANTRIP_SPELL;
    if(str == "talkarpas")
      return SOHM_CANTRIP_SPELL;
    if(str == "suacovisp")
      return SOHM_CANTRIP_SPELL;
    if(str == "suacovisp")
      return SOHM_CANTRIP_SPELL;
    if(str == "reskafar")
      return SOHM_CANTRIP_SPELL;
    if(str == "thirkualtiui")
      return SOHM_CANTRIP_SPELL;
    if(str == "apianak")
      return SOHM_MINOR_SPELL;
    if(str == "arcanfethos")
      return SOHM_MINOR_SPELL;
    if(str == "arcanisvaes")
      return SOHM_MINOR_SPELL;
    if(str == "bakmadaingis")
      return SOHM_MINOR_SPELL;
    if(str == "chikohk")
      return SOHM_MINOR_SPELL;
    if(str == "ickrakfethos")
      return SOHM_MINOR_SPELL;
    if(str == "nasirmitne")
      return SOHM_MINOR_SPELL;
    if(str == "odenarcanis")
      return SOHM_MINOR_SPELL;
    if(str == "okiai")
      return SOHM_MINOR_SPELL;
    if(str == "pabfrahrir")
      return SOHM_MINOR_SPELL;
    if(str == "ripeidronik")
      return SOHM_MINOR_SPELL;
    if(str == "shirak")
      return SOHM_MINOR_SPELL;
    if(str == "tonashingis")
      return SOHM_MINOR_SPELL;
    if(str == "trothdraconis")
      return SOHM_MINOR_SPELL;
    if(str == "trothocuir")
      return SOHM_MINOR_SPELL;
    if(str == "uvelucavaes")
      return SOHM_MINOR_SPELL;
    if(str == "wievaixen")
      return SOHM_MINOR_SPELL;
    if(str == "wintektor")
      return SOHM_MINOR_SPELL;
    if(str == "xarzithinloilfrey")
      return SOHM_MINOR_SPELL;
    if(str == "edarjikmada")
      return SOHM_LESSER_SPELL;
    if(str == "ehtahxiekiv")
      return SOHM_LESSER_SPELL;
    if(str == "hewavers")
      return SOHM_LESSER_SPELL;
    if(str == "iniksuaco")
      return SOHM_LESSER_SPELL;
    if(str == "ixenchasid")
      return SOHM_LESSER_SPELL;
    if(str == "ixenner")
      return SOHM_LESSER_SPELL;
    if(str == "kadenadon")
      return SOHM_LESSER_SPELL;
    if(str == "levexlaraek")
      return SOHM_LESSER_SPELL;
    if(str == "ricindenthanus")
      return SOHM_LESSER_SPELL;
    if(str == "shochraos")
      return SOHM_LESSER_SPELL;
    if(str == "sjachbuala")
      return SOHM_LESSER_SPELL;
    if(str == "skaerenpab")
      return SOHM_LESSER_SPELL;
    if(str == "trothixen")
      return SOHM_LESSER_SPELL;
    if(str == "trothweyog")
      return SOHM_LESSER_SPELL;
    if(str == "trothshochraos")
      return SOHM_LESSER_SPELL;
    if(str == "trothgul")
      return SOHM_LESSER_SPELL;
    if(str == "trothuvelucal")
      return SOHM_LESSER_SPELL;
    if(str == "xarzithnar")
      return SOHM_LESSER_SPELL;
    if(str == "zhinpersvek")
      return SOHM_LESSER_SPELL;
    if(str == "arcanossalur")
      return SOHM_GREATER_SPELL;
    if(str == "edarmolik")
      return SOHM_GREATER_SPELL;
    if(str == "haddross")
      return SOHM_GREATER_SPELL;
    if(str == "reelojawa")
      return SOHM_GREATER_SPELL;
    if(str == "temep")
      return SOHM_GREATER_SPELL;
    if(str == "viraxregpos")
      return SOHM_GREATER_SPELL;
    if(str == "vistoma")
      return SOHM_GREATER_SPELL;
    if(str == "whedabra")
      return SOHM_GREATER_SPELL;
    if(str == "xiekxilunwai")
      return SOHM_GREATER_SPELL;
    if(str == "edarvirednith")
      return SOHM_ADVANCED_SPELL;
    if(str == "ganimshochraos")
      return SOHM_ADVANCED_SPELL;
    if(str == "hexlithdrevab")
      return SOHM_ADVANCED_SPELL;
    if(str == "ixengarmth")
      return SOHM_ADVANCED_SPELL;
    if(str == "jennufethos")
      return SOHM_ADVANCED_SPELL;
    if(str == "kepeskwiivai")
      return SOHM_ADVANCED_SPELL;
    if(str == "plythusuiaerl")
      return SOHM_ADVANCED_SPELL;
    if(str == "suacodrevab")
      return SOHM_ADVANCED_SPELL;
    if(str == "svihossalur")
      return SOHM_ADVANCED_SPELL;
    if(str == "thirkusio")
      return SOHM_ADVANCED_SPELL;
    if(str == "tonashkepesk")
      return SOHM_ADVANCED_SPELL;
    if(str == "trotharcanis")
      return SOHM_ADVANCED_SPELL;
    if(str == "virednith")
      return SOHM_ADVANCED_SPELL;
    if(str == "welunyoweth")
      return SOHM_ADVANCED_SPELL;
}

// Memorise and unmemorise functions

public int
memorise(string str)
{
 
    int memorised_spells;

    if (!strlen(str))
    {
        notify_fail("What spell do you want to memorise from your spellbook?\n");
        return 0;
    }

    if(!SOHM_MANAGER->query_scribed_spell(this_player(), str)) 
    {
        notify_fail("That spell doesn't seem to be in your spellbook to " +
            "memorise.\n");
        return 0;
    }

    if(SOHM_MANAGER->query_memorised_spell(this_player(), str + "_memorised")) 
    {
        notify_fail("You have already memorised that spell!\n");
        return 0;
    }    

    if(!query_sohm_spell_level(str))
    {
        notify_fail("This spell is uncategorised and cannot be memorised. " +
          "Please leave a bug report.\n");
          return 0;
    }

    if(query_sohm_spell_level(str) == SOHM_CANTRIP_SPELL)
    {
       if(SOHM_MANAGER->query_cantrips_memorised(this_player()) == this_player()->query_cantrip_spells_max())
       {
          notify_fail("You already have memorised the maximum number " +
             "of cantrips.\n" +
             "Unmemorise a cantrip if you wish to memorise " +str+ ".\n");
          return 0;
       }
       
       memorised_spells = SOHM_MANAGER->query_cantrips_memorised(this_player()) + 1;
       SOHM_MANAGER->set_cantrips_memorised(this_player(), memorised_spells);
    }

    if(query_sohm_spell_level(str) == SOHM_MINOR_SPELL)
    {
       if(SOHM_MANAGER->query_minors_memorised(this_player()) == this_player()->query_minor_spells_max())
       {
          notify_fail("You already have memorised the maximum number of " +
             "minor spells.\n" +
             "Unmemorise a minor spell if you wish to memorise " +str+ ".\n");
          return 0;
       }
       
       memorised_spells = SOHM_MANAGER->query_minors_memorised(this_player()) + 1;
       SOHM_MANAGER->set_minors_memorised(this_player(), memorised_spells);
    }

    if(query_sohm_spell_level(str) == SOHM_LESSER_SPELL)
    {
       if(SOHM_MANAGER->query_lessers_memorised(this_player()) == this_player()->query_lesser_spells_max())
       {
          notify_fail("You already have memorised the maximum number of " +
             "lesser spells.\n" +
             "Unmemorise a lesser spell if you wish to memorise " +str+ ".\n");
          return 0;
       }
       
       memorised_spells = SOHM_MANAGER->query_lessers_memorised(this_player()) + 1;
       SOHM_MANAGER->set_lessers_memorised(this_player(), memorised_spells);
    }

    if(query_sohm_spell_level(str) == SOHM_GREATER_SPELL)
    {
       if(SOHM_MANAGER->query_greaters_memorised(this_player()) == this_player()->query_greater_spells_max())
       {
          notify_fail("You already have memorised the maximum number of " +
             "greater spells.\n" +
             "Unmemorise a greater spell if you wish to memorise " +str+ ".\n");
          return 0;
       }
       
       memorised_spells = SOHM_MANAGER->query_greaters_memorised(this_player()) + 1;
       SOHM_MANAGER->set_greaters_memorised(this_player(), memorised_spells);
    }

    if(query_sohm_spell_level(str) == SOHM_ADVANCED_SPELL)
    {
       if(SOHM_MANAGER->query_advanced_memorised(this_player()) == this_player()->query_advanced_spells_max())
       {
          notify_fail("You already have memorised the maximum number of " +
             "advanced spells.\n" +
             "Unmemorise an advanced spell if you wish to memorise " +str+ ".\n");
          return 0;
       }
       
       memorised_spells = SOHM_MANAGER->query_advanced_memorised(this_player()) + 1;
       SOHM_MANAGER->set_advanced_memorised(this_player(), memorised_spells);
    }

    write("You memorise the spell " +str+ ".\n");
    allbb(" memorises a spell.");

    SOHM_MANAGER->memorise_spell(this_player(), str +"_memorised");
    return 1;
}

public int
unmemorise(string str)
{
    int memorised_spells;
    int spell_type = query_sohm_spell_level(str);

    if (!strlen(str))
    {
        notify_fail("What spell do you want to unmemorise?\n");
        return 0;
    }

    if(!SOHM_MANAGER->query_memorised_spell(this_player(), str + "_memorised")) 
    {
        notify_fail("You haven't memorised that spell.\n");
        return 0;
    }

    if(SOHM_MANAGER->query_memorise_time(this_player(), spell_type) > time())
    {
        string recover_str = "a bit of time";


        int mem_time = SOHM_MANAGER->query_memorise_time(this_player(), spell_type);
        int recover_time = mem_time - time();

        if(recover_time < 1800)
         recover_str = "less than half an hour";
        else if(recover_time < 3600)
         recover_str = "less than an hour";
        else if(recover_time < 7200)
         recover_str = "approximately one hour";
        else if(recover_time < 172800)
        {
           int recover_hours = recover_time / 3600;
           recover_str = "approximately " +recover_hours+ " hours";
        }
        else
        {
           int recover_days = recover_time / 86400;
           recover_str = "approximately " +recover_days+ " days";
        }

        notify_fail("You have not recovered the mental focus to unmemorise " +
           "another spell of that nature. You will have to wait " +recover_str+
           " before you are in the mindset to clear your memory of that " +
           "type of spell.\n");
        return 0;
    }

    write("You clear your head of the spell " +str+ ".\n");
    allbb(" concentrates for a moment.");

    SOHM_MANAGER->unmemorise_spell(this_player(), str +"_memorised");

    if(query_sohm_spell_level(str) == SOHM_CANTRIP_SPELL)
    {      
       memorised_spells = SOHM_MANAGER->query_cantrips_memorised(this_player()) - 1;
       SOHM_MANAGER->set_cantrips_memorised(this_player(), memorised_spells);
    }

    if(query_sohm_spell_level(str) == SOHM_MINOR_SPELL)
    {      
       memorised_spells = SOHM_MANAGER->query_minors_memorised(this_player()) - 1;
       SOHM_MANAGER->set_minors_memorised(this_player(), memorised_spells);
    }

    if(query_sohm_spell_level(str) == SOHM_LESSER_SPELL)
    {      
       memorised_spells = SOHM_MANAGER->query_lessers_memorised(this_player()) - 1;
       SOHM_MANAGER->set_lessers_memorised(this_player(), memorised_spells);
    }

    if(query_sohm_spell_level(str) == SOHM_GREATER_SPELL)
    {      
       memorised_spells = SOHM_MANAGER->query_greaters_memorised(this_player()) - 1;
       SOHM_MANAGER->set_greaters_memorised(this_player(), memorised_spells);
    }

    if(query_sohm_spell_level(str) == SOHM_ADVANCED_SPELL)
    {      
       memorised_spells = SOHM_MANAGER->query_advanced_memorised(this_player()) - 1;
       SOHM_MANAGER->set_advanced_memorised(this_player(), memorised_spells);
    }

    // Sets the timer for when the player can next unmemorise a spell of that type
    SOHM_MANAGER->add_memorise_time(this_player(), spell_type);

    return 1;
}

// Wind whisper functions

public int
stell(string str)
{
    return (SOHM_SPELLS + "wind_whisper")->do_ability(str);
}

public int
shistory(string str)
{
    object player = this_player();

    // This will retrieve the last 10 messages in the tell history
    mixed history = SOHM_MANAGER->query_tell_history(player);
    if (!sizeof(history))
    {
        write("You have received no messages through the wind whisper spell.\n");
        return 1;
    }
    
    string history_text = "";
    history_text += sprintf("%15-s %-s\n", "Sender", "Message");
    history_text += sprintf("%'-'15-s %'-'60s\n", "", "");
    for (int index = sizeof(history) - 1; index >= 0; --index)
    {
        mixed message_item = history[index];
        if (sizeof(message_item) < 2)
        {
            continue;
        }
        string sender = message_item[0];
        string message = message_item[1];
        history_text += sprintf("%15-s %-s\n", capitalize(sender), message);
    }
    
    write(history_text + "\n");
    return 1;
}

// Special command for those who have the mage strength spell
// Allows the collection of minotaur blood.

public int
sbleed(string str)
{
    object * oblist;
    object player = this_player();
    object vial, pot;
    int in;

    if(!SOHM_MANAGER->query_memorised_spell(player,"hewavers_memorised"))
    {
        notify_fail("You need to have memorised mage strength before " +
           "you can bleed a corpse.\n");
        return 0;
    }
    
    if (!str)
    {
        notify_fail("What do you want to bleed?\n");
        return 0;
    }

    oblist = parse_this(str, "[the] %o");
    if (!sizeof(oblist))
    {
        return 0;
    }

    if (!oblist[0]->query_prop(CORPSE_S_RACE))
    {
        notify_fail("You can only bleed corpses.\n");
        return 0;
    }

    if (oblist[0]->query_prop(CORPSE_S_RACE) != "minotaur")
    {
        notify_fail("There is no need to bleed this corpse. You only need to "+
           "collect minotaur blood for the mage strength.\n");
        return 0;
    }

    if (oblist[0]->query_decay() < 4)
    {
        notify_fail("The corpse is too decayed and the blood too congealed "+
           "to be useable as a spell component.\n");
        return 0;
    }

    if (!objectp(vial = present("_std_potion_vial", player)))
    {
        notify_fail("Without a vial, you cannot collect the blood.\n");
        return 0; 
    }

    string corpse = oblist[0]->short();

    player->catch_tell("You kneel beside the " + corpse + " and fill a vial "+
           "with its blood.\n");
    tell_room(environment(player), QCTNAME(player)+ " kneels beside the " + 
            corpse + " and fills a vial with its blood.\n", 
            ({ player }), player);

    setuid();
    seteuid(getuid());

    pot = clone_object(SOHM_OBJS + "potions/mstrength_potion");
    pot->set_identified();

    // remove the vial
    if ((in = vial->num_heap()) > 1)
        vial->set_heap_size(--in);
    else
        vial->remove_object();

    // move it
    if (pot->move(player))
      pot->move(environment(player),1);  

    // decay corpse
    oblist[0]->decay_fun();  
        
    return 1;
}

// Functions for setting the teleport spell locations
// Move to common soul when working, change from WOHS to SOHM 


int
filter_tool(object obj)
{
      if (obj->id("wand"))
        return 1;
      else if (obj->id("staff"))
        return 1;
      else 
        return 0;
}

int
steleport(string str)
{
    int     size = 0;
    int     max_locs;
    object  caster = TP,
            env = environment(caster);
    string  fail, comm_str, arg, room, loc = "";
    mapping locations = SOHM_MANAGER->query_teleport_locations(caster);

    if(!SOHM_MANAGER->query_memorised_spell(caster, "arcanossalur_memorised") && 
       !SOHM_MANAGER->query_memorised_spell(caster, "svihossalur_memorised"))
    {
          notify_fail("What? You do not have such a command available to you.\n");
          return 0;
    }

    if(caster->query_guild_name_occ() == "School of High Magic")
    {
       max_locs = 3;
       comm_str = "steleport";
    }
    else
    {
       max_locs = min(10, (caster->query_guild_level_occ() + 3));
       comm_str = "wteleport";
    }

    
    if (!str)
    {
          write("The teleport commands available to you:\n\n"+
                "    " +comm_str+ " <list> for a list of memorised locations " +
                "you can teleport to.\n"+
                "    " +comm_str+ " <set [location]> to set where you stand as " +
                "a location to teleport to.\n"+
                "    " +comm_str+ " <remove [location]> to forget one of your " +
                "teleport locations.\n    " +
                "<cast arcanossalur [location]> to teleport to a remembered location.\n\n");
          return 1;
    }

    if(str == "list" || str == "locations")
    {
       if(!m_sizeof(SOHM_MANAGER->query_teleport_locations(caster)))
       {
          write("You cannot recall having previously set any locations.\n");
          return 1;
       }

       foreach(string element: m_indexes(locations))
       {
           size++;
           loc += capitalize(element);
           if (m_sizeof(locations) - size == 1)
               loc += " and ";
           else if (m_sizeof(locations) - size > 1)
               loc += ", ";
       }
       write("You remember having previously set the following teleportation locations:\n" +
       "   "+ loc + ".\n\n" +
       "You can set a total of " +max_locs+ " teleportation locations.\n");
          return 1;
    }

    if (str == "set")
    {
       write("By what name do you want to set this location that you want to " + 
             "teleport to?\n");
       return 1;          
     }

    if (parse_command(str, environment(caster), "'set' [to] %s", arg))
    {
        if (env->query_prop(ROOM_M_NO_TELEPORT) ||
            env->query_prop(ROOM_M_NO_TELEPORT_TO))
            fail = "Something prevents you from setting this place as a " +
                   "teleportation location.\n";

        if(fail)
        {
           write(fail);
           return 1;          
         }

        if (m_sizeof(locations) >= max_locs)
        {
            write("You cannot remember any more locations.\n");
            return 1;
        }

        if (!arg)
        {
            write("By what name do you want to set this location you want to " + 
            "teleport to?\n");
            return 1;          
        }    
    
        if (member_array(arg, m_indexes(locations)) > -1)
        {
            write("You already have a location memorized by that name.\n");
            return 1;
        }
    
        if (!file_size(file_name(env) + ".c"))
        {
            write("The fabric of space seems different here, you " +
                "don't think you are able to teleport from here.\n");
            return 1;
          
        }
    
        if (member_array(file_name(env), m_values(locations)) > -1)
        {
            write("You already have that location memorized.\n");
            return 1;
        }

         if (strlen(arg) > 15 || sizeof(explode(arg, " ")) > 1)
         {
            write("Please refrain from any longer names and use single words.\n");
            return 1;
         }

         // Need to be holding a wand or wielding a staff to add a location
         if (!caster->query_weapon(-1) && !caster->query_tool(-1))
         {
             write("You need to be wielding a staff or holding a wand " +
              "to mark a location for teleportation.\n");
             return 1;
         }

         object *weapon;

         /* Filter out non-staffs */
         if(caster->query_tool(-1))
           weapon = filter(caster->query_tool(-1), filter_tool);  

         if(!sizeof(weapon))
         {
             write("You aren't wielding a staff or holding a wand " +
                   "to mark a location for teleportation.\n");
	     return 1;
         }

        arg = lower_case(arg);

        write("You trace a rune on the " +
            (env->query_prop(ROOM_I_INSIDE) ? "floor" : "ground") +
            " with your " +weapon[0]->short()+ " and commit this place to memory " +
            "as " + capitalize(arg) + ".\n");

        set_this_player(caster);

        string set_room = file_name(env);

        all(" traces a rune on the " +
            (env->query_prop(ROOM_I_INSIDE) ? "floor" : "ground") +
            " with " +HIS(caster)+ " " +weapon[0]->short()+ 
            " and whispers a few arcane words of magic.\n");

        set_this_player(caster);
        SOHM_MANAGER->add_teleport_locations(caster, arg, set_room);
        return 1;

    }
    else if (parse_command(str, environment(caster), "[to] 'remove' %s", arg))
    {  
        if(member_array(lower_case(arg), m_indexes(locations)) > -1)
        {
            write("You whisper words of magic and uncommit " +
            "the place you knew as " + capitalize(arg) + " from memory.\n");
            SOHM_MANAGER->remove_teleport_locations(caster, lower_case(arg));
    
            return 1;
        }
        else
        {
            write("You cannot recall having previously named such a location.\n");
            return 1;
        }
    }

    notify_fail("What are you trying to do? " +comm_str+ " <set>, <remove> or <list>?\n");
    return 0;
}

