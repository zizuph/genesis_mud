
/* This file is /d/Shire/orcorc/orc_soul.c 
 *
 * Intended for use by the Tribe of Azog of
 * Moria.
 *   Apologies to Elessar of Gondor for shamelessly stealing
 *   from his rangersoul. *grin*
 *
 *   Dunstable, July 1994
 *
 */

#pragma save_binary

inherit "/cmd/std/command_driver";
#include <macros.h>
#include <formulas.h>
#include "sys/orc.h"
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
#include "sys/olist.h"
#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))



string
get_soul_id()
{
   return "Tribe of Azog";
}

int
query_cmd_soul()
{
   return 1;
}

mapping
query_cmdlist()
{

   setuid();
   seteuid(getuid());

   return ([
     "bare"    : "bare",
     "clench"  : "clench",
     "grasp"   : "grasp",
     "help"    : "help",
     "hiss"    : "hiss",
     "orclist" : "list_active_orcs",
     "punch"   : "punch",
     "rough"   : "rough",
     "shove"   : "shove",
     "sneer"   : "sneer",
     "thrash"  : "thrash"
     ]);

/* The above are in the form: command : function */

}

int
bare(string str)
{
   if(!strlen(str))
   {
    write("Bare what, your tusks?\n");
    return 1;
   }
   if(str != "tusks")
   {
    write("You can't bare your "+str+", stupid!\n");
    return 1;
   }

   write("You bare your tusks menacingly, showing everyone you mean business.\n");
   say(QCTNAME(TP)+ " bares his tusks menacingly.\n");
   return 1;

}


int
clench()
{
   write("You clench your fists, preparing them for battle.\n");
   say(QCTNAME(TP) + " clenches "+HIS_HER(TP)+" fists "+
   "menacingly.\n");
   return 1;
}


int
grasp(string str)
{
   object *oblist;
   
   if(!strlen(str))
   {
    write("You grasp nothing but thin air.\n");
    say(QCTNAME(TP) + " grasps the very air, in futility.\n");
    return 1;
   }

   oblist = parse_this(str, "[the] %l");
   if(!sizeof(oblist))
   {
    write("Grasp whom?\n");
    return 1;
   }

   actor("You grasp ",oblist,"by the neck and pull them to you.");
   target(" grasps you by the neck and pulls you to him, a gasp of air "+
   "escaping your clutched throat.",oblist);
   all2act("quickly grasps",oblist, " by the throat.\n");
   return 1;

}

int
help(string str)
{
   if(str != "orc") return 0;
   write("The Tribe of Azog have the following emotions "+
   "At their command: \n"+
   "bare tusks: bare your tusks\n"+
   "clench    : clench your fists\n"+
   "grasp     : take hold of someone by the neck\n"+
   "help      : this menu\n"+
   "hiss      : say something like an orc would\n"+
   "orclist   : see which other of the Tribe of Azog are on\n"+
   "punch     : let 'em have it!\n"+
   "rough     : treat someone with the respect they deserve\n"+
   "shove     : give 'em a push!\n"+
   "thrash    : really intimidate your enemy!\n");
   return 1;
}

int
hiss(string str)
{
   if(this_player()->query_prop(LIVE_M_MOUTH_BLOCKED))
   {
     write("You can't seem to hiss in your condition.\n");
     return 1;
   }
   
   say(QCTNAME(TP)+ " hisses viciously from "+HIS_HER(TP)+" clenched teeth: "+ str +"\n");
   write("You hiss: "+str+"\n");
   return 1;
}




int
punch(string str)
{
   object *oblist;
   if(!strlen(str))
   {
    write("Deliver a punch to whom?\n");
    return 1;
   }

   oblist = parse_this(str, "[the] %l");

   if(!sizeof(oblist))
   {
    write("You don't seem to want to punch that person.\n");
    return 1;
   }

   actor("You whallop",oblist," powerfully, daring them to fight.");
   target(" suddenly punches you with force- your face throbs!",oblist);
   all2act("punches",oblist," powerfully, challenging a fight.");
   return 1;

}



int
rough(string str)
{
   object *oblist;
   if(!strlen(str))
   {
     write("Who did you want to rough up?\n");
     return 1;
   }
   oblist = parse_this(str, "[the] %l");

   if(!sizeof(oblist))
   {
     write("Who did you want to rough up?\n");
     return 1;
   }

     actor("You take",oblist," and shake them roughly.");
   target(" grabs you and shakes you up roughly",oblist);
   all2act("grabs",oblist, " and shakes them roughly.");
     return 1;
}


int
shove(string str)
{
   object *oblist;
   if(!strlen(str))
   {
    write("Shove whom?\n");
    return 1;
   }

   oblist = parse_this(str, "[the] %l");

   if(!sizeof(oblist))
   {
    write("Shove whom?\n");
    return 1;
    }

   actor("You intimidatingly shove",oblist,", who stumbles back unsteadily.");
   target(" shoves you forcefully, causing you to stumble back unsteadily.",oblist);
   all2act("forcefully shoves",oblist,", who has to stumble to retain balance.");
   return 1;
}



int
sneer()
{
    write("You curl your upper lip in derision.\n");
    all(" sneers evilly, baring "+HIS_HER(TP)+" teeth in the process.");
    return 1;
}



// Some routines taken directly from 'tackle'.
int
thrash(string str)
{
   object *oblist;

   if(!strlen(str))
   {
    write("You have to choose a target to thrash.\n");
    return 1;
   }

     oblist = parse_this(str, "[the] %l");

     if (!sizeof(oblist))
     {
    notify_fail("Thrash whom?\n");
    return 0;
     }

     if ((F_DARE_ATTACK(this_player(),oblist[0]) && (random(10) > 3)))
     {    
        target(" comes running at you with a sudden ferocity.\n" +
        capitalize((string) this_player()->query_pronoun()) +
        " pushes you hard and you stumble backwards, your arms waving for balance.\n" +
        "You fall to the ground painfully.", oblist);
        actor("You violently thrash", oblist);
        all2act("thrashes", oblist, ".\n" + ((sizeof(oblist) > 1) ? "They stumble":
        capitalize((string) oblist[0]->query_pronoun()) + " stumbles") +
        " backwards, waving rapidly for balance, then falling painfully.");

     }
     else
     {
            target(" comes running at you with a sudden ferocity.\n" +
       capitalize((string) this_player()->query_pronoun()) +
       " misses as you side-step quickly, falling flat on the ground.", oblist);
       actor("You try to thrash", oblist, " but they stepped out of the way.");
       all2act("tries to thrash", oblist, " but the victim moved suddenly out of the way!");
       all(" falls suddenly on " + this_player()->query_possessive() + " face.");

     }

     return 1;
 }

