#pragma save_binary

/* /d/Genesis/delivery/example_delivery.c
 * 
 * For a complete documentation on the delivery offices, please read
 * /d/Genesis/delivery/delivery_offices.doc
 *
 * Created by Aridor 05/95
 * Last modified by Aridor 06/07/95
 *
 * This is the identification object for the delivery offices.
 * Each domain that has delivery offices must have a similar
 * file in /d/<domain>/open/delivery.c
 *
 *
 * Syntax:
 * The function query_domain_delivery_offices() returns an array of arrays
 * of individual offices. Each office-array contains four values which
 * are explained below:
 * -Name of the office           a string to uniquely identify this office
 * -giveout/recieve identifier   a number: 0 send and receive packets,
 *                                         1 send only,
 *                                         2 receive only.
 * -offices to send to           0 or an array of office names, this option
 *                                         should rarely be used!
 * -offices not to send to       0 or an array of office names, use this
 *                                         option if two offices are located
 *                                         fairly close to each other.
 * 
 */

mixed *
query_domain_delivery_offices()
{
    return 
      ({ ({ "the Shop in Solace", /* The first office is the shop in Solace */
	      0,                  /* this place sends and receives packets */
	      0,                  /* no limits on where to send packets except */
	      ({ "the Personnel Office in the palace in Palanthas" }) }),
	                          /* never send packets to Palanthas. */
	   
	   ({ "Newports",         /* The second office is in Newports */
		1,                /* only send out packets from here */
		({ "the Shop in Solace",
		     "the Personnel Office in the palace in Palanthas"}),
		                  /* only send packets to Solace and Palanthas
				     from this office in Newports */
		0 }),             /* not needed since the limit is already in
				     the line above. */
	   
	   ({ "the Personnel Office in the palace in Palanthas", /* Palanthas */
		2,                /* only receive packets here, don't send */
		0,                /* not needed, we're not sending */
		0, })             /* not needed, we're not sending */
     });
}