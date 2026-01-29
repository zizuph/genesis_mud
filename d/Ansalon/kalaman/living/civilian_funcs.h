void
greet_func1(object enemy)
{
    if(!CAN_SEE(TO, enemy))
	return;
    if(environment(TO) != environment(enemy))
	return;
    if(P("ansalon_sword_object",TP))
	if(random(12) == 1)
	{
	    if(TP->query_gender() == 1)
	    {
		command("say She wears the insignia of the crimson kestrel!");
		command("say Just like out of the tales! A heroine, " +
		  "as fair as she is brave, comes to save the city!");
	    }
	    else
	    {
		command("say He wears the insignia of the crimson kestrel!");
		command("say to " +TP->query_real_name()+ " Greetings " +
		  "mighty warrior! May your blade cleave many a " +
		  "draconian skull!");
	    }
	    command("bow " +TP->query_real_name());
	}
}

void
knight_greet(object enemy)
{
    if(!CAN_SEE(TO, enemy))
	return;
    if(environment(TO) != environment(enemy))
        return;
    if(TP->query_knight_level())
	if(random(5) == 1)
	{
	    if(random(2) == 1)
	    {
		command("peer inter " +TP->query_real_name());
		command("emote mumbles something about the knights of Solamnia.");
	    }
	    else
	    {
		if(TP->query_knight_sublevel() == 11)
		{
		    command("emote calls over his shoulder: Kids! Come " +
		      "see this! The " +TP->query_knight_subtitle() +
		      " has come to Kalaman!");
		    command("bow awkward " +TP->query_real_name());
		}
		else
		{
		    if(TP->query_gender() == 1)
		    {
			command("say to " +TP->query_real_name() +
			  " Greetings milady Knight of Solamnia!");
			command("bow awkward " +TP->query_real_name());
		    }
		    else
		    {
			command("say to " +TP->query_real_name() +
			  " Greetings sir knight of Solamnia!");
			command("bow awkward " +TP->query_real_name());
		    }
		}
	    }
	}
}

void
goblin_greet(object enemy)
{
    if(!CAN_SEE(TO,enemy))
	return;
    if(environment(TO) != environment(enemy))
        return;

    if(TP->query_race_name() == "goblin" ||
       TP->query_race_name() == "hobgoblin")
    {
	if(random(7) == 1)
	{
	    if(random(3) == 1)
	    {
		command("say to " +TP->query_real_name()+ " Man you're ugly! " +
		  "If I didn't know that goblins were not allowed inside the " +
		  "city, I'd say you were one!");
	    }
	    else
	    {
		command("shout Help! A goblin is in the city!!!");
		command("back " +TP->query_real_name());
		TO->run_away();
	    }
	}
    }
}

void
hobbit_greet(object enemy)
{
    if(!CAN_SEE(TO, enemy))
	return;
    if(environment(TO) != environment(enemy))
        return;

    if(TP->query_race_name() == "kender")
    {
	if(random(6) == 1)
	{
	    if(random(2) ==1)
	    {
		command("say to " +TP->query_real_name()+ " Hey! " +
		  "You keep your hands out of my pockets? You hear me?");
		command("scowl " +TP->query_real_name());
	    }
	    else
	    {
		command("say to " +TP->query_real_name() +
		  " Hey! Whats a kender doing in the city?");
		command("grumble");
		command("emote mumbles something about kenders being as hard to " +
		  "keep out as rats from a sewer.");
	    }
	}
    }
    if(TP->query_race_name() == "hobbit")
    {
	if(random(12) == 1)
	{
	    if(random(2) ==1)
	    {
		command("peer " +TP->query_real_name());
		command("say to " +TP->query_real_name() + " What manner " +
		  "of creature are you?");
		command("say to " +TP->query_real_name() + " A thin, " +
		  "beardless dwarf? A shrunken human? Or just " +
		  "a cute goblin?");
		command("chuckle");
	    }
	    else
	    {
		command("say to " +TP->query_real_name() + " Hey kid! What are you doing out on " +
		  "the street without your moma?");
		command("say to " +TP->query_real_name()+ " And where did you " +
		  "get all the stuff? They aren't toys!");
		command("scold " +TP->query_real_name());
	    }
	}
    }
}
