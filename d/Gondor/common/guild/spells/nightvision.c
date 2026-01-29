/* 
 * This is a very simple spell that adds a little to the players ability to
 * see in the dark. The duration varies with the success of the casting,
 * and with the players wisdom. The skill in spellcraft is counted in.
 *
 * Elessar. May 1994.
 *
 * Modification log:
 * 01-Oct-1997, Olorin: Revision of do_nightvision_spell:
 *                      Proper indentation, error code printed to player
 *                      if shadow_me fails,
 *                      modified skill list for resolve_task so it adds 
 *                      up to a SKILL WEIGHT of 200 (was 280 before),
 *                      replaced SS_FORM_ENCHANTMENT by SS_FORM_CONJURATION
 *                      (in agreement with the old documentation!),
 *                      increased max duration to about 6 minutes.
 */
#define SP_NIGHTV_INGR  ({ "_nightv_spell_ingr_" })
#define NV_MANA_LIMIT      30 /* How much mana does it cost to cast this spell? */
#define NV_CAST_LIMIT      15 /* How wise and skilled must the caster be? */
#define SPELL_DIR	"/d/Gondor/common/guild/spells/" /* Where is our spell dir? */
#define RANGER_NIGHTVISION  "ranger_with_nightvision"
#define RANGER_DARKVISION   "ranger_with_darkvision"

object shadow;

void nightvision_end(object pl);

/* Function name: nightvision
 * Description:   Will give the player 1 factor better ability to see in
 *                darkness. It costs equal mana on success or failure,
 *                but might also give even worse ability on failure.
 * Arguments:     none at low levels, higher levels or Gondorian Rangers
 *                may give second person as argument.
 * Returns:       1/0
 */
nomask mixed
do_nightvision_spell(string str)
{
    object  tp = TP,
            room = ENV(tp),
           *ingr_arr;
    int     dur,
            power, 
            esf_roll, 
            no_ingr = 0,
            success,
            is_wiz,
            fighting;

     /* Checks if prop ROOM_I_NO_MAGIC is set. */
    if (RNMAGIC(room)) 
        return "Some strange power in this place prevents you from casting the spell.\n";

    ingr_arr = find_ingr(SP_NIGHTV_INGR, tp);
    if (!sizeof(ingr_arr)) 
        no_ingr = 1;
    if (tp->query_wiz_level()) 
        is_wiz = 1;
    if (objectp(tp->query_attack()))
        fighting = 1;
    if (tp->query_mana() < NV_MANA_LIMIT)
        return "You feel too weak to cast this spell.\n";

    power = tp->query_skill(SS_FORM_CONJURATION) + tp->query_skill(SS_ELEMENT_LIFE);
    if ((power - NV_CAST_LIMIT) < 0)
        return "You are too unskilled to cast this spell.\n";
    if (tp->query_prop(RANGER_NIGHTVISION)) 
	return "You cannot have more than one nightvision active.\n";
    if (tp->query_prop(RANGER_DARKVISION))
	return "You cannot have both darkvision and nightvision at the same time.\n";
    if (present("Ranger_Blind_Object", tp))
    {
        log_file("nightvision", tp->query_name() + " tried to cast nightvision "
          + "while blinded by brawl, " + ctime(time()) + ".\n");
/*
        no_ingr = 3;
        fighting = 5;
*/
    }
    esf_roll = random(NV_MANA_LIMIT/3 * (1 + no_ingr + fighting));
    if (esf_roll > power)
    {
	esf(esf_roll - power, NV_MANA_LIMIT);
	return 1;
    }
    success = tp->resolve_task(TASK_ROUTINE,
        ({ SKILL_WEIGHT, 200, SKILL_AVG, 
               SS_SPELLCRAFT, SS_FORM_CONJURATION, SS_ELEMENT_LIFE, 
                              SKILL_END }) );

    // Failure? Only mortal can fail!
    if (!is_wiz && (success <= 0))
    {
        tp->catch_msg("You try to chant the prayer to Elbereth, but "
          + "your voice fails.\n");
	tell_room(ENV(tp), QCTNAME(tp) + " fails to cast a spell correctly.\n", tp);
	lose_random_ingr(ingr_arr);
	return 1;
    }
    write("You concentrate for a while, praying for Elbereth to bless you "+
        "with better vision at night.\n");
    say(QCTNAME(tp) + " gestures a little, while mumbling something.\n", tp);

    str = lower_case(str);

    power += tp->query_skill(SS_SPELLCRAFT);

    // Max for Gondor company:
    //    60 + (     100               / 5) + (60 + 50 + 50) / 2 + 52) * 2
    //  = 60 + (   20 + 80 + 52 ) * 2 = 364 secs = 6 minutes max
    dur = 60 + (tp->query_stat(SS_WIS) / 5 + power / 2 + success) * 2;

    if (!strlen(str) || (str == "myself") || (str == "me") ||
	(str == tp->query_race_name()) || (str == tp->query_real_name()))
    {
        tp->add_prop(RANGER_NIGHTVISION,1);
        seteuid(getuid(TO));
        shadow = clone_object(SPELL_DIR+"nightv_shadow");
        shadow->set_strength(MIN(5, power / 15));
        if ((success = shadow->shadow_me(tp)) != 1) 
        {
            shadow->remove_shadow();
            write("The spell did not work, because of a bug.\n" +
                "Send a mail to the guildmaster reporting this, please.\n" +
                "Error code = " + success + ".\n");
            tp->remove_prop(RANGER_NIGHTVISION,1);
            return 1; 
        }
        if (no_ingr) 
            tp->add_mana(-NV_MANA_LIMIT);
        else 
            tp->add_mana(-(NV_MANA_LIMIT/2));
        set_alarm(itof(dur), 0.0, &nightvision_end(tp));
        remove_ingr(ingr_arr);
        write("Your eyes feel strange and perceptive.\n");
        say(QCTNAME(tp)+ " exclaims 'Elbereth!', and "
            +tp->query_possessive()+
            " eyes start glowing faintly green.\n", tp);
        return 1;
    }
    write("You feel that you are unable to cast Nightvision on\n"+
        "anyone else but yourself.\n");
    return 1;
}

/* Function name:
 * Description:
 * Arguments:
 * Returns:
 */
void
nightvision_end(object pl)
{
   if (!objectp(pl))
   {
     pl = ENV(TO);
     if (!objectp(pl))
       find_player("elessar")->catch_msg("Nightvision bug: Player gone!\n");
   }
   if (!objectp(shadow))
     find_player("elessar")->catch_msg("Nightvision bug: Shadow gone from " + pl->query_name() + "!\n");
   shadow->remove_shadow();
   pl->remove_nightv_shadow();
   pl->remove_prop(RANGER_NIGHTVISION);
   pl->catch_msg("Your nightvision slowly fades away.\n");
   say(QCTNAME(pl)+"'s eyes slowly stop glowing.\n",pl);
}
