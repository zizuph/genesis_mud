/* This file is intended to have some nice combat help functions. */

/*
 * Function:    c_can_attack
 * Arguments:   ob: The object this_player() wants to attack.
 *              verb: The verb used to attack.
 * Description: Find out whether this_player() is able to attack ob.
 *              Checks are made for NO_ATTACK properties, also, introduced
 *              victims must be attacked twice. Check if this_player() has
 *              enough discipline to attack ob.
 * Returns:     Failure string if cannot attack.
 *              Typical usage: str = c_can_attack(a,b);
 *                             if (stringp(str))
 *                               {
 *                                    NF(str);
 *                                    return 0;
 *                               }
 */
string
c_can_attack(object ob, string verb)
{
    mixed mess;

    if (!ob || !living(ob) || (ob == TP) || ob->query_ghost())
        return C(verb) + " who?\n";

    if (mess = ob->query_prop(OBJ_M_NO_ATTACK))
        return (stringp(mess) ? mess :
	    "You sense a devine presence protecting the intended victim.\n");

    if (E(ob) && (mess = E(ob)->query_prop(ROOM_M_NO_ATTACK)))
        return (stringp(mess) ? mess :
	    "You sense that someone has laid a peace spell over this room.\n");

    if (TP->query_met(ob) && TP->query_enemy(0) != ob)/* && !TP->query_npc() */
      {
          if (TP->query_prop(LIVE_O_LAST_KILL) != ob)
            {	
                TP->catch_msg("Attack " + QTNAME(ob) +
                      "?!? Please confirm by trying again.\n");
                TP->add_prop(LIVE_O_LAST_KILL, ob);
	        return "";
            }
/*          else
 *           TP->remove_prop(LIVE_O_LAST_KILL);
 */
      }
    if (!F_DARE_ATTACK(TP, ob))
        return "Umm... no, You do not have enough self-discipline to dare!\n";
    
}

