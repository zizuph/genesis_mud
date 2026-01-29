/*
 * - /d/Avenir/union/lib/stone.h
 *
 * Defines file to hold defines used in the union sphere guild object.
 * This object is located at: /d/Avenir/union/obj/stone.c
 *
 * Revisions:
 *   Lucius, Oct  4, 2005: Initial creation and moving of the static
 *           case switch for 'ufeel' to a more dynamic mapping in this file.
 *   Lilith Mar 2022: Added a few more emotions.
 *
 */
#ifndef __UNION_SPHERE__
#define __UNION_SPHERE__
/*
 * Mapping for the 'ufeel' command.
 *
 * Note: ufeels should be emotions not things like "hello" "goodbye"
 * "I'm questing" "I'm going to X" and so on. It's a form of empathy,
 * not communication, though it may be used that way if they are creative.
 *
 * The value field may be either an array or a string aliased to another index.
 * mapping ufeel = ([
 *     (string)"ufeel1" : (string)"alias",
 *     (string)"ufeel2" : (string *)({ "my msg", "their msg" }),
 *     ])
 */
private static mapping m_ufeel = ([
	 "active" : ({ "sensation of activity", "feeling active" }),
    "adventurous" : ({ "adventurous feelings", "feeling adventurous" }),
	 "afraid" : ({ "fear", "feeling afraid" }),
	  "agree" : "agreeable",
      "agreeable" : ({ "agreement", "feeling agreeable" }),
	 "amazed" : ({ "amazement", "feeling amazed" }),
	 "amused" : ({ "feeling of amusement", "feeling amused" }),
	  "angry" : ({ "anger", "feeling very angry" }),
	"annoyed" : ({ "annoyance", "feeling annoyed" }),
	"anxious" : ({ "anxiety", "feeling rather anxious" }),
     "apologetic" : ({ "regret", "feeling apologetic" }),
   "appreciative" : ({ "appreciation", "feeling appreciative" }),
	 "ardent" : ({ "ardency", "feeling ardent" }),
      "attentive" : ({ "attention", "feeling attentive" }),
      "available" : ({ "availability", "available" }),
	   "awed" : ({ "feeling of awe", "in awe" }),

        "bashful" : ({ "self-consciousness", "feeling bashful" }),
        "blessed" : ({ "feeling that you are blessed", "feeling blessed" }),
   "bloodthirsty" : ({ "thirst for blood", "feeling bloodthirsty" }),
	  "bored" : ({ "feeling of boredom", "feeling rather bored" }),
	  "bossy" : ({ "bossiness", "feeling bossy" }),
	   "busy" : ({ "busyness", "feeling busy" }),

	   "calm" : ({ "feeling of calm", "feeling calm" }),
       "cautious" : ({ "caution", "feeling cautious" }),
    "comfortable" : ({ "feeling of comfort", "feeling comfortable" }),
	"concern" : ({ "concern", "feeling concerned" }),
      "confident" : ({ "feeling of confidence", "feeling confident" }),

       "confused" : ({ "confusion", "feeling confused" }),
       "consoled" : ({ "consolement", "feeling consoled" }),
	"content" : ({ "sense of contentment", "feeling quite content" }),
      "convinced" : ({ "conviction", "feeling convinced" }),
	  "brave" : "courageous",
     "courageous" : ({ "courage", "feeling courageous" }),
	"curious" : ({ "curiosity", "feeling curious" }),

    	 "danger" : ({ "feeling of danger", "in danger" }),
    	 "daring" : ({ "daring", "feeling daring" }),
     	   "dead" : "death",
	      "death" : ({ "feeling that Mascarvin is near", "near death" }),
      "delighted" : ({ "delight", "feeling delighted" }),
       "defeated" : ({ "feeling of defeat" , "feeling defeated" }),
      "depressed" : ({ "depression", "feeling depressed" }),
    	 "desire" : ({ "desire", "wanting something" }),
     "determined" : ({ "determination", "feeling determined" }),
      "dignified" : ({ "feeling of dignity", "feeling dignified" }),
     "diplomatic" : ({ "desire for diplomacy", "feeling diplomatic" }),
   "disagreeable" : ({ "disagreement", "feeling disagreeable" }),
    	"disgust" : ({ "disgust", "feeling disgusted" }),
     "dismissive" : ({ "dismissal", "feeling dismissive" }),
     "distraught" : ({ "feeling of distress", "feeling distraught" }),
     "distracted" : ({ "feelings of distraction", "feeling distracted" }),

    	  "eager" : ({ "eagerness", "feeling eager" }),
         "elated" : ({ "elation", "feeling elated" }), 
      "energetic" : ({ "energy", "feeling energetic" }),
     "enthralled" : ({ "fascination", "feeling enthralled" }),
       "euphoric" : ({ "feeling of euphoria", "feeling euphoric" }),
    	"envious" : ({ "feeling of envy", "feeling envious" }),
    	"excited" : ({ "excitement", "feeling excited" }),

           "fear" : "fearful",
        "fearful" : ({ "fear", "feeling fearful" }),
         "feisty" : ({ "feistiness", "feeling feisty" }),
     "frustrated" : "frustration",
    "frustration" : ({ "frustration", "feeling frustrated" }),

        "ghastly" : ({ "feeling ghastly", "feeling ghastly" }),  
       "generous" : ({ "desire to give", "feeling generous" }),
       "grateful" : ({ "gratitude", "feeling grateful" }),
      "gratified" : ({ "feeling of gratification", "feeling gratified" }),
         "greedy" : ({ "greed", "feeling greedy" }),
         "grumpy" : ({ "grumpiness", "feeling grumpy" }),

	      "happy" : ({ "happiness", "feeling very happy" }),
         "hahabi" : ({ "panic", "in Hahabi's grasp" }),
	      "haste" : ({ "haste", "in a hurry" }),
    "heartbroken" : ({ "heartbreak", "feeling heartbroken" }),
	       "help" : ({ "need for help", "in need of help" }),
	    "helpful" : ({ "yearning to help", "wanting to be helpful" }),
       "homesick" : ({ "desire to be home", "longing for home" }),
	       "hope" : ({ "hopefulness", "feeling hopeful" }),
      "horrified" : ({ "horror", "feeling horrified" }),
	     "hunted" : ({ "feeling of being hunted", "being hunted" }),
	    "hunting" : ({ "thrill in the Hunt", "enjoying a thrilling hunt" }),
	     "hungry" : ({ "hunger", "hungry" }),

      "impatient" : "impatience",
     "impatience" : ({ "impatience", "feeling impatient" }),
   "inconsolable" : ({ "inconsolability", "feeling inconsolable" }),
    "independent" : ({ "feeling of independence", "feeling independent" }),
    "indifferent" : ({ "indifference", "feeling indifferent" }),
       "insecure" : ({ "insecurity", "feeling insecure" }),
       "inspired" : ({ "inspiration", "feeling inspired" }),
     "interested" : ({ "feeling of interest", "feeling interested" }),
     "irresolute" : ({ "uncertainty", "feeling irresolute" }),

	  "jazur" : ({ "feeling that Jazur is with you",
	              "feeling graced by Jazur" }),
	    "joy" : ({ "joy", "feeling joyful" }),

	  "alone" : "lonely",
	 "lonely" : ({ "loneliness", "missing you" }),
	   "lost" : ({ "feeling of being lost", "feeling lost" }),

    "masochistic" : ({ "masochistic feelings", "feeling masochistic" }),
     "meditative" : ({ "desire to meditate", "feeling meditative" }),	
     "melancholy" : ({ "melancholy", "feeling melancholic" }),
       "merciful" : ({ "feeling of mercy", "feeling merciful" }),
    "mischievous" : ({ "craving for mischief", "feeling mischievous" }),
       "mistaken" : ({ "mistakenness", "feeling mistaken" }),
    	  "moody" : ({ "moodiness", "feeling moody" }),
      "murderous" : ({ "desire to kill someone",
	              "feeling ready to kill someone" }),

       "obedient" : ({ "obedience", "feeling obedient" }),

	"nervous" : ({ "nervousness", "feeling nervous" }),
	"nitikas" : ({ "avarice", "being guided by Nitikas" }),
	"nostalgic" : ({ "nostalgic", "feeling nostalgic" }),

	   "pain" : ({ "pain", "in pain" }),
        "passion" : "passionate",
     "passionate" : ({ "passion", "feeling passionate"}),
	"patient" : ({ "patience", "being patient" }),
	   "pity" : ({ "feeling of pity", "feeling pity" }),
	"playful" : ({ "playfulness", "feeling playful" }),
	"pleased" : ({ "pleasure", "pleased about something" }),
	  "ready" : "prepared",
       "prepared" : ({ "readiness", "feeling ready" }),
	  "pride" : "proud",
	  "proud" : ({ "feeling of great pride", "feeling very proud" }),

	  "quiet" : ({ "quietness", "feeling quiet" }),

     "rebellious" : ({ "rebelliousness", "feeling rebellious" }),
    	 "regret" : ({ "regret", "feeling regretful" }),
    	"relaxed" : ({ "feeling of relaxation", "feeling relaxed" }),
       "relieved" : ({ "feeling of relief", "feeling relieved" }),
      "reluctant" : ({ "reluctance", "reluctance" }),
    	"remorse" : ({ "remorse", "feeling remorseful" }),
       "reserved" : ({ "reservation", "feeling reserved" }),
       "restless" : ({ "restlessness", "feeling restless" }),

	    "sad" : ({ "great sadness", "terribly sad" }),
       "sadistic" : ({ "sadistic feelings", "feeling sadistic" }),
      "satisfied" : ({ "satisfaction", "feeling satisfied" }),
	"seasick" : ({ "sensations of sailing", "feeling seasick" }),
	  "share" : ({ "empathy", "sharing your feelings" }),
	"shocked" : ({ "shock", "feeling shocked" }),
        "shy" : ({ "feeling shy", "shyness" }), 
	 "silent" : ({ "silence", "being silent" }),
        "silence" : ({ "need for silence", "desiring silence" }),
         "sisera" : ({ "carnal desires", "tickled by Sisera" }),
	 "sleepy" : ({ "need to sleep soon", "going to sleep soon" }),
       "stubborn" : ({ "strength of your resolve", "feeling stubborn" }),
     "submissive" : ({ "submissive feelings", "feeling submissive" }),
     "supportive" : ({ "support", "supportive of you" }),
      "sybaritic" : ({ "sybaritic feelings", "feeling sybaritic" }),
    "sympathetic" : ({ "sympathy", "feeling sympathetic" }),

       "tranquil" : ({ "tranquility", "feeling tranquil" }),
      "thagrinus" : ({ "confusion", "touched by Thagrinus" }),
    "thirsty" : ({ "thirst", "thirsty" }),
	  "tired" : ({ "feeling of fatigue", "feeling tired" }),
	"triumph" : ({ "feeling of triumph", "feeling triumphant" }),

	  "upset" : ({ "upset emotions", "feeling upset" }),
	  "vexed" : ({ "vexation", "feeling vexed" }),

  "uncomfortable" : ({ "discomfort", "feeling uncomfortable" }),
       "doubtful" : "unconvinced",
    "unconvinced" : ({ "doubt", "feeling unconvinced" }),
  "understanding" : ({ "understanding", "feeling understanding" }),

     "wanderlust" : ({ "impulse to travel", "feeling like travelling" }),
        "welcome" : ({ "feeling of welcome", "feeling welcome" }),
          "wrath" : ({ "wrath", "wrathful" }),
	"worried" : ({ "worry", "feeling worried" }),

          "zaren" : ({ "wrath", "possessed by Zaren" }),

]);

/*
 * Return the global ufeelings mapping for use in the Union sphere
 * guild object.
 */
public mapping
query_ufeel_map(void)	{ return m_ufeel; }

#endif  __UNION_SPHERE__
