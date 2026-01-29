inherit "/std/object";

#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>

#define SHADOW  OBJ_DIR+"bleeding_sh"

static mixed where;
static object shadow;

void 
create_object()
{
  set_name(({"wound","bleeding","_bleeding_wound_"}));
  set_adj(({"nasty","bleeding"}));
  set_short("nasty bleeding wound");
  set_long("Your life fluid slowly runs out through it taking you "+
		"closer to death every minute.\n");

  set_no_show_composite(1);
  add_prop(OBJ_I_VOLUME, 0);
  add_prop(OBJ_I_WEIGHT, 0);
  add_prop(OBJ_M_NO_DROP, 1);
}

void 
set_bleeding_where(string arg) { if(arg) where = arg; }
string 
query_bleeding_where() { return where; }

void
enter_env(object dest, object old)
{
  seteuid(getuid());
  ::enter_env(dest, old);
  if(living(dest))
  {
    if((shadow=clone_object(SHADOW)) && shadow->shadow_me(dest))
    {
      shadow->set_bleeding(TO);
      dest->catch_msg("You have a "+short()+
			(where ? " on your "+where : "")+".\n");
      dest->add_subloc(file_name(TO), TO);
      return;
    }
    else 
    {
      if(shadow) shadow->remove_shadow();
      remove_object();
    }
  }
}

void
leave_env(object old, object dest)
{
  ::leave_env(old, dest);
  if(living(old))
  {
    old->remove_subloc(file_name(TO));
    shadow->remove_shadow();
  }
}

string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc != file_name(TO))
      return "";

    if (for_obj != on)
      return CAP(HE(on))+" has a "+short()+
             (where ? " on "+HIS(on)+" "+where : "")+".\n";
    else
      return "You have a "+short()+
		(where ? " on your "+where : "")+".\n";
}

int
remove_object()
{
  if(shadow) shadow->remove_shadow();
  if(living(ENV(TO))) ENV(TO)->remove_subloc(file_name(TO));
  return ::remove_object();
}

string 
query_auto_load() 
{
  int *arg = shadow->query_bleeding_variables();

  return MASTER+":#1#"+where+"#2#"+arg[0]+"#3#"+arg[1]+"#"; 
}

void
init_arg(string arg)
{
  string foo;
  int a,b;

  sscanf(arg,"%s#1#%s#2#%d#3#%d#%s", foo, where, a, b, foo);

  if(where == "0") where = 0;
  set_alarmv(1.0, 0.0, "set_variables", ({ a, b }) );
}

mixed
query_shadow() { return shadow; }

void
set_variables(int a, int b)
{
  ENV(TO)->set_bleeding_variables(a, b);
}
