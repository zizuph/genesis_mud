/* This is identification object for the delivery offices
 * Each domain that has delivery offices must have a similar
 * file in /d/<domain>/open/delivery.c
 */

mixed *
query_domain_delivery_offices()
{
    return ({   ({  "the Prancing Pony in Bree", 0, 0, 
                ({  "The Stonebows Inn of the Shire",
                    "Police Headquarters of Frogmorton",
                    "Pipe and Fork Inn of Michel Delving",}), }),

                ({  "Police Headquarters of Frogmorton", 0, 0, 
                ({  "The Stonebows Inn of the Shire",
                    "the Prancing Pony in Bree",
                    "Pipe and Fork Inn of Michel Delving",}), }),
            
                ({  "The Stonebows Inn of the Shire", 2, // receive only
                    0,
                ({  "the Prancing Pony in Bree",
                    "Police Headquarters of Frogmorton",
                    "Pipe and Fork Inn of Michel Delving",}), }),

                ({  "Pipe and Fork Inn of Michel Delving", 0, 0, 
                ({  "The Stonebows Inn of the Shire",
                    "the Prancing Pony in Bree",
                    "Police Headquarters of Frogmorton",}), }),

	  });
}
