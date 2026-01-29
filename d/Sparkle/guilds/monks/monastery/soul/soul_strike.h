/*******************************************************************\
| SOUL_STRIKE.H                                                     |
\*******************************************************************/

/*
 * 03/07/04 Arandir     Polished up and bugfixed
 * 02/05/03 Arandir	Ported to new area without rewrite
 * ??/??/?? Cirion	Created
 *
 */

// This file is included rather than inherited
// because LPC cannot handle diamond inheritance

//-------------------------------------------------------------------

int m_action_strike (string sArgs)
{
  object oWho = this_player ();
  object oRoom = environment (oWho);
  mixed  *axWhom;
  object oWhom;
  string sWhere;
  string *asHitlocs;

  notify_fail ("Whom and where wouldst thou strike ?\n");

  if (strlen (sArgs))
  {
    if (parse_command (sArgs, oRoom, "%l [on] %s", axWhom, sWhere))
    {
      if (axWhom [0] < 0)
      {
        // The player used specification such as "first", we
        // need to find which item this really is, but we
        // do not need to care about heaps as livings
        // really do not heap ... :-)

        if (-(axWhom [0]) >= sizeof (axWhom)) return (FALSE);
        oWhom = axWhom [-(axWhom [0])];
      }
      else if (axWhom [0] == 0)
      {
        // The player used specification such as "all" ...

        if (sizeof (axWhom) != 2) return (FALSE);
        oWhom = axWhom [1];
      }
      else
      {
        // The player used specification such as "one" ...

        if (axWhom [0] != 1) return (FALSE);
        oWhom = axWhom [1];
      }
    }
    else
    {
      parse_command (sArgs, oRoom, "[on] %s", sWhere);
      oWhom = oWho->query_attack ();
    }
  }
  else
  {
    oWhom = oWho->query_attack ();
    sWhere = "";
  }

  if (!oWhom) return (FALSE);

  // Check whether the hitlocation exists on the target ...

  asHitlocs = dg_get_hitlocs (oWhom);

  if (strlen (sWhere))
  {
    if (member_array (sWhere, asHitlocs) < 0)
    {
      notify_fail (QCTNAME (oWhom) + " does not seem to have " +
                   LANG_ADDART (sWhere) + ". Possible areas you " +
                   "can strike on " + QTNAME (oWhom) + " are " +
                   COMPOSITE_WORDS (asHitlocs) + ".\n");
      return (FALSE);
    }
  }

  // The shadow takes care of the rest ...

  oWho->m_start_strike (oWhom, sWhere);

  return (TRUE);
}

//-------------------------------------------------------------------

