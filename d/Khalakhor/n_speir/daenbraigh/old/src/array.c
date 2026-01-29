/*
 * Perl style array functions
 * TAPAKAH, 10/2005
 */

public nomask mixed
pop_arr(mixed array)
{
  mixed tail;
  int t;

  t = sizeof(array) - 1;
  tail = array[t];
  exclude_array(array,t,t);

  return tail;
}

public nomask int
push_arr(mixed array,mixed element)
{
  array += ({element});

  return sizeof(array);
}

public nomask mixed
shift_arr(mixed array)
{
  mixed head;

  head = array[0];
  exclude_array(array,0,0);

  return head;
}

public nomask int
unshift_arr(mixed array, mixed element)
{
  array = ({element}) + array;

  return sizeof(array);
}
