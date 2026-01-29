// file name:    ~Avenir/common/bazaar/Obj/worn/special_hat
// creator(s):    Grace  Nov  1995
// last update:   Cirion Feb  1996
//                 -added emotes to the hat, took away
//                   weight/volume penalties
//                Most of the emotes just masks of, and similiar
//                   to, /cmd/std/soul_cmd
// purpose:       used for hats made in the hatshop tent
// note:
// bug(s):
// to-do:

inherit "/cmd/std/command_driver";
inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <adverbs.h>
#include <cmdparse.h>
#include <const.h>
#include <filter_funs.h>
#include <language.h>
#include <living_desc.h>
#include <macros.h>
#include <ss_types.h>
#include <formulas.h>

#define SOULDESC(x)       (this_player()->add_prop(LIVE_S_SOULEXTRA, (x)))
#define HIS                this_player()->query_possessive()
#define NAME               this_player()->query_name()
#define HIM                this_player()->query_objective()
#define HE                 this_player()->query_pronoun()

string adj1, adj2, adj3, adj4;

void set_adj1(string str)
{
   adj1 = str;
}

void set_adj2(string str)
{
   adj2 = str;
}

void set_adj3(string str)
{
   adj3 = str;
}

void set_adj4(string str)
{
   adj4 = str;
}

void initialize_cloak()
{
   if(!adj1) adj1 = "special";    //crests, embroidery, etc
   if(!adj2) adj2 = "blue";       //colors...
   if(!adj3) adj3 = "flowing";    //desc - hooded, collared
   if(!adj4) adj4 = "wool";       //material - wool, linen, silk, leather
   
set_short(""+adj1+" "+adj2+" "+adj3+" "+adj4+" cloak");
   
   set_long("This is a fine "+adj4+" cloak. The quality of the " +
      "craftsmanship is consistent with what one would expect " +
      "of a cloak made by Corista ip Sanctuary.\n" +
      "There is a small silver tag sewn to the inside of it.\n");
   
   add_item(({"tag"}), "The tag reads: Hand-crafted especially for ~ " +
      capitalize(NAME) + " ~ by Corista the Cloak " +
      "Crafter in Sanctuary.\n");
   
   set_name("cloak");
   set_adj(({adj2, adj3, adj4}));
   return;
}

void create_armour()
{
   initialize_cloak();
   
   set_ac(3);
   set_am(({2,-1,-1})); // Better by a tiny bit against slashing, etc.
   
   set_at(A_ROBE);
   
   add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3));
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(3, A_ROBE));
   add_prop(OBJ_I_VOLUME, 1000);
   
}

string query_recover()
{
   string rec;
   rec = MASTER + ":";
   
   rec += "#adj1#" + adj1;
   rec += "#adj2#" + adj2;
   rec += "#adj3#" + adj3;
   rec += "#adj4#" + adj4;
   
   
   rec += query_arm_recover();
   return rec;
}

void init_recover(string arg)
{
   string dummy;
   int i_check;
   
   sscanf(arg, "%s#adj1#%s#%s", dummy, adj1, dummy);
   sscanf(arg, "%s#adj2#%s#%s", dummy, adj2, dummy);
   sscanf(arg, "%s#adj3#%s#%s", dummy, adj3, dummy);
   sscanf(arg, "%s#adj4#%s#%s", dummy, adj4, dummy);
   
   init_arm_recover(arg);
   
   initialize_cloak();
   
   return;
}

/*
* string cloak() gives back a description of the cloak
* using only one of its adjectives, so that you
* don't get ugly too-long descriptions. Picks only from
* the first 3 adjectives.
*/
string cloak()
{
   string *adj = query_adjs();
   
   adj -= ({"worn"});
   
   if(sizeof(adj) < 3) return " " + adj[0] + " " + query_name();
   
   return " " + adj[random(3)]
   + " " + query_name();
}

/*
* Add/mask emotions to make them more fun!
*/
init()
{
   ::init();
   
   add_action("read_tag", "read");
   add_action("back", "back");
   add_action("bow", "bow");
   add_action("comfort","comfort");
   add_action("curtsey","curtsey");
   add_action("dance","dance");
   add_action("hold","hold");
   add_action("offer","offer");
   add_action("toss","toss");
}

int read_tag(string str)
{
   if(!str || str == "") return 0;
   
   notify_fail("Read what?\n");
   
   if(str == "tag" || str == "the tag")
      {
      write("The tag reads: Hand-crafted especially for ~ " +
         capitalize(NAME) + " ~ by Corista the Cloak " +
         "Crafter in Sanctuary.\n");
      return 1;
   }
   return 0;
}

/*
* Most of these emotions simply copied
* from the standard emotion soul and
* modified slightly.
   */

int
back(string str)
{
   object *oblist;
   string *how;
   
   if(!query_worn()) return 0;
   
   how = parse_adverb_with_space(str, "slowly", 0);
   
   if (!stringp(how[0]))
      {
      write("You draw your"+cloak()+" around you while " +
         "backing away" + how[1] + ".\n");
      all(" draws "+HIS+cloak()+" around "+HIM+" and " +
         "begins to back away" + how[1] + ".");
      return 1;
   }
   
   oblist = parse_this(how[0], "[away] [from] [the] %l");
   
   if (!sizeof(oblist))
      {
      notify_fail("Back [how] away from whom?\n");
      return 0;
   }
   
   actor("You draw your"+cloak()+" around you while " +
      "backing away"+how[1]+" from", oblist);
   all2actbb("draws "+HIS+cloak()+" around "+HIM+" and begins " +
      "to back away"+ how[1] + " from", oblist, 0, how[1]);
   targetbb(" draws "+HIS+cloak()+" around "+HIM+" and begins " +
      "to back" + how[1] + " away from you.", oblist, how[1]);
   return 1;
}

int
bow(string str)
{
   object *oblist;
   string *how;
   
   if(!query_worn()) return 0;
   
   how = parse_adverb_with_space(str, "charmingly", 0);
   
   if (!strlen(how[0]))
      {
      write("You bow"+how[1]+", your"+cloak()+
         " trailing behind you.\n");
      allbb(" bows"+how[1]+", "+HIS+cloak()+
         " trailing behind "+HIM+".");
      return 1;
   }
   
   oblist = parse_this(how[0], "[to] / [before] [the] %l");
   
   if (!sizeof(oblist))
      {
      notify_fail("Bow [how] to whom?\n");
      return 0;
   }
   
   actor("You bow" + how[1] + " to", oblist, ", your"+cloak()+
      " trailing behind you.");
   all2actbb("bows"+how[1]+" to", oblist, ", "+HIS+cloak()+
      " trailing behind "+HIM+".");
   targetbb(" bows"+how[1]+" before you, "+HIS+cloak()+
      " trailing behind "+HIM+".", oblist);
   return 1;
}

int
comfort(string str)
{
   object *oblist;
   
   if(!query_worn()) return 0;
   
   oblist = parse_this(str, "[the] %l");
   
   if (!sizeof(oblist))
      {
      notify_fail("Comfort whom?\n");
      return 0;
   }
   
   actor("You comfort", oblist, " within the folds of your"+cloak()+".");
   all2act("comforts", oblist, " within the folds of "+HIS+cloak()+".");
   target(" comforts you within the folds of "+HIS+cloak()+".", oblist);
   return 1;
}

int
curtsey(string str)
{
   object *oblist;
   string *how;
   
   if(!query_worn()) return 0;
   
   how = parse_adverb_with_space(str, "gracefully", 0);
   
   if (!strlen(how[0]))
      {
      write("You curtsey"+how[1]+", lifting the edges of " +
         "your"+cloak()+" daintily as you do so.\n");
      all(" curtseys"+how[1]+", lifting the edges of "+HIS+cloak()+
         " daintily as "+HE+" does so.");
      return 1;
   }
   
   oblist = parse_this(how[0], "[to] / [before] [the] %l");
   
   if (!sizeof(oblist))
      {
      notify_fail("Curtsey [how] to whom?\n");
      return 0;
   }
   
   actor("You curtsey"+how[1]+" to", oblist, ", lifting the edges "+
      "of your"+cloak()+" daintily as you do so.");
   all2actbb("curtseys"+how[1]+" to", oblist,", lifting the edges "+
      "of "+HIS+cloak()+" daintily as "+HE+" does so.");
   targetbb(" curtseys"+how[1]+" to you, lifting the edges "+
      "of "+HIS+cloak()+" daintily as "+HE+" does so.", oblist);
   return 1;
}


int
dance(string str)
{
   object *oblist;
   
   if(!query_worn()) return 0;
   
   if (!stringp(str))
      {
      write("You dance, your"+cloak()+" swirling around you.\n");
      all(" dances, "+HIS+cloak()+" swirling around "+HIM+".");
      return 1;
   }
   
   oblist = parse_this(str, "[the] %l");
   
   if (!sizeof(oblist))
      {
      notify_fail("Dance with whom?\n");
      return 0;
   }
   
   actor("You dance with", oblist, ", your"+cloak()+" swirling "+
      "romantically around you.");
   all2act("dances with", oblist, ", "+HIS+cloak()+" swirling "+
      "romantically around them.");
   target(" dances with you, "+HIS+cloak()+" swirling romantically "+
      "around you.", oblist);
   return 1;
}


int
hold(string str)
{
   object *oblist;
   
   if(!query_worn()) return 0;
   
   oblist = parse_this(str, "[the] %l [protectively]");
   
   if (!sizeof(oblist))
      {
      notify_fail("Hold whom?\n");
      return 0;
   }
   
   actor("You hold", oblist, " protectively within the warmth "+
      "and security of your"+cloak()+".");
   all2act("holds", oblist, " protectively within the warmth "+
      "and security of "+HIS+cloak()+".");
   target(" holds you protectively within the warmth "+
      "and security of "+HIS+cloak()+".", oblist);
   return 1;
}


int offer(string str)
{
   object *oblist;
   string *how;
   
   if(!query_worn()) return 0;
   
   how = parse_adverb_with_space(str, "graciously", 0);
   
   oblist = parse_this(how[0], "[my] [cloak] [to] [the] %l");
   
   if (!sizeof(oblist))
      {
      notify_fail("Offer your hem [how] to whom?\n");
      return 0;
   }
   
   actor("You"+how[1]+" offer the hem of your"+cloak()+" to be "+
      "kissed by", oblist, ".");
   all2actbb(how[1]+" offers the hem of "+HIS+cloak()+
      " to be kissed by", oblist, ".");
   targetbb(how[1]+" offers the hem of "+HIS+cloak()
      + " for you to kiss.", oblist);
   return 1;
}


int toss(string str)
{
   str = check_adverb_with_space(str, "nonchalantly");
   
   if(!query_worn()) return 0;
   
   if (str == NO_ADVERB_WITH_SPACE)
      {
      notify_fail("Toss your cloak how?\n");
      return 0;
   }
   
   write("You"+str+" toss your"+cloak()+" over your shoulders.\n");
    all(str+" tosses "+HIS+cloak()+" over "+HIS+" shoulders.");
   return 1;
}

