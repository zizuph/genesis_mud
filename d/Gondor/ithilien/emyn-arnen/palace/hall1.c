inherit "/d/Gondor/common/room";

#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/ithilien/emyn-arnen/arnen_defs.h"

#define  GHALL		(ITH_DIR + "emyn-arnen/palace/ghall")

void
create_room()
{
    set_short("The entrance hall of the House of the Stewards in Emyn Arnen");
    set_long(BSN("This is the entrance hall of the House of the Stewards "
      + "in Emyn Arnen. To the north is a large archway leading out onto "
      + "the road, while a passage leads south into another hall and "
      + "a corridor branches off to the west."));

    add_exit(ITH_DIR + "emyn-arnen/vrd4",          "north", 0, 1);
    add_exit(GHALL,                                "south", 0, 1);
    add_exit(ITH_DIR + "emyn-arnen/palace/sqcorr", "west",  0, 1);

    add_item(({"archway", "gate", "hinges", "door", "entrance"}), BSN(
        "A large archway is leading out of the building onto the "
      + "road to the north. The large hinges on which the wings of the "
      + "gate once hung can still be seen at the sides of the archway, "
      + "but of the gate itself there remains nothing."));

    add_item(({"hall", "entrance hall", }), BSN(
        "This is a large hall just inside the House of the Stewards. "
      + "The vaulted roof rests on two large stone pillars. Pillars, "
      + "roof and walls were made from stone blocks hewn from the same "
      + "rock of light grey colour. Exits lead north through an archway "
      + "back onto the road, south into another hall, and west "
      + "into a corridor."));

    PALACE_WALLS
    PALACE_FLOOR
    PALACE_PILLARS
    PALACE_ROOF
    PALACE_STONES

    add_item(({"corridor", }), BSN(
        "The corridor is leading west into what probably once were the "
      + "servant quarters of the house."));

    add_item(({"passage", "other hall", "second hall", }), "@@exa_passage@@");

    FIX_EUID
    GHALL->load_me();
}

int
filter_living(object x) { return living(x); }

int
random_filter(object x, int a)
{
    return (random(100) < a);
}

string *
query_a_race(object * x)
{
    int     i,
            mh = TP->query_prop(CONT_I_HEIGHT),
            hh;
    string *s = ({}),
            size;

    for (i = 0; i < sizeof(x); i++)
    {
        if ((hh = x[i]->query_prop(CONT_I_HEIGHT)) < mh/2)
            size = "tiny ";
        else if(hh < (( 90 * mh)/100))
            size = "small ";
        else if(hh < ((110 * mh)/100))
            size = "normal ";
        else if(hh < ((150 * mh)/100))
            size = "large ";
        else if(hh < ((200 * mh)/100))
            size = "very large ";
        else
            size = "giant ";
        s += ({ LANG_ADDART(size)+x[i]->query_race_name() });
    }

    return s;
}

string
exa_passage()
{
    object *npcs,
            ghall = find_object(GHALL);
    string  desc = "The passage is leading south into a second hall. ";

    if (objectp(ghall))
        npcs = filter(all_inventory(ghall), "filter_living", TO);
    npcs = filter(npcs, "random_filter", TO, TP->query_skill(SS_AWARENESS));

    if (!sizeof(npcs))
        desc += "In the impenetrable darkness beyond the passage, "
          + "you cannot make out what is waiting for you there.";
    else
        desc += "There you can make out the shadows of "
          + COMPOSITE_WORDS(query_a_race(npcs)) +".";

    return BSN(desc);
}

