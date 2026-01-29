#include "defs.h"

inherit PARTY_BASE;

object lotho;

void
create_party_room()
{
    add_prop(ROOM_S_MAP_FILE, "party.txt");

    set_short("A white gateway");
    set_long("This is the entrance point where party-goers arrive. "+
      "A pearl white gate stands to the north of you and a guard post "+
      "has been placed here to make sure no trouble occurs at the party. "+
      "To the east is a small money lenders tent"+
      (PARTY_MASTER->query_costumes() ? ", to the west a blue tent has "+
	"been placed," : "") + " and to the south a grand pavilion stands.\nA large sign.\n");
    add_item(({"white gate","gate","pearl white gate"}),
        "The pearl white gate stands seven feet high. Its flawless " +
        "design shimmers with an air of enchantment.\n");
    add_item(({"post","guard post"}),
        "A quickly assembled guard post has been placed here. It houses " +
        "the Shirriffes hired to make sure the party goes on without " +
        "any trouble makers.\n");
    add_item(({"tent","lenders tent","money lenders tent"}),
        "The money lender's tent is small and brightly colored. It is " +
        "round with a tall pennant rising from the center of the tent. " +
        "The tent is clean and large enough to hold many hobbit-folk. The " +
        "flaps are pulled back, forming an open entrance.\n");
    add_item(({"pennant", "large pennant", "large flag", "flag"}),
        "The pennant is large and forrest green. It is triangular shaped " +
        "and rises above the money lenders tent. The pennant waves lazily " +
        "in a breeze.\n");

    add_item("sign",
        "The sign is large and painted white. It is next to the guard post " +
        "and is probably worth reading.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

    if (PARTY_MASTER->query_costumes())
    	add_exit(PARTY_DIR + "costume_shop", "west",0,1);
    else
        add_exit(PARTY_DIR + "costume_shop", "west","@@tent_closed@@");

    add_exit(PARTY_DIR + "bank", "east", 0, 1);
    add_exit(PARTY_DIR+"podium","south");
    reset_shire_room();
}

void
reset_shire_room()
{
    if (!lotho)
    {
	lotho = clone_object(PARTY_NPC+"lotho");
	tell_room(TO,"A hobbit arrives at his post.\n");
	lotho->move(TO);
    }
}

string read_sign()
{
    return "On the sign you see painted in bright letters you read:\n\n" +
        "\tThese commands are available to you throughout the party area.\n\n" +
        "\temote (str)     :   To make your own emotion.\n" +
        "\tinvite <person> :   To invite someone to the party.\n" +
        "\thelp room       :   To find out what commands you have\n" +
        "\t                    for each room (if any).\n" +
        "\treturn          :   To return to where you came from before " +
            "the party.\n" +
        "\tboot <player>   :   Show an ill-mannered player the door.\n" +
        "\tend party       :   This ends the party and removes everyone\n" +
        "\t                    from the party area.\n\n" +
        "You can type <help party> anywhere in the party area to see " +
            "this information.\n\n";
}

int
tent_closed()
{
    if (this_player()->query_wiz_level()) return 0;

    write("The costume tent is closed. The proprietor must have run out " +
        "of supplies and is off getting more. Hopefully it will open for " +
        "the next party.\n");
    return 1;
}