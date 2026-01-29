
#define SP_PEACE_INGR	({ "_stop_spell_mushroom_" })
#define SP_PEACE_MANA	40
#define SP_PEACE_MIN	50
#define SP_PEACE_TASK	TASK_ROUTINE
#define SP_PEACE_LIST	({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
		SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END, \
		SS_FORM_CONJURATION, SS_ELEMENT_EARTH })




/*
 * Function name:   do_peace_spell
 * Decription:	    Cast the peace fighting spell.
 * Returns:	    1 if spell was cast, 0 or the errorstring otherwise.
 */
mixed
do_peace_spell()
{
    object env, obj, *ingr_arr;
    int success, is_wiz;
    string fail;

    is_wiz = this_player()->query_wiz_level();
    env = environment(this_player());

    if (present("_orome_peace_", environment(this_player())))
	return "It is unnecessary to call for peace here.\n";

    if (fail = check_player(this_player(), SP_PEACE_INGR, SP_PEACE_MANA, SP_PEACE_MIN))
	return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_PEACE_INGR, this_player());

    /* Let's see how successful she is */
    if (!is_wiz &&
        (success = this_player()->resolve_task(SP_PEACE_TASK,SP_PEACE_LIST)) <= 0)
    {
	fail_cast(this_player(),ingr_arr);
	return 1;
    }

    tell_room(env, QCTNAME(this_player()) + " calls upon Orome to make peace "
	    + "here.\n", this_player());
    this_player()->catch_msg("You call upon Orome to stop the fighting.\n");

    if (env->query_prop(ROOM_I_INSIDE))
    {
       tell_room(env, break_string(
          "Outside you hear a deep rumble. "
        + "Suddenly a bolt of lightning cuts through the ceiling and impacts "
        + "on the floor!\n",70));
    }
    else
    {
       tell_room(env, break_string(
          "Clouds gather above you and form a dense, gray blanket. "
        + "Suddenly a bolt of lightning springs from the clouds and impacts "
        + "on the ground!\n",70));
    }

    /* Finally start casting the spell */
    seteuid(getuid());
    obj = clone_object(HERALD_DIR + "stop_obj");
    obj->move(env);

    if (success < 15)
	success = 15;
    else if (success > 300)
	success = 350;

    if (is_wiz)
        success = 200;
    
    obj->make_peace(2*success);
    
    /* Make her pay for it and remove the ingredients */
    if (!is_wiz)
    {
	this_player()->add_mana(-SP_PEACE_MANA);
	remove_ingr(ingr_arr);
    }

    tell_room(env, QCTNAME(this_player()) + " has a prayer answered.\n", this_player());
    this_player()->catch_msg("Orome answers your prayer.\n");

    return 1;
}

