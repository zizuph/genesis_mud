/*
 *	WARNING!
 *
 *	This file is obsolete! Do not use!
 *
 *	Olorin, February 1997
 */
/* Quest-bit handler, for converting dec to bin.
 * By Elessar for Genesis, March '92.
 * Thanks to Nick of Krynn for the idea, Aedil of Alchar for binary-education.
 */

int *
convert_dec(int dec)
{
  int a,i,n;
  int *bin_arr;
  a = dec;
  bin_arr = ({});
  while (n < 8) {
    i = a/2;
    if (i * 2 != a) bin_arr = bin_arr +({ 1 });
    else bin_arr = bin_arr + ({ 0 });
    n++;
    a = i;
    }
  return bin_arr;
}

int
convert_bin(int *bin_arr)
{
  int dec,n;
  while (n<sizeof(bin_arr)) {
    dec = dec +(bin_arr[n] * (1 << n));
    n++;
    }
  return dec;
}

void
set_bin_bits(int group, int from_bit, int no_of_bits, object player, int dec)
{
  int i, n, *bin_arr;
  bin_arr = ({});
  bin_arr = convert_dec(dec);
  seteuid(getuid(this_object()));
  while (n < no_of_bits) {
    if (!bin_arr[n]) player->clear_bit(group, from_bit + n);
    else player->set_bit(group, from_bit + n);
    n++;
    }
}

int
query_bin_bits(int group, int from_bit, int no_of_bits, object player)
{
  int i, n, dec, *bin_arr;
  bin_arr = ({});
  while (n < no_of_bits) {
    bin_arr = bin_arr + ({ (player->test_bit("Gondor",group, from_bit + n)) });
    n++;
    }
  dec = convert_bin(bin_arr);
  return dec;
}

