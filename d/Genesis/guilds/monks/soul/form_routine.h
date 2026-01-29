/*   forms / kata
 */
#define FORM_INDEX   "_A_O_D_form_index_"
#define FORM_ALARM   "_A_O_D_form_alarm_"

#define SAY(str, who)  tell_room(environment(who),(QCTNAME(who)+ str), ({who}))

/* linkdeath cleanup */
private int
ld_clean(object tp) 
{
    if (interactive(tp))
        return 0;

    remove_alarm(tp->query_prop(FORM_ALARM));
    tp->remove_prop(FORM_ALARM);
    tp->remove_prop(FORM_INDEX);
    return 1;
}


private void
posture(object tp)
{
    if (ld_clean (tp))
        return;

    tell_object(tp, 
        "You take take a deep breath, and as you exhale "+
        "you assume the relaxed stance which your teachers drilled "+
        "into you: feet spread shoulder-width apart, elbows bent, "+
        "hands relaxed and forward of your hips.\n");

     SAY(" breathes deeply and assumes a relaxed stance.\n", tp);
}

private void
begin(object tp)
{
    if (ld_clean (tp))
        return;

    tell_object(tp,
        "You begin to practice the physical forms of dragon-"+ 
        "discipline, seeking the mind-body unity integral to "+
        "effective use of your combat moves.\n");

    SAY(" springs into fluid motion.\n", tp);
}

private void
form_one(object tp)
{
    if (ld_clean (tp))
        return;

    if (m_query_monk(tp, SS_LAYMAN))
    {
        tell_object(tp, "You do not have "+
            "sufficient knowledge of the dragon-discipline to "+
            "proceed any farther with your forms.\n");
        tp->command("$mstop");
        return;
    }

    tell_object(tp,
        "Your mind wills your body to take the first of "+
        "the dragon forms, Poised for Flight.\n"+
        "Your arms seem to float upwards until they are out-"+
        "stretched. You feel the membranes of your wings unfold.\n");

    SAY(" raises "+ HIS(tp) +" arms as though unfolding "+ 
        HIS(tp)+" wings.\n", tp);
}

private void
form_two(object tp)
{
    if (ld_clean (tp))
        return;

    tell_object(tp,
        "You swiftly flow into Dragon Launch, springing into "+
        "the air, pulling your arms in against your body and "+
        "then thrusting them forward and up, your taloned fingers "+
        "seeming to hold your arched body suspended above the "+ 
        "ground.\n");
    SAY(" launches into the air, defying gravity with "+
        "fantastic ease.\n", tp);
}

private void
form_three(object tp)
{
    if (ld_clean (tp))
        return;

    tell_object(tp,
        "You are a dragon in flight, engaging its enemy in the "+
        "air, claws slashing and jaws striking, before wheeling "+
        "away, a cry of challenge trumpeting from your throat.\n");

    SAY(" whirls like a winged fury, hands and feet hammering "+
        "the air.\n", tp);

    tp->command("$kiai");
}

private void
form_four(object tp)
{
    if (ld_clean (tp))
        return;

    tell_object(tp,
        "You land lightly on the balls of your feet and shift "+
        "to the Dragon Strike stance.\n");
    SAY(" lands in a crouch, then assumes a deceptively "+
        "relaxed stance.\n", tp);
}

private void
form_five(object tp)
{
    if (ld_clean (tp))
        return;

    tell_object(tp,
        "You lunge forward, the muscles in your extended arms rippling "+
        "with effort as your talon-like fingers puncture the enemy's "+
        "armoured breast to rip out its heart.\n");

    SAY(" lunges forward, the muscles in "+ HIS(tp) +" extended "+
        "arms rippling as "+ HE(tp) +" makes a quick, jabbing motion "+
        "with a taloned fist.\n", tp);
}     

private void
form_six(object tp)
{
    tell_object(tp,
        "Your blood sings a dragon-song in your ears as you "+
        "effortlessly tumble in the air, flipping backwards to "+
        "land, cat-like, on your feet.\n");
    
    SAY(" tumbles backwards in the air and lands, cat-like, "+
        "on "+ HIS(tp) +" feet.\n", tp);
}

private void
form_end(object tp)
{
    if (ld_clean (tp))
        return;

    tell_object(tp,
        "You drop your arms to your sides and perform a small bow, "+
        "holding it for a few seconds before standing fully erect.\n");
    SAY(" drops "+ HIS(tp) +" arms to "+ HIS(tp) +" sides and "+
         "performs a small bow.\n", tp);
  
    remove_alarm(tp->query_prop(FORM_ALARM));
    tp->remove_prop(FORM_ALARM);
    tp->remove_prop(FORM_INDEX);
}

private function* forms = ({ posture, begin, form_one, form_two,
       form_three, form_four, form_five, form_six, form_end });

private void
start_form(object tp)
{
    int index = tp->query_prop(FORM_INDEX);
  
    tp->add_prop(FORM_INDEX, index+1);
    applyv(forms[index], ({tp}));
}

int
aod_form(string str)
{
    object tpl;

    if (strlen(str))
    {
        notify_fail("The form "+ str +" cannot be done.\n");
        return 0;
    }

    if (this_player()->query_prop(FORM_ALARM)) 
    {
        write("You are already practicing your forms!\n");
        return 1;
    }

    tpl = this_player();
    this_player()->remove_prop(FORM_INDEX);
    this_player()->add_prop(FORM_ALARM, set_alarm(3.0, 6.0, 
        &start_form(tpl) ) );
    return 1;
}

/*
 *      stop_forms 
 */
int
aod_stop_form(string str)
{
    int alarm_id;

    if (strlen(str))
    {
        notify_fail("The form "+ str +" can't be done.\n");
        return 0;
    }

    if (!(alarm_id = this_player()->query_prop(FORM_ALARM))) 
    {
        write("Thou art not practicing thine forms.\n");
        return 1;
    }

    remove_alarm(alarm_id);
    this_player()->remove_prop(FORM_ALARM);
    this_player()->remove_prop(FORM_INDEX);

    write("You stop practicing the physical forms of your dragon-"+
        "discipline.\n");
    allbb(" stops practicing "+ HIS(this_player()) +" combat movements.");
    return 1;
}



