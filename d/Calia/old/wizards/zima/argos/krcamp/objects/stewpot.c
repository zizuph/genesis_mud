/* A stew pot found throughout the kretan encampment
**
** Date     Coder       Action
** -------- ----------- ---------------------------------------
** 8/15/96  Zima        Created
*/
inherit "std/object";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"
#include "stew.h"
#define  MAX_STEW_AMT 5
 
int      stew_amt=0;   /* # "bites" of stew in pot */
 
/* prototypes */
void set_stew_long();
void set_stew_amt(int amt);
void reset_stew();
int  query_stew_amt();
 
void create_object() {
    set_name("stewpot");
    add_name("pot");
    set_adj(({"large","iron"}));
    set_short("large iron stewpot");
    set_stew_amt(MAX_STEW_AMT); /* sets long desc of pot */
 
    add_item(({"stew","stew in pot","stew from pot"}),
               "@@exa_stew");
    add_cmd_item(({"stew","stew in pot","stew from pot"}),
                ({"smell","sniff"}), "@@smell_stew");
    add_cmd_item(({"stew","stew in pot","stew from pot"}),
                "taste", "@@taste_stew");
    add_item("fire",
             "It is a small fire heating the pot.\n");
 
    add_prop(OBJ_I_WEIGHT, 200000);
    add_prop(OBJ_M_NO_GET, "It is too heavy to lift.\n");
    add_prop(OBJ_M_NO_INS, "It is too heavy to lift.\n");
}
 
/*
** RESET_STEW - initialize the stew pot
** QUERY_STEW_AMT - how much stew is in the pot?
*/
void reset_stew()     { set_stew_amt(MAX_STEW_AMT); }
int  query_stew_amt() { return stew_amt; }
 
/*
** SET_STEW_AMT - set the amount of stew and change the desc of the pot
*/
void set_stew_amt(int amt) {
   if ((amt<0)||(amt>MAX_STEW_AMT)) stew_amt=0; else stew_amt=amt;
   set_stew_long();
}
 
 
/*
** SET_STEW_LONG - set the long desc of the pot, indicating the amt of stew
*/
void set_stew_long() {
    string desc;
    switch (stew_amt) {
       case 5:  desc="It is brimming with steaming hot stew.\n";    break;
       case 4:  desc="It is almost full of hot stew.\n";            break;
       case 3:  desc="It is half full of warm stew.\n";             break;
       case 2:  desc="It has a little warm stew left in it.\n";     break;
       case 1:  desc="It is almost empty, only a bit of cold stew remains.\n";
                break;
       default: desc="It is empty, only a coating of stew on the inside.\n";
    }
    desc="It is a large iron pot sitting over a small fire, used for "+
         "cooking. "+desc;
    this_object()->set_long(desc);
}
 
/*
** EXA_STEW - describe the stew in the pot
*/
string exa_stew() {
   if (stew_amt>0)
      return("It is a thick stew made with vegetables, herbs, and some kind "+
             "of meat. It looks good, but perhaps you should smell or taste "+
             "it first.\n");
   else
      return ("There is no stew left in the pot, only a thin coating "+
              "of its former contents.\n");
}
 
/*
** DO_SMELL - allow the player to smell the stew in the pot
*/
int do_smell(string Parms) {
    object Tp=this_player();
    object Tr=environment(Tp);
    string *Parm;
 
    /* must specify stew in pot */
    if (!(Parms)) return 0;
    Parm=explode(Parms," ");
    if (member_array("stew",Parm)==-1) {
       write("Smell what?\n");
       return 1;
    }
 
    tell_room(Tr,QCTNAME(Tp)+" bends over and smells the stew in the pot.\n",
              Tp);
    write("You bend over the pot and smell the stew.\n");
    write("It is not your mother's cooking, but it smells hearty.\n");
    return 1;
}
 
/*
** DO_TASTE - allow the player to taste the stew in the pot
*/
int do_taste(string Parms) {
    object Tp=this_player();
    object Tr=environment(Tp);
    string *Parm;
 
    /* must specify stew in pot */
    if (!(Parms)) return 0;
    Parm=explode(Parms," ");
    if (member_array("stew",Parm)==-1) {
       write("Taste what?\n");
       return 1;
    }
 
    tell_room(Tr,QCTNAME(Tp)+" dips "+(Tp->query_possessive())+" finger in "+
              "the pot and tastes the stew.\n",Tp);
    write("You dip you finger in the pot and tast the stew.\n");
    write("It could use a little more spice, but it tastes wholesome.\n");
    return 1;
}
 
/*
** DO_EAT
** allows player to eat stew from pot, if has spoon
*/
int do_eat(string Parms) {
   object Tp=this_player();
   object Tr=environment(Tp);
   object spoon=present("spoon",Tp);
   object stew_obj;
   string *Parm;
 
   /* must specify stew in pot */
   if (!(Parms)) return 0;
   Parm=explode(Parms," ");
   if ((member_array("stew",Parm)==-1) ||
      ((member_array("pot",Parm)==-1)&&(member_array("stewpot",Parm)==-1)))
      return 0;
 
   /* must be stew in pot and must have any spoon */
   if (!stew_amt)
      { write("There is no stew left in the pot!\n"); return 1; }
   if (!spoon)
      { write("You'll need a spoon to eat from the pot.\n"); return 1;}
 
   /* have player eat spoonful of stew */
   if (Tp->eat_food(75)) {
      write("You eat some of the stew from the pot.\n");
      tell_room(Tr,QCTNAME(Tp)+" eats some stew from the pot.\n",Tp);
      Tp->add_hp(10+random(10));
      write("You feel nourished by the hearty stew.\n");
      set_stew_amt((stew_amt-1));
   }
   else { /* unable to eat food...too full maybe? */
      write("You try to eat some stew from the pot, but you are too full.\n");
   }
 
   return 1;
}
 
/*
** DO_STIR - allow player to stir stew in pot if has spoon
*/
int do_stir(string Parms) {
    object Tp=this_player();
    object Tr=environment(Tp);
    object Spoon=present("spoon",Tp);
    string *Parm;
    string SpoonShort;
 
    /* must specify stew in pot & must have spoon */
    if (!(Parms)) return 0;
    Parm=explode(Parms," ");
    if (member_array("stew",Parm)==-1) { write("Stir what?\n"); return 1; }
    if (!Spoon) {write("You'll need a spoon to stir the stew.\n"); return 1; }
    SpoonShort=(Spoon->query_short());
 
    tell_room(Tr,QCTNAME(Tp)+" stirs the stew in the pot with "+
                "a "+SpoonShort+".\n",Tp);
    write("You stir the stew in the pot with the "+SpoonShort+".\n");
    return 1;
}
/*
** INIT
** include commands with object
*/
void init() {
   add_action("do_eat",   "eat");
   add_action("do_smell", "smell");
   add_action("do_stir", "stir");
   add_action("do_taste", "taste");
}
