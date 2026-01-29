/*
 * seer_search_base.c
 *
 * This object contains the support needed to search for
 * the cloth and dagger required for the Seer and the Lord
 * Quest. It moves them around between a number of 
 * predetermined rooms as the quest resets.
 *
 * Khail - Feb 24/97
 *
 * Modifications:
 *   - Made it so that if the quest items are no longer available on
 *     Eldoral, then you can find it if you haven't already done
 *     so. [Petros, April 2009]
 *         
 */
#pragma strict_types

#include "defs.h"

public string *      dagger_found = ({ });
public string *      cloth_found  = ({ });

/*
 * Function name: reset_quest
 * Description  : Changes the location of the dagger and cloth.
 *                Done by removing the search props from the
 *                current location, and adding them to the new one.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_quest()
{
  /* If this room is the current location for the dagger, */
  /* add the search prop if necessary, otherwise just reset */
  /* the found flags. */
    if (file_name(TO) == SEER_BRAIN->query_location("value"))
    {
        if (TO->query_prop(OBJ_S_SEARCH_FUN) == "uncover_hidden")
        {
            dagger_found = ({ });
            cloth_found = ({ });
        }
        else
        {
            TO->add_prop(OBJ_I_SEARCH_TIME, 5);
            TO->add_prop(OBJ_S_SEARCH_FUN, "uncover_hidden");
            TO->add_prop(ROOM_I_NO_CLEANUP, 1);
        }
    }

  /* Since this object isn't the current location, if */
  /* the search prop exists here, remove it. */
    else
    {
        if (TO->query_prop(OBJ_S_SEARCH_FUN) == "uncover_hidden")
        {
            dagger_found = ({ });
            cloth_found = ({ });
            TO->remove_prop(OBJ_I_SEARCH_TIME);
            TO->remove_prop(OBJ_S_SEARCH_FUN);
            TO->remove_prop(ROOM_I_NO_CLEANUP);
        }
    }
}

/*
 * Function name: uncover_hidden
 * Description  : What to do when the player has searched here.
 * Arguments    : player - Object pointer to the searching player.
 *                str - Argument passed with the 'search' command.
 * Returns      : A string if something found, "" if nothing.
 */
public string
uncover_hidden(object player, string str)
{
    object dagger,
           cloth;
    string what,
           to_find;

  /* Default fail message if no argument specified. */
    if (!str)
        return "";

  /* Fail if player isn't on the seer quest. */
    if (!player->query_prop(LIVE_I_SEER_QUEST))
        return "";

  /* If an array of locations to search has been specified, but */
  /* to player isn't searching one of them, fail. */
    if (TO->query_prop(DAGGER_AS_SEARCH_TARGETS) &&
        member_array(str, TO->query_prop(DAGGER_AS_SEARCH_TARGETS)) < 0)
        return "";

    if (!dagger_found)
    {
        dagger_found = ({ });
    }
    
  /* What to do if the player was searching for the dagger. */
    if (!IN_ARRAY(player->query_real_name(), dagger_found))
    { 
        seteuid(getuid());
        dagger = clone_object(WEP + "dagger");
        dagger->move(TO);
        dagger_found += ({ player->query_real_name() });
      /* Add a flag to the player verifying he found the dagger. */
        player->add_prop(LIVE_I_SEER_QUEST,
            player->query_prop(LIVE_I_SEER_QUEST) | SEQ_FOUND_DAGGER);
        return "Searching carefully, you " +
            "are soon rewarded when an ancient dagger rolls " +
            "onto the ground!\n";
    }

    if (!cloth_found)
    {
        cloth_found = ({ });
    }
        
  /* If the player wasn't looking for the dagger, was he looking */
  /* for the cloth? */
  /* Fail if the cloth has already been found. */
    if (IN_ARRAY(player->query_real_name(), cloth_found))
        return "";

   /* Otherwise, give cloth to this player. */
    else
    {
        seteuid(getuid());
        cloth = clone_object(OBJ + "cloth");
        cloth->move(TO);
        cloth_found += ({ player->query_real_name() });
      /* Mark the player as having found the cloth. */
        player->add_prop(LIVE_I_SEER_QUEST,
            player->query_prop(LIVE_I_SEER_QUEST) | SEQ_FOUND_CLOTH);
        return "Searching carefully, you are surprised to " +
            "find a small piece of cloth!\n";
    }
  /* Fail for any other possibilities. */
    return "";
}
                
