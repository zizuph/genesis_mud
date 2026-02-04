inherit "/d/Terel/cedric/guild/obj/instrument";

#define SHAWM_FIX ({"shawm_reed",\
      "shawm_mouthpiece",\
      "shawm_keys",\
      "shawm_water_damage",\
      "shawm_big"})

public void
create_instrument()
{
    set_damage_desc(({"has a dried-out and cracked reed",
                      "has no mouthpiece",
                      "has some rusty and immobile keys",
                      "has sustained heavy water damage",
                      "has a shattered bell"}));
    set_short("beautiful Minstrel's shawm");
    set_long(
            "This shawm is a long conical bore that flares out " +
            "into a two-inch bell. Made of stained walnut wood, it "+
            "may be disassembled into three basic parts: a small " +
            "mouthpiece with double-reed and pirouette, a long " +
            "section with drilled fingerholes, and the bell. " +
            "Three of the lower fingerholes are covered with pads; "+
            "keys maneuver the pads, making the shawm easier to " +
            "play. This is an alto shawm and its range is low, " +
            "rich, and melancholy. Around the circumference of " +
            "the bell, intertwined with a lily flower, is " +
            "the floridly engraved name of your muse, " +
            holder->query_muse_name()+ ". You may inspect your " +
            "shawm to assess its state of tuning and general " +
            "repair.\n");
}

public string
show_instrument_subloc(object carrier, object for_obj)
{
    if (carrier == for_obj)
    {
        return "Your Minstrel's shawm is alive with music and " +
               "dedicated to "+ carrier->query_muse_name() + ".\n";
    }
    else
    {
        return capitalize(carrier->query_pronoun()) + " proudly carries" +
               " a Minstrel's shawm.\n";
    }
}
