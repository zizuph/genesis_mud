inherit "/d/Terel/cedric/guild/obj/instrument";

#define HARP_FIX ({"harp_strings",\
      "harp_forepillar",\
      "harp_neck",\
      "harp_resonator",\
      "harp_big"})

string muse = "";
object owner;

public void
create_instrument()
{
    set_damage_desc(({ "has a handful of missing strings",
		       "has a cracked forepillar",
		       "has a severely warped neck",
		       "has a crushed resonator",
		       "is broken completely in half"}));

    set_name("harp");
    set_short("exquisite Minstrel's harp");
    set_long(
            "This harp, made of a dark brown and fragrant spruce " +
            "wood, measures two and a half feet and is meant to be " +
            "pressed against the chest or rested in the lap. A " +
            "broad resonator supports a sounding board from which " +
            "29 strings, tuned diatonically, stretch up to the " +
            "neck, gently curving like a swan's. A narrow " +
            "forepillar reaches from the resonator's base to the " +
            "neck, forming a basic triangle. Above the point at " +
            "which the neck and forepillar meet, a carved and " +
            "painted head, depicting @@muse_desc@@, has been placed. " +
            "You may inspect your " +
            "harp to determine its state of tuning and general " +
            "repair.\n");
}

public string
muse_desc()
{
    if (owner && this_player() == owner)
    {
        return strlen(muse) ? muse + ", your muse" : "your muse";
    }

    return strlen(muse) ? "the muse " + muse : "a muse";
}

public void
set_owner(object who)
{
    owner = who;
    muse = who->query_muse_name() || "";
}

public string
show_instrument_subloc(object carrier, object for_obj)
{
    if (carrier == for_obj)
    {
  	return "Your Minstrel's harp is alive with music and dedicated " + 
  	       "to " + carrier->query_muse_name() + ".\n";
    }
    else
    {
	return capitalize(carrier->query_pronoun()) + " proudly carries" +
	       " a Minstrel's harp.\n";
    }
}
