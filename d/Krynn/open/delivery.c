/* For a complete documentation on the delivery offices, please read
 * /d/Genesis/delivery/delivery_offices.doc
 *
 *
 * This is the identification object for the delivery offices
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
    return ({({"the Shop in Solace",0,0,0}),
	       ({"Newports",0,
		   ({"the Prancing Pony in Bree",
		     "the Shop in Solace",
		     "the Personnel Office in the palace in Palanthas",}),0}),
		/* restrict offices for Newports so the first time
		 * deliverers don't get frustrated cause they can't find the
		 * office. Newports is where most come first as it's a tour
		 * from the Questmaster to find the place.
		 */
		({"the Personnel Office in the palace in Palanthas",0,0,0})
	  });
}
