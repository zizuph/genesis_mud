/*
 * Created by      : Shadowlynx 
 * Creation Date   : December 10, 1999
 * Copywrite       : Shadow deForest
 * File            : /d/Genesis/start/human/sparkle/train/train_main.c
 * Description     : Main hall of the Sparkle Training Center.
 * Purpose         : A player will be able to list their guilds here.
 * Comments        : 
 * Modification log: 
 */

#pragma save_binary
#pragma strict_types

/* Mudlib support for training skills, meditation, and listing guilds. */
inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";

/* To be inherited by all Sparkle rooms. */
inherit "/d/Genesis/start/human/sparkle/base_room";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#include "../defs.h"

/* Prototypes */
void     set_up_skills();
/* VBFC for long description, based on status/presence of cat */
string   my_long(string arg);

void
create_room()
{
    set_short("Main Hall of the Sparkle Training Center");
    set_long(my_long);

add_item(({"walls","stone walls","rough stone walls"}),"All" +
  " four walls are elaborately decorated with trophies" +
  " brought back from successful adventures.\n");

add_item("wall","Which wall would you like to look at?" +
  " The north, south, west or east wall?\n");

add_item("north wall","In the center of this northern wall" +
  " is a set of glass paned double doors leading out" +
  " into a courtyard.\n");

add_item("south wall","In the center of this southern wall" +
  " is the main entrance door to the Training Center." +
  " Going through this door will take you back out" +
  " into the market square of Sparkle.\n");

add_item("west wall","Dominating the center of this western" +
  " wall is a huge stone fireplace with a blazing fire" +
  " crackling in the hearth. Next to the fireplace is" +
  " a high arched doorway leading into the west wing" +
  " of the training center.\n");

add_item("east wall","Affixed to the center of this eastern" +
  " wall is a large guild board which lists the" +
  " guilds of which you are currently a member.\n");

add_item("trophies","Numerous trophies decorate the walls" +
  " displaying the bravery of past adventurers. Among" +
  " these trophies, you spot a black lion's head, a wild" +
  " boar head, the preserved body of a death spider" +
  " the head of a ferocious red dragon, a bestial" +
  " statue of a gargoyle, the head of a frost giant," +
  " the fearsome heads of a hydra. the body of a giant" +
  " shadow lizard, the head of a medusa, a minotaur" +
  " head, the body of a giant octopus, the head of a" +
  " snow wolf, the coiled body of a wyrm and the" +
  " unmistakeable head of a dogcow. Perhaps a closer examination" +
  " is in order.\n");

add_item(({"head","body","trophy","trophy head"}),"Which trophy" +
  " did you wish to look at?\n");

add_item(({"lion","black lion","lion head","black lion head",
    "lion's head","black lion's head","head of a black lion",
    "head of a lion"}),"This is the head of a black lion." +
  " It is not known whether black lions are the result" +
  " of wizard experiments or natural cross-breeding in" +
  " the wild. What is certain, is that they are a cross" +
  " between a black panther and a lion, a mix that makes" +
  " them the most savage of all the hunting cats. Black" +
  " lions are among the most deadly of predators.\n");

add_item(({"boar","wild boar","boar head","wild boar head",
    "head of a wild boar","head of a boar","boar's head",
    " wild boar's head"}),"This is the head of a wild" +
  " boar. Wild boars are hunted for their choice meat" +
  " and pelts which can fetch a small fortune in gold." +
  " They look like huge pigs covered in tangled clumps" +
  " of coarse reddish-brown hair. They are brutish," +
  " agressive beasts and will stand and fight with their" +
  " tusks. with an almost savage fury.\n");

add_item(({"spider","death spider","preserved death spider",
    "preserved spider","preserved body","preserved spider body",
    "spider body","preserved death spider body","body of a spider",
    "preserved body of a spider","preserved body of a death spider",
    "body of a death spider","spider's body","death spider's body",
    "preserved spider's body","preserved death spider's body"}),"The" +
  " death spider is a most deadly foe. These diabolical" +
  " creatures appear as massive grey-black spiders with" +
  " demonic heads. Being almost five meters across, they" +
  " lurk in dungeons and ruins ready to trap an unwary" +
  " adventurer.\n");

add_item(({"dragon","red dragon","ferocious red dragon",
    "ferocious dragon","dragon's head","red dragon's head",
    "ferocious dragon's head","ferocious red dragon's head",
    "dragon head","red dragon head","ferocious dragon head",
    "ferocious red dragon head","head of a ferocious dragon",
    "head of a ferocious red dragon","head of a red dragon",
    "head of a dragon"}),"Red dragons are hoarders who" +
  " relish collecting coins, jewels and treasure. When" +
  " encopuntered, a red dragon will usually be in a" +
  " cavern sprawled across the top of a huge pile of" +
  " valuables. Red dragons are automatically suspicious" +
  " of anyone they meet, believing them to be thieves" +
  " intent on stealing their treasure and will attack" +
  " immediately. They can shoot fire-balls from their" +
  " mouths, which they send roaring through the air" +
  " to explode upon their target.\n");

add_item(({"statue","gargoyle statue","bestial gargoyle",
    "bestial gargoyle statue","gargoyle","bestial statue",
    "statue of a gargoyle","bestial statue of a gargoyle",
    "statue of a bestial gargoyle"}),"Gargoyles are" +
  " ferocious beasts whose ability to blend with the" +
  " surrounding rock is such that they will surprise" +
  " a prey almost every time and be able to deliver" +
  " the first blow automatically. They are roughly" +
  " humanoid in shape, with clawed hands and feet," +
  " and bestial heads brimming with teeth and horns." +
  " A pair of large leathery wings sprouts from" +
  " their backs, and a point-tipped tail hangs" +
  " behind. They are coloured a mottled grey that" +
  " looks just like stone. This camouflage allows" +
  " them to play their favorite trick on unsuspecting" +
  " adventurers - standing motionless on a piece" + 
  " of stone and pretending to be a statue until" +
  " they can strike.\n");

add_item(({"giant","frost giant","frost giant head",
    "giant head","giant's head","frost giant's head",
    "head of a giant","head of a frost giant"}),"Frost" +
  " giants can range up to six meters tall and live" +
  " in the coldest regions. Their skin is pale white," +
  " but much of it is usually hidden by their long" +
  " white beards and hair, and under swathes of" +
  " polar bear fur. Frost giants are not afraid" +
  " of attacking adventurers, for they know that" +
  " gold may often be found in their pockets. Frost" +
  " giants dearly love to hoard their treasure in" +
  " caves.\n");

add_item(({"hydra","fearsome hydra","heads of a hydra",
    "hydra heads","fearsome hydra heads","hydra's heads",
    "fearsome hydra's heads","heads of a fearsome hydra"}),
  "The hydra is a many-headed creature which can" +
  " be found in many differnt areas. Though they" +
  " are rare, they often figure as the villains" +
  " in heroic tales. They are reptilian creatures," +
  " like fat-bodied snakes, with a number of large" +
  " heads rising on long necks from their bodies." +
  " The beast can have as little as two or as many" +
  " as seven wide-mouthed, fang-filled heads. Covered" +
  " in greenish-brown scales, this nightmarish beast" +
  " can grow as much as ten meters long.\n");

add_item(({"lizard","shadow lizard","giant shadow lizard",
    "giant lizard","lizard body","giant shadow lizard body",
    "giant lizard body","body of a giant shadow lizard",
    "body of a giant lizard","body of a shadow lizard",
    "giant shadow lizard's body","shadow lizard's body",
    "lizard's body"}),"Giant shadow lizards can be" +
  " major hazards to adventurers. They can be as" +
  " large as six meters tall and a half meter high." +
  " The creatures appear slow as they lumber along" +
  " on four ungainly feet and drag their cumbersome" +
  " tails behind them, but in a fight they prove" +
  " to be remarkably agile, darting between swords" +
  " to deliver savage bites with their large fang" +
  " filled mouths.\n");

add_item(({"medusa","medusa head","medusa's head",
    "head of a medusa"}),"The Medusa is a strange" +
  " humanoid that looks like a wizened old lady" +
  " dressed in ragged clothes, her head covered" +
  " by a thick shawl. She appears harmless and" +
  " frail. Many adventurers have been taken in" +
  " by this helpless appearance and drawing near" +
  " to her they have offered to help by lending" +
  " a strong arm to steady the poor old crone." +
  " With a demonic laugh, the Medusa will throw" +
  " back the shawl and fix the unwary traveller" +
  " with a red-eyed stare which has the power to" +
  " paralyze the victim. In place of the Medusa's" +
  " hair sprouts a mass of wriggling snakes. If" +
  " you stare too long at a Medusa, your limbs" +
  " will begin to stiffen and within moments" +
  " you will be nothing but solid stone!\n");

add_item(({"minotaur","head of a minotaur",
    "minotaur's head","minotaur head"}),"This" +
  " perilous beast is half-man, half-bull" +
  " making for a fearsom combination. The" +
  " head is shaggy and bovine, with a large" +
  " pair of horns curving from the top. The" +
  " favorite method of attack from a minotaur" +
  " is a head-down charge, snorting and" +
  " stamping just like a bull.\n");

add_item(({"octopus","giant octopus","octopus body",
    "giant octopus body","body of a giant octopus",
    "body of an octopus","giant octopus's body",
    "octopus's body"}),"A giant octopus is a" +
  " cunning predator, with a strong dextrous" +
  " body. They can grow to alarming sizes." +
  " Their favorite tactic is to grasp a" +
  " living creature, gradually eenfold it" +
  " in their tentacles and crust the life" +
  " out of it.\n");

add_item(({"wolf","snow wolf","snow wolf head",
    "wolf head","wolf's head","snow wolf's head",
    "head of a wolf","head of a snow wolf"}),"Snow" +
  " wolves are larger than normal wolves, and" +
  " are savage killers which fear nothing. They" +
  " are covered all over with shaggy white fur," +
  " and blend well into their surroundings." +
  " Only their hunger-grazed red eyes will" +
  " give them away. Fire will keep the snow" +
  " wolf at bay, but wood burns quicker than" +
  " their patience slackens. The moment the" +
  " fire begins to die they will close in for" +
  " the kill.\n");

add_item(({"wyrm","coiled wyrm","coiled wyrm body",
    "wyrm body","coiled body of a wyrm","coiled body",
    "wyrm's body","coiled wyrm's body","body of a wyrm",
    "body of a coiled wyrm"}),"Wyrms are solitary beasts" +
  " thought to be related to dragons. They have" +
  " lizard-like heads and leathery wings. They" +
  " live to a great age and are highly intelligent." +
  " Wyrms are thin and snake-like, without legs" +
  " or feet and they cannot fly. These great white" +
  " beasts dwell in icy regions where their colouring" +
  " allows them to blend with their background." +
  " Their usual method of attack is to rear up" +
  " on their coils, wings outstretched for balance," +
  " and blast their victims with their icy breath." +
  " They can also bite their victim but prefer to" +
  " use their breath weapon as much as possible.\n");

add_item(({"dogcow","unmistakable head of a dogcow",
    "unmistakable dogcow head","head of a dogcow",
    "dogcow's head","unmistakable dogcow's head",
    "head of an unmistakable dogcow"}),"This dogcow" +
  " is a rather strange creature. It looks somewhat" +
  " like a very small cow, or perhaps a very large" +
  " terrier. It is covered with long white hair with" +
  " large patches of carbon black mixed in. A pair" +
  " of bone-yellow horns sprout from the top of the" +
  " head and are sharpened to a gleaming point. It" +
  " has deep soulful eyes but doesnt appear dangerous." +
  " However, many an adventurer has fallen victim to" +
  " its beguiling song of Moof!\n");

add_item(({"fireplace","stone fireplace","hearth",
    "huge stone fireplace"}),"A huge stone fireplace" +
  " dominates the west wall. The well molded" +
  " stones appear to be of the same type as" +
  " the surrounding walls. Several small curios" +
  " are displayed along the length of the wood" +
  " mantle. A blazing fire crackles in the" +
  " hearth. A large iron grate keep the sparks" +
  " at bay.\n");

add_item(({"mantle","wood mantle","fireplace mantle",
    "wood-grained mantle","wood-grained fireplace mantle"}),
  "This wood-grained mantle runs along the width" +
  " of the stone fireplace a couple feet above" +
  " the blazing fire crackling in the hearth." +
  " Several small curios are displayed along" +
  " the length of the mantle.\n");

add_item(({"curio","small curio","item","small item"}),
  "Which item did you wish to look at?\n");

add_item(({"curios","small curios","items","small items"}),
  "Several small curios are displayed along the" +
  " length of the wood-grained mantle. Upon closer" +
  " inspection, you discern what appears to be a" +
  " miniature replica of a pirate ship enclosed" +
  " in a glass bottle as the centerpiece. A little" +
  " to the left of the ship is a small wood carving" +
  " of what looks like the steering wheel of a ship," +
  " To the far left is a rather strange contraption" +
  " that looks suspiciously like a timepiece under" +
  " a glass dome. On the right of the tiny ship is" +
  " a spyglass propped up on a small three-legged" +
  " tripod. To the far right is a fairly large" +
  " transparant globe on a base of pure gold." +
  " Inside the water filled orb is a sparkling" +
  " minature city handcrafted in exquisite detail.\n");

add_item(({"globe","large globe","transparent globe",
    "large transparent globe","globe on a base of pure gold",
    "large transparent globe on a base of pure gold","orb",
    "large globe on a base of pure gold","water filled orb",
    " transparent globe on a base of pure gold"}),"This" +
  " is a fairly large transparent globe completely" +
  " filled with azure blue water. Inside the orb" +
  " is a sparkling miniature city handcrafted in" +
  " exquisite detail.\n");

add_item(({"water","blue water","azure blue water",
    "azure water"}),"Azure blue water completely fills" +
  " the large transparent globe.\n");

add_item(({"city","minature city","sparkling city",
    "sparkling minature city","Chyvawil","chyvawil"}),
  "An exquisitely handcrafted miniature city" +
  " sparkles inside the water filled orb. The" +
  " detail is so precise you can almost see" +
  " tiny figurines walking along the twinkling" +
  " streets. The buildings tower above the" +
  " cobblestone lanes in varying degrees of" +
  " height. Dark shadowy doorways and blackened" +
  " windows are interspersed among the small" +
  " structures. It looks so amazingly real" +
  " you could almost picture yourself walking" +
  " amongst the citizens.\n");

add_item(({"spyglass","propped spyglass on a tripod",
    "propped spyglass","spyglass on a tripod","telescope",
    "spyglass propped up on a small three-legged tripod",
    "spyglass propped up on a three-legged tripod",
    "spyglass propped up on a small tripod"}),"This" +
  " spyglass is made of brass having a glass" +
  " eyepiece. The purpose of this instrument" +
  " is to look through the eyepiece to bring" +
  " distant objects into close proximity for" +
  " viewing in greater detail. Crewmen on a" +
  " ship find it most useful when sailing" +
  " to watch the horizon for land masses or" +
  " other ships.\n");

add_item(({"tripod","small tripod","three-legged tripod",
    "small three-legged tripod"}),"Like the spyglass" +
  " this small three-legged tripod is also made" +
  " of brass. It has three small legs, all about" +
  " four inches long. The top end of each leg is" +
  " connected to a curved brass cradle. The legs" +
  " are then extended at perfect sixty degree" +
  " angles from the cradle to form a perfectly" +
  " triangular shaped base.\n");

add_item(({"cradle","brass cradle","curved cradle",
    "curved brass cradle"}),"This is a curved brass" +
  " cradle in which the spyglass rests.\n");

add_item(({"dome","glass dome"}),"This is a glass" +
  " dome protecting a strange contraption that" +
  " looks suspiciously like a timepiece.\n");


// add_exit(TOWN_DIR + "road3","north");
add_exit("/d/Genesis/wiz/domain", "south", "@@sblock");

add_prop(OBJ_S_WIZINFO, "@@wizinfo");
add_prop(ROOM_I_INSIDE, 1);
add_prop(ROOM_I_TYPE, ROOM_NORMAL);
set_noshow_obvious(1);

create_skill_raise();
set_up_skills();
}

string
my_long(string arg)

nomask void
make_wiz()
{
    "/secure/master"->create_wizard(TI->query_real_name());
    TI->update_hooks();
}

nomask int
sblock()
{
    object ob;

    if (TP->query_wiz_level() && !TP->query_prop("walk_backwards"))
    {
	write ("\nYou sense the magic at work all around you as you step"+
	  "through the door.\n\n");
	return 0;
    }
    if (!TP->query_wiz_level() && TP->query_prop("walk_backwards") &&
      (ob = present("dust of contrariness", TP)) &&
      ob->query_rubbed() && (TP->query_average_stat() >= 100))
    {
	/* Promote the player to apprentice and tell everyone about
	   the happy event */
	ob->remove_object(); /* get rid of contrariness */
	TP->move_living("south", "/d/Genesis/wiz/volcano_centre");
	write("Welcome to wizardhood.\n");
	map(users(), "wtell", this_object());
	make_wiz();

	TP->command("save");
	return 1;
    }
    write("A strong force field prevents you from going that way.\n");
    return 1;
}

void
wtell(object ob)
{
    if (ob != TP)
	ob->catch_msg("There is a flash of pure magic, and suddenly "+
	  "you realise that\n"+ QNAME(TP) +" has been accepted "+
	  "in to the ranks of wizards.\n");
}

void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    gs_leave_inv(ob, to);
}

void
set_up_skills()
{
    string me, ot;

    me = "fight unarmed"; ot = me;
    sk_add_train(SS_UNARM_COMBAT,  ({ me, ot }),     0, 0, 30 );
    me = "defend yourself"; ot = "use defence skill";
    sk_add_train(SS_DEFENCE,  ({ me, ot }),     0, 0, 20 );
    me = "use a sword"; ot = me;
    sk_add_train(SS_WEP_SWORD,  ({ me, ot }),     0, 0, 25 );
    me = "use a knife"; ot = me;
    sk_add_train(SS_WEP_KNIFE,  ({ me, ot }),     0, 0, 30 );
    me = "use a club"; ot = me;
    sk_add_train(SS_WEP_CLUB,   ({ me, ot }),	 0, 0, 25 );
    me = "use spellcraft"; ot = me;
    sk_add_train(SS_SPELLCRAFT, ({ me, ot }),    0, 0, 20 );
    me = "appraise the quality of different objects"; ot = me;
    sk_add_train(SS_APPR_OBJ,	({ me, ot }),      0, 0, 30 );
    me = "appraise the value of different objects"; ot = me;
    sk_add_train(SS_APPR_VAL,	({ me, ot }), 0, 0, 30 );
    me = "swim"; ot = me;
    sk_add_train(SS_SWIM,	({ me, ot }), 0, 0, 50 );
    me = "climb"; ot = me;
    sk_add_train(SS_CLIMB,	({ me, ot }), 0, 0, 40 );
    me = "hunt wild game"; ot = me;
    sk_add_train(SS_HUNTING,	({ me, ot }), 0, 0, 30 );
    me = "be aware of your surroundings"; ot = "his awareness";
    sk_add_train(SS_AWARENESS, ({ me, ot }),     0, 0, 40 );
    me = "trade and make deals"; ot = me;
    sk_add_train(SS_TRADING,	({ me, ot }),       0, 0, 30 );
}

static int
walk(string str)
{
    notify_fail("How or where do you want to walk?\n");
    if (!str)
	return 0;

    if (str == "backwards")
    {
	TP->add_prop("walk_backwards", 1);
	write("You are now walking backwards.\n");
	say(QCTNAME(TP) + " turns around and starts walking backwards.\n");
	return 1;
    }

    if (str == "forwards")
    {
	TP->add_prop("walk_backwards", 0);
	write("You are now walking forwards.\n");
	say(QCTNAME(TP) + " turns around and starts walking forwards.\n");
	return 1;
    }

    if (parse_command(str, this_object(), "'backwards' 'through' [the] 'portal' / 'curtain' / 'curtains'"))
    {
	TP->add_prop("walk_backwards", 1);
	write("You walk back first towards the portal.\n");
	say(QCTNAME(TP) + " walks back first towards the portal.\n");
	return !sblock();
    }
    return 0;
}

void
init()
{
    ::init();

    init_skill_raise();
    init_guild_support();

    //    add_action(walk, "walk");
    //    add_action(walk, "go");
}
