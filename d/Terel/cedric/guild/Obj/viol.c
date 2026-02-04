inherit "/d/Terel/cedric/guild/obj/instrument";

#define VIOL_FIX ({"viol_string",\
      "viol_bow", \
      "viol_bridge",\
      "viol_tuning_pegs",\
      "viol_big"})

public void
create_instrument()
{
    set_damage_desc(({ "is missing an A-string",
                       "has a loose and warped bow",
                       "has a splintered and collapsed bridge",
                       "has lost all its tuning-pegs",
                       "has its fingerboard completely cracked off" }));

    set_name("viol");
    set_short("fine Minstrel's viol");
    set_long(
            "This dark spruce-wood instrument is roughly two " +
            "feet in length. The sounding-box has a flat back " +
            "and rounded shoulders which curve inward and then " +
            "out again to round off at the bottom. Six strings, " +
            "tuned in fourths and thirds, stretch over the bridge, "+
            "up a fretted fingerboard, and are held by tuning-pegs "+
            "at the top of the neck. A bow, held with palm " +
            "upward, is drawn across the strings to produce sound." +
            "  While playing the viol, the instrument may be rested "+
            "on the knee or pressed against the arm and shoulder." +
            "  Twin fresco-like paintings, depicting " +
            holder->query_muse_name()+ ", your Muse, adorn the " +
            "sounding-box, beneath resonating C-shaped holes. " +
            "You may inspect your viol to assess its state of " +
            "tuning and general repair.\n");
}

public string
show_instrument_subloc(object carrier, object for_obj)
{
    if (carrier == for_obj)
    {
        return "Your Minstrel's viol is alive with music and " +
               "dedicated to "+ TP()->query_muse_name() + ".\n";
    }
    else
    {
        return capitalize(carrier->query_pronoun()) + " proudly carries" +
               " a Minstrel's viol.\n";
    }
}
