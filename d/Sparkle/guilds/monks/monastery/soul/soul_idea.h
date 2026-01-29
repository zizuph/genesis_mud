/*******************************************************************\
| SOUL_IDEA.H                                                       |
\*******************************************************************/

/*
 * 07/06/03 Arandir     Using logging for reports to facilitate log rotation
 * 03/07/08 Arandir     Rewrote to support the bug, idea, typo commands
 * 02/05/03 Arandir	Ported to new area without rewrite
 * ??/??/?? Cirion	Created
 *
 */

// This file is included rather than inherited
// because LPC cannot handle diamond inheritance

//-------------------------------------------------------------------

void m_report_bug (string sText)
{
  object oWho = this_player ();

  if (strlen (sText))
  {
    s_log (M_LOG_BUG, capitalize (dg_get_name (oWho)) + " has reported a bug.\n" + sText, oWho);
    write ("Thank you for reporting the bug.\n");
  }
  else write ("Aborted.\n");
}


void m_report_idea (string sText)
{
  object oWho = this_player ();

  if (strlen (sText))
  {
    s_log (M_LOG_IDEA, capitalize (dg_get_name (oWho)) + " has reported an idea.\n" + sText, oWho);
    write ("Thank you for reporting the idea.\n");
  }
  else write ("Aborted.\n");
}


void m_report_typo (string sText)
{
  object oWho = this_player ();

  if (strlen (sText))
  {
    s_log (M_LOG_TYPO, capitalize (dg_get_name (oWho)) + " has reported a typo.\n" + sText, oWho);
    write ("Thank you for reporting the typo.\n");
  }
  else write ("Aborted.\n");
}

//-------------------------------------------------------------------

int m_action_bug (string sArgs)
{
  object oEditor;

  if (strlen (sArgs))
  {
    m_report_bug (sArgs);
  }
  else
  {
    DG_FIXUID;
    oEditor = clone_object (EDITOR_OBJECT);
    oEditor->edit (m_report_bug);
  }

  return (TRUE);
}


int m_action_idea (string sArgs)
{
  object oEditor;

  if (strlen (sArgs))
  {
    m_report_idea (sArgs);
  }
  else
  {
    DG_FIXUID;
    oEditor = clone_object (EDITOR_OBJECT);
    oEditor->edit (m_report_idea);
  }

  return (TRUE);
}


int m_action_typo (string sArgs)
{
  object oEditor;

  if (strlen (sArgs))
  {
    m_report_typo (sArgs);
  }
  else
  {
    DG_FIXUID;
    oEditor = clone_object (EDITOR_OBJECT);
    oEditor->edit (m_report_typo);
  }

  return (TRUE);
}

//-------------------------------------------------------------------

