// Herald guild list, borrowed from the Rangers



#define SP_PALANDIR_INGR	({ })
#define SP_PALANDIR_MANA	1
#define SP_PALANDIR_MIN	0
#define SP_PALANDIR_TASK	TASK_SIMPLE
#define SP_PALANDIR_LIST	({ SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
		SKILL_WEIGHT, 90, SKILL_AVG, SS_WIS, SS_INT, SKILL_END, \
		SS_FORM_DIVINATION, SS_ELEMENT_LIFE })



int
list_active_heralds()
{
   string g_name, g_short;
   int i;
   object robe;
   object *list;
   write("These are the Heralds that occupy the realms:\n");
   list = users();
   for (i = 0; i < sizeof(list); i++)
   {
      g_name = capitalize(list[i]->query_real_name());
      if (IS_MEMBER(list[i]))
         {
         /* Don't want a jr's name on the guildlist */
         if ((extract(g_name, -2) == "jr") && (!(TP->query_wiz_level())))
            continue;
         if(!list[i]->query_invis())
            {
            if (list[i]->query_wiz_level())
            {
              g_short = list[i]->query_title();
              write("O " + g_name + " " + g_short);
            }
            else
            {
              g_short = list[i]->query_title();
              write("o " + g_name + " " + g_short);
              }
          }
         if (list[i]->query_invis() && TP->query_wiz_level())
            {
            write("I (" + g_name + ")");
          }
         if ((robe = present("_herald_robe_", list[i])) &&
               (list[i]->short())) 
         {
            if (list[i]->query_ghost())
               write(" <deceased>");
          }
         else {
            if (list[i]->short())
               write(" <no robe>");
          }
         if (!list[i]->query_invis() || TP->query_wiz_level())
            write("\n");
        }
   }
   write("---------------------------------------------------------------\n");
   return 1;
}


/*
 * Function name:   do_palandir_spell
 * Description:	    Cast the palandir spell
 *
 * Returns:	    1 if spell was cast, 0 or the errorstring otherwise.
 */
mixed
do_palandir_spell()
{
    int is_wiz, success;
    object *ingr_arr;
    string fail;

    is_wiz = this_player()->query_wiz_level();

    /* Check the player for ingredients and mana */
    if (fail = check_player(this_player(), SP_PALANDIR_INGR, SP_PALANDIR_MANA, SP_PALANDIR_MIN))
        return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_PALANDIR_INGR, this_player());

    /* Let's see how successful she is */
    if (!is_wiz &&
        (success = this_player()->resolve_task(SP_PALANDIR_TASK, SP_PALANDIR_LIST)) <= 0)
    {
	fail_cast(this_player(),ingr_arr);
        return 1;
    }

    this_player()->catch_msg("You concentrate on the palantir in the Elven "+
    "Tower Elostirion.\n");
    set_alarm(2.7,0.0,"list_active_heralds");

    tell_room(environment(this_player()), QCTNAME(this_player()) + " turns to face the West for a moment, "
     + "then turns back.\n",this_player());


    /* Remove the ingredients and make her pay for it */
    if (!is_wiz)
    {
   	remove_ingr(ingr_arr);
   	this_player()->add_mana(-SP_PALANDIR_MANA);
    }
    return 1;
}

