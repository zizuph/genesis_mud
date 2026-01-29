void
greet_func1(object enemy)
{
    if(!CAN_SEE(TO, enemy))
	return;

    switch(random(6))
    {
    case 0:
	command("emote walks over to you and begins massaging " +
	  "your shoulders.");
	command("say Was that your first time with us? You " +
	  "seemed a little shy...");
	command("giggle");
	break;
    case 1:
	command("emote gets up from the bed and throws herself " +
	  "around you, giving you a looooong kiss.");
	command("say You were amazing last night! I hope to see " +
	  "you again soon...");
	command("emote spanks you playfully.");
	break;
    case 2:
	command("emote stretches shamelessly before you.");
	command("say You were a little rough last night... next time " +
	  "perhaps you should hire Grinhilda the troll... she likes " +
	  "it rough, as she regenerates.");
	command("emote rubs her side thoughtfully.");
	break;
    case 3:
	command("emote walks over to you and wraps her arms " +
	  "around your neck.");
	command("say You must have some dwarf blood in you! " +
	  "I didn't think you would ever stop!");
	command("grin lust");
	command("say Next time I think you should pay an " +
	  "extra gold or two, and have a few more girls in " +
	  "on the action!");
	command("wink");
	break;
    case 4:
	command("emote stretches lithely out before you.");
	command("say I knew a calian that looked just like you...");
	command("say He loved to use his warrior skills in "+
	  "bed, especially his move behind, if you know " +
	  "what I mean...");
	command("giggle");
	break;
    case 5:
	command("emote wraps her arms around you.");
	command("say Let me guess... you used to be a member of the Army of " +
	  "Angmar? You sure know how to swing that club of yours..");
	command("giggle misc");
	break;
    }
}
