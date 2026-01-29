inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include "/d/Gondor/defs.h"

create_object()
{
  set_name("Garlic_Stench_Object");
  add_prop(OBJ_I_VOLUME,0);
  add_prop(OBJ_I_WEIGHT,0);
  add_prop(OBJ_I_NO_DROP,1);
  add_prop(OBJ_I_INVIS,1);
}

void
enter_env(object to, object from)
{
  ::enter_env(to,from);
  if (!living(to)) 
  {
    remove_object();
    return;
  }
  set_alarm(300.0,0.0,"remove_stench");
}

void
init()
{
  ::init();
  add_action("do_breathe","breath");
  add_action("do_breathe","exhale");
}

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

int
do_breathe(string str)
{
  int i;
  string vb;
  object *ob;

  vb = query_verb();
  if(!stringp(str))
  {
    write("You exhale deeply, and the stench of garlic pervades your surroundings.\n");
    say(QCTNAME(TP)+" exhales deeply. The stench of garlic takes away your breath.\n");
  }
  else
  {
    ob = parse_this(str, "%l");
    if(!sizeof(ob))
    {
      NF(CAP(vb) + " at whom?\n");
      return 0;
    }
    write("You exhale deeply straight into the face of " +
      COMPOSITE_LIVE(ob) + ".\n");
    say(QCTNAME(TP) + " exhales deeply into the face of " +
      COMPOSITE_LIVE(ob) + ".\n", ob + ({TP}));
    for(i = 0; i < sizeof(ob); i++)
    {
      ob[i]->catch_msg(QCTNAME(TP) +
        " exhales deeply straight into your face.\n" +
        "The garlic stench is unbearable.\n" + 
        "You feel sick!\n");
      ob[i]->command("puke " + TP->query_real_name());
    }
  }
  return 1;
}

void
remove_stench()
{
  if(interactive(ENV(TO)))
    ENV(TO)->catch_msg("You feel your breath improving.\n");
  TO->remove_object();
}
