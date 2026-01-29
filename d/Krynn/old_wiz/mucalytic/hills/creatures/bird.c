/* A tweety bird. ~mucalytic/hills/creatures/bird */

inherit "/std/monster";
inherit "/std/creature";
inherit "/std/combat/unarmed";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

int flying = 0; // Is the bird flying?

#define ATT_WING1       0
#define ATT_WING2       1
#define ATT_BEAK        2

#define HIT_BODY        0
#define HIT_HEAD        1
#define HIT_WING1       2
#define HIT_WING2       3

#define BIRD_ADJS ({ "red-breasted", "white-breasted", "yellow-beaked", \
                     "long-beaked", "speckle-winged", "stubby-tailed", \
                     "long-tailed", "white-feathered", "ruffled-feathered", \
                     "speckle-feathered", "short-beaked", "speckle-breasted" })

void create_creature()
{
    set_name("bird");
    set_pname("birds");
    set_race_name("bird");
    set_gender(random(2));
    set_alignment(random(100));
    set_adj(BIRD_ADJS[random(sizeof(BIRD_ADJS))]);
    set_long("A cute little bird tweeting and singing. Its song fills you "+
        "with joy and makes you feel on top of the world.\n");

    set_stats(({ (1 + random(3)),     /* str */
                 (3 + random(4)),     /* dex */
                 (1 + random(3)),     /* con */
                 (2 + random(3)),     /* int */
                 (3 + random(3)),     /* wis */
                 (1 + random(3)) })); /* dis */

    set_hp(10000);

                    /* Att_id     Hit Pen  Dam_type      %  Att_string */
    set_attack_unarmed(ATT_WING1,   6,  5,  W_BLUDGEON, 20, "left wing");
    set_attack_unarmed(ATT_WING2,   6,  5,  W_BLUDGEON, 20, "right wing");
    set_attack_unarmed(ATT_BEAK,    9,  9,  W_IMPALE,   60, "beak");

                    /* Hit_id     Ac   %  Hit_string */
    set_hitloc_unarmed(HIT_BODY,   3, 40, "body");
    set_hitloc_unarmed(HIT_HEAD,   2, 10, "head");
    set_hitloc_unarmed(HIT_WING1,  2, 25, "left wing");
    set_hitloc_unarmed(HIT_WING2,  2, 25, "right wing");

    add_prop(OBJ_M_NO_ATTACK, "@@can_attack_bird");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_WEIGHT, 12000);
    add_prop(CONT_I_HEIGHT, 10);

    set_act_time(random(10));
    add_act("emote cocks its head at you.");
    add_act("emote whistles merrily.");
    add_act("emote chirps tunefully.");
    add_act("emote @@air_ground@@.");
    add_act("emote @@fly_land@@.");
}

string air_ground()
{
    int ran;

    ran = random(4);

    if(flying)
    {
        switch(ran)
        {
            case 0:
                return("swoops through the air above you");
            case 1:
                return("glides through the air");
            case 2:
                return("flies round in circles above you");
            case 3:
                return("squarks at you as it flies past");
        }
    }
    else
    {
        switch(ran)
        {
            case 0:
                return("roots around in the ground, looking for worms");
            case 1:
                return("hops around aimlessly");
            case 2:
                return("chirps hungrily");
            case 3:
                return("turns its head this way and that");
        }
    }
}

string fly_land()
{
    if(flying)
    {
        flying = 0;
        remove_prop(LIVE_S_SOULEXTRA);
        remove_prop(LIVE_S_EXTRA_SHORT);
        return("falls groundwards before landing gracefully");
    }
    else
    {
        flying = 1;
        add_prop(LIVE_S_EXTRA_SHORT, " (flying)");
        add_prop(LIVE_S_SOULEXTRA, "flying up in the air.");
        return("flaps "+POSSESSIVE(TO)+" wings hard and takes off in a "+
            "flurry of feathers");
    }
}

mixed can_attack_bird()
{
    if(flying)
        return("You try to attack the bird but fail, since "+PRONOUN(TO)+" "+
             "is flying out of reach in the sky above you.\n");
    else
        return 0;
}
