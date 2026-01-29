/*******************************************************************\
| ROOM_ITEM.H                                                       |
+-------------------------------------------------------------------+
| Room fragment responsible for item functions.                     |
\*******************************************************************/

/*
 * 08/02/03 Arandir     Fixed matching of items
 * 08/02/02 Arandir     Created
 * 10/07/24 Lavellan    Excludes "me", which was spamming the log
 * 10/09/26 Lavellan    Excludes add_items "early", fixes monk room problem.
 *
 */

// This file is included rather than inherited
// because LPC cannot handle diamond inheritance

//-------------------------------------------------------------------

// mItemsMissing : Keeps track of unsuccessfully examined items.
//   key            : Item name
//   data           : Array of players who have examined the item

private mapping mItemsMissing = ([ ]);

// S_ITEMS_REPORT_MISSING : Minimum number of players that has to
//                          examine an item for it to be reported.

#define S_ITEMS_REPORT_MISSING          3

//-------------------------------------------------------------------

/*
 * Function name : s_action_examine
 * Description   : Executed when somebody issues the examine action.
 *                 Keeps track of items examined unsuccessfully and
 *                 reports them so that items players expect can be
 *                 added.
 *
 */

int s_action_examine (string sArgs)
{
  object *aoItems;
  string sWho;

  // Do some normalization on the item first.

  sArgs = lower_case (sArgs);
  sArgs = s_remove_whitespace (sArgs);
  sArgs = s_remove_doublespace (sArgs);

  // Check if arg is an add_item, and return if so.
  // This is to prevent the text of the add_item being evaluated
  // (along with any VBFC there).
  if (item_id(sArgs))
    return (FALSE);

  // The code here resembles that of the examine command,
  // except for checking the items inside deep inventories.
  // There seems to be no easy way of learning about the
  // failure of the examine command itself ...

  if (!stringp (TO->long (sArgs)) && !parse_command (sArgs, TO, "%i", aoItems))
  {
    sWho = s_get_name (TP);
    
    // Players often examine "me", and no room should interfere
    // with that, so we can ignore that.
    
    if (sArgs == "me")
        return (FALSE);

    // We could just merge the player into the array here,
    // but we need to know if the number of players in
    // the array has increased over the limit.

    if (member_array (sArgs, m_indices (mItemsMissing)) < 0)
    {
      mItemsMissing [sArgs] = ({ sWho });
    }

    if (member_array (sWho, mItemsMissing [sArgs]) < 0)
    {
      mItemsMissing [sArgs] += ({ sWho });

      if (sizeof (mItemsMissing [sArgs]) == S_ITEMS_REPORT_MISSING)
      {
        s_log (S_LOG_DEBUG_FILE, "Often missing item is " + sArgs + ".", TO);
      }
    }
  }

  // We always return false since this is not a real command.

  return (FALSE);
}

//-------------------------------------------------------------------

