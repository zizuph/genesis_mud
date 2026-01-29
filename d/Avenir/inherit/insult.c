//  insult.c
// Produces random insulting messages.
// Usage : Inherit this object and call insult ()
//
// May 28 1994    /Boriska

static string
*adj1 =
({
"artless", "bawdy", "beslubbering",
"bootless", "churlish", "cockered", "clouted", "craven",
"currish", "dankish", "dissembling", "droning", "errant",
"fawning", "fobbing", "froward", "frothy", "gleeking", "goatish",
"gorbellied", "impertinent", "infectious", "jarring",
"loggerheaded", "lumpish", "mammering", "mangled", "mewling",
"paunchy", "pribbling", "puking", "puny", "quailing", "rank",
"reeky", "roguish", "ruttish", "saucy", "spleeny", "spongy",
"surly", "tottering", "unmuzzled", "vain", "venomed",
"villainous", "warped", "wayward", "weedy", "yeasty"
});

static int
adj1_len = sizeof(adj1);

static string
*adj2 =
({
"base-court", "bat-fowling", "beef-witted",
"beetle-headed", "boil-brained", "clapper-clawed", "clay-brained",
"common-kissing", "crook-pated", "dismal-dreaming", "dizzy-eyed",
"doghearted", "dread-bolted", "earth-vexing", "elf-skinned",
"fat-kidneyed", "fen-sucked", "flap-mouthed", "fly-bitten",
"folly-fallen", "fool-born", "full-gorged", "guts-griping",
"half-faced", "hasty-witted", "hedge-born", "hell-hated",
"idle-headed", "ill-breeding", "ill-nurtured", "knotty-pated",
"milk-livered", "motley-minded", "onion-eyed", "plume-plucked",
"pottle-deep", "pox-marked", "reeling-ripe", "rough-hewn ", 
"rude-growing", "rump-fed", "shard-borne", "sheep-biting",
"spur-galled", "swag-bellied", "tardy-gaited", "tickle-brained",
"toad-spotted", "unchin-snouted", "weather-bitten"
});

static int
adj2_len = sizeof(adj2);

static string
*noun =
({
"apple-john", "baggage", "barnacle", "bladder",
"boar-pig", "bugbear", "bum-bailey", "canker-blossom",
"clack-dish", "clotpole", "coxcomb", "codpiece", "death-token",
"dewberry", "flap-dragon", "flax-wench", "flirt-gill",
"foot-licker", "fustilarian", "giglet", "gudgeon", "haggard",
"harpy", "hedge-pig", "horn-beast", "hugger-mugger", "jolthead",
"lewdster", "lout", "maggot-pie", "malt-worm mammet", "measle",
"minnow", "miscreant", "moldwarp", "mumble-news", "nut-hook",
"pigeon-egg", "pignut", "puttock", "pumpion", "ratsbane", "scut",
"skainsmate", "strumpet", "varlot", "vassal", "whey-face",
"wagtail"
});

static int
noun_len = sizeof(noun);

public string
insult ()
{
  return (" " + adj1[random(adj1_len)] + " " + 
	  adj2[random(adj2_len)] + " " +
	  noun[random(noun_len)] );
}



















