/*******************************************************************\
| SOUL_EMOTES_I_P.H                                                 |
\*******************************************************************/

/*
 * 10/10/08 Lavellan    Added three dragons
 * 07/06/14 Arandir     Added two dragon army dragons and fire lizard
 * 06/09/20 Arandir     Fixed use of Q macros instead of X macros
 * 06/09/02 Arandir     Fixed use of XOBJ style macros
 * 04/08/17 Arandir     Added action attributes to other emote calls
 * 04/08/15 Arandir     Logging of unknown dragons
 *                      Added action attributes to parse_this
 * 03/10/08 Arandir     Fixed typos in mpoke
 * 03/09/20 Arandir     Added the mpoke emote
 * 03/09/14 Arandir     Removed the thys and thous in error messages
 * 03/09/07 Arandir     Fixed typos due to all2act not expanding VBFC
 * 03/07/24 Arandir     Support for claiming dragon as kin
 * 03/07/02 Arandir     Polished up
 * 02/05/03 Arandir	Ported to new area without rewrite
 * 99/02/01 Lilith	Emotes updated and added
 * 96/04/16 Cirion	Created
 *
 */

// This file is included rather than inherited
// because LPC cannot handle diamond inheritance

//-------------------------------------------------------------------

/*
 * Function name : m_action_inspired
 *
 */

int m_action_inspired (string sArgs)
{
  object oWho = this_player ();
  object *aoObjects;

  notify_fail ("By whom or what are you inspired ?\n");

  if (!strlen (sArgs))
  {
    write ("You stand momentarily transfixed by a shaft of " +
           "inspiration as one of the teachings of Segoy becomes " +
           "suddenly clear to you.\n");
    allbb (" stands momentarily transfixed, an ecstatic, " +
           "enlightened look upon " + XPOS (oWho) + " face.", "",
           ACTION_VISUAL | ACTION_INGRATIATORY);
    M_SOULDESC ("standing transfixed");

    return (TRUE);
  }

  aoObjects = parse_this (sArgs, "[by] [the] %i", ACTION_VISUAL | ACTION_INGRATIATORY);
  if(!sizeof (aoObjects)) return (FALSE);

  actor ("You are so inspired by", aoObjects, " that you stand as " +
         "though transfixed, suffused with enlightened ecstacy.");
  targetbb (" stands as though transfixed, apparently inspired " +
            "by you on a deeply spiritual level.", aoObjects, "",
            ACTION_VISUAL | ACTION_INGRATIATORY);
  all2actbb (" stands as though transfixed, apparently inspired " +
             "by", aoObjects, " on a deeply spiritual level.", "",
             ACTION_VISUAL | ACTION_INGRATIATORY);

  return (TRUE);
}

/*
 * Function name: m_action_karma
 */

int m_action_karma (string sArgs)
{
    object oWho = this_player ();
    
    string karmaDesc = "You have learned " + oWho->m_get_karma_description()
        + " lessons from your enemies.\n";
    
    write(karmaDesc);
    
    return (TRUE);
}

/*
 * Function name : m_action_kiai
 *
 */

int m_action_kiai (string sArgs)
{
  object oWho = this_player ();
  string sFragmentHow;

  if (oWho->query_prop (LIVE_M_MOUTH_BLOCKED))
  {
    notify_fail ("You cannot seem to use your mouth.\n");
    return (FALSE);
  }

  if (oWho->query_fatigue () < 5)
  {
    notify_fail ("You are too tired to utter a combat cry.\n");
    return (FALSE);
  }

  // This is a remnant from the time when a combat cry
  // could scare opponents away. The fatigue drain is
  // not justified now ...

  oWho->add_fatigue (-15);

  switch (oWho->query_skill (SS_UNARM_COMBAT))
  {
    case -99 .. 5:  sFragmentHow = "tiny";          break;
    case  6 .. 10:  sFragmentHow = "pathetic";      break;
    case 11 .. 20:  sFragmentHow = "amateur";       break;
    case 21 .. 28:  sFragmentHow = "loud";          break;
    case 29 .. 36:  sFragmentHow = "rather loud";   break;
    case 37 .. 50:  sFragmentHow = "very loud";     break;
    case 51 .. 65:  sFragmentHow = "roaring";       break;
    case 66 .. 80:  sFragmentHow = "titanic";       break;
    case 81 .. 90:  sFragmentHow = "deafening";     break;
    case 91 .. 999: sFragmentHow = "heroic dragon"; break;
  }
  sFragmentHow = LANG_ADDART (sFragmentHow);

  write ("You utter " + sFragmentHow + " combat cry.\n");
  all (" utters " + sFragmentHow + " combat cry.", "", ACTION_AURAL | ACTION_THREATENING);

  return (TRUE);
}


/*
 * Function name : m_action_kill
 *
 */

int m_action_kill (string sArgs)
{
  object oWho = this_player ();
  object *aoObjects;
  string *asAdverb;

  notify_fail ("Whom do you wish to kill ?\n");

  asAdverb = parse_adverb_with_space (sArgs, "fluidly", FALSE);

  if (!strlen (asAdverb [0])) return (FALSE);

  aoObjects = parse_this (asAdverb [0], "[the] %l", ACTION_VISUAL | ACTION_THREATENING);
  aoObjects -= ({ oWho });

  if (sizeof (aoObjects) != 1) return (FALSE);

  actor ("Mind and body become one as you" + asAdverb [1] + " slip into " +
         "a stance from which you can attack", aoObjects);
  targetbb ("'s face looks serenely determined as " + XPNOUN (oWho) +
            " focuses " + XPOS (oWho) + " eyes upon you and slips" +
            asAdverb [1] + " into a distinctly martial stance.", aoObjects, "",
            ACTION_VISUAL | ACTION_THREATENING);
  all2actbb (asAdverb [1] + " slips into a stance from which " +
             XPNOUN (oWho) + " can attack", aoObjects, "",
             ACTION_VISUAL | ACTION_THREATENING);

  oWho->command ("$kill " + OB_NAME (aoObjects [0]));

  return (TRUE);
}


int m_action_kin (string sArgs)
{
  object oWho = this_player ();
  object *aoObjects;
  object oObject;

  notify_fail ("Which dragon do you wish to claim your kin ?\n");

  aoObjects = parse_this (sArgs, "[the] %l", ACTION_VISUAL | ACTION_INGRATIATORY);
  aoObjects -= ({ oWho });

  if (sizeof (aoObjects) != 1) return (FALSE);
  if (!dg_is_dragon (aoObjects [0])) return (FALSE);

  // We remember the dragons that were claimed kin.

  switch (MASTER_OB (aoObjects [0]))
  {
    // These are used for the guru quest.

    case "/d/Ansalon/balifor/flotsam_forest/living/faery_dragon":
      oWho->m_add_kin ("flotsam faery dragon");
      break;
    case "/d/Ansalon/balifor/flotsam_forest/living/g_dragon":
      oWho->m_add_kin ("flotsam green dragon");
      break;
    case "/d/Ansalon/goodlund/nethosak/forest/npc/b_dragon":
      oWho->m_add_kin ("mithas black dragon");
      break;
    case "/d/Calia/eldoral/npc/firestorm":
      oWho->m_add_kin ("calia shackled dragon");
      break;
    case "/d/Calia/mountain/monsters/polymorph_demon":
      oWho->m_add_kin ("calia ice demon");
      break;
    case "/d/Kalad/common/wild/pass/npc/deep_dragon":
      oWho->m_add_kin ("kalad deep dragon");
      break;
    case "/d/Khalakhor/inisi/roke/npc/bluedragon":
      oWho->m_add_kin ("cadu blue dragon");
      break;
    case "/d/Krynn/common/npcs/khisanth":
      oWho->m_add_kin ("krynn black dragon");
      break;
    case "/d/Krynn/common/npcs/sleet":
      oWho->m_add_kin ("icewall white dragon");
      break;
    case "/d/Terel/dark/mon/drake":
      oWho->m_add_kin ("avenir cave drake");
      break;
    case "/d/Krynn/pax/monster/ember":
      oWho->m_add_kin ("krynn red dragon");
      break;
    case "/d/Krynn/pax/monster/flamestrike":
      oWho->m_add_kin ("krynn old dragon");
      break;
    case "/d/Terel/mountains/obj/dragon":
      oWho->m_add_kin ("terel black dragon");
      break;
    case "/d/Terel/mountains/redlair/monster/dragon":
      oWho->m_add_kin ("terel red dragon");
      break;
    case "/d/Terel/ribos/monster/evil_thang":
      oWho->m_add_kin ("ribos evil dragon");
      break;

    // These are here just for completeness.

    case "/d/Ansalon/guild/dragonarmy/dragons/fear_dragon":
      oWho->m_add_kin ("ansalon fear dragon");
      break;
    case "/d/Ansalon/guild/dragonarmy/dragons/strike_dragon":
      oWho->m_add_kin ("ansalon strike dragon");
      break;
    case "/d/Khalakhor/inisi/roke/npc/dragon":
      oWho->m_add_kin ("roke drooling dragon");
      break;
    case "/d/Sparkle/guilds/monks/monastery/npc/mzenska":
      oWho->m_add_kin ("sparkle fire lizard");
      break;

    case "/d/Avenir/common/dark/mon/drake":
      oWho->m_add_kin ("avenir cave drake");
      break;
    case "/d/Krynn/solamn/eplains/living/b_dragon":
      oWho->m_add_kin ("krynn blue dragon");
      break;
    case "/d/Krynn/icewall/castle2/npc/attackdragon":
      oWho->m_add_kin ("icewall attack dragon");
      break;
    case "/d/Krynn/common/warfare/npcs/red/young_red_dragon":
      oWho->m_add_kin ("krynn young red dragon");
      break;

    // We want to know about unknown dragons because we
    // need to remember all dragons by name ...

    default:
      s_log (M_LOG_DEBUG, "Unknown dragon encountered.", aoObjects [0]);
      break;
  }

  actor ("Looking directly at", aoObjects, ", you take a deep breath " +
         "and draw a likeness of a dragon tooth in the air, ceremoniously " +
         "proclaiming " + XOBJ (aoObjects [0]) + " your kin. You feel " +
         "your head swoon as the simple gesture puts you in a trance and " +
         "a feeling of sameness with the dragon engulfs you.");
  targetbb (" looks at you with a trancelike expression, drawing a " +
            "likeness of a dragon tooth in the air just in front of you.",
            aoObjects, "", ACTION_VISUAL | ACTION_INGRATIATORY);
  all2actbb (" looks at", aoObjects, " with a trancelike expression, drawing " +
             "a likeness of a dragon tooth in the air just in front of " +
             XOBJ (aoObjects [0]) + ".", "", ACTION_VISUAL | ACTION_INGRATIATORY);

  return (TRUE);
}


/*
 * Function name : m_action_knuckles
 *
 */

int m_action_knuckles (string sArgs)
{
  object oWho = this_player ();
  object *aoObjects;
  string *asAdverb;

  notify_fail ("Whose knuckles do you wish to tend ?\n");

  asAdverb = parse_adverb_with_space (sArgs, "gingerly", 0);

  if (!strlen (asAdverb [0]))
  {
    write ("You nurse your knuckles" + asAdverb [1] +
           ", hoping the pain will subside.\n ");
    allbb (" nurses "  + XPOS (oWho) + " knuckles" +
           asAdverb [1] + ", in an effort to stop the pain.", "",
           ACTION_CONTACT | ACTION_VISUAL | ACTION_INGRATIATORY);

    return (TRUE);
  }

  aoObjects = parse_this (asAdverb [0], "[to] [the] %l", ACTION_CONTACT | ACTION_VISUAL | ACTION_INGRATIATORY);
  if (!sizeof (aoObjects)) return (FALSE);

  actor ("You nurse", aoObjects, "'s knuckles" + asAdverb [1] + ", in an effort to stop the pain.");
  targetbb (asAdverb [1] + " tends to your wounded knuckles.", aoObjects, "", ACTION_CONTACT | ACTION_VISUAL | ACTION_INGRATIATORY);
  all2actbb (asAdverb [1] + " nurses", aoObjects, "'s knuckles.", "", ACTION_CONTACT | ACTION_VISUAL | ACTION_INGRATIATORY);

  return (TRUE);
}


/*
 * Function name : m_action_look
 *
 */

int m_action_look (string sArgs)
{
  object oWho = this_player ();
  object *aoObjects;
  string *asAdverb;
  string sFragmentThoughts;

  notify_fail ("At whom do you wish to look ?\n");

  if (m_is_monk (oWho, SS_OCCUP))
  {
    asAdverb = parse_adverb_with_space (sArgs, "confidently", FALSE);
  }
  else
  {
    asAdverb = parse_adverb_with_space (sArgs, "carefully", FALSE);
  }

  if (!strlen (asAdverb [0]))
  {
    write ("You look" + asAdverb [1] + " about you, feeling " +
           "completely secure and self-reliant.\n");
    all (" looks" + asAdverb [1] + " around, to all appearances quite " +
         "secure and self-reliant.", "", ACTION_VISUAL);
    M_SOULDESC ("looking dangerous");

    return (TRUE);
  }

  aoObjects = parse_this (asAdverb [0], "[at] [the] %l", ACTION_VISUAL);
  if (sizeof (aoObjects) != 1) return (FALSE);

  if (m_is_monk (oWho, SS_OCCUP))
  {
    sFragmentThoughts = XPNOUN (aoObjects [0]) + " certainly entertains " +
                        "no second thoughts about trifling with you.";
  }
  else
  {
    sFragmentThoughts = "you hope " + XPNOUN (aoObjects [0]) + " will " +
                        "think twice before trifling with you.";
  }

  actor ("You" + asAdverb [1] + " look", aoObjects, " over, so secure in your " +
         "abilities that " + sFragmentThoughts);
  target (" looks" + asAdverb [1] + " at you, to all appearances quite " +
          "secure and self-reliant.", aoObjects, "", ACTION_VISUAL);
  all2act (" looks" + asAdverb [1] + " at", aoObjects, ", to all appearances " +
           "quite secure and self-reliant.", "", ACTION_VISUAL);

  return (TRUE);
}


/*
 * Function name : m_action_poke
 *
 */

int m_action_poke (string sArgs)
{
  object oWho = this_player ();
  object *aoObjects;
  string *asAdverb;

  notify_fail ("Whom do you wish to poke ?\n");

  if (!strlen (sArgs)) return (FALSE);

  aoObjects = parse_this (sArgs, "[the] %l", ACTION_CONTACT | ACTION_VISUAL);

  switch (sizeof (aoObjects))
  {
    case 0:
      return (FALSE);

    case 1:
      actor ("You poke", aoObjects, " in the ribs, indicating just " +
             "how fat and lazy " + XPNOUN (aoObjects [0]) + " has become.");
      targetbb (" pokes you in the ribs, indicating just " +
                "how fat and lazy you have become.", aoObjects, "",
                ACTION_CONTACT | ACTION_VISUAL);
      all2actbb (" pokes", aoObjects, "in the ribs, indicating just " +
                 "how fat and lazy " + XPNOUN (aoObjects [0]) + " has become.", "",
                 ACTION_CONTACT | ACTION_VISUAL);
      break;

    default:
      actor ("You poke", aoObjects, " in the ribs, indicating just " +
             "how fat and lazy they have become.");
      targetbb (" pokes you in the ribs, indicating just " +
                "how fat and lazy you have become.", aoObjects, "",
                ACTION_CONTACT | ACTION_VISUAL);
      all2actbb (" pokes", aoObjects, "in the ribs, indicating just " +
                 "how fat and lazy they have become.", "",
                 ACTION_CONTACT | ACTION_VISUAL);
      break;
  }

  return (TRUE);
}


/*
 * Function name : m_action_pray
 *
 */

int m_action_pray (string sArgs)
{
  write ("You pray that the strength and wisdom you are developing " +
         "through your study of the dragon-discipline will not fail " +
         "you in your moment of need.\n");
  allbb (" appears to concentrate for a long moment, as though in " +
         "prayer.", "", ACTION_VISUAL);
  M_SOULDESC ("looking pious");

  return (TRUE);
}


/*
 * Function name : m_action_pity
 *
 */

int m_action_pity (string sArgs)
{
  object oWho = this_player ();
  object *aoObjects;
  object *aoWeapons;

  notify_fail ("For whom do you feel pity ?\n");

  if (!strlen (sArgs))
  {
    write ("You find yourself pitying all those who are lacking " +
           "in dragon discipline.\n");
    allbb (" looks about " + XOBJ (oWho) + " with an expression of " +
           "pity on " + XPOS (oWho) + " face.", "", ACTION_VISUAL);

    return (TRUE);
  }

  aoObjects = parse_this (sArgs, "[for] [the] %l", ACTION_VISUAL);
  if (sizeof (aoObjects) != 1) return (FALSE);

  aoWeapons = aoObjects [0]->query_weapon (-1);

  if (!sizeof (aoWeapons))
  {
    if (m_is_monk (aoObjects [0]))
    {
      notify_fail ("Why would you pity someone who is mastering " +
                   "unarmed combat for a dependence upon weapons ?\n");
      return (FALSE);
    }

    actor ("You pity", aoObjects, " for " + XPOS (aoObjects [0]) + " dependence upon weapons.");
    targetbb (" appears to pity you for your dependence upon weapons.", aoObjects, "", ACTION_VISUAL);
    all2actbb (" appears to pity", aoObjects, " for " + XPOS (aoObjects [0]) + " dependence upon weapons.", "", ACTION_VISUAL);

    return (TRUE);
  }

  actor ("You look from", aoObjects, " to " + LANG_THESHORT (aoWeapons [0]) + " " +
         XPNOUN (aoObjects [0]) + " wields, pitying " +
         XOBJ (aoObjects [0]) + " for " +
         XPOS (aoObjects [0]) + " dependence upon weapons.");
  targetbb (" looks from you to your " + XSHORT (aoWeapons [0]) + " and back, " +
            "a look of pity upon " + XPOS (oWho) + " face.", aoObjects, "",
            ACTION_VISUAL);
  all2actbb (" looks from", aoObjects," to " + LANG_THESHORT (aoWeapons [0]) + " " +
             XPNOUN (aoObjects [0]) + " wields, a look of pity on " +
             XPOS (oWho) + " face.", "", ACTION_VISUAL);

  return (TRUE);
}

//-------------------------------------------------------------------

