/* 
 *  include_language.h - a Mercenary ability to speak in racial languages,
 *      based on the mudlib rsay, with modifications from Auberon's
 *      Thornlin militia language
 *
 *  by Morrigan, 12/01
 */

#define LANGUAGES ({ "elven", "goblin", "dwarven", "common", "gnomish", "hobbit" })
#define LANGUAGE_ALL_RSAY (55) /* When will you understand all rsay */
#define LANGUAGE_MIN_RSAY (15) /* Below this you understand no rsay */

#define W1 ({ "a", "i", "a", "i", "a", "1", "2", \
               "i", "u", "a", "a","i","i","d","i","a", \
              "a", "i", "a", "s", "n", "e", "w" })
#define W2 ({ "am", "if", "be", "at", "or", "to", "po", "no", "of", "on", "we", \
              "an", "to", "by", "at", "my", "an", "it", "mt", "mm", "to", "as", \
              "nw", "se", "sw", "ne", "up", "or", "of", "an", "in", "do", "go", \
              "or", "it", "or", "he", "to", "of", "no", "in", "is", "so", "of", \
              "hi", "on" })
#define W3 ({ "the", "and", "his", "she", "him", "but", "why", "the", "you", "the", \
              "who", "elf", "met", "I'm", "axe", "was", "are", "one", "had", "not", \
              "man", "boy", "top", "her", "and", "let", "its", "all", "can", "has", \
              "how", "mad", "and", "you", "yes", "out", "had", "two", "see", "its", \
              "the", "and", "try", "get", "but", "let", "for", "too", "who", "now", \
              "bad", "set", "the", "for", "bat", "did", "use", "may", "new", "our", \
              "any", "put", "off", "old", "men", "say", "the", "and", "you", "was", \
              "her", "him", "orc", "lot", "pat", "ton", "let", "I'd", "sky", "ice" })
#define W4 ({ "hand", "lady", "keep", "give", "that", "late", "talk", "it's", "long", "tell", \
              "this", "them", "they", "hers", "mine", "ours", "walk", "tell", "loot", "talk", \
              "take", "kill", "like", "hate", "orcs", "camp", "food", "soon", "have", "they", \
              "tent", "part", "with", "nice", "horn", "boat", "bank", "this", "real", "sure", \
              "ship", "road", "army", "that", "also", "herb", "shop", "that", "them", "know", \
              "yeah", "sure", "this", "that", "take", "like", "also", "been", "come", "went", \
              "very", "left", "when", "merc", "heal", "pike", "came", "went", "more", "help", \
              "said", "told", "tell", "mail", "mage", "lord", "hall", "gone", "done", "pick", \
              "that", "with", "they", "this", "from", "have", "what", "were", "when", "your", \
              "each", "them", "then", "than", "many", "some", "into", "time", "make", "made", \
              "over", "down", "only", "find", "very", "just", "most", "know", "must", "does", \
              "well", "back", "much", "good", "even", "same", "look", "that", "with", "they", \
              "knew", "hide", "dark", "give", "gave", "king", "huge", "camp", "scry", "wish", \
              "lots", "team", "many", "lack", "wise", "dumb", "fool", "past", "rude", "liar", \
              "dock", "pier", "just", "soon", "rain", "snow", "sand", "rock" })
#define W5 ({ "likes", "those", "herbs", "takes", "sword", "going", "there", "which", \
              "spear", "takes", "taken", "wants", "helps", "heals", "their", "about", \
              "mails", "plate", "sabre", "torch", "owned", "taken", "would", "could", \
              "later", "liked", "hated", "short", "going", "water", "which", "other", \
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
              "can't", "won't", "don't", "lying", "birth", "storm", "icing", "queen" })
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
              "portal", "mother", "father", "sister", "uncles", \
	      "family", "parent", "happen", "living", "bandit", \
	      "plants", "animal", "purple", "orange", "yellow", \
	      "dozens", "grapes", "apples", "banana", "fruits", \
	      "houses", "travel", "wither", "wicker", "warned" })
#define W7 ({ "through", "persons", "another", "because", "thought", "differs", "halberd", \
              "numbers", "mailing", "telling", "talking", "sending", "walking", "reasons", \
              "polearm", "winners", "battles", "wizards", "impaled", "impales", "outlaws", \
              "through", "another", "because", "dwarves", "hobbits", "Calians", "rangers", \
              "knights", "daggers", "poisons", "potions", "satchel", "brought", "circled", \
              "members", "waiting", "Flotsam", "Balifor", "Sparkle", "Emerald", "winners", \
              "Sybarus", "battles", "enemies", "whiskey", "goblins", "dunadan", "pikemen", \
              "pikeman", "message", "charged", "charges", "battled", "wearing", "working", \
              "hunting", "scrying", "heralds", "bottoms", "wanting", "waiting", "fleeing", \
              "teaming", "parties", "lacking", "footmen", "shields", "fooling", "passing", \
              "welcome", "Entwash", "wishful", "confirm", "pending", "guarded", "officer", \
              "unhappy", "dragons", "friends", "armours", "cloaked", "doesn't", "planned", \
	      "brother", "patient", "blatant", "bananas", "oranges", "warning", "instead" })
#define W8 ({ "thinking", "Sanction", "defences", "polearms", "halberds", "fighting", \
              "messages", "blocking", "honoured", "tracking", "Thornlin", "replying", \
              "ambushed", "ambushes", "differed", "patience", "horsemen", "shielded", \
              "guarding", "watchful", "regarded", "consider", "unwanted", "stalling", \
              "Vingaard", "Ithilien", "definite", "possible", "confirms", "verified", \
              "inferior", "superior", "officers", "mailings", "tricking", "planning", \
              "friendly", "Hobbiton", "Pelargir", "armoured", "couldn't", "wouldn't", \
	      "massacre", "rainbows", "potatoes", "tomatoes", "should've", "outstanding", \
	      "homecoming", "welcomed", "parasite", "misgiving", "hardship", "ponytail", \
	      "blackened", "mercenary", "travelled", "relative", "paternal", "maternal", \
	      "kindness", "happiness", "stealing", "killings", "marriage", "assaulted", \
	      "engaged", "married", "divorced", "separate", "overcast", "lightning", \
	      "downfall", "hurricane" })

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
    back = capitalize(str);

  /* Retain capitializations */
  if(str == capitalize(str))
   back = capitalize(back);

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
 * msay - Mercenary ability to speak in racial tongues
 * 	by Morrigan, 12/2001
 * 
 * Adapted from /cmd/live/speech.c rsay code
 */
int
msay(string str)
{
    int     index;
    int     size;
    mixed   tmp;
    object *oblist;
    string  race = this_player()->query_race_name();
    string  lang_race;
    string  pos = this_player()->query_possessive();
    int     skill;
    string  *words;
    int     sentence_size;
    int     sentence_index;
    string  to_print;
    string  language;
    string  my_str;
    int     difficulty;

    NF("You have no environment, where are you?!\n");
    if (!objectp(environment(this_player())))
        return 0;

    NF("Say [in what race's language] [what]?\n");
    if (!stringp(str))
        return 0;

    if (tmp = this_player()->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        write(stringp(tmp) ? tmp : "You are gagged and cannot speak.\n");
        return 1;
    }
 
    NF("Say [in what race's language] [what]?\n");
    if (!parse_command(str, environment(this_player()), 
	"[in] %w %s", language, str))
	return 0;

    /* Make the language prettier and set up difficulty levels here */
    switch(language)
    {
	case "elf":
        case "elven":
	case "elfish":
	case "elvish":
	case "elfin":
	    language = "elven";
            lang_race = "elf";
	    difficulty = 50;
	    break;
	case "dwarf":
	case "dwarfish":
	case "dwarvish":
	case "dwarven":
	    language = "dwarven";
            lang_race = "dwarf";
	    difficulty = 45;
	    break;
	case "human":
	case "common":
	case "standard":
	case "basic":
	    language = "common";
	    difficulty = 0;
	    break;
	case "gnome":
	case "gnomish":
	    language = "gnomish";
            lang_race = "gnome";
	    difficulty = 60;
	    break;
	case "hobbit":
	case "hobbitish":
	    language = "hobbit";
            lang_race = "hobbit";
	    difficulty = 35;
        break;
	case "goblin":
	    language = "goblin";
            lang_race = "goblin";
	    difficulty = 40;
        break;
    }

    NF("You cannot speak "+language+".\n");
    if (member_array(language, LANGUAGES) == -1)
	return 0;

    if ((this_player()->query_skill(SS_LANGUAGE) < difficulty) &&
	race != lang_race && language != "common")
        return 0;

    oblist = FILTER_OTHER_LIVE(all_inventory(environment(this_player())));
    words = explode(str, " ") - ({ "" });
    sentence_size = sizeof(words);
    sentence_index = -1;

    /* The mercenary will always think he spoke perfectly */
    my_str = str;
    str = "";

    /* Adjust the difficulty for resolve_task */
    difficulty = difficulty * 10;

    /* Make the merc not speak the language perfectly */
    while(++sentence_index < sentence_size)
    {
        /* Speak common and/or your racial language perfectly */
        if (race == lang_race || language == "common")
        {
            str = my_str;
            break;
        }

        if (this_player()->resolve_task(difficulty + 
	    strlen(words[sentence_index]) * 10, 
	    ({ SKILL_WEIGHT, 200, SS_LANGUAGE, SKILL_WEIGHT, 75, 
	    SKILL_AVG, TS_WIS, TS_INT, SKILL_END }) ) > 0 || 
            race == language || language == "common")
        {
            str += " " + words[sentence_index];
        }
        else
        {
            str += (" " + replace(words[sentence_index]));
        }
    }

    /* Make this look prettier by taking out the empty space */
    if (extract(str, 0, 0) == " ")
        str = extract(str, 1);

    index = -1;
    size = sizeof(oblist);
    while(++index < size)
    {
        /* Wizards, players of the same race and people with a generally
         * high education in languages will understand the racial speech.
         */
        if ((lang_race == oblist[index]->query_race_name()) ||
            (oblist[index]->query_wiz_level()) ||
            ((skill = oblist[index]->query_skill(SS_LANGUAGE)) >=
                LANGUAGE_ALL_RSAY) || language == "common")
        {
            tell_object(oblist[index],
                this_player()->query_The_name(oblist[index]) + " says in " +
                (oblist[index]->query_race_name() == lang_race ? "your native" : 		"the "+language)
                 + " tongue: "+str+"\n");
            continue;
        }

        /* If you hardly have any language skill, you will not understand
         * one word uttered.
         */
        if (skill < LANGUAGE_MIN_RSAY)
        {
            tell_object(oblist[index],
                this_player()->query_The_name(oblist[index]) +
                " says something completely incomprehensible.\n");
            continue;
        }

        /* Other players will only hear a part of the text. */
        skill -= LANGUAGE_MIN_RSAY;
        to_print = "";
        sentence_index = -1;
        while(++sentence_index < sentence_size)
        {
            if (random(LANGUAGE_ALL_RSAY - LANGUAGE_MIN_RSAY) <= skill)
            {
                to_print += " " + words[sentence_index];
            }
            else
            {
                to_print += (" " + replace(words[sentence_index]));
            }
        }

        tell_object(oblist[index],
            this_player()->query_The_name(oblist[index]) +
            " says in the "+language+" tongue:" + to_print + "\n");
    }

    if (this_player()->query_option(OPT_ECHO))
    {
        if (race == lang_race)
            write("You say in your native tongue: " + my_str + "\n");
           else
            write("You say in the "+language+" tongue: " + my_str + "\n");
    }
    else
        write("Ok.\n");

    return 1;
}
