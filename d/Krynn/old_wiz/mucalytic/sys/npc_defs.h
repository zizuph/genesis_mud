#include "/sys/stdproperties.h"

/* Height and weight definitions. */

#define INCHES	2.5		/* 2.5 centimetres = 1 inch.    */
#define FEET	30.0		/* 30 centimetres = 1 foot.     */
#define KILOS	1000		/* 1000 grammes = 1 kilogramme. */

/* Race names definitions */

#define RACE	({ "dwarf", "elf", "gnome", "hobbit", "human", "orc" })

/* Adjective (male/female) definitions */

#define ADJ  ({ ({ "scruffy", "smelly", "boring", "ugly", "sweet", "spotty", \
                   "grumpy", "cute", "greasy", "moody", "tiresome", "rude", \
                   "sweaty", "bald" }), \
		({ "sweet", "cute", "animated", "rude", "grumpy", "tiresome", \
                   "boring", "friendly", "energetic", "dull", "merry", \
                   "nervous", "jovial", "melancholy" }), \
		({ "stocky", "loud-mouthed", "big-headed", "scarred", \
                   "stubbly", "excitable", "stout", "pale", "arrogant", \
                   "idiotic", "deranged", "fidgity", "handsome", "brave" }), \
		({ "philosophical", "haughty", "excited", "stroppy", "pale", \
                   "deranged", "fidgety", "idiotic", "arrogant", "light", \
                   "big-headed", "petite", "slender", "willowy" }) })

/* Name (male/female and race) definitions
 *
 * Many thanks to Blare for his brilliant help in thinking up new names.
 */

#define NAMES ({ ({ "grumpylump", "rockeater", "gutsy", "burrfoot", "graft", \
                    "granite", "hammerjaw", "dween", "bedrock", "scorn" }), \
		 ({ "eledra", "talumna", "teronna", "hulata", "kilatti", \
                    "bezuda", "ramadali", "ralapna", "trasteri", "gorum" }), \
		 ({ "elendor", "endoran", "geldren", "titlan", "elessedil", \
                    "emerman", "ander", "erelin", "eltar", "tyrillian" }), \
		 ({ "willow", "erin", "spirit", "star" , "tellessa", \
                    "moonbeam", "blossom", "buttercup", "wildflower", \
                    "snowflake" }), \
		 ({ "runt", "pipsqueak", "tasslehof", "toadstool", "stumpy", \
                    "wenders", "fleetfoot", "halcom", "forton", "spike" }), \
		 ({ "mouse", "twinkle", "coriander", "finch", "gable", \
                    "tulana", "mogne", "harro", "grahilda", "pimlico" }),\
		 ({ "reginard", "hamson", "marmadas", "merimac", "bingo", \
                    "otho", "frollin", "gorbadoc", "isengrim", "mundo" }), \
		 ({ "tulip", "pansy", "dandelion", "rosebud", "chrysanthemum", \
                    "daffodil", "crocus", "rose", "petal", "sunbeam" }), \
		 ({ "thugruff", "balthus", "swinebeard", "hannicus", "ronin", \
                    "lexar", "keldor", "mantrax", "torak", "laskar" }), \
		 ({ "mathilda", "sabona", "monika", "clementine", "susannah", \
                    "samantha", "lucy", "elizabeth", "patricia", "lisa" }), \
		 ({ "rog", "scarface", "basher", "bonecrusher", "bigmouth", \
                    "firebreather", "grogslosher", "blackeye", "redface", \
                    "scourge" }), \
		 ({ "grelda", "grognog", "krilboth", "ludrak", "hasni", \
                    "drobnok", "garuk", "brist", "thast", "dridda" }) })

/* Some standard emotions */

#define EMOTES	({	"belch",	"burp",		"cackle",	\
			"cough",	"explode",	"fart",		\
			"flip",		"frown",	"fume",		\
			"glare",	"grin",		"growl",	\
			"grumble",	"rolleyes",	"scowl",	\
			"scratch",	"scream",	"sigh",		\
			"smile",	"smirk",	"sneeze",	\
			"steam",	"stomp",	"stretch",	\
			"tap",		"think",	"twiddle"	})

#define FEMOTES	({	"bat",		"blush",	"bounce",	\
			"cackle",	"chuckle",	"cough",	\
			"curtsey",	"dance",	"duh",		\
			"eeks",		"eyebrow",	"flip",		\
			"frown",	"fume",		"gasp",		\
			"giggle",	"grin",		"groan",	\
			"grumble",	"hiccup",	"hmm",		\
			"jump",		"laugh",	"moan",		\
			"nod",		"purr",		"raspberry",	\
			"sigh",		"sing",		"smile",	\
			"smirk",	"snap",		"sneeze",	\
			"snigger",	"stretch",	"strut",	\
			"sulk",		"twiddle",	"wiggle",	\
			"wink",		"yawn",		"yodel"		})
