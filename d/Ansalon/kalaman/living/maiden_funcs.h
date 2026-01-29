void
greet_func1(object enemy)
{
    if(!CAN_SEE(TO, enemy))
	return;

    if(P("ansalon_sword_object",TP))
	if(random(12) == 1)
	{
	    if(TP->query_gender() == 1)
	    {
		command("say to " +TP->query_real_name() + " My that is a beautiful " +
		  "insignia you are wearing! The craftwork on that kestrel is simply divine! " +
		  "Where can I get one?");
	    }
	    else
	    {
		command("say to " +TP->query_real_name()+ " My, is that the crimson " +
		  "kestrel insignia you wear? The mark of a master swordsman?");
		command("curtsey shy " +TP->query_real_name());
		command("say to " +TP->query_real_name() + " Men like you are in " +
		  "big demand these days, with times being so dark, and evil creatures " +
		  "such as those hideous skeletal warriors haunting the night!");
		command("shiver");
	    }
	}
}

void
knight_greet(object enemy)
{
    if(!CAN_SEE(TO, enemy))
	return;

    if(TP->query_knight_level())
	if(random(10) == 1)
	{
	    if(random(2) == 1)
	    {
		command("frown");
		command("emote mumbles something about the knights of Solamnia.");
	    }
	    else
	    {
		if(TP->query_knight_sublevel() == 11)
		{
		    command("emote gasps: Oh my! The " +TP->query_knight_subtitle() + "!");
		    command("curtsey " +TP->query_real_name());
		    command("say to " +TP->query_real_name() + " Greetings " +TP->query_knight_subtitle()+
		      "!");
		    command("smile shy " +TP->query_real_name());
		}
		else
		{
		    if(TP->query_gender() == 1)
		    {
			command("say to " +TP->query_real_name() +
			  " Greetings milady knight of Solamnia!");
			command("curtsey " +TP->query_real_name());
		    }
		    else
		    {
			command("sigh wist " +TP->query_real_name());
			command("say to " +TP->query_real_name() +
			  " Greetings sir knight of Solamnia!");
			command("curtsey " +TP->query_real_name());
		    }
		}
	    }
	}
}

void
goblin_greet(object enemy)
{
    if(!CAN_SEE(TO, enemy))
	return;
    if(TP->query_race_name() == "goblin" ||
       TP->query_race_name() == "hobgoblin")
    {
	if(random(7) == 1)
	{
	    command("say Oh my! Oh my! A goblin!");
	    command("shout Help! A goblin is here in Kalaman!");
	    command("panic");
	    command("cower");
	    TO->run_away();
	}
    }
}

void
hobbit_greet(object enemy)
{
    if(!CAN_SEE(TO, enemy))
	return;

    if(TP->query_race_name() == "kender")
    {
	if(random(4) == 1)
	{
	    if(random(2) ==1)
	    {
		command("say to " +TP->query_real_name() + " Hello there little one!");
		command("ruffle " +TP->query_real_name());
		command("say to " +TP->query_real_name() + " Now you don't get into any " +
		  "trouble around here, okay?");
		command("smile compas " +TP->query_real_name());
	    }
	    else
	    {
		command("jump");
		command("say to " +TP->query_real_name()+ " Oh! You shouldn't sneak " +
		  "up on people like that! You almost scared me to death!");
		command("peer " +TP->query_real_name());
		command("say to " +TP->query_real_name() + " Funny, I always thought " +
		  "kender were not allowed in Kalaman.");
		command("shrug .");
	    }
	}
    }
    if(TP->query_race_name() == "hobbit")
    {
	if(random(4) ==1)
	{
	    if(random(2) ==1)
	    {
		command("say to " +TP->query_real_name() + " My, you are " +
		  "very short for a human!");
		command("giggle");
	    }
	    else
	    {
		command("say to " +TP->query_real_name()+ " Oh... you poor dear. " +
		  "Have you lost your mother? Come... let me help you find her.");
		command("comfort " +TP->query_real_name());
	    }
	}
    }
}
