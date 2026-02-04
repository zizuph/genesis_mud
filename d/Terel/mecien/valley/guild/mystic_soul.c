/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
* mystic_soul.c
*
* This soul holds the general commands and feelings of the Mystic Order
* It is based upon Nick's soul for the Solamnian Knights
* (copied  and modified by Mortricia from
      *  /doc/examples/solamn/solamn_soul.c)
*
* Recoded by Sorgum 5/94
*/

inherit "/cmd/std/command_driver";

#include "/d/Terel/include/Terel.h"

#include <const.h>
#include <options.h>
#include <ss_types.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"


/*
* Function name: get_soul_id
* Description:   Return a proper name in order to get a nice printout
* Returns:  A string that is the name of this soul
*/
public string
get_soul_id()
{
   return "Mystic Order";
}

/*
* Function name: query_cmd_soul
* Description:   Is this a cmd_soul
* Returns:  1 (an int) to indicate this is a cmd_soul.
*/
public int
query_cmd_soul()
{
   return 1;
}

/*
* Function name: query_cmdlist
* Description:   A list of verbs and functions (please add new in alphabetical
   *                order)
* Returns:  A mapping from verbs to functions
*/
public mapping
query_cmdlist()
{
   seteuid(getuid(TO));
   return ([
         "absolve":"absolve",
         "adore":"adore",           /* OK */
	"awe":"awe",
         "beseech":"beseech",       /* OK */
         "blink":"blink",           /* OK */
         "channel":"channel",
         "chant":"chant",           /* OK */
         "confess":"confess",
         "consecrate":"consecrate",
         "curse":"curse",           /* OK */
       "dread":"dread",
         "farewell":"farewell",     /* OK */
         "fathom":"fathom",        
         "hail":"hail",
         "help":"help",
	"harken":"harken",
         "humble":"humble",
         "meyes":"meyes",
         "mlaugh":"mlaugh",           /* OK */
	"mnod":"mnod",
         "ms":"ms",                 /* OK */
         "msmile":"msmile",           /* OK */
	"mtouch":"mtouch",
         "obedience":"obedience",
	"overshadow":"overshadow",
         "piety":"piety",
         "pray":"pray",             /* OK */
	"prayer":"prayer",
	"recant":"recant",
         "reflect":"reflect",
         "rend":"rend",
         "reverence":"reverence",   /* OK */
         "ridicule":"ridicule",     /* OK */
         "salute":"salute",
         "scold":"scold",           /* OK */
         "scorn":"scorn",           /* OK */
         "sign":"sign",
         "wail":"wail",             /* OK */ 
         "weep":"weep",
         ]);
}

/* **************************************************************************
* Here follows the actual functions. Please add new in alphabetical order.
* **************************************************************************/

/********************* absolve ***********************/
absolve(string str){

    object *ob, *mm, *mc;
    object soot, mring;
    int i;
    NF("Absolve who?\n");
    if(!str)
	return 0;

    NF("Absolve who?\n");
    ob = parse_this(str, "[the] %l");
    if(sizeof(ob)!=1)
	return 0;
    NF("Only an archon may absolve.\n");
   if(TP->query_skill(MYSTIC_RANK) < 5)
  return 0;
    NF("You cannot absolve this person.\n");
    if(!MEMBER(ob[0]))
	return 0;

    soot = present("holy_soot", TP);
    if(!soot) {
	NF("You need holy soot to absolve.\n");
	return 0;
    }
    
    if((TP->query_mystic_rank()) > (ob[0]->query_mystic_rank())) {

	TP->catch_msg("You absolve " + ob[0]->query_name() + 
	      " placing soot upon " + ob[0]->query_possessive() + " face.\n");
  ob[0]->catch_msg(QCTNAME(TP) + " absolves you, placing soot upon your face.\n");
	tell_room(environment(TP), QCTNAME(TP) +
	   " absolves " + ob[0]->query_name() + " placing soot upon " +
		ob[0]->query_possessive() + " face.\n", ({ TP, ob[0]}));
	ob[0]->lower_rank(TP);
	write_file("/d/Terel/mecien/log/absolved", TP->query_name() +
		   " absolved " + ob[0]->query_name() + " to " +
	   ob[0]->query_guild_title_occ() + " at " + ctime(time()) + ".\n");
  soot->remove_object();
  mring = present("mystic_ring", ob[0]);
  if(mring) mring->update_spells(ob[0]);
  return 1;
}
TP->catch_msg("You do not have the stature.\n");
return 1;
}


/********************* adore *****************************************/
int
adore(string str)
{
   object *oblist;
   string pro;
   
   oblist = parse_this(str, "[the] %l");
   
   if (!sizeof(oblist))
      {
      NF("Adore who?\n");
      return 0;
   }
   
   if (sizeof(oblist) == 1)
      actor("You grant", oblist, " the adoration that " +
      oblist[0]->query_pronoun() + " deserves.");
   else
      actor("You grant", oblist, " the adoration that they deserve.");
   
   target(" adores you.", oblist);
   all2act(" shows adoration for", oblist);
   return 1;
}

awe(){
   write("You stand in awe.\n");
 allbb(" is gripped by some mysterious compelling force, nearly trembling to the ground in awe.");
   return 1;
}
/********************* beseech *****************************************/
int
beseech(string str)
{
   object *oblist;
   
   oblist = parse_this(str, "[the] %l");
   
   if (!sizeof(oblist))
      {
      NF("Beseech who?\n");
      return 0;
   }    
   
   actor("You beseech", oblist);
   target(" beseeches you.", oblist);
   all2act(" beseeches", oblist);
   return 1;
}

/********************* blink *****************************************/
int
blink(string str)
{
   if (strlen(str))
      {
      NF("Blink what?\n");
      return 0;
   }
   
   write("You blink.\n");
   all(" blinks.");
   return 1;
}

/******************** channel ****************************************/
int
channel(string str)
{
   int out_mana, in_mana, mana;
   object who;
   string receiver;
   
   NF("You do not possess the needed training.\n");
   if (TP->query_skill(SS_CHANNELING) < 25)
      return 0;
   
   NF("You do not have the strength.\n");
   if (TP->query_mana() < 100)
      return 0;
   
   NF("You will need the mystic staff to succeed.\n");
   if (!present(MYSTIC_STAFF, TP))
      return 0;
   
   NF("You have failed in thy attempts.\n");
   if (sscanf(str, "to %s", receiver) != 1)
      return 0;
   
   who = find_living(receiver);
   
   NF("That person cannot be located.\n");
   if (!who || who->query_wiz_level() > 0)
      return 0;
   
   NF("Only mystics can receive the ancient powers.\n");
   if (!MEMBER(who))
      return 0;
   
   say(QCTNAME(TP) + " takes hold of " + TP->query_possessive() +
      " staff and pronounces ancient words.\n");
   TP->add_mana(-100);
   TP->catch_msg("You feel weakened.\n");
   out_mana = TP->query_skill(SS_CHANNELING);
   in_mana = who->query_skill(SS_CHANNELING);
   mana = (out_mana*in_mana)/100; 
   if (mana < 1)
      {
      who->catch_msg("You feel a slight warmth.\n");
      return 1; 
   }
   tell_room(environment(who), QCTNAME(who) + " glows with a " +
      "mysterious radiance.\n", who);
   who->catch_msg("You feel strength and power come to you from afar.\n");
   who->add_mana(mana);
   return 1;
}

/********************* chant *****************************************/
int
chant(string str)
{
   object *oblist;
   int i;
   string what;
   
   if (!strlen(str))
      {
      write("You chant a hymn to the Ancient Ones.\n");
      all(" chants an ancient hymn.");
      return 1;
   }
   
   oblist = parse_this(str, "[the] %l");
   
   if (!sizeof(oblist))
      {
      NF("Chant who?\n");
      return 0;
   }
   
   actor("You chant the honor of", oblist);
   
   for (i = 0; i < sizeof(oblist); i++)
   {
      if (oblist[i]->query_wiz_level())
         what = "greatness";
      else
         what = "honour";
      
      oblist[i]->catch_msg(QCTNAME(TP) + " chants your " + what + ".\n");
   }
   return 1;
}

/***************************** confess *******************************/
int
confess(){
   write("You confess your iniquity and seek atonement.\n");
   allbb(" confesses " + TP->query_possessive() + " iniquity and seeks "
         + "atonement.");
   return 1;
}

int
dread(){
  write("You are filled with a sense of dread and hide your face.\n");
   allbb(" trembles and turns white, holding a hand before " + 
  TP->query_possessive() + " face, as if to ward off some horrible power.");
   return 1;
}

private void
kneel_msgs(object who)
{
   who->catch_msg("You kneel down.\n");
   say(QCTNAME(who) + " kneels down.\n", ({ who, TP }));
   TP->catch_msg(QCTNAME(who) + " kneels down.\n");
   TP->catch_msg("You consecrate " + QTNAME(who) + ", placing your " +
      "hands upon " + who->query_possessive() +
      " shoulders.\n");
   who->catch_msg(QCTNAME(TP) + " consecrates you to the Ancients.\n");
   say(QCTNAME(TP) + " consecrates " + QTNAME(who) + 
      " by placing " + TP->query_possessive() + " hands upon "
      + who->query_possessive() + " shoulders.\n",({who, TP}));
   who->set_skill(EXALT, 0);
   return;
}

private void
notify_nonpresent_mystics(object who, string what)
   {
   object *ul;
   int i;
   
   ul = users();
   
   for (i=0; i<sizeof(ul); i++)
   if (MEMBER(ul[i]) && present(MYSTIC_RING, ul[i]) &&
         environment(ul[i]) != environment(who))
   ul[i]->catch_msg("From deep within you realize that " +
      QTNAME(who) + what);
   
   return;
}

/********************* consecrate ************************************/
int
consecrate(string str)
{
   object *mm, *mc;
   object *ob, robe, mantle, alb, ring, cantor;
   int i, my_rank, rank, anointed, mys;
   string new;
   
   NF("Consecrate who?\n");
   if (!str)
      return 0;
   
   my_rank = TP->query_mystic_rank();
   NF("Only an Archon may consecrate.\n");
   if (my_rank < MYSTIC_ARCHON)
      return 0;
   
   NF("Consecrate who?\n");
   ob = parse_this(str, "[the] %l");
   if (sizeof(ob) == 0 || sizeof(ob) >= 2)
      return 0;
   
   mm = ({ });         /* mm contains all mystic members */
   for (i = 0; i < sizeof(ob); i++)
   if (MEMBER(ob[i]) && interactive(ob[i]) && ob[i] != TP)
      mm += ({ ob[i] });
   
   mc = ({ });         /* mc contains mystic candidates as protector*/
   for (i = 0; i < sizeof(ob); i++)
   if (!MEMBER(ob[i]) && interactive(ob[i]))
      mc += ({ ob[i] });
   
   if (sizeof(mm) == 0 && sizeof(mc) == 0)
      return 0;
   
   if (sizeof(mm))
      {
      NF("You must be in the Shrine!\n");
      if (sscanf(MASTER_OB(ETP), GUILD_DIR+"%s", new) != 1)
         return 0;
   }
   
   cantor = present("mieriys", ETP);
   
   for (i = 0; i < sizeof(mm); i++)      /* Loop over mystic members */
   {
      anointed = mm[i]->query_prop("anointed");
      rank     = mm[i]->query_mystic_rank();
      mys      = mm[i]->query_stat(SS_OCCUP);
      ring     = present(MYSTIC_RING, mm[i]);
      robe     = present(MYSTIC_ROBE, mm[i]);
      mantle   = present(MYSTIC_MANTLE, mm[i]);
      alb      = present(MYSTIC_ALB, mm[i]);
      
      if (rank == MYSTIC_ARCHON)
         {
         TP->catch_msg(QCTNAME(mm[i]) + " is an Archon!\n");
         continue;
        }
      else
         if (rank == MYSTIC_PATRIARCH)
         {
         TP->catch_msg(QCTNAME(mm[i]) + " is the Patriarch!\n");
         continue;
        }
      
      if (!anointed)
         {
         TP->catch_msg(QCTNAME(mm[i]) + " has not been anointed.\n");
         continue;
        }
      if (!ring)
         {
         TP->catch_msg(QCTNAME(mm[i]) + " has not the ring!\n");
         continue;
        }
      
      /*if (TP->query_advance_rank() == 0) */
         /*
      * check the consecratee! not the consecrator!  -- Sorgum */
      if (mm[i]->query_advance_rank() == 0)
         {
         if (rank == MYSTIC_NOVITIATE)
            TP->catch_msg(QCTNAME(mm[i]) +
            " is not ready to be consecrated" +
            " to the White Circle.\n");
         if (rank == MYSTIC_CIRCLE)
            TP->catch_msg(QCTNAME(mm[i]) +
            " is not ready to be consecrated" +
            " to the Holy Star.\n");
         if (rank == MYSTIC_STAR)
            TP->catch_msg(QCTNAME(mm[i]) +
            " is not ready to join in the" +
            " Song of Antiquity.\n");
         if (rank == MYSTIC_CANTOR)
            TP->catch_msg(QCTNAME(mm[i]) +
            " is not ready to stand before" +
            " the Ancient Tree.\n");
         if (rank == MYSTIC_EXARCH)
            TP->catch_msg(QCTNAME(mm[i]) +
            " is not ready to behold" +
            " the Mystery.\n");
         continue;
        }
      if (rank >= MYSTIC_NOVITIATE && !robe)
         {
         TP->catch_msg(QCTNAME(mm[i]) + " must possess the white robe.\n");
         continue;
        }
      if (rank >= MYSTIC_CIRCLE && !mantle)
         {
         TP->catch_msg(QCTNAME(mm[i]) +" must possess the gray mantle.\n");
         continue;
        }
      /* The holy alb is now in place... Mortricia Sept. 94 */
      if (rank >= MYSTIC_STAR && !alb) {
         TP->catch_msg(QCTNAME(mm[i]) +
            " must possess the holy alb.\n");
         continue;
        }
      
      if (mm[i]->advance_rank(TP) == 0) {
         TP->catch_msg("Somehow you aren't allowed to consecrate " +
            QTNAME(mm[i]) +
            ". Could be a bug... Mail Mortricia or Sorgum.\n");
         continue;
        }
      
      kneel_msgs(mm[i]);
      new = RANKTITLE[rank + 1];
      
      TP->catch_msg(QCTNAME(mm[i]) + " is now a " + new + ".\n");
      mm[i]->catch_msg("You are now an honoured " + new + ".\n");
      say(QCTNAME(mm[i]) + " is now a " + new + ".\n", ({mm[i], TP})); 
      
      if (cantor)
         cantor->command("smile at "+mm[i]->query_real_name());
      
      if (ring)
         ring->update_spells(mm[i]);
      
      setuid();
      seteuid(getuid());
      write_file(CONSECRATED, TP->query_name() + " consecrated " +
         mm[i]->query_name() + " to " + new + " (" +
         ctime(time()) + ").\n");
      
      notify_nonpresent_mystics(mm[i], " is now a " + new + ".\n");
   }
   
   for (i=0; i<sizeof(mc); i++)    /* Loop over protector candidates */
   {
      if (present(MYSTIC_PRING, mc[i]))
         {
         TP->catch_msg(QCTNAME(mc[i]) + " is already a protector.\n");
         continue;
        }
      anointed=mc[i]->query_prop("anointed");
      if (!anointed)
         {
         TP->catch_msg(QCTNAME(mc[i]) + " has not been anointed.\n");
         continue;
        }
      kneel_msgs(mc[i]);
      mc[i]->catch_msg("You are now known to the Ancients.\n");
      say(QCTNAME(mc[i]) + " is now known to the Ancients as " +
         "protector.\n", mc[i]);
      mc[i]->catch_msg("A gold ring appears in your hand.\n"); 
      setuid();
      seteuid(getuid());
      ring=clone_object(GUILD_DIR+"obj/pring");
      if (ring->move(mc[i]))
         {
         ring->move(environment(mc[i]));
         mc[i]->catch_msg("You drop the "+ring->short()+".\n");
         tell_room(environment(TP), QCTNAME(mc[i]) + " drops the " +
            ring->short()+".\n", mc[i]);
        }
      notify_nonpresent_mystics(mm[i], " is now known to the Ancients as "+
            "protector.\n");
   }   
   return 1;
}

/********************* curse *****************************************/
int
curse(string str)
{
   object *oblist;
   int i, old;
   
   if (!strlen(str))
      {
      write("You make the cursing sign and utter the invocation.\n");
      all(" intones an ancient curse.");
      return 1;
   }
   
   oblist = parse_this(str, "[the] %l");
   
   if (!sizeof(oblist))
      {
      NF("Curse who?\n");       
      return 0;
   }
   
   actor("You curse", oblist, " with an ancient sign and invocation.");
   all2act(" curses", oblist, " with an ancient sign and invocation.");
   
   for (i = 0; i < sizeof(oblist); i++) {
      if (oblist[i]->query_wiz_level()) 
         oblist[i]->catch_msg(QCTNAME(TP) + " dares to curse you.\n");
      else 
         oblist[i]->catch_msg(QCTNAME(TP) + " curses you with an ancient " +
         "sign and invocation.\n");
     old = oblist[i]->query_skill(130007);
    oblist[i]->set_skill(130007, (old + 1));
   }
   return 1;
}

/********************* recant *****************************************/
int
recant(string str)
{
   object *oblist;
   int i, old;
   
   if (!strlen(str))
      {
       write("You recant what you have spoken.\n");
    all(" recants all that has transpired.");
      return 1;
   }
   
   oblist = parse_this(str, "[the] %l");
   
   if (!sizeof(oblist))
      {
      NF("Recant who?\n");       
      return 0;
   }
   
   actor("You recant the curse from", oblist, " with a wave of the ancient sign and a solemn invocation.");
   all2act(" recants a curse from", oblist, " with a wave of an ancient sign and a solemn invocation.");
   
   for (i = 0; i < sizeof(oblist); i++) {
      if (oblist[i]->query_wiz_level()) 
         oblist[i]->catch_msg(QCTNAME(TP) + " recants a curse from you.\n");
      else 
         oblist[i]->catch_msg(QCTNAME(TP) + " recants a curse from you with a wave of an ancient " +
         "sign and a solemn invocation.\n");
     old = oblist[i]->query_skill(130007);
     if(oblist[i]->query_skill(130007)){
    oblist[i]->set_skill(130007, (old - 1));
    }
   }
   return 1;
}
/********************* farewell *****************************************/
int
farewell(string str)
{
   object *oblist;
   
   oblist = parse_this(str, "[to] %l");
   
   if (!sizeof(oblist))
      {
      NF("Farewell who?\n");
      return 0;
   }    
   
   actor("You bid farewell to", oblist);
   target(" bids farewell to you.", oblist);
   all2act(" bids farewell to", oblist);
   return 1;
}

int
fathom(){
   write("You fathom the dark powers of the ancient world.\n");
   all(" fathoms the secrets of the ancient darkness.");
   return 1;
}
harken(){
   write("You stand still, harkening to the voices of ages past.\n");
  all(" stands still and silent, gazing upward solemnly, as if harkening to some distant and unheard voices.");
   return 1;
}

private int
am_humble(object player, object other)
{
  /*
   * We all hail to the Prophet
   */

  if (player->query_real_name() == "mecien")
    return 0;

  /*
   * Mortals shall hail wizards
   */

  if (player->query_wiz_level() && (other->query_wiz_level() == 0))
    return 0;

  if ((player->query_wiz_level() == 0) && other->query_wiz_level())
    return 1;

  /*
   * Next check rank first
   */

  if (player->query_mystic_rank() > other->query_mystic_rank())
    return 0;

   if (player->query_mystic_rank() < other->query_mystic_rank()) return 1;
      if(player->query_mystic_rank() == other->query_mystic_rank()){
   if(player->query_skill(EXALT) < other->query_skill(EXALT)) return 1;
   if(player->query_skill(EXALT) > other->query_skill(EXALT)) return 0;
   if(player->query_mystic_office() > other->query_mystic_office()) return 0;
   if(player->query_mystic_office() < other->query_mystic_office()) return 1;
     }
  /*
   * Otherwise it depends on guild stat
   */

  return (player->query_stat(SS_OCCUP) <= other->query_stat(SS_OCCUP));
}
  
/********************* hail ****************************************/
int
hail(string str)
{
   object *oblist;
   string proper;
   int rank;
   int i;
   
   if ((!strlen(str)) || str == "all") {
      write("You hail all present.\n");
      all(" hails everyone with a sign of peace.");
      return 1;
   }
   
   oblist = parse_this(str, "[to] %l");
   
   if (!sizeof(oblist) || (sizeof(oblist) >= 2))
      {
      NF("Hail who?\n");
      return 0;
   }
   
   if (!MEMBER(oblist[0]))
      {
      NF("That person is not of the Order.\n");
      return 0;
   }
   
   rank = oblist[0]->query_spell_level();
   switch (rank)
   {
      case 120..9999:
      proper = "most arcane majesty";
      break;
      case 100..119:
      proper = "most imperious reverence";
      break;
      case 95..99:
      proper = "my hallowed eminence";
      break;
      case 90..94:
      proper = "your exalted grace";
      break;
      case 80..89:
      proper = "most hallowed elder";
      break;
      case 70..79:
      proper = "hallowed elder";
      break;
      case 60..69:
      proper = "hallowed reverence";
      break;
      case 50..59:
      proper = "most honoured elder";
      break;
      case 40..49:
      proper = "honoured elder";
      break;
      case 30..39:
      proper = "honoured reverence";
      break;
      case 20..29:
      proper = "mystic friend";
      break;
      default:
      proper = "mystic novice";
      break;
   }
   
   if (oblist[0]->query_real_name() == "mecien")
      proper = "Prophet";
   
   if (oblist[0]->query_real_name() == "mrpr")
      proper = "most honoured majesty";
   
   if (oblist[0]->query_real_name() == "mortricia")
      proper = "mystic Lady";
   
   if (oblist[0]->query_real_name() == "sorgum") {
      proper = "mystic Lord";
   }

   if (am_humble(TP, oblist[0]))
   {
      actor("You hail", oblist, " in solemn humility.");
      target(" kneels before you and chants: Hail, " + proper + ".",
         oblist);
      all2act(" kneels before", oblist, " and chants: Hail, " +
         proper + ".");
      return 1;
   }
   
   actor("You hail", oblist, " with a mystic blessing.");
   target(" hails you with a mystic blessing.", oblist);
   all2act(" hails", oblist, " with a mystic blessing.");
   return 1;
}

/************** help *************************************************/
int
help(string str)
{
   string subject, filename;
   
   if (!str)
      return 0;
   
   if (sscanf(str, "mystic %s", subject) != 1)
      return 0;
   
   setuid();
   seteuid(getuid(TO));
   filename = GUILD_HELP_DIR + subject;
   if (file_size(filename) > 0)
      {
      write(read_file(filename));
      return 1;
   }
   
   NF("No mystic help on that subject I'm afraid.\n");
   return 0;
}

/********************** humble *************************************/
   int
   humble(string str)
   {
      object *oblist;
      
      if (!strlen(str))
         {
         write("You humble yourself.\n");
         all(" humbles " + TP->query_objective() + 
             "self according to the ancient ways.");
         return 1;
        }
      
      oblist = parse_this(str, "[to] %l");
      
      if (!sizeof(oblist))
         {
         NF("Humble yourself before whom?\n");    
         return 0;
        }
      
      actor("You humble yourself before", oblist);
      target(" humbles " + TP->query_objective() +
             "self before you.", oblist);
      all2act(" humbles " + TP->query_objective() +
             "self before", oblist);
      return 1;
   }


 /********************** meyes *************************************/
   int
   meyes()
   {
   write("You show the eyes of mystery.\n");
   allbb(" grows dark and " + TP->query_possessive() +
         " eyes glow with a luminous golden fire.");
         return 1;
   }

/********************* mlaugh *****************************************/
int
mlaugh(string str)
{
   object *oblist;
   string *how;
   
   if (!strlen(str))
      {
      write("You laugh mysteriously.\n");
      all(" struggles a bit, then is consumed with a mysterious laugh.");
      return 1;
   }
   
   how = parse_adverb_with_space(str, "mysteriously", 0);
   
   if (!strlen(how[0]))
      {
      write("You laugh" + how[1] + ".\n");
      all(" struggles a bit, then is consumed with a mysterious laugh.");
      return 1;
   }
   
   oblist = parse_this(how[0], "[at] [the] %l");
   
   if (!sizeof(oblist))
      {
      notify_fail("Laugh how?\n");
      return 0;
   }
   
   target(" laughs" + how[1] + " at you.", oblist);
   actor("You laugh" + how[1] + " at", oblist, ".");
   all2act(" laughs" + how[1] + " at", oblist);
   return 1;
}

/********************* mnod ***************************************/
int
mnod(string str)
{
   object *oblist;
   string my;
   
  my = TP->query_possessive();
   if (!strlen(str)) {
    write("You bow your head in solemn and respectful reverence.\n");
    all(" bows " +  my + " head with solemn and respectful reverence.");
      return 1;
   }
   
   oblist = parse_this(str, "[for] %l");
   
   if (!sizeof(oblist))
      {
      NF("Nod for who?\n");    
      return 0;
   }

   
  actor("You bow your head respectfully to solemnly acknowledge", oblist);
 target(" respectfully bows " + my + " head to you in solemn acknowledgement.", oblist);
 all2act(" respectfully, with a bow of " + my + " head, solemnly acknowledges", oblist);
   return 1;
}
/********************* ms (mystic speech) ****************************/
int
ms(string msg)
{
   object *oblist;
   int i;
   
   if (TP->query_prop(LIVE_M_MOUTH_BLOCKED)) {
      write("You cannot use your mouth at the moment.\n");
      return 1;
   }
   if (TP->query_skill(SS_LANGUAGE) < 20)
      {
      NF(break_string("To be able to speak the Ancient Mystic Tongue you " +
            "must improve thy language skills.\n", 72));
      return 0;
   }
   
   if (!strlen(msg))
      {
      NF("Say what in the mystic language?\n");
      return 0;
   }
   
   if (TP->query_option(OPT_ECHO)) {
      write(break_string("Using the Ancient Tongue, you intone: " +
            msg + "\n", 72));
   } else {
      write("Ok.\n");
   }
   
   oblist = all_inventory(ETP);
   for (i=0; i < sizeof(oblist); i++)
   {
      if (living(oblist[i]) && oblist[i] != TP)
         {
         if (MEMBER(oblist[i]) && oblist[i]->query_skill(SS_LANGUAGE) > 19)
            oblist[i]->catch_msg(QCTNAME(TP) + " intones: " +
                                 msg + "\n");
         else
            oblist[i]->catch_msg(QCTNAME(TP) +
            " speaks in a mystical language.\n");
        }
   }
   return 1;
}
   
   /********************** msmile *************************************/
   int
   msmile(string str)
   {
   write("You smile a mysterious smile.\n");
  allbb(" smiles mysteriously, which seems to summon an eerie presence.");
         return 1;
   }

/********************* mtouch *****************************************/
int
mtouch(string str)
{
   object *oblist;
   
   oblist = parse_this(str, "[to] %l");
   
   if (!sizeof(oblist))
      {
   NF("Mystically touch who?\n");
      return 0;
   }    
   
   actor("With a spirit of peace, you lay your hand upon", oblist);
   target(" lays " + TP->query_possessive() + " hand upon your shoulder and a sense of peace and friendship fills you.", oblist);
   all2act(" lays " + TP->query_possessive() + " hand upon the shoulder of", oblist);
   return 1;
}
/*************************** obedience ******************************/
int obedience(){
   write("You show your obedience to the ancient ways.\n");
  allbb(" falls upon the ground, showing " + TP->query_possessive() +
   " obedience to the ancient ways.");
   return 1;
  }

/********************** overshadow *************************************/
   int
   overshadow(string str)
   {
      object *oblist;
      
      if (!strlen(str))
         {
   write("You impress your image upon the world of shadow.\n");
   all(" is suddenly overshadowed by a strange and eerie darkness.");
         return 1;
        }
      
      oblist = parse_this(str, "[to] %l");
      
      if (!sizeof(oblist))
         {
  NF("Overshadow who?\n");

         return 0;
        }
      
   if(oblist[0]->query_stat(SS_WIS) > TP->query_stat(SS_WIS) +
    random(50)){
     actor("You are not great enough to overshadow", oblist);
  target(" attempts to discern something in your spirit, but you manage to avert the vision with your will.", oblist);
  return 1;
   }

  actor("With your spiritual force, you overshadow the mind of", oblist);
  target(" rises up before you, a darkness growing, as " + TP->query_pronoun() +
  " probes your spirit with some arcane power.", oblist);
  all2act(" seems to overshadow", oblist);
   set_alarmv(2.0, -1.0, "feel_weak", ({ oblist[0], TP }));
      return 1;
   }

feel_weak(object who, object me){
  who->catch_msg("You feel a strange weakness as the spirit of " + QCTNAME(me) + " leaves you.\n");
}

/********************* piety ***************************************/
int
piety(){

  int num;
  string desc;
  object high, full;

   if(TP->query_prop("blessed")){
  write("The blessing of the Ancients is upon you.\n");
  }

 if(TP->query_prop("anointed")){
  write("The marking of the sacred oil is upon you.\n");
  }

  high = present("mystic_high", TP);
  if(high){
  write("You are drunk with mystic wine.\n");
  }
  
  full = present(MYSTIC_FULL, TP);
  if(full){
  write("You feel nourished by sacred bread.\n");
  }
  
  num = TP->query_skill(130005);
  switch (num){
  case 1000..9999: desc = "sublimely filled by"; break;
  case 850..999: desc = "exalted by"; break;
  case 750..849: desc = "graced by"; break;
  case 500..749: desc = "highly favoured by"; break;
  case 250..499: desc = "in harmony with"; break;
  case 100..249: desc = "at one with"; break;
  case 1..99: desc = "in need of"; break;
  case 0: desc = "unknown to"; break;
  default: desc = "obscure to"; break;
  }
  if(TP->query_alignment() < 200){
  write("Seek holiness.\n");
  return 1;
  }
  write("You are " + desc + " the ancient spirits.\n");
   say(QCTNAME(TP) + " places " + TP->query_possessive() +
      " hands together in prayer and looks upwards.\n");
  return 1;
}

/*************************** prayer ******************************/
int prayer(){
   write("You quietly recite a prayer honouring the Ancient chosen for you.\n");
  allbb(" quietly recites an ancient prayer.");
   return 1;
  }

/********************* pray ***************************************/
int
pray(string str)
{
   object *oblist;
   
   if (!strlen(str)) {
      write("You pray for a time.\n");
      all(" intones a prayer.");
      return 1;
   }
   
   oblist = parse_this(str, "[for] %l");
   
   if (!sizeof(oblist))
      {
      NF("Pray for who?\n");    
      return 0;
   }
   
   actor("You pray for", oblist);
   target(" prays for you.", oblist);
   all2act(" intones a prayer over", oblist);
   return 1;
}

/****************************** reflect ******************************/
reflect(){
   write("You reflect upon the mysteries of the ancient world.\n");
   allbb(" reflects upon some ancient mystery, " + TP->query_possessive()
         + " face aglow with inspiration.");
   return 1;
}

/***************************** rend ***********************************/
rend(){
    write("You rend your garments due to the heinous blasphemy.\n");
    allbb(" rends " + TP->query_possessive() + 
          " garments in the face of such heinous blasphemy.");
    return 1;
}



/********************* reverence *************************************/
int
reverence(string str)
{
   object *oblist;
   
   oblist = parse_this(str, "[to] / [for] %l");
   
   if (!sizeof(oblist))
      {
      NF("Reverence who?\n");
      return 0;
   }
   
   actor("You show your reverence for", oblist);
   target(" shows " + TP->query_possessive() + " reverence for you.", oblist);
   all2act(" shows " + TP->query_possessive() +  " reverence for", oblist);
   return 1;
}

/********************* ridicule *************************************/
int
ridicule(string str)
{
   object *oblist;
   int my_wis, ob_wis, i;
   string xself;
   
   oblist = parse_this(str, "[the] %l");
   
   if (!sizeof(oblist))
      {
      NF("Ridicule who?\n");
      return 0;
   }
   
   my_wis = TP->query_stat(SS_WIS);
   
   switch (TP->query_gender())
   {
      case G_MALE:
      xself="himself";
      break;
      case G_FEMALE:
      xself="herself";
      break;
      default:
      xself="itself";
      break;
   }
   
   for (i = 0; i < sizeof(oblist); i++)
   {
      ob_wis = oblist[0]->query_stat(SS_WIS);
      
      if (oblist[i]->query_wis_level() && !(TP->query_wiz_level()))
         ob_wis *= 2;
      
      if (my_wis + random(my_wis) > ob_wis + random(ob_wis))
         {
         TP->catch_msg("You managed to ridicule " + QTNAME(oblist[i]) +
            ".\n");
         oblist[i]->catch_msg(QCTNAME(TP) + " managed to ridicule you.\n");
         say(QCTNAME(TP) + " managed to ridicule " + QTNAME(oblist[i]) +
            ".\n",({ oblist[i], TP }));
        }
      else
         {
         TP->catch_msg("You are making a fool of yourself instead.\n");
         oblist[i]->catch_msg(QCTNAME(TP) + " makes a fool of " + xself +
            " when trying to ridicule you.\n");
         say(QCTNAME(TP) + " makes a fool of " + xself +
            " when trying to ridicule " + QTNAME(oblist[i])+".\n",
            ({ oblist[i], TP }));
        }
   }
   return 1;
}

/********************* salute *************************************/
int
salute(string str)
{
   int i;
   object *oblist;
   string x;
   
   if (!strlen(str))
      {
      write("You salute everyone.\n");
      all(" salutes you in a mysterious way.");
      return 1;
   }
   
   oblist = parse_this(str, "[the] %l");
   
   if (!sizeof(oblist))
      {
      NF("Salute who?\n");
      return 0;
   }
   
   for (i=0; i<sizeof(oblist); i++)
   {
      if (T_WIZ(oblist[i]))
         {
         x = "ancient master";
         if (oblist[i]->query_gender() == 1)
            x = "ancient mistress";
         TP->catch_msg("You salute " + QTNAME(oblist[i]) +
            " as your " + x + ".\n");
         oblist[i]->catch_msg(QCTNAME(TP) + " salutes you as " +
            TP->query_possessive() + " " + x + ".\n");
        }
      else
         if (MEMBER(oblist[i]) || oblist[i]->query_wiz_level())
         {
         TP->catch_msg("You salute "+QTNAME(oblist[i])+".\n");
         oblist[i]->catch_msg(QCTNAME(TP) + " salutes you in mystery.\n");
        }
      else
         {
         TP->catch_msg("You bid "+QTNAME(oblist[i])+" welcome.\n");
         oblist[i]->catch_msg(QCTNAME(TP) + " bids you welcome.\n");
        }
   }
   return 1;
}

/********************* scold *************************************/
int
scold(string str)
{
   object *oblist;
   
   if ((!strlen(str)) || (str == "all"))
      {
      write("You scold each and all.\n");
      all(" scolds each and all.");
      return 1;
   }
   
   oblist = parse_this(str, "[the] %l");
   if (!sizeof(oblist))
      {
      NF("Scold who?\n");    
      return 0;
   }
   
   actor("You give", oblist, " a real scolding.");
   target(" scolds you for being such a scourge.", oblist);
   all2act(" scolds", oblist, " for being such a scourge.");
   return 1;
}

/********************* scorn *****************************************/
int
scorn(string str)
{
   object *oblist;
   
   oblist = parse_this(str, "[the] %l");
   
   if (!sizeof(oblist))
      {
      NF("Scorn who?\n");
      return 0;
   }    
   
   actor("You scorn", oblist);
   target(" scorns you.", oblist);
   all2act(" scorns", oblist, " with great contempt.");
   return 1;
}

/*********************** sign *******************************/
int
sign(string str){
   object *oblist;
     if(!str){
      TP->catch_msg("You trace the ancient sign of mystery before yourself.\n");
      all(" raises a hand and cryptically traces a mysterious " +
         "sign before " + TP->query_objective() + "self.");
      return 1;
     }
      oblist = parse_this(str, "[at] %l");
      
      if (!sizeof(oblist))
         {
         NF("Sign who?\n");    
         return 0;
        }
      
      actor("You trace the ancient sign before", oblist);
      target(" raises a hand and traces an ancient sign before you.", oblist);
      all2act(" raises a hand and traces an ancient sign before", oblist);
    if(oblist[0]->query_prop(LIVE_I_UNDEAD)){
       oblist[0]->catch_msg("You feel dread from this horrible sign!\n");
   tell_room(environment(TP), QCTNAME(oblist[0]) + " gnashes " 
                + oblist[0]->query_possessive() + " teeth and holds up " +
                "a hand to fend away the sign!\n", oblist[0]);
    }
      return 1;
   

   }

/********************** wail *************************************/
   int
   wail(string str)
   {
      object *oblist;
      
      if (!strlen(str))
         {
         write("You wail loudly.\n");
         all(" wails loudly in anguish.");
         return 1;
        }
      
      oblist = parse_this(str, "[to] %l");
      
      if (!sizeof(oblist))
         {
         NF("Wail to whom?\n");    
         return 0;
        }
      
      actor("You wail in front of ", oblist);
      target(" wails in front of you.", oblist);
      all2act(" wails in front of", oblist);
      return 1;
   }

   /********************** weep *************************************/
   int
   weep(string str)
   {
      object *oblist;
      
      if (!strlen(str))
         {
         write("You weep, showing your deepest sorrow.\n");
         all(" weeps aloud, revealing " + TP->query_possessive() +
             " great sorrow.");
         return 1;
        }
      
      oblist = parse_this(str, "[to] %l");
      
      if (!sizeof(oblist))
         {
         NF("Weep before whom?\n");    
         return 0;
        }
      
      actor("You weep for", oblist);
      target(" weeps for you.", oblist);
      all2act(" weeps for", oblist);
      return 1;
   }
