/*
   prestige.c
   
   Module for knight's prestige, code taken from
   /d/Krynn/open/monster/monster.c
   
   Fysix@Genesis, Oct 1997
 */
#pragma strict_types
#pragma save_binary

static int  Prestige;

/* Function name: set_knight_prestige
 * Description:   Set the prestige changing value in the mobile
 * Arguments:     pres - the prestige, if > 0 it will add to the acc, if < 0
 *                it will add to the stat.
 */
public void
set_knight_prestige(int pres)
{
   Prestige = pres;
}

/* Function name: query_knight_prestige
 * Description:   Return the prestige this monster will affect a knight.
 * Returns:       The prestige.
 */
public int
query_knight_prestige()
{
   return Prestige;
}
