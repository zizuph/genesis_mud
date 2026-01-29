/* glad_soul.c: The gladiator soul: Mylos, 6.8.93.
 *     Charge edited & Misc fixes: Shiva, 9/11/94, 1/15/95, 3/10/95.
 *     Emotes and General Debuging: Serpine, 4/27/95, 5/1/95.
 *     Help and mbrothers commands: Shiva, 6/26/95.
 *     Efficeincy and bug fixes: Astro & Serpine, 11/26/95.
 *     Converted some catch_msg -> catch_tell: Lucius, 01/13/2001.
 *     Modified 'brothers' to not list other guild titles: Lucius, 01/13/2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/lib/multi_alarm";

#include "defs.h"
#include <cmdparse.h>
#include <wa_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include "/std/combat/combat.h"
#include <macros.h>


#define HESHE (this_player()->query_pronoun())
#define HISHER (this_player()->query_possessive())
#define HIMHER (this_player()->query_objective())

void do_charge(object target, object attacker);
void allow_charge(object ob);
void expire_berserk(object ob, int con);
void do_berserk(object ob);
void allow_berserk(object ob);


string
get_soul_id()
{
    return "psion";
}

int
query_cmd_soul()
{
    return 1;
}

/* **********************************************************************
 * The list of verbs and functions. Please add new in alphabetical order.
 */
mapping
query_cmdlist()
{
    return ([
      /* ************** COMMANDS ************** */
      "berserk"    : "berserk",
      "ber"        : "berserk",
      "brothers"   : "list_members",
      "br"         : "list_members",
      "mbrothers"  : "list_members",
      "mbr"        : "list_members",
      "charge"     : "charge",
      "ch"         : "charge",
      "help"       : "help",
      "leave"      : "leave",
      "seecharge"  : "seecharge",

      /* ************** EMOTES **************** */
      "gadjust"    : "gadjust",
      "gbite"      : "gbite",
      "gbelch"     : "gbelch",
      "gboast"     : "gboast",
      "gbow"       : "gbow",
      "gchallenge" : "gchallenge",
      "gcrouch"    : "gcrouch",
      "gcurse"     : "gcurse",
      "gdare"      : "gdare",
      "gdeclare"   : "gdeclare",
      "gdefy"      : "gdefy",
      "gdust"      : "gdust",
      "geye"       : "geye",
      "ggloat"     : "ggloat",
      "ghear"      : "ghear",
      "ghowl"      : "ghowl",
      "glaugh"     : "glaugh",
      "glook"      : "glook",
      "grage"      : "grage",
      "groar"      : "groar",
      "gsalute"    : "gsalute",
      "gscratch"   : "gscratch",
      "gshake"     : "gshake",
      "gsharpen"   : "gsharpen",
      "gshave"     : "gshave",
      "gsneer"     : "gsneer",
      "gspin"      : "gspin",
      "gspit"      : "gspit",
      "gstance"    : "gstance",
      "gthreaten"  : "gthreaten",
      "gtooth"     : "gtooth",
    ]);
}

void
create()
{
    seteuid(getuid());
}

int
is_cutter(object cutter)
{
    if (!function_exists("create_weapon", cutter)) return 0;
    if (0 > member_array(cutter->query_wt(), ({W_SWORD,W_AXE,W_KNIFE})))
	return 0;
    return 1;
}

int
maxout(int stat)
{
    if (stat>150) return 150;
    return stat;
}

int 
is_psion(object ob)
{
    return (ob && IS_MEMBER(ob));
}

object
thing_in_inventory(string thing_needed)
{
    object *thing_list;
    if(!sizeof(thing_list=(FIND_STR_IN_OBJECT(thing_needed, TP))))
	return 0;
    return thing_list[0];
}

/* ******************* emotes begin here ********************* */

int
gadjust(string str)
{
    object *armour;

    if (!strlen(str))
    {
	write("You adjust your armour in preparation for battle.\n");
	allbb(" adjusts "+HISHER+" armour in preparation for battle.");
	return 1;
    }

    if (!sizeof(armour = FIND_STR_IN_ARR(str, TP->query_armour(-1))))
    {
	NF("Gadjust what?\n");
	return 0;
    }

    write("You adjust your " + armour[0]->short() + " in preparation "+
      "for battle.\n");
    allbb(" adjusts " + HISHER + " " + armour[0]->short() +
      " in preparation for battle.\n"); 
    return 1;
}

int
gbelch(string str)
{
    object *oblist;

    if(!strlen(str))
    {
	write("You belch rudely with the uncouth pride of a gladiator.\n");
	allbb(" belches rudely with the uncouth pride of a gladiator.");
	return 1;
    }

    if(!sizeof(oblist = parse_this(str, "%l")))
    {
	NF("Belch at whom?\n");
	return 0;
    }

    target(" belches rudely in your direction.", oblist);
    actor("You belch rudely in the direction of",oblist);
    all2act(" belches rudely in the direction of",oblist);
    return 1;
}

int
gbite(string str)
{
    object pacifier;

    if (!strlen(str))
    {
	write("You bite your tongue until blood runs down your chin.\n");
	allbb(" bites " + HISHER + " tongue until blood runs down " +
	  HISHER + " chin.");
	return 1;
    }

    if (!(pacifier = thing_in_inventory(str)))
    {
	NF("That doesn't appear to be in your inventory.\n");
	return 0;
    }

    write("You bite on the " + (pacifier->short()) + " to calm down.\n");
    allbb(" gnaws violently on " + HISHER + " " + (pacifier->short()) +
      " in order to calm " + HISHER + " berserk fury.");
    return 1;
}

int
gboast(string str)
{
    if (!strlen(str))
    { 
	write("You boast shamelessly of your prowess in battle.\n");
	allbb(" boasts shamelessly of " + HISHER + " prowess in battle.");
	return 1;
    }

    write("You shamelessly boast: " + str + "\n");
    allbb(" shamelessly boasts: " + str + "\n");
    return 1;
}

int
gbow(string str)
{
    object *oblist;
    string *how;
    how = parse_adverb_with_space(str, "deeply", 0);

    if(sizeof(TP->query_weapon(-1)))
    {

	if (!strlen(how[0]))
	{
	    write("You lower your weapons and bow your muscled body" + how[1] + ".\n");
	    all(" lowers " + HISHER + " weapons and bows " + HISHER + 
	      " muscled body" + how[1] + ".");
	    return 1;
	}

	oblist = parse_this(how[0], "[to] [the] %l");

	if (!sizeof(oblist))
	{
	    notify_fail("Bow to whom?\n");
	    return 0;
	}

	actor("You lower your weapons and bow your muscled body" + how[1] + " to", oblist); 
	target(" lowers " + HISHER + " weapons and bows " + HISHER + 
	  " muscled body" + how[1] + " to you.", oblist);
	all2act(" lowers " + HISHER + " weapons and bows " + HISHER +
	  " muscled body" + how[1] + " to", oblist);
	return 1;

    }
    else
    {

	if (!strlen(how[0]))
	{
	    write("You bow your muscled gladiator's body" + how[1] + ".\n");
	    all(" bows " + HISHER + " muscled gladiator's body" + how[1] + ".");
	    return 1;
	}

	oblist = parse_this(how[0], "[to] [the] %l");

	if (!sizeof(oblist))
	{
	    notify_fail("Bow to whom?\n");
	    return 0;
	}

	actor("You bow your muscled gladiator's body" + how[1] + " to", oblist); 
	target(" bows " + HISHER + " muscled gladiator's body" + how[1] +
	  " to you.", oblist);
	all2act(" bows " + HISHER + " muscled gladiator's body" + how[1] +
	  " to", oblist);
	return 1;

    }
}

int
gchallenge(string str)
{
    object *oblist;

    if(!strlen(str))
    {
	write("You offer to face anyone in the arena stupid enough "+
	  "to challenge your might.\n");
	all(" challanges everyone in earshot to face " + HIMHER +
	  " in the arena. If they dare.");
	return 1;
    }

    if(!sizeof(oblist = parse_this(str, "%l")))
    {
	NF("Challenge the unworthy gains one nothing?\n");
	return 0;
    }

    target(" challenges you to combat with bloodlust "+
      "in " + HISHER + " eye.", oblist);
    actor("You challenge", oblist," to combat with bloodlust "+
      "in your eye.");
    all2act(" challenges", oblist," to combat with bloodlust "+
      "in " + HISHER + " eye.");
    return 1;
}

int
gcrouch(string str)
{
    object *oblist;

    if(!strlen(str))
    {
	write("You jump into a fighting crouch.\n");
	allbb(" jumps into a fighting crouch.");
	return 1;
    }

    if(!sizeof(oblist = parse_this(str, "[before] %l")))
    {
	NF("Crouch before who?\n");
	return 0;
    }

    targetbb(" jumps into a fighting crouch in front of you.", oblist);
    actor("You jump into a fighting crouch in front of", oblist);
    all2actbb(" jumps into a fighting crouch in front of", oblist);
    return 1;
}

int
gcurse(string str)
{
    object *oblist;

    if(!strlen(str))
    {
	write("You call upon Kalak to destroy all that oppose you.\n");
	all(" curses loudly, calling on Kalak to strike down " + HISHER + " foes.");
	return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[at] / [on] [the] %l")))
    {
	NF("Curses are not something to be lightly bandied about.\n");
	return 0;
    }

    target(" curses, calling on Kalak to strike you dead.", oblist);
    actor("You call upon Kalak to curse", oblist);
    all2act(" curses violently, calling for Kalak to strike down", oblist);
    return 1;
}

int
gdare(string str)
{
    object lineindust, *oblist;

    setuid();
    seteuid(getuid());

    if(present("_glad_dare_obj_", environment(TP)))
    {
	write("There is already a line in the dust in this spot.\n"+
	  "You will have to wait for it to blow away.\n");
	allbb(" stares coldly at the line in the dust.");
	return 1;
    }

    (lineindust = clone_object(PSION_OBJ+"gdareobj"))->move(ENV(TP), 1);
    lineindust->set_gdrawer(TP);

    if (sizeof(oblist = parse_this(str, "%l")))
    {
	targetbb(" traces a line in the ground before you and "+
	  "dares you to cross it.", oblist);
	actor("You trace a line on the ground in front of you "+
	  "and dare",oblist," to cross it.");
	all2actbb(" traces a line on the ground before " + HIMHER +
	  " and dares", oblist," to step across it.");
	return 1;
    }

    write("You trace a line on the ground in front of you and "+
      "dare anyone to cross it.\n");
    allbb(" traces a line on the ground before " + HIMHER +
      " and dares anyone to cross it.");
    return 1;
}

int
gdeclare(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("Suddenly you snap back in time to Kalak's slave pits and " +
	  "hear yourself screaming the words your trainer burned into " +
	  "your mind:\n\"THE MOST RUTHLESS WILL ALWAYS WIN THE DAY!!\"\n");
	all("'s eyes glaze over with a sudden coldness as " + HESHE +
	  " screams:\n\"THE MOST RUTHLESS WILL ALWAYS WIN THE DAY!!\"");
	return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[at] [to] %l")))
    {
	NF("You'll only make yourself hoarse.\n");
	return 0;
    }

    actor("Suddenly you snap back in time to Kalak's slave pits and " +
      "hear yourself screaming at", oblist, " the words your trainer burned into " +
      "your mind:\n\"THE MOST RUTHLESS WILL ALWAYS WIN THE DAY!!\"");

    target("'s eyes glaze over with a sudden coldness as " + HESHE +
      " screams:\n\"THE MOST RUTHLESS WILL ALWAYS WIN THE DAY!!\" at you.", oblist);

    all2act("'s eyes glaze over with a sudden coldness as " + HESHE +
      " screams:\n\"THE MOST RUTHLESS WILL ALWAYS WIN THE DAY!!\" at", oblist);
    return 1;
}

int
gdefy(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("Defiantly you spit out: 'There can be only one!'\n"+
	  "You hear lightning strike somewhere far away.\n");
	all(" stretches to " + HISHER + " full height and defiantly "+
	  "growls: 'There can be only one!'\n"+
	  "You are sure you hear a crackle of energy nearby.");
	return 1;
    }

    if(!sizeof(oblist = parse_this(str, "%l")))
    {
	NF("Defy anyone in particular?\n");
	return 0;
    }

    target(" stands toe to toe with you in utter defiance.", oblist);
    actor("You stand toe to toe with", oblist, " in utter defiance.");
    all2actbb(" stands toe to toe with", oblist, " in utter defiance.");
    return 1;
}

int
gdust(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You shake more Athasian dust from your boots.\n");
	allbb(" shakes more Athasian dust from " + HISHER + " boots.");
	return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[at] / [on] %l")))
    {
	NF("You decide to save your limited supply of dust.\n");
	return 0;
    }

    targetbb(" shakes dust from "+HISHER+" boots all over your feet!",
      oblist);
    actor("You shake the dust of Athas all over the feet of",oblist);
    all2actbb(" shakes dust from "+HISHER+" boots all over the feet of",
      oblist);
    return 1;
}

int
geye(string str)
{
    object *oblist;

    if(!strlen(str))
    {
	write("You roll your eyes up into your head so that only "+
	  "the whites are visible.\n");
	allbb(" rolls his eyes up into "+HISHER+" head, so that only "+
	  "the whites are visible.");
	return 1;
    }

    if(!sizeof(oblist = parse_this(str, "[up] %l")))
    {
	NF("Eye up whom?\n");
	return 0;
    }

    if(sizeof(oblist) == 1)
    {

	targetbb(" eyes you up as a possible adversary.",oblist);
	actor("You eye up",oblist," as a possible adversary.");
	all2actbb(" eyes up",oblist," as a possible adversary.");

	TP->command("$compare stats with " + OB_NAME(oblist[0]));

	return 1;
    }

    targetbb(" eyes you up as a possible adversary.", oblist);
    actor("You eye up", oblist," as a possible adversary.");
    all2actbb(" eyes up", oblist," as a possible adversary.");
    return 1;
}

int
ggloat(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You gloat over your many victories in battle.\n");
	all(" gloats over "+HISHER+" many victories in battle.");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");
    if (!sizeof(oblist))
    {
	notify_fail("Gloat at who?\n");
	return 0;
    }
    actor("You gloat over your many victories against", oblist); 

    target(" cruelly gloats over "+HISHER+" many victories against you.", oblist);

    all2act(" cruelly gloats over "+HISHER+" many victories against", oblist);
    return 1;
}

int
ghear(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You close your eyes and listen pleasantly "+
	  "to your favorite sound: Death.\n");
	allbb(" closes "+HISHER+" eyes and gets a pleasant smile as "+
	  HESHE+" quietly listens to the glorious sounds of death.");
	return 1;
    }

    if(!sizeof(oblist = parse_this(str, "[to] %l")))
    {
	NF("You seem to hear a distant voice, urging you into battle.\n");
	return 0;
    }

    targetbb(" stares at you ominously. " + HESHE + " seems to listening " +
      "to something you aren't aware of.", oblist);
    actor("As you regard", oblist," you can hear a voice in your head, " +
      "urging you to attack.  It is the voice of Kalak, master of "+
      "both the Gladiators and the city-state of Tyr.");
    all2actbb(" seems to hear something and starts staring strangely at",
      oblist, "\nYou listen but hear nothing.");
    return 1;

}

int
glaugh(string str)
{
    object *oblist;

    if(!strlen(str))
    {
	write("You roll your head back and roar with laughter.\n");
	all(" rolls "+HISHER+" head back and roars with laughter.");
	return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[at] %l")))
    {
	NF("Laugh at whom?\n");
	return 0;
    }

    target(" rolls " + HISHER + " head back and roars with laughter at you.",
      oblist);
    actor("You roar with laughter at the pathetic", oblist);
    all2act(" rolls "+HISHER+" head back and roars with laughter at", oblist);
    return 1;
}

int
glook(string str)
{
    object *oblist;
    string glookstr;

    if(!strlen(str))
    {
	write("You make a quick scan of the area, searching for "+
	  "your next opponent.\n");
	allbb(" makes a quick scan of the area, searching for "+
	  HISHER + " next opponent.");
	return 1;
    }

    if(!sizeof(oblist = parse_this(str, "[at] %l")))
    {
	NF("Look at who with plans of dismemberment?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
	glookstr = "them";
    else
	glookstr = (oblist[0]->query_objective());

    targetbb(" looks at you as " + HESHE + " plans for your dismemberment.",
      oblist);
    actor("You look at",oblist," as you prepare to dismember "+glookstr+".");
    all2actbb(" looks at", oblist, ", seeming to plan to dismember " +
      glookstr + ".");
    return 1;
}

int
ghowl(string str)
{
    object footrest, *oblist;
    if(!strlen(str))
    {
	if(!(footrest=present("corpse",E(TP))))
	{
	    write("You howl 'FOR THE GLORY OF KALAK!'\n");
	    allbb(" howls "+HISHER+" warcry, 'FOR THE GLORY OF KALAK!'");
	    return 1;
	}

	write("You put your foot on the corpse and " +
	  "let loose a terrifying howl of victory.\n");
	allbb(" puts " + HISHER + " right foot upon the corpse" +
	  ", letting out a fierce howl of victory.");
	return 1;
    }

    if(!sizeof(oblist = parse_this(str, "[at] %l")))
    {
	NF("Howl a warcry at whom?\n");
	return 0;
    }

    target(" howls at you with "+HISHER+" earshattering warcry: 'FOR "+
      "THE GLORY OF KALAK!'\nYou move back a few steps.", oblist);
    actor("You howl 'FOR THE GLORY OF KALAK' at", oblist);
    all2act(" howls "+HISHER+" warcry, 'For the glory of Kalak!', at",
      oblist);
    return 1;
}

int
grage(string str)
{
    object *oblist;

    if(!strlen(str))
    {
	write("Unable to hold it back you explode with rage.\n");
	allbb(" shakes violently as "+HESHE+" is filled with pure rage.");
	return 1;
    }

    if(!sizeof(oblist = parse_this(str, "[at] %l")))
    {
	NF("Rage at whom?\n");
	return 0;
    }

    targetbb(" looks at you with absolute rage on "+HISHER+" face.",oblist);
    actor("You look with rage at", oblist);
    all2actbb(" looks with rage at", oblist);
    return 1;
}

int
groar(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You roar with the fury of the Athasian desert.\n");
	all(" roars with the fury of the Athasian desert.");
	return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[at] %l")))
    {
	NF("You'll only make yourself hoarse.\n");
	return 0;
    }

    target(" lets out a roar like an Athasian Nightmare Beast.\n"+
      "You are filled with mindless terror.", oblist);
    actor("You roar like an Athasian Nightmare Beast at", oblist);
    all2act(" roars like an Athasian Nightmare Beast at", oblist);
    return 1;
}

int
gsalute(string str)
{
    object *oblist;
    string salstra, salstro;

    if (!strlen(str))
    {
	write("You salute King Kalak of Tyr as a powerful (albeit "+
	  "ruthless, unforgiving, and cruel) master.\n");
	all(" salutes King Kalak of Tyr, known for his cruel and "+
	  "ruthless nature, as a powerful master.");
	return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[to] / [at] %l")))
    {
	NF("Salute whom?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	salstra = "";
	salstro = "opponents";
    }
    else
    {
	salstra = "a ";
	salstro = "opponent";
    }

    targetbb(" salutes you as a brave and worthy opponent.", oblist);
    actor("You salute", oblist, " as " + salstra + "brave and worthy " +
      salstro + ".");
    all2actbb(" salutes", oblist, " as " + salstra + "brave and worthy " + 
      salstro + ".");
    return 1;
}

int
gscratch(string str)
{
    object blade;

    if(!strlen(str))
    {
	write("As you scratch your scars you recall every battle in "+
	  "which you were wounded.\n");
	allbb(" scratches "+HISHER+" scars with a sigh, seeming to "+
	  "recall how "+HESHE+" received each wound.");
	return 1;
    }

    if(!(blade=thing_in_inventory(str)))
    {
	NF("You don't seem to have such a thing.\n");
	return 0;
    }

    if(!is_cutter(blade))
    {
	NF("There isn't a blade on that to run your finger on.\n");
	return 0;
    }

    write("You run your finger along the blade of your "+(blade->short())+
      ". The scratching sensation makes you feel very alert.\n");
    allbb(" fingers the blade of "+HISHER+" "+(blade->short())+
      " thoughtfully. It seems to help "+HIMHER+" focus.");
    return 1;
}

int
gshake(string str)
{
    object *oblist;
    string shakestr;

    if (!strlen(str))
    {
	write("You shake your hands, making the blood of your last "+
	  "kill splatter all over everything.\n");
	allbb(" shakes "+HISHER+" hands and splatters the blood from "+
	  HISHER + " last kill all over everything.");
	return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[hands] [with] %l")))
    {
	NF("You choose not to waste the blood that coats your hands.\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
	shakestr = "them";
    else
	shakestr = HIM_HER(oblist[0]);

    actor("As you shake hands with", oblist, ", you drip blood from " +
      "your last kill on " + shakestr + ".");
    all2actbb(" shakes hands with", oblist, ", dripping blood from " +
      HISHER + " last kill on " + shakestr + ".");
    target(" shakes your hand, dripping blood from "+HISHER+" last "+
      "kill onto you.", oblist);
    return 1;
}


int
gsharpen(string str)
{
    object blade;

    if(!strlen(str))
    {
	write("You perform a sequence of ritual combat moves, designed "+
	  "to sharpen your martial skills to a keen edge and to "+
	  "impress the arena crowds.\n");
	allbb(" begins a sequence of ritual combat moves: The fluid "+
	  "motions are almost hyptonic, and truly demonstrate "+
	  HISHER+" mastery of the arts of battle.");
	return 1;
    }

    if(!(blade=thing_in_inventory(str)))
    {
	NF("You don't seem to have such a thing.\n");
	return 0;
    }

    if(!is_cutter(blade))
    {
	NF("It wouldn't be worth the effort to sharpen that.\n");
	return 0;
    }

    write("You sit down and begin to slowly run the "+(blade->short())+
      " along a rough stone, attempting to hone its edge.\n");
    allbb(" sits down and begins to slowly draw the "+(blade->short())+
      "along a rough stone. Soon the weapon's edge glints in the "+
      "the light with renewed vigor.");
    return 1;
}

int
gshave(string str)
{
    object blade;
    string shaver, shaved, shavedp;

    shaver  = str;

    if ((TP->query_gender()) == G_FEMALE)
    {
	shaved  = "legs";
	shavedp = "they need";
    }
    else
    {
	shaved  = "chin";
	shavedp = "it needs";
    }

    if(!strlen(shaver))
    {
	write("You scratch your "+shaved+" thoughtfully, "+
	  "wondering if "+shavedp+" a shave.\n");
	allbb(" scratches "+HISHER+" "+shaved+" thoughtfully.");
	return 1;
    }

    if (extract(shaver, 0, 4) == "with ") (shaver=extract(shaver, 5));
    if (extract(shaver, 0, 3) == "the ") (shaver=extract(shaver, 4));

    if(!(blade=thing_in_inventory(shaver)))
    {
	NF("You don't seem to have that cutting impliment.\n");
	return 0;
    }

    if(!is_cutter(blade))
    {
	NF("You don't feel that will be good for shaving.\n");
	return 0;
    }

    write("You skillfully shave your "+shaved+" with the "+(blade->short())+
      " astounding those nearby with your skill.\n");
    allbb(" skillfully shaves " + HISHER + " " + shaved + " with " + 
      HISHER + " " + (blade->short()) + ". You marvel at how "+
      HESHE + " avoids cutting "+HIMHER+"self.");
    return 1;
}

int
gsneer(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You sneer contemptuously at the inferior warriors around you.\n");
	all(" sneers contemptuously at the inferior warriors around "+HIMHER+".");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");
    if (!sizeof(oblist))
    {
	notify_fail("Sneer at who?\n");
	return 0;
    }
    actor("You sneer contemptuously at", oblist, " for being such " +
      (sizeof(oblist) > 1 ? "inferior warriors." : "an inferior warrior.")); 

    target(" sneers contemptuously at you for being such an inferior warrior.", 
      oblist);

    all2act(" sneers contemptuously at", oblist, " for being such " +
      (sizeof(oblist) > 1 ? "inferior warriors." : "an inferior warrior."));
    return 1;
}

int
gspin(string str)
{
    object blade;

    if(!strlen(str))
    {
	write("You spin around with a crowd pleasing combat move.\n");
	allbb(" spins around in a display of acrobatics that no doubt "+
	  "would leave an arena audience talking about "+HISHER+" "+
	  "abilities for weeks; if not months.");
	return 1;
    }

    if(!(blade=thing_in_inventory(str)))
    {
	NF("You don't seem to have such a thing.\n");
	return 0;
    }

    if(!is_cutter(blade))
    {
	NF("You doubt you can spin that very impressively.\n");
	return 0;
    }

    write("With obvious ease you spin your "+(blade->short())+
      " around in a deadly combat arc.\n");
    allbb(" spins "+HISHER+" "+(blade->short())+" around "+HIMHER+
      "self with terrifying speed and skill, obviously amused by "+
      "your awed reaction.");
    return 1;
}

int
gspit(string str)
{
    object *oblist;

    if(!strlen(str))
    {
	write("You spit out mud from the dust of Athas.\n");
	allbb(" spits out mud from the dust of Athas.");
	return 1;
    }

    if(!sizeof(oblist = parse_this(str, "[at] %l")))
    {
	NF("The mud of Athas clings to the roof of your mouth.\n");
	return 0;
    }

    targetbb(" spits a clump of saliva coated mud at you!", oblist);
    actor("You spit the mud of Athas at", oblist);
    all2actbb(" spits saliva coated mud at", oblist);
    return 1;
}

int
gstance(string str)
{
    object *oblist;

    if(!strlen(str))
    {
	write("You assume a professional stance.\n");
	allbb(" assumes a professional stance.");
	return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[before] %l")))
    {
	NF("Is it wise to just run around posing to just anybody?\n");
	return 0;
    }

    targetbb(" assumes a professional stance in front of you.", oblist);
    actor("You assume a professional stance in front of", oblist);
    all2actbb(" assumes a professional stance in front of",oblist);
    return 1;
}

int
gthreaten(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("A threatening look flashes across your face.\n");
	all(" gets an extremely threatening look on "+HISHER+" face.");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
    {
	notify_fail("Threaten who?\n");
	return 0;
    }
    actor("A terrible look of anger flashes across your face as you " +
      "threaten to kill", oblist); 

    target("'s cold eyes pierce your heart as " +HESHE+ " threatens to kill you. " +
      "\nYou are certain " + HESHE + " means what " + HESHE + " says.", oblist);

    all2act("'s face hardens with a terrible look of anger as " + HESHE + 
      " threatens to kill", oblist);
    return 1;
}

int
gtooth(string str)
{
    object *oblist;
    string headp, toothp;

    if(!strlen(str))
    {
	write("You spit out one of your broken teeth.\n");
	allbb(" spits out a broken tooth.");
	return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[at] %l")))
    {
	NF("Hey, you could poke somebodies eye out with one of those!\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	headp = "heads";
	toothp = "some broken teeth";
    }
    else
    {
	headp = "head";
	toothp = "a broken tooth";
    }

    targetbb(" spits out " + toothp + ", hitting you in the head!", oblist);
    actor("You spit out " + toothp + " at the " + headp + " of", oblist);
    all2actbb(" spits out " + toothp + " at the " + headp + " of",oblist);
    return 1;
}


/* ******************* berserk *************************************** */
int
berserk()
{
    object glad = TP;
    if(!(glad->query_skill(SS_BERSERK)))
    {
	NF("Berserk is a skill, not just something you do.\n");
	return 0;
    }

    if (glad->query_prop(GLAD_I_IS_BERSERK) == 1)
	write("You are foaming at the mouth as it is.\n");
    else if (((glad->query_base_stat(SS_CON))/5) > (glad->query_fatigue()))
	write("You are too exhausted to go berserk.\n");
    else
    {
	glad->add_prop(GLAD_I_IS_BERSERK, 1);
	set_alarm(5.0, 0.0, &do_berserk(glad));
	glad->catch_tell("Your breathing becomes heavier.\n");
	say(QCTNAME(glad)+" breaks out in a sweat as "+HIS_HER(glad)+
	  " breathing becomes heavier.\n", glad);
    }  
    return 1;
}

void
do_berserk(object ob)
{
    int str, dis, con, skill, time, old_hp, old_maxhp, new_hp,
    max, new_maxhp;

    if (!objectp(ob)) return;
    skill = ob->query_skill(SS_BERSERK);
    time = 25 + skill/4;  /* between 25 and 50 seconds */
    max = 10 + ob->query_base_stat(SS_STR) / 10 - 
    (ob->query_stat(SS_STR) - ob->query_base_stat(SS_STR));
    str = MIN(ob->query_base_stat(SS_STR) / 7, max);
    max = 10 + ob->query_base_stat(SS_DIS) / 10 - 
    (ob->query_stat(SS_DIS) - ob->query_base_stat(SS_DIS));
    dis = MIN(ob->query_base_stat(SS_DIS) / 7, max);
    /* con bonus is skill dependant */  
    con = ob->query_base_stat(SS_CON) * (5 + skill/ 10) / 100;

    /* let the mudlib take care of str and dis */
    ob->add_tmp_stat(SS_STR, str, time/20);
    ob->add_tmp_stat(SS_DIS, dis, time/20);

    old_maxhp = ob->query_max_hp();
    old_hp = ob->query_hp();
    ob->set_stat_extra(SS_CON,con+ob->query_stat_extra(SS_CON));
    new_maxhp = ob->query_max_hp();
    new_hp = new_maxhp * old_hp / old_maxhp;
    ob->heal_hp(new_hp - old_hp);

    set_alarm(itof(time), 0.0, &expire_berserk(ob, con));
    ob->catch_tell("You start slavering at the mouth.\n");
    say(QCTNAME(ob) + " works "+ob->query_objective()+"self"+
      " into a wild battle rage.\n", ob);
}

void
expire_berserk(object ob, int con)
{
    int burnout, old_hp, old_maxhp, new_hp, new_maxhp;

    if (!objectp(ob)) return;
    old_maxhp = ob->query_max_hp();
    old_hp = ob->query_hp();
    ob->set_stat_extra(SS_CON,ob->query_stat_extra(SS_CON)-con);
    new_maxhp = ob->query_max_hp();
    new_hp = new_maxhp * old_hp / old_maxhp;
    ob->heal_hp(new_hp - old_hp);

    burnout = ((ob->query_base_stat(SS_CON))/6);
    if (burnout > (ob->query_fatigue())) (ob->set_fatigue(1));

    else (ob->add_fatigue(-burnout));

    set_alarm(itof(MAX(10, 25 - ob->query_skill(SS_BERSERK) / 5)), 0.0,
      &allow_berserk(ob));
    tell_object(ob, "You begin to calm down and return to a normal frame "+
      "of mind.\n");
    say(QCTNAME(ob) + " seems to have returned to a normal frame of "+
      "mind.\n");
}

void
allow_berserk(object ob) 
{ 
    if (!objectp(ob)) return;
    tell_object(ob, "\nYou can now enter a berserked state again.\n\n");
    ob->remove_prop(GLAD_I_IS_BERSERK);
}


/* ******************** brothers (list_members) ******************** */
int 
list_members()
{
    string name, title, str1, str2, list;
    int i, cnt = 0;
    object *glads;

    glads = filter(users(), "is_glad", this_object());
    glads = sort_array(filter(glads, not @ &->query_wiz_level()),
      "alphabetize", this_object());

    list = "Rumours hold that the following Gladiators are " +
    "on the prowl:\n\n";

    for (i = 0; i < sizeof(glads); i++)
    {
	str2 = "";

	if ((glads[i]->query_invis()) ||
	  (extract(glads[i]->query_name(), -2) == "jr"))
	    continue;

	if (!(name = capitalize(glads[i]->query_real_name())))
	    name = "";

	/*
		if (!(title = glads[i]->query_title()))
		    title = "";
	 */
	if (!(title = glads[i]->query_guild_title_occ()))
	    title = "";

	if (glads[i]->query_guild_family_name() &&
	  glads[i]->query_guild_title_race())
	{
	    title = glads[i]->query_guild_title_race() +", the "+ title;
	}
	else
	{
	    title = "the "+ title;
	}

	if (glads[i]->query_invis() && IS_WIZ(TP))
	    name = "(" + name + ")";

	str1 = name + " " + title;

	if (IS_WIZ(TP))
	{
	    str2 = sprintf("(%3s)", (IS_WIZ(glads[i]) ? "wiz" :
		"" + glads[i]->query_average()));
	}

	cnt++;
	list += sprintf("- %=-68s %-5s\n", str1, str2);
    }

    list += "=====================================================" +
    "======================\n";
    list += "Total number of active Gladiators is " + cnt + ".\n\n";

    if (FCHAR(query_verb()) == "m")
    {
	TP->more(list);
    }
    else
    {
	write(list);
    }

    return 1;
}

int alphabetize(object a, object b)
{
    string aname = a->query_name();
    string bname = b->query_name();

    return (aname < bname ? -1 : (aname == bname ? 0 : 1));
}

/* ******************* charge ***************************************** */
string
c_can_attack(object attacker, object target)
{
    string pnshname = attacker->query_real_name();
    if (!target || !living(target) || !present(target, ENV(attacker)))
	return "Charge whom?\n";

    if (attacker->query_prop(LIVE_I_ATTACK_DELAY))
    {
	return "You are too stunned to execute the charge.\n";
    }


    if (target->query_prop(OBJ_M_NO_ATTACK))
    {
	if (stringp(target->query_prop(OBJ_M_NO_ATTACK)))
	    return (target->query_prop(OBJ_M_NO_ATTACK));
	return "You detect a presence protecting the intended victim.\n";
    }

    if (environment(target) && environment(target)->query_prop(ROOM_M_NO_ATTACK))
    {
	if (stringp(E(target)->query_prop(ROOM_M_NO_ATTACK)))
	    return ((E(target)->query_prop(ROOM_M_NO_ATTACK))+".\n");
	return "You detect a magical peace spell on the room.\n";
    }

    if ((!attacker->query_npc()) && (attacker->query_met(target)) &&
      (!(attacker==(target->query_attack()))) &&
      (attacker->query_prop(LIVE_O_LAST_KILL) != target))
    {
	attacker->catch_msg("Attack " + QTNAME(target) +
	  "?!? Please confirm by trying again.\n");
	attacker->add_prop(LIVE_O_LAST_KILL, target);
	return "";
    }

    if (!F_DARE_ATTACK(attacker, target)) return "You don't dare attack.\n";

    if (CHECK_PUNISHMENT(EXPEL, pnshname))
	return "By Kalak's decree a gladiator expelled by the "
	+"Overseers may not charge.\n";
}

int
charge(string str)
{
    object ob, *obj;
    object charger = TP;
    string how;

    /* Does attacker have the skill? */
    if (!(charger->query_skill(SS_CHARGE)))
    {
	NF("First you should learn how.\n");
	return 0;
    }

    /* Is the attacker already busy? */
    if ((charger->query_prop(GLAD_I_IS_CHARGE)))
    {
	if ((charger->query_prop(GLAD_I_IS_CHARGE))==1)
	    NF("You are already preparing such an attack.\n");
	else NF("It seems you can't summon the energy to do that now.\n");
	return 0;
    }

    /* What are we attacking anyway? */
    if (strlen(str))
    {
	if (!sizeof(obj = parse_this(str, "[at] / [into] [the] %l")))
	{
	    NF("Choose a more appropriate target.\n");
	    return 0;
	}
	ob = obj [0];
    }
    else if (!(ob = charger->query_attack()))
    {
	NF("But you aren't in battle with anyone!\n");
	return 0;
    }

    /* Are we even allowed to attack it? */
    if (stringp(how = c_can_attack(charger, ob)))
    {
	NF(how);
	return 0;
    }

    /* Hurray! Lets set up the alarms to begin and end charge. */
    charger->catch_tell("You prepare to execute the lethal attack.\n");
    set_alarm(itof(1 + random(5)), 0.0, &do_charge(ob, charger));

    charger->add_prop(GLAD_I_IS_CHARGE, 1);

    /* Initiate battle with the target */
    if (!(ob==(charger->query_attack()))) { ob->attacked_by(charger); }
    charger->attack_object(ob);

    return 1;
}

void
do_charge(object target, object attacker)
{
    int hitsuc, hurt, prop;
    string how, chargestr;
    object chargeob;

    if (!objectp(attacker))
	return;

    chargeob = present("_glad_charge_ob_", attacker);

    set_alarm(itof(MIN(89, (125 - (attacker->query_skill(SS_CHARGE))))),
      0.0, &allow_charge(attacker));

    if(!(chargeob)) (chargestr="charge");
    else (chargestr=(chargeob->return_charge_desc()));

    /* Has there been a seperation before the charge occured? */
    if ((attacker->query_prop(GLAD_I_IS_CHARGE))==2) return;

    if (present(target, environment(attacker)) &&
      target != attacker->query_attack())
    {
	target = attacker->query_attack();
    }

    /* Has target become invalid somehow? */
    if (stringp(c_can_attack(attacker, target)))
    {
	attacker->catch_tell("You decide to abandon your "+chargestr+".\n");
	return;
    }

    /* Perform the actual collision! */
    attacker->add_prop(GLAD_I_IS_CHARGE, 2);
    if ((hitsuc = QEXC(attacker)->cb_tohit(-1, 50, target)) > 0)
	hurt = target->hit_me(2 * (F_PENMOD(maxout(STR(attacker)) / 5 +
	      maxout(CON(attacker)) / 5, attacker->query_skill(SS_CHARGE)) +
	    15), W_BLUDGEON, attacker, -1)[0];
    else
	hurt = target->hit_me(hitsuc, 0, attacker, -1)[0];

    if (attacker->query_fatigue() > 2)
	attacker->add_fatigue(-3);
    else
    {
	attacker->set_fatigue(0);
	attacker->reduce_hit_points(10);
	attacker->catch_tell("The strain of the attack drains you.\n");
    }

    if (hurt >= 0) 
    {
	attacker->add_panic(- hurt / 5);
	if (target->query_hp() > 0)
	{
	    if (hurt > 75)
		how = "on the verge of collapse";
	    else if (hurt > 50)
		how = "severely hurt";
	    else if (hurt > 30)
		how = "hurt";
	    else if (hurt > 15)
		how = "injured";
	    else if (hurt > 0)
		how = "dazed";
	    else how = "amazed by such a feeble attack";

	    attacker->catch_msg("You strike "+QTNAME(target)+" with "+
	      "your "+chargestr+".\n");
	    attacker->catch_msg(QCTNAME(target)+" looks "+ how +".\n");

	    target->catch_msg(QCTNAME(attacker) + " strikes you with "+
	      HIS_HER(attacker) + " "+chargestr+".\n");
	    target->catch_tell("You feel " + how + ".\n");

	    attacker->tell_watcher(QCTNAME(attacker)+" strikes " +
	      QTNAME(target) + " with " + HIS_HER(attacker) + " " +
	      chargestr+".\n", target);

	    return;
	}

	attacker->catch_msg("Bones break and blood splatters as you "+
	  "devastate " + QTNAME(target) + " with your "+chargestr+
	  ", throwing "+HIM_HER(target)+" to the ground in a "+
	  "bloody, lifeless heap.\n");

	attacker->tell_watcher(QCTNAME(target) + " lets out a final shriek in "+
	  "horrible agony and falls lifelessly to the "+
	  "ground at the feet of " + QTNAME(attacker) + ".\n", target);

	target->do_die(attacker);
	return;          
    }    

    attacker->add_panic(2);
    attacker->add_attack_delay(2, 0);

    attacker->catch_msg("You miss " + QTNAME(target) + " completely "+
      "with your "+chargestr+".\n");

    target->catch_msg(QCTNAME(attacker) + " flails wildly past you, "+
      "missing miserably with "+HIS_HER(attacker)+" "+chargestr+".\n");

    attacker->tell_watcher(QCTNAME(attacker) + " runs past " + QTNAME(target) +
      " in a botched attempt to hit "+HIM_HER(target) + ".\n", target);
}    

void
allow_charge(object ob) 
{ 
    ob->catch_tell("\nYou feel ready to crush your foe again.\n\n");
    ob->remove_prop(GLAD_I_IS_CHARGE);
}

/* *********************** help *************************** */
int help(string str)
{
    string *subjects, help_file;
    int i;

    setuid();
    seteuid(getuid());

    if (str == "gladiator")
    {
	if (!sizeof(subjects = filter(get_dir(PSION_HELP),
	      "filter_help_files", TO)))
	    return 0;

	str = "";

	for (i = 0; i < sizeof(subjects); i++)
	    str += explode(subjects[i], ".")[0] + "\n";

	write("Help is available to gladiators on these subjects:\n");
	write(sprintf("%-#60s\n", str));
	write("\nUse 'help gladiator <subject>' to access help " +
	  "files.\n\n");

	return 1;
    }

    if (sscanf(str, "gladiator %s", help_file) &&
      file_size(help_file = PSION_HELP + help_file + ".help") >= 0)
    {
	TP->more(read_file(help_file));
	return 1;
    }

    return 0;
}

int filter_help_files(string file)
{
    return (extract(file, -5) == ".help");
}
/* *********************** leave **************************** */
int
leave(string str)
{
    if (str != "gladiator guild") return 0;

    if (!TP->query_prop("_glad_i_leave"))
    {
	write("To reject the Guild of Gladiators is to die.\nIf you are "+
	  "sure type 'leave gladiator guild' again.\n");
	TP->add_prop("_glad_i_leave", 1);
	return 1;
    }
    TP->kick_out_psion();
    return 1;
}

/* ********************** Seecharge ********************** */
int
seecharge()
{
    object glad = TP;
    object chargeob = present("_glad_charge_ob_", glad);

    glad->catch_tell("Your charge text is currently set to:\n");
    if(!(chargeob)) glad->catch_tell("    charge\n");
    else glad->catch_tell("    "+(chargeob->return_charge_desc())+"\n");
    glad->catch_tell("To change it, if you are worthy, use the "+
      "'setcharge' command in the gladiators' meditation room.\n");
    return 1;
}

/* ********************** Updating ********************** */
/* 
 * Call update_nice to update the soul in a friendly way.
 * If there are any alarms present in the soul, it waits.
 */
static void
update_nice_retry(object caller, int n)
{
    int t, rep;
    float max = 0.0;
    mixed alarms;

    if (n > 10)
    {
	caller->catch_tell("Tried 10 times! Bailing out!");
	return;
    }

    alarms = get_all_alarms();
    if (sizeof(alarms) != 0)
    {
	for (t = 0; t < sizeof(alarms); t++)
	{
	    if (alarms[t][2] > max)
		max = alarms[t][2];
	    if (alarms[t][3] != 0.0)
		rep = 1;
	}
	caller->catch_tell("Longest alarm present: " + ftoa(max) + "\n");
	if (rep)
	{
	    caller->catch_tell("Repeating alarm! Bailing out!");
	    return;
	}
	set_alarm(max + 0.5, 0.0, &update_nice_retry(caller, n + 1));
	return;
    }
    caller->catch_tell("Updating the soul.\n");
    destruct();
}

void
update_nice()
{
    int t, rep;
    float max = 0.0;
    mixed alarms = get_all_alarms();

    if (sizeof(alarms) != 0)
    {
	for (t = 0; t < sizeof(alarms); t++)
	{
	    if (alarms[t][2] > max)
		max = alarms[t][2];
	    if (alarms[t][3] != 0.0)
		rep = 1;
	}
	write("Longest alarm present: " + ftoa(max) + "\n");
	if (rep)
	{
	    write("Repeating alarm! Bailing out!");
	    return;
	}
	set_alarm(max + 0.5, 0.0, &update_nice_retry(this_player(), 0));
	return;
    }
    write("Updating the soul.\n");
    destruct();
}

