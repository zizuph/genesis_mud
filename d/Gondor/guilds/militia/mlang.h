/* 
 * mlang.h, hacked by Auberon, May 2001 from Cirion's
 * Sybarite language of 1996.
 */

#ifndef MY
#define MY this_player()->query_possessive()
#endif
#define HE this_player()->query_pronoun()

#define W1 ({ "a", "i", "a", "i", "a", "1", "2", \
               "i", "3", "a", "a","i","i","4","i","a", \
              "a", "i", "a", "s", "n", "e", "w" })
#define W2 ({ "am", "if", "be", "at", "or", "to", "po", "no", "of", "on", "we", \
              "an", "to", "by", "at", "my", "an", "it", "mt", "SU", "to", "as", \
              "nw", "se", "sw", "ne", "up", "or", "of", "an", "in", "do", "go", \
              "or", "it", "or", "he", "to", "of", "no", "MM", "is", "so", "of", \
              "DA", "VK" })
#define W3 ({ "the", "and", "his", "she", "him", "but", "why", "the", "you", "the", \
              "who", "elf", "met", "I'm", "axe", "was", "are", "one", "had", "not", \
              "man", "boy", "top", "her", "and", "let", "its", "all", "can", "has", \
              "how", "mad", "and", "you", "yes", "out", "had", "two", "see", "its", \
              "the", "and", "try", "get", "but", "let", "for", "too", "who", "now", \
              "bad", "set", "the", "for", "jab", "did", "use", "may", "new", "our", \
              "any", "put", "off", "old", "men", "say", "the", "and", "you", "was", \
              "RDA", "BDA", "orc", "lot", "RoG", "RoI", "let", "I'd"  })
#define W4 ({ "hand", "lady", "keep", "give", "that", "late", "talk", "it's", "long", "tell", \
              "this", "them", "they", "hers", "mine", "ours", "walk", "tell", "loot", "talk", \
              "take", "kill", "like", "hate", "orcs", "camp", "food", "soon", "have", "they", \
              "tent", "part", "with", "nice", "horn", "boat", "bank", "this", "real", "sure", \
              "ship", "road", "army", "that", "also", "herb", "shop", "that", "them", "know", \
              "yeah", "sure", "this", "that", "take", "like", "also", "been", "come", "went", \
              "very", "left", "when", "Bree", "heal", "pike", "came", "went", "more", "help", \
              "said", "told", "tell", "mail", "mage", "lord", "hall", "gone", "done", "pick", \
              "that", "with", "they", "this", "from", "have", "what", "were", "when", "your", \
              "each", "them", "then", "than", "many", "some", "into", "time", "make", "made", \
              "over", "down", "only", "find", "very", "just", "most", "know", "must", "does", \
              "well", "back", "much", "good", "even", "same", "look", "that", "with", "they", \
              "knew", "hide", "dark", "give", "gave", "jabs", "huge", "camp", "scry", "wish", \
              "lots", "team", "many", "lack", "wise", "dumb", "fool", "past", "rude", "liar", \
              "dock", "pier", "just", "soon" })
#define W5 ({ "likes", "those", "herbs", "takes", "sword", "going", "there", "which", \
              "spear", "takes", "taken", "wants", "helps", "heals", "their", "about", \
              "mails", "plate", "sabre", "torch", "owned", "taken", "would", "could", \
              "later", "liked", "hated", "short", "going", "pikes", "which", "other", \
              "taken", "stole", "coins", "their", "leave", "Shire", "water", "after", \
              "valar", "walks", "going", "being", "saved", "mages", "where", "write", \
              "booty", "these", "thief", "drunk", "start", "union", "wrong", "think", \
              "beats", "drink", "doubt", "early", "those", "Terel", "three", "place", \
              "dwarf", "elves", "these", "don't", "won't", "enemy", "again", "small", \
              "Gelan", "Calia", "looks", "Krynn", "comes", "there", "which", "their", \
              "fight", "can't", "right", "where", "evade", "about", "would", "could", \
              "known", "knows", "sneak", "block", "broke", "light", "bring", "guild", \
              "taken", "giant", "swarm", "parry", "tired", "horse", "known", "teams", \
              "party", "group", "times", "lacks", "troll", "smart", "allow", "let's", \
              "brawl", "truth", "plans", "eager", "angry", "upset", "happy", "cloak", \
              "can't", "won't", "don't", "lying" })
#define W6 ({ "shield", "beaten", "liking", "taking", "skills", \
              "person", "taught", "people", "leaves", "fights", \
              "ranger", "Calian", "stolen", "killed", "battle", \
              "troops", "coming", "gotten", "leaves", "saying", \
              "potion", "poison", "dagger", "missed", "losers", \
              "impale", "healed", "fought", "talked", "mailed", \
              "fights", "killer", "Gondor", "treaty", "morgul", \
              "Avenir", "goblin", "friend", "bother", "outlaw", \
              "people", "called", "though", "around", "number", \
              "ambush", "battle", "hobbit", "kender", "attack", \
              "hiding", "hidden", "sneaky", "golden", "knight", \
              "broken", "shadow", "lights", "guilds", "Neraka", \
              "jabbed", "evaded", "evades", "pigeon", "travel", \
              "charge", "honour", "horses", "scried", "herald", \
              "wanted", "teamed", "groups", "lacked", "nazgul", \
              "wraith", "trolls", "stupid", "humble", "unwise", \
              "fooled", "tricky", "tricks", "passed", "Anduin", \
              "regard", "polite", "verify", "honest", "beauty", \
              "dragon", "armour", "cloaks", "hooded", "rather", \
              "portal"  })
#define W7 ({ "through", "persons", "another", "because", "thought", "differs", "halberd", \
              "numbers", "mailing", "telling", "talking", "sending", "walking", "reasons", \
              "polearm", "winners", "battles", "wizards", "impaled", "impales", "outlaws", \
              "through", "another", "because", "dwarves", "hobbits", "Calians", "rangers", \
              "knights", "daggers", "poisons", "potions", "satchel", "brought", "circled", \
              "members", "waiting", "Flotsam", "Balifor", "Sparkle", "Emerald", "winners", \
              "Sybarus", "evading", "jabbing", "whiskey", "goblins", "dunadan", "pikemen", \
              "pikeman", "message", "charged", "charges", "battled", "wearing", "working", \
              "hunting", "scrying", "heralds", "Militia", "wanting", "waiting", "fleeing", \
              "teaming", "parties", "lacking", "footmen", "shields", "fooling", "passing", \
              "welcome", "Entwash", "wishful", "confirm", "pending", "guarded", "officer", \
              "unhappy", "dragons", "militia", "armours", "cloaked", "doesn't", "planned" })
#define W8 ({ "thinking", "Sanction", "impaling", "polearms", "halberds", "fighting", \
              "messages", "blocking", "honoured", "tracking", "Thornlin", "replying", \
              "ambushed", "ambushes", "differed", "patience", "horsemen", "shielded", \
              "guarding", "watchful", "regarded", "consider", "unwanted", "stalling", \
              "Isengard", "Ithilien", "definite", "possible", "confirms", "verified", \
              "inferior", "superior", "officers", "brawling", "tricking", "planning", \
              "friendly", "Hobbiton", "Pelargir", "armoured", "couldn't", "wouldn't" })

/*
 * Function:   replace
 * Arguments:  one word to replace
 * Returns:    A replacement word of the same
 *             string length in the new language.
 */
string replace(string str)
{
  string back, nihil;

  switch(strlen(str))
  {
    case 1: back = W1[random(sizeof(W1))]; break;
    case 2: back = W2[random(sizeof(W2))]; break;
    case 3: back = W3[random(sizeof(W3))]; break;
    case 4: back = W4[random(sizeof(W4))]; break;
    case 5: back = W5[random(sizeof(W5))]; break;
    case 6: back = W6[random(sizeof(W6))]; break;
    case 7: back = W7[random(sizeof(W7))]; break;
    default: back = W8[random(sizeof(W8))]; break;
  }

  /* Retain names of living people */
  if(stringp(str) && find_living(lower_case(str)))
    back = CAP(str);

  /* Retain capitializations */
  if(str == CAP(str))
   back = CAP(back);

  /* Retain punctuation */
  if(sscanf(str, "%s.", nihil))
   back += ".";
  if(sscanf(str, "%s!", nihil))
   back += "!";
  if(sscanf(str, "%s?", nihil))
   back += "?";
  if(sscanf(str, "%s,", nihil))
   back += ",";

  return back;
}

/*
 * Function: construct_str
 * Argument: the array of words to be replaced into
 *           the new language.
 * Returns:  The array of words in the translated
 *           string.
 */
string *construct_str(string *oldstr)
{
   string *newstr;
   int     i;

  for(i=0; i<sizeof(oldstr); i++)
     newstr[i] = replace(oldstr[i]);

  return newstr;
}

void msay_to(object me, object who, string *newstr, string *oldstr, string what)
{
  int      lang,
           i;
  string   endstr = "";

  if(!present(who, ENV(me)))
    return;

    /* Militia automatically understand it */
    if (IS_MILITIA(who))
    {
        who->catch_msg(QCTNAME(me)+" says in Lossarnach dialect: "+
            what+"\n");
        return;
    }
    
    /* Wizards automatically understand it */
    if (who->query_wiz_level())
    {
        who->catch_msg(QCTNAME(me)+" says in Lossarnach dialect (which you understand because you "+
            "are a wizard): "+
            what+"\n");
        return;
    }

  lang = who->query_skill(SS_LANGUAGE);
  if (IS_RANGER(who)) lang += 35;
  if (IS_DUNADAN(who)) lang += 15;
  if(lang < 25)
  {
    for(i=0;i<sizeof(newstr);i++)
     endstr += newstr[i] + " ";
    who->catch_msg(QCTNAME(me)+" says something in a strange "
     +"tongue you can't even identify.\n");
    return;
  }           
  if(lang < 35)
  {
    for(i=0;i<sizeof(newstr);i++)
     endstr += newstr[i] + " ";
    who->catch_msg(QCTNAME(me)+" says something incomprehensible "
     +"in some human tongue.\n");
    return;
  }

  if(lang < 50)
  {
    for(i=0;i<sizeof(newstr);i++)
     endstr += newstr[i] + " ";
    who->catch_msg(QCTNAME(me)+" says in "
     + "Adunaic dialect something like: "+endstr+"\n");
    return;
  }
  /* I think that Sybarite, Elemental Mantras, Draco, etc. are so hard as
     to make language skill not very useful, so am intentianally making it
     quite a bit easier than those (difficulty 90, 87.5, and 100 respectively).
   */
  for(i=0;i<sizeof(newstr);i++)
  {
    if((lang) > random (135))
      endstr += oldstr[i] + " ";
    else if (random(5) > 2) endstr += "... ";
	else endstr += newstr[i] + " ";
  }

  who->catch_msg(QCTNAME(me)+" says in a "
     +"language you recognize as Lossarnach Adunaic: "+endstr+"\n");
  return;
}

int msay(string str)
{
  object  *people;
  mixed    fail_msg;
  int      i, who;
  string  *oldstr,
          *newstr;

    if (!strlen(str) || str == "")
    {
    NF("Say what in the Lossarnach Adunaic dialect?\n");
    return 0;
    }    
    
  if(fail_msg = TP->query_prop(LIVE_M_MOUTH_BLOCKED))
  {
    if(stringp(fail_msg))
     NF(fail_msg);
    else
     NF("You cannot seem to use your mouth.\n");
    return 0;
   }

  people = filter(all_inventory(ENV(TP)), interactive) - ({ TP });
  
    /* if (TP->query_option(OPT_ECHO)) */
    TP->catch_msg("You say in the tongue of Lossarnach: "+str+"\n");
  /* else
    TP->catch_msg("Ok.\n"); */

  if(!sizeof(people))
   return 1;

  oldstr = explode(str, " ");

  newstr = allocate(sizeof(oldstr));

  for(i=0; i<sizeof(oldstr); i++)
     newstr[i] = replace(oldstr[i]);

  for(i=0;i<sizeof(people);i++)
    msay_to(TP, people[i], newstr, oldstr, str);

  return 1;
}
