
/*
   A little gophero, used in the gopheroo catching quest in Gelan.
   It must be caught by a series of actions, using one of the special 
   trash heap objects. See the quest doc for more details.
   It will usually try to escape if successfully picked up,
   and will scamper away if one tries to catch it unsuccessfully.
   It will also periodically scamper away of its own accord.
   It is not a tough creature and will scamper away on attack also.

   Coder: Maniac

   History:
           12/4/98    rabbit -> gopheroo                      Maniac
           16/8/97    updated alarm handling                  Maniac 
           25.1.95    Modified on quest change                Maniac
   
*/

#pragma save_binary

inherit "/std/creature";
inherit "/std/combat/unarmed";  

inherit "/std/act/domove"; 
inherit "/std/act/action";

void stop_docile();
void bolt(); 
void struggle();


#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include <filter_funs.h>
#include <tasks.h>
#include "monster.h"
#include GOPHEROO_QUEST

/*
 * Attack and hitloc id's 
 */
#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1

string *bolt_to;
int struggle_alarm = 0;
int bolt_alarm = 0;
int docile_alarm = 0;
int docile = 0;
int struggled_once = 0;
int bolt_count = 0;


void
gopheroo_moves()
{
    set_m_in("bounces in at high speed.");
    set_mm_in("bounces in at high speed.");
    set_m_out("bounces away at high speed.");
    set_mm_out("bounces away at high speed.");
}


void
twitch_nose()
{
    if (living(environment(this_object())) || docile)
        return;
    command("emote twitches its nose.");
}



void
prick_ears()
{
    if (living(environment(this_object())) || docile)
        return;
    command("emote pricks up its ears.");
}


void
hop()
{
    if (living(environment(this_object())) || docile)
        return;
    command("emote bounces around slowly.");
}


void
scratch()
{
    if (living(environment(this_object())) || docile)
        return;
    command("emote scratches its head with one of its hind legs.");
}



/* Make the gopheroo docile, so that it can be picked up, won't bolt
   and won't struggle for the duration of its docility */
void
make_docile()
{
    docile = 1; 
    if (!docile_alarm)
        docile_alarm = set_alarm(60.0, 0.0, stop_docile);
}


/* Stop the period of docility of the gopheroo */
void
stop_docile()
{
    docile = 0;
    docile_alarm = 0;
}

/* 
   Start bolting (if not being held by a living)
   of bolting regularly. This makes it harder to find the
   gopheroo and do what you have to do before it bolts again.
*/
start_bolt()
{
    object in = environment(this_object());

    if (living(in) || (bolt_alarm) || (struggle_alarm))
        return; 
    else
        bolt_alarm = set_alarm(120.0, 0.0, bolt); 
}


/* Stop bolting regularly. Will still bolt if attacked though */
stop_bolt()
{
    if (bolt_alarm)
        remove_alarm(bolt_alarm);
    bolt_alarm = 0;
}



/* bolt, only if not in a living environment.
   If in a living environment, or an environment with no
   players, stop trying to bolt */
bolt()
{
    object in = environment(this_object());

    if (docile)
        return;

    if (living(in) || !sizeof(FILTER_PLAYERS(all_inventory(in))))
    {
        stop_bolt();
        return;
    }

    if (bolt_count >= sizeof(bolt_to)) 
        bolt_count = 0; 
    if (bolt_to[bolt_count] == file_name(in)) { 
        bolt_count++; 
        if (bolt_count >= sizeof(bolt_to)) 
            bolt_count = 0; 
    } 

    move_living("X", bolt_to[bolt_count]); 
    bolt_count++; 
    stop_bolt(); 
    start_bolt(); 
}



/* If being held by a living, start struggling. */
start_struggle()
{
    object in = environment(this_object());

    if (!living(in) || (struggle_alarm) || (bolt_alarm))
       return;
    else
       struggle_alarm = set_alarm(6.0, 0.0, struggle);  
}


/* stop struggling */
stop_struggle()
{
    if (struggle_alarm)
        remove_alarm(struggle_alarm);
    struggle_alarm = 0;
}


/* gopheroo successfully jumps out of the living's grasp */
jump_out()
{
  object in = environment(this_object());

  stop_struggle();   

  if (!living(in)) 
      return;
  else {
      in->catch_msg(this_object()->query_The_name(in) + 
                    " wriggles free of " +
                    "your grasp and jumps out of your arms!\n");
      if (in->query_skill(SS_ANI_HANDL) < HANDL_MIN) 
          in->catch_msg("You just aren't good enough with animals, are " +
                        "you!\n");
      tell_room(environment(in), QCTNAME(this_object()) + " wriggles " +
                    "free of " + QTNAME(in) + "'s grasp and jumps out " +
                    "of " + in->query_possessive() + " arms!\n", in);
      move(environment(in));
      start_bolt();
      struggled_once = 0;
  }
}


/* gopheroo tries to struggle free from the living's grasp */
struggle()
{
  object in = environment(this_object());

  if (docile_alarm) {
      remove_alarm(docile_alarm);
      docile = 0;
      docile_alarm = 0;
  }

  if (in->id(OWNER_NAME))
    return;

  if (!living(in)) {
    stop_struggle();
    return;
  }
  else  {
    in->catch_msg(QCTNAME(this_object()) + " frantically " +
          "tries to wriggle out of your grasp.\n");
    tell_room(environment(in), QCTNAME(this_object()) + 
          " frantically tries to wriggle out of " +
          QTNAME(in) + "'s grasp.\n", in); 

    if ((in->query_skill(SS_ANI_HANDL) >= HANDL_MIN) &&
        (struggled_once == 0)) {
      struggled_once = 1;
      in->catch_msg("You manage to " +
         "hold onto it though! Better give it back to its owner quick " +
         "or you may not be so lucky next time!\n");
      tell_room(environment(in), capitalize(in->query_pronoun()) + 
         " manages to hold onto it though!\n", in);

      stop_struggle();
      struggle_alarm = set_alarm(180.0, 0.0, struggle); 
    }
    else 
       jump_out(); 
  }
}



/* bolt if attacked, as long as not being held by attacker */
void
attacked_by(object attacker)
{
    object in = environment(this_object());

    ::attacked_by(attacker);
    if (!living(in)) 
        start_bolt(); 
}


/* start struggle if going to living */
void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    if (living(to)) {
        stop_bolt(); 
        start_struggle(); 
        struggled_once = 0;
    }
}



void
init_living()
{
    ::init_living(); 
    if (interactive(this_player())) 
        start_bolt(); 
}


/* if gopheroo eats the carrot ok, it is docile (pick-uppable) */
void
docile_seq(object from)
{
    if (command("eat carrot")) {
        make_docile();
        from->add_prop(I_TRAPPED_GOPHEROO, 1);
        tell_room(environment(from), DOCILE_MSG);
     }
}



/* gopheroo doesn't want a rotten carrot */
void
rotten_carrot(object from, string str)
{
     tell_room(environment(from), str);
     command("drop carrot");
}


void
no_accept(object ob)
{
    object in = environment(this_object());

    tell_room(in, "The " + short() + " doesn't want " +
                  LANG_THESHORT(ob) + " and leaves it.\n");
}


/* trying to take the gopheroo */
mixed
get_check()
{
    if (docile) 
        return 0;
    else 
        return "The gopheroo bounces away from your hands.\n";
}


/* receieve objects, will only accept carrots */
void
enter_inv(object ob, object from)
{
  object in = environment(this_object());

  ::enter_inv(ob, from);

  if (living(in) && (from == in)) 
  { 
     in->catch_msg("The " + short() + " doesn't want " +
                   LANG_THESHORT(ob) + " and leaves it.\n");
     ob->move(in);
     return;
  }
  else if (!living(in) && (ob->id(CARROT_NAME)) && living(from)) 
  {
    if (!(ob->query_condition()))
     {
       set_alarm(0.2, 0.0, &rotten_carrot(from, ob->fail_catch()));
       return;
     }
    else  
    {
      set_alarm(0.2, 0.0, &docile_seq(from));
      return;
    }
  }
  else if (living(from)) 
  {
     set_alarm(0.2, 0.0, &no_accept(ob));
     ob->move(in);
     return;
  }
}


void
create_creature()
{
    set_name("bouncer"); 
    add_name(GOPHEROO_NAME);
    set_race_name("gopheroo");
    set_gender(0);
    set_short("energetic white gopheroo");
    set_adj(({"energetic", "white" }));
    set_long("An energetic white gopheroo, clearly a "
           + "domestic animal. Who could its "
           + "owner be?\n");

    /* str, con, dex, int, wis, dis
    */
    set_stats(({ 10, 10, 10, 10, 10, 10}));

    set_hp(query_max_hp());

    set_attack_unarmed(A_BITE,  10, 10, W_IMPALE, 40, "teeth");
    set_attack_unarmed(A_LCLAW, 10, 10, W_SLASH,  30, "left paw");
    set_attack_unarmed(A_RCLAW, 10, 10, W_SLASH,  30, "right paw");
   
    set_hitloc_unarmed(H_HEAD, ({ 5, 5, 5, 5 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 5, 5, 5, 5 }), 80, "body");

    seteuid(getuid());

    bolt_to = ({ 
                 GELAN_ROOMS + "square_central_e",
                 GELAN_ROOMS + "square_fountain_e", 
                 GELAN_ROOMS + "square_southend_center_e", 
                 GELAN_ROOMS + "square_sw",
                 GELAN_ROOMS + "square_fountain_nw",
                 GELAN_ROOMS + "square_corner_ne",
              });

    add_prop(OBJ_M_NO_GET, "@@get_check");
    add_prop(OBJ_M_NO_INS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    add_prop(CONT_I_WEIGHT, 3000);
    add_prop(CONT_I_VOLUME, 3000);
    add_prop(LIVE_I_NEVERKNOWN, 1); 

    set_act_time(3);
    add_act("@@twitch_nose");
    add_act("@@hop");
    add_act("@@prick_ears");  
    add_act("@@scratch");

    gopheroo_moves();
}
