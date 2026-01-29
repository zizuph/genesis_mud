/*******************************************************************\
| BASE_OBJ_CLOTHES.H                                                |
\*******************************************************************/

/*
 * 00/06/19 Cirion      Created
 * 03/04/04 Arandir	Ported to new area and bugfixed
 * 03/05/10 Arandir     Split into armour and wearable classes
 * 03/11/13 Arandir     Changed the decay to work even when
 *                      somebody who is not a monk holds the
 *                      object. This takes care of objects that
 *                      stay after their owner has left the guild.
 *
 */

inherit M_PLAYER_LIBS;

//-------------------------------------------------------------------

// Time after which the clothes will decay when dropped

#define M_CLOTHES_DECAY         300.0

//-------------------------------------------------------------------

private int iDecayLastAlarm = ALARM_NONE;

//-------------------------------------------------------------------

/*
 * Function name : create_armour
 * Function name : create_object
 * Description   : Constructor depends on the type of
 *                 the clothes object that we create.
 *
 */

#ifdef M_CLOTHES_ARMOUR
void create_armour ()
{
  ::create_armour ();
#endif
#ifdef M_CLOTHES_WEARABLE
void create_object ()
{
  ::create_object ();
#endif

  // All monk clothes have a hidden name equal to the master
  // object to make it easy to identify them in an inventory.

  add_name (MASTER, TRUE);
}

//-------------------------------------------------------------------

/*
 * Function name : m_clothes_decay
 * Description   : An alarm that makes sure clothes decay
 *
 */

void m_clothes_decay ()
{
  object oThis = this_object ();
  object oHolder = environment (oThis);

  // Remember that the alarm already expired.

  iDecayLastAlarm = ALARM_NONE;

  // The clothes decay if they are not in an inventory
  // of a living monk or an NPC for the set decay time.

  if (living (oHolder))
  {
    if (query_interactive (oHolder) && !m_is_monk (oHolder))
    {
      oThis->remove_me ();
      tell_object (oHolder, "Your " + LANG_SHORT (oThis) + " rapidly decays and falls apart.\n");
      oThis->remove_object ();
    }
  }
  else
  {
    tell_room (oHolder, capitalize (LANG_THESHORT (oThis)) + " rapidly decays and falls apart.\n");
    oThis->remove_object ();
  }
}

//-------------------------------------------------------------------

/*
 * Function name : enter_env
 *
 */

void enter_env (object oTo, object oFrom)
{
  if (iDecayLastAlarm != ALARM_NONE) remove_alarm (iDecayLastAlarm);
  iDecayLastAlarm = set_alarm (M_CLOTHES_DECAY, 0.0, &m_clothes_decay ());
}


/*
 * Function name : leave_env
 *
 */

void leave_env (object oFrom, object oTo)
{
#ifdef M_CLOTHES_WEARABLE
  wearable_item_leave_env (oFrom, oTo);
#endif

  ::leave_env (oFrom, oTo);
}

//-------------------------------------------------------------------

/*
 * Function name : appraise_object
 *
 */

#ifdef M_CLOTHES_WEARABLE
void appraise_object (int iNumber)
{
  ::appraise_object (iNumber);
  appraise_wearable_item ();
}
#endif

//-------------------------------------------------------------------

