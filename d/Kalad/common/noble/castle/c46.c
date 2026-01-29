// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

object  hc_member, hc_member2, hc_member3, hc_member4,
        zintra,
        guard = allocate(3);

int guards_called;

void
call_to_remove_corpse(object enemy)
{
    tell_room(TO,"A servent dashes in to drag out the lifeless "+
        "body that was "+QTNAME(enemy)+".\n",enemy);
    enemy->move_living("M",NOBLE + "wayfarer/s8",1,1);
    tell_room(ENV(enemy),"A servant enters and drops a body, then "+
        "leaves again.\n",enemy);
}
    
void
call_guards(object enemy)
{
    if (guards_called)
        return;

    guard = clone_npcs(guard, NOBLE + "npc/castle_guard");

    guard[0]->team_join(guard[1]);
    guard[0]->team_join(guard[2]);

    if (present(guard[0]))
        guard[0]->command("shout We shall help you!");

    guards_called = 1;
}

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    set_long("You have entered a large and splendid chamber filled with "+
        "many high nobles. There is a giant circular table in the center "+
        "of the room, with many comfortable chairs all around it. The "+
        "walls are draped with giant tapestries and ornaments. There is "+
        "a large glass window overlooking the table, letting light shine "+
        "through to illuminate the room. There are two rows of benches "+
        "on the sides of the room surrounding the table in the center. The "+
        "ground is covered with a rich, black fur rug. There is a large "+
        "golden plaque above your head in the doorway.\n");

    INSIDE;

    add_item("table","The table is made of highly polished oak, and at "+
        "each chair there is a steel plate on the edge of the table with "+
        "a name on it. There are papers and pens and ink bottles scattered "+
        "among the table, as well as a few scrapes of food and wine glasses.\n");
    add_item("chairs","The chairs are made of wood, and are padded with "+
        "down filled cusions.\n");
    add_item("tapestries","There are many maginficant tapestries hanging "+
        "about. They are of many colors and patterns.\n");
    add_item("ornaments","You see ancient weapons and animal heads "+
        "among the walls, as well as ornate candle holders and glassballs.\n");
    add_item("window","Looking through the window, you see the "+
        "bright blue sky and the eternal Kaladian sun.\n");
    add_item("benches","The wooden benches contain a few spectators.\n");
    add_item("spectators","They come here to observe the meetings of "+
        "the High Council.\n");
    add_item("rug","The rug seems to be made of some furry black "+
        "animal.\n");
    add_item("plaque","The plaque reads: The High Council.\n");
    add_cmd_item("plaque","read","The Plaque reads: The High Council.\n");

    add_exit(NOBLE + "castle/c45", "west");

    reset_room();
}


void
reset_room()
{
    hc_member = clone_npcs(hc_member, NOBLE + "npc/council_noble");
    hc_member2 = clone_npcs(hc_member2, NOBLE + "npc/council_noble2");
    hc_member3 = clone_npcs(hc_member3, NOBLE + "npc/council_noble");
    hc_member4 = clone_npcs(hc_member4, NOBLE + "npc/council_noble2");
    zintra = clone_npcs(zintra, NOBLE + "npc/zintra_in_council");

    guards_called = 0;
}

