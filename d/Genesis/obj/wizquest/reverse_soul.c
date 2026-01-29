#pragma save_binary

inherit "/cmd/std/soul_cmd";

/* **************************************************************************
 * Return a proper name of the soul in order to get a nice printout.
 */
string
get_soul_id()
{
    return "reversesoul";
}

/* **************************************************************************
 * This is a command soul.
 */
int
query_cmd_soul()
{
    return 1;
}

/* **************************************************************************
 * The list of verbs and functions. Please add new in alfabetical order.
 */
mapping
query_cmdlist()    
{
    return ([
	     "applaud":"puke",

	     "blush":"blush",
	     "bounce":"scream",
	     "bow":"spit",
	     "burp":"burp",

	     "cackle":"cackle",
	     "choke":"choke",
	     "chuckle":"chuckle",
	     "clap":"clap",
	     "comfort":"slap",
	     "complain":"thank",
	     "confuse":"confuse",
	     "confused":"think",
	     "cough":"cough",
	     "cry":"laugh",
	     "cuddle":"cuddle",
	     "curtsey":"curtsey",

	     "dance":"dance",
	     "despair":"smirk",

	     "fart":"wiggle",
	     "finger":"love",
	     "flip":"sulk",
	     "fondle":"fondle",
	     "forget":"remember_live",
	     "french":"french",
	     "frown":"smile",

	     "gasp":"gasp",
	     "giggle":"giggle",
	     "glare":"glare",
	     "grin":"grin",
	     "groan":"groan",
	     "grope":"ruffle",
	     "grovel":"grovel",
	     "growl":"sigh",

	     "hiccup":"yawn",
	     "hug":"tackle",

	     "kick":"lick",
	     "kiss":"slap",
	     "knee":"french",

	     "laugh":"cry",
	     "lick":"kick",
	     "love":"finger",

	     "moan":"purr",

	     "nibble":"nibble",
	     "nod":"shake",

	     "panic":"panic",
	     "pat":"pat",
	     "point":"wave",
	     "poke":"poke",
	     "pout":"pout",
	     "puke":"applaud",
	     "purr":"moan",

	     "remember":"forget_live",
	     "ruffle":"grope",

	     "scream":"bounce",
	     "shake":"nod",
	     "shiver":"shiver",
	     "shrug":"shrug",
	     "sigh":"growl",
	     "sing":"snarl",
	     "slap":"comfort",
	     "smile":"frown",
	     "smirk":"despair",
	     "snap":"snap",
	     "snarl":"sing",
	     "sneeze":"sneeze",
	     "snicker":"snicker",
	     "sniff":"sniff",
	     "snore":"snore",
	     "snuggle":"snuggle",
	     "spit":"bow",
	     "squeeze":"squeeze",
	     "stare":"stare",
	     "steam":"steam",
	     "strut":"strut",
	     "sulk":"flip",

	     "tackle":"hug",
	     "thank":"complain",
	     "think":"confused",
	     "tremble":"tremble",
	     "twiddle":"twiddle",

	     "wave":"point",
	     "whistle":"yodel",
	     "wiggle":"fart",
	     "wink":"wink",
	     "worship":"worship",
	     "yawn":"hiccup",
	     "yodel":"whistle"

	 ]);
}



