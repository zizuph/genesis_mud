/* gresolle did it */

/* fuck I hate puck */

inherit "/std/spells" furmel;

#include <stdproperties.h>
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>

#define SCROLLFILE "/d/Roke/Athas/obj/the_coming_book"
#define MINIMUM 25
#define MAXIMUM 125
#define FAILMANA 10
#define SUCCESSMANA 50

#define CHECKPROP "_obj_component_to_blast"

void create_spells()
{
  add_name("bfbfbfss");
    set_name("papyrous");
    set_adj("black");
    add_adj("fluffy");
    set_short("black, fluffy piece of papyrous");
    set_long("This old papyrous is falling apart from age.\n"
        +"");

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 0);
        add_prop(OBJ_I_NO_DROP, "You really don't want to drop this!\n");
        add_prop(OBJ_M_NO_SELL, "The shopkeeper don't want it, so "+ 
                "can just as well stop think about selling it.\n");
    
    add_spell("blast","blast","Magic Hands Blast");
} 

damage(int strength)        {
  int damage;
        if (strength<MINIMUM)
        damage = MINIMUM;
                if (strength>MAXIMUM)
                damage = MAXIMUM;
        else
                damage = strength;
  return damage;
}

blast(string s)
{
  object enemy;
  int tohit;
  int dam;
  string text;

  if (TP->query_mana() < 40)
  {
      TP->catch_msg("You don't have sufficient mana to cast this spell.\n");
      return 1;
  }
  if(!(enemy = TP->query_attack()))
    {
      TP->catch_msg("You're not fighting anyone!\n");
      return 1;
    }

  TP->add_mana(-10);

  tohit = TP->query_stat(SS_WIS)+TP->query_skill(SS_UNARM_COMBAT);
  
  if((tohit-random(200))<0)
    {
      TP->catch_msg("You create a huge hole in the air with your hands!\n");
      return 1;
    }

  TP->add_mana(-40);

  dam = (TP->query_stat(SS_STR)*tohit)/200;

  dam = enemy->hit_me(dam,W_BLUDGEON,TP,-1)[0];

  text = "unharmed though";
  if (dam > 0)
      text = "sligthly hurt";
  if (dam > 15)
      text = "rather hurt";
  if (dam > 30)
      text = "very hurt";
  if (dam > 50)
      text = "crushed";



  TP->catch_msg("You hit "+QCTNAME(enemy)+" hard in the chest.\n"+
    capitalize(enemy->query_pronoun())+" looks "+text+".\n");
  return 1;
}
init()
{
  ::init();
    add_action("read","read");
  }

int read(string s)
{
  NF("read what?\n");
  if(!id(s))
    return 0;
  
  cat(SCROLLFILE);
  return 1;
}

query_auto_load() {
  string name;
  int i;

  sscanf(file_name(this_object()),"%s#%d", name, i);
  return name;
}

enter_env(object to,object from)
{
  ::enter_env(to,from);

  if(!to)
    return;
  
    remove_name("bfbfbfss");

    if(present("bfbfbfss",to))
      {
	to->catch_msg("The papyrouses magically melts together.\n");
	remove_object();
      }
    
    add_name("bfbfbfss");
  }




