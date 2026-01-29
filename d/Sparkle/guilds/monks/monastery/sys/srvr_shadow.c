/*******************************************************************\
| SRVR_SHADOW.C                                                     |
+-------------------------------------------------------------------+
| Stub to forward calls to monk shadow. This gets rid of what is    |
| rather unpredictable behavior of calls to monk shadow when the    |
| caller can be the shadowed object.                                |
\*******************************************************************/

/*
 * 05/05/10 Arandir     Added stub for m_get_kins
 * 05/04/24 Arandir     Created
 *
 */

//-------------------------------------------------------------------

mixed *m_get_character (object oWho)
{
  return (oWho->m_get_character ());
}


string *m_get_kins (object oWho)
{
  return (oWho->m_get_kins ());
}

//-------------------------------------------------------------------

