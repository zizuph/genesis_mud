/*******************************************************************\
| SOUL_SIGNING.H                                                    |
\*******************************************************************/

/*
 * 07/06/03 Arandir     Fixed a typo in msign and msignal
 * 06/09/02 Arandir     Fixed use of XOBJ style macros
 * 04/03/29 Arandir     Minor additions to distortions
 * 03/12/23 Arandir     Some extra spaces removed
 * 03/12/21 Arandir     Created
 *
 */

// This file is included rather than inherited
// because LPC cannot handle diamond inheritance

//-------------------------------------------------------------------

#define M_SUSPECT_WORD_LENGTH   15
#define M_INVALID_WORD_LENGTH   30

#define M_WORD_DISTORTIONS_BEFORE ([ \
  "i'm"         : "i am", \
  "you're"      : "you are", \
  "he's"        : "he is", \
  "she's"       : "she is", \
  "it's"        : "it is", \
  "we're"       : "we are", \
  "they're"     : "they are", \
  "i've"        : "i have", \
  "you've"      : "you have", \
  "he's got"    : "he has got", \
  "she's got"   : "she has got", \
  "it's got"    : "it has got", \
  "we've"       : "we have", \
  "they've"     : "they have", \
  "i'll"        : "i will", \
  "you'll"      : "you will", \
  "he'll"       : "he will", \
  "she'll"      : "she will", \
  "it'll"       : "it will", \
  "we'll"       : "we will", \
  "they'll"     : "they will", \
  "i'd"         : "i would", \
  "you'd"       : "you would", \
  "he'd"        : "he would", \
  "she'd"       : "she would", \
  "it'd"        : "it would", \
  "we'd"        : "we would", \
  "they'd"      : "they would", \
  "don't"       : "do not", \
  "gimme"       : "give me", \
  "gonna"       : "going to", \
  "gotta"       : "got to", \
  ":)"          : "smile", \
  ":-)"         : "smile", \
  ":("          : "sadness", \
  ":-("         : "sadness", \
])

#define M_WORD_DISTORTIONS_AFTER ([ \
  "a"           : "", \
  "an"          : "", \
  "the"         : "", \
  "as"          : "", \
  "at"          : "", \
  "by"          : "", \
  "in"          : "", \
  "of"          : "", \
  "on"          : "", \
  "so"          : "", \
  "to"          : "", \
  "for"         : "", \
  "am"          : "be", \
  "are"         : "be", \
  "is"          : "be", \
  "has"         : "have", \
  "will"        : "shall", \
])

//-------------------------------------------------------------------

/*******************************************************************\
| Speech distortion                                                 |
\*******************************************************************/

string m_signing_distort (string sText, int iRank)
{
  string *asWorded;
  string *asWordedTemporary;
  string sTextLowercase;
  string sTextTemporary;
  string sWord;
  mixed  xDistortion;
  int    iCharacter;
  int    iIndex;

  sTextLowercase = lower_case (sText);
  sTextLowercase = dg_remove_whitespace (sTextLowercase);
  sTextLowercase = dg_remove_doublespace (sTextLowercase);

  // First level of replacemens is done before filtering.

  asWorded = explode (sTextLowercase, " ");

  for (iIndex = 0 ; iIndex < sizeof (asWorded) ; iIndex ++)
  {
    xDistortion = M_WORD_DISTORTIONS_BEFORE [asWorded [iIndex]];
    if (stringp (xDistortion))
    {
      asWorded [iIndex] = xDistortion;
    }
  }

  sTextLowercase = implode (asWorded, " ");

  // Do some simple filtering on character level.

  sTextTemporary = "";
  for (iIndex = 0 ; iIndex < strlen (sTextLowercase) ; iIndex ++)
  {
    iCharacter = sTextLowercase [iIndex];
    if (dg_is_alphanumeric_or_space (iCharacter))
    {
      sTextTemporary += strchar (iCharacter);
    }
    else sTextTemporary += " ";
  }

  sTextLowercase = sTextTemporary;

  // Second level of replacement is done after filtering.

  asWorded = explode (sTextLowercase, " ");

  for (iIndex = 0 ; iIndex < sizeof (asWorded) ; iIndex ++)
  {
    xDistortion = M_WORD_DISTORTIONS_AFTER [asWorded [iIndex]];
    if (stringp (xDistortion))
    {
      asWorded [iIndex] = xDistortion;
    }
  }

  sTextLowercase = implode (asWorded, " ");

  // The repeated implosions and explosions are necessary
  // to handle replacements that add new words.

  // Drop some words depending on the rank. Top rank should
  // never drop words, bottom rank should drop most words.
  // Also drop too long words to avoid using gnomish to
  // sign everything undistorted.

  asWorded = explode (sTextLowercase, " ");

  asWordedTemporary = ({ });
  for (iIndex = 0 ; iIndex < sizeof (asWorded) ; iIndex ++)
  {
    sWord = asWorded [iIndex];
    if ((strlen (sWord) < M_SUSPECT_WORD_LENGTH +
                          random (M_INVALID_WORD_LENGTH -
                                  M_SUSPECT_WORD_LENGTH)) &&
        (random (100) < iRank))
    {
        asWordedTemporary += ({ sWord });
    }
  }

  asWorded = asWordedTemporary;

  // Now just capitalize everything and return the result.

  asWorded = dg_capitalize_array (asWorded - ({ "" }));

  return (implode (asWorded, " "));
}

//-------------------------------------------------------------------

int m_action_sign (string sArgs)
{
  object oActor = this_player ();
  object oListener;
  object *aoListeners;
  string sTextActor;
  string sTextListener;
  int    iRankActor;
  int    iRankListener;
  int    iListener;

  notify_fail ("What do you wish to say by signing ?\n");

  if (!strlen (sArgs)) return (FALSE);

  // The first distortion is done when signing, the second is
  // done when observing. Makes it tough to get something
  // across, but hey, that is life ...

  iRankActor = m_get_normalized_rank (oActor);
  sTextActor = m_signing_distort (sArgs, iRankActor);

  if (strlen (sTextActor))
  {
    write ("You twitch your fingers in a message: " + sTextActor + ".\n");

    aoListeners = FILTER_CAN_SEE (FILTER_LIVE (all_inventory (environment (oActor)) - ({ oActor })), oActor);

    for (iListener = 0 ; iListener < sizeof (aoListeners) ; iListener ++)
    {
      oListener = aoListeners [iListener];

      if (CAN_SEE_IN_ROOM (oListener))
      {
        if (m_is_monk (oListener))
        {
          iRankListener = m_get_normalized_rank (oListener);
          sTextListener = m_signing_distort (sTextActor, iRankListener);
          if (strlen (sTextListener))
          {
            oListener->catch_tell (XCTNAME (oListener, oActor) + " twitches " +
                                   XPOS (oActor) + " fingers in " +
                                   "a message: " + sTextListener + ".\n");
          }
          else
          {
            oListener->catch_tell (XCTNAME (oListener, oActor) + " twitches " +
                                   XPOS (oActor) + " fingers in " +
                                   "a message. You are unable to get the " +
                                   "meaning though.\n");
          }
        }
        else
        {
          oListener->catch_tell (XCTNAME (oListener, oActor) + " twitches " +
                                 XPOS (oActor) + " fingers.\n");
        }
      }
    }
  }
  else
  {
    write ("You attempt to sign a message but fail to get the proper meaning across.\n");
    allbb (" twitches " + XPOS (oActor) + " fingers almost imperceptibly.");
  }

  return (TRUE);
}


int m_action_signal (string sArgs)
{
  object oActor = this_player ();
  object oRoom = environment (oActor);
  mixed  *axListeners;
  object oListener;
  string sText;
  string sTextActor;
  string sTextListener;
  int    iBlind;
  int    iRankActor;
  int    iRankListener;

  notify_fail ("To whom and what do you wish to tell by signing ?\n");

  if (!strlen (sArgs)) return (FALSE);
  if (!parse_command (sArgs, oRoom, "%l %s", axListeners, sText)) return (FALSE);

  if (axListeners [0] < 0)
  {
    // The player used specification such as "first", we
    // need to find which item this really is, but we
    // do not need to care about heaps as livings
    // really do not heap ... :-)

    if (-(axListeners [0]) >= sizeof (axListeners)) return (FALSE);
    oListener = axListeners [-(axListeners [0])];
  }
  else if (axListeners [0] == 0)
  {
    // The player used specification such as "all" ...

    if (sizeof (axListeners) != 2) return (FALSE);
    oListener = axListeners [1];
  }
  else
  {
    // The player used specification such as "one" ...

    if (axListeners [0] != 1) return (FALSE);
    oListener = axListeners [1];
  }

  if (!oListener) return (FALSE);
  if (!strlen (sText)) return (FALSE);
  if (!CAN_SEE (oActor, oListener)) return (FALSE);

  // The first distortion is done when signing, the second is
  // done when observing. Makes it tough to get something
  // across, but hey, that is life ...

  iRankActor = m_get_normalized_rank (oActor);
  sTextActor = m_signing_distort (sText, iRankActor);

  if (strlen (sTextActor))
  {
    int iBlind = !CAN_SEE_IN_ROOM (oListener);

    if (iBlind)
    {
      write ("You extend your hand towards " + XTNAME (oActor, oListener) + " and " +
             "touching " + XPOS (oListener) + " shoulder, twitch your " +
             "fingers in a message: " + sTextActor + ".\n");
      all2actbb (" extends " + QPOS (oActor) + " hand towards",
                 ({ oListener }),
                 " and touching " + XPOS (oListener) + " shoulder, twitches " +
                 XPOS (oActor) + " fingers.");
    }
    else
    {
      write ("You turn towards " + XTNAME (oActor, oListener) + " and twitch your " +
                       "fingers in a message: " + sTextActor + ".\n");
      all2actbb (" turns towards",
                 ({ oListener }),
                 " and twitches " + XPOS (oActor) + " fingers.");
    }

    if (m_is_monk (oListener))
    {
      iRankListener = m_get_normalized_rank (oListener);
      sTextListener = m_signing_distort (sTextActor, iRankListener);

      if (strlen (sTextListener))
      {
        if (iBlind) oListener->catch_tell ("You feel fingers touch your shoulder and twitch " +
                                           "in a message: " + sTextListener + ".\n");
               else oListener->catch_tell (XCTNAME (oListener, oActor) + " turns towards you " +
                                           "and twitches " + XPOS (oActor) + " " +
                                           "fingers in a message: " + sTextListener + ".\n");
      }
      else
      {
        if (iBlind) oListener->catch_tell ("You feel fingers touch your shoulder and twitch " +
                                           "in a message. You are unable to get the meaning " +
                                           "though.\n");
               else oListener->catch_tell (XCTNAME (oListener, oActor) + " turns towards you " +
                                           "and twitches " + XPOS (oActor) + " " +
                                           "fingers in a message. You are unable to get " +
                                           "the meaning though.\n");
      }
    }
    else
    {
      if (iBlind) oListener->catch_tell ("You feel fingers touch your shoulder and twitch.\n");
             else oListener->catch_tell (XCTNAME (oListener, oActor) + " turns towards you " +
                                         "and twitches " + XPOS (oActor) + " fingers.\n");
    }
  }
  else
  {
    write ("You attempt to sign a message but fail to get the proper meaning across.\n");
    allbb (" twitches " + XPOS (oActor) + " fingers almost imperceptibly.");
  }

  return (TRUE);
}

//-------------------------------------------------------------------

