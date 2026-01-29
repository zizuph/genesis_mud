/*
 * File Name        : pirate_soul.c
 * By               : Elmore.
 * Inspiration from : The Neidar Guild by Arman.
 *                    Occ_fighter Guild by Unknown.
 * Date             : Nov. 2000.
 * Description      : Contains the soul for the pirate guild, the emotes
 *                    and help files.
 * 
 *
 * Modied by Navarre June 2006:
 * Added command for the attack special Pbash.
 * And changed emote pbash to pelbow for press gangers.
 * June 24th: Navarre, Removed "Mail torqual for ideas", since he is
 * not in krynn anymore.
 * July 1st, added ability for king/queen to do ptitle to view title.
 */ 

#pragma strict_types
#pragma save_binary
#pragma no_clone

#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include "/d/Ansalon/common/defs.h"

/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

#define PIRATE_ALT_MSG "_pirate_alt_msg"

private int order_members(object a, object b);

/* 
 * Function name: get_soul_id
 * Description:   Give a name for this soul
 * Returns:       string - the soul's id
 */
string
get_soul_id() 
{ 
    return GUILD_NAME + " soul"; 
}

/*
 * Function name: query_cmd_soul
 * Description:   identify this as a valid cmdsoul
 * Returns:       1
 */
int 
query_cmd_soul() 
{ 
    return 1; 
}

int
help(string str)
{
    if (str == "pirates emotes" || str == "pirate emotes")
    {
        write("\nThe sash of the Pirates of the Bloodsea can do this:\n" +
        "------------------------------------------------------------------------------\n" +
        "- pappraise <who>  - Eye up someone and estimate if it would be worth the     \n" +
        "                     trouble of kidnapping them and demanding a ransom.       \n" +
        "- pbarnacle        - Remove the barnacles and seaweed from your hair.         \n" +
        "- pbounty <target> - Place a bounty on <target's> head.                       \n" +
        "- pcharge <target> - Attack <target>.                                         \n" +
        "- pescape          - Make a quick escape with your treasure.                  \n" +
        "- pfind            - Find some old treasure that you buried long ago.         \n" +
        "- pgrip            - Grip your weapon tightly, eager to plunder and smell     \n" +
        "                     the blood of battle.                                     \n" +
        "- pgroan           - Groan loudly, disappointed at the loss of opportunity    \n" +
        "                     to loot and plunder.                                     \n" +
        "- phang            - Dance the hempen jig - there's gonna be a hanging.       \n" +
        "- pjolly           - Hoist the jolly roger and signal the start of a raid.    \n" +
        "- pkiss <target>   - Kiss <target>, the pirate way.                           \n" +
        "- plaugh           - Laugh coarsely like an old seadog.                       \n" +
        "- plist            - Get a list of the pirates currently plundering Genesis.  \n" +
        "- plook            - Thoughtfully look up at the rigging.                     \n" +
        "- pmutiny          - Show no faith in the current standard of leadership.     \n" +
        "- ppeer <target>   - Peer at <target> with your glazy pirate eyes.            \n" +
        "- ppirate <target> - Show <target> what a scurvy pirate dog you really are.   \n" +
        "- praid <how>      - You declare <how> that you want to set out on a raid to  \n" +
        "                     burn and pillage.                                        \n" +
        "- prigging         - Mutter contemptuously after being ordered to repair      \n" +
        "                     the rigging.                                             \n" +
        "- prub             - Rub your hands together at the prospect of more coins.   \n" +
        "- psalt            - Salt some meat and provisions for the trip at sea.       \n" +
        "- psash            - Straighten your sash.                                    \n" +
        "- pscramble        - Scramble up to the crows nest.                           \n" +
        "- psearch          - Search frantically for some buried treasure.             \n" +
        "- pshow            - Show around your gold tooth that you looted on your      \n" +
        "                     last raid.                                               \n" +
        "- pslap            - Slap someone heartily on the back.                       \n" +
        "- psmell           - Take a deep breath, enjoying the salty sea air.          \n" +
        "- psmile           - You smile, revealing a goldtooth.                        \n" +
        "- pstand           - Stand tall, confident upon the deck of a ship in rough   \n" +
        "                     seas.                                                    \n" +
        "- pstagger         - You stagger around singing an old pirate song.           \n" +
        "- pstare           - Stare out to sea, searching for a rich ship to plunder.  \n" +
        "- psurvey          - Survey the land for a place to bury your treasure.       \n" +
        "- ptale <target>   - Turn to <target> and begin to spin a heroic tale about   \n" +
        "                     the Bloodsea storms you have sailed through.             \n" +
        "- pthink           - Think hard about what to spend your looted coins on.     \n" +
        "- pthreat <target> - Threaten <target> to hand over his/her coins.            \n" +
        "- pwhip <target>   - Whip <target> with your nine tailed whip.                \n" +
        "- pwrestle <who>   - Arm wrestle with <who>                                   \n" +
        "- set pbash <msg>  - Sets the battle cry used during combat with pbash.       \n");

        if(PADMIN->query_pirate_king(TP) ||
           PADMIN->query_pressganger(TP) ||
           PADMIN->query_piratelord(TP) ||
           PADMIN->query_firstmate(TP))
        {
            write("\n------- PRESS GANGER EMOTES -------\n"+
            "- pelbow <target>  - Bash someone like a true press ganger.                     \n" + 
            "- pdowse <target>  - Dowse <target> with grog.                                  \n" +
            "- vote <target>    - Vote <target> to join the pirates (ONLY IN PIRATE CAVE).   \n");
        }

        if(PADMIN->query_pirate_king(TP))
        {
            write("\n------- PIRATE KING EMOTES -------\n"+
            "- allow <target>    - Allow <target> to enter the Kings room.                   \n"+
            "- ptitle            - Shows what your title would be in the event of a mutiny.  \n");
        }
        write("------------------------------------------------------------------------------\n" +
        "You can also wear, tie and remove the sash.\n\n");
        return 1;
    }

    if(str == "pirates" || str == "pirate")
    {
        write("There are some topics all pirates should know about:\n\n"+
              "Booze        - the art of staggering\n"+
              "Emotes       - emotions shown by a pirate\n"+
              "Guildpolicy  - the policy who to rob and plunder\n"+
              "History      - a brief history on the crew and the king\n"+
              "Language     - a dictionary for pirate slang\n"+
              "Leaving      - how to become a poor land dweller again\n"+
              "Titles       - a list of the crew member titles\n\n"+
             "Use 'help pirates <topic>'.\n\n");
       return 1;
    }

    if(str == "pirates booze" || str == "pirate booze")
    {
         write("\nThe staggering of a drunk pirate\n"+
               "--------------------------------\n"+
          "Booze is one of the best friends of a pirate. No day "+
          "goes by without him or her having some imported roke "+
          "beers or lifting a good keg of rum to the lips. "+
          "Sometimes a pirate gets so drunk that balance of the "+
          "body becomes harder and harder, causing heavy "+
          "staggering in order to try and keep standing on the "+
          "legs. The world seems to be one immense blur of moving "+
          "strange shapes and flickering lights and colours. "+
          "Though it seems to be a great disadvantage for the art "+
          "of fighting of a pirate, in practice it is not. The foe "+
          "tends to show great trouble in hitting the staggering "+
          "pirate for his or her uncoordinated moves disorientate "+
          "the attacks. With the use of less alcohol the balance "+
          "returns to the legs until only a pounding headache and "+
          "a blasted sober body remains.\n\n"+
          "The experienced pirate also favours a nice bottle of "+
          "grog, which carries an exquisite taste. The pirates are "+
          "also known to use the bottle for other means than just "+
          "drinking, for example to <pbash> some heads with it.\n\n");
        return 1;
    }

    if(str == "pirates guildpolicy" || str == "pirate guildpolicy")
    {
        write("\nAbout the policy of the pirate crew\n"+
              "------------------------------------\n"+
          "It is very simple, no creature is too good or too evil "+
          "to be robbed by a pirate, so says the Pirate King. A "+
          "pirate lives for his or her treasure and will not step "+
          "back from danger in obtaining more gold and jewelry. "+
          "Fearless beings as they are they still have the wits to "+
          "know when to turn from a fight to secure the their "+
          "hidden treasures from falling into other hands. Often "+
          "do pirates band up to become stronger and to be able to "+
          "beat stronger enemies to loot even greater treasures as "+
          "they are able to when roaming the lands alone. The idea "+
          "is still that the whole is greater than the sum of the "+
          "parts, though eventually a pirate is just interested in "+
          "the size of his or her own pile of loot.\n"+
          "However, when pirates succeed in making an exceptionally "+
          "good raid they often do not hoard the extra money but "+
          "'invest' it in some rum in a pub, wasting the money as "+
          "easily as they got it. To have a good time is worth a "+
          "lot to pirates.\n\n");
        return 1;
    }

    if(str == "pirates history" || str == "pirate history")
    {
        write("\nFirst written pirate history from the spoken tales\n"+
              "--------------------------------------------------\n"+
          "The first thing to tell is that this is the first "+
          "attempt to write down the history of pirates as it has "+
          "been told over the years by pirates to newcomers. Alas, "+
          "tales differ and so do interpretations of them so the "+
          "history will not be the same in the hearts of every "+
          "pirate. The core is the same in all lines though so it "+
          "is still useful to finally have a written version.\n\n"+
          "Secondly this is only a brief version to create a "+
          "beginning, a first attempt, to write down the ancient "+
          "pirate lore as it started ages ago. This short version "+
          "can and will be extended and updated over time by the "+
          "wisest and most experienced members of the crew.\n\n"+
          "A GENERAL INTRO OF HISTORY:\n\n"+
          "The Age of Darkness, as it was recorded by Astinus of "+
          "Palanthas, began when a burning mountain hit Istar. "+
          "We call this event nowadays the Cataclysm. "+
          "The Cataclysm created among other things the Blood Sea "+
          "and also two islands which were all that remained of "+
          "Kothas and Mithas, home of the minotaurs. "+ 
          "Early on the minotaurs learned to create powerful ships "+
          "and used them to raid neigbours and plunder foreign "+
          "vessels. Soon other races took to piracy as well and "+
          "mixed with the minotaur crews. Those pirates became "+
          "the bane of the sea and their ruthless and daring "+
          "reputation well-deserved and hard-earned.\n"+
          "War ships mostly didn't catch the swift attack vessels "+
          "of the pirates. Even the Dragonarmies learned this the "+
          "hard way.\n"+
          "Nearly from the beginning the pirate crews consisted "+
          "of freedom loving men and women who dared and "+
          "cherished the adventure the capricious sea has to offer "+
          "daily.\n"+
          "However, this life has also its price: Nearly no pirate "+
          "dies in his bed. Actually it is an nightmare for those "+
          "people to die in a bed!\n "+
          "Until today the landlubbers' pants get wet when they "+
          "see the Jolly Roger on the horizon!\n\n");
        return 1;
    }

    if(str == "pirates language" || str == "pirate language")
    {
       write("\nThe great dictionary of pirate slang for crew members\n"+
         "-----------------------------------------------------\n"+
         "chatterin' pecker       - parrot\n"+
         "da rocky cabin          - the hidden pirate lair\n"+
         "gainin' fer da belt     - adding money to your treasure\n"+
         "gibberin' glibbers      - land dwellers\n"+
         "hairy fleapick'r        - monkey\n"+
         "iron clingclang         - iron pegleg\n"+
         "jolly roger             - skull and crossed bones\n"+
         "klabautermann           - spirit aboard a ship\n"+
         "me floatin' beerbelly   - a pirate's ship\n"+
         "me hidden maiden        - hidden treasure\n"+
         "me ol' rusty pin        - sword or knife\n"+
         "me wooden matey         - good barrel or keg of booze\n"+
         "ol' seadog              - pirate\n"+
         "pieces of eight         - piece between seven and nine\n"+
         "polish ye shiny pearls  - cut out one's eyes\n"+
         "rest fer me ol' corpse  - rest for the body\n"+
         "sailin' dry seas        - travelling over land\n"+
         "salty razorblades       - sharks\n"+
         "scourge o' da seas      - the respected pirate king\n"+
         "shak' ye pocket         - robbing someone for cash\n"+
         "shiverin' timbers       - being afraid\n"+
         "stir da waters          - swim\n"+
         "walk the plank          - get killed\n"+
         "ye big walk hast come   - prepare to die\n\n");
        return 1;
    }

    if(str == "pirates leaving" || str == "pirate leaving")
    {
        write("\nLeaving the life of robbing and plundering\n"+
          "------------------------------------------\n"+
          "Should ye ever become less interested in the robbing "+
          "of the people of these realms and the plundering of the "+
          "ships sailing the many oceans that exist, then there is "+
          "a way to become a poor land dweller again. Ye can go to "+
          "the room where ye once joined the proud pirate crew and "+
          "'abandon the crew'. But be warned that once ye abandon "+
          "the crew ye will have a hard time convincing the old "+
          "scavengers to take ye back on their ships, fer a "+
          "pirate ye be from the heart. If ye do not have the "+
          "pirate heart ye do not belong to the courageous and "+
          "treasureseeking mateys ever again. So the old Pirate "+
          "King has decided.\n\n");
        return 1;
     }

    if(str == "pirates titles" || str == "pirate titles")
    {
        write("\nThe titles for the crew members\n"+
        "-------------------------------\n"+
        "Deck Swappy of the Bloodsea\n"+
        "Experienced Deck Swappy of the High Seas\n"+
        "Cabinboy/Cabingirl of the Bloodsea\n"+
        "Learned Cabinboy/Cabingirl of the High Seas\n"+
        "Raider of the Bloodsea\n"+
        "Drunken Raider of the High Seas\n"+
        "Swashbuckler of the Bloodsea\n"+
        "Wanted Swashbuckler of the High Seas\n"+
        "Freebooter of the Bloodsea\n"+
        "Feared Freebooter of the High Seas\n"+
        "Buccaneer of the Bloodsea\n"+
        "Deadly Buccaneer of the High Seas\n"+
        "Corsair of the Bloodsea\n"+
        "Dreaded Corsair of the High Seas\n"+
        "Cutthroat of the Bloodsea\n"+
        "Veteran Cutthroat of the High Seas\n"+
        "Pirate of the Bloodsea\n"+
        "Notorious Pirate of the High Seas\n"+
        "Scourge of the Bloodsea\n"+
        "Scurvy Scourge of the High Seas\n"+
        "Pirate Lord/Lady of the Bloodsea\n"+
        "Legendary Pirate Lord/Lady of the High Seas\n\n");
        return 1;
     }
    return 0;
}


/*
 * Function name: query_cmdlist
 * Description:   Get the commands available on this soul and
 *                their corresponding function names.
 * Returns:       mapping - a mapping that maps command names
 *                          to function names.
 */
mapping
query_cmdlist()
{
    return ([
        /* Command name : Function name */
          "allow"       : "allow",
          "pallow"      : "allow",
          "help"        : "help",
          "pappraise"   : "pappraise",
          "pbarnacle"   : "pbarnacle",
          "pbash"       : "do_ability",
          "pelbow"      : "pelbow",
          "pbounty"     : "pbounty",
          "pdowse"      : "pdowse",
          "pescape"     : "pescape",
          "pfind"       : "pfind",
          "pgrip"       : "pgrip",
          "pgroan"      : "pgroan",
          "phang"       : "phang",
          "pjolly"      : "pjolly",
          "plaugh"      : "plaugh",
          "plist"       : "plist",
          "plook"       : "plook",
          "pmutiny"     : "pmutiny",
          "ppeer"       : "ppeer",
          "ppirate"     : "ppirate",
          "praid"       : "praid",
          "prigging"    : "prigging",
          "prub"        : "prub",
          "psalt"       : "psalt",
          "psash"       : "psash",
          "pscramble"   : "pscramble",
          "psearch"     : "psearch",
          "pshow"       : "pshow",
          "pslap"       : "pslap",
          "psmell"      : "psmell",
          "psmile"      : "psmile",
          "pstand"      : "pstand",
          "pstagger"    : "pstagger",
          "pstare"      : "pstare",
          "psurvey"     : "psurvey",
          "ptale"       : "ptale",
          "pthink"      : "pthink",
          "pthreat"     : "pthreat",
          "pwhip"       : "pwhip",
          "pwrestle"    : "pwrestle",
          "pkiss"       : "pkiss",
          "pstance"     : "pstance",
          "pcharge"     : "pcharge",
          "ptitle"      : "ptitle",
          "set"         : "set_pbash"
           ]);
}

public mapping
query_ability_map()
{
    return ([
             "pbash" : GUILD_OBJ + "pirate_pbash"
             ]);
}

int
pgrip(string str)
{
    if (str)
    {
       write("Just use 'pgrip' without any arguments\n");
    }
    if (!str)
    {
	      write("You grip your weapon tightly, eager to smell blood again.\n");
	      say(QCTNAME(TP) + " grips "+POSSESSIVE(TP)+" weapon tightly, eager "+
              "to smell blood again.\n");
    }
    return 1;
}


int
ptale(string str)
{
    object *oblist;

    if(strlen(str) && !sizeof(oblist = parse_this(str, "[at] %l")))
    {
	      write("Ptale at who?\n");
        return 1;
    }

    if (sizeof(oblist))
    {
        actor("You turn to", oblist, " and begin to spin a heroic tale about "+
              "the Bloodsea storms you have sailed through.\n");
        targetbb(" begins to spin a heroic tale about the Bloodsea storms "+
                  HE(TP)+ " has sailed through.", oblist);
        all2actbb(" turns to", oblist, " as "+HE(TP)+ " begins to spin a tale "+
                "about the Bloodsea storms "+HE(TP)+ " has sailed through.\n");
        return 1;
    }

    write("You begin to spin a heroic tale about the Bloodsea storms you "+
          "have sailed through.\n");
    allbb(" begins to spin a heroic tale about the Bloodsea storms " +HE(TP)+
          " has sailed through.\n");
    return 1;
}


int
pstand(string str)
{
    object *pers;
    if (!str)
    {
	      write("You stand tall, confident as if standing upon the deck of a ship in "+
              "rough seas.\n");
	      say(QCTNAME(TP) + " stands tall before you, confident "+
              "as if standing upon the deck of a ship in rough seas.\n");
	      return 1;
    }
    pers = parse_this(str, "[at] %l");
    NF("Pstand at who?\n");

    if (!pers || !sizeof(pers))
      return 0;

    tell_room(E(TP), QCTNAME(TP) + " stands tall before you, confident "+
            "as if standing upon the deck of a ship in rough seas.\n", pers + ({TP}));
    TP->catch_msg("You stand tall, confident as if standing upon the deck "+ 
              " of a ship in rough seas.\n");
    pers->catch_msg(QCTNAME(TP) + " stands tall before you, confident "+
            "as if standing upon the deck of a ship in rough seas.\n");
    return 1;
}

int
pstare(string str)
{
    if (str)
    {
       write("Just use 'pstare' without any arguments.\n");
    }
    if (!str)
    {
  	    write("You stare out over the sea, searching for a rich ship to plunder.\n");
	      say(QCTNAME(TP) + " stares out to sea, searching for a rich ship to "+
              "plunder.\n");
    }
    return 1;
}

int
plaugh(string str)
{
    if (str)
    {
       write("You only use 'plaugh' without any arguments.\n");
    }
    if (!str)
    {
	      write("You laugh coarsely like an old seadog.\n");
	      say(QCTNAME(TP) + " laughs coarsely like an old seadog.\n");
    }
    return 1;
}

int
psmell(string str)
{
    if (str)
    {
       write("You only use 'psmell' without any arguments.\n");
    }
    if (!str)
    {
	      write("You take a deep breath, enjoying the salty sea air.\n");
	      say(QCTNAME(TP) + " takes a deep breath, enjoying the salty sea air.\n");
    }
    return 1;
}

int
plook(string str)
{
    if (str)
    {
       write("You only use 'plook' without any arguments.\n");
    }
    if (!str)
    {
	      write("You thoughtfully look up at the rigging.\n");
	      say(QCTNAME(TP) + " thoughtfully looks up at the rigging.\n");
    }
    return 1;
}


int
pgroan(string str)
{
    if (str)
    {
       write("You only use 'pgroan' without any arguments.\n");
    }
    if (!str)
    {
	      write("You groan loudly, disappointed at the loss of an "+
              "opportunity to loot and plunder.\n");
	      say(QCTNAME(TP) + " groans loudly, disappointed at the loss "+
              "of an opportunity to loot and plunder.\n");
    }
    return 1;
}


int
praid(string str)
{
    string *how = parse_adverb_with_space(str, "fierily", 0);

    write("You declare"+how[1]+" that you want to set out on a raid to burn and pillage.\n");
    all(" declares"+how[1]+" that "+HIS(TP)+ " wants to go on a raid to burn and pillage.");
    return 1;
}


int
pappraise(string str)
{
    object *oblist;

    if(!strlen(str) || !sizeof(oblist = parse_this(str, "[the] %l")))
    {
	      NF("Pappraise whom?\n");
	      return 0;
    }

    actor("You eye up", oblist," and try to estimate if it would be worth the " +
          "trouble of kidnapping and demanding a ransom.");
    target(" gives you a greedy gleam and suddenly you remember tales of pirates "+
           "kidnapping people and demanding ransom for them.", oblist);
    all2act(" gets a greedy gleam in "+HIS(TP)+" eyes as "+HE(TP)+ " looks at", oblist,". "+
            "You wonder if it is still pirate custom to kidnap people and demand a ransom.");
    return 1;
}



int
pwrestle(string str)
{
    object *ob;
    object obj;
    int str_diff;
    string target_name;

    if(!strlen(str))
    {
	notify_fail("Arm wrestle with whom?\n");
	return 0;
    }

    ob = parse_this(str, "[with] %l");

    if(!sizeof(ob))
    {
	notify_fail("Arm wrestle with whom?\n");
	return 0;
    }

    obj = ob[0];

    actor("You grasp", ob, "'s right hand and begin to arm wrestle with "+HIM(obj)+".");
    target(" grasps your right arm and begins to arm wrestle with you.", ob);
    all2act(" grasps",ob,"'s right hand and begins to arm wrestle with "+HIM(obj)+".");
 
    if (obj->query_guild_name_lay() == "Pirate of the Bloodsea")
    {
        if (obj->query_stat(SS_STR) <= TP->query_stat(SS_STR))
        {
           set_alarm(4.0, 0.0, &actor("You gather all the strength in your right arm and "+
                                      "with brute force you manage to win the arm wrestling "+
                                      "match against", ob, "."));
           set_alarm(4.0, 0.0, &target(" wins against you in the arm wrestling match.", ob, "."));
           set_alarm(4.0, 0.0, &all2act(" wins against",ob," in the arm wrestling match."));
           return 1;
        }
        else
        {
           set_alarm(4.0, 0.0, &actor("You gather all the strength in your right arm but "+
                                      "without success, you loose the arm wrestling match against", ob, "."));
           set_alarm(4.0, 0.0, &target(" looses against you in the arm wrestling match.\n"+
                                       "You win!", ob, "."));
           set_alarm(4.0, 0.0, &all2act(" looses against",ob," in the arm wrestling match."));
           return 1;
        }
    }
    else
    {
           set_alarm(4.0, 0.0, &actor("You realize that", ob, " is too strong for you, and just as "+
                                      "you are about to lose, you kick "+HIS(obj)+" shin causing "+HIM(obj)+
                                      " to loose concentration for a second and giving you the upper hand.\n"+
                                      "You win the arm wrestling match."));
           set_alarm(4.0, 0.0, &target(" wins against you in the arm wrestling match.", ob, "."));
           set_alarm(4.0, 0.0, &all2act(" wins against",ob," in the arm wrestling match."));
    }

    return 1;
}



int
psmile(string str)
{
    if (str)
    {
       write("You only use 'psmile' without any arguments.\n");
    }
    if (!str)
    {
	      write("You smile, revealing a gold tooth you once looted from a corpse.\n");
	      say(QCTNAME(TP) + " smiles, revealing a gold tooth "+HE(TP)+" once looted "+
              "from a corpse.\n");
	      return 1;
    }
    return 1;
}


int
pstagger(string str)
{
    if (str)
    {
       write("You only use 'pstagger' without any arguments.\n");
    }
    if (!str)
    {
	      write("You stagger around singing an old pirate song.\n");
	      say(QCTNAME(TP) + " staggers around singing an old pirate song.\n");
	      return 1;
    }
    return 1;
}



int
ppeer(string str)
{
    object *oblist;

    if(strlen(str) && !sizeof(oblist = parse_this(str, "[at] %l")))
    {
	      write("Ppeer at whom ?");
        return 1;
    }

    if (sizeof(oblist))
    {
        actor("You peer at", oblist, " with your glazy pirate eyes.\n");
        targetbb(" peers at you with "+HIS(TP)+ " glazy pirate eyes.", oblist);
        all2actbb(" peers at", oblist, " with "+HIS(TP)+ " glazy pirate eyes.\n");
        return 1;
    }

    write("You peer around with your glazy pirate eyes.\n");
    say(QCTNAME(TP) + " peers around with "+HIS(TP)+" glazy pirate eyes.\n");
    return 1;
}


int
pshow(string str)
{
    if (str)
    {
       write("You only use 'pshow' without any arguments.\n");
    }
    if (!str)
    {
	      write("You show around your gold tooth that you looted on your last raid.\n");
      	say(QCTNAME(TP) + " shows "+HIS(TP)+ " gold tooth around, that "+HE(TP)+" looted on "+HIS(TP)+" last raid.\n");
      	return 1;
    }
    return 1;
}


private int
filter_pirates(object who)
{
    string coven;

    if (!who->query_guild_member(GUILD_NAME))
        return 0;

    if (who == TP)
        return 1;

    /* Wizards see everyone */
    if (TP->query_wiz_level())
        return 1;

#ifndef DA_TESTING
    /* Wizards are not shown to mortals */
    if (who->query_wiz_level())
        return 0;

    /* Wizards jr are not shown to mortals */
    if (extract(who->query_real_name(), -2) == "jr")
        return 0;
#endif DA_TESTING

    return 1;
}

mixed
make_list(object *members)
{
    string name, title, str1, str2, list = "";
    int i, size, cnt = 0;

    size = sizeof(members);
    i = -1;
    while (++i < size)
    {    
        str1 = SECURITY->query_wiz_pretitle(members[i]);
        str2 = "";

        if (strlen(name = members[i]->query_name()))
        {
            str1 += (strlen(str1) ? " " + name : name);
        }
        else
        {
            continue;
        }

        if (strlen(title = members[i]->query_guild_title_lay()))
        {
            str1 += (strlen(str1) ? " the " + title : capitalize(title));
        }

        if (TP->query_wiz_level())
        {
            str2 = "(" + (members[i]->query_wiz_level() ? "wiz" :
              members[i]->query_average_stat()) + ")";
        }

        cnt++;
        list += sprintf("- %=-68s %-5s\n", str1, str2);
    }
    
    return ({ list, cnt });
}

int
plist()
{
    mixed tmp;
    string list;
    int cnt;
    object *members;

    write("These Pirates are currently plundering the people of Genesis:\n");
    write("-------------------------------------------------------------\n");
    members = sort_array(filter(users(), filter_pirates), order_members);

    tmp = make_list(members);
    list = tmp[0];
    cnt = tmp[1];

#ifdef STATUE_WHEN_LINKDEAD
#ifdef OWN_STATUE
    /* If there is a room where statues of linkdead people can be found,
     * we add that to the list.
     */
    members = filter((all_inventory(find_object(OWN_STATUE)) - members), 
        &not() @ &->query_npc());
    members = sort_array(filter(members, filter_pirates), order_members);
    tmp = make_list(members);
    if (cnt = tmp[1])
    {
        list += "\nCurrently resting in the cave " + (cnt > 1 ? "are:\n" : "is:\n");
        list += tmp[0];
    }
#endif OWN_STATUE
#endif STATUE_WHEN_LINKDEAD



    if (query_verb()[0..0] == "m")
    {
        setuid();
        seteuid(getuid());
        TP->more(list);
    }
    else
    {
        write(list);
    }

    return 1;
}

private int
order_members(object a, object b)
{
    int ai, bi;
    

    ai = a->query_guild_level_lay();
    bi = b->query_guild_level_lay();

    if(PADMIN->query_pirate_king(b))
    {
        bi = 22;
    }

    if (ai < bi)
        return 1;

    if (ai > bi)
        return -1;

    ai = a->query_guild_level_lay();
    bi = b->query_guild_level_lay();

    if(PADMIN->query_pirate_king(a))
    { 
        ai = 22;
    }

    return ((ai < bi) ? 1 : (ai == bi ? 0 : -1));  
}


int
psash(string str)
{
    if (str)
    {
       write("You only use 'psash' without any arguments.\n");
    }
    if (!str)
    {
	      write("You straighten your sash and show yourself ready for the battle to come.\n");
	      say(QCTNAME(TP) + " straightens "+HIS(TP)+ " sash and shows "+HIM(TP)+"self ready for the battle to come.\n");
	      return 1;
    }
    return 1;
}


int
pfind(string str)
{
    if (str)
    {
       write("You only use 'pfind' without any arguments.\n");
    }
    if (!str)
    {
	      write("You find some old treasure that you buried long ago.\n");
	      say(QCTNAME(TP) + " finds some old treasure that "+HE(TP)+ " buried long ago.\n");
	      return 1;
    }
    return 1;
}


int
psurvey(string str)
{
    if (str)
    {
       write("You only use 'psurvey' without any arguments.\n");
    }
    if (!str)
    {
	      write("You survey the land eargerly for a suitable place to bury your "+
              "treasure.\n");
	      say(QCTNAME(TP) + " surveys the land eargerly for a suitable place "+
            "to bury "+HIS(TP)+" treasure.\n");
	      return 1;
    }
    return 1;
}


int
pescape(string str)
{
    if (str)
    {
       write("You only use 'pescape' without any arguments.\n");
    }
    if (!str)
    {
	      write("You glance quickly in all directions looking for a handy "+
              "escape route to abscond with your new found treasure.\n");
	      say(QCTNAME(TP) + " glances quickly in all directions looking for "+
              "a handy escape route to abscond with "+HIS(TP)+" new found "+
              "treasure.\n");
	      return 1;
    }
    return 1;
}


int
psalt(string str)
{
    if (str)
    {
       write("You only use 'psalt' without any arguments.\n");
    }
    if (!str)
    {
	      write("You salt some meat and provisions in preparation for a long "+
              "trip at sea.\n");
	      say(QCTNAME(TP) + " salts some meat and provisions in preparation "+
            "for a long trip at sea.\n");
	      return 1;
    }
    return 1;
}

int
psearch(string str)
{
    if (str)
    {
       write("You only use 'psearch' without any arguments.\n");
    }
    if (!str)
    {
	      write("You search frantically for some buried treasure.\n");
	      say(QCTNAME(TP) + " searches frantically for some buried "+
            "treasure.\n");
	      return 1;
    }
    return 1;
}


int
ppirate(string str)
{
    object *ob;
    object obj;

    if(!strlen(str))
    {
	      notify_fail("Ppirate whom?\n");
	      return 0;
    }

    ob = parse_this(str, "[the] %l");

    if(!sizeof(ob))
    {
	      notify_fail("Ppirate whom?\n");
	      return 0;
    }

    obj = ob[0];

    actor("You demonstrate to", ob," what a scurvy pirate dog you "+
          "really are.");
    target(" demonstrates to you what a scurvy pirate dog "+HE(TP)+
           " really is.", ob);
    all2act(" demonstrates to", ob," what a scurvy pirate dog "+
            HE(TP)+ " really is.");
    return 1;
}


int
pthreat(string str)
{
    object *ob;
    object obj;
    int multiple_targets = 0;

    if(!strlen(str))
    {
	      notify_fail("Pthreat whom?\n");
	      return 0;
    }

    ob = parse_this(str, "[the] %l");

    if(!sizeof(ob))
    {
	      notify_fail("Pthreat whom?\n");
	      return 0;
    }

    if (sizeof(ob) > 1)
        multiple_targets = 1;

    obj = ob[0];
   
    if (multiple_targets == 1)
    {
        actor("You hold your weapon to", ob,"'s throat and threaten to take "+
              "their coins!");
        target(" holds "+HIS(TP)+ " weapon to your throat and threatens to take "+
               "your coins!", ob);
        all2act(" holds "+HIS(TP)+ " weapon to", ob,"'s throat and threatens to take "+
                "their coins!");
    }
    else
    {
        actor("You hold your weapon to", ob,"'s throat and threaten to take "+
              HIS(obj)+ " coins!");
        target(" holds "+HIS(TP)+ " weapon to your throat and threatens to take "+
               "your coins!", ob);
        all2act(" holds "+HIS(TP)+ " weapon to", ob,"'s throat and threatens to take "+
                HIS(obj)+ " coins!");
    }
    return 1;
}


int
pwhip(string str)
{
    object *ob;
    object obj;

    if(!strlen(str))
    {
	      notify_fail("Pwhip whom?\n");
	      return 0;
    }

    ob = parse_this(str, "[the] %l");

    if(!sizeof(ob))
    {
	      notify_fail("Pwhip whom?\n");
	      return 0;
    }

    obj = ob[0];

    actor("You take out your nine tailed whip and give", ob," a"+
          " good cat whipping.");
    target(" takes out "+HIS(TP)+ " nine tailed whip and gives you a good "+
           "cat whipping.", ob);
    all2act(" takes out "+HIS(TP)+ " nine tailed whip and gives", ob," a"+
            " good cat whipping.");
    return 1;
}


int
pbounty(string str)
{
    object *ob;
    object obj;

    if(!strlen(str))
    {
	      notify_fail("Pbounty whom?\n");
	      return 0;
    }

    ob = parse_this(str, "[the] %l");

    if(!sizeof(ob))
    {
	      notify_fail("Pbounty whom?\n");
	      return 0;
    }

    obj = ob[0];

    actor("You place a bounty of 1000 gold coins on", ob,"'s head.");
    target(" places a bounty of 1000 gold coins for the one who brings "+
           HIM(TP) + " your head!", ob);
    all2act(" places a bounty of 1000 gold coins on", ob,"'s head.");
    return 1;
}


int
pmutiny(string str)
{
    if (str)
    {
       write("You only use 'pmutiny' without any arguments.\n");
    }
    if (!str)
    {
	      write("You declare a mutiny showing absolutely no faith "+
              "in the current standard of leadership.\n");
	      say(QCTNAME(TP) + " declares a mutiny showing absolutely no faith "+
            "in the current standard of leadership.\n");
	      return 1;
    }
    return 1;
}


int
pjolly(string str)
{
    if (str)
    {
       write("You only use 'pjolly' without any arguments.\n");
    }
    if (!str)
    {
	      write("You hoist the jolly roger and signal the start "+
              "of a raid.\n");
	      say(QCTNAME(TP) + " hoists the jolly roger and signals the start "+
            "of a raid.\n");
	      return 1;
    }
    return 1;
}


int
pthink(string str)
{
    if (str)
    {
       write("You only use 'pthink' without any arguments.\n");
    }
    if (!str)
    {
	      write("You think hard about what to spend your loooted "+
              "pieces of eight on.\n");
	      say(QCTNAME(TP) + " thinks hard about what to spend "+HIS(TP)+" loooted "+
              "pieces of eight on.\n");
	      return 1;
    }
    return 1;
}
 

int
pbarnacle(string str)
{
    if (str)
    {
       write("You only have to use 'pbarnacle' without any arguments.\n");
    }
    if (!str)
    {
	      write("You skillfully remove the barnacles and seaweed "+
              "from your hair.\n");
	      say(QCTNAME(TP) + " skillfully removes the barnacles and seaweed "+
              "from "+HIS(TP)+ " hair.\n");
	      return 1;
    }
    return 1;
}

int
phang(string str)
{
    if (str)
    {
       write("You only use 'phang' without any arguments.\n");
    }
    if (!str)
    {
	      write("You dance the hempen jig, while shouting: 'There's gonna be a "+
              "hanging!'\n");
	      say(QCTNAME(TP) + " dances the hempen jig, while shouting: 'There's "+
            "gonna be a hanging!'\n");
	      return 1;
    }
    return 1;
}


int
pscramble(string str)
{
    if (str)
    {
       write("You only use 'pscramble' without any arguments.\n");
    }
    if (!str)
    {
	      write("You scramble up to the crows nest to get a better "+
              "look at passing ships to plunder.\n");
	      say(QCTNAME(TP) + " scrambles up to the crows nest to get a better "+
            "look at passing ships to plunder.\n");
	      return 1;
    }
    return 1;
}


int
prigging(string str)
{
    if (str)
    {
       write("You only use 'prigging' without any arguments.\n");
    }
    if (!str)
    {
	      write("You mutter contemptuously after being ordered to "+
              "repair the rigging.\n");
	      say(QCTNAME(TP) + " mutters contemptuously after being ordered to "+
            "repair the rigging.\n");
	      return 1;
    }
    return 1;
}
 


int
pslap(string str)
{
    object *ob;
    object obj;

    if(!strlen(str))
    {
	      notify_fail("Pslap whom?\n");
	      return 0;
    }

    ob = parse_this(str, "[the] %l");

    if(!sizeof(ob))
    {
	      notify_fail("Pslap whom?\n");
	      return 0;
    }

    obj = ob[0];


    actor("You cry out: 'Shiver me timbers!' and slap", ob," heartily on the back.");
    target(" cries out: 'Shiver me timbers!' and slaps you heartily on the back.", ob);
    all2act(" cries out: 'Shiver me timbers!' and slaps", ob," heartily on the back.");
    return 1;
}

int
prub(string str)
{
    if (str)
    {
       write("Only use 'prub' without any arguments.\n");
    }
    else
    {
      write("You rub your hands together gleefully at the prospect of more coins.\n");
      say(QCTNAME(TP) + " rubs "+HIS(TP)+" hands together gleefully at the prospect "+
          "of more coins.\n");
    }
    return 1;
}


int
pelbow(string str)
{
    object *ob;
    object obj;

    if(!PADMIN->query_pressganger(TP) && 
       !PADMIN->query_firstmage(TP) &&
       !PADMIN->query_piratelord(TP) &&
       !PADMIN->query_pirate_king(TP))
    {
        notify_fail("What ?\n");
    }

    if(!strlen(str))
    {
	      notify_fail("Pelbow whom?\n");
	      return 0;
    }

    ob = parse_this(str, "[the] %l");

    if(!sizeof(ob))
    {
	      notify_fail("Pelbow whom?\n");
	      return 0;
    }

    obj = ob[0];

    actor("You elbow", ob," in the face and punch "+HIM(obj)+ " in the gut "+
          "in true press ganger tradition.");
    target(" elbows you in the face and punches you in the guts like a true "+
           "press ganger.", ob);
    all2act(" elbows", ob," in the face and punches "+HIM(obj)+ " in the "+
            "guts like a true press ganger.");
    return 1;
}


int
pdowse(string str)
{
    object *ob;
    object obj;

    if (!PADMIN->query_pirate_king(TP) &&
        !PADMIN->query_pressganger(TP) &&
        !PADMIN->query_piratelord(TP) &&
        !PADMIN->query_firstmate(TP))
    {
        notify_fail("What?\n");
    }

    if(!strlen(str))
    {
	      notify_fail("Pdowse whom?\n");
	      return 0;
    }

    ob = parse_this(str, "[the] %l");

    if(!sizeof(ob))
    {
	      notify_fail("Pdowse whom?\n");
	      return 0;
    }

    obj = ob[0];

    actor("You dowse", ob," with grog readying "+HIM(obj)+ " for passage "+
          "into the pirate ranks.");
    target(" dowses you with grog readying you for passage into the pirate "+
           "ranks.", ob);
    all2act(" dowses", ob," with grog readying "+HIM(obj)+ " for passage "+
            "into the pirate ranks.");
    return 1;
}

int
pcharge(string str)
{
    object *ob;
    object obj;

    if(!strlen(str))
    {
       notify_fail("Pcharge whom?\n");
       return 0;
    }

    ob = parse_this(str, "[the] %l");

    if(!sizeof(ob))
    {
       notify_fail("Pcharge whom?\n");
       return 0;
    }

    obj = ob[0];

    switch(random(5))
    { 
        case 1:
            actor("You cross your fingers for good luck and run "+
                  "towards", ob,", ready for a good fight!");
            target("crosses "+HIS(TP)+" fingers for good luck and runs towards you, "+
                   "ready for a good fight!", ob);
            all2act(" crosses "+HIS(TP)+" fingers for good luck and runs "+
                    "towards", ob,", ready for a good fight!");
            break;

        case 2:
            actor("Hoping for great treasures to loot, you charge "+
                  "towards", ob," with a blaze of fury in your eyes!");
            target("'s eyes gleam with greed as "+HE(TP)+ " charges towards you!", ob);
            all2act("'s eyes gleam with greed as "+HE(TP)+ " charges towards", ob,"!");
            break;

        case 3:
            actor("You shout: 'For Crew and King!' and charge blindly into battle "+
                  "against", ob,". You can feel the bloodlust running through your veins!");
            target(" shouts: 'For Crew and King!' and charges blindly into battle "+
                   "against you. You can almost see the bloodlust in "+HIS(TP)+ " eyes!", ob);
            all2act(" shouts: 'For Crew and King!' and charges blindly into battle "+
                   "against", ob,". You can clearly see the bloodlust in "+HIS(TP)+ " eyes!");
            break;

        case 4:
            actor("Totally prepared for the battle to come, you look menacingly at", ob," before "+
                  "running straight into "+HIM(obj)+"!");
            target(" looks totally prepared for the battle to come, as "+HE(TP)+" looks menacingly "+
                   "into your eyes before running straight into you!", ob);
            all2act(" looks totally prepared for the battle to come, as "+HE(TP)+" looks menacingly "+
                   "at", ob," before running straight into "+HIM(obj)+"!", ob);
            break;

        default:
            actor("Shouting a wild battlecry to fuel your battlelust you charge "+
                  "towards", ob," with an unrivaled fury!");
            target(" shouts a wild battlecry and charges at you with an unrivaled fury!", ob);
            all2act(" shouts a wild battlecry and charges towards", ob," with an unrivaled fury!");
            break;
    }

    if (P(obj, E(TP)))
	TP->command("$kill "+obj->query_real_name());
    else
    {
       write("Your enemy has escaped!\n");
       all(" blinks as " + HIS(TP) + " enemy runs away.\n");
    }
    return 1;
}


int
pkiss(string str)
{
    object *ob;
    object obj;

    if(!strlen(str))
    {
       notify_fail("Pkiss whom?\n");
       return 0;
    }

    ob = parse_this(str, "[the] %l");

    if(!sizeof(ob))
    {
       notify_fail("Pkiss whom?\n");
       return 0;
    }

    obj = ob[0];

    actor("Laughing rudely you grab", ob,"'s waist, pulling "+HIM(obj)+" towards you "+
          "and giving "+HIM(obj)+ " a long and intensive kiss!");
    target(" laughs loudly and grasps your waist, pulling you towards "+HIM(TP)+" and giving "+
           "you a long kiss which nearly robs your senses.", ob);
    all2act(" laughs rudely and grasps", ob," by the waist, pulling "+HIM(obj)+" towards "+HIM(TP)+
            " and giving "+HIM(obj)+ " a long breathtaking kiss.");
    return 1;
}

int
allow(string str)
{
    object *ob;
    object obj;

    // find_player("arman")->catch_msg("[Pirates] allow command checked.\n");

    // if not the king, say what?
    if(!PADMIN->query_pirate_king(TP))
    {
      return 0;
    }

    if(!strlen(str))
    {
       notify_fail("Allow whom?\n");
       return 0;
    }

    ob = parse_this(str, "[the] %l");

    if(!sizeof(ob))
    {
       notify_fail("Allow whom?\n");
       return 0;
    }

    obj = ob[0];

    obj->add_prop(I_AM_ALLOWED, 1);
    
    actor("You allow", ob," to enter the Kings room in the pirate cave.");
    target(" allows you to enter the Kings room in the pirate cave.", ob);
    all2act(" allows", ob," to enter the Kings room in the pirate cave.");
    return 1;
}

int
ptitle(string str)
{
    if(!PADMIN->query_pirate_king(TP)) 
    {
      return 0;
    }

    if(strlen(str))
    {
       notify_fail("Use <ptitle> without any arguments to view what your "+
                   "title would be after a mutiny.\n");
       return 1;
    }
    TP->catch_tell("In the event of a successful mutity you would be known "+
                   "as a "+this_player()->query_king_title()+".\n");
    return 1;
}

void set_pbash_msg(string str)
{
  this_player()->add_prop(PIRATE_ALT_MSG, str);
}

int
set_pbash(string str)
{
  string* args; 
  string new_string;

  if(!strlen(str))
  {
    notify_fail("Set what? pbash?\n");
    return 0;
  }
  args = explode(str, " ");

  if(args[0]!="pbash")
  {
    notify_fail("Set what? pbash?\n");
    return 0;
  }
  if(sizeof(args)==1)
  {
    this_player()->catch_tell("Use: set pbash <message> or set pbash off\n");
    return 1;
  }
  if(str == "set pbash off")
  {

  }
  else
  {
    args = args - ({args[0]});
    new_string = implode(args, " ");
    set_pbash_msg(new_string);
    this_player()->catch_tell("You have set your pbash message.\n");
    return 1;
  }
}
