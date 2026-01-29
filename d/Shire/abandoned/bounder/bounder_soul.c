/*   This file is /d/Shire/bounders/soul/bounder_soul.c
 *
 *   Intended for use by the Bounders of the Shire in the
 *   Shire domain in Genesis.
 *   Stolen from the Adventuresome Hobbits stolen from
 *   the Ranger soul :)
 *
 */

#pragma save_binary

inherit "/cmd/std/command_driver";
#include <macros.h>
#include <formulas.h>
#include "/d/Shire/bounders/guild.h"
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

/*************************************************************
 *** Guild Specials called by the shadow now...

#ifndef NO_DECK
#include "deck.c"
#endif

#ifndef NO_NAIL
#include "nail.c"
#endif

 ***/

int alarm_id;

string
get_soul_id()
{
    return "Bounders of the Shire";
}

int
query_cmd_soul()
{
    return 1;
}

mapping
query_cmdlist()
{

    setuid();
    seteuid(getuid());

    return ([
      "bbow"       :   "bbow",
      "bstance"    :   "bstance"
    ]);

    /* The above are in the form: command : function */

}

int
bbow(string str)
{
    object *oblist;
    if(!strlen(str)) /* no string supplied */
    {
	write("You get down on one knee and bow, awkwardly.\n");
	all(" bows awkwardly from one knee.");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Bow to whom?\n");
	return 1;
    }

    actor("You bow, presenting yourself to the service of",oblist,".");
    target(" bows to you, at your service.",oblist);
    all2act(" bows to",oblist,", at their service.");
    return 1;

}

int bstance(string str)
{
    object *oblist;
    string how;
    if(!strlen(str)) /* no string supplied */
    {
	write("You pull up your belt and plant your feet wide in "+
	  "preparation for some rough stuff.\n");
	all(" pulls up "+HIS_HER(TP)+" belt, setting "+HIS_HER(TP)+" feet "+
	  "apart in preparation for the worst.");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if(!sizeof(oblist))
    {
	write("Stare down whom?\n");
	return 1;
    }

    switch(how->query_stat(SS_LAYMAN))
    {
    case 0..25:
	how = "some";
	break;
    case 26..50:
	how = "measureable";
	break;
    case 51..75:
	how = "considerable";
	break;
    case 76..100:
	how = "surprising";
	break;
    case 101..200:
	how = "legendary";
        break;
    default:
	how = "considerable";
	break;
    }

    actor("You pull up your belt and plant your feet wide, locking "+
      "your gaze onto", oblist,".");
    target(" pulls up "+HIS_HER(TP)+" belt, settles into a fighting stance, "+
      "and stares you right in the eyes.\nApparently you are messing with a "+
      "hobbit of "+ how +" toughness.", oblist);
    all2act(" pulls up his belt and settles into a wide fighting stance, "+
      "staring down", oblist," with a look of total defiance.\n"+
      "Apparently "+ QCTNAME(TP) +" is a hobbit of "+ how +" toughness.");
    return 1;

}
