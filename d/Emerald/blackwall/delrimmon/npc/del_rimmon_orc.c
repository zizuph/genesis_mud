/*
 *  /d/Emerald/blackwall/delrimmon/npc/del_rimmon_orc.c
 *
 *  This is the standard file for Orcs in the Del Rimmon area.
 *
 *  Copyright (c) October 1997, Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/npc/blackwall_orc";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"
#include "/d/Emerald/sys/paths.h"

#define DR_WEP   (DEL_RIMMON_DIR + "obj/wep/")
#define DR_ARM   (DEL_RIMMON_DIR + "obj/arm/")
#define    ELITE        ( ({ DR_WEP + "wr_sword", \
                             DR_WEP + "r_axe", \
                             DR_WEP + "d_sword", \
                             DR_WEP + "shad_axe", \
                             DR_WEP + "osword" \
                        }) )

#define WEP_ARRAY1 \
    ({DR_WEP + "longsword", DR_WEP + "spear", DR_WEP + "dagger" })
#define WEP_ARRAY2 ({DR_ARM + "shield" })
#define ARM_ARRAY1 ({DR_ARM + "chainmail" })
#define ENEMY_ALIGNMENT    200

/* global variables */
static int     Chief;   /* is this orc a Chief? */
static string *Wep1,    /* arrays to define the armament of the npc */
              *Wep2,
              *Arm1;
static int     Attack_Id;
static int     Wimpy_Run;

/* prototypes */
public void    create_del_rimmon_orc();
nomask void    create_blackwall_orc();
public string  alignlook();
public string  describe();
public void    set_arm_arrays();
public varargs void    arm_me(int cc = 10, int sc = 5);

public int     query_chief() { return Chief; }


/*
 * Function name:        create_del_rimmon_orc
 * Description  :        dummy routine for inheritance purposes
 */
public void
create_del_rimmon_orc()
{
} /* create_del_rimmon_orc */

/*
 * Function name:        create_blackwall_orc
 * Description  :        set up the npc, with area presets
 */
nomask void
create_blackwall_orc()
{
    int     rnd = random(51),
            rnd1 = random(61),
            rnd2 = random(61),
            rndchief;

    if (!random(6))
    {
        Chief = 1;
    }

    add_name("soldier");
    add_name("_del_rimmon_orc");
    add_adj(alignlook());
    remove_adj("orc");
    remove_adj("orcish");

    set_race_name("orc");

    create_del_rimmon_orc();

    if (Chief)
    {
        rndchief = 30 + rnd1;
        set_name("orc chieftain");
        set_short(implode(query_adjs(), " ")+ " orc chieftain");
        set_pshort(implode(query_adjs(), " ")+ " orc chieftains");
        set_pname("orc chieftains");
        add_name("orc");
        add_name("chieftain");
        set_long(describe() + "He seems to be some kind of"
          + " chieftain.\n");
    set_stats( ({ 100+random(50), 100+random(50), 120+random(40),
                  60+random(60),  40+random(80),  120+random(20) }) );
    }

    else
    {
        rndchief = rnd2;
        set_name("orc");
        set_short(implode(query_adjs(), " ")+ " orc");
        set_pshort(implode(query_adjs(), " ")+ " orcs");
        set_pname("orcs");
        set_long(describe());
    set_stats( ({ 65+random(35), 65+random(35), 70+random(30),
                  40+random(60), 20+random(80), 100+random(20) }) );
    }

    set_alignment(-300 + (-10 * rnd));

    add_prop(CONT_I_HEIGHT,   180 + rndchief / 2);
    add_prop(CONT_I_WEIGHT, 75000 + rndchief * 500);
    add_prop(CONT_I_VOLUME, 70000 + rndchief * 500);    
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop("_live_i_del_rimmon_orc", 1);

    FIX_EUID
} /* create_blackwall_orc */

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

    if (this_object()->id("akugla"))
    {
        weapon = clone_object(ONE_OF_LIST(ELITE))->move(TO);
        clone_object(DR_ARM + "bone_shield")->move(TO);

        this_object()->command("$wield all");
        this_object()->command("$wear all");
        return;
    }

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
        clone_object(DR_ARM + "shoes")->move(TO);
    }

    if (Chief)
    {
        clone_object(DR_ARM + "helmet")->move(TO);
    }

    command("wield all");
    command("wear all");
} /* arm_me */
