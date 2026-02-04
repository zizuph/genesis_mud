inherit "/d/Terel/cedric/guild/obj/instrument";

#define LUTE_FIX ({"lute_string",\
      "lute_tuning_peg",\
      "lute_fret_board",\
      "lute_bridge",\
      "lute_big"})

public void
create_instrument()
{
    set_damage_desc(({ "has a broken string",
		       "has lost a tuning-peg",
		       "has a warped fret-board",
		       "has a fractured bridge",
		       "has a large crack in its sounding-case" }));

     set_short("handsome Minstrel's lute");
     set_long(
            "The pear-shaped body of this beautiful lute has " +
            "been crafted from striped ribs of yew wood. " +
            "From the balsam wood bridge up the fretted neck " +
            "six strings have been tightly stretched, the lower " +
            "five in double courses. On each tuning-peg holding " +
            "the strings, a tiny marble cameo has been carved, " +
            "depicting " +holder->query_muse_name()+
            ", the muse to whom this instrument was dedicated. " +
            "A circular hole in the lute's body, beneath the " +
            "strings, allows the instrument to resonate " +
            "strongly. You may inspect your lute to assess its " +
            "state of tuning and general repair.\n");
}


public string
show_instrument_subloc(object carrier, object for_obj)
{
    if (carrier == for_obj)
    {
	return "Your Minstrel's lute is alive with music and " +
	       "dedicated to "+ carrier->query_muse_name() + ".\n";
    }
    else
    {
	return capitalize(carrier->query_pronoun()) + " proudly carries" +
	       " a Minstrel's lute.\n";
    }
}
