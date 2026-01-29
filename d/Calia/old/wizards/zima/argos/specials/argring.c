/*
** Personal ring of zima with commands to work in the Argos area
**
** HISTORY
** Date       Action
** ---------- -----------------------------------
** 9/1/95      Created
*/
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/argos/argos.h"
#include METRO_TOURS_DEF
 
void create_armour() {
    set_name("ring");
    set_adj("argos");
    set_short("argos ring");
    add_prop(OBJ_M_NO_GIVE,1);
    add_prop(OBJ_M_NO_DROP,1);
    set_long(
       "It is an elegant gold ring with a large diamond. An inscription "+
       "written around the seeing reads: ZIMA THE HIEROPHANT OF ARGOS. "+
       "(arghelp).\n");
    set_ac(0);
    set_at(A_FINGERS);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE,   50);
}
 
int arghelp(string parms) {
   write("Argos Commands: queryprop, setprop, querybits, setbits, clearbits, "+
         "toecheck, cleartoes, argos, metro "+
         "swterr, nwterr, krcamp, palace, academie, "+
         "dephtemp, themtemp, arxtemp, phartemp, academie, arena, mclub, "+
         "logs.\n");
   return 1;
}
 
int cd(string parms) {
   string dir;
   string verb=query_verb();
   if (verb=="argos")
      dir=ARGOS_DIR;
   else if (verb=="logs")
      dir="/d/Calia/zima/log";
   else if (verb=="mclub")
      dir="/d/Calia/zima/mclub";
   else if (verb=="old")
      dir="/d/Calia/zima/argos";
   else if (verb=="clogs")
      dir="/d/Calia/log";
   else
      dir=ARGOS_DIR+verb;
 
   if (parms) dir=dir+"/"+parms;
   this_player()->command("cd "+dir);
   return 1;
}
 
void do_query_quest_prop(object Tp) {
   Tp->catch_msg("Argos tour prop is: "+(Tp->query_prop(ARGOS_TOUR_PROP))+
         ".\n");
}
 
int query_quest_prop() {
   do_query_quest_prop(this_player());
   return 1;
}
 
int set_quest_prop(string parm) {
   object Tp=this_player();
   int    val=atoi(parm);
   Tp->add_prop(ARGOS_TOUR_PROP,val);
   do_query_quest_prop(Tp);
   return 1;
}
 
void do_query_quest_bits(object Tp) {
   int bit1=Tp->test_bit(QUEST_DOM,QUEST_GROUP,QUEST_BIT1);
   int bit2=Tp->test_bit(QUEST_DOM,QUEST_GROUP,QUEST_BIT2);
   int bit3=Tp->test_bit(QUEST_DOM,QUEST_GROUP,QUEST_BIT3);
   write("Argos metro quest bits: "+(bit1)+" "+(bit2)+" "+(bit3)+".\n");
}
 
void do_toe_check(object Tp) {
   int *arr=(Tp->query_prop(TOE_QUEST_PROP));
   int i;
   write("Toe check: ");
   if (arr)
      for (i=0; i<sizeof(arr); i++) write(arr[i]+" ");
   else
      write("0");
   write("\n");
}
 
int toe_check(string parms) {
   do_toe_check(this_player());
   return 1;
}
 
int clear_toes(string parms) {
   object Tp=this_player();
   Tp->add_prop(TOE_QUEST_PROP,({0,0,0,0,0,0,0,0,0}));
   do_toe_check(Tp);
   return 1;
}
int set_bits(string parm) {
   object Tp=this_player();
   int    bits=atoi(parm);
   int    b1=(bits/100);
   int    b2=(bits-(b1*100))/10;
   int    b3=(bits-(b1*100)-(b2*10));
   if (b1) Tp->set_bit(QUEST_GROUP,QUEST_BIT1);
   else    Tp->clear_bit(QUEST_GROUP,QUEST_BIT1);
   if (b2) Tp->set_bit(QUEST_GROUP,QUEST_BIT2);
   else    Tp->clear_bit(QUEST_GROUP,QUEST_BIT2);
   if (b3) Tp->set_bit(QUEST_GROUP,QUEST_BIT3);
   else    Tp->clear_bit(QUEST_GROUP,QUEST_BIT3);
   do_query_quest_bits(Tp);
   return 1;
}
 
int query_quest_bits() {
   do_query_quest_bits(this_player());
   return 1;
}
 
int clear_quest_bits(string parm) {
   object Tp=this_player();
   Tp->clear_bit(QUEST_GROUP,QUEST_BIT1);
   Tp->clear_bit(QUEST_GROUP,QUEST_BIT2);
   Tp->clear_bit(QUEST_GROUP,QUEST_BIT3);
   do_query_quest_bits(Tp);
   return 1;
}
 
void init() {
   ::init();
   add_action("arghelp","arghelp");
   add_action("cd","argos");
   add_action("cd","metro");
   add_action("cd","krcamp");
   add_action("cd","academie");
   add_action("cd","palace");
   add_action("cd","swterr");
   add_action("cd","nwterr");
   add_action("cd","dephtemp");
   add_action("cd","themtemp");
   add_action("cd","arxtemp");
   add_action("cd","phartemp");
   add_action("cd","academie");
   add_action("cd","arena");
   add_action("cd","chorio");
   add_action("cd","mclub");
   add_action("cd","clogs");
   add_action("cd","logs");
   add_action("set_quest_prop","setprop");
   add_action("query_quest_prop","queryprop");
   add_action("toe_check","toecheck");
   add_action("clear_toes","cleartoes");
   add_action("clear_quest_bits","clearbits");
   add_action("set_bits","setbits");
   add_action("query_quest_bits","querybits");
}
 
void enter_env(object dest, object from) {
   ::enter_env(dest,from);
   if ((living(dest))&&(!(dest->id("zima")))) {
      dest->catch_msg("The ring disappears in a flash of light!\n");
      this_object()->remove_object();
   }
}
