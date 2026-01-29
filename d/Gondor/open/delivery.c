/*
 *  This is identification object for the delivery offices
 *
 *  Each domain that has delivery offices must have a similar
 *  file in /d/<domain>/open/delivery.c
 *
 *  This file for the domain Gondor.
 *
 *  Olorin, 11-may-1995
 */

mixed *
query_domain_delivery_offices()
{
    return ({ ({"Bendar's General Store in Edoras", 
        0, 
        0, 
        ({"Delivery Office of Thornlin", }), }),
	    
        ({"Delivery Office of Thornlin", 
        0, 
        0, 
        ({"Bendar's General Store in Edoras", }), }),
	  });
}
