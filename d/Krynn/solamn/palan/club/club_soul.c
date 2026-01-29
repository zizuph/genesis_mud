/* created by Aridor 12/13/93 
 * club_soul.c
 * This soul holds the general commands and feelings of the Prestigious Knights' Club
 *
 */

inherit "/cmd/std/command_driver";


#include "clubdefs.h"

#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>
#include "/d/Krynn/open/sys/composite.h"
/* Allows for constructs like: 'his blue shirt, his green pants and his red boots' */
#include <language.h>


/*****************************************************************************
 * Soul identifying and autoloading
 *****************************************************************************/

string get_soul_id() { return "Prestigious Knights Club"; }

int query_cmd_soul() { return 1; }

/*****************************************************************************
 * The list of verbs and functions. Please add new in alphabetical order.
 *****************************************************************************/

mapping
query_cmdlist()
{
    seteuid(getuid());
    return ([
"cadjust":"cadjust",
"cadvise":"cadvise",
"cbark":"cbark",
"cdraw":"cdraw",
"cnoemotion":"cnoemotion",
"coath":"coath",
"cobey":"cobey",
"crage":"crage",
"csheath":"csheath",
"cstern":"cstern",
"cstrap":"cstrap",
"ctense":"ctense",
"cwipe":"cwipe",
"draw":"cdraw",
"help":"help",
"sheath":"csheath",
    ]);
}

static mixed
parse_this(string str, string form)
{
    object   *oblist, *tmplist;
    int      i;

    tmplist = ({});
    if (!CAN_SEE_IN_ROOM(this_player()))
        return tmplist;

    if (!str || (!parse_command(lower_case(str), environment(this_player()),
                         form, oblist)))
        return ({});

    oblist = NORMAL_ACCESS(oblist, 0, 0);

    if (!sizeof(oblist))
        return ({});

    for (i = 0; i < sizeof(oblist); i++)
    {
        if (objectp(oblist[i]) && living(oblist[i]) &&
                (this_player() != oblist[i]) &&
                CAN_SEE(this_player(), oblist[i]))
            tmplist = tmplist + ({ oblist[i] });
    }
    return tmplist;
}

/*****************************************************************************
 * Here follows the functions. New functions should be added in alphabetic
 * order.
 ****************************************************************************/

/*
 * Global variables
 *
 */


/******************************* cAdjust ************************************
 * Suggested by Kayen
 */
int
cadjust(string str)
{
    mixed *arm, *to_adjust = ({ });
    mixed *id_things;
    int i;
    NF("Adjust what?\n");
    if (!str)
      return 0;
    arm = TP->query_armour(-1);
    id_things = FIND_STR_IN_OBJECT(str,TP);
    for(i = 0; i<sizeof(arm); i++)
      if (str == "all" || member_array(arm[i],id_things) >= 0)
	to_adjust += ({ arm[i] });
    NF("You don't wear such armour.\n");
    if (to_adjust == ({}))
      return 0;
    setuid();
    seteuid(getuid());
    tell_room(E(TP), QCTNAME(TP) + " adjusts " +
	      MYART_COMPOSITE_LIVE(to_adjust, POSSESSIVE(TP)) +
	      " to fit more perfectly.\n",TP);
    TP->catch_msg("Being a little uncomfortable, you adjust " +
		  MYART_COMPOSITE_LIVE(to_adjust,"your") + " to fit better.\n");
    return 1;
}

/******************************* cAdvise ************************************/
int
cadvise(string str)
{
  NF("Advise what?\n");
  if (!str)
    return 0;
  tell_room(E(TP), QCTNAME(TP) + " advises " + str + ".\n", TP);
  tell_object(TP, "You advise " + str + "\n");
  return 1;
}


/******************************* cBark ************************************/
int
cbark(string str)
{
  NF("Bark what?");
  if (!str)
    return 0;
  tell_room(E(TP), QCTNAME(TP) + " barks: " + str + "!\n", TP);
  tell_object(TP, "You bark: " + str + "!\n");
  return 1;
}


/******************************* cDraw ************************************/
int
cdraw(string str)
{
  mixed tmp;
  object *ob;
  object sheathed = TP->query_prop(CLUB_O_SHEATHED_WEAPON);
  object scab = (IS_CLUB_MEMBER(TP));
  if (!sheathed)
    {
      if (scab->is_a_real_scabbard())
	{
	  TP->catch_msg("You don't have a weapon sheathed in your " +
			"scabbard you could draw.\n");
	  tell_room(E(TP), QCTNAME(TP) + " reaches for " + POSSESSIVE(TP) +
		    " scabbard, but notices too late that " +
		    TP->query_pronoun() + " has no weapon sheathed.\n",TP);
	}
      else
	{
	  TP->catch_msg("You don't have a weapon in your holster" +
			" you could draw.\n");
	  tell_room(E(TP), QCTNAME(TP) + " reaches for " + POSSESSIVE(TP) +
		    " holster, but notices too late that " +
		    TP->query_pronoun() + " has no weapon in it.\n",TP);

	}
      return 1;
    }
  sheathed->remove_prop(OBJ_I_NO_DROP);
  tmp = sheathed->query_prop(CLUB_M_TMP_NO_DROP);
  if (tmp)
    sheathed->add_prop(OBJ_I_NO_DROP, tmp);
  sheathed->unset_no_show();
  sheathed->unset_no_show_composite();
  TP->remove_prop(CLUB_O_SHEATHED_WEAPON);
  TP->catch_msg("You draw the " + sheathed->short() + ".\n");
  tell_room(E(TP), QCTNAME(TP) + " draws " + POSSESSIVE(TP) + " " + sheathed->short() +
	    " from " + POSSESSIVE(TP) + " " + scab->query_my_type() + ".\n",TP);
/*  if (TP->wield(sheathed) == 1)*/
  sheathed->wield_me();

  if (!str)
    return 1;
  TP->command("shout Est Sularus oth Mithas.   My honor is my life!\n");
  write("- all in one swift, flowing motion. You " +
      "valiantly charge towards the enemy.\n");
  say("- all in one swift, flowing motion. " + capitalize(PRONOUN(TP)) +
      " valiantly charges towards the enemy.\n");
  TP->command("kill " + str);
  return 1;
}


/******************************* cNoEmotion ************************************/
int
cnoemotion(string str)
{
  tell_room(E(TP), QCTNAME(TP) + " shows no emotion on " + POSSESSIVE(TP) + " ice cold face.\n", TP);
  tell_object(TP, "You don't allow any emotion to show on your face.\n");
  TP->change_prop(LIVE_S_SOULEXTRA, "showing no emotion");
  return 1;
}


/******************************* cOath ************************************/
int
coath(string str)
{
  tell_room(E(TP), QCTNAME(TP) + " announces: Est Sularus oth Mithas.   My honor is my life!\n", TP);
  tell_object(TP, "You announce: Est Sularus oth Mithas.   My honor is my life!\n");
  return 1;
}


/******************************* cObey ************************************/
int
cobey(string str)
{
  object *pers;
  NF("Obey who?\n");
  if (!str)
    return 0;
  pers = FIND_STR_IN_OBJECT(str, E(TP));
  if (!sizeof(pers))
    return 0;
  if (pers[0]->query_prop(LIVE_I_IS) && pers[0] != TP)
    {
      tell_room(E(TP), QCTNAME(TP) + " bows to " + QTNAME(pers[0]) + " in obedience.\n",({pers[0],TP}));
      TP->catch_msg("You bow to " + QTNAME(pers[0]) + " in obedience.\n");
      pers[0]->catch_msg(QCTNAME(TP) + " bows to you in obedience.\n");
      return 1;
    }
  return 0;
}


/******************************* cRage **************************************/
int
crage(string str)
{
    object scab = IS_CLUB_MEMBER(TP);
    object sheathed = TP->query_prop(CLUB_O_SHEATHED_WEAPON);
    string his_her = POSSESSIVE(TP);
    string scabbard = (scab->is_a_real_scabbard() ? "scabbard" : "holster");

    write("Burning with rage, you are about to draw your weapon.\n");
    if (sheathed)
	say("Eyes burning with controlled rage, " + QTNAME(TP) + " draws " +
	    his_her + " " + sheathed->short() + " halfway from " +
	    his_her + " " + scabbard + ".\n");
    else
	say("Eyes burning with controlled rage, " + QTNAME(TP) + " reaches for " +
	    his_her + " " + scabbard + ", realizing too late that there is no " +
	    "weapon " + (scabbard == "scabbard" ? "sheathed" : "in it") + ".\n");
    return 1;    
}

/******************************* cSheath ************************************/
int
csheath(string str)
{
  mixed tmp;
  object *can_sheath;
  object scab = IS_CLUB_MEMBER(TP);
  object sheathed = TP->query_prop(CLUB_O_SHEATHED_WEAPON);
  mixed *wep = TP->query_weapon(-1);
  string the_wep;
  if (!str)
    {
      if (wep == ({}))
	{
	  NF("You are not wielding any weapons.\n");
	  return 0;
	}
      if (sheathed)
	{
	  NF("There is already a weapon in the " + scab->query_my_type() + ".\n");
	  return 0;
	}
      sheathed = wep[0];
      if (scab->is_a_real_scabbard())
	{
	  NF("You need a holster to put something else in it but a sword or a knife.\n");
	  if (sheathed->weapon_type() != "sword" && sheathed->weapon_type() != "knife")
	    return 0;
	}
      else
	{
	  NF("You need a scabbard to put a sword or a knife in it.\n");
	  if (sheathed->weapon_type() == "sword" || sheathed->weapon_type() == "knife")
	    return 0;
	}
      TP->add_prop(CLUB_O_SHEATHED_WEAPON, sheathed);
      the_wep = wep[0]->short();
/*      TP->unwield(sheathed);*/
      sheathed->unwield_me();
      sheathed->add_prop(CLUB_M_TMP_NO_DROP, sheathed->query_prop(OBJ_M_NO_DROP));
      sheathed->add_prop(OBJ_M_NO_DROP, 1);
      sheathed->set_no_show();
      sheathed->set_no_show_composite();
      if (scab->is_a_real_scabbard())
	{
	  TP->catch_msg("You sheath your " + the_wep + ".\n");
	  tell_room(E(TP),QCTNAME(TP) + " sheathes " +
		    POSSESSIVE(TP) + " " + the_wep + ".\n",TP);
	}
      else
	{
	  TP->catch_msg("You put your " + the_wep + " into your holster.\n");
	  tell_room(E(TP),QCTNAME(TP) + " puts " + POSSESSIVE(TP) + " " +
		    the_wep + " into " + POSSESSIVE(TP) + " holster.\n",TP);

	}
      return 1;
    }
  else
    { 
      NF("There is already a weapon in the " + scab->query_my_type() + ".\n");
      if (sheathed)
	return 0;
      can_sheath = FIND_STR_IN_OBJECT(str, TP);
      NF("You don't have a " + str + ".\n");
      if (!sizeof(can_sheath))
	return 0;
      sheathed = can_sheath[0];
      NF("You can't put THAT into your " + scab->query_my_type() + ".\n");
      if (!sheathed->weapon_type())
	return 0;
      if (sheathed->query_wielded() == TP)
	sheathed->unwield_me();
      if (scab->is_a_real_scabbard())
	{
	  NF("You need a holster to put something else in it but a sword or a knife.\n");
	  if (sheathed->weapon_type() != "sword" && sheathed->weapon_type() != "knife")
	    return 0;
	}
      else
	{
	  NF("You need a scabbard to put a sword or a knife in it.\n");
	  if (sheathed->weapon_type() == "sword" || sheathed->weapon_type() == "knife")
	    return 0;
	}
      the_wep = sheathed->short();
      TP->add_prop(CLUB_O_SHEATHED_WEAPON, sheathed);
      sheathed->add_prop(CLUB_M_TMP_NO_DROP, sheathed->query_prop(OBJ_M_NO_DROP));
      sheathed->add_prop(OBJ_M_NO_DROP, 1);
      sheathed->set_no_show();
      sheathed->set_no_show_composite();
      if (scab->is_a_real_scabbard())
	{ 
	  TP->catch_msg("You sheath your " + the_wep + ".\n");
	  tell_room(E(TP),QCTNAME(TP) + " sheathes " + POSSESSIVE(TP) +
		    " " + the_wep + ".\n",TP);
	}
      else
	{
	  TP->catch_msg("You put your " + the_wep + " in your holster.\n");
	  tell_room(E(TP),QCTNAME(TP) + " puts " + POSSESSIVE(TP) + " " +
		    the_wep + " in " + POSSESSIVE(TP) + " holster.\n",TP);  
	}
      return 1;
    }
}


/******************************* cStern ************************************/
int
cstern(string str)
{
    object scab = IS_CLUB_MEMBER(TP);
    object sheathed = TP->query_prop(CLUB_O_SHEATHED_WEAPON);
    string his_her = POSSESSIVE(TP);
    string scabbard = (scab->is_a_real_scabbard() ? "scabbard" : "holster");

    write("You straighten up, looking stern and forboding.\n");
    if (sheathed)
   say(C(his_her) + " face stern and forboding, " + QTNAME(TP) +
	    " straightens up, " + his_her + " hand riding lightly on the " +
	    sheathed->short() + " in " + his_her + " " + scabbard + ".\n");
    else
   say(C(his_her) + " face stern and forboding, " + QTNAME(TP) +
	    " straightens up, " + his_her + " hand riding lightly on " +
	    his_her + " empty " + scabbard + ".\n");

    return 1;
}

/******************************* cStrap ************************************/
int
cstrap(string str)
{
  object scab = IS_CLUB_MEMBER(TP);
  string location;
  NF("You can have your holster strapped to your back only.\n");
  if (!scab->is_a_real_scabbard())
    return 0;
  NF("Strap where?\n");
  if (!str)
    return 0;
  NF("You can strap your scabbard only to your side or to your back.\n");
  if (str != "side" && str != "back")
    return 0;
  location = str;
  TP->change_prop(CLUB_S_SCABBARD_LOCATION, location);
  scab->change_location(location);
  tell_object(TP, "You unbuckle your scabbard and strap it to your " +
	      location + ".\n");
  tell_room(E(TP), QCTNAME(TP) + " unbuckles " + POSSESSIVE(TP) +
	    " scabbard and straps it to " + POSSESSIVE(TP) + " " +
	    location + ".\n", TP);
  return 1;
}


/******************************* cTense ***********************************/
int
ctense(string str)
{
    object scab = IS_CLUB_MEMBER(TP);
    object sheathed = TP->query_prop(CLUB_O_SHEATHED_WEAPON);
    string his_her = POSSESSIVE(TP);
    string scabbard = (scab->is_a_real_scabbard() ? "scabbard" : "holster");

    write("You start to feel tension building up inside.\n");
    if (sheathed)
	say(QCTNAME(TP) + " looks tense, " + his_her + " hand playing lightly " +
	    "over the hilt of the " + sheathed->short() + " in " + his_her + " " +
	    scabbard + ".\n");
    else
	say(QCTNAME(TP) + " looks tense, " + his_her + " hand playing lightly " +
	    "over " + his_her + " empty " + scabbard + ".\n");
    return 1;
}


/******************************* cWipe ************************************/
static int
has_a_blade(object wep)
{
  return (wep->weapon_type() != "club" && wep->weapon_type() != "polearm" &&
	  wep->weapon_type() != "javelin");
}


int
cwipe(string str)
{
  mixed *wep = TP->query_weapon(-1);
  string s = ((sizeof(wep) > 1) ? "s" : "");
  int i, has_blade = 1;
  for (i = 0; i<sizeof(wep); i++)
    has_blade = has_blade && has_a_blade(wep[i]);
  NF("You don't wield any weapons.\n");
  if (wep == ({}))
    return 0;
  tell_room(E(TP), QCTNAME(TP) + " wipes the blood of the last battle from " +
	    (has_blade ? ("the blade" + s + " of ") : "") +
	    COMPOSITE_DEAD(wep) + ".\n", TP);
  tell_object(TP, "You wipe the blood of the last battle from " +
	      (has_blade ? ("the blade" + s + " of ") : "") +
	      "your weapon" + ((sizeof(wep) > 1) ? "s" : "") + ".\n");
  return 1;
}


/******************************* help ************************************/
int
help(string str)
{
  if (!str)
    return 0;
  if (str != "knights club")
    return 0;
  tell_object(TP,"The following commands are available:\n" +
	         "  - cadjust <what>        Adjust some armour to fit better\n" +
	         "  - cadvise <what>        Give advice to people\n" +
	         "  - cbark <command>       Bark a command\n" +
	         "  - cdraw                 Draw the weapon from the scabbard\n" +
	         "    cdraw <person>        Draw weapon and attack person in one motion\n" +
	         "  - cnoemotion            Show no emotion whatsoever\n" + 
	         "  - coath                 Hail the oath of the Knights\n" +
	         "  - cobey <person>        Bow in obedience to person\n" +
	         "  - crage                 Burning with rage\n" +
	         "  - csheath <weapon>      Sheath a weapon in the scabbard\n" +
	         "  - cstern                Look stern and forboding\n" +
	         "  - cstrap 'side|back'    Strap your scabbard to either your side or your back\n" +
	         "  - ctense                Feel tension building up\n" +
	         "  - cwipe                 Wipe your weapons clean after a battle\n" +
	         "  - draw                  Same as 'cdraw'\n" +
	         "  - help knights club     Get this screen\n" +
	         "  - sheath <weapon>       Same as 'csheath'.\n");
  return 1;
} 

