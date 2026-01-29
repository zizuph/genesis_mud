//
// Breviary - book of canticles/prayers/spells - GUILD OBJECT!!
//
// 01/06/00 Zima	Created
//
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define  NAHUAIRE_STEP       5.0
#define  NAHUAIRE_HARMONY	 1
#define  NAHUAIRE_INTERVAL	 1800.0

inherit SR_BOOK_BASE;
inherit GEN_MAGIC+"spellcasting";

int    nhn=0;		//step of the prayer. 0->not doing this prayer
object room;		//room in which prayer begins and must be done
object saggart;		//saggart doing the prayer
int    naDone=0;	//have done prayer for a time period

//---------------------------------------------------------------------------
// create_book
//---------------------------------------------------------------------------
void create_book()
{
   title="Breviary of the Order of Sean-Rhian";
   set_short("black leather-bound book");
   add_name(({"breviary",GUILD_OBJ}));
   add_adj(({"black","leather-bound"}));
   set_long("It is a black leather-bound book entitled: "+title+".\n");
   set_max_pages(1);
   set_book_file("breviary.txt");

   //protect the guild object!
   add_prop(OBJ_I_NO_DROP,1);
   add_prop(OBJ_I_NO_STEAL,1);
   add_prop(OBJ_I_NO_SELL,1);

   //add spells
   add_spell(SR_SPELL_GLOR);
   add_spell(SR_SPELL_LEUS);
   add_spell(SR_SPELL_TINE);
   add_spell(SR_SPELL_STUA);
   add_spell(SR_SPELL_SITHEAN);

}

//---------------------------------------------------------------------------
// enter_env and leave_env
//---------------------------------------------------------------------------
void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    add_spell_object(env);
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    remove_spell_object(env);
}


//---------------------------------------------------------------------------
// reset_naHuaire - set flag to 0, indicating time interval for next prayer 
//					opportunity has elapsed
//---------------------------------------------------------------------------
void reset_naHuaire()     { naDone=0;      }

//---------------------------------------------------------------------------
// some query functions
//---------------------------------------------------------------------------
int    query_naHuaire_done()    { return naDone;  }
int    query_naHuaire_step()    { return nhn;     }
object query_naHuaire_room()    { return room;    }
object query_naHuaire_saggart() { return saggart; }

//---------------------------------------------------------------------------
// step_naHuaire - do one step of the prayer
//---------------------------------------------------------------------------
void step_naHuaire()
{
	string pos=(saggart->query_possessive());
	string msg;
	int	   harmony;

	//check if should do next step
	if (!nhn)			    return;	//if not praying anymore, quit
	if (ENV(TO)!=saggart)   return;	//saggart must still have breviary
	if (ENV(saggart)!=room)			//saggart must stay in same room
	{
		saggart->catch_msg("You have broken the stillness of your meditation.\n");
		nhn=0;
		return;
	}

	//create the verse
	msg="You trace the tricircum before your face and pray:\n   Luaidh bi ";
	switch (nhn)
	{
	case 1: msg+="Argante, seer of all mysteries!";						break;
	case 2: msg+="Rhiannon, princess of the clouds!";					break;
	case 3: msg+="Kesair, who stirs the living water of the earth!";	break;
	case 4: msg+="Irgalach, defender of the faith, conquerer of evil!"; break;
	case 5: msg+="Seanchan Tor, high priest of the Most High!";			break;
	case 6: msg+="Camulos, who traverses the skies and seas!";			break;
	case 7: msg+="Ambisargus, who is given all knowledge!";				break;
	case 8: msg+="Secnasach, who rules the elements of the earth!";		break;
	case 9: msg+="Ragallach, who brings the purifying fire!";			break;
	case 10:msg+="Maighal the Archangel, High Servant of Ardaugh!";		break;
	case 11:msg+="Ardaugh the Most High, Order forever and ever!";		break;
	case 12:msg+="Ardaugh agus Maighal agus an Solsheyderi, amen!";		break;
	case 13://finish the prayer
		    saggart->catch_msg(
				     "You raise your head and arise from meditation.\n");
			tell_room(ENV(saggart),QCTNAME(saggart)+" raises "+pos+" head "+
				      "and rises from meditation.\n",saggart);
			if (!naDone) //if haven't done prayer in a while
			{
				saggart->catch_msg("You increase in Harmony with Ardaugh.\n");
				harmony=(saggart->query_skill(SS_SR_HARMONY));
				harmony+=NAHUAIRE_HARMONY;
				saggart->set_skill(SS_SR_HARMONY,harmony);
				naDone=1;
				set_alarm(NAHUAIRE_INTERVAL,0.0,&reset_naHuaire());
			}
			nhn=0;
			return;
	default: //a big error!
		nhn=0;
		saggart->catch_msg("You feel a grave error in Na Huaire!-"+nhn+"\n");
		return;
	}

	//write messages
	tell_room(ENV(saggart),QCTNAME(saggart)+" traces a three circles before "
			  +pos+" face and mumbles a prayer.\n",saggart);
	saggart->catch_msg(msg+"\n");

	//schedule next step
	nhn++;
	set_alarm(NAHUAIRE_STEP,0.0,&step_naHuaire());
}

//---------------------------------------------------------------------------
// do_naHuaire - command to start or stop the Na Huaire (Hourly) prayer
//---------------------------------------------------------------------------
int do_naHuaire(string parm)
{
	//only a saggart possessing breviary can do the prayer
	if ((!(TP->is_saggart()))||(ENV(TO)!=TP))
		return 0;

	//may be wanting to stop the prayer
	if (parm=="stop")
	{
		write("You interrupt your prayer and come out of meditation.\n");
		nhn=0;
		return 1;
	}

	//if already praying, ignore command
	if (nhn>0)
	{
		write("You are already in prayer and meditation.\n");
		return 1;
	}

    //start the prayer
	saggart=TP;
	write("You bow your head and begin to meditate in prayer.\n");
	tell_room(ENV(TP),QCTNAME(TP)+" bows "+(TP->query_possessive())+" head and "+
		      "begins to meditate in prayer.\n",saggart);
	nhn=1;
	room=ENV(TP);
	set_alarm(NAHUAIRE_STEP,0.0,&step_naHuaire());
	return 1;
}

//---------------------------------------------------------------------------
// list_spells - invoked when player does 'spells'
//---------------------------------------------------------------------------
public void
list_spells()
{
	write("-------------------------------------------------------------------\n");
	write("            The Order of Saggarts of Sean-Rhian                    \n");
	write("-------------------------------------------------------------------\n");
	::list_spells();
	write("-------------------------------------------------------------------\n");
}

//---------------------------------------------------------------------------
// init
//---------------------------------------------------------------------------
void init() 
{
   ::init();
   add_action(&do_naHuaire(),"nahuaire");
}


