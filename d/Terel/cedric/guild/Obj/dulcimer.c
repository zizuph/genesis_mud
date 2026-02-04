inherit "/d/Terel/cedric/guild/obj/instrument";

#define DULCIMER_FIX ({"dulcimer_string",\
      "dulcimer_hammer",\
      "dulcimer_tuning_peg",\
      "dulcimer_bridge",\
      "dulcimer_big"})

public void
create_instrument()
{
    set_damage_desc(({ "has a broken string",
                       "is without one of its hammers",
                       "has lost several tuning-pegs",
                       "has a warped bridge",
                       "is broken completely in half"}));

    set_short("carefully crafted Minstrel's dulcimer");
    set_long(
            "This beautiful dulcimer has been crafted from a " +
            "large, trapezoidally shaped piece of white ash wood. " +
            "Two octaves of silvery strings, in double courses, " +
            "are suspended across the width of " +
            "the instrument. These strings weave intricately over " +
            "two central bridges at different lengths to produce " +
            "different pitches. Between the two central bridges " +
            "a silhouette has been painted, an image of " +
            holder->query_muse_name()+ ", the Muse to whom this " +
            "dulcimer was dedicated. Two hammers are kept in a " +
            "small compartment on the dulcimer's back. You may " +
            "inspect your " +
            "dulcimer to assess its state of tuning and general " +
            "repair.\n");
}

public string
show_instrument_subloc(object carrier, object for_obj)
{
    if (carrier == for_obj)
    {
        return "Your Minstrel's dulcimer is alive with music and " +
               "dedicated to " + carrier->query_muse_name() + ".\n";
    }
    else
    {
        return capitalize(carrier->query_pronoun()) + " proudly carries" +
               " a Minstrel's dulcimer.\n";
    }
}
