
#define SP_RAMAR_INGR	({ })
#define SP_RAMAR_MANA	20
#define SP_RAMAR_MIN	0
#define SP_RAMAR_TASK	TASK_ROUTINE
#define SP_RAMAR_LIST	({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
		SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END, \
		SS_FORM_CONJURATION, SS_ELEMENT_LIFE })


/*
 * Function name:   do_ramar_spell
 * Description:	    Cast the Ramar spell (Wings)
 * Arguments:       None
 * Returns:	    1 if spell was cast, 0 or the errorstring otherwise.
 */
mixed
do_ramar_spell(string str)
{
    int is_wiz, success;
    object eagle, player, *ingr_arr;
    string fail;

     player = this_player();
    if(environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
     notify_fail("You may only summon a messenger when outdoors.\n");
     return 1;
    }

    is_wiz = this_player()->query_wiz_level();

    /* Check the player for ingredients and mana */
    if (fail = check_player(this_player(), SP_RAMAR_INGR, SP_RAMAR_MANA, SP_RAMAR_MIN))
        return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_RAMAR_INGR, this_player());

    /* Let's see how successful she is */
    if (!is_wiz &&
        (success = this_player()->resolve_task(SP_RAMAR_TASK, SP_RAMAR_LIST)) <= 0)
    {
	fail_cast(this_player(),ingr_arr);
        return 1;
    }

   if(present("eagle",environment(this_object())))
   {
    write("You already have a messenger.\n");
    return 1;
    }

    set_alarm(15.0,0.0,"get_eagle",player);
    /* Remove the ingredients and make her pay for it */
    if (!is_wiz)
    {
    	remove_ingr(ingr_arr);
    	this_player()->add_mana(-SP_RAMAR_MANA);
    }

    return 1;

}

void
get_eagle(object player)
{
   object eagle;

    this_player()->catch_msg("You close your eyes and call upon Manwe for a messenger.\n"
	+ "You hear a shrill cry from on high, and your messenger lands on your shoulder.\n");
    tell_room(environment(this_player()), QCTNAME(this_player()) + " closes " + this_player()->query_possessive() + " eyes in prayer.\n "
     + "You hear a shrill cry from right above you as an "
     + "eagle swoops down from the sky.\n", this_player());
    seteuid(getuid());
    eagle = clone_object(HERALD_DIR + "eagle");
    eagle->move(this_player(),1);
    return;
}

