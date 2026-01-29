inherit "/std/object";

#include "stdproperties.h"
#include "/d/Shire/common/defs.h"
#include <smiths.h>

string giver="";
string given_to="";

void
create_object() {
   set_name(({"figurine","bear figurine"}));

   set_long("This small figurine is made from solid metal."+
      " All details are fabulously chiseled into the metal. Use <help"+
      " figurine> to see the commands usable on it.\n");

   add_prop(OBJ_I_WEIGHT,500);
   add_prop(OBJ_I_VOLUME,100);
   add_prop(OBJ_I_VALUE,100);
}

init() {
   ::init();

   add_action("help","help");
   add_action("stroke","stroke");
   add_action("smile","smile");
   add_action("give","give");
   add_action("throw","throw");
}

int
help(string str) {
   if (str!="figurine") return 0;

   write("This is what you think you can do with the figurine:\n");
   write("<stroke figurine>   feel the nice craftmanship.\n");
   write("<smile figurine>    smile in memory of giver of the figurine.\n");
   write("<give figurine>     give the figurine to someone as a present.\n");
   write("<throw figurine>    throw the blasted figurine away in anger.\n\n");
   return 1;
}

int
stroke(string str) {
   if (str!="figurine") return 0;

   write("You stroke the figurine lightly with your finger, enjoying the"+
      " marvelous craftmanship.\n");
   say(QCTNAME(TP)+" lets "+HIS_HER(TP)+" fingers run over the finely"+
      " chiseled details of the figurine.\n");
   return 1;
}

int
smile(string str) {
   if (str!="figurine") return 0;

   if (given_to!=TP->query_name()) {
      write("Since you were not given this figurine you cannot smile"+
         " in memory of the giver, can you?\n");
      return 1;
   }

   write("You smile in memory of "+giver+". This figurine was really a"+
      " kingly gift.\n");
   say(QCTNAME(TP)+" looks at a small figurine "+HE_SHE(TP)+" is carrying,"+
      " and smiles happily.\n");
   return 1;
}

int
give(string str) {
   string *parts;
   object *others=(({TP,}));
   object rec;

   parts=explode(str," ");

   if (parts[0]!="figurine") return 0;

   if (sizeof(parts)!=2) {
      write("The syntax is: give figurine name.\n");
      return 1;
   }

   if (parts[0]!="figurine") return 0;

   rec=find_player(parts[1]);
   if ((!rec) || (!present(rec,ENV(TP)))) return 1;

   others += ({rec});

   TP->catch_msg("You give the figurine to "+QCNAME(rec)+" as a token of"+
      " friendship.\n");
   rec->catch_msg(QCTNAME(TP)+" gives you a small metal figurine as a"+
      " token of friendship.\n");
   tell_room(QCTNAME(TP)+" gives a small figurine to "+QCNAME(rec)+" as a"+
      " token of friendship.\n",others);

   giver=TP->query_name();
   given_to=rec->query_name();
   TO->move(rec);

   return 1;
}

int
throw(string str) {
   if (str!="figurine") return 0;

   TP->command("scream");
   write("You decide to get rid of the blasted figurine once for all.\n");
   TP->command("fume");
   write("You throw the figurine away.\n");
   say(QCTNAME(TP)+" throws something away.\n");   

   TO->remove_object();

   return 1;
}
