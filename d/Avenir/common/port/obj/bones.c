/* Shipcaptain bones for bury bones quest
 *  Cirion 040996
 */
inherit "/std/object";
#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/port/bury_bones.h"

int    ring = 1;

void crumble(object who);

void create_object()
{
  set_name("bones");
  add_name(BONES_ID);
  add_name("skeleton");
  set_adj(({"old","wet","ancient"}));
  set_short("pile of old bones");
  set_long("They are a pile of disjointed bones "
   +"from a human skeleton. The skull lies in the "
   +"centre, staring upwards with a gruesome leer "
   +"on its face. @@see_ring@@\n");

  ACI("bones",({"feel","touch"}),"They are still wet.\n");

  add_prop(OBJ_I_WEIGHT, 2000);
  add_prop(OBJ_I_VOLUME, 10000);
  add_prop(OBJ_I_VALUE, 3);
  add_prop(OBJ_M_NO_BUY, 1);

  seteuid(getuid());
}

string see_ring()
{
  if(!ring)
   return "";
  if(TP->query_skill(SS_AWARENESS) < 28)
   return "";

  return "You can see a pale glimmering, like a ring, "
   +"on one of the finger digits in the pile.";
}

void enter_env(object to, object from)
{
    ::enter_env(to, from);

    LOG_THIS(to->query_name() +" got the bones.");    
    if(interactive(to) && to->test_bit("Avenir", GROUP, BIT))
        set_alarm(25.0, 0.0, &crumble(to));
}

void crumble(object who)
{
  object     where;

  if(!present(TO, who))
   return;

  seteuid(getuid());
  LOG_THIS("The bones fell apart in "+who->query_name()
          +"'s inventory");
  who->catch_msg(CAP(LANG_THESHORT(TO))+" falls apart in "
    +"your hands.\n");
  set_alarm(0.1, 0.0, remove_object);
}

void init()
{
  ::init();

  add_action("pull","pull");
  add_action("pull","pry");
  add_action("pull","get");
}

int pull(string str)
{
  if(TP->query_skill(SS_AWARENESS) < 28 || !ring)
    return 0;

  NF(CAP(QVB)+" what?\n");
  if(!parse_command(str, ({}), 
      "[the] 'ring' [from] [the] [pile] / [finger] / [bones]"))
   return 0;

  NF("You try to reach into the bones to "+QVB+" the ring, "
    +"but you cannot quite reach it.\n");
  if(TP->query_stat(SS_DEX) < random(100) + 35)
   return 0;

  seteuid(getuid());
  clone_object(PORT+"obj/signet")->move(TP, 1);
  ring = 0;
  write("You manage to slide the ring off the finger digit.\n");
  return 1;
}
