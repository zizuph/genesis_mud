/*
 *  /d/Gondor/guilds/morgulmage/obj/nazgul_admin_ceremony.c
 *
 *  This file contains the promotion ceremony for mages being
 *  turned into Nazgul. Ideas by Aldinach.
 *
 *  Eowul, August 2009
 */
 
private object promoting_nazgul, receiving_mage;
private object sauron;

// Prototypes
void nazgul_ceremony_step1();
void nazgul_ceremony_step2();
void nazgul_ceremony_step3();
void nazgul_ceremony_step4();
void nazgul_ceremony_step5();
void nazgul_ceremony_step6();
void nazgul_ceremony_step7();
void nazgul_ceremony_step8();
void nazgul_ceremony_step9();
void nazgul_ceremony_step10();
void nazgul_ceremony_step11();
void nazgul_ceremony_step12();
void nazgul_ceremony_step13();
void nazgul_ceremony_step14();
void nazgul_ceremony_step15();
void nazgul_ceremony_step16();
void nazgul_ceremony_step17();
void nazgul_ceremony_step17a();
void nazgul_ceremony_step18();
void nazgul_ceremony_step19();
void nazgul_ceremony_step20();
void nazgul_ceremony_step21();
void nazgul_ceremony_step22();
void nazgul_ceremony_step23();
void nazgul_ceremony_step24();

private void initiate_nazgul_ceremony(object nazgul, object mage)
{
    if(objectp(promoting_nazgul) || objectp(receiving_mage)) return;
    
    promoting_nazgul = nazgul;
    receiving_mage = mage;
    
    set_alarm(5.0, 0.0, nazgul_ceremony_step1);
}

private int check_all_present() 
{
    int mage_present = objectp(receiving_mage) 
        && (environment(receiving_mage) == environment(this_object()));
    int nazgul_present = objectp(promoting_nazgul) 
        && (environment(promoting_nazgul) == environment(this_object()));
    
    if (mage_present && nazgul_present) return 1;
    
    if (objectp(sauron)) {
        tell_room(environment(this_object()), QCTNAME(sauron) + " rasps "
          + "threatingly as he notices some servants missing and fades "
          + "from view.\n");
        sauron->remove_object();
    } else {
        tell_room(environment(this_object()), "As the required servants "
          + "are no longer present, the ceremony is aborted.\n");
    }
    
    promoting_nazgul = 0;
    receiving_mage = 0;
    return 0;
}

private void nazgul_ceremony_step1()
{
    if(!check_all_present()) return;
    
    string message = capitalize(receiving_mage->query_mage_name()
      + ", you have expressed your desire to enter into the pinnacle "
      + "of service within this Tower. While you have managed to "
      + "collect the required votes from the Nine to be considered, "
      + "the ultimate decision is not ours to make.\n");
      
    promoting_nazgul->catch_msg("\nYou rasp: " + message);      
    tell_room(environment(this_object()), "\n" +
        QCTNAME(promoting_nazgul) + " rasps: " + message,
        ({ promoting_nazgul }), promoting_nazgul);
        
    set_alarm(5.0, 0.0, nazgul_ceremony_step2);
}

private void nazgul_ceremony_step2()
{
    if(!check_all_present()) return;
    
    promoting_nazgul->catch_msg("\nYou withdraw deferentially into "
      + "your robe, remaining silent but watchful.\n");
    tell_room(environment(this_object()), "\n" +
        QCTNAME(promoting_nazgul) + " withdraws deferentially into "
      + promoting_nazgul->query_possessive() + " robe, remaining "
      + "silent but watchful.\n",
      ({ promoting_nazgul }), promoting_nazgul);
      
    set_alarm(10.0, 0.0, nazgul_ceremony_step3);
}

private void nazgul_ceremony_step3()
{
    if(!check_all_present()) return;

    tell_room(environment(this_object()),    
        "\nThe air in the throne room shimmers and suddenly darkens. "
      + "You perceive the arrival of a terrible presence, bringing "
      + "with it a palpable sense of unease.\n");
      
    set_alarm(10.0, 0.0, nazgul_ceremony_step4);
}

private void nazgul_ceremony_step4()
{
    if(!check_all_present()) return;

    tell_room(environment(this_object()),        
        "\nIn what is now nearly complete darkness in the chamber, "
      + "the outline of a figure coalesces at the edge of your "
      + "vision. You recognize your Master at once, and your knees "
      + "weaken in His horrible presence.\n");

    seteuid(getuid());
    sauron = clone_object("/std/monster");
    sauron->set_name("sauron");
    sauron->set_race_name("figure");
    sauron->set_adj(({ "towering", "ethereal" }));
    sauron->set_short("towering ethereal figure");
    sauron->set_long("You attempt to examine the figure more "
        + "closely, but as you turn in its direction, you feel its "
        + "burning red eyes boring into you and dare not meet its "
        + "fiery gaze.\n");
    sauron->add_prop(NPC_I_NO_LOOKS, 1);
    sauron->add_prop(OBJ_M_NO_ATTACK, 1);
    sauron->add_prop(LIVE_I_NEVERKNOWN, 1);
    sauron->set_stats(({400, 400, 400, 400, 400, 400}));
    sauron->add_prop(CONT_I_HEIGHT, 300);
    sauron->set_hp(sauron->query_max_hp());
    sauron->move(environment(this_object()), 1);
    
    set_alarm(15.0, 0.0, nazgul_ceremony_step5);
}

private void nazgul_ceremony_step5()
{
    if(!check_all_present()) return;

    tell_room(environment(this_object()), "\n" +       
        QCTNAME(sauron) + " speaks in a terrifying voice: "
      + capitalize(promoting_nazgul->query_mage_name()) + ", "
      + "have you truly found a servant capable of carrying "
      + "the ultimate Burden in my Society?\n");
    
    set_alarm(20.0, 0.0, nazgul_ceremony_step6);
}

private void nazgul_ceremony_step6()
{
    if(!check_all_present()) return;

    tell_room(environment(this_object()), "\n"
      + QCTNAME(sauron) + " scans the room intensely with "
      + "its smouldering red orbs before settling on "
      + QTNAME(receiving_mage) + ".\n",
        ({ receiving_mage }), sauron);
    
    receiving_mage->catch_msg("\n" +       
        QCTNAME(sauron) + " scans the room intensely with "
      + "its smouldering red orbs before settling on you.\n");

    set_alarm(10.0, 0.0, nazgul_ceremony_step7);
}

private void nazgul_ceremony_step7()
{
    if(!check_all_present()) return;

    tell_room(environment(this_object()), "\n"     
      + QCTNAME(receiving_mage) + " seems frozen in place "
      + "by the power of the figure's gaze.\n",
        ({ receiving_mage }), sauron);

    receiving_mage->catch_msg("\nAgain, you feel your resolve "
      + "melting as the figure turns its gaze upon you. You "
      + "fall to your knees in submission, in awe of the "
      + "power of your Master.\n");
    receiving_mage->command("$kneel humbly figure");
      
    set_alarm(10.0, 0.0, nazgul_ceremony_step8);    
}

private void nazgul_ceremony_step8()
{
    if(!check_all_present()) return;

    receiving_mage->catch_msg("\nAs you kneel before your Master, "
      + "you feel his presence entering your mind. The presence "
      + "casually tears aside your mental defenses, leaving you "
      + "entirely exposed to a brutal mental interrogation.\n");

    tell_room(environment(this_object()),  "\n"      
      + QCTNAME(receiving_mage) + " suddenly stiffens and "
      + receiving_mage->query_possessive() + " burning red eyes "
      + "roll into the back of " + receiving_mage->query_possessive()
      + " head. At the same time, the towering figure smiles "
      + "grimly, his gaze set unwaveringly upon " 
      + QTNAME(receiving_mage) + ".\n",
        ({ receiving_mage }), sauron);

    set_alarm(10.0, 0.0, nazgul_ceremony_step9);    
}

private void nazgul_ceremony_step9()
{
    if(!check_all_present()) return;

    receiving_mage->catch_msg("\nAs suddenly as it began, the "
      + "interrogation ends and the presence withdraws from your "
      + "mind. You slump forward involuntarily, exhausted by "
      + "the ordeal.\n");

    tell_room(environment(this_object()), "\n"      
      + QCTNAME(receiving_mage) + " slumps forward limply, "
      + "exhaustion evident on " + receiving_mage->query_possessive()
      + " face.\n",
        ({ receiving_mage }), receiving_mage);
      
    receiving_mage->set_hp(1);
    receiving_mage->set_fatigue(1);
    
    set_alarm(8.0, 0.0, nazgul_ceremony_step10); 
}

private void nazgul_ceremony_step10()
{
    if(!check_all_present()) return;
    
    receiving_mage->catch_msg("\nWhile you cannot describe the effects "
      + "of whatever has just befallen you, you know that something "
      + "significant has occurred. Whatever small connection there "
      + "was that bound you to the living world, whatever tenuous "
      + "grasp you held on your memories of life as a mortal are "
      + "suddenly and completely gone.\n");
    receiving_mage->set_race_name("wraith");

    tell_room(environment(this_object()),            
        "\nWhat little color remained in " + receiving_mage->query_possessive()
      + " skin is now completely absent. Where before flesh clung to bone, an "
      + "unnatural and complete emaciation now dominates.\n",
      ({ receiving_mage }), receiving_mage);
      
    set_alarm(10.0, 0.0, nazgul_ceremony_step11); 
}

private void nazgul_ceremony_step11()
{
    if(!check_all_present()) return;

    receiving_mage->catch_msg("\nA sensation of transformation continues, but "
      + "you have little time to consider it further as the figure moves to "
      + "speak yet again.\n");

    tell_room(environment(this_object()), "\nHaving seen this before, you "
      + "recognize the effects of transformation into complete and "
      + "everlasting unlife slowly corrupting the slumped figure.\n",
        ({ receiving_mage }), receiving_mage);
        
    set_alarm(8.0, 0.0, nazgul_ceremony_step12); 
}

private void nazgul_ceremony_step12()
{
    if(!check_all_present()) return;
    
    receiving_mage->catch_msg("\nFinally, the towering figure lifts its gaze "
      + "from you, its grim work completed.\n");
    
    tell_room(environment(this_object()), "\nFinally, the towering figure "
      + "lifts its gaze from " + QTNAME(receiving_mage) + ", its grim work "
      + "completed.\n",
        ({ receiving_mage }), sauron);
        
    set_alarm(5.0, 0.0, nazgul_ceremony_step13); 
}

private void nazgul_ceremony_step13()
{
    if(!check_all_present()) return;

    tell_room(environment(this_object()), "\n" + QCTNAME(sauron) + " booms: "
      + "I have examined the one brought to me by the Nine and find "
      + receiving_mage->query_objective() + " ...\n");

    set_alarm(5.0, 0.0, nazgul_ceremony_step14); 
}

private void nazgul_ceremony_step14()
{
    if(!check_all_present()) return;

    tell_room(environment(this_object()), "\n" + QCTNAME(sauron) + " frowns "
      + "slightly, clearly considering his response.\n", ({}), sauron);
      
    set_alarm(25.0, 0.0, nazgul_ceremony_step15); 
}

private void nazgul_ceremony_step15()
{
    if(!check_all_present()) return;

    tell_room(environment(this_object()), "\nHis brief reverie complete, "
      + "the towering figure continues: " 
      + capitalize(receiving_mage->query_mage_name())
      + ", you have shown courage in putting yourself forward for "
      + "consideration of the burden of the Ring. After scouring your mind "
      + "and testing your resolve, I will bestow upon you one of the Nine "
      + "Rings of Power, and allow you into the circle of the Ulairi, my "
      + "most favored servants.\n", ({ }), sauron);
      
    set_alarm(20.0, 0.0, nazgul_ceremony_step16); 
}

private void nazgul_ceremony_step16()
{
    if(!check_all_present()) return;

    tell_room(environment(this_object()), "\n" + QCTNAME(sauron) + " booms: "
      + "However, remember always that to serve upon my Council requires a "
      + "new level of commitment, an unwavering dedication to the Tower "
      + "and to service. Always will I be watching, and should ever you "
      + "fail me, your Ring will return to me until one worthy of its "
      + "power can be found.\n", ({}), sauron);
      
    set_alarm(15.0, 0.0, nazgul_ceremony_step17); 
}

private void nazgul_ceremony_step17()
{
    if(!check_all_present()) return;

    tell_room(environment(this_object()), "\nSlowly, the figure opens "
      + "his clenched fist and from the dark shadows, a golden band "
      + "emerges. The power emanating from it is obvious as it spins "
      + "slowly in the shadows. With a barely perceptible gesture "
      + "from the ethereal figure, the ring floats purposefully to "
      + "the outstretched hand of " + QTNAME(receiving_mage) + ".\n",
        ({ receiving_mage }), sauron);

    receiving_mage->catch_msg("\nSlowly, the figure opens his clenched "
      + "fist and from the dark shadows, a golden band emerges. The "
      + "power emanating from it is obvious as it spins slowly in the "
      + "shadows.\n");
      
    set_alarm(5.0, 0.0, nazgul_ceremony_step17a); 
}

private void nazgul_ceremony_step17a() 
{
    if(!check_all_present()) return;

    receiving_mage->catch_msg("\nWithout conscious thought, you extend "
      + "your arm in direction of the ring and a slight gesture from "
      + "the ethereal figure sends it floating into your outstretched "
      + "hand.\n");

    MORGUL_MASTER->set_player_as_nazgul(receiving_mage);
    
    set_alarm(10.0, 0.0, nazgul_ceremony_step18); 
}

private void nazgul_ceremony_step18()
{
    if(!check_all_present()) return;

    tell_room(environment(this_object()), "\nSlowly, in a keening "
      + "voice, the black figure intones:\n\n");

    tell_room(environment(this_object()), 
        "\tThree Rings for the Elven-kings under the sky,\n"
      + "\tSeven for the Dwarf-lords in their halls of stone,\n"
      + "\tNine for Mortal Men doomed to die,\n\n");

    set_alarm(5.0, 0.0, nazgul_ceremony_step19); 
}

private void nazgul_ceremony_step19()
{
    if(!check_all_present()) return;

    tell_room(environment(this_object()), 
        "\nUpon uttering this verse, the figure looks meaningfully at "
      + "those gathered before him, and then continues.\n");

    set_alarm(5.0, 0.0, nazgul_ceremony_step20);       
}

private void nazgul_ceremony_step20()
{
    if(!check_all_present()) return;

    tell_room(environment(this_object()), "\n"
      + "\tOne for the Dark Lord on his dark throne,\n"
      + "\tIn the land of Mordor where the shadows lie.\n\n");

    set_alarm(5.0, 0.0, nazgul_ceremony_step21);       
}

private void nazgul_ceremony_step21()
{
    if(!check_all_present()) return;

    tell_room(environment(this_object()), "\nThe figure continues, its "
      + "voice rising into a keening crescendo:\n\n"
      + "\tOne Ring to rule them all, One Ring to find them,\n"
      + "\tOne Ring to bring them all, and in the darkness bind them,\n"
      + "\tIn the land of Mordor where the shadows lie.\n\n");

    set_alarm(10.0, 0.0, nazgul_ceremony_step22);
}

private void nazgul_ceremony_step22()
{
    if(!check_all_present()) return;

    tell_room(environment(this_object()), "\nHis intonation complete, with "
      + "the echoes of his final statement still ringing in your ears, "
      + "the ethereal figure begins to fade from view, his eyes locked "
      + "again on " + QTNAME(receiving_mage) + ".\n",
        ({ receiving_mage }), sauron);

    receiving_mage->catch_msg("\nHis intonation complete, with the echoes "
      + "of his final statement still ringing in your ears, the ethereal "
      + "figure begins to fade from view, his gaze again firmly set upon "
      + "you.\n");
      
    set_alarm(10.0, 0.0, nazgul_ceremony_step23);
}

private void nazgul_ceremony_step23()
{
    if(!check_all_present()) return;

    tell_room(environment(this_object()), "\nAgain the towering figure "
      + "speaks, much more quietly than before: Accept this ultimate "
      + "burden and serve me well in unlife, " 
      + capitalize(receiving_mage->query_mage_name()) + ", and you will "
      + "have my favor. Fail me in any way, and you shall be eternally "
      + "cast asunder...\n", ({}), sauron);
      
    set_alarm(10.0, 0.0, nazgul_ceremony_step24);
}

private void nazgul_ceremony_step24()
{
    if(!check_all_present()) return;
    
    tell_room(environment(this_object()), "\nAs the figure fades completely "
      + "from view, the light in the Throne Room returns to normal and the "
      + "final warning is left ringing clearly in your mind.\n");      
    sauron->remove_object();
    
    object *all_nazgul = filter(all_inventory(environment(this_object())), 
        &->query_nazgul());
    foreach(object nazgul : all_nazgul) 
    {
        MORGUL_MASTER->increase_activity(nazgul, ACTIVITY_PROMOTE_TO_NAZGUL);
    }
    
    receiving_mage = 0;
    promoting_nazgul = 0;
}