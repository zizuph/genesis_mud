/*
 * Command Soul for the Order of the Stars - Arman April 2017
 *
 * This is the command soul that every member of the OotS will
 * have. It includes emotes as well as the abilities/spells that they
 * possess. 
 */

#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <adverbs.h>
#include "../defs.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";

#include "../oots_god_descs.h"
#include "oots_soul_revelations.h"

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
        /* Spell name : Function name */
        "oheal"             : "do_ability",
        "obless"            : "do_ability",
        "osmite"            : "do_ability",
        "oprotect"          : "do_ability",
        "orefresh"          : "do_ability",
        "ocalm"             : "do_ability",
        "oradiance"         : "do_ability",
        "odetect"           : "do_ability",
        "oturn"             : "do_ability",
        "ocure"             : "do_ability",
        "omend"             : "do_ability",
        "oheroism"          : "do_ability",
        "osong"             : "do_ability",
        "osanctify"         : "do_ability",
        // Emotes
        "oarrange"          : "oarrange",
        "obaliset"          : "obaliset",
        "obison"            : "obison",
        "oclasp"            : "oclasp",
        "ocourage"          : "ocourage",
        "ofinger"           : "ofinger",
        "oflick"            : "oflick",
        "ojustice"          : "ojustice",
        "okneel"            : "okneel",
        "opray"             : "opray",
        "opouch"            : "opouch",
        "oredeem"           : "oredeem",
        "ostare"            : "ostare",
        "othought"          : "othought",
        "othrust"           : "othrust",
        "ounity"            : "ounity",

        // Help and Options
        "olist"             : "olist",
        "help"              : "help",        
        "break"             : "oleave",
        "revelations"       : "revelations",

        // Casting and Spell Commands
        "prayers"       : "prayers",
    ]);
}

public mapping
query_ability_map()
{
    return ([
        "oheal"        : OOTS_SPELLS + "oheal",
        "obless"       : OOTS_SPELLS + "obless",
        "osmite"       : OOTS_SPELLS + "osmite",
        "oprotect"     : OOTS_SPELLS + "oprotect",
        "orefresh"     : OOTS_SPELLS + "orefresh",
        "ocalm"        : OOTS_SPELLS + "ocalm",
        "oradiance"    : OOTS_SPELLS + "oradiance",
        "odetect"      : OOTS_SPELLS + "odetect",
        "oturn"        : OOTS_SPELLS + "oturn",
        "ocure"        : OOTS_SPELLS + "ocure",
        "omend"        : OOTS_SPELLS + "omend",
        "oheroism"     : OOTS_SPELLS + "oheroism",
        "osong"        : OOTS_SPELLS + "osong",
        "osanctify"    : OOTS_SPELLS + "osanctify",
    ]);
}

public int
is_valid_medallion(object caster, object obj)
{
    if (!objectp(obj) || !obj->id("oots_guild_object"))
    {
        return 0;
    }
    
    return 1;
}

// OotS emotes in alphabetical order

public int
oarrange(string str)
{
    if(oots_god_name(TP) != "Branchala")
    {
        notify_fail("What?\n");
        return 0;
    }

    if (str)
    {
        notify_fail("You cannot arrange pentameter in that way!\n");
        return 0;
    }

    write("You arrange the clash of steel-on-steel into iambic pentameter.\n");
    allbb(" arranges the clash of steel-on-steel into iambic pentameter.");
    return 1;
}

public int
obaliset(string str)
{
    if(oots_god_name(TP) != "Branchala")
    {
        notify_fail("What?\n");
        return 0;
    }

    if(!str)
      str = "absentmindedly";

    if (FULL_ADVERB(str) == "")
    {
        notify_fail("You cannot practice your baliset fingering in that way!\n");
        return 0;
    }

    string how = FULL_ADVERB(str);

    write("You stare into space, your fingers moving " +how+ " over " +
        "an imagined baliset.\n");
    allbb(" stares into space, " +HIS(TP)+ " fingers moving " +how+
        " over an imagined baliset.");
    return 1;
}

public int
obison(string str)
{
    if(oots_god_name(TP) != "Kiri-Jolith")
    {
        notify_fail("What?\n");
        return 0;
    }

    if (str)
    {
        notify_fail("You cannot offer a prayer to Kiri-Jolith in that way!\n");
        return 0;
    }

    if(CLOCK->query_night() && !(environment(TP)->query_prop(ROOM_I_INSIDE)))
    {
        write("You dedicate a prayer to Kiri-Jolith.\nAbove you, the " +
            "celestial constellation of the Bison Head seems to briefly " +
            "shine more brightly above you.\n");
        allbb(" dedicates a prayer to Kiri-Jolith.\nAbove you, the " +
            "celestial constellation of the Bison Head seems to briefly " + 
            "shine more brightly above you.");
    return 1;
    }

    write("You dedicate a prayer to Kiri-Jolith.\n");
    allbb(" dedicates a prayer to Kiri-Jolith.");
    return 1;
}

public int
oclasp(string str)
{
    object * med = filter(all_inventory(TP), &is_valid_medallion(TP,));
    string medallion = med[0]->short();

    if (!str)
    {
        notify_fail("Clasp what? Your medallion of faith?\n");
        return 0;
    }

    if(!parse_command(str, TP, "[the] %o", med ))
    {
        notify_fail("Clasp what? The medallion of faith?\n");
        return 0;
    }

    write("You clasp your " +medallion+ ", whispering a silent prayer " +
          "of thanks to " + oots_god_name(TP)+".\n");
    allbb(" clasps " +this_player()->query_possessive()+ " " +medallion+ 
          ", whispering a silent prayer of thanks to " +
          oots_god_name(TP) + ".");
    return 1;
}

public int
ocourage(string str)
{
    object * med = filter(all_inventory(TP), &is_valid_medallion(TP,));
    string medallion = med[0]->short();
    string text1, text2;

    if(oots_god_name(TP) != "Kiri-Jolith")
    {
        notify_fail("What?\n");
        return 0;
    }

    object *weapon;
    weapon = this_player()->query_weapon(-1);

    if(!str)
      str = "resolutely";

    if ((!sizeof(weapon)))
    {
        text1 = medallion + " in your hands";
        text2 = medallion + " in " +HIS(TP)+ " hands";
    }
    else
    {
        text1 = medallion + " in one hand and your " +weapon[0]->short()+
            " in the other";
        text2 = medallion + " in one hand and " +HIS(TP)+ " " +
            weapon[0]->short()+ " in the other";
    }

    if (FULL_ADVERB(str) == "")
    {
        notify_fail("You can't clasp your medallion in that way!\n");
        return 0;
    }

    string how = FULL_ADVERB(str);

    write("You " +how+ " clasp your " +text1+ ", praying to " +
        "Kiri-Jolith for courage in battle.\n");
    allbb(" " +how+ " clasps " +HIS(TP)+ " " +text2+ 
        ", praying to Kiri-Jolith for courage in battle.");

    return 1;
}

public int
ofinger(string str)
{
    object * med = filter(all_inventory(TP), &is_valid_medallion(TP,));
    string medallion = med[0]->short();

    if(!str)
      str = "absentmindedly";

    if (FULL_ADVERB(str) == "")
    {
        notify_fail("You can't run a finger along the medallion of " +
                    "faith in that way.\n");
        return 0;
    }

    string how = FULL_ADVERB(str);

    write("You run a finger " +how+ " around the symbols on your " +
          medallion+ ".\n");
    allbb(" runs a finger " +how+ " around the symbols on " +HIS(TP)+ 
          " " +medallion+ ".");
    return 1;
}


public int
oflick(string str)
{

    if(oots_god_name(TP) != "Branchala")
    {
        notify_fail("What?\n");
        return 0;
    }

    object *weapon;
    weapon = this_player()->query_weapon(-1);

    if(!str)
      str = "casually";

    if ((!sizeof(weapon)))
    {
	notify_fail("You are not wielding a weapon to flick!\n");
        return 0;
    }

    if (FULL_ADVERB(str) == "")
    {
        notify_fail("You can't flick your weapon in that way!\n");
        return 0;
    }

    string how = FULL_ADVERB(str);

    write("You " +how+ " flick your " +weapon[0]->short()+ 
        ", producing a pure ringing note.\n");
    allbb(" " +how+ " flicks " +HIS(TP)+ " " +weapon[0]->short()+ 
        ", producing a pure ringing note.");

    return 1;
}

public int
ojustice(string str)
{
    object *oblist;
    object * med = filter(all_inventory(TP), &is_valid_medallion(TP,));
    string medallion = med[0]->short();

    if(oots_god_name(TP) != "Kiri-Jolith")
    {
        notify_fail("What?\n");
        return 0;
    }
    
    if (!strlen(str))
    {
        write("You steel your resolve, grasping your " +medallion+ 
            " fervently, praying that " +oots_god_name(TP)+ " will support " +
            "you as you enact judgment on your foes.\n");
        allbb(" steels " +HIS(TP)+ " resolve, grasping " +HIS(TP)+
            " " +medallion+ " fervently, praying that " +oots_god_name(TP)+ 
            " will support " +HIM(TP)+ " in enacting judgment on " +
            HIS(TP)+ " foes.");
        return 1;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    oblist = oblist - ({ this_player() });
    
    if (!sizeof(oblist))
    {
        notify_fail("Enact judgment upon whom?\n");
        return 0;
    }     
   
    if (sizeof(oblist) > 1)
    {
        notify_fail("Who do you specifically want to enact " +
                    "judgment upon?\n");
        return 0;
    } 

    object ob = oblist[0];

    actor("You steel your resolve, grasping your " +medallion+ 
        " fervently, praying that " +oots_god_name(TP)+ " will support " +
        "you as you enact judgment upon", oblist, ".");
    target(" steels " +HIS(TP)+ " resolve, grasping " +HIS(TP)+
        " " +medallion+ " fervently, praying that " +oots_god_name(TP)+ 
        " will support " +HIM(TP)+ " in enacting judgment upon you.", oblist);
    all2actbb(" steels " +HIS(TP)+ " resolve, grasping " +HIS(TP)+
        " " +medallion+ " fervently, praying that " +oots_god_name(TP)+ 
        " will support " +HIM(TP)+ " in enacting judgment upon", oblist, ".");   
        
   return 1;
}

public int
okneel(string str)
{
    if(!str)
      str = "calmly";

    if (FULL_ADVERB(str) == "")
    {
        notify_fail("You can't kneel in that way.\n");
        return 0;
    }

    string how = FULL_ADVERB(str);

    write("You lower yourself to your knees and " +how+ " pray to " +
          oots_god_name(TP) + " for guidance.\n");
    allbb(" lowers " +HIM(TP)+ "self to " +HIS(TP)+ " knees and " +how+ 
          " prays to " +oots_god_name(TP)+ " for guidance.");
    return 1;
}

public int
opray(string str)
{
    string penalty_message = "";
    int penalty_value;

    if (!str)
    {
       write("You close your eyes and offer a silent prayer to " +
             oots_god_name(TP)+", meditating on how you are " +
             "progressing in the eyes of your " +oots_god_desc(TP)+ ".\n");
       allbb(" closes " +HIS(TP)+ " eyes and offers a silent prayer to " +
             oots_god_name(TP)+ ".");

       setuid();
       seteuid(getuid());

       int cl = TP->query_guild_level_lay() * OOTS_PROGRESSION_MOD;
       int dl = (TP->query_guild_level_lay() + 1) * OOTS_PROGRESSION_MOD;

       int layman_stat = min(60, TP->query_stat(SS_LAYMAN));
       int guild_stat;

       if(TP->query_skill(OOTS_GUILD_XP) > 0)
          guild_stat = max(0, OOTS_GUILD_STAT_FORMULA(TP));
       else
          guild_stat = 0; 
       
       int current_prog = (layman_stat + guild_stat) - cl;
       int prog_required = dl - cl;

       int level_ratio = ftoi((itof(current_prog) / itof(prog_required)) * 100.0);
       string progress_message;

       if(TP->query_guild_level_lay() > 7)
       {
          write("You have progressed as far as you can in the Order.\n");
          return 1;
       }
    
       switch(level_ratio)
       {
        case 0..10:
          progress_message = "newly ordained to your position in the Holy " +
                             "Order of the Stars";
          break;
        case 11..20:
          progress_message = "just beginning your journey to your next " +
                             "ordainment";
          break;
        case 21..30:
          progress_message = "early in your journey to to your next " +
                             "ordainment";
          break;
        case 31..40:
          progress_message = "far from progressing to your next ordainment";
          break;
        case 41..50:
          progress_message = "almost halfway to your next ordainment";
          break;
        case 51..60:
          progress_message = "over halfway to your next ordainment";
          break;
        case 61..70:
          progress_message = "journeying well towards your next ordainment";
          break;
        case 71..80:
          progress_message = "journeying very well towards your next " +
                             "ordainment";
          break;
        case 81..90:
          progress_message = "close to your next ordainment";
          break;
        case 91..100:
          progress_message = "very close to your next ordainment";
          break;
        default:
          progress_message = "uncertain of when your next ordainment " +
                             "will be";
          break;
       }

       if(TP->query_skill(OOTS_GUILD_XP) < 0)
       {
           penalty_value = TP->query_skill(OOTS_GUILD_XP);
           penalty_message = "\nHaving previously left the Holy Order of " +
              "Stars and returned to the faith, the gods ";

           switch(penalty_value)
           {
               case -1000..-1:
                 penalty_message += "are very close to having complete " +
                                    "faith in you again.\n";
                 break;
               case -5000..-1001:
                 penalty_message += "are close to having complete " +
                                    "faith in you again.\n";
                 break;
               case -10000..-5001:
                 penalty_message += "are getting close to having complete " +
                                    "faith in you again.\n";
                 break;
               case -25000..-10001:
                 penalty_message += "are gaining faith in you again.\n";
                 break;
               case -50000..-25001:
                 penalty_message += "are slowly gaining faith in you again.\n";
                 break;
               case -75000..-50001:
                 penalty_message += "are growing more trusting of you.\n";
                 break;
               case -100000..-75001:
                 penalty_message += "are growing slightly more trusting " +
                     "of you.\n";
                 break;
               case -125000..-100001:
                 penalty_message += "are a bit distant to you.\n";
                 break;
               case -150000..-125001:
                 penalty_message += "are distant to you.\n";
                 break;
               case -175000..-150001:
                 penalty_message += "are somewhat untrusting of you.\n";
                 break;
               case -200000..-175001:
                 penalty_message += "are untrusting of you.\n";
                 break;
               default:
                 penalty_message += "are untrusting of you. You will need " +
                     "to prove your dedication before they will let you " +
                     "progress past a certain point.\n";
                 break;
            }
       }            
    
       write("You are " +progress_message+".\n" + penalty_message);
       return 1;
    }
    
    if(LANG_IS_OFFENSIVE(str))
    {
       notify_fail("Your " +oots_god_desc(TP)+ " would not look kindly " +
          "on a prayer including words of profanity.\n");
       return 0;
    } 

    write("You close your eyes and offer a prayer to " +oots_god_name(TP)+ 
          ": " +C(str)+ "\n");
    allbb(" closes " +HIS(TP)+ " eyes and offers a silent prayer to " +
             oots_god_name(TP)+": " +C(str));
    return 1;
}

public int
opouch(string str)
{
    if(!str)
      str = "excitedly";

    string how = FULL_ADVERB(str);

    if(oots_god_name(TP) != "Branchala")
    {
        notify_fail("What?\n");
        return 0;
    }

    if(present("_oots_instrument_flute", TP ))
    {
        write("You rummage " +how+ " through your pouches.\n");
        allbb(" rummages " +how+ " through " +HIS(TP)+ " pouches.");
        return 1;
    }

    write("You rummage " +how+ " through your pouches, finding a " +
        "traditional wooden flute with the markings of Branchala " +
        "lovingly carved along it!\n");
    allbb(" rummages " +how+ " through " +HIS(TP)+ " pouches, " +
        "eventually pulling from them a traditional wooden flute!");

    setuid();
    seteuid(getuid());

    object flute = clone_object(OOTS_OBJS + "flute");
    flute->move(TP, 1);

    return 1;
}

public int
oredeem(string str)
{
    object * oblist;
    object tar;
    object * med = filter(all_inventory(TP), &is_valid_medallion(TP,));
    string medallion = med[0]->short();
    
    notify_fail("Who do you wish to redeem?\n");
    if (!str)
    {
        return 0;
    }

    oblist = parse_this(str, "[the] %l");
    oblist = oblist - ({ this_player() });

    if (!sizeof(oblist))
    {
        return 0;
    }

    tar = oblist[0];

    // Only top level clerics can redeem another member
    if(OOTS_LEVEL(TP) < 9)
    {
        notify_fail("Only Clerics of the Holy Order of the Stars " +
            "may redeem a returning follower.\n");
	return 0;
    }

    if(!IS_OOTS(tar))
    {
        notify_fail(QCTNAME(tar)+ " is not a follower of the Holy Order " +
            "of the Stars. You can only redeem fellow disciples.\n");
	return 0;
    }

    if(tar->query_skill(OOTS_GUILD_XP) > -1)
    {
        notify_fail(QCTNAME(tar)+ " does not need to be redeemed in the " +
            "eyes of the Gods.\n");
	return 0;
    }

    actor("You hold out your " +medallion+ " to", oblist, " and beseech " +
        oots_god_name(TP)+ " to forgive " +tar->query_objective()+ ".\n" +
        "You feel your prayers have been answered.");
    target(" holds out " +HIS(TP)+ " " +medallion+ " to you, beseeching "+ 
        oots_god_name(TP)+ " to forgive you.\nYou feel the blessings of " +
        "the Gods flow through you, and redemption of your past failings " +
        "forgiven.", oblist);
    all2actbb(" holds out " +HIS(TP)+ " " +medallion+ " to", oblist,
        " beseeching " +oots_god_name(TP)+ " to forgive " +tar->query_objective()+ 
        ".");  

    tar->set_skill(OOTS_GUILD_XP, 0); 
        
    return 1;
}

public int
ostare(string str)
{
    if(!str)
      str = "thought";

    if(E(TP)->query_prop(ROOM_I_INSIDE))
    {
        notify_fail("You are inside and cannot stare up in to the night " +
                    "sky.\n");
        return 0;  
    }

    if(GET_TIMEOFDAY != "night")
    {
        notify_fail("It is not night, so you cannot make out the " +
                    "constellations in the skies above you.\n");
        return 0;
    }

    if (FULL_ADVERB(str) == "")
    {
        notify_fail("You cannot stare up in to the sky that way.\n");
        return 0;
    }

    string how = FULL_ADVERB(str);

    write("You stare " +how+ " up into the night sky, ponder the portents " +
          "of the missing constellations of the Queen of Darkness and " +
          "the Valiant Warrior.\n");
    allbb(" stares " +how+ " up into the night sky, pondering the " +
          "portents of the missing contellations of the Queen of Darkness " +
          "and the Valiant Warrior.");
    return 1;
}

public int
othought(string str)
{
    if(oots_god_name(TP) != "Branchala")
    {
        notify_fail("What?\n");
        return 0;
    }

    if (str)
    {
        notify_fail("You cannot get lost in thought that way!\n");
        return 0;
    }

    write("You lose yourself in thought, reaching for an elusive rhyme.\n");
    allbb(" seems lost in thought, reaching for an elusive rhyme.");
    return 1;
}

public int
othrust(string str)
{
    object *oblist;
    object * med = filter(all_inventory(TP), &is_valid_medallion(TP,));
    string medallion = med[0]->short();
    
    if (!strlen(str))
    {
        write("With a cry you thrust your " +medallion+ " forward, feeling " +
              "the strength and support of " +oots_god_name(TP)+ 
              " flow through you.\n");
        allbb(" thrusts forward " +HIS(TP)+ " " +medallion+ " with a " +
              "righteous cry, strong in " +HIS(TP)+ " faith in " +
              oots_god_name(TP)+ " to provide strength and support.");
        return 1;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    oblist = oblist - ({ this_player() });
    
    if (!sizeof(oblist))
    {
        notify_fail("Thrust your medallion towards whom?\n");
        return 0;
    }     
   
    if (sizeof(oblist) > 1)
    {
        notify_fail("Who do you specifically want to thrust your " +
                    "medallion towards?\n");
        return 0;
    } 

    object ob = oblist[0];

    actor("With a righteous cry you thrust your " +medallion+ " towards", 
          oblist, ", feeling the strength and support of " +
          oots_god_name(TP)+ " flow through you.");
    target(" thrusts " +HIS(TP)+ " " +medallion+ " towards you with "+ 
           "a righteous cry, strong in " +HIS(TP)+ " faith in " +
           oots_god_name(TP)+ " to provide strength and support.", oblist);
    all2actbb(" thrusts " +HIS(TP)+ " " +medallion+ " towards", oblist,
              " with a righteous cry, strong in " +HIS(TP)+ " faith in " +
              oots_god_name(TP)+ " to provide strength and support.");

   if(ob->query_prop(LIVE_I_UNDEAD))
   {
      int fear = random(TP->query_stat(SS_WIS)) - ob->query_stat(SS_DIS);

      if(fear > 0)
      {
         switch(fear)
         {
            case 1..10:
              ob->command("$frown uncomfort");
              break;
            case 11..30:
              ob->command("$blanch uneasil");
              break;
            case 31..50:
              ob->command("$back fear");
              break;
            default:
              ob->command("$stagger terror");
              break;
         }
      }
   }         
        
   return 1;
}

public int
ounity(string str)
{
    object *oblist;
    object * med = filter(all_inventory(TP), &is_valid_medallion(TP,));
    string medallion = med[0]->short();

    if(oots_god_name(TP) != "Kiri-Jolith")
    {
        notify_fail("What?\n");
        return 0;
    }
    
    if (!strlen(str))
    {
        notify_fail("Offer a prayer of unity for whom?\n");
        return 0;
    }
    
    oblist = parse_this(str, "[for] %l");
    oblist = oblist - ({ this_player() });
    
    if (!sizeof(oblist))
    {
        notify_fail("Offer a prayer of unity for whom?\n");
        return 0;
    }     
   
    if (sizeof(oblist) > 1)
    {
        notify_fail("Who do you specifically want to offer " +
                    "a prayer for?\n");
        return 0;
    } 

    object ob = oblist[0];

    actor("You offer a prayer of unity to " +oots_god_name(TP)+ " for",
        oblist, ", that your camaraderie might be strengthened.");
    target(" offers a prayer of unity to " +oots_god_name(TP)+ 
        ". You feel as if your heart of soul have newfound " +
        "strength.", oblist);
    all2actbb(" offers a prayer of unity to " +oots_god_name(TP)+ 
        " for greater camaraderie with", oblist, ".");   
        
   return 1;
}


// List of other OotS members function 

public int
olist(string str)
{
    // List of other OotS members
    mixed list = OOTS_MANAGER->query_awake_members(this_player());
    
    list = sort_array(map(list, &->query_presentation()));  
    list = implode(map(list, &operator(+)("- ",)), "\n");  

    this_player()->more("The following followers of the Holy Order of " +
                        "the Stars are currently in the realms:\n"+ 
                        list + "\n");
    
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
    
    if (str == "oots") 
    {         
        if (!pointerp(files = get_dir(OOTS_HELP)) || !sizeof(files))
        {
            return 0; 
        }
        
        if (!stringp(content = read_file(OOTS_HELP + "help")))
        {
            notify_fail("Something is terribly wrong! Please contact "
                + "the guildmaster and let them know that the help files "
                + "for the Order of the Stars are not working property.\n");
            return 0;
        }

        this_player()->more(content);
        return 1;
    } 

    if (sscanf(str, "oots %s", str) != 1)
    {
        return 0;
    }
    
    str = lower_case(str); // set everything to lowercase
    // Players can get information about spells that they know
    if ((objectp(this_player()->find_spell(str))
         && stringp(content = read_file(OOTS_SPELLS_HELP + str)))
        || stringp(content = read_file(OOTS_HELP + str)))
    {
        this_player()->more(content);
        return 1;         
    }

    notify_fail("There are no help topics or prayers by that name.\n"); 
    return 0;     
}

// Functions to leave the OotS

public void
remove_confirmation_prop(object player)
{    
    player->remove_prop(OOTS_I_CONFIRM_LEAVE);
}

public int
oleave(string str)
{
    object player = this_player();

    if (!objectp(player))
    {
        return 0;
    }
    
    if (!strlen(str) || str != "faith with the order of the stars")
    {
        notify_fail("Did you want to <break faith with the order of " +
                    "the stars>?\n");
        return 0;
    }
    
    if (!IS_MEMBER(player))
    {
        notify_fail("You are not a member of the Order of the Stars!\n");
        return 0;
    }
    
    if (!player->query_prop(OOTS_I_CONFIRM_LEAVE))
    {
        write("Type the <break faith with the order of the stars> command " +
              "again in the next minute to confirm that you really want " +
              "to leave.\n");
        player->add_prop(OOTS_I_CONFIRM_LEAVE, 1);
        // Give them 1 minute to respond. If they don't then just remove
        // the property
        set_alarm(60.0, 0.0, &remove_confirmation_prop(player));
        return 1;
    }
    
    player->remove_prop(OOTS_I_CONFIRM_LEAVE);
    setuid();
    seteuid(getuid());
    if (OOTS_JOINROOM->leave_guild(player))
    {
        write("You close your eyes and release your spiritual bond with " +
          "the Holy Order of the Stars.\n\nYou feel the presence of " +
          "Kiri Jolith briefly - stern and solemn, the joyful song of " +
          "Branchala play briefly tinged with sadness, and then the " +
          "presence of Mishakal - sorrowful but understanding, and then " +
          "you feel a sense of emptiness.\n");
        return 1;
    }
    
    notify_fail("For some reason you can't leave the Order of the Stars.\n");
    return 0;
}

/*
 * Function name: prayers
 * Description:   List the active prayers.
 */
public int
revelations(string str)
{

    string content, *files, loc;
    mapping revelations = OOTS_MANAGER->query_oots_revelations(TP);

    if (member_array(lower_case(str), m_values(revelations)) > -1)
    {
       foreach(string element: m_indexes(revelations))
       {
           int mvalue = member_array(lower_case(str), m_values(revelations));
           int mindex = member_array(element, m_indexes(revelations));

// DEBUG("mvalue : "+mvalue+" mindex: " +mindex+ ", element: " +element+".");

           if(mvalue == mindex) 
              loc = element;
       }

// DEBUG("Element: " +loc+ " string: " +lower_case(str));

       setuid(); 
       seteuid(getuid());

       write("You explore the revelation of " +str+ ".\n");

       string revelations_file = loc;

        if (!pointerp(files = get_dir(OOTS_REVELATIONS)) || !sizeof(files))
        {
            return 0; 
        }

        if (!stringp(content = read_file(OOTS_REVELATIONS + revelations_file)))
        {
            notify_fail("Something is terribly wrong! Please contact "
                + "the guildmaster and let them know that the revelations "
                + "files for the Order of the Stars are not working "  
                + "properly.\n");
            return 0;
        }

       this_player()->more(generate_scroll_text(content, " * "));

       return 1;
    }
    
    if (strlen(str) && (str != "list"))
    {
        write("You have not been inspired with such a revelation yet!\n");
        return 1;
    }

    string message_text = oots_revelations_list();

    this_player()->more(generate_scroll_text(message_text, "'revelations " +
                        "<revelation>' to explore in detail"));
    return 1;
}


/*
 * Function:    print_spell_list
 * Description: Used in the prayers command, this will print out
 *              each classification of spells with a header.
 */
public string
print_spell_list(object * spellobjs)
{
    string message_text = "";
    int spells_known = 0; 
    if (sizeof(spellobjs))
    {
        foreach (object spellobj : spellobjs)
        {
            if (!spellobj->query_spell_can_be_learned(this_player()))
            {
                // Only show spells that we actually know
                continue;
            }
            spells_known++;
            message_text += sprintf("%-=12.12s %-=57.57s\n", 
                spellobj->query_spell_name(), spellobj->query_spell_desc() 
                + " (" + spellobj->query_spell_ingredients_description() 
                + ")");
        }
        message_text += "\n";
    }
    if (spells_known == 0) 
    {
        return "";
    }
    return message_text;
}

/*
 * Function name: prayers
 * Description:   List the active prayers.
 */
public int
prayers(string str)
{
    object *spellobjs = this_player()->query_spellobjs();
    spellobjs = filter(spellobjs, &wildmatch(OOTS_SPELLS + "*") @ file_name);
    
    if (!sizeof(spellobjs))
    {
        write("You have no prayers.\n");
        return 1;
    }
    
    string message_text = "Prayers granted to you by " +oots_god_name(TP)+ 
                          "\n\n";
    message_text += print_spell_list(spellobjs);

    this_player()->more(generate_scroll_text(message_text, 
                        "help oots <spell name> for " +
                        "specific spell information"));
    return 1;
}

