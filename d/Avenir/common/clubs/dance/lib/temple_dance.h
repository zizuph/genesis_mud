// -*-C++-*-
// file name: 	  temple_dance.h		
// creator(s):	  Gracie, Nov 21 1995
// update:	  Elwing, Jan 17 1996
// history:       Boriska, November 1995
// purpose:       Place to put dance-sequence
//                separate from the rest
// note:          Elwing of Shire added the link-death check!

/*
 *	ddance  
 *      It looks like Elwing helped solve the Link-Death and the 
 *      what-happens-when-player-quits-in-the-middle-of-a-dance problems
 *      
 */

#define ALLBBX(str) tell_room( environment(tp),(QCTNAME(tp)+ str), ({tp}) )

#define TEST_LINK_DEATH if( !(living(tp) && interactive(tp)) ) \
		{ ld_clean(tp); return; }

private void
ld_clean(object tp) // linkdeath cleanup
{
 if( !living(tp) ) return;

 remove_alarm(tp->query_prop(DANCE_ALARM));
 tp->remove_prop(DANCE_ALARM);
 tp->remove_prop(DANCE_INDEX);
}

// Got to think about implementing with &func table -- Boriska

private void
posture(object tp)
{
  TEST_LINK_DEATH

  tell_object(tp, 
	"You take the posture taught you by the apprentice dancers:\n"+
        "Your head bent graciously with the chin tilted; the arms "+
        "curved and bent, reminiscent of entwining tendrils; the "+
        "left leg bent at the knee and the right hip swivelled "+
        "slightly out.\n");
  ALLBBX(" assumes a graceful posture with her neck arched and her "+
        "arms curved like entwining tendrils.\n");
}

private void
dance_one(object tp)
{
  TEST_LINK_DEATH

  tell_object(tp,
	"You begin moving your feet in intricate, patterned steps.\n"+
        "Your little ankle bells jingle in cadence with your steps.\n");
  ALLBBX(" begins moving her feet in intricate, patterned steps.\n"+
      "Her little ankle bells jingle in cadence with every step.\n");       
}

private void
dance_two(object tp)
{
    TEST_LINK_DEATH

    tell_object(tp,
	"Like a serenade, your body moves in a gentle, rhythm"+
        "ic ecstacy which joins the sweet harmony of the bells.\n");
    ALLBBX("'s body, like a serenade, joins the sweet harmony of "+
        "the bells in gentle, rhythmic movements.\n");
}

private void
dance_three(object tp)
{
    TEST_LINK_DEATH

    tell_object(tp,
	"You match the intricate footwork with swiftly flowing "+
        "gestures of arms and hands, transforming yourself into "+
        "the ideal of feminine charm, coquetry, and grace.\n");
    ALLBBX(" matches the intricacy of her footwork with swiftly "+
        "flowing gestures of arms and hands.\nShe seems trans"+
        "formed into the ideal of feminine charm, coquetry, "+
        "and grace.\n");
}

private void
dance_four(object tp)
{
  TEST_LINK_DEATH

  tell_object(tp,
	      "You raise your voice in wordless song, increasing "+
	      "the tempo of the dance with confident virtuosity.\n");
  ALLBBX(" raises her voice in wordless song and increases the "+
      "tempo of the dance with confident virtuosity.\n");
}

private void
dance_five(object tp)
{
  TEST_LINK_DEATH

  tell_object(tp,
	      "The music of the bells and the sound of your voice "+
	      "are haunting accompaniment to your dance.\nYou feel as "+
	      "if you are floating through space with the same effort"+
	      "less ease as the winged denizens of the air.\n");
  ALLBBX(" seems to dance effortlessly, the music of the bells "+
      "and the sound of her voice a haunting and alluring "+
      "accompaniment.\n");
}

private void
dance_six(object tp)
{
  TEST_LINK_DEATH

  tell_object(tp,
	      "You leap into the air and perform a pirouette where "+
	      "you land.\nWith slow, measured grace, you bend toward "+
	      "the ground, your fingers pantomiming the picking of a "+
	      "flower.\nThen you rise swiftly, your body arched and "+
	      "your arms raised skyward with your fingers in a gesture "+
	      "of holding the most fragile of blossoms.\n");
  ALLBBX(" leaps into the air and performs a pirouette where "+
        "she lands. With slow, measured grace, she bends toward "+
        "the ground, her fingers pantomining the picking of a "+
        "flower.\nShe rises swiftly, her body arched and her arms "+
        "raised skyward, with her fingers shaped as if holding "+
        "the most fragile of blossoms.\n");
//  SOULDESC("dancing beautifully");
}     

private void
dance_end(object tp)
{
  TEST_LINK_DEATH

  tell_object(tp,
	      "You hold that position for several seconds, then "+
	      "relax into a normal stance and curtsey.\n");
  ALLBBX(" remains frozen in that position for several seconds, "+
	"then relaxes to a normal stance and curtseys gracefully.\n");
  
  remove_alarm(tp->query_prop(DANCE_ALARM));
  tp->remove_prop(DANCE_ALARM);
  tp->remove_prop(DANCE_INDEX);
}

private function* dance = ({ posture, dance_one, dance_two, dance_three,
			     dance_four, dance_five, dance_six, dance_end });

private void
do_dance(object tp)
{
  int index = tp->query_prop(DANCE_INDEX);
  
  tp->add_prop(DANCE_INDEX, index+1);
  applyv(dance[index], ({tp}));
}


int
ddance(string str)
{
    object tpl;

    if (strlen(str))
    {
        NF("Ddance "+ str+" can't be done.\n");
        return 0;
    }

    if (TP->query_prop(DANCE_ALARM)) {
      write("You are already dancing!\n");
      return 1;
    }

    command("unwield all");
    tpl = TP ;
    TP->remove_prop(DANCE_INDEX);
    TP->add_prop(DANCE_ALARM, set_alarm(3.0, 10.0, &do_dance(tpl) ) );
    return 1;
}

/*
 *   	dstop  -- part of ddance, so I moved it up here.
 *      It is also commented out until the problems are solved.
 */

int
dstop(string str)
{
  int alarm_id;

  if (strlen(str))
    {
      NF("Dstop "+ str+" can't be done.\n");
      return 0;
    }

  if (!(alarm_id = TP->query_prop(DANCE_ALARM)) ) {
    write("You are not dancing!\n");
    return 1;
  }

  remove_alarm(alarm_id);
  TP->remove_prop(DANCE_ALARM);
  TP->remove_prop(DANCE_INDEX);

  write("You stop dancing.\n");
  allbb(" stops dancing.");
  return 1;
}
