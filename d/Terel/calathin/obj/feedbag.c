inherit "/std/container.c";

#include "/d/Terel/include/Terel.h"
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>   

create_container()
{
     add_prop(CONT_I_WEIGHT,3000);
     add_prop(CONT_I_MAX_WEIGHT,20000);
     add_prop(CONT_I_VOLUME,3000);
     add_prop(CONT_I_MAX_VOLUME,30000);

     set_name(({"feedbag"}));
     set_short("feedbag");
     set_long("A large leather feedbag.  Fill it with oats "+
	      "and strap it on to your steed. ");


}


/*
 * Function:    :  do_strap
 * Description  :  parses the command to drape the saddlebag over
 *                 the steed's back, also performs the move.
 * Arguments    :  "<saddlebag> on <steed>"
 * Returns      :  true if the drape command succeeded.
 */
int
do_strap(string arg)
{

  object steed;
  object(feedbag);
  
  notify_fail("Strap what?\n");

  if (!arg)
    return 0;

  if (!present("feedbag",TP))
    return 0;

  parse_command(arg, ENV(TP), "[the] %o 'on' %o",feedbag , steed);

  if (!steed)
    return 0;

  if (steed != TO)
    return 0;

  if (feedbag->move(steed))
    {
      write ("The feedbag seems to be too heavy for the "+
	    steed->short()+" to carry.\n");
      return 1;
    }

  write ("You strap the "+feedbag->short()+" on the "+
	 steed->short()+"'s muzzle.\n");

  say (QCTNAME(TP)+" straps a "+feedbag->short()+ " onto the muzzle of the "+
        steed->short()+".\n");

  return 1;
}


/*
 * Function     :  do_remove
 * Description  :  parses and performs a command to remove the saddlebag
 *                 from the steed and return it to the player.
 * Arguments    : "<saddlebag> from <steed>"
 * Returns      : true if the remove succeeded
 */
int
do_remove(string arg)
{

  object steed;
  string target;

  notify_fail("Remove what from what?\n");
  if (!arg)
    return 0;

  parse_command(arg, ENV(TP), "[the] %s 'from' %o",target , steed);

  if (!steed)
    return 0;

  if (steed != TO)
    return 0;

  if (!saddlebag) 
    return 0;

  if (saddlebag->move(TP))
    {
      write ("You untie the straps of the "+saddlebag->short()+
	     " and it drops heavily to the ground.\n");

      say (QCTNAME(TP)+" unties the straps of the " +steed->short()+
	   "'s "+saddlebag->short()+", and it falls heavily to"+
	   "the ground.\n");

      saddlebag->move(ENV(TO));

      saddlebag=0;

      return 1;
    }
  else
    {

      write ("You remove the "+saddlebag->short()+" from the "+
	     steed->short()+"'s back.\n");

      say (QCTNAME(TP)+" removes a "+saddlebag->short()+ " from the back "+
	   "of the "+ steed->short()+".\n");

  saddlebag=0;

  return 1;
    }
}
