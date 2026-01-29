// -*-C++-*-
// file name: 	  mime.h		
// creator(s):	  Lilith, Oct-Nov 1996
// update:	  Jan 1997
// history:       
// purpose:       Place to put mime-sequences separate from the 
//                other emotes.
//                Taken from the Dancer's temple_dance.h
// note:          Thanks to Elwing of Shire's help on link-death
//                check.
// bug(s):
// to-do: 

#include <macros.h>
#include <stdproperties.h>
#include <language.h>

#define ALLBBX(str)      tell_room( environment(tp),(QCTNAME(tp)+ str), ({tp}) )
/*
#define TEST_LINK_DEATH  if (!(living(tp) && tp->query_linkdead()) ) \
           		     { ld_clean(tp); return; }
*/

#define TEST_LINK_DEATH if( !(living(tp) && interactive(tp)) ) \
		{ ld_clean(tp); return; }

private void
ld_clean(object tp) // linkdeath cleanup
{
    if (!living(tp)) return;

    remove_alarm(tp->query_prop(MIME_ALARM));
    tp->remove_prop(MIME_ALARM);

    /* Remove speech block if we added one */
    if (tp->query_prop(LIVE_M_MOUTH_BLOCKED))
        tp->remove_prop(LIVE_M_MOUTH_BLOCKED);
}

/*
 *  mfire_eat and its steps
 */

private void
eat_end(object tp, string s)
{
    object *fire;

    TEST_LINK_DEATH

    fire = FIND_STR_IN_OBJECT(s, TP);
    fire = filter(fire, "torch_check", this_object());

    if (!sizeof(fire))
    {
        write("You cannot continue the performance without a "+
            "lighted torch!\n");
        tp->command("$mumstop");
        if (tp->query_wiz_level())
            write("You will need to use <mumstop> to end this performance.\n");
        return;
    }
        
    tell_object(tp,
        "Exhaling forcefully, you send forth a short stream of fire.\n");
    ALLBBX(" exhales forcefully, sending forth a short stream of fire!\n");
    ADD_A_LEVEL(this_player());

    fire[0]->do_extinguish(s); 

    if (tp->query_prop(LIVE_M_MOUTH_BLOCKED, MIME_MESSAGE))
        tp->remove_prop(LIVE_M_MOUTH_BLOCKED);
    tp->remove_prop(EAT_INDEX);
    remove_alarm(tp->query_prop(MIME_ALARM));
    tp->remove_prop(MIME_ALARM);
}

private void
eat_one(object tp, string s)
{
    object *fire;

    TEST_LINK_DEATH
 
    fire = FIND_STR_IN_OBJECT(s, TP);
    fire = filter(fire, "torch_check", this_object());

    if (!sizeof(fire))
    {
        write("You cannot continue the performance without a "+
            "lighted torch!\n");
        tp->command("$mumstop");
        if (tp->query_wiz_level())
            write("You will need to use <mumstop> to end this performance.\n");
        return;
    }

    tell_object(tp, 
        "Tossing your head well back and holding your mouth "+
        "wide open, you insert the "+ fire[0]->short() +" between "+
        "your teeth.\n");
    ALLBBX(" tosses "+ POSSESS(TP) +" head well back and opens "+
        POSSESS(TP) +" mouth wide, inserting the "+
        fire[0]->short() +" between "+ POSSESS(TP) +" teeth!\n");
}

private function* eat = ({ eat_one, eat_end });

private void
do_eat(object tp, string s)
{
    int index = tp->query_prop(EAT_INDEX);
  
    tp->add_prop(EAT_INDEX, index+1);
    applyv(eat[index], ({tp, s}));
}

int mfire_eat(string str)
{
    object *fire;
    object tpl;
    string s;

    if (TP->query_prop(MIME_ALARM))
    {
        notify_fail("You are already performing something!\n");
        return 0;
    }
    if (!strlen(str))
    {
        notify_fail("What do you want to fire eat?\n");
        return 0;
    }
    fire = FIND_STR_IN_OBJECT(str, TP);
    if (sizeof(fire) == 0)
        fire = FIND_STR_IN_OBJECT(str, environment(TP));

    if (!sizeof(fire))
    {
	notify_fail("Can't locate "+ str +". Sorry.\n");
	return 0;
    }
    fire = filter(fire, "torch_check", this_object());
    if (!sizeof(fire))
    {
        notify_fail("But it is not lighted!\n");
        return 0;
    }
    if (sizeof(fire) > 1)
    {
        notify_fail("You can only fire-eat one thing at a time.\n");
        return 0;
    }
    if (objectp(TP->query_attack()))
    {
        notify_fail("It is not wise to eat fire during combat. "+
            "You could injure yourself.\n");
        return 0;
    }

    write("You take a deep, calming breath, and hold it.\n");
    say(QCTNAME(TP) +" takes a deep breath and holds it.\n");       

    tpl = TP ;
    s = str;
    TP->remove_prop(EAT_INDEX);
    if (!TP->query_prop(LIVE_M_MOUTH_BLOCKED))
        TP->add_prop(LIVE_M_MOUTH_BLOCKED, MIME_MESSAGE);
    TP->add_prop(MIME_ALARM, set_alarm(3.0, 5.0, &do_eat(tpl, s) ) );
    return 1;

}

/* 
 *   Levitate 
 */
private void
levi_one(object tp, object who)
{
    TEST_LINK_DEATH
 
    if (!who)
    {
        write("It seems that whatever it was that you were going to "+
            "levitate is no longer here!\n");
        tp->command("$mumstop");
        if (tp->query_wiz_level())
            write("You will need to use <mumstop> to end this performance.\n");
        return;
    }
    if (living(who))
    {
        tell_object(who, tp->query_The_name(who) +" "+
            "extends "+ POSSESS(tp) +" hands toward you, palm up, and "+
            "begins making slow, lifting motions.\n");       
        tell_object(tp, 
            "You extend your hands, palms up, toward "+
            who->query_The_name(tp) +" and make slow, lifting motions.\n");
        tell_room(environment(TP), (QCTNAME(tp) +" extends "+ POSSESS(tp) +
            " hands, palm up, toward "+ QTNAME(who) +" and makes "+
            "slow, lifting motions.\n" ), ({tp, who}));
        return;
    }
    tell_object(tp, 
        "You extend your hands, palms up, toward the "+
        who->short() +" and make slow, lifting motions.\n");
    tell_room(environment(TP), (QCTNAME(tp) +" extends "+ POSSESS(tp) +
        " hands, palm up, toward the "+ who->short() +" and makes "+
        "slow, lifting motions.\n" ), ({tp, who}));
    
}

private void
levi_two(object tp, object who)
{
    TEST_LINK_DEATH
 
    if (!who)
    {
        write("It seems that whatever it was that you were going to "+
            "levitate is no longer here!\n");
        tp->command("$mumstop");
        if (tp->query_wiz_level())
            write("You should use <mumstop> to end this performance.\n");
        return;
    }
    if (living(who))
    {
        tell_object(who, tp->query_The_name(who) +"'s "+
            "extended hands begin to tremble, and "+ POSSESS(tp) +" face "+
            "contorts.\nYou suddenly feel lighter. You look down, and see "+
            "that your feet are a good hand-span above the ground!\n");       
        tell_object(tp, 
            "You make your hands tremble, and contort your face as though "+
            "you are lifting a heavy weight.\n"+ who->query_The_name(tp) +
            " rises a hand-span above the ground!\n");
        tell_room(environment(TP), (QCTNAME(tp) +"'s extended hands begin "+
            "to tremble, and "+ POSSESS(tp) +" face contorts.\n"+
            QCTNAME(who) +" rises gently into the air, stopping a hand-"+
            "span above the ground!\n"), ({tp, who}));
        return;
    }
    tell_room(environment(TP), (QCTNAME(tp) +"'s extended hands begin "+
        "to tremble, and "+ POSSESS(tp) +" face contorts.\nThe "+ 
        capitalize(who->short()) +" rises gently into the air, "+
        "stopping a hand-span above the ground!\n"), ({tp, who}));
    tell_object(tp, 
        "You make your hands tremble, and contort your face as though "+
        "you are lifting a heavy weight.\nThe "+ 
        who->short() +" rises a hand-span above the ground!\n");

}

private void
levi_end(object tp, object who)
{
    TEST_LINK_DEATH
 
    if (!who)
    {
        write("It seems that whatever it was that you were levitating "+
            "is no longer here!\n");
        tp->command("$mumstop");
        if (tp->query_wiz_level())
            write("You should use <mumstop> to end this performance.\n");
        return;
    }
    if (living(who))
    {
        tell_object(who, TP->query_The_name(who) +" "+
            "suddenly sags with exhaustion. "+ capitalize(POSSESS(tp)) +
            " hands drop to "+ POSSESS(tp) +" sides and you land back "+
            "on the ground with a thud!\n");       
        tell_object(tp, 
            "You pretend to sag with exhaustion, allowing "+ 
            who->query_The_name(tp) +
            " to fall to the ground with a thump.\n");
        tell_room(environment(TP), (QCTNAME(tp) +" suddenly sags with ex"+
            "haustion.\n"+ capitalize(POSSESS(tp)) +" hands drop to "+ 
            POSSESS(tp) +" sides and "+ QTNAME(who) +" lands back "+
            "on the ground with a thump!\n"), ({tp, who}));
        ADD_A_LEVEL(this_player());
        tp->remove_prop(LEVI_INDEX);
        remove_alarm(tp->query_prop(MIME_ALARM));
        tp->remove_prop(MIME_ALARM);
        return;
    }
    tell_object(tp, 
        "You pretend to sag with exhaustion, allowing the "+ 
        who->short() +
        " to fall to the ground with a thump.\n");
    tell_room(environment(TP), (QCTNAME(tp) +" suddenly sags with exh"+
        "haustion.\n"+ capitalize(POSSESS(tp)) +" hands drop to "+ 
        POSSESS(tp) +" sides and the "+ who->short() +" lands back "+
        "on the ground with a thump!\n"), ({tp, who}));
    ADD_A_LEVEL(this_player());
    tp->remove_prop(LEVI_INDEX);
    remove_alarm(tp->query_prop(MIME_ALARM));
    tp->remove_prop(MIME_ALARM);
}


private function* levitate = ({ levi_one, levi_two, levi_end, });

private void
do_levitate(object tp, object who)
{
    int index = tp->query_prop(LEVI_INDEX);
  
    tp->add_prop(LEVI_INDEX, index+1);
    applyv(levitate[index], ({tp, who}));
}

int 
levitate(string str)
{
    object *whos, who;
    object tpl;

    if (TP->query_prop(MIME_ALARM))
    {
        notify_fail("You are already performing something!\n");
        return 0;
    }
    if (!strlen(str))
    {
        notify_fail("Who or what do you want to levitate?\n");
        return 0;
    }
    if (str == "me" || str == "myself" || 
        str == TP->query_real_name())
    {
        notify_fail("You cannot levitate yourself.\n");
        return 0;
    }
    whos = FIND_STR_IN_OBJECT(str, environment(TP));
    if (!sizeof(whos))
    {
	notify_fail("Can't locate "+ str +". Sorry.\n");
	return 0;
    }
    if (sizeof(whos) > 1)
    {
        notify_fail("You can only levitate one thing at a time.\n");
        return 0;
    }
    if (objectp(TP->query_attack()))
    {
        notify_fail("It is not wise to attempt this during combat. "+
            "You could be injured.\n");
        return 0;
    }
    who = whos[0];
    if (who->query_prop(HEAP_I_IS))
    {
        notify_fail("You are unable to levitate that for some odd "+
            "reason.\n");
        return 0;
    }
    if ((who->query_prop(OBJ_I_WEIGHT) / 2) > 
       (TP->query_prop(OBJ_I_WEIGHT) + (TP->query_mana() * 2)))
    {
        notify_fail("The "+ str +" is far too heavy for you "+
           "to levitate.\n");     
        return 0;
    }
    if (living(who))
    {
        tell_object(who, TP->query_The_name(who) +
            " stares intently at you.\n");       
        tell_object(TP, "You stare intently at "+ who->query_The_name(TP) +
            ".\n");
        tell_room(environment(TP), (QCTNAME(TP) +" stares intently at "+ 
             QTNAME(who) +".\n" ), ({TP, who}));
        tpl = TP;
        TP->remove_prop(LEVI_INDEX);
        TP->add_prop(MIME_ALARM, set_alarm(2.0, 3.0, &do_levitate(tpl, who)));
        return 1;
    }
    tell_object(TP, "You stare intently at the "+ who->short() +
        ".\n");
    tell_room(environment(TP), (QCTNAME(TP) +" stares intently at the "+ 
         who->short() +".\n" ), ({TP, who}));
    
    tpl = TP;
    TP->remove_prop(LEVI_INDEX);
    TP->add_prop(MIME_ALARM, set_alarm(2.0, 3.0, &do_levitate(tpl, who)));
    return 1;

}

/*
 *     mscarf and its steps
 */
private void
scarf_one(object tp)
{
    TEST_LINK_DEATH

    tell_object(tp, 
        "You flourish a colourful scarf, making it ripple in the "+
        "air before you.\n");
    ALLBBX(" flourishes a colourful scarf, making it ripple in the "+
        "air!\n");
}

private void
scarf_two(object tp)
{
    TEST_LINK_DEATH

    tell_object(tp,
        "You drape the scarf across the palm of your left hand, "+
        "then place a coin in it.\n");
    ALLBBX(" drapes the scarf across the palm of "+ POSSESS(tp) +
        " left hand, then places a single coin in it.\n");       
}

private void
scarf_three(object tp)
{
    TEST_LINK_DEATH

    tell_object(tp,
        "You close your left hand and proceed to stuff the ends of "+
        "the scarf into it with your right one.\n");
    ALLBBX(" closes "+ POSSESS(tp) +" left hand over the coin and, "+
        "using "+ POSSESS(tp) +" right index finger, stuffs the "+
        "ends of the scarf into "+ POSSESS(tp) +" left hand until "+
        "none of it shows.\n");       
}

private void
scarf_four(object tp)
{
    TEST_LINK_DEATH

    tell_object(tp,
        "You wave your right hand gracefully over your left"+
        ".\n");
    ALLBBX(" gracefully waves "+ POSSESS(tp) +" right hand over "+
        POSSESS(tp) +" closed left one.\n");       
}

private void
scarf_end(object tp)
{
    TEST_LINK_DEATH

    tell_object(tp,
        "You hold your left hand up to your eye and peep into it. "+
        "Then you smile broadly and open your hand wide, revealing "+
        "an empty palm.\n");
    ALLBBX(" holds "+ POSSESS(tp) +" left hand up to "+ POSSESS(tp) +
        " eye and peeps into it.\n");
    ALLBBX(" jumps excitedly and opens "+ POSSESS(tp) +" hand wide, "+
        "revealing an empty palm.\nThe coin and scarf have disappeared!\n");
    ADD_A_LEVEL(this_player());

    if (tp->query_prop(LIVE_M_MOUTH_BLOCKED, MIME_MESSAGE))
        tp->remove_prop(LIVE_M_MOUTH_BLOCKED);
    tp->remove_prop(SCARF_INDEX);
    remove_alarm(tp->query_prop(MIME_ALARM));
    tp->remove_prop(MIME_ALARM);

}

private function* scarf = ({ scarf_one, scarf_two, scarf_three, 
			    scarf_four, scarf_end });

private void
do_scarf(object tp)
{
    int index = tp->query_prop(SCARF_INDEX);
  
    tp->add_prop(SCARF_INDEX, index+1);
    applyv(scarf[index], ({tp}));
}

int
mscarf(string str)
{
    object tpl, ob;

    if (strlen(str))
    {
        notify_fail("Mscarf "+ str+" can't be done.\n");
        return 0;
    }

    if (TP->query_prop(MIME_ALARM)) 
    {
        notify_fail("You are already performing something!\n");
        return 0;
    }

    if (!present("scarf", TP))
    {
        notify_fail("You can't perform this trick without a scarf!\n");
        return 0;
    }

    if (!present("coin", TP))
    {
        notify_fail("You can't perform this trick without a coin!\n");
        return 0;
    }

    if (sizeof(filter(all_inventory(TP), &->query_wielded())))
    {
        TP->command("$unwield all");        
    }
    
    tpl = TP ;
    TP->remove_prop(SCARF_INDEX);
    TP->add_prop(MIME_ALARM, set_alarm(3.0, 10.0, &do_scarf(tpl) ) );
    return 1;
}

/*
 *   mtwist and its steps
 *   If you want to add new figures, have to change the string
 *   figures here, and teh mapping in the obj/mummer_balloon.
 */ 
private void
twist_one(object tp, string s)
{
    TEST_LINK_DEATH

    tell_object(tp, 
        "You hold the intestine to your mouth and "+
        "blow into it, filling it with air.\n");
    ALLBBX(" holds an intestine to "+ POSSESS(TP) +
        " mouth and blows into it, filling it with air.\n");
}

private void
twist_two(object tp, string s)
{
    TEST_LINK_DEATH
    tell_object(tp, 
        "You tie the end of the intestine off and begin "+
        "twisting it here and looping it there, making squeeks and "+
        "shrieks fill the air.\n");
    ALLBBX(" ties the end of the intestine off and "+
        "begins twisting it around.\nSqueeks and shrieks from the "+
        "inflated intestine fill the air.\n");
}

private void
twist_end(object tp, string s)
{
    object *gut;
    object figure;

    TEST_LINK_DEATH

    gut = filter(all_inventory(TP), "gut_check", this_object());

    if (!sizeof(gut))
    {
	write("You need an intestine to do this.\n");
        tp->command("$mumstop");
        if (tp->query_wiz_level())
            write("You will need to use <mumstop> to end this performance.\n");
	return;
    }
    
    tell_object(tp,
        "You finish twisting the inflated intestine, which now "+
        "bears a strong resemblance to "+ LANG_ADDART(s) +", and "+
        "happily display your handiwork.\n");
    ALLBBX(" has finished twisting the inflated intestine"+
        ", which now bears a strong resemblance to "+ LANG_ADDART(s) +
        ".\n");
    ADD_A_LEVEL(this_player());

    setuid();
    seteuid(getuid());    

    figure = clone_object(OBJ_DIR +"mummer_balloon");
    figure->set_figure(s);
    figure->create_figure();
    figure->move(TP, 1);
    
    if (gut[0]->query_prop(HEAP_I_IS))
    {
	figure->set_from(gut[0]->singular_short());
        gut[0]->set_heap_size(gut[0]->num_heap() -1);
    }
    else
    {
	figure->set_from(gut[0]->short());
        gut[0]->remove_object();
    }

    tp->remove_prop(TWIST_INDEX);
    remove_alarm(tp->query_prop(MIME_ALARM));
    tp->remove_prop(MIME_ALARM);

}

private function* twist = ({ twist_one, twist_two, twist_end });

private void
do_twist(object tp, string s)
{
    int index = tp->query_prop(TWIST_INDEX);

    tp->add_prop(TWIST_INDEX, index+1);
    applyv(twist[index], ({tp, s}));
}

int
mtwist(string str)
{
    object *model;
    object  tpl;
    string  s;

    if (TP->query_prop(MIME_ALARM))
    {
        notify_fail("You are already performing something!\n");
        return 0;
    }
    if (str == "list")
    {
        write("You are able to make the following balloon figures:\n"+
            capitalize(COMPOSITE_WORDS(figures)) +".\n");
        return 1;
    }
    if (!sizeof(filter(all_inventory(TP), "gut_check", this_object())))
    {
	notify_fail("You need an intestine to do this.\n");
	return 0;
    }
    if (!strlen(str))
    {
        // we'll have to fast forward, do a randomly generated figure.
        s = figures[random(sizeof(figures))];
        tpl = TP;

        write("You take a deep, calming breath, and hold it.\n");
        write("You decide to just let the balloon figure take shape "+
            "in your hands.\n");
        say(QCTNAME(TP) +" takes a deep breath and holds it.\n");     

        TP->remove_prop(TWIST_INDEX);
        TP->add_prop(MIME_ALARM, set_alarm(2.0, 4.0, &do_twist(tpl, s) ) );
        return 1;
    }
   if (str == "intestine" || str == "intestines" || str == "balloon" || 
       str == "bladder" || str == "balloon figure")
    {
        notify_fail("You don't need to use "+ str +" when trying to "+
            "<mtwist>. Just use <mtwist> or <mtwist [model]>, where "+
            "[model] is something in your inventory, in the room "+
            "with you, or from the list in the <mtwist list>.\n");
        return 0;
    }
    model = FIND_STR_IN_OBJECT(str, TP);
    if (!sizeof(model))
        model = FIND_STR_IN_OBJECT(str, environment(TP));
    if (sizeof(model))
        s = model[0]->short(TP);
    else if (member_array(str, figures) != -1)
        s = str;
    else 
    {
        notify_fail("Mtwist "+ str +" cannot be done.\n");
        return 0;
    }

    write("Deciding to make "+ LANG_ADDART(s) +", you hold the image "+
        "in your mind, take a deep, calming breath, and hold it.\n");
    say(QCTNAME(TP) +" suddenly looks thoughtful and takes a deep "+
        "breath.\n");     

    tpl = TP;
    TP->remove_prop(TWIST_INDEX);
    TP->add_prop(MIME_ALARM, set_alarm(3.0, 5.0, &do_twist(tpl, s) ) );
    return 1;
}

/*
 *      mwall and its steps...
 */
private void
wall_one(object tp)
{
    TEST_LINK_DEATH

    tell_object(tp, 
	"You take a deep, steadying breath, readying yourself to "+
        "begin pantomiming being stuck behind an invisible wall.\n");
}

private void
wall_two(object tp)
{
    TEST_LINK_DEATH

    tell_object(tp,
        "You reach the spot where you have decided the invisible "+
        "wall is. You pretend to run into it.\n");
    ALLBBX(" walks into an invisible wall!\n");       
}

private void
wall_three(object tp)
{
    TEST_LINK_DEATH

    tell_object(tp,
	"You pretend to bang your head against the wall, falling "+
        "to the ground in exaggerated agony.\n");
    ALLBBX("'s head bangs into the wall, and "+ PRONOUN(tp) +
        " falls to the ground in obvious agony.\n");
}

private void
wall_four(object tp)
{
    TEST_LINK_DEATH

    tell_object(tp,
	"You rise to your knees and pantomime running your hands "+
        "along the wall, as if feeling for an opening.\n");
    ALLBBX(" rises to "+ POSSESS(tp) +" knees and runs "+ POSSESS(tp) +
        " hands along the invisible wall, feeling for an opening.\n");
}

private void
wall_five(object tp)
{
    TEST_LINK_DEATH

    tell_object(tp,
        "Now you put a frustrated expression on your face. You open "+
        "your mouth in a silent scream and pretend to bang your "+
        "fists on the wall.\n");
    ALLBBX(" suddenly looks very frustrated. You can see "+ OBJECTIVE(tp) +
        " screaming and banging on the wall, but you can't hear "+
        OBJECTIVE(tp) +".\n");
}

private void
wall_six(object tp)
{
    TEST_LINK_DEATH

    tell_object(tp,
        "Now you stand and back away from the wall"+
        ".\n");
    ALLBBX(" gets to "+ POSSESS(tp) +" feet and backs away from the wall"+
        ".\n");
}

private void
wall_seven(object tp)
{
    TEST_LINK_DEATH

    tell_object(tp,
        "You mime taking a deep breath, then run at the wall and fake "+
        "throwing your shoulder against it.\n");
    ALLBBX(" takes a deep breath, then runs toward the invisible wall "+
        "and throws "+ POSSESS(tp) +" shoulder against it.\n");
}

private void
wall_end(object tp)
{
    TEST_LINK_DEATH

    tell_object(tp,
        "You pitch forward in a controlled tumble and land in a heap, "+
        "then carefully exaggerate a triumphant grin.\n");
    ALLBBX(" pitches forward and lands in a heap at your feet, a "+
        "triumphant grin on "+ POSSESS(tp) +" face.\n");
    ADD_A_LEVEL(this_player());

    if (tp->query_prop(LIVE_M_MOUTH_BLOCKED, MIME_MESSAGE))
        tp->remove_prop(LIVE_M_MOUTH_BLOCKED);
    tp->remove_prop(WALL_INDEX);
    remove_alarm(tp->query_prop(MIME_ALARM));
    tp->remove_prop(MIME_ALARM);
}
private function* wall = ({ wall_one, wall_two, wall_three, wall_four,
			    wall_five, wall_six, wall_seven, wall_end });

private void
do_wall(object tp)
{
    int index = tp->query_prop(WALL_INDEX);
  
    tp->add_prop(WALL_INDEX, index+1);
    applyv(wall[index], ({tp}));
}

int
mwall(string str)
{
    object tpl;

    if (strlen(str))
    {
        NF("Mwall "+ str+" can't be done.\n");
        return 0;
    }

    if (TP->query_prop(MIME_ALARM)) 
    {
        notify_fail("You are already performing something!\n");
        return 0;
    }
    if (sizeof(filter(all_inventory(TP), &->query_wielded())))
    {
        TP->command("$unwield all");        
    }
    tpl = TP;
    TP->remove_prop(WALL_INDEX);
    if (!TP->query_prop(LIVE_M_MOUTH_BLOCKED))
        TP->add_prop(LIVE_M_MOUTH_BLOCKED, MIME_MESSAGE);
    TP->add_prop(MIME_ALARM, set_alarm(3.0, 4.0, &do_wall(tpl) ) );
    return 1;
}

/*
 *  mswallow and its steps
 */
private void
swal_one(object tp, object item)
{
    TEST_LINK_DEATH
 
    if (!item)
    {
        write("You seem to have misplaced whatever it was that you "+
           "were going to swallow!\n");
        tp->command("$mumstop");
        if (tp->query_wiz_level())
            write("You will need to use <mumstop> to end this performance.\n");
        return;
    }
    tell_object(tp, 
        "Tossing your head well back and holding your mouth "+
        "wide open, you put the "+ item->short() +" in your "+
        "mouth and make a great show of swallowing it.\n");
    ALLBBX(" puts the "+ item->short() +" in "+ POSSESS(tp) +
        " mouth and swallows.\n"+PRONOUN(tp) +" grimaces and "+
        "massages "+ POSSESS(tp) +" neck, pushing the "+ item->short()+
        " farther down "+ POSSESS(tp) +" throat.\n");
}

private void
swal_two(object tp, object item)
{
    TEST_LINK_DEATH
 
    if (!item)
    {
        write("You seem to have misplaced your prop for this act.\n");
        tp->command("$mumstop");
        if (tp->query_wiz_level())
            write("You will need to use <mumstop> to end this performance.\n");
        return;
    }
    tp->command("$msleeve");
}

private void
swal_end(object tp, object item)
{
    TEST_LINK_DEATH

    if (!(item))
    {
        write("You seem to have misplaced your prop for this act.\n");
        tp->command("$mumstop");
        if (tp->query_wiz_level())
            write("You will need to use <mumstop> to end this performance.\n");
        return;
    }
        
    tell_object(tp,
        "You leap strongly, legs spread wide and toes pointed, and "+
        "pluck the "+ item->short() +" from thin air.\n");
    ALLBBX(" Leaps mightily, legs spread wide and toes pointed, "+
        "and reaching far above "+ POSSESS(tp) +" head, plucks "+ 
        LANG_ASHORT(item) +" from thin air!\nAmazing!\n");
    ADD_A_LEVEL(this_player());

    if (tp->query_prop(LIVE_M_MOUTH_BLOCKED, MIME_MESSAGE))
        tp->remove_prop(LIVE_M_MOUTH_BLOCKED);
    tp->remove_prop(SWALLOW_INDEX);
    remove_alarm(tp->query_prop(MIME_ALARM));
    tp->remove_prop(MIME_ALARM);
}

private function* swallow = ({ swal_one, swal_two, swal_end, });

private void
do_swallow(object tp, object item)
{
    int index = tp->query_prop(SWALLOW_INDEX);
  
    tp->add_prop(SWALLOW_INDEX, index+1);
    applyv(swallow[index], ({tp, item}));
}

int mswallow(string str)
{
    object *items, item;
    object tpl;

    if (TP->query_prop(MIME_ALARM))
    {
        notify_fail("You are already performing something!\n");
        return 0;
    }
    if (!strlen(str))
    {
        notify_fail("What do you want to swallow?\n");
        return 0;
    }
    items = FIND_STR_IN_OBJECT(str, TP);
    if (!sizeof(items))
    {
	notify_fail("Can't locate "+ str +". Sorry.\n");
	return 0;
    }
    if (sizeof(items) > 1)
    {
        notify_fail("You can only swallow one thing at a time.\n");
        return 0;
    }
    if (objectp(TP->query_attack()))
    {
        notify_fail("It is not wise to swallow that during combat. "+
            "You could injure yourself.\n");
        return 0;
    }
    item = items[0];
    if (item->query_prop(OBJ_I_VOLUME) > 5000)
    {
        notify_fail("The "+ item->short() +" is far too large to fit "+
            "into your mouth, never mind swallow!\n");     
        return 0;
    }
    write("You hold "+ LANG_ASHORT(item) +" in your hands and "+
        "display it for all to see.\n");
    say("With practiced grace, "+ QTNAME(TP) +" takes hold of "+ 
        LANG_ASHORT(item) +" and displays it for all to see.\n");       

    tpl = TP;
    TP->remove_prop(SWALLOW_INDEX);
    TP->add_prop(MIME_ALARM, set_alarm(3.0, 3.0, &do_swallow(tpl, item)));
    return 1;

}



/*
 *   	mstop  -- stops the performances.
 * NOTE: A check for the index of each emote sequence must be
 *       added below.
 */
int
mstop(string str)
{
    
    int alarm_id;

    if (strlen(str))
    {
        NF("Mumstop "+ str+" can't be done.\n");
        return 0;
    }
   
    /* Remove speech block just in case it was missed */
    if (TP->query_prop(LIVE_M_MOUTH_BLOCKED, MIME_MESSAGE))
        TP->remove_prop(LIVE_M_MOUTH_BLOCKED);

    if (!(alarm_id = TP->query_prop(MIME_ALARM)) ) 
    {
        notify_fail("Ok.\n");
        return 0;
    }

    remove_alarm(alarm_id);

    /* Add checks for the emote sequence indices here */
    if (TP->query_prop(MIME_ALARM))
        TP->remove_prop(MIME_ALARM);

    write("You stop performing.\n");
    allbb(" stops performing.");
    return 1;
}

