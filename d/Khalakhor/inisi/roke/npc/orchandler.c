/*
 * orchandler.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* orchandler - control the number of orcs running around in the
   forest
   Gresolle - 1992
*/

#pragma save_binary
#pragma strict_types

int nroforcs = 0;

/* Function:     request_orc
   Returns:      1 - ok, 0 - no more orcs allowed
*/
int
query_orc()
{
    return nroforcs;
}

int
request_orc()
{
    if (nroforcs >= 30)
        return 0;

    nroforcs++;

    return 1;
}
/* Function:    orc_died
 */
void
orc_died()
{
    nroforcs--;
}
