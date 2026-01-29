public void
reset_euid()
{
   setuid();
   seteuid(getuid());
}

/*
 * Function name: wail
 * Description  : One of the banshee's special attacks. This one causes players to
 *                panic, freeze in fear, or go insane, if effected at all.
 * Arguments    : N/A (attack hits all players in the room)
 * Returns      : N/A
 */
public void
wail()
{
    object *targets,
           *high_dis,
           *med_dis,
           *low_dis,
           *insane,
           *temp,
           victim,
           old_tp;
    int i;

  /* Get a list of viable targets in the room. That is, all livings */
  /* except wizards. */
    targets = all_inventory(environment(TO)) - ({TO});
    targets = filter(targets, living);
    targets = filter(targets, &not() @ &->query_wiz_level());

    tell_room(environment(TO), QCTNAME(TO) + " rears back her head and unleases " +
        "an unholy wail that seems to slice through your very soul!\n");

    high_dis = filter(targets, &operator(<)(HIGH_DIS) @ &->query_stat(SS_DIS));
    temp = targets - high_dis;
    med_dis = filter(temp, &operator(<)(MED_DIS) @ &->query_stat(SS_DIS));
    temp = temp - med_dis;
    low_dis = filter(temp, &operator(<)(LOW_DIS) @ &->query_stat(SS_DIS));
    insane = temp - low_dis;

#ifdef UNDEAD_DEBUG
    old_tp = this_player();
    set_this_player(find_player("khail"));
    write("high dis:");
    dump_array(high_dis);
    write("\nmed_dis:");
    dump_array(med_dis);
    write("\nlow_dis:");
    dump_array(low_dis);
    write("\ninsane:");
    dump_array(insane);
    set_this_player(old_tp);
#endif

    for (i = 0; i < sizeof(high_dis); i++)
    {
        high_dis[i]->catch_tell("The wail sends a shiver down your spine, but you "+
            "grit your teeth and stand strong against it!\n");
        tell_room(environment(TO), QCTNAME(high_dis[i]) + " shivers violently " +
            "at the sound of the banshee's wail, but seems otherwise unaffected.\n",
            ({TO, high_dis[i]}));
    }

    for (i = 0; i < sizeof(med_dis); i++)
    {
        med_dis[i]->catch_tell("The wail of the banshee cuts through you like " +
            "a knife, and you feel a tendril of fear entwine it's way into " +
            "your mind!\n");
        tell_room(environment(TO), QCTNAME(med_dis[i]) + " takes a step " +
            "backwards, and you see the blood drain from " + HIS_HER(med_dis[i]) +
            "face as " + HE_SHE(med_dis[i]) + " stairs in horror at the " +
            "banshee!\n", ({TO, med_dis[i]}));
        med_dis[i]->add_panic(100);
    }

    for (i = 0; i < sizeof(low_dis); i++)
    {
        low_dis[i]->catch_tell("The wail of the banshee seems to slice through " +
            "your very being, clutching your heart and mind in an icy sheathe " +
            "of pure terror, paralyzing you!\n");
        tell_room(environment(TO), QCTNAME(low_dis[i]) + " stares in wide-eyed " +
            "terror at the wailing banshee, and freezes in stark terror at " +
            "the soul-numbing sound!\n",({TO, low_dis[i]}));
        reset_euid();        
        clone_object(PARALYSIS)->move(low_dis[i],1);
    }

    for (i = 0; i < sizeof(insane); i++)
    {
        insane[i]->catch_tell("The wail of the banshee is too much for " +
            "you to stand, you feel your mind reel and collapse beneath " +
            "the hellish sound!\n");
        tell_room(environment(TO), QCTNAME(insane[i]) + " gets a blank " +
            "look on " + HIS_HER(insane[i]) + " face, and turns a deadly " +
            "shade of white!\n", ({TO, insane[i]}));

        if (present(PARALYZE_NAME, insane[i]))
            return;

        if (insane[i]->query_prop(INSANE_COUNT) <= INSANE_LIMIT)
        {
            temp = targets - ({TO, insane[i]});        
            insane[i]->command("$cackle insanely");
            if (sizeof(temp))
            {
                victim = temp[random(sizeof(temp))];
                insane[i]->set_stat_extra(SS_DIS, 
                    insane[i]->query_stat_extra(SS_DIS) + 100);
                insane[i]->command("$kill " + OB_NAME(victim));
                insane[i]->set_stat_extra(SS_DIS,
                    insane[i]->query_stat_extra(SS_DIS) - 100);
            }
            reset_euid();
            clone_object(PARALYSIS)->move(insane[i],1);
            insane[i]->add_prop(INSANE_COUNT,insane[i]->query_prop(INSANE_COUNT)+1);
        }
        else
        {
            insane[i]->catch_tell("Insanity overcomes your existance, you can "+
                "bear no more! Death is the only release!\n");
            insane[i]->command("$unwield all");
            insane[i]->catch_tell("With your own bare hands, you tear out  " +
                "your own throat in a successful attempt to end the agony!\n");
            tell_room(environment(TO), "To your shock, " + QTNAME(insane[i]) +
                " reaches up with " + HIS_HER(insane[i]) + " bare hands and " +
                "tears out " + HIS_HER(insane[i]) + " own throat!\n",
                ({TO, insane[i]}));
            insane[i]->heal_hp(-100000);
            insane[i]->do_die(insane[i]);
        }
    }
}
