//---------------------------------------------------------------------------
// Cloud of incense
//---------------------------------------------------------------------------
// - produced by smoke from a burning censor
// - an invisible object
// - adds a sentence to the room its in, describing the strength of
//   the incense here (add_my_desc(), change_my_desc(), remove_my_desc())
// - strength determines descriptions and remaining life of cloud
// - strength increased by a smoking censor (see: tool/censor.c::check_cloud()
// - strength decreased over time by recursive calls of weaken().
// - cloud auto-destructs when str weakens to 0 
// - maximum time limit of 10 minutes when cloud used as part of a spell,
//   beginning when the spell effect is started
// - this object responsible for dispelling the spell object
//
// History:
// Date        Coder       Action
//----------   ----------- ----------------------------------
// 5/16/98     Zima        Created
// 1/12/00	   Zima        recoded to be target of a spell effect
//
//
inherit "/std/object";
#include <stdproperties.h>
#include "defs.h"
#define  WEAKEN_TIME  30.0

//---------------------------------------------------------------------------
//							global variables
//---------------------------------------------------------------------------
public int      str=0;		// strength (lifetime left factor) of cloud, 0-20
public object   spell_eff;	// associated spell effect object, if any
 
 
//---------------------------------------------------------------------------
//				simple set and query functions for globals
//---------------------------------------------------------------------------
public void   set_str(int i)               { str=i;            }
public int    query_str()                  { return str;       }
public object query_spell_effect_object()  { return spell_eff; }

//---------------------------------------------------------------------------
//							added_rm_desc   
//---------------------------------------------------------------------------
// returns: depending on str, return desc to be added to room 
string added_rm_desc()
{
   string d;
   switch (str)
   {
   case 0..2:  d="There is a faint fragrance of incense";            break;
   case 3..4:  d="There is a strong fragrance of incense";           break;
   case 5..6:  d="Wisps of fragrant white incense swirl";            break;
   case 7..8:  d="Thick wisps of fragrant white incense swirl";      break;
   case 9..10: d="There is a thin cloud of fragrant white incense";  break;
   case 11..12:d="There is a fragrant cloud of smoky white incense"; break;
   default:    d="There is a thick cloud of fragrant white incense"; break;
   }
	return(d+" in the air here.\n");
}

//---------------------------------------------------------------------------
//								cshort  
//---------------------------------------------------------------------------
// returns: depending on str, return short desc used in messages
string cshort()
{
   string d;
   switch (str)
   {
   case 0..2:   d="faint fragrance of incense";            break;
   case 3..4:   d="strong fragrance of incense";           break;
   case 5..6:   d="wisps of fragrant white incense ";      break;
   case 7..8:   d="thick wisps of fragrant white incense"; break;
   case 9..10:  d="thin cloud of fragrant white incense";  break;
   case 11..12: d="fragrant cloud of smoky white incense"; break;
   default:     d="thick cloud of fragrant white incense"; break;
   }
   return d;
}

//---------------------------------------------------------------------------
//								remove_cloud 
//---------------------------------------------------------------------------
// Function: removes spell effect object (if any); removes added room desc
void remove_cloud()
{
	object rm = ENV(TO);

	//if there is a spell effect associated with cloud, stop it
	if (objectp(spell_eff))
	{
		spell_eff->dispel_spell_effect(TO);
	}

	// if in a room, inform inhabitants and remove added msg from desc
	if (objectp(rm) && (rm->query_prop(ROOM_I_IS)))
	{
		tell_room(rm,
			"The "+cshort()+" disappears from the air.\n");
		rm->remove_my_desc(TO);
	}
}

//---------------------------------------------------------------------------
//								remove_object
//---------------------------------------------------------------------------
// Function: masks stdobject function; invoke remove_cloud when dested
void remove_object()
{
	remove_cloud();
	::remove_object();
}

//---------------------------------------------------------------------------
//							set_spell_effect_object  
//---------------------------------------------------------------------------
// Arguments: seo     - the associated spell effect object
//			  max_sec - the maximum life of the cloud, in seconds
// Function:
// - should be invoked by the start() function of the spell effect object.
// - dispel_spell_effect() is invoked in the given object when the cloud is
//   destroyed. (see remove_object() below)
// - Since clerics could maintain the life of the cloud indefinitely, by
//   using more than one cake of incense and/or censor (allowed for  
//   ritualistic and emotive reasons), this function sets a time
//   limit on the life of the cloud when used in conjunction with a 
//   spell effect                       
public void set_spell_effect_object(object seo, float max_sec) 
{ 
	spell_eff = seo;
	set_alarm(max_sec,0.0,&remove_object());
}

//---------------------------------------------------------------------------
//									weaken  
//---------------------------------------------------------------------------
// Function: decrements the strength fo the cloud
//			 resets added room description
//			 destructs cloud if weakened to non-existence
void weaken()
{
   object rm=ENV(TO);
 
   // check if cloud not in room or is disappearing
   if ((!(rm->query_prop(ROOM_I_IS))) || (str<=0))
   {
	   remove_object();
	   return;
   }

   // decrease the strength factor; double if outside where wind would
   // disperse the cloud
   str--;
   if (!(rm->query_prop(ROOM_I_INSIDE))) str--;
  
   // change the additional descr. in room set by cloud
   rm->change_my_desc(added_rm_desc(),TO);
 
   // schedule the next weaken
   set_alarm(WEAKEN_TIME,0.0,&weaken());
}
 
//---------------------------------------------------------------------------
//								strengthen  
//---------------------------------------------------------------------------
// Function: strengthen the cloud & update the added room desc
//           invoked by the censor
void strengthen()
{
   object rm=ENV(TO);
 
   // if not in a room, we're outta here!
   if (!(rm->query_prop(ROOM_I_IS))) 
   {
	   remove_object();
	   return;
   }

   // increment the strength of the cloud, max 20
   str++;
   if (str>20) 
	   str=20;

   // update added room description
   rm->change_my_desc(added_rm_desc(),TO);
}
 
//---------------------------------------------------------------------------
//									startup  
//---------------------------------------------------------------------------
// Function: starts the cloud "billowing" process
//           invoked by the cloning object (censor)  
void startup()
{
   object rm=ENV(TO);
   if (!(rm->query_prop(ROOM_I_IS))) return;
   str=1;
   rm->add_my_desc(added_rm_desc(),TO);
   tell_room(rm,"The air fills with the fragrant scent of incense.\n");
   set_alarm(WEAKEN_TIME,0.0,&weaken());
}
 
//---------------------------------------------------------------------------
//								create_object
//---------------------------------------------------------------------------
void create_object()
{
    set_name(SR_INC_CLOUD);
    add_name("cloud");
    set_short("cloud of incense");
    set_long("Invisible cloud of incense.\n");
    add_prop(OBJ_I_NO_GET,1);
    add_prop(OBJ_I_INVIS,1);
}
 
//---------------------------------------------------------------------------
//								do_smell  
//---------------------------------------------------------------------------
// Function: allows player to smell/sniff/inhale the incense
int do_smell(string cmd)
{
   string verb=query_verb(),msg;
 
   notify_fail(capitalize(verb)+" what?\n");
   if (!stringp(cmd)) return 0;
   if (!parse_command(cmd,(all_inventory(TP)),
      "'fragrance' / 'air' / 'cloud' / 'incense' / 'smoke' / 'whisps'"))
      return 0;
 
   write("You "+verb+" the air, filling your nostrils with the fragrant "+
         "smell of incense.\n");
   return 1;
}
 
//---------------------------------------------------------------------------
//								init  
//---------------------------------------------------------------------------
// Function: add user commands
void init()
{
   ::init();
   add_action(&do_smell(),"smell");
   add_action(&do_smell(),"sniff");
   add_action(&do_smell(),"inhale");
}
