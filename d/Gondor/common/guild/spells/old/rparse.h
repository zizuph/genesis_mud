#include "/sys/cmdparse.h"

static mixed
parse_this(string str, string form)
{
  object   *oblist, *tmplist;
  int      i;
  tmplist = ({});
  if (!CAN_SEE_IN_ROOM(this_player()))
    return tmplist;
  
  if (!str || (!parse_command(lower_case(str), environment(this_player()),
			      form, oblist)))
    return ({});
  
  oblist = NORMAL_ACCESS(oblist, 0, 0);
  
  if (!sizeof(oblist))
    return ({});
  for (i = 0; i < sizeof(oblist); i++)
    {
      if (objectp(oblist[i]) && living(oblist[i]) &&
	  (this_player() != oblist[i]) &&
	  CAN_SEE(this_player(), oblist[i]))
	tmplist = tmplist + ({ oblist[i] });
    }
  return tmplist;
}






















