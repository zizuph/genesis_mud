#pragma save_binary

inherit "/std/workroom";
#include "/secure/std.h"
#include <macros.h>

create_workroom()
{
    object bb;

    set_short("Administrator's workroom");
    set_long("You find yourself in the workroom of the administrators of Genesis.\n" +
	     "The room is large and well-lit and you can't help feeling rather small\n" +
	     "and insignificant.\n\n" +
	     "In the end of the room opposite to the entrance area you can see a group\n" +
	     "of chairs around a table. That must be the place where the administrators\n" +
	     "come together to plan the development of Genesis. You can see some papers\n" +
	     "on the grand table.\n\n");
    
    add_item(({"table", "grand table"}), 
	     "The grand table dominates the far end of the room. Around it are set chairs\n" +
	     "of different designs, apparently all made to suit very individual shapes\n" +
	     "and tastes. The table itself is about two meters wide and five meters in\n" +
	     "length. It is littered with random notes and papers, apparently left there\n" +
	     "by the administrators after their last meeting.\n");

    add_item(({"note", "notes", "paper", "papers"}),
	     "Your curiousity and snoopiness has been noted and logged. Please report to\n" +
	     "Master Tintin for demotion within three days of reading this note.\n");

    add_item(({"chair", "chairs"}),
        "There is a huge leather chair, an inlaid wooden chair and a plush red chair\n" +
        "which immediately draw your eye.  The other chairs range from the ascetic to\n" +
        "the decadent, an apparent reflection of the owner's personality.\n");

    add_item(({"first chair", "fattys chair", "huge chair", "leather chair", "huge leather chair"}),
        "You immediately identify this as Master Fatty's chair.  Nothing but an\n" +
        "immensely fat gnome could possibly fit into the huge leather monstrosity\n" +
        "supported by an immense number of very sturdy legs you find at one end of\n" +
        "the table.\n");

    add_item(({"second chair", "mrprs chair", "inlaid chair", "wooden chair", "inlaid wooden chair"}),
        "You immediately identify this as Master Mrpr's chair.  It is at the opposite\n" +
        "end of the table from Fatty's chair.  It is a practial-looking wooden chair\n" +
        "inlaid with intricate carvings of pictograms.\n");

    add_item(({"third chair", "plush chair", "red chair", "plush red chair"}),
        "This chair looks quite soft and comfortable.  The ruby hue of the cloth\n" +
        "seems to shimmer in the soft light of the room.  From the runes decorating\n" +
        "the frame of the chair, you decide this must belong to Quis.\n");

    add_item(({"fourth chair","black chair","geds chair"}),
	     "This chair looks very powerful. It hovers over the ground due to some\n"+
	     "magical field. You feel that this chair is controlled by Ged.\n");

    add_exit("/d/Genesis/wiz/virtual", "virtual", 0, 0);
    add_exit("@@goto_start", "start", 0, 0);

    bb = clone_object("/d/Genesis/wiz/applboard");
    bb->move(this_object());
}

string
wizinfo()
{
    return "This room has some special uses besides holding the administrators board.\n\n" +
	"It is only here you can banish names. Do 'help banish' if you are uncertain of\n" +
	"the exact syntax\n";
}
