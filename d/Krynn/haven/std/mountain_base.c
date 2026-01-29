/* Mountain base file for Haven.
* By Morrigan, Jan 97
*/

#include "../local.h"

inherit OUT;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "mountains", }) );

public void
reset_haven_room()
{
    set_searched(random(2));
}

public void
create_mountain()
{

}

nomask void
create_haven_room()
{
    set_place(MOUNTAINS);
    set_long_desc("You travel through the mountains, on the road between " +
      "Solace and Haven.");

    add_item(({"peaks","twin peaks", "Twin Peaks"}),"The Twin Peaks are the "+
      "highest Peaks of the mountains around Darken Wood, the road travels "+
      "between them.\n");
    add_item("sky","It's above you.\n");
    add_item(({"road","winding road"}),"You travel the road to Haven, which "+
      "is to the distant south.\n");
    add_item(({"Kharolis", "kharolis", "Kharolis Mountains", "kharolis mountains"}),
      "The massive range of mountains known as the Kharolis loom to your west, "+
      "travelling both northwards and southwards far beyond the range of your "+
      "vision.\n");
    add_item(({"smaller range", "smaller mountains"}), "This range of mountains "+
      "surrounds the dread forests of Darken Wood, for which you are quite "+
      "glad. It is said that no one has returned from that fell land.\n");
    add_item(({"range", "mountain range"}), "Which range? The Kharolis or the "+
      "smaller range surrounding Darken Wood?\n");
    add_item(({"foothills","hills"}),"The foothills are rolling, and seem to "+
      "melt into the mountains.\n");
    add_item("mountains","The mountains lining Darken Wood lie to your east, "+
      "forming a barrier around the haunted woods, and the Kharolis mountains "+
      "loom over you from the west.\n");
    add_item("mountain","Every mountain looks similar to you, and none stand out.\n");
    add_item(({"foothill","hill"}),"The hills are alike in most ways, although " +
      "they each have their individual differences, of course.\n");

    set_tell_time(500);
    add_tell("You notice a few dwarves climbing through the mountains here, "+
      "probably headed to Solace.\n");
    add_tell("A few rocks come skittering down the mountains to your south, "+
      "startling you, but causing no real damage.\n");
    add_tell("The shrill cry of a bird pierces the otherwise quiet atmosphere.\n");
    add_tell("The sounds you make echo through the many crevices of the "+
      "mountains you're climbing through.\n");

    OUTSIDE;

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({ "road", "winding road", }), 3);

    create_mountain();
    reset_room();

}

void
enter_inv (object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}

