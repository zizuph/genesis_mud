/*
 * Quest-bit handler, for converting dec to bin.
 * Based on Gondor's file by the same name.
 * by Ellesar, March 1992, Mercade Sept 1993 and Olorin June 1995
 * Changed for Faerie by Finwe, April 2005
 *
 *	Do NOT include this file into your code!
 *	Inherit binbit.c instead!
 * 
 */
#pragma strict_types

#ifndef BIT_HANDLER
#define BIT_HANDLER 1

int *
convert_dec(int dec)
{
    int     i,
            n,
           *bin_arr = ({});

    while ((n++) < 8)
    {
        i = dec/2;
        bin_arr += ({ ((i*2) != dec) });
        dec = i;
    }
    return bin_arr;
}

int
convert_bin(int *bin_arr)
{
    int     dec,
            n;

    while (n<sizeof(bin_arr))
    {
        dec += ( (bin_arr[n] != 0) * (1 << n));
        n++;
    }
    return dec;
}

void
set_bin_bits(int group, int from_bit, int no_of_bits, object player, int dec)
{
    int     n,
           *bin_arr = ({});

    bin_arr = convert_dec(dec);

    seteuid(getuid(this_object()));
    while (n < no_of_bits)
    {
        if (!bin_arr[n])
            player->clear_bit(group, from_bit + n);
        else
            player->set_bit(group, from_bit + n);
        n++;
    }
}

int
query_bin_bits(int group, int from_bit, int no_of_bits, object player)
{
    int     n,
           *bin_arr = ({});

    while (n < no_of_bits)
    {
        bin_arr += ({ (player->test_bit("Gondor", group, from_bit + n)) });
        n++;
    }
    return convert_bin(bin_arr);
}

#endif
