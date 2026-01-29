inherit "/std/workroom";

void create_workroom()
{
    set_short("Damax's studio");
    set_long("This is Damax's studio.  The walls and floor are made from a dark, glossy\n"
	+"wood that you don't recognize.  A simple cot sits in one corner, and a large\n"
        +"large wooden table adorns the room's center.  Maps, scrolls and several very\n"

        +"thick C manuals cover the surface of the table.\n"); 
    add_exit("/d/Genesis/start/human/town/tower", "human", 0);
    add_exit("/d/Genesis/wiz/entrance", "news", 0);
    add_exit("/d/Genesis/wiz/domain", "domain", 0);
    add_exit("/d/Genesis/wiz/idea", "idea", 0);
    add_exit("/d/Genesis/wiz/discuss", "discuss", 0);
    add_exit("/d/Genesis/wiz/lpc", "lpc", 0);
    add_exit("/d/Genesis/wiz/infotool", "tool", 0);
    add_exit("/d/Genesis/wiz/post", "post", 0);
    add_exit("/d/Dville/workroom", "meet", 0);
    add_exit("/d/Dville/glykron/palace/stairs", "stair", 0);
    add_exit("/d/Dville/glykron/palace/guild", "guild", 0);
    add_exit("/d/Dville/common/entrance", "common", 0);
}
