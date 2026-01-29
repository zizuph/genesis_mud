
/* 
    An creature of air, called by a Elemental Worshipper of Calia 
    by the spell "Stous".

    Coded by Jaacar & Maniac 1996. 

 */ 

#pragma save_binary

#include "defs.h"

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/domove";
inherit "/d/Calia/std/contents_desc"; 
inherit WOR_MAGIC_OBJECT;

#include <composite.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <options.h>
#include WORSHIP_HEADER
#include SPELLS_HEADER
#include COUNCIL_HEADER

/* 
 * The shout will carry 3 rooms away. Change this number for a different
 * depth - and don't make it more than 3!!
 */
#define SHOUT_DEPTH    3

string summoner_str;
object summoner_ob;
int busy_alarm;

mapping vc = WOR_VALID_CALL; 

int
is_worship(object pl)
{
    return (pl->query_guild_name_lay() == GUILD_NAME);
}


void 
create_creature()
{
   string    adj;

    adj = ({"vague", "indistinct","willowy","hazy","wispy"})[random(5)];

   set_name("speaker");
   add_name("spirit");
    add_name(WOR_AIR_CREATURE);
    add_name(SUMMONED_CREATURE);
   set_race_name("air spirit");
   set_gender(G_NEUTER);
   set_adj(adj);
   set_short(adj + " air spirit");

   set_long("A creature formed from winds and air, this "
     + "spirit is translucent and pale. Wisps of mist "
     + "form what might be strands of hair, billowing out "
     + "in a mad flurry.\n");

   set_m_in("floats in.");
   set_m_out("floats");
   set_mm_in("forms from merging gusts of wind.");
   set_mm_out("explodes in a fury of chaotic winds.");

   set_alignment(0);

   add_prop(CONT_I_WEIGHT, 10);
   add_prop(CONT_I_VOLUME, 1000);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(OBJ_M_NO_ATTACK, "The creature cannot be touched.\n");
    add_prop(OBJ_I_NO_ATTACK,"This creature cannot be touched.\n");
   add_prop(OBJ_M_NO_MAGIC_ATTACK, "The creature cannot be touched.\n");
   add_prop(MAGIC_I_RES_AIR, 90);
   add_prop(LIVE_I_NO_CORPSE, 1);
   add_prop(LIVE_I_SEE_INVIS, 5);
    add_prop(NPC_M_NO_ACCEPT_GIVE,1);

   set_stats(({2, 8, 8, 8, 1, 100}));

   set_skill(SS_AWARENESS, 50);

   set_attack_unarmed(0, 3, 3, W_BLUDGEON, 100, "airy fists");
   set_hitloc_unarmed(0, 5, 100, "airy body");
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
    command("emote dissolves into nothing."); 
    get_summoner()->remove_prop(WOR_CREATURE_SUMMONED);
    tell_object(get_summoner(),"You feel the power of Stous has worn off.\n");
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
    command("emote reforms from the winds before you."); 
}



void
shout_now(object *exclude, object *search, string what, int c, int max)
{
    int index, size;
    object *rooms; 

    if (SHOUT_DEPTH < 2) 
        return;

    if (c >= max) { 
        reform(); 
        return;
    } 

    rooms = FIND_NEIGHBOURS(search[c], SHOUT_DEPTH-1);
    rooms -= exclude;

    index = -1;
    size = sizeof(rooms); 

    while(++index < size)
         tell_room(rooms[index], "Carried on a strong gust of air, "
                      + "an angelic voice sings out: " + what + ".\n");

    exclude += rooms; 
    c++; 
    busy_alarm = set_alarm(1.0, 0.0, 
                    &shout_now(exclude, search, what, c, max)); 
}


void 
do_shout(string what)
{
    object *rooms;
    object troom;
    int    size;

    if(!(troom = environment(this_object())))
        return 0;

     /* We'll take care of this shout in stages, first let's 
        find the neighbouring rooms of this room to depth 1 */  
    rooms = FIND_NEIGHBOURS(troom, 1);
    size = sizeof(rooms);

    /* Then do a shout from each of those rooms (see shout_now) */ 
    if (size > 1) { 
        command("emote reverts to wind and blows away.");
        move_living("M", ELEMENTAL_ROOM); 
        busy_alarm = set_alarm(1.0, 0.0, 
                       &shout_now(({}), rooms+({}), what, 0, size)); 
        return;
    } 

    tell_room(this_object(), "Carried on a strong gust of air, "
                      + "an angelic voice sings out: " + what + ".\n");
}


void
do_speak(string what)
{
    command("say " + what);
}

int
is_worshipper(object ob)
{
    return ob->query_guild_name_lay() == GUILD_NAME;
}


void 
do_call(string what)
{
  object *people = filter(users(), is_worshipper);

  if (!sizeof(people))
     return;
 
  command("emote seems to disperse herself momentarily.");
  move_living("M", ELEMENTAL_ROOM); 

  busy_alarm = set_alarm(1.0, 0.0, reform);

  map(people, &->catch_msg("Upon the winds a light, airy voice calls "
                   + "out:\n" + break_string(what, 50) + "\n"));
}


void
do_look_exit(string what)
{
    string desc;
    object env, s;

    s = get_summoner(); 

    command(what); 

    env = environment(this_object()); 
    if (objectp(present(s, env))) {   
        command("confused"); 
        return;
    } 

    set_this_player(s); 

    move_living("X", environment(s)); 

    desc = ("\n" + room_desc(env,1)); 
    if (desc[strlen(desc)-1] == '\n') 
        desc = desc[0..(strlen(desc)-2)]; 

    tell_room(environment(this_object()),QCTNAME(this_object())+
        " whispers something to "+QTNAME(s)+".\n",({s}));
    tell_object(s,"The "+this_object()->short()+" whispers to you:\n"+
        desc+"\n");
}

void
do_look_person(string what)
{
    string desc;
    object s, env, person;

    s = get_summoner();
    person = find_living(what);

    move_living("X",environment(person));

    env = environment(this_object());
    if (objectp(present(s, env)))
    {
        command("confused");
        return;
    }

    set_this_player(s);

    move_living("X",environment(s));
    desc = ("\n" + room_desc(env,1));

    if (desc[strlen(desc)-1] == '\n')
        desc = desc[0..(strlen(desc)-2)];

    tell_room(environment(this_object()),QCTNAME(this_object())+
        " whispers something to "+QTNAME(s)+".\n",({s}));
    tell_object(s,"The "+this_object()->short()+" whispers to you:\n"+
        desc+"\n");

    setuid();
    seteuid(getuid());
    write_file("/d/Calia/worshippers/spells/scry",
        sprintf("%s %-11s on %-11s\n", ctime(time()),
        capitalize(s->query_real_name()), capitalize(what)));
}


/*
 * Ask and ye shal receive...
 */
void catch_question(string str)
{
  string   nm = this_player()->query_real_name();
  int      i;
  string   what;
    object env, person;

  if(nm != summoner_str)
    return;

  if(!strlen(str))
    return;

  /* Turns 'ask elemental to say Hello.' -> 'ask elemental say Hello.' */
  sscanf(str, "to %s", str);

  /* Shout something over a number of rooms */
  if (sscanf(str, "shout %s", what))
  {
    busy_alarm = set_alarm(1.0, 0.0, &do_shout(what));
    return;
  }

  /* Just say something */
  if (sscanf(str, "speak %s", what) || sscanf(str, "say %s", what))
  {
    busy_alarm = set_alarm(1.0, 0.0, &do_speak(what));
    return;
  }

  if (sscanf(str, "call %s", what)) 
  {
      if (get_summoner()->query_wiz_level())
      {
           what += (" (" +capitalize(summoner_str)+")");
           set_alarm(1.0, 0.0, &do_call(what));
           return;
      }
      if (COUNCIL_CODE->is_council_member(summoner_str))
      {
            if (file_name(environment(get_summoner())) == ALTAR_ROOM)
            {
                what += (" (" + capitalize(summoner_str)+")");
                set_alarm(1.0, 0.0, &do_call(what));
                return;
            }
      }
      if (stringp(what = vc[what])) 
      {   
          what += (" (" + capitalize(summoner_str) + ")");  
          busy_alarm = set_alarm(1.0, 0.0, &do_call(what));
      }
      return;
  } 

  if (sscanf(str, "look %s", what)) { 
     env = environment(this_object()); 
     if (member_array(what, env->query_exit_cmds()) > -1)  
         busy_alarm = set_alarm(1.0, 0.0, &do_look_exit(what)); 
    if (get_summoner()->query_skill(SS_CARVED) == ALL_FLAGS)
    {
     person = find_player(what);
     if (is_worship(person))
         busy_alarm = set_alarm(1.0, 0.0, &do_look_person(what));
     else if (summoner_ob->query_met(person) && !person->query_wiz_level())
    {
        if (summoner_ob->query_mana() < 50)
        {
            command("whisper to "+summoner_str+" You don't have enough mana!");
            return;
        }
        else
        {
        summoner_ob->add_mana(-50);
         busy_alarm = set_alarm(1.0, 0.0, &do_look_person(what));
        }
    }
    }
     return;
  } 
  command("confused"); 
}


string 
race_sound()
{
  return "sings in a light, airy voice";
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
     "A great wind arises, blowing into the area and forming "
    +"a swirling zephyr.\n"
    + QCNAME(this_object()) + " forms from the winds.\n");
  summoner_ob->add_prop(WOR_CREATURE_SUMMONED, this_object());
  return 1;
}

void
init_spell(object caster, object target, object prev)
{
    set_this_player(target);
    summon(target->query_real_name());
}


