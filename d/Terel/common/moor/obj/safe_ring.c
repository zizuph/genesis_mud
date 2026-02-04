// ~Terel/common/moors/obj/safe_ring   Ring of the Ancients  
// Created by Lilith Jan 2022.
//    Made as a treasure for the cottage safe. Intended to resemble 
//      something the Mystics might have worn, back in the day.
// Effects:  Helps block the sting effect of Benton's Wasp the Cleaver.
//
//    Hope to make it help players fight Terel's dragons later on.
//  Revisions:  Lilith Feb 2022: added magic id info and updated cloning
//                of the star through the glory function.

inherit "/std/armour";
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

#define TP this_player()
#define EN environment
#define TO this_object()

#define DRAGON_SLAYER  "_terel_i_am_dragon_slayer"
#define RUNES_REVEALED "_terel_ring_runes_revealed"

public void
create_armour()
{

    set_name("ring");
    add_name(({"_terel_dragon_ring", "_ring_of_the_ancients", 
	"ring of the ancients"}));
    set_adj("ancient");
    add_adj(({"gold", "signet"}));
    set_short("ancient gold signet ring");
    set_long(
      "This is an ancient signet ring, golden and luminous. The band "+
      "has arcane runes etched into it, their meaning lost to the "+
      "erosion of time. The signet is a raised seal, upon which "+
      "are seven stars, a winged serpent, and a few unfamiliar runes.\n");
    add_item("runes", "They are mostly mysterious and unknowable. "+
      "Perhaps if you <study runes> you will learn more.\n");
    add_item(({"signet", "seal"}), "There is a flat surface on the ring "+
      "with a raised seal upon it. The seal has seven stars, a serpent, "+
      "and some runes on it.\n");
    add_item(({"serpent", "winged serpent", "dragon"}), 
      "A dragon-like serpent has been etched into the seal in "+
      "what was once fine detail but is worn down by time. It loops "+
      "around on itself, forming a figure-eight.\n");   
    add_item(({"stars", "star", "seven stars"}), "The stars run in a "+
      "circle around the serpent.\n");
    set_at(A_ANY_FINGER);
    set_ac(20);    
    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_VALUE, 500);
    set_af(TO);   

    add_prop(MAGIC_AM_MAGIC,({ 40, "enchantment" }));
    add_prop(OBJ_S_WIZINFO, 
      "This ring is one fo the rings ofthe Ancients. "+
      "It helps protect the wearer from the special attack "+
      "of Benton's Wasp. Eventually it will provide "+
      "aid in killing the dragons of Terel.\n");
    add_prop(MAGIC_AM_ID_INFO, 
      ({"Ancient ring formed of ancient gold\n", 10,
	"Ancient magic from time untold.\n", 20,
	"To blunt the pain of the cannibal's sting\n", 40, 		  
	"One has only to wear this ring.\n", 45 }));


    setuid();
    seteuid(getuid());	

}


int
remove_runes(object obj)
{
    if (query_worn()->query_prop(RUNES_REVEALED))
	query_worn()->remove_prop(RUNES_REVEALED);
    return 1;
}

mixed
wear(object obj)
{
    write("You feel as though an ancient spirit looms over you as "+
      "you wear the "+ short() +".\nYour vision seems cast in golden "+
      "light for a long moment.\n");
    say(QCTNAME(TP) + " wears the " + short() + " and is surrounded "+
      "in a golden nimbus for a long moment.\n");
    return 1;
}

void
do_star()
{
    object star;
    tell_room(EN(TP), "A sparkling golden star appears over you, "+
      "casting forth rays of golden light, with beams of "+
      "glittering stardust!\n");
    // Not sure what the star will do... perhaps help with dragons?
    // It will destroy the ring, however.
    star = clone_object("/d/Terel/common/moor/obj/star");
    star->move(EN(TP));
    star->do_twinkle();  

}

int
do_glory(string str)
{
    if (!query_worn())
    {
	notify_fail("You are not wearing the "+ short() +".\n");
	return 0;
    }

    // If you have't read the runes intoning this wont work.
    if (!TP->query_prop(RUNES_REVEALED))
    {    
	notify_fail("You wait... and wait... Nothing happens.\n");
	return 0;
    }
    tell_room(EN(TP), QCTNAME(TP) + " intones an ancient phrase "+
      "and holds up "+ TP->query_possessive() +" hands.\nA cloud "+
      "of glowing gold dust floats up into a tiny vortex.\n", TP);
    TP->catch_msg("You raise your hands and call upon the "+
      "stars to manifest their glory.\nYour "+ short() +
      " begins to flake into glowing gold dust that "+
      "that floats upward into a tiny vortex.\n");
    remove_runes(TP);
    set_alarm(3.0, -1.0, &do_star());
    set_alarm(3.5, 0.0, &remove_object());
    return 1;
}

int
give_courage(string str)
{
    object who;

    if (!query_worn())
    {
	notify_fail("You are not wearing the "+ short() +".\n");
	return 0;
    }

    // If you have't read the runes intoning this wont work.
    if (!TP->query_prop(RUNES_REVEALED))
    {    
	notify_fail("You wait... and wait... Nothing happens.\n");
	return 0;
    }

    // You can't do the courage incantation on yourself.
    if (!str || str == "me" || str == "myself")
    {
	write("You close your eyes and take a deep breath as you try "+
	  "to shore up your courage.\n");
	say(QCTNAME(TP) + " briefly closes " + TP->query_possessive() + 
	  "eyes and takes a deep breath.\n");
	return 1;
    } 

    who = present(str, EN(TP));
    if (!who)
    {
	write("Give courage to whom?\n");
	return 1;
    }

    if (!living(who)) 
    {
	write("Your attempt appears to be in vain.\n");		
	return 1;
    }

    TP->catch_msg("You grasp "+ QCTNAME(who) +" by the shoulder, look "+
      "into "+ who->query_possessive() + " eyes, and exhort the ancient "+
      "powers of the ring to fill "+ who->query_objective() +" with a "+
      "dragon's courage.\n");
    who->catch_msg(QCTNAME(TP) + " grasps you by the shoulder and stares "+
      "deeply into your eyes.\n" + capitalize(TP->query_possessive()) + 
      " "+ short() +" glows brightly as " + TP->query_pronoun() +
      " speaks some words in an ancient and mysterious language.\n" +
      "You suddenly feel bolder, as if you could slay dragons.\n");
    tell_room(EN(TP), QCTNAME(TP) + " grasps " + QCTNAME(who) + " by the "+
      "shoulder and stares into "+ who->query_possessive() +" eyes.\n"+
      QCTNAME(TP) +" speaks in an ancient and mystifying language.\n", 
      ({ TP, who }));
    who->add_prop(DRAGON_SLAYER, 1);
    return 1;
}

int 
rune_reveal(object tp)
{
    int sk, st;

    if (tp->query_prop(RUNES_REVEALED))
    {
	tp->catch_msg("One rune means 'glory' and another, "+
	  "'encourage'. The rest of them remain as obscure "+
	  "as ever.\n");
	return 1;
    }		

    sk = tp->query_skill(SS_LANGUAGE);
    st = tp->query_stat(SS_INT);	
    if ((sk + st) > (75 + random(75)))
    {
	tp->catch_msg("Two of the runes make some sort of sense "+
	  "to you. One of them seems to mean 'glory' and the "+
	  "other, 'encourage'. The others remain a mystery.\n");
	tp->add_prop(RUNES_REVEALED, 1);
	return 1;
    }		
}	

int
study_runes(string str)
{
    if (!str)
    {
	notify_fail("Study what, the runes?\n");
	return 0;
    }

    if (str == "rune" || str == "runes")
    {
	write("You run your fingers across the runes and tilt "+
	  "the ring so you can get a closer look.\n");
	say(QCTNAME(TP) +" seems to be studying an "+ short() +
	  " closely.\n");
	set_alarm(3.0, 0.0, &rune_reveal(TP));
	return 1;
    }
}	

void
init()
{

    ::init();

    add_action("do_glory",     "glory");
    add_action("give_courage", "encourage");
    add_action("study_runes",  "study");
}
