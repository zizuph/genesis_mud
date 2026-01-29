/*
 * Quest-bit handler, for converting dec to bin.
 * By Elessar for Genesis, March '92.
 * Thanks to Nick of Krynn for the idea, Aedil of Alchar for binary-education.
 * Typecasted by Mercade, Sept 1993
 * Fixed domain guessing by Arandir, June 2005
 *
 *	Do NOT include this file into your code!
 *	Inherit /d/Gondor/common/lib/binbit.c instead!
 *	Olorin, June 1995
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
    string  dom;
    int     n,
           *bin_arr = ({});

    // Get the domain from the EUID of the caller, same as
    // the clear_bit and set_bit commands do. If there is
    // no domain available, return 0 straight away.

    dom = geteuid (this_object ());
    // Removed by Palmer 23 Oct 2005:
    // write(dom+"\n");
    if (SECURITY->query_domain_number (dom) < 0)
    {
      return (0);
    }
    
    while (n < no_of_bits)
    {
        bin_arr += ({ (player->test_bit(dom, group, from_bit + n)) });
        n++;
    }
    return convert_bin(bin_arr);
}

#endif
