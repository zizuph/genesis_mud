/* Binary bit handler, written by Quetzl    
 * Thanks to Elessar for inspiring this
 * April 1994               
 */

#ifndef BIT_HANDLER
#define BIT_HANDLER 1
#include <macros.h>

public int
query_bin_bits(int group, int left, int right, object who)
{
    int i, tot;
    string domain;
    int size = right - left + 1;
    domain = explode(MASTER, "/")[2];
    for (i=0; i<size; i++)
        tot += ((who->test_bit(domain, group, left+i))<<i);
     return tot;
}

public int
set_bin_bits(int group, int left, int right, object who,
                int dec)
{
    int i, currbit = 1;
    int size = right - left + 1;

    setuid();
    seteuid(getuid());

    if ((currbit<<size) < dec+1)
        return 0;
    for (i = left, currbit = 1; i<=right; i++,
        (currbit = (currbit<<1)))
        (currbit & dec) ? (who->set_bit(group, i)) :
            (who->clear_bit(group, i));
    return 1;
}

public int
increase_bits(int group, int left, int right, object who,
              int negative)
{
    int new = query_bin_bits(group, left, right, who);
    (negative) ? (new--) : (new++);
    return set_bin_bits(group, left, right, who, new);
}

#endif
