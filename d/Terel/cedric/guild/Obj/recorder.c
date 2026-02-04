inherit "/d/Terel/cedric/guild/obj/instrument";

#define RECORDER_FIX ({"recorder_mouldy",\
      "recorder_mouth_piece",\
      "recorder_warped",\
      "recorder_broken",\
      "recorder_big"})

public void
create_instrument()
{
    set_damage_desc(({ "is moldy and needs a good cleaning",
                       "has a cracked mouth-piece",
                       "is badly warped by the humidity",
                       "is missing its bottom section",
                       "has a large crack between finger-holes"}));
    set_short("beautiful Minstrel's recorder");
    set_long(
            "Fashioned from a deep red cherry wood, this recorder " +
            "is actually three sections fitted together: a flat, " +
            "lateral mouthpiece; a long middle piece with eight " +
            "fingerholes; and a small bell-shaped piece on the " +
            "end. A twirling vine of ivy has been carved into the " +
            "wood, running up and down the instrument's length, " +
            "curling at last around a florid inscription: the name " +
            "of your muse, " +holder->query_muse_name()+ ". " +
            "You may inspect your recorder to assess its state of " +
            "tuning and general repair.\n");
}

public string
show_instrument_subloc(object carrier, object for_obj)
{
    if (carrier == for_obj)
    {
	return "Your Minstrel's recorder is alive with music and " +
	       "dedicated to " + carrier->query_muse_name() + ".\n";
    }
    else
    {
        return capitalize(carrier->query_pronoun()) + " proudly carries" +
	       " a Minstrel's recorder.\n";
    }
}
