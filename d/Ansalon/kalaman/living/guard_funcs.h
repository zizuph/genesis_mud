void
greet_func1(object enemy)
{
    if(!CAN_SEE(TO, enemy))
	return;

    if(P("ansalon_sword_object",TP))
	if(random(10) == 1)
	{
	    if(TP->query_alignment() < 0 || TP->query_attack())
	    {
		command("say Be wary of this one, " +HE(TP)+ " wears the insignia of " +
		  "the crimson kestrel!");
		return;
	    }
	    if(TP->query_gender() == 1)
	    {
		command("say She wears the insignia of the crimson kestrel!");
		command("say I swear, I have never seen anyone so fair wearing it.");
	    }
	    else
	    {
		command("say to " +TP->query_real_name()+ " Greetings " +
		  "swordsmaster! Welcome to Kalaman!");
	    }
	    command("bow " +TP->query_real_name());
	}
}

void
knight_greet(object enemy)
{
    if(!CAN_SEE(TO, enemy))
	return;

    if(TP->query_knight_level())
	if(random(6) == 1)
	{
	    if(random(2) == 1)
	    {
		command("nod respect " +TP->query_real_name());
	    }
	    else
	    {
		if(TP->query_knight_sublevel() == 11)
		{
		    command("say Greetings " +TP->query_knight_subtitle() + "! " +
		      "This is an unexpected visit! Welcome to Kalaman!");
		    command("emote shouts over his shoulder: Alert " +
		      "Lord Calof! The " +TP->query_knight_subtitle()+
		      " has come to Kalaman!");
		    command("bow " +TP->query_real_name());
		}
		else
		{
		    if(TP->query_gender() == 1)
		    {
			command("say to " +TP->query_real_name() +
			  " Greetings milady Knight of Solamnia! Enjoy your stay in Kalaman!");
		    }
		    else
		    {
			command("say to " +TP->query_real_name() +
			  " Greetings sir Knight of Solamnia! Welcome to " +
			  "Kalaman!");
		    }
		}
	    }
	}
}
