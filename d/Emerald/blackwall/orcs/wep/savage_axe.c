/* Morognor, the orc captain's, axe.
   A rather deadly weapon, particular when wielded by a goblin,
   and the victim is an elf.
*/

#pragma strict_types
#pragma save_binary

inherit "/std/weapon.c";
inherit "/d/Emerald/blackwall/orcs/wep/pct_hurt.c"; //useful
inherit "/lib/keep"; //players can set the OBJ_M_NO_SELL property

#include "/sys/wa_types.h"
#include <formulas.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <cmdparse.h>

//global variable:
int can_unwield; //Can the user unwield the axe? 1 = yes
object testing; //used in testing only

/* VBFC for the runes which adorn the blade. Those who are highly 
   familiar with magic will get a vague clue as to their meaning.
*/
string
rune_descrip()
{
    string descrip; //the returned string

    descrip = "Fluid, rune-like inscriptions adorn both blade "+
	"and haft of the savage black axe. ";

    if (this_player()->query_skill(SS_SPELLCRAFT) > 50 + random(20))
    {
	descrip += " You identify the markings as sigils commonly "+
	    "employed in darkling artifice. You do not understand "+
	    "their exact purpose, though there can be little doubt "+
	    "that this weapon has been enchanted.\n";
    }

    else
    {
	descrip += " Their signifigance, if any, is lost on you.\n";
    }

    return descrip;
}

void create_weapon()
{
    set_name("axe");
    set_short("savage black axe");
    set_long("A rather large and heavy single-handed axe. Its "+
	     "broad, serrated-edged blade sits atop a handle of "+
	     "good length. The whole is cast of one piece of "+
	     "some perfectly black iron. Odd "+
	     "markings adorn both the blade and the haft. Inspite "+
	     "of its weight, the weapon naturally swings in graceful "+
	     "arcs.\n\nUpon close examination, you realize that it "+
	     "may be possible to 'axethreaten' someone with this weapon.\n");
    set_adj ("savage");
    add_adj ("black");
    add_adj ("iron");

    add_item(({"odd markings", "markings", "runes"}),
	     "@@rune_descrip@@");

    set_hit(36);
    set_pen(42);

    //Magic weapon, therefor :
    likely_dull = 3;
    likely_corr = 3;
    likely_break = 2;

    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_LEFT);
    add_prop(OBJ_I_WEIGHT, 12500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(34,38) + 400 + random(200));
    add_prop(OBJ_I_VOLUME, 4100);

    //Magic weapon, therefor tough and resistant:

    add_prop(OBJ_I_RES_FIRE, 50);
    add_prop(OBJ_I_RES_ACID, 40);
    add_prop(OBJ_I_RES_ELECTRICITY, 75);
    add_prop(OBJ_I_RES_COLD, 50);
 
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(MAGIC_AM_MAGIC,({60,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This weapon appears to have been "+
		                "the work of darkling artifice.\n",
				20, "Magical fire plays an important "+
				"role in the weapons enchantment.\n",
				30, "It was designed to be wielded "+
                                "by an orc, or goblin and not by an "+
				"elf!\n", 40, "This blade will set "+
				"elvish blood afire!!!\n", 65}));
			
   add_prop(OBJ_S_WIZINFO, "This weapon was forged by darklings for the "+
	    "express use of orcs or goblins in fighting elves. "+
	    "ordinarily a 36/42 weapon, it is 42/42 in the hands of "+
	    "goblin or orc. In addition to the usual attacks and damage, "+
	    "blows dealing more than 50 points of damage to an elf "+
	    "result in the elf suffering another 25 + random(50) points "+
	    "of fire damage, as his blood ignites! "+
	    "Oh, and its liable to slay any weak-willed elf foolish "+
	    "enough to attempt to wield it.\n");
 
   set_wf(this_object());
   set_keep(1);//this axe cannot be sold, by default
   
   can_unwield = 1;
}

/* This function is called when an elf has been consumed by the fire from
   the savage black axe. It changes the description of the
   the resulting corpse.

   Args: object room : the room in which the body lies
*/
void
consume_corpse(object room)
{
    object* corpses; // array of corpses in the room
    corpses = filter(all_inventory(room), &->id("corpse"));
    
    /* the freshly arrived corpse is almost certainly at the top of the
       rooms inventory, and therefor should be the first in the list,
       I am not sure any checks are necessary.
    */
    corpses[0]->set_short("smoldering remains");
    corpses[0]->set_long("The smoldering remains of some unfortunate "+
			 "person. Little is left: some blackened bones and "+
			 "a few hunks of still smoldering flesh. Closer "+
			 "examination allows you to deduce that the remains "+
			 "are probably those of an elf.\n");
    corpses[0]->add_adj("smoldering");

    //the remaining corpse 1/5 the original size
    corpses[0]->add_prop(OBJ_I_WEIGHT, corpses[0]->query_prop(OBJ_I_WEIGHT) /
				      5);
    corpses[0]->add_prop(OBJ_I_VOLUME, corpses[0]->query_prop(OBJ_I_VOLUME) /
				      5);
}  
       
/* Whenever an elf is struck sufficiently hard with the savage black
   axe, he or she takes a 75 penetration magical fire attack.
   This function deals with this and the messages that this effect
   generates.
*/
void
burn_elf(object victim, object wielder, string hdesc)
{
    int elfdamage, phurt;
    object victim_env;

//kick out of the function if the victim is no longer alive....
    if (!victim)
    {
	return;
    }

    elfdamage = (25 + random(50)) * ftoi(itof(100 - victim->
       query_magic_res(OBJ_I_RES_FIRE)) / 100.0);
		 
    victim_env = environment(victim);

    if (victim->query_race_name() == "half-elf")
    {
	elfdamage = elfdamage / 2;
    }

    victim->heal_hp(- elfdamage);  

    if (victim->query_hp() <= 0)
    {
	victim->catch_tell("An intense searing pain spreads from the "+
			 "the gaping wound in your " + hdesc +
			 "wound left by the savage black axe. Flames "+
			 "begin to leap from the wound as your blood "+
			 "catches fire!!!\nYou are gripped by an "+
			 "unearthly agony as the fire spreads "+
			 "throughout your body, incinerating you "+
			 "from the inside out!!!\n");
	tell_room(victim_env, "Smoke, then flames "+
		  "spout from the gaping wound in "+
		  QTNAME(victim) + "'s " + hdesc + "! You "+
		  "step back and watch the awesome spectacle "+
		  "as " + victim->query_pronoun() +  " spontaneously "+
		  "combusts!!\n", victim);

	victim->command("$scream");

	/* If a player dies as a result of a wound inflicted by another 
	   or NPC, we want to note that that living killed him. However,
	   if the player killed himself by attempting to wield this axe,
	   we will denote the axe as his killer:
	*/

	if (victim == wielder)
	{
	    can_unwield = 1; //Allows him to unwield the axe in death.
	    remove_prop(OBJ_M_NO_DROP);
	    victim->do_die(this_object());
	}
	
	else
	{
	    victim->do_die(wielder);
	}
	
	// modifiy the remains of the victim
	set_alarm(0.1, 0.0, &consume_corpse(victim_env));
    }

    phurt = pct_hurt(elfdamage, victim);

    switch (phurt)
    { 
        case 0..10:
	    victim->catch_tell("The wound on your " + hdesc + " burns "+
			       "acutely. Tiny wisps of black smoke issue "+
			       "briefly from it before the pain "+
			       "subsides.\n");
	    tell_room(victim_env, "Tiny wisps of black smoke briefly issue "+
		      "from the wound on " + QTNAME(victim) +
		      "'s " + hdesc + ".\n", victim);
	  
	    break;

        case 11..25:
	    victim->catch_tell("You grasp your " + hdesc + " in agony as "+
			     "flames briefly lick your flesh where it "+
			     "was opened by the savage black axe!!!\n");
	    tell_room(victim_env, QCTNAME(victim) + " grasps " +
		      victim->query_possessive() + " " + hdesc + 
		      " in agony as flames briefly lick " +
		      victim->query_possessive() + " flesh where "+
		      "it was opened by the savage black axe.\n",
		      victim);
	    break;
	    
        default:
	    victim->catch_tell("Flames erupt from your " + hdesc +
			       " as your elven blood ignites upon " +
			       "contact with the blade of the savage "+
			       "black axe!!!\n");
	    tell_room(victim_env, "Flames erupt from " + QTNAME(victim) + 
		      "'s " + hdesc + " as " +
		      victim->query_possessive() + " elven blood "+
		      "ignites upon contact with the blade of the "+
		      "savage black axe!\n", victim);		
	    victim->command("$scream");
    }
}
      
int
did_hit(int aid, string hdesc, int phurt,
        object victim, int dt, int phit, int dam)
{ 
    object wielder;

    wielder = environment(this_object());

    if (((victim->query_race_name() == "elf") ||
	 (victim->query_race_name() == "half-elf"))
	&& (dam > 50))
    {  
      	set_alarm(0.0, 0.0, &burn_elf(victim, wielder, hdesc));
    }

    return ::did_hit();
}
/* This function is called when an elf has been foolish enough to 
   wield the axe. He will keep hurting himself with the axe until he 
   succeeds at a task of difficulty 950 against his discipline. Weak
   elves will surely perish.
*/

void
attack_elf()
{    
    int selfdamage, phurt;
    string how, leg;

    if (!wielder) //The axe is not wielded for whatever reason, perhaps
	          //the wielder killed himself ;)
    {
	return;
    }

    if (wielder->resolve_task(960, ({TS_DIS})) > 0)
    {
	wielder->catch_msg("With an incredible effort of will, you "+
			   "manage to release your grip on the savage "+
			   "black axe.\n");
	can_unwield = 1;
	remove_prop(OBJ_M_NO_DROP);
	wielder->command("$drop savage black axe");
	return; //proceed no further
    }

    leg = "right";
    if (random(2))
    {
	leg = "left";
    }

    selfdamage = random(75) + random(75);
    wielder->heal_hp(- selfdamage);

    if (selfdamage > 50)
    {
	// Just did 50 damage with the axe, you know what that means :>
	set_alarm(0.0, 0.0, &burn_elf(wielder, wielder, leg + " leg"));
    }

    if (wielder->query_hp() < 0) // the wielder has slain himself!
    {
	wielder->catch_tell("With a brutal swing of the savage black axe, "+
			   "you sever your " + leg + " leg from your body\n!" +
			   "You fall to the ground, blood pouring from "+
			   "the open wound. Within seconds, the world "+
			   "around you has faded away into darkness...\n");
	tell_room(environment(wielder), "With a brutal swing of the savage "+
		  "black axe, " + QTNAME(wielder) + " severs "+
		  wielder->query_possessive() + " " + leg + " leg from "+
		  wielder->query_poessessive() + " body! Blood pours from "+
		  "the open wound, soaking the ground...\n", wielder,
		  this_object());

	can_unwield = 1; //Allow the wielder to unwield the axe in death.
	wielder->do_die(this_object()); //denote the axe as his killer
    }	
	
// The wielder didn't die, so:
    phurt = pct_hurt(selfdamage, wielder);

    how = "scratching it";
    if (phurt > 5) {how = "cutting it";}
    if (phurt > 20) {how =  "slicing it open";}
    if (phurt > 50) {how = "tearing it open";}
  
    wielder->catch_tell("You cannot control the axe!\nYou take a hard "+
			"swing at your " + leg + " leg, " + how + "!\n");
    tell_room(environment(wielder), capitalize(QTNAME(wielder)) + 
	      " takes a hard swing at " + wielder->query_possessive() + 
	      " " + leg + " leg with the savage black axe, " + how + "!\n",
	      wielder, this_object());

    // The wielder will chop at his legs again in three seconds!
    set_alarm(3.0, 0.0, attack_elf);
}

mixed
wield(object to)
{ 
    if (this_player()->query_race() == "goblin" || this_player()->
	query_race_name() == "orc") // second clause added
                                    // for its wielders benefit
    {
	this_object()->set_hit(42);
	this_player()->catch_tell("As your left hand tightens around the "+
			       "haft of the savage black axe, you "+
			       "suddenly feel strangely comfortable with "+
			       "this weapon. It is almost as if the weapon "+
			       "were crafted specifically for you.\n");
    }
    else
    {
	this_object()->set_hit(36);
    } 
 
    if (this_player()->query_race() == "elf")		    
    {
	can_unwield = 0; //poor elf, he may not unwield the axe!
	add_prop(OBJ_M_NO_DROP, "You are unable to let go of the axe!");
	write("As soon as you grip the savage black axe "+
	      "you realize that you have made a terrible "+
	      "mistake!\n");
	set_alarm(0.0, 0.0, attack_elf);
    }

 // We use the alarm to ensure that the wield() function is completed before
// updating.
    set_alarm(0.0, 0.0, &wielder->update_weapon(this_object()));
    return 0; // print the usual messages, and wield the weapon as normal.
}
	
/* This function is called when something tries to stop wielding
   the axe. Normally, this is not difficult. However, elves cannot unwield
   the axe except with tremendous force of will.
*/
mixed
unwield(object to)
{
    if (!can_unwield)
    { 
	return "You are unable to let go of the axe!\n";
    }

    //  wielder = 0; //needed, otherwise the weapon keeps track of the
                 //previous wielder
    return 0; //Unwield as normal.
}

    
/* Emote granted by the axe. */
int
do_threaten(string arg)
{
    mixed* oblist; //array containing the living the player wishes to
                   //threaten (ideally)

    if (! wielded) //the axe is not wielded
    {
	notify_fail("The savage black axe does not present a meaningful "+
		    "threat unless wielded.\n");
	return 0;
    }

    if (! arg)
    {
	// player threatens no one in particular
	write("You snarl savagely while waving your savage black axe "+
	      "around in a threatening manner.\n");
	say(QCTNAME(this_player()) + " snarls savagely while waving " +
	    this_player()->query_possessive() + " savage black axe "+
	    "around in a threatening manner.\n");
	return 1; //command succeeded
    }

    if ((! parse_command(arg, all_inventory(environment(this_player())),
			 "[the] %i", oblist))||
	!(sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0))))
      //[with] [the] "+
      //			"[savage] [black] [axe]", oblist))
    {
	notify_fail("Threaten whom?\n");
	return 0;
    }
    
    testing = oblist[0];
    oblist[0]->catch_msg(QCTNAME(wielder) + " makes a subtle gesture with "+
			 wielder->query_possessive() + " savage black axe "+
			 "implying that if you do not cooperate, " +
			 wielder->query_pronoun() + " will be more than "+
			 "happy to seperate your head from its shoulders.\n");

    this_player()->catch_msg("You make a subtle gesture towards " + 
			     QTNAME(oblist[0]) + " with your savage black axe "+
			     "implying that if " +  oblist[0]->query_pronoun() + 
			     " does not cooperate, you will be more "+
			     "than happy to seperate " + 
			     oblist[0]->query_possessive() + " head "+
			     "from " + oblist[0]->query_possessive() +
			     " shoulders.\n");

    say(QCTNAME(this_player()) + " makes a subtle gesture towards " +
	QTNAME(oblist[0]) + " with " + this_player()->query_possessive() +
	" savage black axe implying that if " + oblist[0]->
	query_pronoun() + " does not cooperate, " + this_player()->
	query_pronoun() + " will be more than happy to seperate " +
	oblist[0]->query_possessive() + " head from " + 
	oblist[0]->query_possessive() + " shoulders.\n", ({oblist[0], wielder}));

    return 1;
}

void
init()
{
    ::init();
    add_action(do_threaten, "axethreaten");
}







