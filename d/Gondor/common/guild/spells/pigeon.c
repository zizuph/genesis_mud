/*
 * /d/Gondor/common/guild/spells/pigeon.c
 *
 * The 'whistle' spells of the Rangers.
 *
 *  The Rangers' form of communicating. 
 *  By 'whistling' the player summons a pigeon. According to the 
 *  player's skill in animal handling, he can then send messages 
 *  with the pigeon a certain number of times.  
 *
 *  Summoning the pigeon will cost 5-10 manapoints.
 *
 * Coded by Elessar.
 */
#pragma strict_types

#define SP_SUMM_MANA 10
#define RANGER_PIGEON_OB   "_ranger_o_pigeon"

/*
 * Prototypes:
 */
void no_result(object player);
object query_has_pigeon();

/*
 * Global variables:
 */

int
summon_pigeon(object player)
{
  object  Pigeon;
  Pigeon = query_has_pigeon();
  if (objectp(Pigeon))
  {
    find_player("elessar")->catch_msg("PIGEON: " + TP->query_name() + "'s pigeon a valid object.\n");
    if (Pigeon->query_busy())
    {
      write("You feel that your pigeon is too busy to return right now.\n");
      return 1;
    }
    if (living(environment(Pigeon)))
    {
      if (!environment(environment(Pigeon))) 
        {
            set_alarm(10.0, 0.0, &no_result(TP));
            return 1;
        }
      if (environment(environment(Pigeon))->query_prop(ROOM_I_INSIDE))
      {
        set_alarm(10.0, 0.0, &no_result(TP));
        return 1;
      }
      if (environment(Pigeon)->query_prop(ROOM_I_INSIDE))
      {
        set_alarm(10.0, 0.0, &no_result(TP));
        return 1;
      }
    }
      Pigeon->return_to(TP);
      return 1;
  }

  seteuid(getuid(this_object()));
  Pigeon = clone_object(RANGER_DIR + "obj/pigeon");
  Pigeon->set_owner(TP);
  TP->add_prop(RANGER_PIGEON_OB, Pigeon);
  Pigeon->set_times_to_fly((TP->query_skill(SS_ANI_HANDL) / 6) + 1);
  Pigeon->start_place();
  return 1;
}

void
no_result(object player)
{
  player->catch_msg("You don't see any sign of your carrier-pigeon.\n");
}

object
query_has_pigeon()
{
    object  pigeon;
    if (!TP->query_prop(RANGER_PIGEON_OB))
        return 0;
    find_player("elessar")->catch_msg("PIGEON: " + TP->query_name() + " has a pigeon.\n");
    return TP->query_prop(RANGER_PIGEON_OB);
}


mixed
do_whistle_spell(string what)
{
  int fail, is_wiz, success;
  object tp, env, p_obj;
  if (what && what != "for pigeon")
    return 0;
  
  tp = this_player();
  env = environment(tp);
  
  if (query_has_pigeon())
    if (present(query_has_pigeon(), tp))
      return "You have already got a pigeon.\n";
  if (env->query_prop(ROOM_I_INSIDE))
    return "You cannot summon a pigeon when inside a room.\n";
  if (fail = check_player(tp, 0, SP_SUMM_MANA))  
    return fail;
  
  if (!is_wiz &&
      (success = tp->resolve_task(TASK_SIMPLE,
      ({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, SKILL_WEIGHT, 80,
	 SS_ANI_HANDL, SS_FORM_CONJURATION, SS_ELEMENT_LIFE }))) <= 0)
    {
      tp->catch_msg("You fail to cast the spell properly.\n");
      tell_room(env,QCTNAME(tp)+" fails to cast a spell properly.\n",tp);
      return 1;
    }
  tell_room(env,QCTNAME(tp)+" whistles a sharp, shrill sound.\n",tp);
  tp->catch_msg("You whistle a sharp, shrill sound to summon your carrier pigeon.\n");
  summon_pigeon(tp);
  if (!is_wiz)
    tp->add_mana(-SP_SUMM_MANA);
  return 1;
}
