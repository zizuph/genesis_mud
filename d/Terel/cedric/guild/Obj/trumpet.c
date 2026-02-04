inherit "/d/Terel/cedric/guild/obj/instrument";

#define TRUMPET_FIX ({"trumpet_blocked",\
      "trumpet_rusty",\
      "trumpet_mouthpiece",\
      "trumpet_dented",\
      "trumpet_big"})

public void
create_instrument()
{
    set_damage_desc(({ "is blocked up and needs to be cleaned",
                       "is badly rusted",
                       "needs a mouthpiece",
                       "has been severely dented",
                       "has been pounded almost completely flat"}));

    set_name("trumpet");
    set_short("shiny Minstrel's trumpet");
    set_long(
            "This long and slender trumpet has been fashioned " +
            "out of brass that shines with golden lustre. A silver "+
            "alloy mouthpiece may be detached from the smaller " +
            "end. From the mouthpiece, the bore of the trumpet " +
            "gradually increases in diameter, bending back around " +
            "itself only once and then flaring out into a bell. " +
            "Although the trumpet has no valves or keys, the " +
            "various pitches of the harmonic series may be " +
            "produced by manipulating the shape of the ombouchure " +
            "and pressure of air blown through the mouthpiece. " +
            "This trumpet has been tuned to the fundamental pitch " +
            "of D. The name of your Muse, " +holder->query_muse_name()+
            ", has been inscribed in elaborate silver runes along " +
            "the final section of the instrument. You may inspect " +
            "your trumpet to assess its state of tuning and " +
            "general repair.\n");
}

public string
show_instrument_subloc(object carrier, object for_obj)
{
    if (carrier == for_obj)
    {
        return "Your Minstrel's trumpet is alive with music and " +
               "dedicated to " + TP()->query_muse_name() + ".\n";
    }
    else
    {
        return capitalize(carrier->query_pronoun()) + " proudly carries" +
               " a Minstrel's trumpet.\n";
    }
}
