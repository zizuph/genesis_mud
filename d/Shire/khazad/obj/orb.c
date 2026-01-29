inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Shire/defs.h"

/* Global Variables */
int orb_shine = 0;
int stage = 0;
 
/* Prototypes */
void show_and_tell();
void lights_out();
 
void
create_object()
{
  set_name("orb");
  set_short("@@short_description@@");
  set_long("@@long_description@@");

  add_prop(OBJ_I_WEIGHT, 1000);
  add_prop(OBJ_I_VOLUME, 1000);
  add_prop(OBJ_I_VALUE, 0);
}

string
short_description()
{
  if (orb_shine)
    return "shimmering orb";

  else
    return "crystal orb";
}

string
long_description()
{
  if (orb_shine)
  {
    return "A shimmering orb one foot in diameter. It radiates a "+
           "pure, soft light and instills in you a sense of serenity "+
           "and peace. You feel a warmth roll over your body as the "+
           "orb's light caresses you. A true treasure of the ancient "+
           "days of Khazad-dum.\n";
  }

  else
  {
    return "A crystaline orb one foot in diameter. It dazzles as "+
           "it reflects any light that falls upon its highly polished "+
           "surface. Light weight and fragile this orb would surely "+
           "shatter if not handled carefully.\n";
  }
}
 
mixed
query_magic_protection(mixed prop, object for_who)
{
  if (for_who == TP)
  {
    if (prop == MAGIC_I_RES_COLD)
      return ({ 25, 1 });
    
    else
      return 0;
  }

  else
    return ::query_magic_protection(prop, for_who);
}

int
do_shine(string str)
{

  if (!str)
    return 0;

  else if (ENV(TO) != TP)
    return 0;
 
  else if (str != "aglareb elena")
    return 0;

  else if (orb_shine)
  {
    write("Your words have no further effect.\n");
    return 1;
  }
  
  else
  {
    set_alarm(1.0,0.0,show_and_tell);
    return 1;
  }
}

void
show_and_tell()
{
  switch (stage)
  {
    case 0:
      write("Craddeling the "+short()+" in both hands you raise it "+
            "above your head.\n");
      say(QCTNAME(TP) +" raises the "+short()+" with arms "+
         "outstretched.\n");
      stage = 1;
      set_alarm(2.0,0.0,show_and_tell);
      break;
    case 1:
      write("The "+short()+" shines with the light of the stars.\n");
      say(QCTNAME(TP) +" mumbles something and the "+short()+" begins "+
         "to shine.\n");
      add_prop(OBJ_I_LIGHT, 4);
      TP->add_magic_effect(this_object());
      TP->add_mana(-50);
      set_alarm(300.0, 0.0, lights_out);
      stage = 0;
      orb_shine = 1;
      break;
  }
}  

void
lights_out()
{
  if (ENV(TO) == TP)
  {
    tell_room(ENV(TP), "The "+short()+" quickly dims.\n");
    TP->remove_magic_effect(TO);
  }
 
  else
    tell_room(ENV(TO), "The "+short()+" quickly dims.\n");
 
  orb_shine = 0;
  add_prop(OBJ_I_LIGHT, 0);
}
 
void
init()
{
  ::init();
  add_action(do_shine,"say");
  add_action(do_shine,"'",2);
}

void
leave_env(object from, object to)
{
  ::leave_env(from, to);
  
  if (TP->query_magic_res(MAGIC_I_RES_COLD))
    TP->remove_magic_effect(this_object());
}
