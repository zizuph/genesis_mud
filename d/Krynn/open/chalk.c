/* The piece of chalk for the Cabal of Hiddukel. */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include "../guild/guild.h"
#include <stdproperties.h>
#include <macros.h>

#define CH_MAX_WRITING       30
#define CH_MAX_LENGTH       120
#define CHALK_MESSAGE       "There is writing on the " + where + " here.\n"

int ch_length;

void
init()
{
  ADA("write");
}


void
create_object()
{
   if (!IS_CLONE)
      return;
   
   set_name("piece of chalk");
   set_pname("pieces of chalk");
   add_name("chalk");
   add_name("piece");
   add_name(CHALK);
   set_short("piece of chalk");
   set_pshort("pieces of chalk");
   set_long("@@my_long");
   
   ch_length = CH_MAX_LENGTH;

   add_prop(OBJ_M_NO_SELL, 1);
   add_prop(OBJ_I_VALUE, "@@my_value");
   add_prop(OBJ_I_WEIGHT, 2);
   add_prop(OBJ_I_VOLUME, 10);
}

int
my_value()
{
  return ch_length + 10;
}


my_long()
{
  string str;
  if (ch_length == CH_MAX_LENGTH)
    str = "It looks brand new";
  else if (ch_length > CH_MAX_LENGTH * 13 / 15)
    str = "It looks almost ununsed";
  else if (ch_length > CH_MAX_LENGTH * 10 / 15)
    str = "It looks used";
  else if (ch_length > CH_MAX_LENGTH * 6 / 15)
    str = "It looks well used";
  else if (ch_length > CH_MAX_LENGTH * 2 / 15)
    str = "It is rather short";
  else if (ch_length > 0)
    str = "It is merely a stub";
  else
    str = "There is nothing left that you could possibly use, though";
  return "This is an ordinary piece of chalk you can write with. " +
         str + ".\n";
}

/* the chalk is there to write,
 * we write something
 */
write(string str)
{
  int dummy;
  string where;
  object writing_obj;
  object here = E(TP);
  NF("What?\n");
  if (E(TO) != TP)
    return 0;
  NF("It is too dark to see.\n");
  if (!CAN_SEE_IN_ROOM(TP))
    return 0;
  NF("Write what?\n");
  if (!str)
    return 0;
  NF("You are not able to write here.\n");
  if (!here)
    return 0;
 
  where = (here->query_prop(ROOM_I_INSIDE) ? "floor" : "ground");
  if (member_array(CHALK_MESSAGE, here->query_desc()) != -1)
    return 0;
  if (here->query_prop(ROOM_I_NO_EXTRA_DESC))
    return 0;

  NF("There isn't enough space here to write such a long message.\n");
  if (strlen(str) > CH_MAX_WRITING)
    return 0;

  if (strlen(str) > ch_length)
    str = extract(str,0,ch_length);
  seteuid(getuid(TO));
  ch_length -= strlen(str);
  where = (here->query_prop(ROOM_I_INSIDE) ? "floor" : "ground");
  TP->catch_msg("You write a message on the " + where + ".\n");
  dummy = random(CH_MAX_LENGTH * 3) - ch_length + (CH_MAX_LENGTH / 4);
  if (ch_length <= 0)
    TP->catch_msg("Hmmm, you used all the chalk, there is nothing left anymore.\n");
  else if (dummy < 0)
    {
      TP->catch_msg("Oops! The piece of chalk breaks. It is much shorter now.\n");
      ch_length += dummy;
      if (ch_length <= 0)
	TP->catch_msg("Hmmm, in fact there is nothing left anymore.\n");
    }
  writing_obj = clone_object(OBJ + "writing_obj");
  writing_obj->set_writing_text(str, where);
  writing_obj->move(here);
  writing_obj->initiate_self_destruct();
  SAYBB(" bends down and writes something on the " + where + ".");
  here->add_my_desc(CHALK_MESSAGE, writing_obj);
  if (ch_length <= 0)
    set_alarm(3.0,0.0,"remove_object");
  return 1;
}
