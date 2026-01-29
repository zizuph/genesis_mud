/*
* Created by: Damian Horton
* Date: 1997 (c)
*
* File: /d/Cirath/ridge/wep/wicked.c
* Comments: Received permission to edit file, Luther Sept 01
*/
/* Code (c) 1997 to Damian Horton
   This is my first attempt at a weapon, hopefully to be made into
   a cruel new club. It is the property of the gith leader.
   Special thanks to Dunstable, for the code used to determine the ac
   of hit locations (lifted from his maul.c). */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";
#include "/sys/wa_types.h"
#include <formulas.h>
#include "defs.h"

void create_weapon()
{
        set_name("scourge");
        set_short("wicked barbed scourge");
        set_long("This is a truly vicious weapon, seemingly designed "+
	 "to prolong the suffering of ones foes. It consists of "+
	 "a wooden handle, to which are attached five distinct "+
	 "strips of inix leather. Imbedded at the end of each of "+
	 "these five foot long whips is a series of cruel "+
	 "metal barbs, designed to tear strips of flesh out of the "+
	 "unfortunate recipient of its blows. Furthermore, the "+
	 "entire length of the whips are embedded with sharp pieces "+
	 "of obsidian, ensuring that all save the most poorly placed "+
	 "blows causes painful scratches.\n"+
	 "This is a particularly gruesome weapon to employ against "+
	 "exposed flesh!\n");

       	set_adj ("wicked");
  	add_adj ("barbed");

  	set_hit(39);
  	set_pen(27);
	set_wt(W_CLUB);
  	set_dt(W_SLASH);
  	set_hands(W_ANYH);
	add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
        add_prop(MAGIC_AM_MAGIC, ({ 10, "psionic" }));
	add_prop(OBJ_M_NO_BUY, "No I don't want to sell this weapon. I'll "
			+"keep it to my self.");
	set_likely_corr(0);
	set_likely_dull(-10000);
    	add_prop(OBJ_I_WEIGHT,2750);
  	add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(37,27) + random(200));
  	add_prop(OBJ_I_VOLUME,750);
	add_prop(MAGIC_AM_ID_INFO, ({"This cruel weapon displays "+
      		"evidence of having been psionically enhanced.\n", 10,
      		"The enchantment is weak by comparaison to some magical "+
      		" enchantments, yet this certainly enhances the weapons "+
      		"effectivness, turning an implement of torture into a "+
      		"useful weapon.\n", 20}));
	
	add_prop(OBJ_S_WIZINFO, "The psionic enhancement is what is "+
      		"responsible for the weapons unsually good hit and "+
      		"penetration values. The increased damage to unarmed "+
      		"areas, and the dex loss associated with being struck "+
      		"with this weapon are non-magical properties of its "+
      		"design. I figure this weapon would be EXCEPTIONALLY "+
      		"painful to be struck by, and this abnormally potent pain "+
      		"manifests itself in temporary dex loss in its victims.\n");
	set_wf(TO);
	
}

int
did_hit(int aid, string hdesc, int phurt,
	object enemy, int dt, int phit, int dam)
{
    object special, me = ENV(TO);
    
    ::did_hit();    
	
    if(enemy->query_hp()<=0)
    {
	me->catch_msg("With a quick flick of the wrist you bring "+
	    "the wicked barbed scourge across "+QTNAME(enemy)+"'s"+
	    " face, tearing it open! "+QCTNAME(enemy)+" falls to "+
	    "the ground, writhing in agony, but you do not relent! "+
	    "You strike at "+HIM_HER(enemy)+" with the scourge, "+
	    "again and again, tearing away "+HIS_HER(enemy)+" flesh "+
	    "until there is nothing left of "+HIM_HER(enemy)+
	    " save a hideously mutilated corpse.\n");
	me->tell_watcher(QCTNAME(me)+" tears open the face of "+
	    QTNAME(enemy)+" with the wicked barbed scourge! "+
	    QCTNAME(enemy)+" falls to the ground, writhing in agony, "+
	    "but "+QTNAME(me)+" shows "+HIM_HER(enemy)+" no mercy! "+
	    QCTNAME(me)+" strikes "+QTNAME(enemy)+" again, and "+
	    "again, tearing away "+HIS_HER(enemy)+" flesh until "+
	    "all that remains is a hideously mutilated corpse!\n", me, enemy);
	enemy->catch_msg(QCTNAME(me)+" tears open your face with "+
	    HIS_HER(me)+" wicked barbed scourge! The agony is "+
	    "unbearable! You collapse to the ground, unable to "+
	    "endure the pain, but "+QTNAME(me)+" shows you no mercy! "+
	    "Sharp spikes of agony make their way to your brain, as "+
	    QTNAME(enemy)+" strikes you again, and again, stripping "+
	    "away your flesh!\n"+
	    "Gradually, the pain of each successive "+
	    "blow becomes less and less, as the world around you "+
	    "begins to dim, and you are plunged into darkness...\n");
	enemy->do_die(query_wielded());
	return 1;
    }
    
    switch(phurt)
    {
      case -1:
	me->catch_msg(QCTNAME(enemy)+" deftly dodges your clumsy "+
	      "attack!\n");
	enemy->catch_msg("You deftly dodge "+QTNAME(me)+
	      "'s clumsy attempts to whip you.\n");
	me->tell_watcher(QCTNAME(enemy)+" deftly dodges "+
	      QTNAME(me)+"'s clumsy attempts to whip "+HIM_HER(enemy)+
	      ".\n", me, enemy);
	break;
      case 0..3:
	me->catch_msg("You scratch "+QTNAME(enemy)+"'s "+hdesc+
	  " with your wicked barbed scourge.\n");
	enemy->catch_msg(QCTNAME(me)+" scratches your "+hdesc+
	    " with "+HIS_HER(me)+" wicked barbed scourge.\n");
	me->tell_watcher(QCTNAME(me)+" scratches "+QTNAME(enemy)+
	    "'s "+hdesc+" with "+HIS_HER(me)+" wicked barbed "+
	    "scourge.\n", me, enemy);
	break;               
      case 4..10:
	me->catch_msg("You flay the flesh of "+QTNAME(enemy)+"'s "+
	    hdesc+" with your wicked barbed scourge.\n");
	me->tell_watcher(QCTNAME(me)+" flays the flesh of "+
	    QTNAME(enemy)+"'s "+hdesc+" with "+HIS_HER(me)+" wicked "+
	    "barbed scourge.\n", me, enemy);
	enemy->catch_msg(QCTNAME(me)+" flays the flesh of your "+
	    hdesc+" with "+HIS_HER(me)+" wicked barbed scourge.\n");
	break;
      case 11..20:
	me->catch_msg("You cruelly lacerate "+QTNAME(enemy)+"'s "+
	    hdesc+" with your wicked barbed scourge!\n");
	me->tell_watcher(QCTNAME(me)+" cruelly lacerates "+
	    QTNAME(enemy)+"'s "+hdesc+" with "+HIS_HER(me)+
	    " wicked barbed scourge!\n", me, enemy);
	enemy->catch_msg(QCTNAME(me)+" cruelly lacerates your "+hdesc+
	    " with "+HIS_HER(me)+" wicked barbed scourge!\n");
	break;
      case 21..30:
	me->catch_msg("You tear strips of flesh out of "+
	    QTNAME(enemy)+"'s "+hdesc+" with your wicked barbed "+
	    "scourge!\n");
	me->tell_watcher(QTNAME(me)+" tears strips of flesh out of "+ 
	    QTNAME(enemy)+"'s "+hdesc+" with "+HIS_HER(me)+" wicked "+
	    "barbed scourge!\n", me, enemy);
	enemy->catch_msg(QCTNAME(me)+" tears strips of flesh out of "+
	    "your "+hdesc+" with "+HIS_HER(me)+" wicked barbed "+
	    "scourge!\n");
	break;
      case 31..50:
	me->catch_msg("Chunks of raw flesh fly from "+QTNAME(enemy)+ 
	    "'s "+hdesc+" as you strike it with your wicked barbed "+
	    "scourge!\n");
	me->tell_watcher("Chunks of raw flesh fly from "+QTNAME(enemy)+ 
	    "'s "+hdesc+" when "+QTNAME(me)+" strikes "+HIM_HER(enemy)+
	    " with the wicked barbed scourge!\n", me, enemy);
	enemy->catch_msg(QCTNAME(me)+" tears chunks of flesh out of "+
	    "your "+hdesc+" with "+HIS_HER(me)+" wicked barbed "+
	    "scourge!\n");
	break;
      case 51..80:
	me->catch_msg("As you strike "+QTNAME(enemy)+"'s "+hdesc+
	    ", your wicked barbed scourge gets caught on something! "+
	    "You tug forcefully on the scourge, scraping the bone "+
	    "on which it had gotten caught, and releasing a shower "+
	    "of blood!\n");
	me->tell_watcher(QCTNAME(me)+"'s wicked barbed scourge seems "+
	    "to get caught on "+QTNAME(enemy)+"'s "+hdesc+"! You hear "+
	    "the grating sound of metal scraping against bone as "+
	    QTNAME(me)+" yanks the scourge free, showering you with "+
	    "warm blood!\n", me, enemy);
	enemy->catch_msg(QCTNAME(enemy)+"'s wicked barbed scourge "+
	    "tears into your "+hdesc+" and gets caught on a bone!\n "+
	    QCTNAME(enemy)+" gives it a tremendous tug, sending a "+
	    "current of agony through your nerves as the barbs "+
	    "scrape against the bone! A shower of blood ensues "+
	    "as the barbs are pulled from your flesh!\n");
	break;
      default:
	me->catch_msg("With a flick of the wrist, you bring the "+
	    "wicked barbed scourge up across "+QTNAME(enemy)+"'s "+
	    "face, tearing it open! "+QCTNAME(enemy)+" staggers "+
	    "around in blind agony!\n");
	me->tell_watcher("With a flick of the wrist, "+QTNAME(me)+
	    " brings the wicked barbed scourge up across "+QTNAME(enemy)+
	    "'s face, tearing it open! "+QCTNAME(enemy)+" staggers "+
	    "around in blind agony!\n", me, enemy);
	enemy->catch_msg("with a flick of the wrist, "+QTNAME(me)+
	    " brings the wicked scourge up across your face, tearing "+
	    "it open! You stagger around, in blind agony!\n");
	break;
    }
    
    /*
    if((DIS(enemy)<dam)&&(!present("_scourge_object_",enemy)))
    {     
	enemy->catch_msg("You are overcome by the debilitating "+
	    "agony of your wounds!\n");
	me->tell_watcher(QCTNAME(enemy)+" is overcome by "+
	    "debilitating agony!\n");
	me->catch_msg("Your last blow has left "+QCTNAME(enemy)+
	    "in debilitating agony!\n");
	clone_object(RIDGE_OBJ+"scourge_object")->move(enemy);
	//special=clone_object(RIDGE+"/obj/scourge_object.c");
	//special->move(enemy);
    }
  */
    return 1;
 
}
public mixed
wield(object to)
{
	if(TP->query_alignment() > 200)
	{
		TP->catch_msg("As you grasp the wicked barbed scourge, a barely "+
	  		"perceptible warmth travels up your "+
	  		"arm, and then resides in your brain. You begin to "+
	  		"have second thoughts about employing it as a weapon. "+
	  		"Do even orcs and draconians deserve to be tortured to "+
	  		"death?!?\n");
	}
	else
	{
		TP->catch_msg("As you grasp the wicked barbed scourge, a barely "+
	      		"perceptible warmth travels up your "+
	      		"arm, and then resides in your brain.\n");
	}
	
	TP->command("grin sadistic");
	return 0;
}