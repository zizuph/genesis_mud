/*******************************************************************\
| SOUL_PLEXUS.H                                                     |
\*******************************************************************/

/*
 * 06/09/02 Arandir     Non player characters can now plexus
 * 04/05/11 Arandir     Missing check for guild branch added
 * 03/07/07 Arandir     Polished up and bugfixed
 * 02/05/03 Arandir	Ported to new area without rewrite
 * ??/??/?? Cirion	Created
 *
 */

// This file is included rather than inherited
// because LPC cannot handle diamond inheritance

//-------------------------------------------------------------------

int m_action_plexus (string sArgs)
{
  object oWho = this_player ();
  object *aoWhom;
  object oWhom;

  if (query_interactive (oWho) && !m_is_monk (oWho, SS_OCCUP)) return (FALSE);

  notify_fail ("Whom wouldst thou stun ?\n");

  if (strlen (sArgs))
  {
    aoWhom = parse_this (sArgs, "%l");
    if (sizeof (aoWhom) != 1) return (FALSE);
    oWhom = aoWhom [0];
  }
  else
  {
    oWhom = oWho->query_attack ();
  }

  if (!oWhom) return (FALSE);

  // The shadow takes care of the rest ...

  oWho->m_start_plexus (oWhom);

  return (TRUE);
}

//-------------------------------------------------------------------

