// file name: d/Avenir/common/outpost/fort1.c
// creator(s):  Kazz    Feb '95
// last update: Lilith Apr 2022 for Fort Makeover
// purpose:     outpost guard room
// note:	various dwarves gather here if needed to defend the fort.
// bug(s):
// to-do:       

#include "/d/Avenir/common/outpost/outpost.h"

inherit "/d/Avenir/inherit/tail";
inherit OUTPOST +"fort_base";

void
create_fort_room()
{
	// add_exit_views() uses the short, so using lower case and articles.
    set_short("the guard's common room");
    set_long("This large room seems to be the common room where "+
	  "the guards of Fort Sybarus spend their time when off-duty. "+
      "Tables with stools and benches fill the room. "+
      "Various dwarves move around, talking, sitting, tending "+
      "weapons and armour. "+ 
      "Half of the north wall is the black stone of the fort, "+
      "while the other half marks the beginning of the natural "+
	  "stone of the cavern wall. "+
      "South you can see the central courtyard of the fortress. "+
	  "An archway leads west into the North Tower, while "+
      "east is another room which appears to a dining hall. "+
      "\nTwo large signs have been posted high on the far "+
      "wall.\n");

    add_exit("fort4","east");
    add_exit("fort3","south");
    add_exit("adv_guild", "west");
	
    add_npc(MON + "dw_guard_offduty", 3);
	room_add_object(OBJ +"seats/obsidian_bench", 1);
	room_add_object(OBJ +"seats/basalt_bench", 1);
	room_add_object(OBJ +"seats/stool", 1);
	room_add_object(OBJ +"table_commonrm", 1);

    // These are in the fort_base.c
	add_exit_views();
    add_fort_room();
	
    add_item(({"wall", "north wall"}),
      "Only half of the northern wall is constructed, the other "+
	  "half is the natural cavern wall, which curves overhead to "+
	  "the southeast.\n" );

    add_item(({"west wall", "western wall", "signs"}),
      "There are two signs on this wall. Both have huge letters "+
      "above them. One reads 'INFIDELS' and the other reads "+
      "'ABSOLVED'.\n");
    add_item(({"sign"}),
      "Which one? The infidels sign or the absolved sign?\n");  
    add_item(({"infidel", "infidels", "infidels sign", "infidel sign"}),
      "@@do_infidel@@The people listed above are infidels unless "+
      "their names also appear on the 'absolved' sign.\n");
    add_cmd_item(({"infidel", "infidels", "infidels sign", "infidel sign"}),
      "read",
      "@@do_infidel@@The people listed above are infidels unless "+
      "their names also appear on the 'absolved' sign.\n");
    add_item(({"absolved", "absolved sign"}),
      "@@do_absolved@@The people listed above have been "+
      "absolved of their crimes.\n");
    add_cmd_item(({"absolved", "absolved sign"}), "read",
      "@@do_absolved@@The people listed above have been "+
      "absolved of their crimes.\n");

	reset_fort_room();

} 

string
do_infidel()
{
    string text;
    text = read_file("/d/Avenir/log/misc/malefactor");
    this_player()->more(text);
    return "\n";      
}

string
do_absolved()
{
    string text;
    text = read_file("/d/Avenir/log/misc/absolved");
    this_player()->more(text);
    return "\n";      
}
