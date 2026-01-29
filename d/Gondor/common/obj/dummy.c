inherit "/std/object";

create_object()
{
  set_name("dummy");
  set_short("dummy object");
  set_long("This is a dummy object. You wonder what it might be for.\n");
}

 /*
  * This function approximates:  sqrt(weight+volume) 
  * I assume a mean value for (weight + volume) of mean = 150000
  * the function is only valid for the vicinity of this value,
  * ie for about 30000 .. 400000
  * In this region the error is below 10%
  * The square root of the mean value, sqmean, has to be inserted by hand
  *
  * The formula uses a Taylor expansion of
  *     sqrt( 1 + x )
  */

int
calc_sqrt(int weight, int volume)
{
  int mean, sqmean, scale, div;
  int x, z;

  mean = 150000;
  sqmean = 387;
  scale = 1000;
  div = mean/scale;

  x = (weight + volume - mean) / div;
  write("x: " + x + "\n");
  z = ( scale + x/2 - (x*x)/8/scale + (x*x*x)/16/scale/scale);
  write("weight: " + weight + "  volume: " + volume + "  result: " + z + "\n");
  z = z * sqmean / scale;
/*
  z = z * scale / 7;
*/
  write("weight: " + weight + "  volume: " + volume + "  result: " + z + "\n");
  return z;
}
