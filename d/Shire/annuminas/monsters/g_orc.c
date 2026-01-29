#include "/d/Shire/sys/defs.h"
#include "/d/Shire/orcmaker/orcmaker.h"

inherit "/d/Shire/orcmaker/orcmaker";

#define RNAMES ({\
    "tharburz", "frushkul", "shakh", "aarshlut", "tharguz", \
    "muzgaash", "durgaz", "bishuk", "fotkurz", "narnulubat",\
    "glob", "lugburzum", "lughorn", "nurzum", "brogud",\
    "ashbarzg", "daruk", "nurzum", "dargum", "skrithurz",\
    "barash", "durgaz", "ulkurz", "lagurz", "garshuk"\
})

#define RADJ ({ \
    "large black-eyed", "skinny hideous", "long-armed evil",\
    "grey-skinned pale", "large club-footed", "large fanged",\
    "grim pale", "grinning brutal", "dull-witted terrible",\
    "squat broad", "dark-skinned swarthy", "large wide mouthed",\
    "flat-nosed sallow skinned", "deadly flat-nosed",\
    "hideous warring", "squint-eyed flat-nosed", "large brutal",\
    "cruel pale", "repulsive squat", "red squint-eyed broad",\
    "hideous brutal", "terrible black-eyed", "savage black-skinned",\
    "large black", "leering squint-eyed"})

#define RLONG ({ \
    "has black eyes and is tall.",\
    "looks skinny and hideos.",\
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
    "has black skin and looks savage",\
    "looks tall and has black skin.",\
    "looks leering with squint eyes.",\
})

int orc_num = random(24);

void
create_orc()
{
    set_living_name(RNAMES[orc_num]);
    set_name(({RNAMES[orc_num], "soldier", "_orc_soldier_"}));
    set_pname("soldiers");
    add_adj(RADJ[orc_num]);
    set_short(RADJ[orc_num] + " orc");
    add_adj("orc");
    set_race_name("orc");
    set_long("This is a "+RADJ[orc_num]+" orc guard. It is one of " +
        "the orcs from the Misty Mountains, and from the looks of it, " +
        "the orc seems to be from the tribe of the Black Cave. He " + 
        RLONG[orc_num]+" He looks very evil.\n");
    set_title("Vicious Member of the Black Cave tribe");

    set_type(GUARD);
    set_power(35 + random(10));
    set_random_move(8);
    set_restrain_path("/d/Shire/annuminas");
    

}

