/*
*  /d/Sparkle/area/jade/obj/wep/greenwood_bow.c
*  Created 2017-02-22 by Martin Berka on Genesis MUD
*  A bow made from the Jade Forest, and used to keep everything in it at bay.
*  The Forest is very insular. The bow is quite weak - unless:
*  -strung with a forest bowstring, which doubles its strength;
*  -firing forest arrows, x2;
*  -fired by someone with the forest in them (i.e., greenish) - x 2
*  -fired by someone with the forest in them (i.e., greenish) - x 2
*  -fired from the Jade farm attic meeting all prior conditions - automatically
*  hides, better than would be possible with a high Hide skill (min. 20, or
*  SS_HIDE-15).
*  -fired by an expert (Family NPC or completed possible quest, below) -
*  x2 outside the Forest, inside it - total accuracy, instant death to non-
*  non-Family NPC's and 9+% damage to REMAINING player hp (more for larger
*  players, used in Runaway quest gauntlet).
*
*  Originally, a pro-archery reward for bow quest - concept currently abandoned:

Apple: can be worn IF IN ORCHARD; affect appraise/exa. Require simple TS_DEX
to wear. On wearing or on entering a jade_room, apple
(/d/Genesis/start/human/wild2/obj/apple#728066,
/d/Genesis/start/human/wild2/lawn) is shot by an arrow; now "broken", "still
delicious!" but no longer wearable. Causes fear.

If SS_WEP_MISSILE at least the maximum non-guild archery level, now carrying
a note ("you think all this shooting is easy? Come up here and try it
yourself!"). Go to attic. As emphasized there, they are constantly turning wood
into bows and arrows. Make your own. ("bring me the components
and I'll give you one of the finished ones."). Go out into the forest and
search greenwood trees for branches. May need to climb a tree to find one.
Location random by player. Take it to family in attic, receive unstrung bow -
force player to wait two days for the wood to form?
Get a tendon from a corpse (search corpse - sinew should not emerge by itself;
quest will specify arm, leg, or back tendon, but later explain that it doesn't
really matter - "we use them all!") and turn into bowstring. Sharpen some reeds
with a knife. Quest reward -
the bow (quality decreases with time as it has not been treated; player can
trade parts for a fresh one, without the special steps, and get a certain amount
of free arrows from the stacks, once per arma). Plus XP.
*/

#include "../../defs.h"

#include <stdproperties.h>
#include <ss_types.h> //Skills
# include <wa_types.h> //Weapons/wielding

inherit "/std/bow";

/* Global variables */
int true;

/*
 * Function     : create_bow
 * Description  : Construct the bow, unstrung.
 */
public void
create_bow()
{
    set_adj(({"small", "greenwood"}));
    set_short("small greenwood bow");
    set_long("@@bow_description");

    stringed = 0; //User must supply a string.

    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 2750);
    set_hit(40);
    set_pen(58);
}


/*
 * Function     : bow_description
 * Description  : Description should vary depending on stringing.
 * Returns      : (string) Custom description
 */
string
bow_description()
{
    switch (stringed)
    {
        case 0:
            return "This is a shaped, treated branch, recently cut from one of "
            + "the colourful trees of the Jade Forest. It could be made into a "
            + "proper bow if one were to string it with something.\n";
        case 1:
            return "This is a bow made from the coloured wood characteristic "
            + "of the Jade Forest. It shares the same greenish colour, so it "
            + "must have been cut from a living tree.\n";
        case 2:
            return "This bow is made from the wood and flesh of the Jade "
            + "Forest. The limbs are the same green as the trees there, "
            + "indicating that they were cut from a living one. The string is "
            + "made of two strands of dry sinew, twisted together, quite "
            + "inelastic - and faintly green, "
            + "like all creatures that live off the Forest's monochromatic "
            + "vegetation.\n";
    }
}

/*
 * Function name: do_fire
 * Description  : When firing Override of launch_weapon's key firing function to add a
 *          large split-second stat boost to an archer firing the true bow in
 *          its natural environment. TODO - restrict to special arrows.
 */
public void
do_fire()
{
    //Check whether bow is complete and fired in its natural environment
    string this_room_path = file_name(environment(Archer)); //Or Archer_env glob

    if (stringed == 2 && wildmatch(ROOM_DIR + "*", this_room_path))
    {
        int size_factor, dam, percent_hurt;
        if (Target->query_npc())
        {
            dam = Target->query_hp();   //NPC's are killed instantly
            percent_hurt = 100;
        }
        else
        {   //Larger players lose more, since less hindered by direct combat
            size_factor = ftoi(log( itof(Target->query_stat(SS_CON)) ) / 1.3);
            dam = Target->query_hp() * (9 + size_factor) / 100;
            percent_hurt = 100 * dam / Target->query_max_hp();
        }

        if (wildmatch("*attic*", this_room_path)) //Attic conceals very well
        {
            Archer->add_prop(OBJ_I_HIDE, Archer->query_skill(SS_HIDE) - 15);
            did_hit(0, "body", percent_hurt, Target, W_IMPALE, 90, dam);
            Archer->remove_prop(OBJ_I_HIDE);
        }
        else
        {
            did_hit(0, "body", percent_hurt, Target, W_IMPALE, 90, dam);
        }
        if ((int)Target->query_hp() <= 0)
        {
            Target->do_die(Archer);
        }
    }
    else
    {
        ::do_fire();    //Firing without any boost
    }

    /*  //ATTEMPT TO HANDLE PERCENTAGE SHOTS VIA COMBAT SYSTEM
        int normal_str, normal_dex;

        normal_str = Archer->query_stat(0);
        normal_dex = Archer->query_stat(1);
        Archer->set_base_stat(SS_DEX, Target->query_stat(SS_DEX)*2);
        //Need excellent accuracy

        float target_con = itof(Target->query_stat(SS_CON));
        if (target_con > 10.0)
        {
            Archer->set_base_stat(SS_STR, ftoi(target_con * log(target_con) /
                3.0)); //Scale by ~log_20 - trying to match effect of CON on hp
        }

        Archer->set_stat(0, normal_str);
        Archer->set_stat(1, normal_dex);
    */
}

/*
 * Function     : string_bow_hook
 * Description  : Following stringing, check whether string is from Jade Forest
 */
void
string_bow_hook()
{
    if (wildmatch(WEP_DIR + "*", bowstring)) //Bowstring comes from Jade Forest
    {
        stringed = 2; //Strung as it was meant to be.
        this_player()->catch_msg("The sinews of the string seem to grow into "
            + "the wood of the bow like roots.\n");
    }
}
