inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */
query_auto_load()
{
    return MASTER;
}

create_object()
{
    set_name("symbol");
    add_name("dark sun");
    set_short("symbol of a dark sun");
    add_name("hsotoot");
    set_long("The symbol of the Holy Order of Thanar. On the back is a "+
      "list of the proper duties of a member.\n"+
      "~~~~~~~~~~~~~~~~~~~~~~~~~\n"+
      "-Worship the great god Thanar above all others.\n"+
      "-Seek to convert others to the Order of Thanar.\n"+
      "-Further the cause of humanity above all other races.\n"+
      "-Eliminate the non-human infestation in Kalad and in other lands.\n"+
      "~~~~~~~~~~~~~~~~~~~~~~~~~~\n"+
      "Type 'help thanar' for more information.\n"+
      "_________________________\n");

    add_prop(OBJ_I_NO_DROP,"You would not dare to drop the symbol!\n");
    set_no_show();
}

public string 
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (for_obj == on)
	data = "You are ";
    else
	data = "Judging from the intricacy of the tattoos on " + (environment(TO)->query_possessive()) + " forehead, it appears as if " + (environment(TO)->query_pronoun()) + " is ";

    if(on->query_average_stat() < 10)
	data+="a Reckless Member of the Holy Order of Thanar.\n";
    else
    if(on->query_average_stat() < 20)
	data+="A Vainglorious Member of the Holy Order of Thanar.\n";
    else
    if(on->query_average_stat() < 30)
	data+="a Foolhardy Member of the Holy Order of Thanar.\n";
    else
    if(on->query_average_stat() < 40)
	data+="an Experienced Member of the Holy Order of Thanar.\n";
    else
    if(on->query_average_stat() < 50)
	data+="a Learned Member of the Holy Order of Thanar.\n";
    else
    if(on->query_average_stat() < 60)
	data+="a Wise Member of the Holy Order of Thanar.\n";
    else
    if(on->query_average_stat() < 70)
	data+="a Great Member of the Holy Order of Thanar.\n";
    else
    if(on->query_average_stat() < 80)
	data+="a Worldly Member of the Holy Order of Thanar.\n";
    else
    if(on->query_average_stat() < 90)
	data+="an Outstanding Member of the Holy Order of Thanar.\n";
    else
    if(on->query_average_stat() < 100)
	data+="a Noviciate Leader of the Holy Order of Thanar.\n";
    else
    if(on->query_average_stat() < 110)
	data+="a Leader of the Holy Order of Thanar.\n";
    else
    if(on->query_average_stat() < 130)
	data+="a True Leader of the Holy Order of Thanar.\n";
    else
    if(on->query_average_stat() < 150)
	data+="a Godly Leader of the Holy Order of Thanar.\n";
    else
	data+="the Chosen One of Thanar.\n";

    return data;
}

void
enter_env(object to, object from)
{
    remove_name("hsotoot");
    if(to->query_race_name() != "human")
    {
	to->catch_msg("Your symbol of the Holy Order of Thanar vanishes "+
	  "from your grasp; You are not human!\n");
	remove_object();
	return;
    }

    add_name("hsotoot");
    if(living(environment(TO)))
	to->add_subloc("hsotoot",TO);
}

public void
leave_env(object from, object to)
{
    this_player()->remove_subloc("hsotoot");
}
init()
{
    ::init();
    add_action("help","help");
    add_action("display","display");
    add_action("bless","symbol");
    add_action("tpray","tpray");
    add_action("tlaugh","tlaugh");
    add_action("tanger","tanger");
    add_action("tsnarl","tsnarl");
    add_action("disgust","disgust");
    add_action("tscream","tscream");
    add_action("tlevels","tlevels");
}
int
help(string str)
{
    if(!str || str != "thanar")
    {
	notify_fail("Help what? Help thanar?\n");
	return 0;
    }
    write("As a member of the Holy Order of Thanar, the following commands "+
      "are available to you:\n"+
      "~~~~~~~~~~~~~~~~~~~~~\n"+
      "-display-->Display your holy symbol, it will get you past the guards.\n"+
      "-symbol--->Bless the area.\n"+
      "-tpray---->Pray to Thanar for aid.\n"+
      "-tlaugh--->Laugh in true amusement.\n"+
      "-tanger--->Vent your pent-up emotions.\n"+
      "-tsnarl--->Snarl with righteous fury.\n"+
      "-disgust-->Show how you feel about the lesser(non-human) races.\n"+
      "-tscream-->Utter a fearsome battle cry.\n"+
      "-tlevels-->A listing of titles in the Order.\n"+
      "~~~~~~~~~~~~~~~~~~~~~\n");
    say(QCTNAME(TP) + " stares intently at " + TP->query_possessive() + " symbol of a dark sun.\n");
    return 1;
}
display()
{
    write("You boldly thrust out your hand and display the holy symbol of "+
      "Thanar.\n");
    say(QCTNAME(TP) + " boldly thrusts out " + TP->query_possessive() + " hand and displays the holy symbol of Thanar.\n");
    return 1;
}
bless()
{
    write("Grasping your holy symbol of Thanar, you call upon its powers "+
      "to bless the area.\n");
    say("Grasping the holy symbol of Thanar, " + QCTNAME(TP) + " calls upon its powers to bless the area.\n");
    set_alarm(2.0,0.0,"bless_effect");
    return 1;
}
bless_effect()
{
    write("The area around you visibly darkens.\n");
    say("The area around " + QCTNAME(TP) + " visibly darkens.\n");
}
tpray()
{
    write("You clasp your hands together in reverence towards Thanar, the "+
      "greatest god of Kalad.\n");
    say(QCTNAME(TP) + " clasps " + TP->query_possessive() + " hands together in reverence towards Thanar, the greatest god of Kalad.\n");
    set_alarm(2.0,0.0,"tpray_effect");
    return 1;
}
tpray_effect()
{
    write("An apparition of the great god Thanar appears before you, and "+
      "you realize that your prayers have been answered.\n");
    say("A gathering of darkness enshrouds " + QCTNAME(TP) + ", then slowly fades away.\n");
}
tlaugh()
{
    write("You laugh menacingly, and look around the area with a superior glint in "+
      "your eyes.\n");
    say(QCTNAME(TP) + " laughs menacingly, and looks around the area with a superior glint in " + TP->query_possessive() + " eyes.\n");
    return 1;
}
tanger()
{
    write("Your face slowly contorts into a mask filled with hate, anger "+
      "and disgust.\n");
    say(QCTNAME(TP) + "'s face slowly contorts into a mask filled with "+
      "hate, anger and disgust.\n");
    return 1;
}
tsnarl()
{
    write("You look around the area and snarl with righteous fury.\n");
    say(QCTNAME(TP) + " looks around the area and snarls with righteous fury.\n");
    set_alarm(1.0,0.0,"tsnarl_effect");
    return 1;
}
tsnarl_effect()
{
    if(TP->query_base_stat(SS_DIS) > 124)
	say("You cringe in outright terror at the horrible expression on " + QCTNAME(TP) + "'s face.\n");
    else
    if(TP->query_base_stat(SS_DIS) > 74)
	say("You look at " + QCTNAME(TP) + " with a look of fear on your face.\n");
    else
    if(TP->query_base_stat(SS_DIS) > 49)
	say("You chuckle in amusement at " + QCTNAME(TP) + "'s attempt to strike terror in your heart.\n");
}
disgust()
{
    write("You spit on the ground in disgust at the thought of the lesser, "+
      "non-human races.\n");
    say(QCTNAME(TP) + " spits on the ground in disgust at the thought of the lesser, non-human races.\n");
    set_alarm(2.0,0.0,"disgust_effect");
    return 1;
}
disgust_effect()
{
    write("You feel better after expressing your hatred of the demihumans.\n");
    say(QCTNAME(TP) + " feels better after expressing " + TP->query_possessive() + " hatred of the demihumans.\n");
}
tscream()
{
    write("You raise your voice in a horrific cry of battle!\n");
    say(QCTNAME(TP) + " raises " + TP->query_possessive() + " voice in "+
      "a horrific cry of battle!\n");
    return 1;
}
tlevels()
{
    write("The following is the hierarchical ranking found within the Order.\n"+
      "->Reckless Member.\n"+
      "->Vainglorious Member.\n"+
      "->Foolhardy Member.\n"+
      "->Experienced Member.\n"+
      "->Learned Member.\n"+
      "->Wise Member.\n"+
      "->Great Member.\n"+
      "->Worldly Member.\n"+
      "->Outstanding Member.\n"+
      "->Noviciate Leader.\n"+
      "->Leader.\n"+
      "->True Leader.\n"+
      "->Godly Leader.\n"+
      "->The Chosen One of Thanar.\n"+
      "If you have suggestions for titles, feel free to leave an 'idea' "+
      "at the Secret Chamber of the Order, or mail Antharanos.\n");
    return 1;
}
