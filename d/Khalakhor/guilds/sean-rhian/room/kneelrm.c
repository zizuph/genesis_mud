/* Kneeling room - room can inherit this to implement kneeling
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 5/30/98     Zima        Created
** 7/20/98     Zima        Added support for prostrate
*/
/* inherits/includes */
inherit "/d/Khalakhor/std/room";
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"
#define  KNEELING "_iam_kneeling"
#define  TPN      QCTNAME(TP)
 
string   kneel_before; // name of object kneeling before, if any
string   ing_form   = "kneeling";
string   verb_form  = "kneel";
string   verb_forms = "kneels";
int      pos;
 
//
// create_khalakhor_room()
//
void create_khalakhor_room()
{
   set_short("Base Kneeling Room");
   set_long("   This is the base kneeling room.\n");
}
 
//
// set_verbs
//
void set_verbs(string verb)
{
   if ((verb=="prostrate")||(verb=="lie")||(verb=="lay")) //allow bad english
      {
      ing_form   = "lying prostrate";
      verb_form  = "lie prostrate";
      verb_forms = "lies prostrate";
      pos        = 2;
      }
   else
      {
      ing_form   = "kneeling";
      verb_form  = "kneel";
      verb_forms = "kneels";
      pos        = 1;
      }
}
 
//
// kneel
//
int kneel(string cmd)
{
   set_verbs(query_verb());
 
   if (TP->query_prop(KNEELING))
      write("You are already "+ing_form+".\n");
   else if (stringp(kneel_before))
      {
      write("You "+verb_form+" reverently before "+kneel_before+".\n");
      tell_room(TO,TPN+" "+verb_forms+" reverently before "+
                   kneel_before+".\n",TP);
      }
   else
      {
      write("You "+verb_form+" down on the ground.\n");
      tell_room(TO,TPN+" "+verb_forms+" down on the ground.\n",TP);
      }
   TP->add_prop(KNEELING,pos);
   return 1;
}
 
//
// rise
//
int rise(string cmd)
{
   int mypos = (TP->query_prop(KNEELING));
   if (!mypos)
      write("You are not kneeling.\n");
   else if (mypos==2)
      {
      write("You rise from lying prostrate on the ground.\n");
      tell_room(TO,TPN+" rises from lying prostrate on the ground.\n",TP);
      TP->remove_prop(KNEELING);
      }
   else
      {
      write("You rise from kneeling.\n");
      tell_room(TO,TPN+" rises from kneeling.\n",TP);
      TP->remove_prop(KNEELING);
      }
   return 1;
}
 
//
// check_kneeling - vbfc this function in all exits
//
int check_kneeling()
{
   if (!(TP->query_prop(KNEELING))) return 0;
   write("You must rise first.\n");
   return 1;
}
 
//
// kneeling - is this player kneeling?
//
int kneeling(object tp) { return (tp->query_prop(KNEELING)); }
 
//
// init - add actions to the room
//
void init()
{
   ::init();
   add_action(&kneel(),"kneel");
   add_action(&rise(), "rise");
}
