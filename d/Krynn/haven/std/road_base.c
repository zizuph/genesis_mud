/* Road base file for Haven.
* By Morrigan, Jan 97
*/

#include "../local.h"

inherit OUT;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "hills", }) );

public void
reset_haven_room()
{
    set_searched(random(2));
}

public void
create_road()
{

}

nomask void
create_haven_room()
{
    set_place(ROAD);
    set_long_desc("The mountains lining Darken wood rise up to your east, "+
      "and dusty plains stretch out to the west.");

    add_item(({"peaks","twin peaks", "Twin Peaks"}),"The Twin Peaks are the "+
      "highest Peaks of the mountains around Darken Wood, the road travels "+
      "between them. They lie to the north of you.\n");
    add_item("sky","It's above you.\n");
    add_item(({"road","winding road"}),"You travel the road to Haven, which "+
      "is to the south.\n");
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
    add_item(({"plants","scraggly plants"}),"Some of the plants may be useful "+
      "herbs.\n");
    add_item("plant","This plant may be a useful herb.\n");
    set_tell_time(400);
    add_tell("You notice a caravan of travellers stopped alongside the road as "+
      "you pass, probably resting before they continue.\n");
    add_tell("A group of dwarves stomp past you, travelling north towards the "+
      "mountains.\n");
    add_tell("A few of the plainsmen from the east travel the road, their " +
      "legs taking long strides as they make their way towards Haven.\n");
    add_tell("You hear the distant sound of what seems like a wolf howling from "+
      "the mountains to the far west.\n");
    add_tell("A group of birds passes overhead, their shadows racing along " +
      "the dark ground here.\n");
    add_tell("In the far north you notice the clouds are exceptionally dark, "+
      "probably a fierce storm raging in the northern lands.\n");

    OUTSIDE;

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({ "scraggly plants", "plant", "plants", }), 3);

    create_road();
    reset_room();

}

void
enter_inv (object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}

