inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

string *exit;

void create_object()
{
 set_name("_trickster_tie_object_");
 set_no_show_composite(1);
 add_prop(OBJ_M_NO_DROP,1);
}

void get_exits()
{
 string *ex;
 int i;

 exit=({});
 ex=ENV(ENV(TO))->query_exit();
 if(!sizeof(ex)) return;

 for(i=1;i<sizeof(ex);i+=3)
  {
   switch(ex[i])
    {
     case "east": exit+=({"e","east"});break;
     case "west": exit+=({"w","west"});break;
     case "south": exit+=({"s","south"});break;
     case "north": exit+=({"n","north"});break;
     case "northeast": exit+=({"ne","northeast"});break;
     case "northwest": exit+=({"nw","northwest"});break;
     case "southeast": exit+=({"se","southeast"});break;
     case "southwest": exit+=({"sw","southwest"});break;
     case "up": exit+=({"u","up"});break;
     case "down": exit+=({"d","down"});break;
     default: exit+=({ex[i]});
    }
  }
}

void init()
{
 add_action("block","",1);
 ::init();
}

int block(string what)
{
 string verb;

 verb=query_verb();
 if(verb=="untie")
  {
   NF("Untie what?? Laces on your shoes maybe?\n");
   if(!what || what!="laces") return 0;

   me("You untie laces on your shoes and can move again!");
   say(QCTNAME(TP)+" unties laces on "+POS(TP)+" shoes.\n");
   ENV(TO)->remove_tie_shadow();
   remove_object();
   return 1;
  }

 if(member_array(verb,exit)==-1) return 0;

 write("As you try to walk you fall down! Someone has tied laces on "+
   "your shoes!!\nYou'd better untie them to be able to walk again!\n");
 say("As "+QTNAME(TP)+" tried to walk "+PRO(TP)+" falls down with a "+
   "loud scream!\nYou notice laces on "+POS(TP)+" shoes are tied!!\n");
 return 1;
}

string *query_exit()
{
 return exit;
}

