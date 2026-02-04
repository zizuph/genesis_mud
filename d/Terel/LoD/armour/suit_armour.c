/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * suit_armour.c
 * Adapted from a ribos armour, 10-1998
 * 
 * Simulation of a 15th century suit of armour
 *
 *Trofast
 * 
 * 
 * Modified for use with the new standard armour for Terel.
 * Torm, Sep 98
 */

#define HIS(x) x->query_possessive()
#define HE(x)  x->query_pronoun()
#define HIM(x) x->query_objective()

#define WEAR_LOG "/d/Terel/log/suit_log"

#include "/d/Terel/include/Terel.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit STDARMOUR;

object dresser=0, dressee=0;
int i, alarm_id, penalty=0;

//Function declarations

//The player has to get someone to help him wear it.
int  request_assistance(object dresser);

// Starts the alarm that performs the wearing script.
void start_stuff (int j);

// The wearing script
void do_stuff(object dresser,  
	      object dressee);

// Adds properties to the player.  Called from wear_terel_armour.
int  add_stuff();

//Cleans up
void reset_vars();

//Logs the wearing.
void write_log(object dresser,
	      object dressee);

public void
create_terel_armour()
{
    
    set_name(({"suit of armour", "suit", "armour","suit_of_armour"}));
    set_pname(({"suits of armour", "suits", "armours"}));
    set_adj("shining");
    add_adj("plate");
    set_short("suit of shining plate armour");
    set_pshort("suits of shining plate armour");
    set_ac(50);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({"enchantment",50}));
    add_prop(OBJ_S_WIZINFO,"This suit of armour covers the entire "+
	     "body, so no other armour can be worn with it. It also "+
	     "has a strength requirement to wear it effectively. If the "+
	     "player does not have enough str, he will receive negative"+
	     " quickness. 160 Str and up receives no penalty. The armour"+
	     " also require the assistance of another player for the "+
	     "wearer to wear. This armour is worn by the colonel in "+
	     "the legion of darkness. The armour also adds an extra "+
	     "short, to 'Trofast in shining armour'.\n\nThe armour is "+
	     "an accurate reproduction of a 15th-century medieval suit "+
	     "of armour.\n");

    add_prop(MAGIC_AM_ID_INFO,({
             "The suit of armour will provide good protection from "+
             "physical blows.\n",40,
             "The suit of armour will slow down the wearer if the "+
             "wearer is not strong enough to bear the weight.\n",70}));
    set_at(A_BODY | A_TORSO | A_HEAD | A_LEGS | A_ARMS |A_HANDS |A_FEET );
    set_am(({0,0,-10}));
    set_likely_break(2);
    set_likely_cond(2);
    set_armour_size(MEDIUM);
    add_prop(OBJ_I_WEIGHT,50000);
    add_prop(OBJ_I_VOLUME,80000);
    add_prop(OBJ_I_VALUE,10000);


    set_long("A full suit of shining plate armour. Made of burnished "+
	     "steel, the component parts are expertly crafted to fit "+
	     "together.  \n"+

	     "The upper part of the armour consists of a solid steel "+
	     "breastplate and backplate, joined over the shoulders with "+
	     "leather straps.  "+
	     "The lower part of the armour is composed of a series of "+
	     "faulds around the waist, from which tassets hang to protect "+
	     "the hips.  Broad cuisses cover the "+
	     "front part of the thigh, while smaller plates wrap around "+
	     "the back of the leg.  Over the knees, solid poleyns are "+
	     "attached to the articulated lames of the knee joint. "+
	     "The calf and shin are protected by greaves "+
	     "and sabatons worn on the feet. "+
	     "Underneath all, a thick linen acton is worn, "+
	     "to which the arming points of the arm and leg "+
	     "harnesses are tied.\n"
);


    add_item(({"arming points"}), 
	     "Leather discs attached to various pieces of the armour "+
	     "so that they can be tied to the acton. Each arming "+
	     "point has two holes for laces to pass through.\n");

    add_item(({"acton","arming doublet", "arming coat"}), 
	     "A quilted linen coat with buttons up the front.  The arming "+
	     "coat, as it is called, provides comfort and added protection "+
	     "for the wearer.  The sleeves are cut wide under the shoulder "+
	     "to provide good mobility for the arm. The arm and leg "+
	     "harnesses can be securely tied to laces on the shoulder "+
	     "and waist.\n");

    add_item(({"bascinet","bascinets"}), 
	     "A sleek, closed helmet consisting of a tight-fitting skull "+
	     "cap, a hinged visor, and a skirted ventail.  The bascinet "+
	     "is highly regarded for its range of vision, pronounced "+
	     "glancing surface, and its lightweight design.\n");

    add_item(({"visor","visors"}), 
	     "A hinged visor on the bascinet.  Horizontal slits in the "+
	     "visor provide good vision when the visor is down.  With "+
	     "the visor up, most of the wearer's face is exposed.\n");

    add_item(({"ventail","ventails"}), 
	     "A chainmail skirt attached to the bascinet that protects the "+
	     "throat and neck.  Because it is a separate piece, the "+
	     "wearer has fairly good mobility of the head and neck.\n");

    add_item(({"breastplate","breastplates"}), 
	     "A globular sheet of steel that covers the chest and "+
	     "abdomen. The edge around the arm and neck openings is rolled "+
	     "outward to prevent chafing and to help deflect weapons.\n");

    add_item(({"backplate","backplates"}), 
	     "An almost perfectly rectangular piece of steel plate "+
	     "that protects the back.  Leather straps connect it to "+
	     "the breastplate over the shoulders.\n");

    add_item(({"arm harness"}), 
	     "The arm harness is the assembled collection of all the "+
	     "armours of the arm, including the pauldron, spaulder, "+
	     "rerebrace, couter, vambrace, and gauntlets.  The pieces"+
	     "are permanently riveted together, with articulated lames "+
	     "at the joints.\n");

    add_item(({"spaulder","spaulders"}), 
	     "The shoulder point defence, a dished (rounded) cup "+
	     "with small lames extending from it.  It is riveted to"+
	     "the rerebrace.  A leather arming point can connect to"+
	     "the arming coat or to the breastplate.\n");

    add_item(({"pauldron","pauldrons"}), 
	     "Pauldrons are an extension of the shoulder defence.  "+
	     "Plated lames hanging from the spaulder provide added "+
	     "protection for the armpit and part of the chest and back.\n");

    add_item(({"rerebrace","rerebraces"}), 
	     "A round cannon that covers the upper arm.  An arming point "+
	     "connects to the acton, and at the elbow riveted lames "+
	     "connect to the couter.\n");

    add_item(({"couter","couters"}), 
	     "A rounded, slightly conical armour for the elbow.  Small "+
	     "wings wrap around to cover part of the inner elbow, and "+
	     "riveted lames connect it to the upper and lower cannons "+
	     "of the arm.\n");

    add_item(({"vambrace","vambraces"}), 
	     "A round cannon that covers the lower arm.  "+
	     "At the elbow riveted lames connect to the couter, but "+
	     "there is enough play so the vambrace can twist with "+
	     "the motion of the lower arm.\n");

    add_item(({"gauntlets","gauntlets"}), 
	     "These are hourglass gauntlets, with a flared cuff that "+
	     "allows some wrist movement.  Each finger is defended by "+
	     "articulated scales, with gatlings on the knuckles (similar "+
	     "to poleyns on the knees).  The gauntlets are lined with "+
	     "soft leather.\n");

    add_item(({"fauld","faulds"}), 
	     "Several thick hoops of steel worn round the waist to "+
	     "protect the hips, abdomen and lower back.  The breastplate "+
	     "and backplate are tied to the faulds to form a cuirass. "+
	     "Steel plated tassets hang down below.\n");

    add_item(({"tasset","tassets"}), 
	     "Ribbed steel plates with a thick rolled edge hang down "+
	     "from the faulds, covering the pelvis, buttocks and "+
	     "hips.  They form a sort of skirt for the wearer.\n");

    add_item(({"leg harness"}), 
	     "The leg harness is the assembled collection of all the "+
	     "leg armours, including the cuisse, poleyn, greaves "+
	     "and sabaton.\n");  
    
    add_item(({"cuisse","cuisses"}), 
	     "Arming points at the top of these broad thick plates "+
	     "connect them to the acton.  The cuisses cover the "+
	     "front and back part of the thigh, connected at the side "+
	     "with straps.\n");

    add_item(({"poleyn","poleyns"}), 
	     "The poleyn is a round cap covering the knee, connected "+
	     "to the greaves and cuisses by articulated lames.  "+
	     "Separate wings extend back around the back of the knee "+
	     "on either side of the leg.\n");

    add_item(({"lames","lame"}), 
	     "In the knee and arm joints, and on the neck armour, "+
	     "narrow, thin plates of steel called lames are layered "+
	     "and flared in such a way as to allow movement while "+
	     "still providing protection.  Even the gauntlets have "+
	     "tiny, extremely finely-crafted lames allowing for "+
	     "finger movement.\n");

    add_item(({"greave","greaves"}), 
	     "These plate greaves are made in two pieces, front and "+
	     "back, hinged on the outer edge and buckled together "+
	     "on the inside of the lower leg.\n");

    add_item(({"sabaton","sabatons"}), 
	     "These shiny, steel boots are made from articulated "+
	     "plates ending in a round toecap.  The top of the sabaton "+
	     "extends upwards underneath the bottom of the greaves.\n");


}

void
init()
{
  ::init();
  add_action("request_assistance","request");
}

void
reset_vars()
{
  dresser=0;
  dressee=0;
  if(get_alarm(alarm_id))
    remove_alarm(alarm_id);
  alarm_id=0;
  i=0;
  return;
}

void
write_log(object dresser,
	 object dressee)
{
string str;
str=dressee->query_name()+" helped by "+dresser->query_name()+
    " on";

write_file(WEAR_LOG, str+" (" + ctime(time()) + ")\n");

}


int
add_stuff()
{

//Add props to the player, then return 1.

     // Since it's a full suit of armour, the wearer gets slowed down 
     // unless they are very strong.

     penalty= 80 - ((wearer->query_stat(SS_STR)) / 2);

     if (penalty<0) penalty=0;

     wearer->add_prop(LIVE_I_QUICKNESS, 
		      wearer->query_prop(LIVE_I_QUICKNESS) - penalty);

     // But they get this extra short!
     wearer->add_prop(LIVE_S_EXTRA_SHORT, " in shining armour");
 
     return 1;
}


mixed 
wear_terel_armour(object obj) 
{

  //Allow wizards and npcs to wear it normally.
  if ( (!(interactive(wearer))) | (wearer->query_wiz_level() >0) ) 
    return add_stuff();
  
  //Block the normal wear command.  They need someone to help them.
  if (!dresser) 
{
       return "You cannot simply wear the suit of armour, it is too " +
      "unwieldy.  Perhaps if you requested the assistance "+ 
      "of someone?\n";
}
  //If the wearing alarm is already running, tell them to be patient!
  if (alarm_id)  
{
       return "It takes time to wear the suit of armour properly! \n";
}

     return add_stuff();
}

mixed 
remove(object obj)
{
  //Speed them back up after removing the heavy armour.
   wearer->add_prop(LIVE_I_QUICKNESS, 
                    wearer->query_prop(LIVE_I_QUICKNESS)+penalty);

   //Remove the extra short desc.
   wearer->remove_prop(LIVE_S_EXTRA_SHORT);

   /*   if (interactive(wearer))
     write_file(WEAR_LOG, wearer->query_name()+" removed. (" + 
		ctime(time()) + ")\n");
		*/

  /* If you want special remove messages put them here */
  /* and return 1 instead of 0.                         */ 
  return 0;
}


int
request_assistance(string str)
{
int response, race_size;
object yes_no_object;    

    notify_fail("Request assistance from whom?\n");

    if (!str) return 0;

    dressee=TP;

	/* tmp dresser added, so wrong use of this action does
	 * not set dresser variable.  - Udana 08/2006*/
	object tmp_dresser = 0;


    // Syntax is: "request [the] assistance of/from <player>"

    if (!parse_command(str,ENV(dressee), 
		       "[the] 'assistance' 'of' / 'from' %o",
		       tmp_dresser))
      return 0;

    //You're already wearing it!
    if (TO->query_worn()) 
    {
        notify_fail("You're already wearing the suit of armour.\n");
        return 0;
    }
 
    //Can't request assistance if you are already getting it.
    if (alarm_id)
    {
        notify_fail ("Yes, yes.\n");
        return 0;
    }

    //Only players can help.
    if (!interactive(tmp_dresser))
      {
	reset_vars();
	return 0;
      }

    //Can't help yourself.
    if (tmp_dresser==dressee) return 0; 

    // Not if they aren't there.
    if (!present(tmp_dresser,ENV(dressee))) return 0;

    // Not if they are hidden or invis.
    if (!(CAN_SEE(dressee,tmp_dresser))) return 0;

    // Not if you can't see in the room.
    if (!(CAN_SEE_IN_ROOM(dressee))) return 0;

    //Not if you are in combat.
    if ( objectp(tmp_dresser->query_attack())
	| objectp(dressee->query_attack()) ) 
      {
	notify_fail("There's no time for that now!\n");
	return 0;
      }

    // Have to have all available armour locations empty.
    // I'm sure there is a more elegant way to do this but oh well...
    if (dressee->query_armour(A_BODY))
          {
         notify_fail("You are wearing too much!\n");
         return 0;
       }
    if (dressee->query_armour(A_TORSO))
       {
         notify_fail("You are wearing too much!\n");
         return 0;
       }
    if (dressee->query_armour(A_HEAD))
       {
         notify_fail("You are wearing too much!\n");
         return 0;
       }
    if (dressee->query_armour(A_LEGS))
       {
         notify_fail("You are wearing too much!\n");
         return 0;
       }
    if (dressee->query_armour(A_ARMS))
       {
         notify_fail("You are wearing too much!\n");
         return 0;
       }
    if (dressee->query_armour(A_HANDS))
       {
         notify_fail("You are wearing too much!\n");
         return 0;
       }
    if (dressee->query_armour(A_FEET))
       {
         notify_fail("You are wearing too much!\n");
         return 0;
       }
 
//Have to be a race that can wear MEDIUM.
    race_size = RACE_SIZE_TRACKER->query_race_size(dressee->query_race_name());

    if (!(TO->query_armour_size() & race_size))
        {
         notify_fail ("The suit of armour does not fit properly on you.\n");
         return 0;
        }

	/* All went ok, seting up real dresser varaiable */
	dresser = tmp_dresser;
			
    dressee->catch_msg ("You request the assistance of "+QTNAME(dresser)+
			" in wearing the suit of shining armour.\n");
   
    dresser->catch_msg (QCTNAME(dressee) + " requests your assistance in "+
	        "wearing " + HIS(dressee) +" suit of shining "+
		"armour.  Do you want to help " 
		+ HIM(dressee)+ "? Yes/No\n");

    tell_room(ENV(dressee), QCTNAME(dressee)+" requests the assistance "+
	      "of "+QTNAME(dresser)+" in wearing the suit of "+
	      "shining armour.\n", 
	      ({dresser,dressee}));

    setuid();
    seteuid(getuid());

    // To request assistance from someone, we clone a yes_no 
    // object from Shiva.  ~shiva/open/yes_no.c

    //Check if it clones ok.
    if (yes_no_object=clone_object(LOD_DIR + "armour/yes_no"))
      {
	//Calls start_stuff with the parameter from get_answer.
	if (!yes_no_object->get_answer(dresser, &start_stuff(), 10.0))
	  {
	    //get_answer went wrong, remove it.
	    yes_no_object->remove_object();
	    return 0;
	  }
	return 1;
      }       

}

void
start_stuff(int j)
{
switch (j)
  {
    // Dresser refused to help.
  case 0:
    
    {
      dresser->catch_msg("You refused the request.\n");
      dressee->catch_msg(QCTNAME(dresser)+" refused your request.\n");
      tell_room(ENV(dressee),QCTNAME(dresser)+ 
		" refused the request.\n", 
		({dresser,dressee}));
      reset_vars();
      return;
    }

    // Dresser agreed to help, start the show.
  case 1:
    {
     i=0;
     alarm_id=set_alarm(0.0, 5.0, &do_stuff(dresser, dressee));
     return;
    }

    // No response from the dresser, the inconsiderate oaf.
  default:
    {
      dressee->catch_msg("There was no response to your request.\n");
      reset_vars();
      return;
    }
  }
  return;
}

void
do_stuff(object dresser, object dressee)
{

  // If the dresser leaves in the middle, stop the show.
   if (!present(dresser,ENV(dressee))) 
     {
       dressee->catch_msg(QCTNAME(dresser)+" ran out on you!\n");
       reset_vars();
       return;
     }
// If the dresser drops the suit of armour, stop the show.
   if (!present (TO, dressee))
       {
	 dressee->catch_msg("You stop dressing.\n");
	 dresser->catch_msg("You are unable to help any longer!\n");

	 tell_room(ENV(dressee),
		       QCTNAME(dressee)+ " stops dressing.\n ",
		       ({dresser,dressee}));
	 reset_vars();
	 return;
       }

   //If someone starts a fight, stop the show.
    if ( objectp(dresser->query_attack())
	| objectp(dressee->query_attack()) ) 
      {
	 dressee->catch_msg("You stop dressing.\n");
	 dresser->catch_msg("You are unable to help any longer!\n");

	 tell_room(ENV(dressee),
		       QCTNAME(dressee)+ " stops dressing.\n ",
		       ({dresser,dressee}));	
	reset_vars();
	return 0;
      }

   switch(i)
    {
    case 0:
     // Dresser agrees to help.
     {
       //But the dresser can't figure it out.

       if ( (dresser->query_skill(SS_APPR_OBJ)) < 30 )
	 {
	   dressee->catch_msg(QCTNAME(dresser)+ " gets a confused look on "+
			      HIS(dresser) + " face as "+
			      HE(dresser)+ " looks over "+
			      "the parts that comprise the suit of armour. "+
			      "It seems you'll have to find another "+
			      "assistant.\n");
	   dresser->catch_msg("As you look at the confusing array of "+
			      "parts that comprise the armour, "+
			      "a hot feeling rises in your throat. "+
			      "There's no way you could construct the "+
			      "suit properly!\n");

	     tell_room(ENV(dressee),
		       QCTNAME(dresser)+ " gets a confused look on "+
		       HIS(dresser) + " face as "+
		       HE(dresser) + " looks over "+
		       "the parts that comprise the suit of armour.\n ",
		       ({dresser,dressee}));

	     reset_vars();
	     return;
	   }


	 break;
	   }
     case 1:

       {
	 dressee->catch_msg("You carefully arrange the components of the "+
			    "suit of armour on the floor.  "+
			    QCTNAME(dresser)+ " watches "+
			    "closely and takes note of each piece.\n");
	 dresser->catch_msg(QCTNAME(dressee)+ " carefully arranges the "+
			    "components of the suit of armour on the "+
			    "floor.  You take close note of each piece.\n\n");
	 dresser->catch_msg(long());
	 tell_room(ENV(dressee),QCTNAME(dressee)+ " carefully "+
		   "arranges the components of the suit of armour on the "+
		   "floor.  "+QCTNAME(dresser)+" watches closely.\n",
		   ({dresser,dressee}));
	 break;
       }
     case 2:
       {
	dressee->catch_msg("You step into the steel sabatons, pulling the "+
			   "top of each boot above your ankle.\n");

	tell_room(ENV(dressee),QCTNAME(dressee)+ " steps into the "+
		  "steel sabatons, pulling the top of each boot above "+
		  HIS(dressee)+ " ankle.\n", dressee);
	break;
       }
       
    case 3:
       {
	dressee->catch_msg("You pull the linen acton over your shoulders "+
			   "and insert your arms into the thick sleeves. "+
			   "One by one you fasten each of the dozen or so "+
			   "buttons down the front, and smooth the fabric "+
			   "down over your waist.\n");
	tell_room(ENV(dressee),QCTNAME(dressee)+" pulls the linen acton over "+
			   HIS(dressee) + " shoulders and inserts "+
			   HIS(dressee) +" arms into the thick sleeves.  "+
			   "One by one "+HE(dressee)+ " fastens each of "+
			   "the dozen or so buttons down the front, and "+
			   "smooths the fabric down over "+
			   HIS(dressee) +" waist.\n", dressee);
	break;
       }

    case 4:
       {
	dressee->catch_msg("You step into the the faulds, which are on the "+
			   "ground. "+QCTNAME(dresser)+ " lifts the faulds "+
			   "and tassets up to your waist, and you grab "+
			   "the metal hoop and hold on.\n");
	dresser->catch_msg(QCTNAME(dressee)+ " steps into the the faulds, "+
			   "which are on the ground.  You lift the faulds "+
			   "and tassets up to "+HIS(dressee)+ " waist, and "+
			   HE(dressee)+" grabs the metal hoop.\n");
	tell_room(ENV(dressee), QCTNAME(dressee) +" steps into the the "+
		  "faulds, which are on the ground.  "+QCTNAME(dresser)+
		  " lifts the faulds and tassets up to "+QTNAME(dressee)+
		  "'s waist, and "+HE(dressee)+" grabs the metal hoops.\n",
		  ({dresser,dressee}));
	break;
       }

     case 5:
       {
	dressee->catch_msg(QCTNAME(dresser)+" picks up the heavy breastplate "+
			   "and backplate and holds the two pieces apart.  "+
			   "Sliding sideways between them, you stick your "+
			   "head and shoulders through the straps.  You "+
			   "stagger for a moment at the sudden shock of "+
			   "weight as "+QTNAME(dresser)+ " lowers the "+
			   "armour onto your shoulders.\n");
	dresser->catch_msg("You pick up the heavy breastplate and backplate "+
			   "and hold the two pieces apart.  "+QCTNAME(dressee)+
			   " slides sideways between them, sticking "+
			   HIS(dressee)+ " head and shoulders through the "+
			   "straps.  "+QCTNAME(dressee) +" staggers for "+
			   "a moment as you lower the armour onto "+
			   HIS(dressee) +" shoulders.\n");
	tell_room(ENV(dressee),QCTNAME(dresser)+" picks up the heavy "+
		  "breastplate and backplate and holds the two pieces "+
		  "apart.  "+QCTNAME(dressee)+ " slides sideways between "+
		  "them, sticking "+HIS(dressee)+ " head and shoulders "+
		  "through the straps.  "+QCTNAME(dressee)+ " staggers for "+
		  "a moment as "+QTNAME(dresser)+ " lowers the armour "+
		  "onto "+HIS(dressee) +" shoulders.\n", ({dresser,dressee}));
	break;
       }

     case 6:
       {
	dressee->catch_msg(QCTNAME(dresser)+ " quickly ties the bottom of "+
			   "the breastplate and backplate to the hooped ring "+
			   "of the faulds, forming a cuirass.  You are now "+
			   "able to release the faulds and stand easy.\n");
	dresser->catch_msg("You quickly tie the bottom of the breastplate "+
			   "and backplate to the hooped ring of the faulds, "+
			   "forming a cuirass.  "+QCTNAME(dressee)+ 
			   " releases the faulds and stands easy.\n");
	tell_room(ENV(dressee),QCTNAME(dresser)+ " quickly ties the bottom "+
		  "of the breastplate and backplate to the hooped ring of "+
		  "the faulds, forming a cuirass.  "+QCTNAME(dressee)+ 
		  " releases the faulds and stands easy.\n", 
		  ({dresser,dressee}));
	 break;
       }

     case 7:
       {
	dressee->catch_msg(QCTNAME(dresser)+" picks up the right leg "+
			   "harness and holds it while you insert "+
			   "your leg through the wings of the poleyn.\n");
	dresser->catch_msg("You pick up the right leg harness and hold it "+
			   "while "+QTNAME(dressee)+ " inserts "+
			   HIS(dressee)+ " leg through the wings of the "+
			   "poleyn.\n");
	tell_room(ENV(dressee),QCTNAME(dresser)+" picks up the right leg "+
		  "harness and holds it while "+QTNAME(dressee)+ " inserts "+
		  HIS(dressee)+ " leg through the wings of the poleyn.\n", 
		  ({dresser,dressee}));
	break;
       }

     case 8:
       {
	dressee->catch_msg(QCTNAME(dresser)+" wraps the cuisses around your "+
			   "thigh, buckling the front and back plates "+
			   "together.  Then "+HE(dresser)+" closes the "+
			   "two pieces of the greave around your lower leg "+
			   "and buckles them securely.  \n");
	dresser->catch_msg("You wrap the cuisses around "+QTNAME(dressee)+
			   "'s thigh, buckling the front and back plates "+
			   "together.  Then you close the two pieces "+
			   "of the greave around "+HIS(dressee)+ " lower leg "+
			   "and buckle them securely.  \n");
	tell_room(ENV(dressee),QCTNAME(dresser)+ " wraps the cuisses around "
		  +QTNAME(dressee)+"'s thigh, buckling the front and back "+
		  "plates together.  Then "+HE(dresser)+ " closes the two "+
		  "pieces of the greave around "+HIS(dressee)+ " lower leg "+
		  "and buckles them securely.\n", 
		  ({dresser,dressee}));
	break;
       }

     case 9:
       {
	dressee->catch_msg(QCTNAME(dresser)+" ties the arming points of "+
			   "the cuisse to the laces of the acton.  "+
			   HE(dresser)+" tugs on the leg harness to make "+
			   "sure it is securely fastened.  You kick and "+
			   "bend your leg a bit, testing its weight. \nThen, "+
			   "you and "+QTNAME(dresser) +" repeat the process "+
			   "for the left leg harness.\n");
	dresser->catch_msg("You tie the arming points of the cuisse to the "+
			   "laces of the acton.  You tug on the leg harness "+
			   "to make sure it is securely fastened.  "+
			   QCTNAME(dressee)+ " kicks and bends "+HIS(dressee)+
			   " leg a bit, testing its weight. Then "+
			   QTNAME(dressee)+ " and you repeat the process "+
			   "for the left leg harness.\n");
	tell_room(ENV(dressee),QCTNAME(dresser)+" ties the arming points "+
		  "of the cuisse to the laces of the acton.  "
		  +QCTNAME(dressee)+ " tugs on the leg harness and kicks "+
		  "and bends "+HIS(dressee)+" leg a bit, testing its weight. "+
		  "Then "+ QTNAME(dressee)+" and "+ QTNAME(dresser)+ 
		  " repeat the process for the left leg harness.\n", 
		  ({dresser,dressee}));
	break;
       }

     case 10:
       {
	dressee->catch_msg(QCTNAME(dresser)+" holds up the one of the arm "+
			   "harnesses and straightens it.  You insert your "+
			   "arm into the tubular cannon of the rerebrace, "+
			   "inching your sleeves down into the vambraces as "+
			   QTNAME(dresser)+" pulls the harness up to your "+
			   "shoulder.  \n");
	dresser->catch_msg("You hold up the one of the arm harnesses and "+
			   "straighten it. "+QCTNAME(dressee)+ " inserts "+
			   HIS(dressee) +" arm into the tubular cannon of "+
			   "the rerebrace, inching "+HIS(dressee)+
			   " sleeves down into the vambraces as you pull "+
			   "the harness up to "+HIS(dressee)+ " shoulder.\n");
	tell_room(ENV(dressee),QCTNAME(dresser)+" holds up the one of the "+
		  "arm harnesses and straightens it.  "+QCTNAME(dressee)+ 
		  " inserts "+HIS(dressee)+" arm into the tubular cannon "+
		  "of the rerebrace, inching "+HIS(dressee)+ " sleeves down "+
		  "into the vambraces as "+QTNAME(dresser)+" pulls the "+
		  "harness up to "+HIS(dressee)+" shoulder.  \n", 
		  ({dresser,dressee}));
	break;
       }

     case 11:
       {
	dressee->catch_msg(QCTNAME(dresser)+" ties the arming point of the "+
			   "rerebrace to the laces on the acton.  You flex "+
			   "your arm to get your elbow in the right place.  "+
			   QCTNAME(dresser)+ " then puts the other arm "+
			   "harness on your other arm.\n");
	dresser->catch_msg("You tie the arming point of the rerebrace to "+
			   "the laces on the acton.  "+QCTNAME(dressee)+
			   " flexes "+HIS(dressee)+ " arm to get "+
			   HIS(dressee)+ " elbow in the right place.  You "+
			   "then put the other arm harness on "+
			   HIS(dressee)+ " other arm.\n");
	tell_room(ENV(dressee),QCTNAME(dresser) + " ties the arming point of "+
		  "the rerebrace to the laces on the acton.  "+
		  QCTNAME(dressee)+ " flexes "+HIS(dressee)+ " arm to get "+
		  HIS(dressee)+ " elbow in the right place.  "+
		  QCTNAME(dresser)+"then puts the other arm harness on "+
		  HIS(dressee)+ " other arm.\n",
 ({dresser,dressee}));
	 break;
       }

     case 12:
       {
	dressee->catch_msg(QCTNAME(dresser)+ " places each spaulder and "+
			   "pauldron on your shoulders. Then, "+
			   HE(dresser)+" ties the arming points of each "+
			   "spaulder to the rerebracers and to the acton "+
			   "at the neck.\n");
	dresser->catch_msg("You place each spaulder and pauldron on "+
			   HIS(dressee)+" shoulders. Then, you tie the "+
			   "arming points of each spaulder to the "+
			   "rerebracers and to the acton at the neck.\n");
	tell_room(ENV(dressee),QCTNAME(dresser)+ " places each spaulder "+
		  "and pauldron on "+HIS(dressee)+"'s shoulders.  "+ 
		  "Then, "+HE(dresser)+" ties the arming points of each "+
		  "spaulder to the rerebracers and to the acton at the "+
		  "neck.\n", ({dresser,dressee}));
	break;
       }

     case 13:
       {
	dressee->catch_msg("Finally, "+QTNAME(dresser) +" hands you the "+
			   "bascinet, which you lower over your head.  "+
			   "Raising the visor for a moment, you look out "+
			   "through new eyes.  You are now as the "+
			   "proverbial knight in shining armour, armed to "+
			   "all points and ready for battle!\n");
	dresser->catch_msg("Finally, you hand "+QTNAME(dressee)+ 
			   " the bascinet, which "+HE(dressee) +
			   " lowers over "+HIS(dressee)+ " head.  "+
			   QCTNAME(dressee)+" raises the visor for a moment "+
			   "and looks at you.  "+capitalize(HE(dressee))+
			   " is now as the proverbial knight in shining "+
			   "armour, armed to all points and ready for "+
			   "battle!\n");
	tell_room(ENV(dressee),"Finally, "+QTNAME(dresser) +" hands "+
		  QTNAME(dressee)+" the bascinet, which "+HE(dressee)+
		  " lowers over "+HIS(dressee)+" head.  "+
		  capitalize(HE(dressee))+
		  "raises the visor for a moment and looks at "+
		  QTNAME(dresser) +".  "+capitalize(HE(dressee))+
		  " is now as the proverbial knight in shining armour, "+
		  "armed to all points and ready for battle!\n", 
		  ({dresser,dressee}));
	remove_alarm(alarm_id);
	alarm_id=0;
	dressee->command("wear suit_of_armour");
	write_log(dresser,dressee);
       }

     default:
       {
	 reset_vars();
       }
     }
     i++;
}
