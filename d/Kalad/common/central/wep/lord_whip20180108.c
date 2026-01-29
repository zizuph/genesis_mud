/*
 * Cotillion - 2006-04-20
 * - Fixed so ::did_hit is called
 * Petros - 2008-07-24
 * - Fixed so that watchers can see the combat messages
 * Gorboth - 2011-03-30
 * - Removed do_die() call ... no weapons that kill newbies please.
 */
inherit "/d/Kalad/std/weapon";
inherit "/cmd/std/command_driver";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
int special_on;

/* some definitions that controls the weapon */
/* min-time is the minimum time an add_attack_delay has */
/* extra-time is the random seed for added time to the delay */
/* hp-punishment is the hp taken away if the whip 'wins' control or */
/* refuses to be wielded. */

#define MIN_TIME       20
#define EXTRA_TIME     20
#define HP_PUNISHMENT 400

/* by Korat */
void create_weapon()
{
    ::create_weapon();

    set_name("whip");
    set_adj(({"blackened", "long"}));

    set_short("blackened whip");

    set_long((this_object())->my_long);

    add_item(({ "handle" }), "The handle looks like a spiral of twinned" +
	     " cords made of this black skin, laid upon itself in several"     +
	     " layers. In the butt end you see the tip of a shining white"     +
	     " ebony tooth that must be the core of the handle. When you touch"+
	     " the sharp tooth it penetrates your skin and draws a drop of"    +
	     " blood that disappears as suddenly as it came out. The tooth"    +
	     " seems to glow even whiter.\n");

    add_item(({"tip", "thorn", "thorns"}), "Along the tip of this whip"  +
	     " you see several small and sharp thorns that seems to be a part" +
	     " of the black leather. You wouldn't like to be torn up by"       +
	     " these.\n");

    set_hit(48);
    set_pen(40);
    set_wt(W_CLUB);
    set_dt(W_SLASH|W_IMPALE);
    set_wf(TO);
    add_prop(OBJ_I_VALUE ,       2800);
    add_prop(OBJ_I_WEIGHT,       7000);
    add_prop(OBJ_I_VOLUME,       5000);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));

    add_prop(MAGIC_AM_ID_INFO,({"When you study this whip of black scaled"+
				    " leather, you recognize a strong force of will flowing inside"   +
				    " it, emanating from a large tooth inside the thick handle. This" +
				    " force seems to control the movement of the whip as a dragon"    +
				    " would control its tail to hit as much as possible, and and make"+
				    " damage. With your understanding of such objects you know that"  +
				    " this whip is not a weapon wielded without a battle between"     +
				    " forces of minds that if won at all, will tire the wielder for"  +
				    " each battle the whip fights for you, and if lost might lead to" +
				    " death. A dangerous weapon indeed.\n", 55 }));

   
    add_prop(OBJ_S_WIZINFO,"This whip is made of the tail-skin of a small"+
	     " black dragon, thereby inheriting magical powers. This whip will"+
	     " hit any opponent very easily, but the damage is lower. If the"  +
	     " whip hits a head, it will add an attack-delay to the victim"    +
	     " for " + MIN_TIME + " + random(" + EXTRA_TIME + ") seconds. It"  +
	     " will also draw ((100 - ss_spellcraft()) + 100) / 3 of mana"     +
	     " (which means a max of 65 and a min of 33 mana-points) from the" +
	     " wielder since the whip will struggle for control. If the mana"  +
	     " reach 0, it draws " + HP_PUNISHMENT + " hp and unwields itself."+
	     " The player are given a short time to avoid this; they can"      +
	     " unwield it before the hp are taken away. For the special to"    +
	     " work, the player _must_ be in brave mode ('whimpy brave')."     +
	     " Several items are requied to have this whip wielded: DIS > 60," +
	     " SS_CLUB > 60 and Spellcraft > 10. If one fails in wielding, "   +
	     HP_PUNISHMENT + " hitpoints are taken.\n");
}

/* different long() if its wielded or not  */
   
string
  my_long()
{
    if (query_wielded() == this_player())
    {
        return "When you grip the handle of the black scaled leather of"  +
            " this whip you feel a force in contact with your mind, ready"+
            " to win any battle for you. It feels like burning inside"    +
            " your hand making you want to drop it down and be free of"   +
            " those black shadows the whip makes almost by itself as it"  +
            " dances in the air. A nauseating sound fills the air when"   +
            " you handle the whip; You think it must be the small thorns" +
            " that stick out all over the tip of it that sings in the"    +
            " air.\n";
    }

    return "When you touch the black scaled leather of this whip you"     +
        " feel a force touch your mind in warning, making you hesitate to"+
        " try to wield it. Coiled up with its lethal, thorny tip touching"+
        " the rough and thick handle it seems like a snake in full"       +
        " tension, ready to bite anyone daring to touch it. A mighty"     +
        " weapon in the hands of a brave warrior.\n";
}

/*
 * Check if the player can wield it or not.
 */

mixed
  wield(object what)
{
    write("You grip the handle of the whip, determined to wield it. A"   +
	  " strong force penetrates your mind and screams terrifyingly!"   +
	  " Everything is black...\n");

    say(QCTNAME(TP) + " grips the handle of a blackened whip. Suddenly"  +
        " the eyes of " + QCTNAME(TP) + " seems to grow black!\n");

    if ((TP->query_stat(SS_DIS) > 60) &&
        (TP->query_skill(SS_WEP_CLUB) > 60) &&
        (TP->query_skill(SS_SPELLCRAFT) > 10))
    {
        set_alarm(3.0, 0.0, "wield_success");
        return 0;
    }

    set_alarm(2.0, 0.0, "wield_fail");
    return "The whip curls itself together.\n";
}

wield_fail()   
{
    TP->heal_hp(-HP_PUNISHMENT);
    say("With a scream " + QCTNAME(TP) + " releases the grip on the whip!\n");
    write("Something whispers to you : Fool! Youuu think you are woooorthy "+
	  "to uuuuse me??!! In the pain you feel your strength wither slowly "+
	  "away as drained by a strong force in control of your mind. With a "+
	  "scream you release the grip on the handle.\n");
    if(TP->query_hp() <= 0)
    {
	write("Too late! With a horribly scream of victory the voice whispers "+
	      "to you: Ahhh...ssssoo now you will perishhhh. I do promise you that "+
	      "I will feeeeast on your soul!\n");
    /* Killing newbies is a bad policy. (Gorboth)
	TP->do_die(TO);
    */
    }
    write("Gasping for breath, you manage to force the black shadow away. You "+
	  "feel rather tired and less healthy.\n");
    TP -> command("puke");
}

wield_success(object ob)
{
    write("Then you concentrate all your powers and force the darkness away. "+
	  "With a horrible scream of defeat the whip coils itself out and settles "+
	  "itself in your hand..\n");
    say(QCTNAME(TP) + "'s eyes seems to clear up and return slowly to normal again.\n");
    TP->command("shiver");
    return 1;
}

mixed
  unwield(object what)
{
   
    /* This code is borrowed from Jeremiah. */
    /* It will stop any brawling attempt when the High lord */
    /* is wielding the whip. */
   
    if((E(TO)->id("urian")) && (E(TO)->query_hp() > 0))
    {
	tell_room(E(E(TO)), "The whip refuses to unwield ...", E(TO));
	return "The whip cannot be unwielded!";
    }
    write("You release the grip on the handle of the whip. You see it shivers along "+
	  "its length before it curls itself together with a will of its own.\n");
    return 0;
}

void
  init()
{
    ::init();
    add_action("slash","whipslash");
    add_action("rattle","whiprattle");
    add_action("snap","whipsnap");
}

/* This function will change the combat messages of the whip. */
/* It will also make a special attack if the whip makes damage */
/* on the head of the enemy. This special is add_attack_delay() */

public mixed did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    int which;
    float seconds;
    string mine_msg;
    string your_msg;
    string other_msg;
    object ishere;
    object head;
    object wielder = query_wielded();
    which=random(2);
   
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    /* Change the combat messages */
    switch(phurt)
    {
    case -1:
    case -2:
	if (which == 0)
	{
	    mine_msg="You slash wildly after "+QTNAME(enemy)+", but you "+
		"miss utterly.\n";
	    your_msg=QCTNAME(wielder)+" slash the "+short()+
		" wildly after you, but misses utterly.\n";
	    other_msg=QCTNAME(wielder)+" slash the "+short()+
		" at "+QTNAME(enemy)+", but misses utterly.\n";
	}
	else
	{
	    mine_msg = "The tip of the "+short()+" sings as it cuts through "+
		"empty air.\n";
	    your_msg = "The tip of "+QTNAME(wielder)+"'s "+short()+
		" sings as it cuts through empty air.\n";
	    other_msg = "The tip of "+QTNAME(wielder)+"'s "+short()+
		" sings as it cuts through empty air.\n";
	}
	break;
    case 0:
	if (which = 0)
	{
	    mine_msg = "When you slash down the "+short()+", "+QTNAME(enemy)+
		" sees it and deaftly sidesteps the lethal tip.\n";
	    your_msg = "When "+QTNAME(wielder)+" slashes down the "+short()+
		" you see it coming and sidestep it with ease.\n";
	    other_msg = "When "+QTNAME(wielder)+" slashes down the "+short()+
		", "+QTNAME(enemy)+" sees it coming and steps aside.\n";
	}
	else
	{
	    mine_msg = "With a scream you try to hit "+QTNAME(enemy)+
		" but the tip of the "+short()+" narrowly misses.\n";
	    your_msg = "With a scream "+QTNAME(wielder)+" tries to hit "+
		"your "+ hdesc + ", but narrowly misses.\n";
	    other_msg = "With a scream "+QTNAME(wielder)+" tries to hit "+
		QTNAME(enemy)+", but narrowly misses.\n";
	}
	break;
    case 1..5:
	if (which==0)
	{
	    mine_msg = "Cunningly you slash the "+short()+" sideways and "+
		"leave a small bleeding mark on "+QTNAME(enemy)+"'s "+
		hdesc+".\n";
	    your_msg = "Too fast for you to avoid it the "+short()+"'s tip "+
		"slashes towards you from the side, leaving a small "+
		"bleeding mark on your "+hdesc+".\n";
	    other_msg = QCTNAME(enemy)+" fail to avoid the "+short()+"'s tip "+
		"and receives a small bleeding mark on "+
		enemy->query_possessive()+" "+hdesc+".\n";
	}
	else
	{
	    mine_msg = "Your "+short()+" touches the flesh on "+QTNAME(enemy)+
		"'s "+hdesc+" and draws some blood.\n";
	    your_msg = QCTNAME(wielder)+"'s "+short()+" touches your "+hdesc+
		" and draws some blood.\n";
	    other_msg = QCTNAME(wielder)+"'s "+short()+" touches "+
		QTNAME(enemy)+"'s "+hdesc+" and draws some blood.\n";
	}
	break;
    case 6..10:
	mine_msg = "Your "+short()+" slices off a piece of flesh as it hits "+
	    QTNAME(enemy)+"'s "+hdesc+".\n";
	your_msg = QCTNAME(wielder)+"'s "+short()+" slices off a piece of "+
	    "flesh as it hits your "+hdesc+".\n";
	other_msg = QCTNAME(wielder)+"'s "+short()+" slices off a piece of "+
	    "flesh from "+QTNAME(enemy)+"'s "+hdesc+".\n";
	break;
    case 11..20:
	mine_msg = "You raise the "+short()+" above your head and send "+
	    "it hard down on "+QTNAME(enemy)+"'s "+hdesc+
	    ", inflicting a bleeding wound.\n";
	your_msg = QCTNAME(wielder)+" raises the "+short()+" above "+
	    wielder->query_pronoun()+" and then sends it hard down at your "+
	    hdesc+", leaving behind a bleeding wound.\n";
	other_msg = QCTNAME(wielder)+ " raises the "+short()+" above the "+
	    "head and sends it hard down on "+QTNAME(enemy)+"'s "+hdesc+
	    ", inflicting a bleeding wound.\n";
	break;
    case 21..40:
	mine_msg = "The "+short()+" rips into the "+hdesc+" of "+
	    QTNAME(enemy)+" and blood pours out.\n";
	your_msg = "The "+short()+" rips into your "+hdesc+
	    " and blood pours out.\n";
	other_msg = "The "+short()+" rips into the "+hdesc+" of "+
	    QTNAME(enemy)+" and blood pours out.\n";
	break;
    case 41..60:
	mine_msg = QCTNAME(enemy)+" screams as the "+short()+" tears into "+
	    enemy->query_possessive()+" "+hdesc+". You can see white bones "+
	    "through the inflicted wound.\n";
	your_msg = "You scream as the "+short()+" tears into your "+hdesc+
	    ", and penetrates down to your bones.\n";
	other_msg = QCTNAME(enemy)+" screams as the "+short()+" tears into "+
	    enemy->query_possessive()+" "+hdesc+". You can see white bones "+
	    "through the inflicted wound.\n";
	break;
    case 61..80:
	mine_msg = "With devastating effect you hurl the tip of the "+
	    short()+" down on "+QTNAME(enemy)+" and watch it dig into the "+
	    hdesc+", tearing loose flesh and bones on its way.\n";
	your_msg = "In shock you watch the tip of the "+short()+" dig into "+
	    "your "+hdesc+", tearing loose flesh and bones on its way.\n";
	other_msg = "With devastating effect "+QTNAME(wielder)+" hurls "+
	    "the tip of the "+short()+" down on "+QTNAME(enemy)+"'s "+
	    hdesc+", and watch it tear loose flesh and bones on its way.\n";
	break;
    case 81..90:
	mine_msg = "Your "+short()+" almost tore "+
	    "through the "+hdesc+" of "+QTNAME(enemy)+".\n";
	your_msg = "The "+short()+" almost tore right through "+
	    "your "+hdesc+".\n";
	other_msg = "The "+short()+" wielded by "+QTNAME(wielder)+
	    " almost tore through the "+hdesc+" of "+QTNAME(enemy)+".\n";
	break;
    default:
	mine_msg = "With an enormous force you massacre "+QTNAME(enemy)+".\n";
	your_msg = "With an enormous force "+QTNAME(wielder)+" massacres "+
	    "you.\n";
	other_msg = "With an enormous force "+QTNAME(wielder)+" massacres "+
	    QTNAME(enemy)+".\n";
      
	/* if the whip killed the enemy, the enemy is 'decaptivated' */
         
	if(enemy->query_hp() <= 0)
	{
	    mine_msg = mine_msg+"You decapitated "+QTNAME(enemy)+".\n"+
		"You hear a chilling voice scream in your head in joy.\n";
	    other_msg = other_msg+QCTNAME(wielder)+" decapitated "+
		QTNAME(enemy)+".\n";
	}
	else
	{
	    mine_msg=mine_msg+"A voice whispers in your head: Sooooon "+
		"we will feeeasst on "+enemy->query_possessive()+" sooouul!\n";
	    your_msg=your_msg+"A voice whispers in your head: Sooooon "+
		"I will feeeeasst on youuur sooouuul!\n";
	}
	break;
    }
    wielder->catch_msg(mine_msg);
    enemy->catch_msg(your_msg);
    wielder->tell_watcher(other_msg,enemy);
   
    /* the rest is a check if a special attack should be added. */
      
    if (hdesc=="head" && phurt >0)
    {
	if(wielder->query_whimpy()!=0)
	{
	    wielder->catch_msg("A voice from within your head "+
			       "whispers to you: I will not help cooowardssss!\n");
	}
	else
	{
	    if (enemy->query_hp()>0)
            {
		seconds = random(EXTRA_TIME)+MIN_TIME;
		enemy->add_attack_delay(seconds);
		enemy->catch_msg("When the "+short()+" touches your head, "+
				 "a terrible pain runs through your mind, filling your "+
				 "head with a penetrating blackness...\n");
		wielder->catch_msg("You feel a terrible force "+
				   "flow from the handle of the "+short()+". It vibrates through "+
				   "the black leather and seems to burst into "+QTNAME(enemy)+"'s head.\n");
		wielder->catch_msg("You feel your inner self being drained "+
				   "of power.\n");
		wielder->tell_watcher(QCTNAME(enemy)+" screams up in pain. "+
			     C(enemy->query_possessive())+" eyes seems "+
			     "to grow black.\n",enemy);
		enemy->command("scream");
		if (!(wielder->query_npc()))
		    set_alarm(0.0,0.0,"give_punishment",wielder);
	    }
	}
    }
    return 1;
}

/* this function punishes the wielder when a special is done. */
/* it draws mana until there is no mana left, and then */
/* draws hp, and unwields itself. */

void
  give_punishment(object who)
{
    int mana_left;
    int mana_draw;
    int spellcraft_skill;
    spellcraft_skill = who->query_skill(SS_SPELLCRAFT);
    mana_left = who->query_mana();
   
    /* the mana taken is max 65 and min 33 mana-points.
     *  This low penalty is here because the player _must_
     *  be 'wimpy brave' to use this special.
     */
   
    mana_draw = ((100-spellcraft_skill)+100)/3;
    if (mana_left>mana_draw)
	who->set_mana(mana_left-mana_draw);
    else
    {
	who->set_mana(0);
	who->catch_msg("A chilling voice, soaked of loathing and hatreded, "+
		       "penetrates your mind: Yoouur power over me has withered awayy! "+
		       "Nooow I shall feeeasst on yooouur sooouul!\n");
	who->catch_msg("You suddenly feel something penetrate your palm.\n");
	set_alarm(7.0,0.0,"do_take_hp", who);
	wielder->tell_watcher(QCTNAME(who)+" suddenly turns very pale, small drops "+
		     "of sweat runs down from the forehead. You shiver when you "+
		     "see that "+who->query_possessive()+
		     " eyes start to turn black.\n",who);
    }
}

/* the player has a small time to unwield the whip */
/* before the hp is taken. This punishment can then be */
/* avoided.              */

void
  do_take_hp(object who)
{
    if (TO->query_wielded())
    {
	who->heal_hp(-HP_PUNISHMENT);
	who->catch_msg("A terrible pain runs through your body as your "+
		       "lifeforce seems to trickle into the handle of the "+short()+
		       ".\n");
	if (who->query_hp() <= 0)
	{
	    who->catch_msg("Suddenly everything becomes black....\n");
	    who->do_die(TO);
	}
	who->catch_msg("As sudden as the black void came, it "+
		       "dissappears...and the voice in your mind fades away in dissapointment.\n");
	who->command("unwield "+short());
    }
}


/* An emote: Slash. started with 'whipslash' */

int
  slash(string str)
{
    object who;
    object *victims;
    if (!(TO->query_wielded()))
    {
	write("You must wield the whip first!\n");
	return 1;
    }
    if (!str)
    {
	write("Slash who?\n");
	return 1;
    }
    victims = parse_this(str,"%l");
    if (sizeof(victims)==0)
    {
	write("You look around, but find nobody to slash.\n");
	return 1;
    }
    if (sizeof(victims)>1)
    {
	write("Who do you want to slash? Be more precise!\n");
	return 1;
    }
    /* try to find the victim of the slash */
    who = victims[0];
    TP->catch_msg("You slash "+QTNAME(who)+" with your whip, leaving "+
		  "a bleeding scar on "+who->query_possessive()+" face!\n");
    TP->catch_msg("That person is marked for life!\n");
    who->catch_msg(QCTNAME(TP)+" lifts the whip above "+
		   TP->query_objective()+"self, and slashes it down on your face!\n");
    who->catch_msg("A long reddish scar is left behind from the vicious slash!\n");
    wielder->tell_watcher(QCTNAME(TP)+" lifts the whip above "+
		 TP->query_objective()+"self, and slashes it down on "+QTNAME(who)+
		 "'s face. A long reddish scar is left behind from the "+
		 "vicious slash!\n",who);
    return 1;
}

/* an emote: rattle. It is started with 'whiprattle' */

rattle() 
{
    if(!query_wielded(TO))
    {
	write("You must wield the whip first!\n");
	return 1;
    }
    write("You swing the whip around you in waveformed patterns, making "+
	  "the needles on the tip to hit each other.\n");
    write("The whip rattles dangerously!\n");
    say(QCTNAME(TP) + " starts to swing the whip around " + TP->query_objective() + 
	"self.\n");
    say("The whip rattles dangerously around you!\n");
    return 1;
}

/* an emote: Snap. This is started with 'whipsnap' */

snap() /* this one is borrowed from Antharanos' coding */
{
    if(!query_wielded(TO))
    {
	write("You must wield the whip first!\n");
	return 1;
    }
    write("You raise the whip above you and snap it down.\n");
    write("The whip goes CRACK!\n");
    say(QCTNAME(TP) + " raises the whip above " + TP->query_objective() + "self and snaps it down.\n");
    say("The whip goes CRACK!\n");
    return 1;
}

