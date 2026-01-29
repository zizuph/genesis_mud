//---------------------------------------------------------------------------
//  Base Sean-Rhian Staff - enflameable by spell;
//                          can be rewielded in left/right/both hands
//   Coder         Date                Action
// -------------- -------- ----------------------------------------------
// Zima           12/1/97  Created
// Zima           5/15/98  Recoded as a base for all SR staffs
// Zima			  1/9/00   Recoded to glow instead of flame, add colors
//-----------------------------------------------------------------------
inherit "/d/Khalakhor/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "defs.h"
 
// parse command patterns for rewielding
#define  BOTHH  "%o [in] [with] 'both' [hand] [hands]"
#define  LEFTH  "%o [in] [with] 'left' [hand] [hands]"
#define  RIGHTH "%o [in] [with] 'right' [hand] [hands]"

// hit/pen enhancement factors, based on aura level
#define  HIT_ENH1     1.0
#define  PEN_ENH1     1.0
#define  HIT_ENH2	  2.0
#define  PEN_ENH2     2.0 
 
// Global vars and their default values, set up for npc monks
int    bhit    = 30;  // base (non-flaming) hit value
int    bpen    = 10;  // base (non-flaming) pen value
int    hit_enh = 2;   // factor to enhance hit by when flaming
int    pen_enh = 2;   // factor to enhance pen by when flaming

// staff descriptions 
int    aura=0;  //aura color; 0=none, 1=blue, 2=red
string sshort;  //non-glowing short
string slong;   //non-glowing long
 
//---------------------------------------------------------------------------
// simple query functions for global vars  
//---------------------------------------------------------------------------
int    query_base_hit()      { return bhit;    }
int    query_base_pen()      { return bpen;    }
int    query_hit_enh()       { return hit_enh; }
int    query_pen_enh()       { return pen_enh; }
int    query_aura()			 { return aura;    }
string query_sshort()		 { return sshort;  }
string query_slong()		 { return slong;   }
string color()
{
	switch(aura)
	{
	case 1:  return "blue";
	case 2:  return "red";
	}
	return "";
}

//---------------------------------------------------------------------------
// simple set functions for global vars  
//---------------------------------------------------------------------------
void   set_base_hit(int i)   { bhit=i;           }
void   set_base_pen(int i)   { bpen    = i;      }
void   set_hit_enh(int i)    { hit_enh = i;      }
void   set_aura(int i)       { aura    = i;      }
void   set_sshort(string s)  { sshort  = s;      }
void   set_slong(string s)   { slong   = s;      }
 
//---------------------------------------------------------------------------
// extinguish - extinguishes the staff
//---------------------------------------------------------------------------
void extinguish() 
{
    object env=ENV(TO);
    object tp;
    object troom;

    if (!(aura)) return;

    // update descriptions and hit/pen
    remove_adj("glowing");
	remove_adj(color());
    set_short(sshort);
    set_long(slong);
    set_hit(bhit);
    set_pen(bpen);
    set_aura(0);

    // inform all of what is happening, and update weapon
	if (!objectp(env)) return;
    if (living(env))  // in the possession of a living
       {
	   tp = env;
       troom = ENV(tp);
       if (!(tp->query_npc()))
          tp->catch_msg("The aura of your "+sshort+" fades away.\n");
       tell_room(troom,"The aura of the "+sshort+" of "+QTNAME(tp)+  
		         " fades away.\n",tp);
       if (objectp(TO->query_wielded())) 
		   tp->update_weapon(TO);
       }
    else if (env->query_prop(ROOM_I_IS)) // on the ground
       {
       troom=env;
       tell_room(troom,"The aura of the "+sshort+ " fades away.\n");
       }

	//change the light setting
    TO->remove_prop(OBJ_I_LIGHT);
    if (objectp(troom)) troom->update_light(1); //1=recursive, check all
}
 
//---------------------------------------------------------------------------
// illuminate - lights staff, increasing its power: activated by a "spell"
//              level  - aura level, determines color and effect 
//              numsec - number of seconds staff will remain glowing
//---------------------------------------------------------------------------
void illuminate(int level, int numsec) 
{
    object tp=ENV(TO);
	float  satime=120.0;
    object troom;
	string col;
    int    light;
 
    // staff must not already be glowing
    if (aura) return;

	// determine environment
	if (living(tp))							// held by a living
		troom=ENV(tp);						
	else if (tp->query_prop(ROOM_I_IS))		// laying in a room
		{
		troom=tp;
		tp=0;
		}
	else									//unknown, no messages
		tp=0;
		
    // update descriptions 
    set_aura(level);
	col = color();
    add_adj("glowing");
	add_adj(col);
    set_short("glowing "+sshort);
    set_long(slong+"It is glowing with a "+col+" aura.\n");

	// update hit/pen values according to level
	switch (aura)
	{
	case 1:  set_hit(ftoi(itof(bhit)*HIT_ENH1)); 
		     set_pen(ftoi(itof(bpen)*PEN_ENH1)); 
             add_prop(OBJ_I_LIGHT,3);
			 break;
	case 2:  set_hit(ftoi(itof(bhit)*HIT_ENH1)); 
		     set_pen(ftoi(itof(bpen)*PEN_ENH1));
			 add_prop(OBJ_I_LIGHT,1);
			 break;
	}
    if (objectp(tp)) tp->update_weapon(TO);

	// update light values
    if (objectp(troom)) troom->update_light(0);
 
    // tell all what's happening
	if (objectp(tp))
		{
		if (!(tp->query_npc()))
           tp->catch_msg("Your "+sshort+" begins to glow with a "+col+
		                 " aura!\n");
        tell_room(troom,"The "+sshort+" of "+QCTNAME(tp)+" begins "+
			            "to glow with a "+col+" aura!\n",tp);
		}
	else if (objectp(troom))
		tell_room(troom,"The "+sshort+" begins to glow with a "+col+
		                " aura!\n");
	//else no messages!
			             
 
    // schedule extinguishing
    if (numsec>0) satime=itof(numsec);
    set_alarm(satime,0.0,&extinguish());
}
 
//---------------------------------------------------------------------------
// enter_env - allow only a manach or saggart to receive a glowing staff
//---------------------------------------------------------------------------
void enter_env(object inv, object from) 
{
	if ((aura) && (!(inv->id("manach"))) && (!(inv->is_saggart())))
		extinguish();
   ::enter_env(inv,from);
}
 
//---------------------------------------------------------------------------
// update_srstaff
//---------------------------------------------------------------------------
void update_srstaff() 
{
    set_short(sshort);
    set_long(slong);
    set_hit(bhit);
    set_pen(bpen);
    set_name("staff");
    add_name(SR_STAFF_ID);
    set_hands(W_RIGHT);
    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);
    add_prop(OBJ_I_NO_STEAL,1);
    set_wf(TO);
}
 
//---------------------------------------------------------------------------
// create_khalakhor_weapon
//---------------------------------------------------------------------------
void create_khalakhor_weapon() 
{
	//set default descriptions
	set_sshort("tall ornately-carved staff");
	set_slong("It is a tall oak staff, ornately carved with shamrocks and "+
		      "runes along its length, and topped with a gold tricircum "+
			  "talisman.\n");
    update_srstaff();
}
 
//---------------------------------------------------------------------------
// do_rewield - check if already wieldable in indicated hand, then rewield
//---------------------------------------------------------------------------
void do_rewield(int which, string errmsg) 
{
   mixed  rc;
   int old=query_hands();
   string pro=HIS_HER(TP), rhstr, pstr;
 
   // if already wielded in this hand, give message
   if (old==which)
      {
      write("The "+query_name()+" is already wielded "+errmsg+".\n");
      return 0;
      }
 
   // try to quietly unwield the weapon
   rc = (TP->unwield(TO));
   if (stringp(rc)) { write(rc+"\n"); return; }
 
   // switch the hands
   set_hands(which);
   wielded_in_hand=which;
 
   // try to quietly wield the weapon in new hands
   rc=(TP->wield(TO));
   if (stringp(rc)) {
      write(rc+"\n");
      set_hands(old);
      wielded_in_hand=old;
      TP->wield(TO); // wield back the way it was
      return;
   }
   TP->update_weapon(TO);
 
   // inform all of what has happened.
   switch (which) {
      case W_LEFT:  rhstr=pro+" left hand";  pstr="your left hand"; break;
      case W_RIGHT: rhstr=pro+" right hand"; pstr="your right hand";break;
      case W_BOTH:  rhstr="both hands";      pstr=rhstr;            break;
   }
   write("You rewield the "+query_short()+" in "+pstr+".\n");
   tell_room(ENV(TP),QCTNAME(TP)+" rewields "+pro+" "+query_short()+
                      " in "+rhstr+".\n",TP);
}
 
//---------------------------------------------------------------------------
// rewield - allows player to rewield weapon in both/left/right hand(s)
//---------------------------------------------------------------------------
int rewield(string cmd) 
{
   object  wep;
   object  wielder=(query_wielded());
   object* inv=all_inventory(TP);
 
   if (!stringp(cmd))
      write("Rewield "+query_name()+" in both/left/right hand(s)?\n");
   else if ((!objectp(wielder))||(wielder!=TP))
      write("You are not wielding the "+query_name()+".\n");
   else if ((parse_command(cmd,inv,"%o %s",wep))&&(wep!=TO))
      write("Rewield what?\n");
   else if (parse_command(cmd,inv,BOTHH,wep))
      do_rewield(W_BOTH,"with both hands");
   else if (parse_command(cmd,inv,LEFTH,wep))
      do_rewield(W_LEFT,"with the left hand");
   else if (parse_command(cmd,inv,RIGHTH,wep))
      do_rewield(W_RIGHT,"with the right hand");
   else
      write("Rewield "+query_name()+" in which hand(s)?\n");
   return 1;
}
 
//---------------------------------------------------------------------------
// init - add commands
//---------------------------------------------------------------------------
void init() 
{
   ::init();
   add_action(&rewield(),"rewield");
}
