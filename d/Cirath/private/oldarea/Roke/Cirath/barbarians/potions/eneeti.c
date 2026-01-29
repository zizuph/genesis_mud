inherit "/std/potion";
inherit "/lib/herb_support";

#include "/d/Roke/Cirath/defs.h"
#include "/d/Roke/common/defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <herb.h>
#include <wa_types.h>
#include <filter_funs.h>
#include "/std/combat/combat.h"
#include "/sys/poison_types.h"
#include <formulas.h>

int pint  = 10,
    ptime = 100,
    pdam  = 30;

static mixed parse_this(string str, string form)
{
  object   *oblist, *tmplist;
  int      i;

  tmplist = ({});
  if (!CAN_SEE_IN_ROOM(this_player()))
    return tmplist;

  if (!str || (!parse_command(lower_case(str), environment(this_player()),form,
    oblist)))
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

static void tell_watcher(string str, object me, object enemy)
{
  object *ob;
  int i;

  ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
  ob -= ({ enemy });
  for (i = 0; i < sizeof(ob); i++)
    if (ob[i]->query_see_blood())
      ob[i]->catch_msg(str);
}

int check(object ob)
{
  if(!living(ob))
    return 0;

  return 1;
}

void
create_potion()
{
  set_name("potion");
  set_adj("icky");
  add_adj("green");
  set_short("icky green potion");
  set_id_long("This green potion is called Eneeti. It is not meant to be "+
              "quaffed, but thrown at an enemy. When hitting it releases "+
              "a cloud of poison around the victim.The potion smells and "+
              "tastes awful.\n");
  set_unid_long("his is a icky green potion which doesn't smell very good "+
                "nor tasting any better.\n");
  set_unid_smell("The potion has an icky stench.\n");
  set_id_smell("The Eneeti potion has an icky stench.\n");
  set_unid_taste("Yech!!\n");
  set_id_taste("Yech! It tastes dreadful!!.\n");
  set_potion_name("eneeti");
  set_soft_amount(50);
  set_alco_amount(0);
  set_id_diff(10);
  set_potion_value(0);
  set_quaff_verb("quaff");
  set_effect(HERB_SPECIAL,"",0);

  add_prop(OBJ_I_VALUE, 0);
  add_prop(OBJ_I_NO_GIVE,1);
  add_prop(OBJ_I_NO_DROP,1);

  set_long("@@long_func");
}

void
init()
{
    ::init(); /* If this isn't added cmd items won't work. */

  add_action("throw_it","toss");
  add_action("quaff_it", quaff_verb);
  if (quaff_verb != "quaff")
    add_action("quaff_it", "quaff");
  if (quaff_verb != "taste")
    add_action("taste_it", "taste");
  if (quaff_verb != "smell")
    add_action("smell_it", "smell");
}

void
destruct_object()
{
  object ob;
 
 if (quaffed_it && quaff_verb != "quaff")
  {
    quaffed_non_quaff_potion();
  }
  else
  {
    do_herb_effects();
  }
  seteuid(getuid());

  ob = clone_object(OBJ+"flask");

  if (ob->move(environment(this_object())))
    ob->move(environment(this_object()), 1);

  set_alarm(0.0, 0.0, "remove_object");
}

void
special_effect()
{
  object ob;

  ob = clone_object(BARBARIANS+"obj/pois_obj");
  ob->set_interval(pint);
  ob->set_time(ptime);
  ob->set_damage(({POISON_FATIGUE, pdam, POISON_HP,pdam}));
  ob->move(this_player());
  ob->start_poison();
}

set_interval(interval) { pint = interval; }
set_time(time)         { ptime = time;    }
set_damage(dam)        { pdam = dam;      }

int throw_it(string str)
{
  object enemy,*a,ob,pois;
  string *s,person;
  int tdex,edex,i;

  reset_euid();
  s = explode( str, " ");

  NF("Toss what?\n");
  if(s[0] != "eneeti")
    return 0;

  NF("Toss where?\n");
  if(s[1] != "towards")
    return 0;

  person = lower_case(s[2]);

  NF("You can't throw the potion on everybody!.\n");
  if (!person || person == "all")
      return 0;
  
  NF("Toss Eneeti potion on who?\n");
  a = CMDPARSE_ONE_ITEM(person,"check","check");

  if(!sizeof(a))
    return 0;

  ob = a[0];

  enemy=TP->query_attack();
  if (!enemy || enemy != ob) 
  {
    TP->attack_object(ob);
  }

  tdex = TP->query_stat(SS_DEX);
  edex = ob->query_stat(SS_DEX);

  if (random(2 * tdex) > edex)
  {
    TP->catch_msg("You lobby the Eneeti potion towards "+QTNAME(ob)+" and manage "+
      "to hit "+ob->query_objective()+".\n The flask breaks and covers "+
      QTNAME(ob)+" in a green cloud of poison.\n");
    ob->catch_msg(QCTNAME(TP)+" lobbys a flask towards you and manages to hit you."+
      "\nThe flask breaks and releases a poison cloud which immideately surrounds "+
       "you.\n");
    tell_watcher(QCTNAME(TP)+" lobbys a flask towards "+QTNAME(ob)+" and manages "+
      "to hit "+ob->query_personjective()+".\n The flask breaks and a green cloud of "+
      "poison surrounds "+QTNAME(ob)+".\n",TP,ob);
    pois = clone_object(BARBARIANS+"obj/pois_obj");
    pois->set_interval(pint);
    pois->set_time(ptime);
    pois->set_damage(({POISON_HP,pdam,POISON_FATIGUE,pdam}));
    pois->move(ob);
    pois->start_poison();
  }
  else
  {
    TP->catch_msg("You lobby your Eneeti potion towards "+QTNAME(ob)+", but miss.\n");
    ob->catch_msg(QCTNAME(TP)+" lobbys a strange flask towards you. Luckily it misses.\n");
    tell_watcher(QCTNAME(TP)+" lobbys a strange flask towards "+QTNAME(ob)+
      ", but misses "+ob->query_objective()+".\n",TP,ob);
  }
  
  set_alarm(0.0, 0.0, "remove_object");
  return 1;
}
