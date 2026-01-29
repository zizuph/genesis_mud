/*
 *  /d/Gondor/rohan/isengard/npc/wh_orc.c
 *
 *  This is the standard file for Orcs from Isengard.
 *
 *  Copyright (c) October 1997, Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Gondor/rohan/isengard/npc/isengard_npc.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/isengard/defs.h"

#define WH_WEP   (ISEN_DIR + "wep/")
#define WH_ARM   (ISEN_DIR + "arm/")
#define WEP_ARRAY1 \
    ({WH_WEP + "wh_longsword", WH_WEP + "wh_spear", WH_WEP + "wh_knife" })
#define WEP_ARRAY2 ({WH_ARM + "wh_shield" })
#define ARM_ARRAY1 ({WH_ARM + "wh_chainmail" })

/* global variables */
static int     Uruk;    /* is this orc an Uruk? */
static string *Wep1,    /* arrays to define the armament of the npc */
              *Wep2,
              *Arm1;

/* prototypes */
public void    create_isengard_orc();
nomask void    create_isengard_npc();
public string  alignlook();
public string  describe();
public void    set_arm_arrays();
public varargs void    arm_me(int cc = 10, int sc = 5);
public void    add_isengard_emotes();

public int     query_uruk() { return Uruk; }


/*
 * Function name:        create_isengard_orc
 * Description  :        dummy routine for inheritance purposes
 */
public void
create_isengard_orc()
{
} /* create_isengard_orc */

/*
 * Function name:        create_isengard_npc
 * Description  :        set up the npc, with isengard presets
 */
nomask void
create_isengard_npc()
{
    int     rnd = random(11),
            rnd1 = random(21),
            rnd2 = random(21),
            rnduruk;

    if (!random(6))
    {
        Uruk = 1;
    }

    add_name("soldier");
    add_name("_isengard_orc");
    add_adj(alignlook());

    set_race_name("goblin");

    create_isengard_orc();

    if (Uruk)
    {
        rnduruk = 30 + rnd1;
    }

    else 
    {
        rnduruk = rnd2;
    }

    if (Uruk)
    {
        set_name("uruk");
        set_short(implode(query_adjs(), " ")+ " uruk");
        set_pshort(implode(query_adjs(), " ")+ " uruk-hai");
        set_pname("uruk-hai");
    }

    else
    {
        set_name("orc");
        set_short(implode(query_adjs(), " ")+ " orc");
        set_pshort(implode(query_adjs(), " ")+ " orcs");
        set_pname("orcs");
    }

    set_long(describe());

    if (Uruk)
    {
        default_config_npc(70 + rnduruk);
    }
    else
    {
        default_config_npc(65 + (rnd1+rnd2)/4);
    }

    set_alignment(-300 + (-10 * rnd));

    set_base_stat(SS_STR,      65 + rnduruk);
    set_base_stat(SS_DIS,      95 + rnduruk);
    set_base_stat(SS_INT,      50 + random(rnduruk));
    set_base_stat(SS_WIS,      50 + random(rnduruk));

    set_skill(SS_AWARENESS,    25+rnd);
    set_skill(SS_CLIMB,        45+rnd);
    set_skill(SS_SWIM,         45+rnd);
    set_skill(SS_DEFENCE,      25+rnd);
    set_skill(SS_WEP_KNIFE,    70 + rnduruk - 10);
    set_skill(SS_WEP_SWORD,    75 + rnduruk / 3);
    set_skill(SS_WEP_POLEARM,  70 + rnduruk / 2);
    set_skill(SS_PARRY,        70 + rnduruk / 2);
    set_skill(SS_DEFENCE,      70 + rnduruk / 2);

    add_prop(CONT_I_HEIGHT,   180 + rnduruk / 2);
    add_prop(CONT_I_WEIGHT, 75000 + rnduruk * 500);
    add_prop(CONT_I_VOLUME, 70000 + rnduruk * 500);    
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop("_live_i_isengard_orc", 100);

    FIX_EUID
} /* create_isengard_npc */

/*
 * Function name:        alignlook
 * Description  :        provides a random adjective for the npc
 * Arguments    :        none
 * Returns      :        str -- one from the list of adjectives
 */
public string
alignlook()
{
    return ONE_OF_LIST(
        ({"filthy", "black-skinned", "foul-smelling",
          "limping", "six-fingered", "black-toothed",
          "fast-moving", "hunchbacked", "bow-legged",
          "injured", "broad-backed", "battle-scarred"}));
} /* alignlook */

/*
 * Function name:        describe
 * Description  :        based on the adjective given to this orc,
 *                       we provide a nice long description
 * Arguments    :        none
 * Returns      :        str -- the long description for the npc
 */
public string
describe()
{
    switch(query_adj())
    {
        case "filthy":
            return(BSN("Filth and refuse cover this disgusting creature."
              + " Glaring at its environs, it appears to be displeased"
              + " about something."));
            break;
        case "black-skinned":
            return(BSN("Below what it is wearing, this orc has a skin so"
              + " black that it makes surrounding colours seem much"
              + " brighter. Its eyes, a dull white, glow with hatred."));
            break;
        case "foul-smelling":
            return(BSN("The stench which wafts from this orc is completely"
              + " vile, as if to suggest that this creature had been"
              + " wallowing in its own refuse. The look in its eyes makes"
              + " clear the foul personality which accompanies the smell."));
            break;
        case "limping":
            return(BSN("One of this orc's legs seems to be stunted somewhat,"
              + " forcing the creature to walk with a pronounced limp. He"
              + " is peering bitterly at his environs."));
            break;
        case "six-fingered":
            return(BSN("The left hand of this orc clearly displays an odd"
              + " configuration of not five, but six gnarled fingers."
              + " Undoubtedly, this creature is the result of some foul"
              + " breeding process gone awry."));
            break;
        case "black-toothed":
            return(BSN("The hideous grin of this creature reveals many"
              + " gnarled and broken teeth, all of which are coated with"
              + " some form of black substance. From the appearance of"
              + " things, it would seem as if this vile creature had been"
              + " gnawing on charcoal."));
            break;
        case "fast-moving":
            return(BSN("Though calm and still most of the time, this"
              + " particularly dangerous looking orc will occasionally"
              + " make a sudden movement in seemingly random directions."
              + " It is almost as if he is testing the area for hidden"
              + " enemies."));
            break;
        case "hunchbacked":
            return(BSN("Bent and horribly stooped toward the ground,"
              + " this unfortunate orc seems to suffer from a nearly"
              + " crippling form of spinal irregularity. A large hump"
              + " rises on his back where one might expect a head to"
              + " emerge above the shoulders, while his neck and head"
              + " protrude well below what would be considered normal."));
            break;
        case "bow-legged":
            return(BSN("This stocky orc is perhaps one of the rare"
              + " members of its race with skill in horse riding, or"
              + " at least it would appear that way based on the bow-"
              + "legged look of his standing posture. He is snarling,"
              + " and peering from side to side."));
            break;
        case "injured":
            return(BSN("Blood stains the side of this cruel looking"
              + " orc, and it would appear that he suffers from some"
              + " form of puncture wound, perhaps by an arrow, below"
              + " his left ribcage. The gritted teeth and furrowed brow"
              + " in his expression betray the fact that he is in pain."));
            break;
        case "broad-backed":
            return(BSN("With long arms reaching almost to the ground,"
              + " this extremely broad-backed orc has the build of a"
              + " medium sized gorilla. The look of stupidity on his"
              + " face does not make him appear any less dangerous."));
            break;
        case "battle-scarred":
            return(BSN("Scars of battle cover the face and limbs of this"
              + " particularly hardy looking orc soldier. There is a"
              + " patient and cunning look in his eyes, behind which"
              + " smoulders an unmistakable hatred."));
            break;
        default:
            return(BSN("Gnarled and filthy, this orc soldier leers at"
              + " its surroundings, perhaps searching for something to"
              + " torture or kill."));
            break;
    }

    return "";
} /* describe */

/*
 * Function name:        set_arm_arrays
 * Description  :        allows us to set individual arrays in
 *                       this and inheriting files
 */
public void
set_arm_arrays()
{
    Wep1 = WEP_ARRAY1;
    Wep2 = WEP_ARRAY2;
    Arm1 = ARM_ARRAY1;
} /* set_arm_arrays */

/*
 * Function name:        arm_me
 * Description  :        give the npc armour and weapons
 */
public varargs void
arm_me(int cc = 10, int sc = 5)
{
    object  weapon;

    /* ok... this is the lame old way... fix it! */
    MONEY_MAKE_CC(cc + random(cc))->move(TO);
    MONEY_MAKE_SC(sc + random(sc))->move(TO);

    set_arm_arrays();

    if (sizeof(Wep1))
    {
        (weapon = clone_object(ONE_OF_LIST(Wep1)))->move(TO);
    }

    if ((weapon->query_hands() != W_BOTH) && sizeof(Wep2))
    {
        clone_object(ONE_OF_LIST(Wep2))->move(TO);
    }

    if (sizeof(Arm1))
    {
        clone_object(ONE_OF_LIST(Arm1))->move(TO);
        clone_object(ISEN_DIR + "arm/wh_shoes")->move(TO);
    }

    if (Uruk)
    {
        clone_object(ISEN_DIR + "arm/wh_helmet")->move(TO);
    }

    command("wield all");
    command("wear all");
} /* arm_me */

/*
 * Function name:        add_isengard_emotes
 * Description  :        we want to overwrite the emotes defined
 *                       in the master, giving these orcs ones
 *                       which relate to their situation
 */
public void
add_isengard_emotes()
{
    set_chat_time(15 + random(15));
    add_chat("Heh... I can't wait till we get orders to march!");
    add_chat("I can't wait to see the look on the faces of those"
           + " riders when we roast their horses, and eat them!");
    add_chat("The Rohirrim don't scare me! I'll cut them down"
           + " to size!");
    add_chat("I say we burn Edoras first... its got the most"
           + " horses!");
    add_chat("Once we've taken that damned Rider Captain, then"
           + " we can do as we please on the plains!");
    add_chat("I've not seen the Worm in days... if he's betrayed"
           + " us, I'll enjoy watching Sharkey fume!");

    set_cchat_time(5 + random(10));
    add_cchat("Taste my black blade, pathetic fool!");
    add_cchat("If there's one thing I can't stand, its you!!");
    add_cchat("Now you've angered me. Soon you'll be dead!");
    add_cchat("My sword needs a scabbard! Your throat will do nicely!");

    set_act_time(15 + random(15));
    add_act("frown");
    add_act("emote tests the weight of his weapon.");
    add_act("emote covers his eyes with his forearm, and"
          + " peers up at the sky.");
    add_act("scratch");

    set_cact_time(2 + random(2));
    add_cact("emote crouches, swinging wildly at you with his weapon!");
    add_cact("shout Die, you worthless maggot!!");
    add_cact("emote spits on you in disgust!");
    add_cact("scream");
} /* add_isengard_emotes */
