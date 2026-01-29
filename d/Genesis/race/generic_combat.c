/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */

/*
   race/generic_combat.c

   This is the Genesis specific combat routines.
*/
inherit "/std/combat/chumlock";

/*
%Intox p}verka fulhetsgrad / sk|nhetsgrad
Fulhetsgrad > 90 inneb{r (100-%intox)*10 % / 30+DIS/10 hb att attackera 
 			                   / 10+DIS/10 hb att provocera

Sk|nhetsgrad > 90 inneb{r (100-%intox)*10 % / 30 + DIS/10 hb att ge bort pengar
					    / 10 + DIS/10 hb att antasta
*/

/*
 * Function name: cb_adjust_combat_on_intox
 * Description:   Called to let intoxication affect combat. This
 *                is used to do nasty drunk type things *laugh*
 * Arguments:     pintox: %intoxicated      
 */
public void
cb_adjust_combat_on_intox(int pintox)
{
    object *p;

    if (pintox < 90)
	return;

    p = all_inventory(environment(qme()));

    if (!sizeof(p))
    {
	
    }
}
