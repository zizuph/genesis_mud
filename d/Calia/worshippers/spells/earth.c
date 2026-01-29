
/*
    An earth creature, called by an Elemental Worshipper of Calia
    by the spell "Choma".

    Coded by Jaacar 1996.

 */

#pragma save_binary

#include "defs.h"

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/domove";
inherit WOR_MAGIC_OBJECT;

#include <composite.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include WORSHIP_HEADER
#include SPELLS_HEADER

string summoner_str;
object summoner_ob;
int busy_alarm;

string    *randadj;

void create_creature()
{
   string    adj;

   randadj = ({"massive", "huge", "large", "rumbling", "grotesque"});
   adj = randadj[random(sizeof(randadj))];

   set_name("bearer");
   add_name("golem");
    add_name(WOR_EARTH_CREATURE);
    add_name(SUMMONED_CREATURE);
   set_race_name("earth golem");
   set_gender(G_NEUTER);
   set_adj(adj);
   set_short(adj + " earth golem");

   set_long("It is a huge, lumbering creature, shapeless and "
     +"grey. It seems to be made from dark clay, and two "
     +"dark holes signify where the eyes might be.\n");

   set_m_in("lumbers in.");
   set_m_out("lumbers");
    set_mm_in("reforms from the ground before you.");
    set_mm_out("turns into a fine dust and blows away.");

   set_alignment(0);

   add_prop(CONT_I_WEIGHT, 500000);
   add_prop(CONT_I_VOLUME, 50000);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(NPC_M_NO_ACCEPT_GIVE, VBFC_ME("check_give"));
   add_prop(OBJ_M_NO_ATTACK, 1);
   add_prop(MAGIC_I_RES_EARTH, 90);
   add_prop(LIVE_I_NO_CORPSE, 1);

   set_stats(({150, 8, 8, 8, 1, 100}));

   set_skill(SS_AWARENESS, 50);

   set_attack_unarmed(0, 3, 3, W_BLUDGEON, 100, "clay arms");
   set_hitloc_unarmed(0, 5, 100, "clay body");
}

mixed
get_summoner()
{
    if (!objectp(summoner_ob) && stringp(summoner_str))
        summoner_ob = find_player(summoner_str); 

    if (summoner_ob->query_linkdead()) 
        return 0;

    return summoner_ob;    
}

void
notify_dispel_magic(object dispeller)
{
    command("drop all");
    command("emote crumbles into fine dust.");
    get_summoner()->remove_prop(WOR_CREATURE_SUMMONED);
    tell_object(get_summoner(),"You feel the power of Choma has worn off.\n");
}

void
warn_caster()
{
    tell_object(get_summoner(),"You feel the power of Choma has almost worn off.\n");
}

void
recall()
{
    object s;

    s = get_summoner();

    if (!objectp(s))
        remove_object();

    remove_alarm(busy_alarm);

    move_living("X", environment(s));
}


void 
reform()
{
    object s; 

    s = get_summoner(); 

    if (!objectp(s)) 
        remove_object(); 

    if (environment(this_object()) == environment(s)) 
        return;

    move_living("M", environment(s)); 
    command("emote reforms before you.");
}

/*
 * Only receive items from me
 */
mixed check_give()
{
  if ((this_player()->query_real_name() == summoner_str)
     && present(this_player(), environment(this_object())))
    return 0;

  return " will not accept it.\n";
}

/*
 * Ask and ye shal receive...
 */
void catch_question(string str)
{
  mixed   *things;
  string   nm = this_player()->query_real_name();
  int      i;
  object  *moved = ({});

  if(nm != summoner_str)
    return;

  if(!strlen(str))
    return;

  sscanf(str, "for %s", str);

  if(str == "all")
  {
    if(!command("give all to " + nm))
     command("say I cannot.");
    return;
  }

    if (str == "get")
    {
        command("get all");
        return;
    }

    if (str == "fill")
    {
        if (!command("put things in pack"))
            command("say I cannot.");
        return;
    }

    if (str == "empty")
    {
        if (!command("get all from pack"))
            command("say I cannot.");
        return;
    }

  things = FIND_STR_IN_OBJECT(str, this_object());
  things = FILTER_SHOWN(FILTER_DEAD(things));

  if(!sizeof(things))
  {
    command("say I have no " + str + ".");
    return;
  }

    if (str == "things")
    {
        command("say I have " + COMPOSITE_DEAD(all_inventory(this_object())));
        return;
    }

  for(i=0;i<sizeof(things);i++)
  {
    if(!things[i]->move(this_player()))
     moved += ({ things[i] });
  }

  if(!sizeof(moved))
  {
    command("say I cannot.");
    return;
  }

  this_player()->catch_msg(QCTNAME(this_object()) + " raises up and hands "
   + COMPOSITE_DEAD(moved) + " to you.\n");
  say(QCTNAME(this_object()) + " hands " + COMPOSITE_DEAD(moved)
   + " to " + QTNAME(this_player()) + ".\n");
  return;
}

string race_sound()
{
  return "booms";
}

int 
summon(string str)
{

  if (strlen(summoner_str))
      return 0;

  summoner_str = lower_case(str);

  if(!(summoner_ob = find_player(summoner_str)))
      return 0;

  move_living("M", environment(summoner_ob));
  tell_room(environment(this_object()), 
     "The earth shakes and groans, and suddenly it parts as "
    + QNAME(this_object()) + " forms from the clay.\n");
  summoner_ob->add_prop(WOR_CREATURE_SUMMONED, this_object());
  return 1;
}

void
init_spell(object caster, object target, object prev)
{
    set_this_player(target);
    summon (target->query_real_name());
    set_alarm(540.0,0.0,warn_caster);
}

