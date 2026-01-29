/* For a complete documentation on the delivery offices, please read
 * /d/Krynn/open/EXPORT/delivery_offices
 *
 *
 * This is identification object for the delivery offices
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

/* Changes: 	
   Kazz  May 11, 1995:     'outpost manager office'
*/


mixed *
query_domain_delivery_offices()
{
    return ({ ({"the outpost manager's office in Avenir",0,0,0}),
          });
}
