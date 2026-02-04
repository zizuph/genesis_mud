/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
/*
 *  Mystic healing candle, type = 0  -> healing hp
 *                         type = 1  -> healing mana
 *                         type = 2  -> healing fatigue
 *  see the inherit file for more info
 *  Mortricia 960502 (based on Cedric's old candle)
 */
inherit "/d/Terel/mecien/valley/guild/obj/std_candle";

public void
create_candle()
{
    set_healing_type(1);
    set_adj("blue");
    set_candle_long("This delicate taper is a deep azure in color. " +
            "A strip of metallic foil, bearing a strange seal " +
            "resembling an intricate silver star, is wrapped " +
            "around the bottom of the candle. The wax smells " +
            "somehow of mystery and knowledge, of ancient texts " +
            "and mystic runes.");
    set_heal_msg("The pungent incense of the candle fills your " +
                 "senses and clears your mind.\n");
    set_other_msg("The pleasant smell of the candle fills your " +
                  "senses, but there is something unsatifying about " +
                  "it. It is as if a certain bliss is in reach, but " +
                  "not to be granted to you today.\n");
}
