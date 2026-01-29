/*
 * Command Soul for the School of High Magic - Arman January 2016
 *
 * This is the command soul that every member of the SoHM will
 * have. It includes emotes as well as the abilities/spells that they
 * possess.  Based on Petros' Academic code.
 *
 * Created by Petros, September 2009
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
    return GUILD_NAME + " Soul"; 
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
        // Emotes
        "scalm"             : "scalm",
        "sconcentrate"      : "sconcentrate",
        "sfarewell"         : "sfarewell",
        "sfinger"           : "sfinger",
        "sfrown"            : "sfrown",
        "slean"             : "slean",
        "slisten"           : "slisten",
        "spouch"            : "spouch",
        "spractice"         : "spractice",
        "srubbish"          : "srubbish",
        "sslump"            : "sslump",
        "sstudy"            : "sstudy",

        // Help and Options
       /* slist will be a cantrip, ehtahhewa
        "slist"             : "slist",
        */
        "saspirant"         : "saspirant",
        "stitle"            : "stitle",
        "help"              : "help",        
        "burn"              : "sleave",
    ]);
}


// SoHM emotes in alphabetical order

public int
scalm(string str)
{
    if (strlen(str))
    {
        notify_fail("You can only calm yourself!\n");
        return 0;
    }
    
    // Concentrates on remaining calm in the face of distractions
    write("You focus your attention inward. The distractions around "
        + "you fade to nothingness, allowing you to remain perfectly "
        + "calm.\n");
    allbb(" focuses " +HIS(TP)+ " attention inwards, becoming perfectly calm.");
    return 1;
}

public int
sconcentrate(string str)
{
    if (strlen(str))
    {
        notify_fail("Concentrate on what?\n");
        return 0;
    }
    write("You close your eyes in concentration, going over your "+
          "spells in preparation for battle.\n");
    allbb(" closes " + this_player()->query_possessive() + " eyes and " +
        "mumbles the words to " + this_player()->query_possessive() + 
        " spells over and over, making certain that " + 
        this_player()->query_pronoun() + " has them memorized.");

    return 1;
}

public int
sfarewell(string str)
{
    object * oblist;
    
    notify_fail("Whom do you wish to say farewell to?\n");
    if (!str)
    {
        return 0;
    }

    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
    {
        return 0;
    }

    target(" informs you that " + this_player()->query_pronoun() + " must "
        + "return to " + this_player()->query_possessive() + " studies, and "
        + "bids you farewell.", 
        oblist);
    actor("You inform", oblist, " that you must return to your studies, and "
        + "bid farewell.");
    all2act(" informs", oblist, " that " + this_player()->query_pronoun()
        + " must return to " + this_player()->query_possessive()
        + " studies, and bids them farewell.");    
        
    return 1;
}

public int
sfinger(string str)
{
    if (strlen(str))
    {
        notify_fail("Finger what?\n");
        return 0;
    }

    write("You gently run your fingers across your spellbook, wiping "+
          "the dust from it.\n");
    allbb(" lightly brushes the dust from " +this_player()->query_possessive()+ 
        " leather-bound spellbook, lingering fondly on the cover.");
    return 1;
}

public int
sfrown(string str)
{
    object *oblist;
    
    if (!strlen(str))
    {
        write("You pause and frown, clearly showing your irritation by the "+
            "interruption.\n");
        allbb(" pauses and frowns, clearly showing " 
                +this_player()->query_possessive()+ " irritation "+
                "by the interruption.");
        return 1;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    oblist = oblist - ({ this_player() });
    
    if (!sizeof(oblist))
    {
        notify_fail("Frown at whom?\n");
        return 0;
    }     
   
    if (sizeof(oblist) > 1)
    {
        notify_fail("Please be a bit more precise - who do you want to frown "+
            "at?\n");
        return 0;
    } 

    actor("You pause and frown, cleary showing your irritation at", oblist,
        "'s interruption.");
    target(" pauses and frowns, clearly showing " 
        +this_player()->query_possessive()+ " irritation at your interruption.", 
        oblist);
    all2actbb(" pauses and frowns, clearly showing " 
        +this_player()->query_possessive()+ " irritation at", oblist, 
        "'s interruption.");
        
   return 1;
}

public int
slean(string str)
{
    object *polearm;
    
    if (strlen(str))
        return notify_fail("Lean on what?\n");

    polearm = this_player()->query_weapon(-1);
    
    if ((!sizeof(polearm)) || (!polearm[0]->id("staff")))
    {
        write("Weary from your spellcasting you support yourself on "+
            "your staff only to find that you haven't brought one. "+
            "You quickly regain your balance.\n");

        tell_room(environment(this_player()), QCTNAME(this_player()) +
                  " shifts " +this_player()->query_possessive()+ 
                  " weight to lean on a staff that isn't there. " +
                  QCTNAME(this_player()) + " regains " 
                  +this_player()->query_possessive()+ 
                  " balance and looks around sheepishly to see if " +
                  "anyone noticed the misstep.", ({ this_player() }), 
                  this_player());           
        return 1;
    }
    
    write("You lean on your " + polearm[0]->short() + 
        ", weary from spellcasting.\n");
    all(" leans on " +this_player()->query_possessive()+ " " 
        + polearm[0]->short() +  ", weary from spellcasting.");
    return 1;
}

public int
slisten(string str)
{
    // Listen to gain knowledge from others
    object * oblist;
    
    notify_fail("Whom do you wish to listen to?\n");
    if (!str)
    {
        return 0;
    }

    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
    {
        return 0;
    }

    target(" inclines " + this_player()->query_possessive() + " ear towards "
        + "you and listens closely for words of wisdom and knowledge.", 
        oblist);
    actor("You incline your ear towards", oblist, " and listen closely for "
        + "words of wisdom and knowledge.");
    all2act(" inclines " + this_player()->query_possessive() + " ear towards", 
        oblist, " and listens closely for words of wisdom and knowledge.");    
        
    return 1;
}

public int
spouch(string str)
{
    if (strlen(str))
        return notify_fail("What?\n");

    write("You look through your pouches, checking to make sure "+
          "that you have all of the necessary components.\n");
    all("'s supple fingers examine "+ this_player()->query_possessive() +
        " pouches, expertly checking all of "+ 
        this_player()->query_possessive() +" spell components.");
    return 1;
}

public int
spractice(string str)
{
    if (strlen(str))
    {
        notify_fail("Practicing should be done on your own!\n");
        return 0;
    }
    
    // Mental excercises
    write("You concentrate upon your magical studies, practicing forms "
        + "that you have been taught.\n");
    allbb(" concentrates upon " + this_player()->query_possessive()
        + " magical studies, practicing forms " +this_player()->query_pronoun()
        + " has been taught.");
    return 1;
}

public int
srubbish(string str)
{
    object *oblist;

    if (!str || !strlen(str))
    {
        notify_fail("Who has a bad opinion?\n");
        return 0;
    }

    oblist = parse_this(str, "%l");

    if (!sizeof(oblist))
    {
        notify_fail("Who has a bad opinion?\n");
        return 0;
    }

    target(" dismisses your opinions as utter rubbish.", oblist);
    all2act(" dismisses", oblist,"'s opinions as utter rubbish.");
    actor("You dismiss", oblist, "'s opinions as utter rubbish.");
    return 1;
}

public int
sslump(string str)
{
    if (strlen(str))
    {
        notify_fail("Slump what?\n");
        return 0;
    }

    write("You slump to the ground, overcome with exhaustion from "+
          "spellcasting.\n");
    all(" pales and slumps to the ground, mentally and physically "+
        "exhausted.");
    return 1;
}

public int
sstudy(string str)
{
    if (strlen(str))
    {
        notify_fail("You should study on your own!\n");
        return 0;
    }
    
    // Go over study notes
    write("You pull out your spellbook and study it closely, "
        + "ignoring your surroundings.\n");
    allbb(" pulls out " + this_player()->query_possessive() + " spellbook " +
        "and studies it closely, ignoring "
        + this_player()->query_possessive() + " surroundings.");
    return 1;
        
}

// List of other SoHM member function - through cantrip ehtahhewa

public int
slist(string str)
{
    // List of other SoHM members
    mixed list = SOHM_MANAGER->query_awake_members(this_player());
    
    list = sort_array(map(list, &->query_presentation()));  
    list = implode(map(list, &operator(+)("- ",)), "\n");  

    this_player()->more("The following Students of High Magic are currently " +
                        "in the realms:\n"+ list + "\n");
    
    return 1;
}

public int
saspirant(string str)
{
   int aspirant = SOHM_MANAGER->query_aspirant_title(this_player());
   string on_off;

   if(this_player()->query_guild_level_occ() < 8)
   {
        notify_fail("You have not yet reached a level to claim to be " +
            "an Aspirant of High Sorcery!\n");
        return 0;
   }
      
   if(!str)
   {
       if(aspirant)
         on_off = "off";
       else
         on_off = "on";

       write("Your Aspirant of High Sorcery title is currently turned " 
              +on_off+".\n");
       return 1;
    }

    if(str == "on")
    {
       write("You turn your Aspirant of High Sorcery title on.\n");
       SOHM_MANAGER->set_aspirant_title(this_player(), 0);
       return 1;
    }

    if(str == "off")
    {
       write("You turn your Aspirant of High Sorcery title off.\n");
       SOHM_MANAGER->set_aspirant_title(this_player(), 1);
       return 1;
    }

    write("Turn your Aspirant of High Sorcery title on or off using " +
       "the command 'saspirant on' or 'saspirant off'.\n");
    return 1;
} 

public int
stitle(string str)
{

   if(this_player()->query_guild_level_occ() < 8)
   {
        notify_fail("You have not yet reached a level to be " +
            "able to claim an alternative title!\n");
        return 0;
   }
      
   if(!str)
   {
       write("stitle what? Your optional title choices based on your other " +
             "guilds are <racial>, <layman>, <craft> or <off>.\n");
       return 1;
   }

   string guild_name;

   if(str == "racial")
   {
      if(!TP->query_guild_name_race())
      {
          notify_fail("You do not have a racial guild!\n");
          return 0;
      }

      if(SOHM_MANAGER->query_alt_race_title(this_player()))
      {
          notify_fail("You are already displaying a title reflecting " +
             "your racial heritage!\n");
          return 0;
      }

      guild_name = TP->query_guild_name_race();
      if(IN_ARRAY(guild_name, ELIGIBLE_RACIAL_TITLES))
      {
          SOHM_MANAGER->set_alt_race_title(this_player(), 1);
          SOHM_MANAGER->set_alt_layman_title(this_player(), 0);
          SOHM_MANAGER->set_alt_craft_title(this_player(), 0);
          write("You change your title to reflect the influence of " +
             "your racial heritage.\n");
          return 1;
      }

      write("There is no alternative title for that racial guild.\n");
      return 1;
   }

   if(str == "layman")
   {
      if(!TP->query_guild_name_lay())
      {
          notify_fail("You do not have a layman guild!\n");
          return 0;
      }

      if(SOHM_MANAGER->query_alt_layman_title(this_player()))
      {
          notify_fail("You are already displaying a title reflecting " +
             "your layman profession!\n");
          return 0;
      }

      guild_name = TP->query_guild_name_lay();
      if(IN_ARRAY(guild_name, ELIGIBLE_LAYMAN_TITLES))
      {
          SOHM_MANAGER->set_alt_race_title(this_player(), 0);
          SOHM_MANAGER->set_alt_layman_title(this_player(), 1);
          SOHM_MANAGER->set_alt_craft_title(this_player(), 0);
          write("You change your title to reflect the influence of " +
             "your layman profession.\n");
          return 1;
      }

      write("There is no alternative title for that layman guild.\n");
      return 1;
   }

   if(str == "craft")
   {
      if(!TP->query_guild_name_craft())
      {
          notify_fail("You do not have a craft guild!\n");
          return 0;
      }

      if(SOHM_MANAGER->query_alt_craft_title(this_player()))
      {
          notify_fail("You are already displaying a title reflecting " +
             "your craft profession!\n");
          return 0;
      }

      guild_name = TP->query_guild_name_craft();
      if(IN_ARRAY(guild_name, ELIGIBLE_CRAFT_TITLES))
      {
          SOHM_MANAGER->set_alt_race_title(this_player(), 0);
          SOHM_MANAGER->set_alt_layman_title(this_player(), 0);
          SOHM_MANAGER->set_alt_craft_title(this_player(), 1);
          write("You change your title to reflect the influence of " +
             "your crafting profession.\n");
          return 1;
      }

      write("There is no alternative title for that craft guild.\n");
      return 1;
   }

   if(str == "off")
   {
       write("You turn your alternate guild title off.\n");
       SOHM_MANAGER->set_alt_race_title(this_player(), 0);
       SOHM_MANAGER->set_alt_layman_title(this_player(), 0);
       SOHM_MANAGER->set_alt_craft_title(this_player(), 0);
       return 1;
   }

    write("Select your alternative guild title using " +
       "the command 'stitle <guild type>'. Your options " +
       "are <racial>, <layman>, <craft> or <off>.\n");
    return 1;
}

public int
help(string str)
{
    // Access help files
    string content, *files; 
    setuid(); 
    seteuid(getuid()); 

    if (!stringp(str) || !strlen(str))
    { 
        return 0; 
    }
    
    if (str == "sohm") 
    {         
        if (!pointerp(files = get_dir(SOHM_HELP)) || !sizeof(files))
        {
            return 0; 
        }
        
        if (!stringp(content = read_file(SOHM_HELP + "general")))
        {
            notify_fail("Something is terribly wrong! Please contact "
                + "the guildmaster and let them know that the help files "
                + "for the School of High Magic are not working property.\n");
            return 0;
        }
        
        write("You open up your spellbook and read the notes "
            + "introducing the School of High Magic.\n");
        this_player()->more(content);
        return 1;
    } 

    if (sscanf(str, "sohm %s", str) != 1)
    {
        return 0;
    }
    
    str = lower_case(str); // set everything to lowercase
    // Players can get information about spells that they know
    if ((SOHM_MANAGER->query_scribed_spell(this_player(), str)
         && stringp(content = read_file(SOHM_SPELLS_HELP + str)))
        || stringp(content = read_file(SOHM_HELP + str)))
    {
        write("You flip through your spellbook and read the notes "
            + "pertaining to " + capitalize(str) + ".\n");
        this_player()->more(content);
        return 1;         
    }

    notify_fail("You can't seem to find any notes on that topic "
        + "within your spellbook.\n"); 
    return 0;     
}

// Functions to leave the SoHM

public void
remove_confirmation_prop(object player)
{    
    player->remove_prop(SOHM_I_CONFIRM_LEAVE);
}

public int
sleave(string str)
{
    object player = this_player();

    if (!objectp(player))
    {
        return 0;
    }
    
    if (!strlen(str) || str != "school of high magic spellbook")
    {
        notify_fail("Did you want to <burn school of high magic spellbook>?\n");
        return 0;
    }
    
    if (!IS_MEMBER(player))
    {
        notify_fail("You are not a member of the School of High Magic!\n");
        return 0;
    }
    
    if (!player->query_prop(SOHM_I_CONFIRM_LEAVE))
    {
        write("Type the <burn school of high magic spellbook> command again " +
           "in the next minute to confirm that you really want to leave.\n");
        player->add_prop(SOHM_I_CONFIRM_LEAVE, 1);
        // Give them 1 minute to respond. If they don't then just remove
        // the property
        set_alarm(60.0, 0.0, &remove_confirmation_prop(player));
        return 1;
    }
    
    player->remove_prop(SOHM_I_CONFIRM_LEAVE);
    setuid();
    seteuid(getuid());
    if (SOHM_JOINROOM->leave_guild(player))
    {
        write("You summon for the last time arcane flames, and watch " +
            "your leather-bound spellbook burn into ash. You have " +
            "abandoned the way of the Magi and have left the School " +
            "of High Magic.\n");
        say(QCTNAME(player) + " summons arcane flames to devour " + 
            this_player()->query_possessive()+ " spellbook, leaving the " +
            "School of High Magic.\n");
        return 1;
    }
    
    notify_fail("For some reason you can't leave the School of High Magic.\n");
    return 0;
}

