/*


Filename: /d/Shire/bree/rooms/town/stable/obj/horse_bells.c
          /d/Shire/bree/rooms/town/stable/steed includes this file.

Purpose:  Allows the steed to wear bells that jingle when it walks.

Coded by: Palmer

Date:     December 6, 2002


 */
#pragma strict_types
#include <const.h>
#include <composite.h>
#include <macros.h>
#define TP this_player()
#define TO this_object()
int do_fasten(string arg);
string additional_longdescr();
int do_unfasten(string arg);


object bells;


/*
 * Function:    :  do_fasten
 * Description  :  parses the command to fasten the bells
 *       to  the steed's ankles, also performs the move.
 * Arguments    :  "<bells> on <steed>"
 * Returns      :  true if the fasten command succeeded.
 */
int
do_fasten(string arg)
{

  object steed;
  string junk;

  notify_fail("That steed is already werring bells!\n");

  if (present("bells"))
    return 0;

  notify_fail("Fasten what?\n");

  if (!arg)
    return 0;

  if (!present("bells",TP))
    return 0;

  parse_command(arg, environment(TP), "[the] 'bells' 'on' [the] %o", steed);
  parse_command(arg, all_inventory(TP), "[the] %o %s", bells, junk);

  if (!present(bells,TP))
    {
      bells=0;
      return 0;
    }

  if (!steed)
    {
      bells=0;
      return 0;
    }


  if (steed != TO)
      {
      bells=0;
      return 0;
    }

  if (bells->move(steed))
    {
      write ("The bells seem to be too heavy for the "+
      "steed to carry.\n");
      bells=0;
      return 1;
    }

  write ("You fasten the "+bells->short()+" to the "+
         "steed's ankles.\n");

  say (QCTNAME(TP)+" fastens the "+bells->short()+ " to the "+
        "steed's ankles.\n");

  steed->has_bells();

  return 1;
}


/*
 * Function:     additional_longdesc
 * Description:  if this_object (the horse) has bells, show it
 */

string
additional_longdescr()
{
  if (!present("bells"))
    {
      return "";
    }
      return capitalize(TO->query_pronoun())+" has bells fastened to "+
             TO->query_possessive()+" ankles.\n";
}


/*
 * Function     :  do_unfasten
 * Description  :  parses and performs a command to unfasten the ankles
 *                 from the steed and return it to the player.
 * Arguments    : "<bells> from <steed>"
 * Returns      : true if the unfasten succeeded
 */
int
do_unfasten(string arg)
{

  object steed;
  string target;

  if (!present("bells"))
    return 0;

  notify_fail("Unfasten what on what?\n");
  if (!arg)
    return 0;

  parse_command(arg, environment(TP), "[the] %s 'on' %o",target , steed);

  if (!steed)
    return 0;

  if (steed != TO)
    return 0;

  if (!bells)
    return 0;

  if (bells->move(TP))
    {
      write ("You unfasten the straps of the "+bells->short()+
             " and they drop jingiling to the ground.\n");

      say (QCTNAME(TP)+" unties the straps of the horse" +
           "'s "+bells->short()+", and they fall jingling to" +
           "the ground.\n");

      bells->move(environment(TO));
      steed->has_no_bells();
      bells=0;

      return 1;
    }
  else
    {

      write ("You unfasten the "+bells->short()+" from the " +
             "steed's ankles.\n");

      say (QCTNAME(TP)+" removes the "+bells->short()+ " from the ankles " +
           "of the steed.\n");
      steed->has_no_bells();
      bells=0;

  return 1;
    }
}


