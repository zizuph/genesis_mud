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
    set_healing_type(0);
    set_adj("thin");
    set_candle_long("This thin candle is so white as to be almost " +
            "translucent. A strip of metallic foil, bearing a strange " +
            "seal resembling an intricate silver star, is wrapped " +
            "around the bottom of the taper. The wax smells of " +
            "wild rosebuds, and deep green forests, and misty sea " +
            "shores, and myriad other pleasant scents whose exact " +
            "nature eludes you.");
    set_heal_msg("The pleasant smell of the candle fills your " +
                 "senses, and has, you suspect, a salutory effect " +
                 "on your health as well.\n");
    set_other_msg("The pleasant smell of the candle fills your " +
                  "senses, but there is something unsatifying about " +
                  "it. It is as if a certain bliss is in reach, but " +
                  "not to be granted to you today.\n");
}
