/*
 *  /d/Gondor/ithilien/road/er7
 *
 *  Modification log:
 *      Alto, 12 August 02. Installed ranger ambush code.
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

public int            move_ranger();
public string         exa_bushes();

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("forest");
    set_area("central eastern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The long straight road continues east towards a ring of trees, "+
    "while it starts sloping down into the west here. Green "+
    "and fair forests stretch out as far as you can see to the north and "+
    "beyond the foul-reeking stream to the south. "+
    "The eastern horizon is dominated by the grey and ominous mountains "+
    "that marks the border to Mordor, and within the grey mass, not far "+
    "away now, you see a dark cleft.");
  add_item(({"mountains","mountain-range","mountain","ephel duath"}),
    "The mountains named Ephel Duath appear to be dark grey from here.\n"+
    "You judge the mountains to be between 5000 to 7000 feet tall,\n"+
    "and you guess they are only about 3 kilometers away now.\n");
  add_item("cleft","You don't see much of it from this distance; it is a deep\n"+
    "gulf of shadow, and whatever is in there lies hidden in the darkness.\n"+
    "Your guess is that this is the Imlad Morgul, the Valley of Dark Sorcery.\n");
  add_item("road","The long straight road starts sloping down to the west,\n"+
    "while it continues towards a belt of trees you can see further east.\n"+
    "The road is well crafted, cobbled with stones and lined with high banks,\n"+
    "going in a straight line east and west.\n");
  add_item(({"trees","ring of trees","belt of trees"}),
    "Not far ahead to the east, looming up like a black wall, you see a\n"+
    "belt of trees, vast of size, very ancient, and placed in a ring.\n");
  add_item(({"forest","forests","woods","flowers"}),
    "The forests of Ithilien are lovely to look upon, consisting of small\n"+
    "woods of resinous trees, fir and cedar and cypress, oaks and ash-trees,\n"+
    "and among them grows bushes of olive and of bay, junipers and myrtles,\n"+
    "and beautiful sage flowers and marjorams and parsleys, asphodels and lilies.\n");
  add_item(({"river","morgulduin","stream"}),
    "The Morgulduin runs from the accursed Morgul valley, and is\n"+
    "dark and foul to look upon, and there is a wrenching smell from it.\n");
    add_item(({"bush", "bushes"}), &exa_bushes());
    add_cmd_item(({"bush", "bushes", "the bush", "the bushes"}),
        "enter", &move_ranger());

  add_exit(ITH_DIR + "road/crossroads", "east", 0, 2);
  add_exit(ITH_DIR + "road/er6",        "west", 0, 2);

  reset_room();
}

string
exa_bushes()
{
    if(!RANGERS_MEMBER(TP))
    {
        return"The bushes line the road on both sides.\n";
    }

    return"The bushes are bent in such a way that you recognize "
        + "a secret ranger mark. You may enter the bushes unobserved if you "
        + "are stealthy.\n";
}

int
move_ranger()
{
    if(!RANGERS_MEMBER(TP))
    {
        NF0("The bushes seem far too tangled to enter.\n");
    }

    if(!TP->query_autosneak())
    {
        NF0("You look nervously around, realizing that you are far "
            + "too exposed to do that safely.\n");
    }

    write("With as much stealth as possible, you slip through the bushes.\n");
    say("You hear a slight rustling from the side of the road.\n");
    tell_room(RANGERS_AMB_DIR + "ambush_3a", QCTNAME(TP) + " is suddenly "
        + "standing beside you.\n");

    TP->move_living("M", RANGERS_AMB_DIR + "ambush_3a", 1, 0);
    return 1;
}


public void
bushes_alert(object ranger)
{
    ranger->catch_msg("Something about the bushes along the road catches "
        + "your eye.\n");
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(RANGERS_MEMBER(ob))
        set_alarm(0.5, 0.0, &bushes_alert(ob));

}
