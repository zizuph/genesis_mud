/* 	this is a box in Gelan for puttings maps in

    coder(s):   Merlin

    history:
		21.09.94	created				Merlin

    purpose:    contract for the healing/curing/operations in gelan 
                hospital

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


inherit "/std/object";
#include "object.h"
#include <stdproperties.h>

int heal;
string playerName;
int signed;
int cost;

create_object()
{
    /* init the variables */

    heal = 0;
    playerName = "";
    signed = 0;
    cost = 0;

    /* descriptions */

    set_name("contract");
    set_short("hospital contract");
    set_long("\n\n                Gelan Hospital\n\n" +
             "bla bla bla bla bla\n\n\n" +
             "The cost for the treatment is " + cost + " coppers.\n" +
             "This contract is for " + "@@get_player@@" + ".\n" +
             "The contract is " + "@@get_signed@@" + ".\n");

} /* create_container */

/*
 * Function name: sign_me
 * Description:   The player signs the contract, now he is ready for healing
 * Arguments:     none
 * Returns:       none
 */

int
sign_me(string arg)
{
  string *argv;
  int i;

  if(!strlen(arg))
  {
    notify_fail("What do you want to sign ?\n");
    return 0;
  }

  argv = explode(arg, " ");

  if(argv[0] != "contract")
  {
    notify_fail("Don't know how to sign " + argv[0] + ".\n");
    return 0;
  }

  /* OK, now the command is correct */

  if(signed)
  {
    write("The contract is already signed by a certain " + playerName + "\n.");
    return 1;
  }

  write("You sign the contract by pressing your thumb against it.\n");

  if(playerName == this_player()->query_name())
    signed = 1;
  else
  {
    write("After signing you realize that the contract was not for you. " +
          "Now the contract is useless.\n");
    signed = -1;
  }

  return 1;
}

/*
 * Function name: tear_me
 * Description:   The player tears the contract in pieces
 * Arguments:     none
 * Returns:       none
 */

int
tear_me(string arg)
{
  string *argv;
  int i;

  if(!strlen(arg))
  {
    notify_fail("What do you want to tear ?\n");
    return 0;
  }

  argv = explode(arg, " ");

  if(argv[0] != "contract")
  {
    notify_fail("Don't know how to tear " + argv[0] + ".\n");
    return 0;
  }

  /* OK, now the command is correct */

  write("You tear the contract into a heap of small pieces.\n" +
        "You quickly free yourself of the heap of useless paper.\n");

  remove_object();

  return 1;
}

/*
 * Function name: init
 * Description:   adds some command(s) to the player
 * Arguments:     none
 * Returns:       none
 */

void
init()
{
  add_action("sign_me", "sign");
  add_action("tear_me", "tear");
}

/*
 * Function name: get_player
 * Description:   returns the name of the player for this contract
 * Arguments:     none
 * Returns:       name of the player as string
 */

string 
get_player()
{
  return playerName;
}

/*
 * Function name: get_signed
 * Description:   returns if contract signed
 * Arguments:     none
 * Returns:       either 'signed' or 'not signed'.
 */

string 
get_signed()
{
  if(signed)
    return "signed";
  else
    return "not signed";
}

/*
 * Function name: fill
 * Description:   fills out the contract (done by doctor)
 * Arguments:     player's name, amount to heal
 * Returns:       none
 */

void
fill(string name, int inHeal, int inCost)
{
  heal = inHeal;
  playerName = name;
  cost = inCost;
}

int
getMaxHeal()
{
  return heal;
}

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */










