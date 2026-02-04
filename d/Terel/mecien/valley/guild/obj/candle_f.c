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
    set_healing_type(2);
    set_adj("green");
    set_candle_long("This slender candle is deep green in color. " +
            "The wax looks ancient, and the bottom part of the " +
            "candle is wrapped with a piece of parchment. There are " +
            "some letter on the parchment. Despite the " +
            "the small and ancient writing style you read: " +
            "For those who want to still their hunger.");
    set_heal_msg("The mild incense of the green candle fills your " +
                 "entire body. You feel less tired.\n");
    set_other_msg("The pleasant smell of the candle fills your " +
                  "senses, but there is something unsatifying about " +
                  "it. It is as if a certain bliss is in reach, but " +
                  "not to be granted to you today.\n");
}
