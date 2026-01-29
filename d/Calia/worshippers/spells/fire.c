
/*
 * This little 'fella will light up all the adjoining rooms
 * of the caster with seperate flame
 * objects.
 */

#pragma save_binary

#include "defs.h"

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/domove";
inherit "/std/act/action";
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

#define FIRE_PATH "/d/Calia/worshippers/spells/flames"

string summoner_str;
object summoner_ob;
int busy_alarm;

string    *randadj,
           summoner;
object    *flames = ({ }),
           waiting_room,
          *all_flames = ({ });

void create_creature()
{
   string adj;

   randadj = ({"roaring", "red", "menacing", "terrible"});
   adj = randadj[random(sizeof(randadj))];

   set_name("light-bringer");
   add_name("djinni");
    add_name(WOR_FIRE_CREATURE);
    add_name(SUMMONED_CREATURE);
   set_race_name("fire djinni");
   set_gender(G_NEUTER);
   set_adj(adj);
   set_short(adj + " fire djinni");

   set_long("Composed of roaring flames churning about in a chaos "
      + "of fiery tendrils, this creature is not of this world. "
      + "The flames shape and form itself constantly, but there "
      + "does seem to be a vague resemblance to a humanoid "
      + "figure.\n");

   set_m_in("arrives trailing fire and smoke.");
   set_m_out("leaves");
   set_mm_in("forms from a violent explosion of smoke and flames.");
   set_mm_out("dies out and fades away.");

   set_act_time(10);
   add_act(VBFC_ME("make_flicker"));

   set_alignment(0);

   add_prop(OBJ_I_LIGHT, 2);
   add_prop(CONT_I_LIGHT, 2);
   add_prop(CONT_I_HEIGHT, 30); 
   add_prop(CONT_I_WEIGHT, 10);
   add_prop(CONT_I_VOLUME, 100);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(OBJ_M_NO_ATTACK, "The flames on its body prevent that.\n");
   add_prop(MAGIC_I_RES_FIRE, 90);
   add_prop(LIVE_I_NO_CORPSE, 1);
   add_prop(LIVE_I_SEE_INVIS, 5);
   add_prop(OBJ_M_NO_INS, 1); 
   remove_prop(OBJ_M_NO_GET); 

   set_stats(({2, 8, 8, 8, 1, 2}));

   set_skill(SS_AWARENESS, 50);

   set_attack_unarmed(0, 3, 3, W_BLUDGEON, 100, "fiery hands");
   set_hitloc_unarmed(0, 5, 100, "fiery body");

   seteuid(getuid());
   waiting_room = clone_object("/std/container");
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
    command("emote explodes shooting flames everywhere, forcing "+
        "you to close your eyes.  When you open your eyes again, it "+
        "is gone.");
    get_summoner()->remove_prop(WOR_CREATURE_SUMMONED);
    tell_object(get_summoner(),"You feel the power of Psotia has worn off.\n");
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
    command("emote reforms from a violent explosion of smoke and flame.");
}

string race_sound()
{
  return "churns in a rasping voice";
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
     "A wave of heat suddenly blows into the area, oppressing and "
    +"fearful.\n"
    + QCNAME(this_object()) + " forms from a massive swirl of smoke "
    + "and ash.\n");

  set_alarm(2.0, 0.0, &command("say I shall light your path, O Great "
    + capitalize(summoner_str) + "!"));
  summoner_ob->add_prop(WOR_CREATURE_SUMMONED,this_object());
  return 1;
}

void goto_him()
{
  object  who;

  if(!strlen(summoner))
   return;

  who = find_living(summoner);

  if(!who)
   return;

  if(!present(summoner, environment(this_object())))
  {
    if(who && !who->query_linkdead())
     move_living("X", environment(who));
  }
}

void init_living()
{
  ::init_living();

  if(!strlen(summoner))
   return;

  if(!present(summoner, environment(this_object())) && find_living(summoner))
   set_alarm(2.0, 0.0, goto_him);
}

/*
 * Since we are moving lots of objects to different rooms every
 * time we enter a room, it would be cpu-unfriendly
 * to keep cloning new flames. Therefore, whenever a flame
 * is dormant (ie, it is not in an adjoining room to the djinni)
 * it will be put in the waiting_room, and then summoned out again
 * when it is next needed. This bypasses the need to keep cloning
 * and destructing the flame objects over and over again.
 */
void add_dormant_flame(object ob)
{
  ob->move(waiting_room, 1);

  if(member_array(ob, flames) == -1)
    flames += ({ ob });
}

/*
 * Are there any flames waiting for me in the waiting_room?
 * If not, clone one.
 */
object get_flame()
{
  object   ob;

  seteuid(getuid());

  if(sizeof(flames))
  {
    while(!objectp(ob))
    {
      ob = flames[0];
      flames -= ({ ob });
    }
   }
   else  
   {
     ob = clone_object(FIRE_PATH);
     all_flames += ({ ob });
   }

   return ob;
}

int flame_filt(object ob)
{
  object where;

  if(!objectp(ob))
   return 0;

  if(!(where = environment(ob)))
   return 0;

  if(!where->query_prop(ROOM_I_IS))
   return 0;

  if(present(ob, environment(this_object())))
   return 0;

  if(member_array(file_name(where), 
     environment(this_object())->query_exit_rooms()) != -1)
   return 0;

  return 1;
}

/*
 * Every time I enter a new room, move the flames to all of my
 * adjoining rooms.
 */
void enter_env(object to, object from)
{
   string *where;
   object  ob, room;
   int     i;

   ::enter_env(to, from);

   filter(all_flames, flame_filt)->dormant();

   if(!to->query_prop(ROOM_I_IS))
    return;

   get_flame()->moveto(to, this_object());

   where = to->query_exit_rooms();

   if(!sizeof(where))
    return 0;

   for(i=0;i<sizeof(where);i++)
   {
     if(!(room = find_object(where[i])))
       continue;

     if(room != environment(this_object())
       && !present("elemental_fire", room))
        get_flame()->moveto(room, this_object());
   }   
}

/*
 * For debugging...
 */
object *query_flames()
{
  return flames;
}

object *query_all_flames()
{
  int       i;
  object   *where = ({ }),
            env;

  for(i=0;i<sizeof(all_flames);i++)
  {
    if(objectp(all_flames[i]))
    {
      env = environment(all_flames[i]);
      where += ({ env });
    }
  }

  return where;
}
    
void
init_spell(object caster, object target, object prev)
{
    set_this_player(target);
    summon (target->query_real_name());
}

string make_flicker()
{
  all_flames->flicker();
  return "emote seems to reform to a new shape.";
}

