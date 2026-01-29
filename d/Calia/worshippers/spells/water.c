
/*
    A water creature, called by an Elemental Worshipper of Calia
    by the spell "Kataraktas".

    Coded by Jaacar, 1996.

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


#define DECANTER "/d/Calia/worshippers/spells/decanter"
#define FLAGON "/d/Calia/worshippers/spells/flagon.c"

string summoner_str;
object summoner_ob;
int busy_alarm;

string    *randadj,
           summoner;

void create_creature()
{
   string    adj;

   randadj = ({"flowing", "translucent", "shimmering", "watery", "churning"});
   adj = randadj[random(sizeof(randadj))];

   set_name("boozer");
   add_name("weird");
    add_name(WOR_WATER_CREATURE);
    add_name(SUMMONED_CREATURE);
   set_race_name("water weird");
   set_gender(G_NEUTER);
   set_adj(adj);
   set_short(adj + " water weird");

   set_long("A vaguely humanoid shaped creature, comprised "+
       "completely of water, with the exception of the eyes "+
       "which are two large aquamarines.\n");

   set_m_in("sloshes in.");
   set_m_out("sloshes");

   set_mm_in("explodes in the room with the fury of a rainstorm.");
   set_mm_out("implodes upon itself and vanishes without a trace.");

   set_alignment(0);

   add_prop(CONT_I_WEIGHT, 500000);
   add_prop(CONT_I_VOLUME, 50000);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
   add_prop(OBJ_M_NO_ATTACK, 1);
   add_prop(MAGIC_I_RES_WATER, 90);
   add_prop(LIVE_I_NO_CORPSE, 1);

   set_stats(({25, 8, 8, 8, 1, 2}));

   set_skill(SS_AWARENESS, 50);

   set_attack_unarmed(0, 3, 3, W_BLUDGEON, 100, "watery arms");
   set_hitloc_unarmed(0, 5, 100, "watery body");
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
    command("emote implodes upon itself and vanishes.");
    get_summoner()->remove_prop(WOR_CREATURE_SUMMONED);
    tell_object(get_summoner(),"You feel the power of Kataraktas has worn off.\n");
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
    command("emote reforms from some leftover moisture in the air.");
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

    if (str == "decanter")
    {
        if (!present("_worship_decanter_",this_player()))
        {
            this_player()->catch_msg(QCTNAME(this_object()) + " hands a glowing "+
               "decanter to you.\n");
            say(QCTNAME(this_object()) + " hands a glowing decanter"
                + " to " + QTNAME(this_player()) + ".\n");
            clone_object(DECANTER)->move(this_player(),1);
            return;
         }
         else
         {
             command("say You already have the decanter!");
             return;
         }
    }
    if (str == "flagon")
    {
        if (!present("_worship_flagon_",this_player()))
        {
            this_player()->catch_msg(QCTNAME(this_object()) + " hands a glowing "+
               "flagon to you.\n");
            say(QCTNAME(this_object()) + " hands a glowing flagon"
                + " to " + QTNAME(this_player()) + ".\n");
            clone_object(FLAGON)->move(this_player(),1);
            return;
         }
         else
         {
             command("say You already have the flagon!");
             return;
         }
    }
    command("say I do not understand.");
    return;
}

string race_sound()
{
  return "gurgles";
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
     "The water from the vial grows in volume quickly.  "
    + QCNAME(this_object()) + " forms from within the water.\n");
  summoner_ob->add_prop(WOR_CREATURE_SUMMONED,this_object());
  return 1;
}

void
init_spell(object caster, object target, object prev)
{
    set_this_player(target);
    summon (target->query_real_name());
}
