/*
**   ARGOS - Metro - Name Server
**   This is not a real room. It's purpose is to provide Argosian NPCs
**   with unique names via calls to this object. These functions work
**   in concert with the names.c file in the monsters dir which is included
**   by each NPC which uses these services.
**   A name is requested by the NPC object when it is cloned, which is
**   randomly selected and removed from the list maintained here. The
**   name is then returned to the list when the NPC is removed/dies.
**   This object coded as a room to ensure no multiple copies.
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   9/17/95    Zima       Created
**  27/2/02     Maniac     Just banished the names in the lists here 
**                         except for ones already taken by players, 
**                         which I removed from the lists. Please don't 
**                         add any more names, there are quite enough.
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/*
** Initial List of Names; resorted to if current lists are empty
*/
#define INIT_MALE_NAMES ({                                              \
   "Borus", "Scamandrius", "Strophius", "Atreus", "Meriones", "Tecton", \
   "Phereclus", "Harmon", "Meges", "Eurypylus", "Euaemon", "Hypsenor",  \
   "Tydeus", "Lycaon", "Sthenelus", "Hypeiron", "Xanthus", "Echemmon",  \
   "Diocles", "Crethon", "Mydon", "Atymnius", "Sarpedon",               \
   "Agamemnon","Bartolonos","Chimeran","Eulogio","Festus","Grammaeus",  \
   "Hermes","Iconium","Jarius","Kalodimos","Linus","Matteo",            \
   "Neapolese","Orenes","Perecles","Quethelen","Satiranus",   \
   "Telecles","Upemeno","Vulcanus","Zaosteles"                 \
 })
 
#define INIT_FEMALE_NAMES ({                                             \
   "Altara","Bithnia","Chemena","Demetria","Eistata","Felecia","Gemiste",\
   "Hellena","Iconia","Kaldina","Lostosia","Matria",           \
   "Novena","Olympia","Pericla","Quartena","Saldeae","Thistes","Umana",  \
   "Voltrias","Xenas","Zena"                                             \
})
 
/*
** Current lists of male/female names
*/
string *MaleNames;
string *FemaleNames;
 
/* just for testing */
string query_lists() {
   string X;
   X="\nMale Names: "+(implode(MaleNames,", "))+"\n";
   X=X+"\nFemale Names: "+(implode(FemaleNames,", "))+"\n";
   return (X);
}
 
/*
** request_name: Called in an NPC to get a name for the NPC when cloned
** parameter:    Gender of the NPC
** note:         If the current list is empty, picks a name from the
**               initial list
*/
string request_name(int gender) {
   string aname;
   if (gender) /* female name */
      if (sizeof(FemaleNames)==0)
         aname=(INIT_FEMALE_NAMES[(random(sizeof(INIT_FEMALE_NAMES)))]);
      else {
         aname=FemaleNames[(random(sizeof(FemaleNames)))];
         FemaleNames=FemaleNames-(({aname}));
      }
   else
      if (sizeof(MaleNames)==0)
         aname=(INIT_MALE_NAMES[(random(sizeof(INIT_MALE_NAMES)))]);
      else {
         aname=MaleNames[(random(sizeof(MaleNames)))];
         MaleNames=MaleNames-(({aname}));
      }
   return aname;
}
 
/*
** return_name: Returns the name of an NPC which has left the game to the
**              name list. (called from remove_object() in NPC)
** Parameters:  aname - the name to be returned to the list
**              gender - gender of the NPC
** Note:        won't return a name to the list if that name is already
**              in the current list. Don't allow return of name not from
**              original list.
*/
void return_name(string aname, int gender) {
   /* don't allow return of null or funky Ob_xxx names */
   if (!(aname)) return;
 
   if (gender) { /* return female name */
      if (member_array(aname,INIT_FEMALE_NAMES)==-1) return;
      if (member_array(aname,FemaleNames)==-1)
         FemaleNames=FemaleNames+(({aname}));
      }
   else { /* return male name */
      if (member_array(aname,INIT_MALE_NAMES)==-1) return;
      if (member_array(aname,MaleNames)==-1)
         MaleNames=MaleNames+(({aname}));
      }
}
 
void init_lists() {
   MaleNames=(INIT_MALE_NAMES);
   FemaleNames=(INIT_FEMALE_NAMES);
}
 
/* room definition */
void create_room() {
   set_short("Name Server Room");
   set_long(
      "This is the Name Server Room for Argos. This is not a real "+
      "room that mortals can get to. There is a list of the currently "+
      "available names on the wall.\n");
   add_item("list","@@query_lists");
   init_lists();
}
