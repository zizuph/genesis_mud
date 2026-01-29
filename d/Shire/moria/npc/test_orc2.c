/* 2007/04/29 Last update
 * 2011/07/19 Lavellan - Removed "extra" adjectives supplied by orcmaker
                       - Replaced big define with array...
                       - Fixed adjectives to all be single words, no spaces
                       - Fixed order of adjs and replaced one odd set
                       - Fixed typo (hideos) and mixture of he/it (all it now)
                       - Added appearance (no more handsome hideous orcs..)
                       - But why the names, they never introduce?
                       - And why "test_orc"? Was this never finished?
 */

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/orcmaker/orcmaker.h"

inherit "/d/Shire/orcmaker/orcmaker";

#define ORC_ARM_DIR "/d/Shire/moria/arm/"
#define ORC_WEP_DIR "/d/Shire/moria/wep/"

//#define ORC_LAIR MINES_DIR + "orc_lair"

#define RNAMES ({\
    "tharburz", "frushkul", "shakh", "aarshlut", "tharguz", \
    "muzgaash", "durgaz", "bishuk", "fotkurz", "narnulubat",\
    "glob", "lugburzum", "lughorn", "nurzum", "brogud",\
    "ashbarzg", "daruk", "nurzum", "dargum", "skrithurz",\
    "barkash", "durgaz", "ulkurz", "lagurz", "garshuk"\
})

/*#define RADJ ({ \
"large black-eyed", "skinny hideous", "long-armed evil", "grey-skinned pale", "large club-footed",\
"large fanged", "grim pale", "grinning brutal", "dull-witted terrible", "squat broad",\
"dark-skinned swarthy", "large wide mouthed", "flat-nosed sallow skinned", "deadly flat-nosed","hideous warring",\
"squint-eyed flat-nosed", "large brutal", "cruel pale", "repulsive squat", "red squint-eyed broad",\
"hideous brutal", "terrible black-eyed", "savage black-skinned", "large black", "leering squint-eyed"})
*/

mixed * radj = ({
({"large", "black-eyed"}), ({"skinny", "hideous"}), ({"long-armed","evil"}),
({"grey-skinned", "pale"}), ({"large", "club-footed"}), ({"large", "fanged"}),
({"grim", "pale"}), ({"dull-witted", "terrible"}), ({"squat", "broad"}),
({"dark-skinned", "sharp-fanged"}), ({"dark-skinned", "swarthy"}), ({"large", "wide-mouthed"}),
({"flat-nosed", "sallow-skinned"}), ({"deadly", "flat-nosed"}), ({"hideous", "warring"}),
({"squint-eyed", "flat-nosed"}), ({"large", "brutal"}), ({"cruel", "pale"}),
({"repulsive", "squat"}), ({"squint-eyed", "broad"}), ({"hideous", "brutal"}),
({"terrible", "black-eyed"}), ({"savage", "black-skinned"}), ({"large", "black"}),
({"leering", "squint-eyed"}) });


#define RLONG ({ \
    "has black eyes and is tall.",\
    "looks skinny and hideous.",\
    "looks evil and has long arms.",\
    "looks pale and grey-skinned.",\
    "looks large and has club feet.",\
    "has large, dripping fangs and is tall.",\
    "has a grim look on his pale face.",\
    "looks dim-witted but terrible.",\
    "looks squat and broad.",\
    "has dark skin and has sharp fangs.",\
    "has dark skin and looks terrible with its dripping fangs.",\
    "has a wide mouth and is very tall.",\
    "has a flat nose and sallow skin.",\
    "looks deadly and has a flat nose.",\
    "looks hideous and ready to attack anything.",\
    "has squint eyes and a flat nose.",\
    "looks very tall and very brutal.",\
    "has pale skin and appears cruel.",\
    "looks repulsive and squat.",\
    "looks tall and has red, squinting eyes.",\
    "looks hideous and brutal.",\
    "has black eyes and looks terrible.",\
    "has black skin and looks savage.",\
    "looks tall and has black skin.",\
    "looks leering with squint eyes.",\
})

int orc_num = random(24);

void
//create_orc()
create_orc()
{
    add_name("soldier");
    remove_adj(query_adjs());
    add_adj(({ radj[orc_num][0], radj[orc_num][1] }));
    set_long("This is a "+radj[orc_num][0] + " " + radj[orc_num][1]+" orc " +
        "soldier. It is one of the orcs from the Mines of Moria. From the "+
        "sign on its shield, it is from the tribe of the Red Claw. It "+
        RLONG[orc_num] + " It looks very evil.\n");
    set_title("Vicious Clan Member of the Red Claw");
    set_appearance(35);


    /*
    set_living_name(RNAMES[orc_num]);
    set_name(({RNAMES[orc_num], "soldier", "_orc_soldier_"}));
    set_pname("soldiers");
    add_adj(RADJ[orc_num]);
    set_short(RADJ[orc_num] + " orc");
    add_adj("orc");
    set_race_name("orc");
    set_long("This is a "+RADJ[orc_num]+" orc soldier. It is one of the orcs " +
        "from the Mines of Moria. From the sign on its shield, it is " +
        "from the tribe of the Red Claw. He "+RLONG[orc_num]+" He looks very evil.\n");
    set_title("Vicious Clan Member of the Red Claw");
    */

    set_type(MORIA_ORC);
    set_power(200);

//    set_long(0);
//    set_title("the Notorious Hobbitmaker of the Shire");

}
/*
void
arm_orc()
{
    setuid(); seteuid(getuid());
    clone_object(ORC_ARM_DIR+"hauberk")->move(TO);
    clone_object(ORC_WEP_DIR+"orcscim")->move(TO);
    command("wield all");
    command("wear all");
}
*/