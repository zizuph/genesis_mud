/*
 * This is soul with standard emotes from: /cmd/std/soul_cmd.c
 * only some of them has been redefined
 *
 *  redefined: apologize, applaud, blush, bounce, bow, brighten, burp, 
 *             cheer, choke, chuckle, cough, cower, cry, curtsey, explode, 
 *             giggle, grin, hug, laugh, nudge, panic, pat, peer, point,
 *             poke, scratch, scream, shake, shrug, slap, snarl, spank, 
 *             squeeze, stare, sulk, tickle, wave, wiggle 
 *
 */

#pragma save_binary
inherit "/cmd/std/soul_cmd";

#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <living_desc.h>
#include <ss_types.h>
#include <wa_types.h>
#include <adverbs.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"

#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define DEPTH 1  /*  How many rooms away the shout will be heard.  */

#define S_C_LEVELS ({ "Servant", "Footman", "Standard Bearer", \
                       "Corporal", "Sergeant", "Warrant Officer", \
                       "Lieutenant", "Captain" })

#define IS_MEMBER(ob)  ob->query_guild_member(GUILD_NAME)
#define IS_HIGHER(ob)  (TP->query_name() != "Milan") && \
			((ob->query_name() == "Milan") || \
			 (member_array(ob->query_s_c_level(), S_C_LEVELS) > \
                          member_array(TP->query_s_c_level(), S_C_LEVELS)))

#define PANIC ONE_OF_LIST(({"panic", \
			    "tremble", \
			    "shiver", \
			    "cringe to "+TP->query_real_name(), \
                            "cower", \
			    "jump"}))

/* The soul identification */
string get_soul_id()
{
  return GUILD_NAME+" - standard emotes";
}

int
list_changed_emotes(string arg)
{
  if(arg != "emotes") 
  {
    NF("Angmar what? Angmar emotes???\n");
    return 0;
  }

  write("\nList of emotes changed for Angmar's Army:\n"+
        "-----------------------------------------\n\n"+
	"apologize, applaud, blush, bounce, bow, brighten, burp, cheer, choke, chuckle, cough, cower, cry, curtsey, explode, giggle, grin, hug, laugh, nudge, panic, pat, peer, point, poke, scratch, scream, shake, shrug, slap, snarl, spank, squeeze, stare, sulk, tickle, wave, wiggle\n\n"+
	"All of them work like standard ones only results are different. "+
	"Hope you will have fun with them and will find out when and what "+
	"they do!\n\n");
  return 1;
}

/* **************************************************************************
 * The list of verbs and functions. Please add new in alphabetical order.
 */
mapping
query_cmdlist()
{
    return ::query_cmdlist() + (["angmar":"list_changed_emotes"]);
}

/*************************************************************/

int query_cmd_soul() { return 1; }

/*************************************************************/
/**********  first some handy functions  *********************/
/*************************************************************/

/*** this returns array of worn shields  ***/
object *shields()
{
  object ob, *shields = ({ });

  if((ob = TP->query_armour(W_LEFT)) && (ob->query_at() == A_SHIELD))
    shields += ({ ob });
  if((ob = TP->query_armour(W_RIGHT)) && (ob->query_at() == A_SHIELD))
    shields += ({ ob });
  return shields;
}

/*** this returns array of wielded clubs  ***/
object *clubs()
{
  object ob, *clubs = ({ });

  if((ob = TP->query_weapon(W_RIGHT)) && (ob->query_wt() == W_CLUB))
    clubs += ({ ob });
  if((ob = TP->query_weapon(W_LEFT)) && (ob->query_wt() == W_CLUB))
    clubs += ({ ob });
  if((ob = TP->query_weapon(W_BOTH)) && (ob->query_wt() == W_CLUB))
    clubs += ({ ob });
  return clubs;
}

/*** this returns short() of one worn shield or 0  ***/
mixed shield()
{
  object sh;

  if(((sh = TP->query_armour(W_LEFT)) && (sh->query_at() == A_SHIELD)) ||
     ((sh = TP->query_armour(W_RIGHT)) && (sh->query_at() == A_SHIELD)))
    return sh->short();
  return 0;
}

/*** this returns short() of one wielded club or 0  ***/
mixed club()
{
  object club;

  club = TP->query_weapon(W_RIGHT);
  if(!club || club->query_wt() != W_CLUB)
  {
    club = TP->query_weapon(W_BOTH);
    if(!club)
      club = TP->query_weapon(W_LEFT);
  }
  if(!club || club->query_wt() != W_CLUB)
    return 0;
  return club->short();
}

string
str_a_arr(mixed arr)
{
  return COMPOSITE_DEAD(arr);
}
string
str_the_arr(mixed arr)
{
  string s, str = COMPOSITE_DEAD(arr);
  

  str = implode(explode(str, " a "), " the ");
  str = implode(explode(str, " an "), " the ");
  if((sscanf(str, "a %s", s) == 1) || (sscanf(str, "an %s", s) == 1))
    str = "the "+s;
  return str;
}
string
str_arr(mixed arr)
{
  string s, str = COMPOSITE_DEAD(arr);

  str = implode(explode(str, " a "), " ");
  str = implode(explode(str, " an "), " ");
  if((sscanf(str, "a %s", s) == 1) || (sscanf(str, "an %s", s) == 1))
    str = s;
  return str;
}
/*************************************************************/
/**********  now redefine emotes  ****************************/
/*************************************************************/

int
apologize(string str)
{
  object *oblist;
  string *how;

  if(!sizeof(clubs())) return ::apologize(str);

  how = parse_adverb_with_space(str, "remorsefully", 0);

  if (!strlen(how[0]))
  {
    write("You apologize"+how[1]+", hiding your "+str_arr(clubs())+
          " behind your back.\n");
    all(" apologizes"+how[1]+", hiding "+HIS(TP)+" "+str_arr(clubs())+
          " behind "+HIS(TP)+" back.");
    return 1;
  }

  oblist = parse_this(how[0], "[to] [the] %l");

  if (!sizeof(oblist))
  {
    notify_fail("Apologize to whom?\n");
    return 0;
  }

  target(" apologizes"+how[1]+" to you, hiding "+HIS(TP)+" "+str_arr(clubs())+
          " behind "+HIS(TP)+" back.", oblist);
  actor("You apologize"+how[1]+" to",oblist,", hiding your "+str_arr(clubs())+
          " behind your back.");
  all2act("apologizes"+how[1]+" to", oblist, ", hiding "+HIS(TP)+" "+
          str_arr(clubs())+" behind "+HIS(TP)+" back.");
  return 1;
}

int
applaud(string str)
{
  object *oblist;
  string *how, what;
    
  if(sizeof(shields()+clubs()) < 2)
    return ::applaud(str);

  what = str_arr(shields()+clubs());

  how = parse_adverb_with_space(str, "wholeheartedly", 0);

  if (!strlen(how[0]))
  {
    all(" applauds"+how[1]+", hitting "+HIS(TP)+" "+what+" together.");
    write("You applaud"+how[1]+", hitting your "+what+" together.\n");
    return 1;
  }

  oblist = parse_this(how[0], "[for] / [to] [the] %l");

  if (!sizeof(oblist))
  {
    notify_fail("Applaud to whom?\n");
    return 0;
  }

  target(" applauds"+how[1]+" to you, hitting "+HIS(TP)+" "+what+
         " together.", oblist);
  actor("You applaud"+how[1]+" to", oblist, 
        ", hitting your "+what+" together.");
  all2act("applauds"+how[1]+" to", oblist, ", hitting "+HIS(TP)+" "+
          what+" together.");
  return 1;
}

int
blush(string str)
{
  if(!sizeof(shields())) return ::blush(str);

  str = check_adverb_with_space(str, "profusely");

  if (str == NO_ADVERB_WITH_SPACE)
  {
    notify_fail("Blush how?\n");
    return 0;
  }

  write("Your try to hide your burning cheeks behind your "+
             str_arr(shields())+".\n");
  SOULDESC("blushing" + str);
  allbb(" hides behind "+HIS(TP)+" "+str_arr(shields())+", blushing"+str+".");
  return 1;
}

int
bounce(string str)
{
  object *s_c = ( clubs() + shields() );

  if(!sizeof(s_c)) return ::bounce(str);

  str = check_adverb_with_space(str, "uncontrollably");

  if (str == NO_ADVERB_WITH_SPACE)
  {
    notify_fail("Bounce how?\n");
    return 0;
  }

  write("You bounce around"+str+", waving with your "+str_arr(s_c)+".\n");
  all(" bounces around"+str+", waving with "+HIS(TP)+" "+str_arr(s_c)+".");
  return 1;
}

int
bow(string str)
{
  object *oblist;
  string *how, what;

  what = ((TP->query_gender() == G_FEMALE) ? "curtsey" : "bow");
  if(!club())
  {
    if(what == "curtsey") return ::curtsey(str);
    return ::bow(str);
  }

  how = parse_adverb_with_space(str, "gracefully", 0);

  if(!strlen(how[0]))
  {
    write("You "+what+how[1]+", waving with your "+club()+".\n");
    allbb(" "+what+"s"+how[1]+", waving with "+HIS(TP)+" "+club()+".");
    return 1;
  }

  oblist = parse_this(how[0], "[to] / [before] [the] %l");

  if (!sizeof(oblist))
  {
    notify_fail("Bow to whom?\n");
    return 0;
  }

  targetbb(" "+what+"s"+how[1]+" to you, waving with "+HIS(TP)+" "+
           club()+".", oblist);
  actor("You "+what+how[1]+" to", oblist, ", waving with your "+club()+".");
  all2actbb(what+"s"+how[1]+" to", oblist, ", waving with "+HIS(TP)+" "+
            club()+".");
  return 1;
}

int
brighten(string str)
{
  if(!club()) return ::brighten(str);
  if (strlen(str))
  {
    notify_fail("Brighten what?\n");
    return 0;
  }
  write("You think about it, then bonk yourself on the head with your "+
        club()+"! Your face brightens!\n");
  all(" thinks about it, then bonks "+HIM(TP)+"self on the head with "+
      HIS(TP)+" "+club()+"! "+CAP(HIS(TP))+" face brightens.");
  return 1;
}

int
burp(string str)
{
  if(!sizeof(shields())) return ::burp(str);

  str = check_adverb_with_space(str, "rudely");

  if (str == NO_ADVERB_WITH_SPACE)
  {
    notify_fail("Burp what?\n");
    return 0;
  }

  write("You burp"+str+".\n"+
        "The sound echoes in your "+str_arr(shields())+".\n");
  all(" burps"+str+".\n"+
      "The sound echoes in "+HIS(TP)+" "+str_arr(shields())+".");
  return 1;
}

int
cheer(string str)
{
  object *s_c = ( clubs() + shields() );

  if(!sizeof(s_c)) return ::cheer(str);

  str = check_adverb_with_space(str, "enthusiastically");

  if (str == NO_ADVERB_WITH_SPACE)
  {
    notify_fail("Cheer how?\n");
    return 0;
  }

  write("You cheer"+str+", waving with your "+str_arr(s_c)+".\n");
  all(" cheers"+str+", waving with "+HIS(TP)+" "+str_arr(s_c)+".");
  SOULDESC("cheering" + str);
  return 1;
}

int
choke(string str)
{
  if(!club()) return ::choke(str);
  if (strlen(str))
  {
    notify_fail("Choke what?\n");
    return 0;
  }

  write("Cough, cough, cough, hark !!!\nHitting your back with your "+
         club()+" doesn't help much.\n");
  all("'s face colour slowly darkens as "+HE(TP)+" chokes, trying in vain "+
      "help "+HIM(TP)+"self by hitting "+HIS(TP)+" back with "+HIS(TP)+
      " "+club()+".");
  SOULDESC("choking on something");
  return 1;
}

int
chuckle(string str)
{
  if(!shield()) return ::chuckle(str);

  str = check_adverb_with_space(str, "politely");

  if (str == NO_ADVERB_WITH_SPACE)
  {
    notify_fail("Chuckle how?\n");
    return 0;
  }

  write("You chuckle"+str+" behind your "+str_arr(shields())+".\n");
  all(" chuckles"+str+" behind "+HIS(TP)+" "+str_arr(shields())+".");
  SOULDESC("chuckling" + str);
  return 1;
}

int
cough(string str)
{
  if(!shield()) return ::cough(str);

  str = check_adverb_with_space(str, "noisily");

  if (str == NO_ADVERB_WITH_SPACE)
  {
    notify_fail("Cough how?\n");
    return 0;
  }

  write("You cover quickly your mouth and cough into your "+shield()+".\n");
  all(" covers quickly "+HIS(TP)+" mouth and coughs into "+HIS(TP)+" "+
      shield()+".");
  SOULDESC("coughing" + str);
  return 1;
}

int
cower(string str)
{
  if(!sizeof(shields())) return ::cower(str);

  if (strlen(str))
  {
    notify_fail("Cower what?\n");
    return 0;
  }

  write("You try to hide behind your "+str_arr(shields())+".\n");
  allbb(" tries to hide behind "+HIS(TP)+" "+str_arr(shields())+".");
  return 1;
}

int
cry(string str)
{
  if (strlen(str))
  {
    notify_fail("Cry what?\n");
    return 0;
  }

  SOULDESC("crying");

  if(!sizeof(parse_this("elf", "%l")))
  {
    if(club())
    {
      write("You bursts into tears, wishing some elves were around to smash "+
            "with your "+club()+" and make you feel better.\n");
      all(" bursts into tears, wishing some elves were around to smash "+
          "with "+HIS(TP)+" "+club()+" and make "+HIM(TP)+" feel better.");
    }
    else
    {
      write("You bursts into tears, wishing some elves were around to bash "+
            "and make you feel better.\n");
      all(" bursts into tears, wishing some elves were around to bash "+
          "and make "+HIM(TP)+" feel better.");
    }
    return 1;
  }
  if(club())
  {
    write("You bursts into tears, wiping them out with your "+club()+".\n");
    all(" bursts into tears, wiping them out with "+HIS(TP)+" "+club()+".");
    return 1;
  }
  if(shield())
  {
    write("You bursts into tears, catching them into your "+shield()+".\n");
    all(" bursts into tears, catching them into "+HIS(TP)+" "+shield()+".");
    return 1;
  }
  write("Waaaaah!\n");
  all(" bursts into tears.");
  return 1;
}

int
curtsey(string str)
{
  return bow(str);
}

int
explodes(string str)
{
  object *oblist, *higher;
  object *s_c = ( clubs() + shields() );
  int i;

  if(!sizeof(s_c)) return ::explodes(str);

  if (!strlen(str))
  {
    write("You hold your breath and explode in anger, waving dangerously "+
          "with your "+str_arr(s_c)+".\n");
    all(" explodes with anger, waving dangerously "+
          "with "+HIS(TP)+" "+str_arr(s_c)+".");
    return 1;
  }

  oblist = parse_this(str, "[at] [the] %l");

  if (!sizeof(oblist))
  {
    notify_fail("Explode at whom?\n");
    return 0;
  }

  higher = ({ });
  for(i=0; i<sizeof(oblist); i++)
    if(IS_HIGHER(oblist[i])) higher += ({ oblist[i] });
  oblist -= higher;

  if (!sizeof(oblist))
  {
    actor("You must control yourself in contact with", higher, 
          ". Your rank is still too low...");
    return 1;
  }

  target(" explodes with anger at you, waving dangerously with "+HIS(TP)+" "+
          str_arr(s_c)+".", oblist);
  actor("You explode in anger at", oblist, ", waving dangerously "+
          "with your "+str_arr(s_c)+".");
  all2act("explodes with anger at", oblist, ", waving dangerously with "+
          HIS(TP)+" "+str_arr(s_c)+".");
  for(i=0; i<sizeof(oblist); i++)
   if(random(TP->query_skill(SS_WEP_CLUB)) > 
      random(oblist[i]->query_stat(SS_DIS)))
    oblist[i]->command(PANIC);
  return 1;
}

int
giggle(string str)
{
  if(!shield()) return ::giggle(str);

  str = check_adverb_with_space(str, "inanely");

  if (str == NO_ADVERB_WITH_SPACE)
  {
    notify_fail("Giggle how?\n");
    return 0;
  }

  write("You giggle"+str+" from behind your "+str_arr(shields())+".\n");
  all(" giggles"+str+" from behind "+HIS(TP)+" "+str_arr(shields())+".");
  SOULDESC("giggling" + str);
  return 1;
}

int
grin(string str)
{
  object *oblist, *higher;
  string *how;
  int i;

  if(!club()) return ::grin(str);

  how = parse_adverb_with_space(str, "evilly", 0);

  if (!strlen(how[0]))
  {
    write("You grin"+how[1]+", swinging your "+str_arr(clubs())+" around.\n");
    allbb(" grins"+how[1]+", swinging "+HIS(TP)+" "+str_arr(clubs())+" around.");
    SOULDESC("grinning" + how[1]);
    return 1;
  }

  oblist = parse_this(how[0], "[at] [the] %l");

  if (!sizeof(oblist))
  {
    notify_fail("Grin at whom?\n");
    return 0;
  }

  higher = ({ });
  for(i=0; i<sizeof(oblist); i++)
    if(IS_HIGHER(oblist[i])) higher += ({ oblist[i] });
  oblist -= higher;

  if (!sizeof(oblist))
  {
    actor("You must control yourself in contact with", higher, 
          ". Your rank is still too low...");
    return 1;
  }

  targetbb(" grins"+how[1]+" at you, swinging "+HIS(TP)+" "+
            str_arr(clubs())+" under your nose.", oblist);
  actor("You grin"+how[1]+" at", oblist, ", swinging your "+str_arr(clubs())+
        " under "+(sizeof(oblist)>1 ? "their noses." : HIS(oblist[0])+" nose."));
  all2act("grins"+how[1]+" at", oblist, ", swinging "+HIS(TP)+" "+
      str_arr(clubs())+
      " under "+(sizeof(oblist)>1 ? "their noses." : HIS(oblist[0])+" nose."));
  SOULDESC("grinning" + how[1]);
  for(i=0; i<sizeof(oblist); i++)
   if(random(TP->query_skill(SS_WEP_CLUB)) > 
      random(oblist[i]->query_stat(SS_DIS)))
    oblist[i]->command(PANIC);
  return 1;
}

int
hug(string str)
{
  object *oblist;
  string *how;

  if(!shield()) return ::hug(str);

  how = parse_adverb_with_space(str, "fiercefully", 1);

  oblist = parse_this(how[0], "[the] %l");

  if (!sizeof(oblist))
  {
    notify_fail("Hug whom?\n");
    return 0;
  }

  target(" hugs you"+how[1]+", pressing "+HIS(TP)+" "+str_arr(shields())+
         " into your ribs.", oblist);
  actor("You hug", oblist, how[1]+", pressing your "+str_arr(shields())+
        " into "+(sizeof(oblist)>1 ? "their" : HIS(oblist[0]))+" ribs.");
  all2act("hugs", oblist, how[1]+", pressing "+HIS(TP)+" "+str_arr(shields())+
          " into "+(sizeof(oblist)>1 ? "their" : HIS(oblist[0]))+" ribs.");
  return 1;
}

int
laugh(string str)
{
  object *oblist, *higher;
  string *how, ccc;
  int i;

  if(!club()) return ::laugh(str);
  ccc = str_arr(clubs());

  if (!strlen(str))
  {
    write("You fall down laughing, beating your "+ccc+
         " on the ground.\n");
    all(" falls down laughing, beating "+HIS(TP)+" "+ccc+
            " on the ground.");
    SOULDESC("laughing");
    return 1;
  }

  how = parse_adverb_with_space(str, "exuberantly", 0);

  if (!strlen(how[0]))
  {
    write("You laugh"+how[1]+", beating your "+ccc+
         " on the ground.\n");
    all(" laughs" + how[1] + ", beating "+HIS(TP)+" "+ccc+
            " on the ground.");
    SOULDESC("laughing" + how[1]);
    return 1;
  }

  oblist = parse_this(how[0], "[at] [the] %l");

  if (!sizeof(oblist))
  {
	notify_fail("Laugh how?\n");
	return 0;
  }

  higher = ({ });
  for(i=0; i<sizeof(oblist); i++)
    if(IS_HIGHER(oblist[i])) higher += ({ oblist[i] });
  oblist -= higher;

  if (!sizeof(oblist))
  {
    actor("You must control yourself in contact with", higher, 
          ". Your rank is still too low...");
    return 1;
  }

  target(" laughs"+how[1]+" at you, beating "+HIS(TP)+" "+ccc+
         " on the ground.", oblist);
  actor("You laugh" + how[1] + " at", oblist, ", beating your "+ccc+
         " on the ground.");
  all2act("laughs" + how[1] + " at", oblist, ", beating "+HIS(TP)+
          " "+ccc+" on the ground.");
  SOULDESC("laughing" + how[1]);
  return 1;
}

int
nudge(string str)
{
  object *oblist;
  string with;

  if(!club() && !shield()) return ::nudge(str);

  oblist = parse_this(str, "[the] %l");

  if (!sizeof(oblist))
  {
    notify_fail("Nudge whom?\n");
    return 0;
  }

  if(club())
    with = club();
  else
    with = shield();

  target(" nudges you with "+HIS(TP)+" "+with+".", oblist);
  actor("You nudge", oblist, " with your "+with+".");
  all2act("nudges", oblist, " with "+HIS(TP)+" "+with+".");
  return 1;
}

int
panic(string str)
{
  if(!club()) return ::panic(str);

  if (strlen(str))
  {
    notify_fail("Panic what?\n");
    return 0;
  }

  write("You panic and try to hide behind your "+club()+".\n");
  allbb(" panics and tries to hide behind "+HIS(TP)+" "+club()+".");
  return 1;
}

int
pat(string str)
{
  object *oblist, *higher;
  string *zones;
  string one, two;
  int i;

  if(!club()) return ::pat(str);

  notify_fail("Whom are you trying to pat?\n");
  if (!strlen(str)) return 0;

  zones = ({ "back", "head", "shoulder" });


  if (sscanf(str, "%s %s", one, two) == 2)
  {
    if (member_array(two, zones) == -1)
      return 0;
    str = one;
  }

  if (!strlen(two))
    two = "head";

  if ((str == (string)this_player()->query_real_name()) ||
      (str == "me") ||
      (str == "myself"))
  {
    write("You pat yourself on your "+two+" with your "+club()+".\n");
    all(" pats "+HIM(TP)+"self on "+HIS(TP)+" "+two+" with "+HIS(TP)+" "+
        club()+".");
    return 1;
  }

  oblist = parse_this(str, "[the] %l [on] [the]");

  if (!sizeof(oblist)) return 0;

  higher = ({ });
  if(two == "head")
    for(i=0; i<sizeof(oblist); i++)
      if(IS_HIGHER(oblist[i])) higher += ({ oblist[i] });
  oblist -= higher;

  if (sizeof(oblist))
  {
    target(" pats you on your "+two+" with "+HIS(TP)+" "+club()+".", oblist);
    actor("You pat", oblist, " on "+
          (sizeof(oblist) > 1 ? "their "+two+"s with your "+club()+".":
  	  HIS(oblist[0])+" "+two+" with your "+club()+"."));
    all2act("pats", oblist, " on " +
          (sizeof(oblist)> 1 ? "their "+two+"s with "+HIS(TP)+" "+club()+".":
	  HIS(oblist[0])+" "+two+" with "+HIS(TP)+" "+club()+"."));
  }
  if (sizeof(higher))
  {
    target(" kneels in front of you and offers you "+HIS(TP)+" "+club()+
           ". You take it and bonk "+HIM(TP)+" on the head with it.", higher);
    actor("You kneel in front of", higher, " and offer "+
          (sizeof(higher) > 1 ? "them" : HIM(higher[0]))+" your "+club()+". "
          +(sizeof(higher) > 1 ? 
	  "They take it in turn and bonk you on the head with it.":
  	  CAP(HE(higher[0]))+" takes it and bonks you on the head with it."));
    all2act("kneels in front of", higher, " and offer "+
      (sizeof(higher) > 1 ? "them" : HIM(higher[0]))+" "+HIS(TP)+" "+club()+". "
      +(sizeof(higher) > 1 ? "They take it in turn and bonk ":
      CAP(HE(higher[0]))+" takes it and bonks ")+
      HIM(TP)+" on the head with it.");
  }
  return 1;
}

int
peer(string str)
{
  object *oblist;
  string *how, sss;

  if(!shield()) return ::peer(str);
  sss = str_arr(shields());

  how = parse_adverb_with_space(str, "quizzically", 0);

  if (!strlen(how[0]))
  {
    write("You peer"+how[1]+" around from behind your "+sss+".\n");
    allbb(" peers"+how[1]+" around from behind "+HIS(TP)+" "+sss+".");
    SOULDESC("peering" + how[1]);
    return 1;
  }

  oblist = parse_this(how[0], "[at] [the] %l");

  if (!sizeof(oblist))
  {
    notify_fail("Peer at whom?\n");
    return 0;
  }

  targetbb(" peers"+how[1]+" at you from behind "+HIS(TP)+" "+
             sss+".", oblist);
  actor("You peer"+how[1]+" at", oblist," from behind your "+
          sss+".  Hmm......");
  all2actbb("peers"+how[1]+" at", oblist, " from behind "+HIS(TP)+" "+
              sss+".");
  SOULDESC("peering" + how[1]);
  return 1;
}

int
point(string str)
{
  object *oblist;
  string *tmp;

  if(!club()) return ::point(str);

  notify_fail("Where do you want to point?\n");

  if(!strlen(str))
  {
    write("You point with your "+club()+" all around.\n");
    allbb(" points with "+HIS(TP)+" "+club()+" all around.");
    return 1;
  }

  if(str == "up" || str == "down" || str == "north" || str == "south" ||
     str == "west" || str == "east" || str == "northwest" ||
     str == "northeast" || str == "southwest" || str == "southeast")
  {
    write("You point "+str+" with your "+club()+".\n");
    allbb(" points "+str+" with "+HIS(TP)+" "+club()+".");
    return 1;
  }

  if(str == (string) this_player()->query_real_name() ||
     str == "me" || str == "myself")
  {
    write("You point at yourself with your "+club()+".\n");
    allbb(" points at "+HIM(TP)+"self with "+HIS(TP)+" "+club()+".");
    return 1;
  }

  oblist = parse_this(str, "[at] [the] %l");

  if (!sizeof(oblist))
  {
    tmp = explode(str, " ");
    if (sizeof(tmp) > 1 && tmp[0] == "at")
      str = implode(tmp[1 .. sizeof(tmp) - 1], " ");
    oblist = FIND_STR_IN_OBJECT(str, environment(this_player()));
    if (!sizeof(oblist))
    {
      if (environment(this_player())->item_id(str))
      {
	write("You point at the "+str+" with your "+club()+".\n");
	allbb(" points at "+LANG_ADDART(str)+" with "+HIS(TP)+" "+
                club()+".");
	return 1;
      }
      return 0;
    }
    write("You point at "+LANG_THESHORT(oblist[0])+" with your "+
             club()+".\n");
    allbb(" points at "+LANG_THESHORT(oblist[0])+" with "+HIS(TP)+" "+
            club()+".");
    return 1;
  }

  targetbb(" points at you with "+HIS(TP)+" "+club()+".", oblist);
  actor("You point at", oblist, " with your "+club()+".");
  all2actbb("points at", oblist, " with "+HIS(TP)+" "+club()+".");
  return 1;
}

int
poke(string str)
{
  object *oblist;
  string *zones;
  string one, two;

  if(!club()) return ::poke(str);

  notify_fail("Poke whom?\n");
  if(!strlen(str)) return 0;

  zones = ({"eye", "ear", "thorax", "abdomen", "shoulder", "ribs"});

  if (sscanf(str, "%s %s", one, two) == 2)
  {
    if(member_array(two, zones) == -1) return 0;
    str = one;
  }

  if (!strlen(two)) two = "ribs";

  oblist = parse_this(str, "[the] %l [in] [the]");

  if (!sizeof(oblist))
  {
    return 0;
  }

  target(" pokes you in the "+two+" with "+HIS(TP)+" "+club()+".", oblist);
  actor("You poke", oblist, " in the "+two+" with your "+club()+".");
  all2act("pokes", oblist, " in the "+two+" with "+HIS(TP)+" "+club()+".");
  return 1;
}

int
scratch(string str)
{
  object *oblist;
  string *zones;
  string one, two, three;

  if(!shield()) return ::scratch(str);
  three = shield();

  zones = ({ "head", "chin", "back", "behind", "nose" });

  if (!strlen(str)) str = "head";

  if (member_array(str, zones) != -1)
  {
    write("You scratch your "+str+" with the edge of your "+three+".\n");
    allbb(" scratches "+HIS(TP)+" "+str+" with the edge of "+HIS(TP)+" "+
            three+".");
    return 1;
  }

  notify_fail("Scratch what?\n");
  if (sscanf(str, "%s %s", one, two) == 2)
  {
    if (member_array(two, zones) == -1)
      return 0;
  }

  if (!strlen(two))
    two = "head";

  oblist = parse_this(one, "[the] %l [at] [the]");

  if (!sizeof(oblist))
  {
    return 0;
  }

  target(" scratches your "+two+" with the edge of "+HIS(TP)+" "+three+".", 
           oblist);
  actor("You scratch", oblist, "'s "+two+" with the edge of your "+
          three+".");
  all2act("scratches", oblist, "'s "+two+" with the edge of "+HIS(TP)+" "+
            three+".");
  return 1;
}

int
scream(string str)
{
  object *oblist, *higher, *rooms, troom;
  int i;

  if(!club()) return ::scream(str);

  if (strlen(str))
  {
	notify_fail("Scream what?\n");
	return 0;
  }
  if (!(troom = environment(this_player()))) return 0;

  rooms = find_neighbour(({ troom }), ({ troom }), DEPTH);
  rooms -= ({ troom });

  for (i = 0; i < sizeof(rooms); i++)
    tell_room(rooms[i], "@@shout_name:" + file_name(this_object()) +
		  "@@ screams loudly!\n", this_player());

  oblist = parse_this("all", "%l");
  higher = ({ });
  for(i=0; i<sizeof(oblist); i++)
    if(IS_HIGHER(oblist[i])) higher += ({ oblist[i] });
  oblist -= higher;

  write("ARRGGGGGGHHHHHH!!!!\n");
  allbb(" screams loudly, angrily smashing everything around with "+HIS(TP)+
           " "+str_arr(clubs())+".");
  for(i=0; i<sizeof(oblist); i++)
   if(random(TP->query_skill(SS_WEP_CLUB)) > 
      random(oblist[i]->query_stat(SS_DIS)))
    oblist[i]->command(PANIC);
  return 1;
}

int
shake(string str)
{
    object *oblist, *members;
    int i;

    if (!strlen(str))
    {
	write("You shake your head in disagreement.\n");
	allbb(" shakes " + this_player()->query_possessive() +
	      " head in disagreement.");
	return 1;
    }

    oblist = parse_this(str, "[with] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Shake hands with whom?\n");
	return 0;
    }

    target(" shakes your hand.", oblist);
    actor("You shake hands with", oblist);

    members = ({ });
    for(i=0; i<sizeof(oblist); i++)
      if(IS_MEMBER(oblist[i]))
      {
        members += ({ oblist[i] });
        oblist[i]->catch_msg("You notice secret Angmar sign and "+
                             "return it back.\n");
      }
    all2act("shakes", oblist, "'s hand.");
    if(sizeof(members))
      actor("Your secret sign was returned by", members);
    return 1;
}

int
shrug(string str)
{
  object *arr = shields()+clubs();

  if(!sizeof(arr)) return ::shrug(str);

  str = check_adverb_with_space(str, "helplessly");

  if (str == NO_ADVERB_WITH_SPACE)
  {
    notify_fail("Shrug what?\n");
    return 0;
  }

  write("You shrug"+str+", flailing your arms with "+
        str_the_arr(arr)+" widely.\n");
  allbb(" shrugs"+str+", flailing "+HIS(TP)+" arms with "+
        str_a_arr(arr)+" widely.");
  return 1;
}

int
slap(string str)
{
  object *oblist, *higher;
  int i;

  if(sizeof(shields()+clubs())<2) return ::slap(str);

  oblist = parse_this(str, "[the] %l");

  if (!sizeof(oblist))
  {
    notify_fail("Slap whom?\n");
    return 0;
  }

  higher = ({ });
  for(i=0; i<sizeof(oblist); i++)
    if(IS_HIGHER(oblist[i])) higher += ({ oblist[i] });
  oblist -= higher;

  if (!sizeof(oblist))
  {
    actor("You must control yourself in contact with", higher, 
          ". Your rank is still too low...");
    return 1;
  }

  if(!club())
  {
    target(" tried to slap you, but "+HIS(TP)+" "+shield()+
           " hit you first!\nOuch!!!", oblist);
    actor("You tried to slap", oblist, ", but your "+shield()+" hit "+
          (sizeof(oblist)>1 ? "them" : HIM(oblist[0])) +" first!");
    all2act("tried to slap", oblist, ", but "+HIS(TP)+" "+shield()+" hit "+
          (sizeof(oblist)>1 ? "them" : HIM(oblist[0])) +" first!");
    return 1;
  }
  target(" tried to slap you, but managed to hit you with "+HIS(TP)+" "+
           club()+" instead!\nOuch!!!", oblist);
  actor("You tried to slap", oblist, ", but managed to hit "+
          (sizeof(oblist)>1 ? "them" : HIM(oblist[0])) +" with your "+
         club()+" instead!");
  all2act("tried to slap", oblist, ", but managed to hit "+
          (sizeof(oblist)>1 ? "them" : HIM(oblist[0])) +" with "+HIS(TP)+" "+
         club()+" instead!");
  return 1;
}

int
snarl(string str)
{
  object *oblist, *higher;
  string *how;
  int i;

  if(!club()) return ::snarl(str);

  how = parse_adverb_with_space(str, "savagely", 0);

  oblist = parse_this(how[0], "[at] [the] %l");

  if (!sizeof(oblist))
  {
    notify_fail("Snarl at whom?\n");
    return 0;
  }

  higher = ({ });
  for(i=0; i<sizeof(oblist); i++)
    if(IS_HIGHER(oblist[i])) higher += ({ oblist[i] });
  oblist -= higher;

  if (!sizeof(oblist))
  {
    actor("You must control yourself in contact with", higher, 
          ". Your rank is still too low...");
    return 1;
  }

  target(" snarls"+how[1]+" at you, waving with "+str_a_arr(clubs())+
         " over your head.\nAren't you scared ?", oblist);
  actor("You snarl" + how[1] + " at", oblist, ", waving with "+
     str_the_arr(clubs())+
     " over "+(sizeof(oblist)>1 ? "their heads." : HIS(oblist[0])+" head."));
  all2act("snarls" + how[1] + " at", oblist, ", waving with "+
           str_a_arr(clubs())+" over "+
         (sizeof(oblist)>1 ? "their heads." : HIS(oblist[0])+" head."));
  SOULDESC("snarling" + how[1]);
  for(i=0; i<sizeof(oblist); i++)
   if(random(TP->query_skill(SS_WEP_CLUB)) > 
      random(oblist[i]->query_stat(SS_DIS)))
    oblist[i]->command(PANIC);
  return 1;
}

int
spank(string str)
{
  object *oblist;
  string *how;

  if(sizeof(shields()+clubs())<2) return ::spank(str);

  how = parse_adverb_with_space(str, "playfully", 1);
  oblist = parse_this(str, "[the] %l");

  if (!sizeof(oblist))
  {
    notify_fail("Slap whom?\n");
    return 0;
  }

  if(!club())
  {
    target(" tried to spank you"+how[1]+", but "+HIS(TP)+" "+shield()+
           " hit you first!\nOuch!!!", oblist);
    actor("You tried to spank", oblist, how[1]+", but your "+shield()+" hit "+
          (sizeof(oblist)>1 ? "them" : HIM(oblist[0])) +" first!");
    all2act("tried to spank", oblist, how[1]+", but "+HIS(TP)+" "+shield()+
        " hit "+(sizeof(oblist)>1 ? "them" : HIM(oblist[0])) +" first!");
    return 1;
  }
  target(" tried to spank you"+how[1]+", but managed to hit you with "+
          HIS(TP)+" "+club()+" instead!\nOuch!!!", oblist);
  actor("You tried to spank", oblist, how[1]+", but managed to hit "+
          (sizeof(oblist)>1 ? "them" : HIM(oblist[0])) +" with your "+
         club()+" instead!");
  all2act("tried to spank", oblist, how[1]+", but managed to hit "+
          (sizeof(oblist)>1 ? "them" : HIM(oblist[0])) +" with "+HIS(TP)+" "+
         club()+" instead!");
  return 1;
}

int
squeeze(string str)
{
  object *oblist;
  string *how;

  if(!shield()) return ::squeeze(str);

  how = parse_adverb_with_space(str, "fondly", 1);

  oblist = parse_this(how[0], "[the] %l");

  if (!sizeof(oblist))
  {
    notify_fail("Squeeze whom?\n");
    return 0;
  }

  target(" squeezes you"+how[1]+", forgetting that "+HIS(TP)+" "+
         str_arr(shields())+" hurt"+(sizeof(shields())>1 ? "" : "s")+
         " your ribs.", oblist);
  actor("You squeeze", oblist, how[1]+".");
  all2act("squeezes", oblist, how[1]+", forgetting that "+HIS(TP)+" "+
        str_arr(shields())+" hurt"+(sizeof(shields())>1 ? "" : "s")+
        " "+(sizeof(oblist)>1 ? "their" : HIS(oblist[0]))+" ribs.");
  return 1;
}

int
stare(string str)
{
    object *oblist;

    if(!strlen(str)) return ::stare(str);

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Stare at whom?\n");
	return 0;
    }

    targetbb(" stares at you with a dangerous gleam in "+HIS(TP)+" eyes.", 
             oblist);
    actor("You stare at", oblist, " with a dangerous gleam in your eyes.");
    all2actbb("stares at", oblist, " with a dangerous gleam in "+HIS(TP)+
              " eyes.");
    return 1;
}

int
sulk(string str)
{
  if(!shield()) return ::sulk(str);

  if (strlen(str))
  {
    notify_fail("Sulk what?\n");
    return 0;
  }

  write("You sulk behind your "+str_arr(shields())+".\n");
  allbb(" sulks behind "+HIS(TP)+" "+str_arr(shields())+".");
  return 1;
}

int
tickle(string str)
{
  object *oblist;
  string *how;

  if(!club()) return ::tickle(str);

  how = parse_adverb_with_space(str, "playfully", 1);

  oblist = parse_this(how[0], "[the] %l");

  if (!sizeof(oblist))
  {
    notify_fail("Tickle whom?\n");
    return 0;
  }

  target(" tickles you"+how[1]+" in the ribs with "+HIS(TP)+" "+
             str_arr(clubs())+".", oblist);
  actor("You tickle", oblist, how[1]+" in the ribs with your "+
          str_arr(clubs())+".");
  all2act("tickles", oblist, how[1]+" in the ribs with "+HIS(TP)+" "+
                str_arr(clubs())+".");
  oblist->command("laugh");
  return 1;
}

int
wave(string str)
{
  object *oblist;
  string *how;

  if(!shield()) return ::wave(str);

  how = parse_adverb_with_space(str, "happily", 0);

  if (!strlen(how[0]))
  {
    write("You wave"+how[1]+", making a little drift with your "+
            str_arr(shields())+".\n");
    allbb(" waves"+how[1]+", making a little drift with "+HIS(TP)+" "+
            str_arr(shields())+".");
    return 1;
  }

  oblist = parse_this(how[0], "[to] [the] %l");

  if (!sizeof(oblist))
  {
    notify_fail("Wave to whom?\n");
    return 0;
  }

  targetbb(" waves"+how[1]+" in your direction, making a little drift with "+
           HIS(TP)+" "+str_arr(shields())+".", oblist);
  actor("You wave"+how[1]+" in", oblist, "'s direction, making a little "+
        "drift with your "+str_arr(shields())+".");
  all2actbb("waves"+how[1]+" in", oblist, "'s direction, making a little "+
            "drift with "+HIS(TP)+" "+str_arr(shields())+".");
  return 1;
}

int
wiggle(string str)
{
  if(!club()) return ::wiggle(str);

  str = check_adverb_with_space(str, BLANK_ADVERB);

  if (str == NO_ADVERB_WITH_SPACE)
  {
    notify_fail("Wiggle what?\n");
    return 0;
  }

  write("You wiggle your bottom"+str+
        ", rubbing it gently with "+str_the_arr(clubs())+".\n");
  allbb(" wiggles "+HIS(TP)+" bottom"+str+
        ", rubbing it gently with "+str_a_arr(clubs())+".");
  return 1;
}

